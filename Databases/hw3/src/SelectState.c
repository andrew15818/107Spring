#include <string.h>
#include <stdlib.h>
#include "Command.h"
#include "SelectState.h"
#include<stdio.h>
void field_state_handler(Command_t *cmd, size_t arg_idx) {
    cmd->cmd_args.sel_args.fields = NULL;
    cmd->cmd_args.sel_args.fields_len = 0;
    cmd->cmd_args.sel_args.limit = -1;
    cmd->cmd_args.sel_args.offset = -1;
    while(arg_idx < cmd->args_len) {
		//printf("Current value of arg %ld: %s\n",cmd->args_len,cmd->args[arg_idx]);
        if (!strncmp(cmd->args[arg_idx], "*", 1 )) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "id", 2) && !cmd->has_where) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "name", 4) && !cmd->has_where) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "email", 5) && !cmd->has_where) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "age", 3) && !cmd->has_where) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if(!strncmp(cmd->args[arg_idx],"where", 5)){
				where_state_handler(cmd,arg_idx);
		} else if (!strncmp(cmd->args[arg_idx],"sum",3)){
				aggreg_state_handler(cmd, arg_idx);
		} else if (!strncmp(cmd->args[arg_idx],"count",5)){
				aggreg_state_handler(cmd,arg_idx);
		} else if(!strncmp(cmd->args[arg_idx],"avg",3)) {
				aggreg_state_handler(cmd,arg_idx);
		}else if (!strncmp(cmd->args[arg_idx], "from", 4)) {
            table_state_handler(cmd, arg_idx+1);
            //return;
        } else if(!strncmp(cmd->args[arg_idx], "table", 5)){
				arg_idx++;
				continue;
		}else {
            cmd->type = UNRECOG_CMD; 
			return; }
		arg_idx += 1;
    }
    cmd->type = UNRECOG_CMD;
	

    return;
}

void table_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len
            && !strncmp(cmd->args[arg_idx], "table", 5)) {

        arg_idx++;
        if (arg_idx == cmd->args_len) {
            return;
        } else if (!strncmp(cmd->args[arg_idx], "offset", 6)) {
            offset_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "limit", 5)) {
            limit_state_handler(cmd, arg_idx+1);
            return;
        }
    }
    cmd->type = UNRECOG_CMD;

    return;
}

void offset_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len) {
        cmd->cmd_args.sel_args.offset = atoi(cmd->args[arg_idx]);

        arg_idx++;

        if (arg_idx == cmd->args_len) {
            return;
        } else if (arg_idx < cmd->args_len
                && !strncmp(cmd->args[arg_idx], "limit", 5)) {

            limit_state_handler(cmd, arg_idx+1);
            return;
        }
    }
    cmd->type = UNRECOG_CMD;
    return;
}

void limit_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len) {
        cmd->cmd_args.sel_args.limit = atoi(cmd->args[arg_idx]);

        arg_idx++;

        if (arg_idx == cmd->args_len) {
            return;
        }
    }
    cmd->type = UNRECOG_CMD;
    return;
}
/*count the number of where args*/
void where_state_handler(Command_t *cmd, size_t arg_idx){
	cmd->has_where =1;
	cmd->where_count =1;
	for(int i =arg_idx ;i< cmd->args_len; i++){
		if(!strncmp(cmd->args[i], "and", 3)){
			cmd->has_and=1;
			cmd->where_count++;
		}else if(!strncmp(cmd->args[i], "or", 2)){
			cmd->has_or =1;	
			cmd->where_count++;
		}
	}
	//if(cmd->has_or){printf("There is an or here\n");}
	//if(cmd->has_where){printf("There is and and here\n ");}
	return;
}
void aggreg_state_handler(Command_t *cmd, size_t arg_idx){
	cmd->aggreg_count++;
	if(cmd->has_aggreg==0){cmd->has_aggreg++;}	
	//printf("Getting an aggreg arg in the form of: %s\n",cmd->args[arg_idx]);
	//printf("Current count of args: %ld\n",cmd->aggreg_count);
}
