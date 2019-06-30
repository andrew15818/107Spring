#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "Util.h"
#include "Command.h"
#include "Table.h"
#include "SelectState.h"
#include "AggregateFunctions.h"
#include "UpdateUtil.h"
#include "DeleteUtil.h"

///
/// Allocate State_t and initialize some attributes
/// Return: ptr of new State_t
///
State_t* new_State() {
    State_t *state = (State_t*)malloc(sizeof(State_t));
    state->saved_stdout = -1;
    return state;
}

///
/// Print shell prompt
///
void print_prompt(State_t *state) {
    if (state->saved_stdout == -1) {
        printf("db > ");
    }
}

///
/// Print the user in the specific format
///
void print_user(User_t *user, SelectArgs_t *sel_args) {
    size_t idx;
    printf("(");
    for (idx = 0; idx < sel_args->fields_len; idx++) {
        if (!strncmp(sel_args->fields[idx], "*", 1)) {
            printf("%d, %s, %s, %d", user->id, user->name, user->email, user->age);
        } else {
            if (idx > 0) printf(", ");

            if (!strncmp(sel_args->fields[idx], "id", 2)) {
                printf("%d", user->id);
            } else if (!strncmp(sel_args->fields[idx], "name", 4)) {
                printf("%s", user->name);
            } else if (!strncmp(sel_args->fields[idx], "email", 5)) {
                printf("%s", user->email);
            } else if (!strncmp(sel_args->fields[idx], "age", 3)) {
                printf("%d", user->age);
            }
        }
    }
    printf(")\n");
}

///
/// Print the users for given offset and limit restriction
///
void print_users(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd) {
    size_t idx;
    int limit = cmd->cmd_args.sel_args.limit;
    int offset = cmd->cmd_args.sel_args.offset;

    if (offset == -1) {
        offset = 0;
    }

    if (idxList) {
        for (idx = offset; idx < idxListLen; idx++) {
            if (limit != -1 && (int)(idx - offset) >= limit) {
                break;
            }
            print_user(get_User(table, idxList[idx]), &(cmd->cmd_args.sel_args));
        }
    } else {
        for (idx = offset; idx < table->len; idx++) {
            if (limit != -1 && (int)(idx - offset) >= limit) {
                break;
            }
            print_user(get_User(table, idx), &(cmd->cmd_args.sel_args));
        }
    }
}

///
/// This function received an output argument
/// Return: category of the command
///
int parse_input(char *input, Command_t *cmd) {
    char *token;
    int idx;
    token = strtok(input, " ,\n");
    for (idx = 0; strlen(cmd_list[idx].name) != 0; idx++) {
        if (!strncmp(token, cmd_list[idx].name, cmd_list[idx].len)) {
            cmd->type = cmd_list[idx].type;
        }
    }
    while (token != NULL) {
        add_Arg(cmd, token);
        token = strtok(NULL, " ,\n");
    }
    return cmd->type;
}

///
/// Handle built-in commands
/// Return: command type
///
void handle_builtin_cmd(Table_t *table, Command_t *cmd, State_t *state) {
    if (!strncmp(cmd->args[0], ".exit", 5)) {
        archive_table(table);
        exit(0);
    } else if (!strncmp(cmd->args[0], ".output", 7)) {
        if (cmd->args_len == 2) {
            if (!strncmp(cmd->args[1], "stdout", 6)) {
                close(1);
                dup2(state->saved_stdout, 1);
                state->saved_stdout = -1;
            } else if (state->saved_stdout == -1) {
                int fd = creat(cmd->args[1], 0644);
                state->saved_stdout = dup(1);
                if (dup2(fd, 1) == -1) {
                    state->saved_stdout = -1;
                }
                __fpurge(stdout); //This is used to clear the stdout buffer
            }
        }
    } else if (!strncmp(cmd->args[0], ".load", 5)) {
        if (cmd->args_len == 2) {
            load_table(table, cmd->args[1]);
        }
    } else if (!strncmp(cmd->args[0], ".help", 5)) {
        print_help_msg();
    }
}

///
/// Handle query type commands
/// Return: command type
///
int handle_query_cmd(Table_t *table, Command_t *cmd) {
    if (!strncmp(cmd->args[0], "insert", 6)) {
        handle_insert_cmd(table, cmd);
        return INSERT_CMD;
    } else if (!strncmp(cmd->args[0], "select", 6)) {
        handle_select_cmd(table, cmd);
        return SELECT_CMD;
    } else if (!strncmp(cmd->args[0], "update", 6)) {
        handle_update_cmd(table, cmd);
        return UPDATE_CMD;
    } else if (!strncmp(cmd->args[0], "delete", 6)) {
        handle_delete_cmd(table, cmd);
        return DELETE_CMD;
    } else {
        return UNRECOG_CMD;
    }
}

///
/// The return value is the number of rows insert into table
/// If the insert operation success, then change the input arg
/// `cmd->type` to INSERT_CMD
///
int handle_insert_cmd(Table_t *table, Command_t *cmd) {
    int ret = 0;
    User_t *user = command_to_User(cmd);
    if (user) {//If use was succesfully created(we havent yet assigned a place to save the users pointer)
        ret = add_User(table, user);//now we do that 
        if (ret > 0) {
            cmd->type = INSERT_CMD;
        }
    }
    return ret;
}

///
/// The return value is the number of rows select from table
/// If the select operation success, then change the input arg
/// `cmd->type` to SELECT_CMD
///
int handle_select_cmd(Table_t *table, Command_t *cmd) {
    cmd->type = SELECT_CMD;
    field_state_handler(cmd, 1);

    //we can create two cases, when we have conditions and when we dont
    if(cmd->cmd_args.sel_args.aggregatorAmount > 0){
        if(cmd->condArgs.whereConditions != -1){
            int listo[table->len];//todo maybe change that size?
            size_t idxlen = getWhereList(table,cmd,listo);
            if (cmd->cmd_args.sel_args.offset <= 0 && (cmd->cmd_args.sel_args.limit > 0 || cmd->cmd_args.sel_args.limit == -1))
                display_agg_info(table, cmd, listo, idxlen);
        }else{
            if (cmd->cmd_args.sel_args.offset <= 0 && (cmd->cmd_args.sel_args.limit > 0 || cmd->cmd_args.sel_args.limit == -1))
                display_agg_info(table, cmd, NULL, 0);
        }
    }else{
        if(cmd->condArgs.whereConditions != -1){
            int listo[table->len];//todo maybe change that size?
            //lammo para llenar arrayo
            size_t idxlen = getWhereList(table,cmd,listo);
            print_users(table, listo, idxlen, cmd);
        }else{
            print_users(table, NULL, 0, cmd);
        }
    }
    return table->len;
}

int handle_update_cmd(Table_t *table, Command_t *cmd){
    cmd->type = UPDATE_CMD;
    update_cmd_handler(cmd);//organize stuff here
    
    //Cycle through parameters until set is found
    int argIdx = 0;
    while(strncmp(cmd->args[argIdx++],"set",3));

    char * fieldName = cmd->args[argIdx];
    char * valueToChangeTo;

    //find field value
    valueToChangeTo = cmd->args[argIdx+2];

    //we have all the values we want, now we use where to get the list to update, if where
    //was not used then we simply pass a null list
    if(cmd->condArgs.whereConditions != -1){
        int listo[table->len];
        //lammo para llenar arrayo
        size_t idxlen = getWhereList(table,cmd,listo);
        doUpdateToList(table, listo, idxlen, cmd,fieldName, valueToChangeTo);
    }else{
        doUpdateToList(table, NULL, 0, cmd,fieldName,valueToChangeTo);
    }
    return 0;

}
int handle_delete_cmd(Table_t *table, Command_t *cmd){
    cmd->type = DELETE_CMD;
    del_cmd_handler(cmd);//organize stuff here
    
    //Get where list as usual
    if(cmd->condArgs.whereConditions != -1){
        int listo[table->len];
        //lammo para llenar arrayo
        size_t idxlen = getWhereList(table,cmd,listo);
        doDeleteFromTable(table, listo, idxlen, cmd);
    }else{
        doDeleteFromTable(table, NULL, 0, cmd);
    }
    return 0;
    
}
///
/// Get list of IDs that comply with WHERE clauses
///
size_t getWhereList(Table_t *table, Command_t* cmd, int * list){
    //If we ge t here is because we have atleast one condition, so we dont have to check
    //that *again*
    size_t idx = 0;
    // Now we loop until we get the first field name
    while(strncmp(cmd->args[idx],"where",5)){
        idx++;
    }
    idx++;
    //Now we 
    char * fieldName = cmd->args[idx++];
    char * operatorchar = cmd->args[idx++];
    char * immField = cmd->args[idx++];

    char * fieldName2;
    char * operatorchar2;
    char * immField2;
    if(cmd->condArgs.ANDsAmount > 0 || cmd->condArgs.ORsAmount> 0){//then this means we have a second condition 
        idx++;//Skip the logical operator
        fieldName2 = cmd->args[idx++];
        operatorchar2 = cmd->args[idx++];
        immField2 = cmd->args[idx++];
    }
    size_t tableidx =0;
    size_t listIdx= 0;

    User_t * usr_ptr;
    while(tableidx < table->len){

        usr_ptr = get_User(table, tableidx);
        bool cond1 = subCompare(fieldName,operatorchar,immField,usr_ptr);

        if(cmd->condArgs.ANDsAmount > 0){
            if(cond1 && subCompare(fieldName2,operatorchar2,immField2,usr_ptr)){
                list[listIdx++] = tableidx;
            }
        }else if(cmd->condArgs.ORsAmount > 0 ){
            if(cond1 || subCompare(fieldName2,operatorchar2,immField2,usr_ptr)){
                list[listIdx++] = tableidx;
            }
        }else if(cond1 == true){
            list[listIdx++] = tableidx;
        }
        tableidx++;
    }
    return listIdx;
}
/// When returning 0 we mean false otherwise(usually 1) we mean true
bool subCompare(char * fieldName, char * operatorchar, char * literal,User_t* usr_ptr){
    bool isNumber = (strtoul(literal,NULL,10) == 0 && strncmp(literal,"0",1))? 0: 1;//if 0 then false otherwise true 
    char * fieldValueC;
    unsigned int fieldValueI;

    if (!strncmp(fieldName,"id",2))
        fieldValueI = usr_ptr->id;
    else if(!strncmp(fieldName,"age",3))
        fieldValueI = usr_ptr->age;
    else if(!strncmp(fieldName,"email",5))
        fieldValueC = usr_ptr->email;
    else if(!strncmp(fieldName,"name",4))
        fieldValueC = usr_ptr->name;

    if(!strncmp(operatorchar,"=",1)){//Todos pueden ser igualados
        if(isNumber)
            return (fieldValueI == strtoul(literal,NULL,10));
        else
            return (!strcmp(fieldValueC,literal));
    } else if(!strncmp(operatorchar, "!=",2)){
        if(isNumber)
            return fieldValueI != strtoul(literal,NULL,10);
        else
            return (strcmp(fieldValueC,literal) == 0)? false: true;
    } else if(!strncmp(operatorchar, ">=",2)){
        return fieldValueI >= strtoul(literal,NULL,10);
    } else if(!strncmp(operatorchar, "<=",2)){
        return fieldValueI <= strtoul(literal,NULL,10);
    } else if(!strncmp(operatorchar, ">",1)){
        return fieldValueI > strtoul(literal,NULL,10);
    } else if(!strncmp(operatorchar, "<",1)){
        return fieldValueI < strtoul(literal,NULL,10);
    }
    return false;
}

///
/// Show the help messages
///
void print_help_msg() {
    const char msg[] = "# Supported Commands\n"
    "\n"
    "## Built-in Commands\n"
    "\n"
    "  * .exit\n"
    "\tThis cmd archives the table, if the db file is specified, then exit.\n"
    "\n"
    "  * .output\n"
    "\tThis cmd change the output strategy, default is stdout.\n"
    "\n"
    "\tUsage:\n"
    "\t    .output (<file>|stdout)\n\n"
    "\tThe results will be redirected to <file> if specified, otherwise they will display to stdout.\n"
    "\n"
    "  * .load\n"
    "\tThis command loads records stored in <DB file>.\n"
    "\n"
    "\t*** Warning: This command will overwrite the records already stored in current table. ***\n"
    "\n"
    "\tUsage:\n"
    "\t    .load <DB file>\n\n"
    "\n"
    "  * .help\n"
    "\tThis cmd displays the help messages.\n"
    "\n"
    "## Query Commands\n"
    "\n"
    "  * insert\n"
    "\tThis cmd inserts one user record into table.\n"
    "\n"
    "\tUsage:\n"
    "\t    insert <id> <name> <email> <age>\n"
    "\n"
    "\t** Notice: The <name> & <email> are string without any whitespace character, and maximum length of them is 255. **\n"
    "\n"
    "  * select\n"
    "\tThis cmd will display all user records in the table.\n"
    "\n";
    printf("%s", msg);
}

