#include "UpdateUtil.h"

//
// We take all information and organize it into cmd itself
//
void update_cmd_handler(Command_t * cmd){
    size_t arg_idx =0;
    cmd->condArgs.whereConditions = -1;
    cmd->condArgs.ANDsAmount = 0;
    cmd->condArgs.ORsAmount = 0;
    
    //I dont think we care about anything before the "set" keyword so ill fast forward to
    //that here
    while(strncmp(cmd->args[arg_idx++],"set",3) != 0);
    //after that we should have our first update string
    
    //Since we are only taking one column to update we can just do it here
    //first we store the column we want to save 
    //find position of the equal sign
    //TODO see if there is a better way to update this 
    strncpy(cmd->cmd_args.upt_args.fieldNameToUpt,cmd->args[arg_idx++],255+1);
    arg_idx++;
    //Now we get the value to update to
    strncpy(cmd->cmd_args.upt_args.valToUptTo,cmd->args[arg_idx],255+1);
    while(arg_idx < cmd->args_len){
        //TODO AQUI TE QUEDASTE TERMINA DE ORGANIZAR TAL COMO SELECT STATE 
        //if(!strncmp(cmd->args[arg_idx],"j)){
        if (!strncmp(cmd->args[arg_idx], "where", 5)) {
            upt_condition_state_handler(cmd,arg_idx+1);
        }
        arg_idx +=1;
    }

}

void doUpdateToList(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd,char * fieldName, char * fieldValue){
    size_t searchLen =  (idxList != NULL)? idxListLen: table->len;
    User_t *  usr_ptr;

    //HACKMDMOD: As per Q9 in Hackmd if more than a row wants to be updated then we dont update
    //anything
    //if(idxListLen != 1)return;
    //bool legalQuery = true;
    if (!strncmp(fieldName, "id", 2)) {
        if (idxListLen > 1 || idxList == NULL) return;
        for (size_t idx = 0; idx < table->len; idx++) {
            if (get_User(table, idx)->id == strtoul(fieldValue,NULL,10))
                return;
        }
    }
    //ENDHACKMDMOD

    for (size_t idx = 0; idx < searchLen; idx++) {
        if (idxList) {
            usr_ptr = get_User(table, idxList[idx]);
        }else{
            usr_ptr = get_User(table, idx);
        }
        //heck if age or id
        if(!strncmp(fieldName,"id",2)){
            // As per Q9 answer the primary key must not be changed
            usr_ptr->id = strtoul(fieldValue,NULL,10);
        } else if(!strncmp(fieldName,"name",4)){
            strncpy(usr_ptr->name,fieldValue, MAX_USER_NAME);
        } else if(!strncmp(fieldName,"email",5)){
            strncpy(usr_ptr->email,fieldValue, MAX_USER_EMAIL);
        } else if(!strncmp(fieldName,"age",3)){
            usr_ptr->age = strtoul(fieldValue,NULL,10);
        }
    }
}

void upt_condition_state_handler(Command_t *cmd, size_t arg_idx) {//TODO modificiaste por aca
        cmd->condArgs.whereConditions = 1;//simply implying that we have a "where" clause, i.e. at least one condition
    if (arg_idx < cmd->args_len) {
        //check the amount of conditions
        size_t tempIdx = arg_idx;
        while(
                tempIdx+3 < cmd->args_len &&//TODO im not so sure about this, i dont know if C has the same thing as c++ where it stops as soon as it detects the first false
                (!strncmp(cmd->args[tempIdx+3],"and",3) || !strncmp(cmd->args[tempIdx+3],"or",2) )
                ){
            cmd->condArgs.whereConditions += 1;
            if(!strncmp(cmd->args[tempIdx+3],"and",3))
                cmd->condArgs.ANDsAmount +=1;
            if(!strncmp(cmd->args[tempIdx+3],"or",3))
                cmd->condArgs.ORsAmount +=1;
            tempIdx += 4;//set it to the field name of the next condition
        }
        //This is where limits and offsets were checked back in selection
    }
    cmd->type = UPDATE_CMD;
    return;
}


