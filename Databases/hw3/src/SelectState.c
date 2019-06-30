#include <string.h>
#include <stdlib.h>
#include "Command.h"
#include "SelectState.h"

void field_state_handler(Command_t *cmd, size_t arg_idx) {
    cmd->cmd_args.sel_args.fields = NULL;
    cmd->cmd_args.sel_args.fields_len = 0;
    cmd->cmd_args.sel_args.limit = -1;
    cmd->cmd_args.sel_args.offset = -1;
    cmd->condArgs.whereConditions = -1;
    cmd->condArgs.ANDsAmount = 0;
    cmd->condArgs.ORsAmount = 0;
    cmd->cmd_args.sel_args.aggregatorAmount = 0;
    while(arg_idx < cmd->args_len) {
        if (!strncmp(cmd->args[arg_idx], "*", 1)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "id", 2)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "name", 4)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "email", 5)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "age", 3)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "from", 4)) {
            table_state_handler(cmd, arg_idx+1);
            return;
        } else {
            // Check for aggregate functions remembering that we can only have one or
            // multiple aggregate functions in a query but no non-aggregate with
            // aggregates
            // They take care of the commas for us
            if (!strncmp(cmd->args[arg_idx], "sum", 3)) {
                cmd->cmd_args.sel_args.aggregatorAmount++;
            } else if (!strncmp(cmd->args[arg_idx], "avg", 3)){
                cmd->cmd_args.sel_args.aggregatorAmount++;
            } else if (!strncmp(cmd->args[arg_idx], "count", 4)){
                cmd->cmd_args.sel_args.aggregatorAmount++;
            } else {
                cmd->type = UNRECOG_CMD;
                return;
            }
        }
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
        } else if (!strncmp(cmd->args[arg_idx], "where", 6)) {
            condition_state_handler(cmd, arg_idx+1);
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

void condition_state_handler(Command_t *cmd, size_t arg_idx) {//TODO modificiaste por aca
        cmd->condArgs.whereConditions = 1;//simply implying that we have a "where" clause
    if (arg_idx < cmd->args_len) {
        //check the amount of conditions
        size_t tempIdx = arg_idx;
        while(
                tempIdx+3 < cmd->args_len &&
                (!strncmp(cmd->args[tempIdx+3],"and",3) || !strncmp(cmd->args[tempIdx+3],"or",2) )
                ){
            cmd->condArgs.whereConditions += 1;
            if(!strncmp(cmd->args[tempIdx+3],"and",3))
                cmd->condArgs.ANDsAmount +=1;
            if(!strncmp(cmd->args[tempIdx+3],"or",3))
                cmd->condArgs.ORsAmount +=1;

            tempIdx += 4;//set it to the field name of the next condition
            //printf("The amount of conditions so far is : %d\n",cmd->cmd_args.sel_args.whereConditions);
        }
        arg_idx= 3+tempIdx;
        //Now to check if it is right

        if (arg_idx == cmd->args_len) {
            return;
        } else if (arg_idx < cmd->args_len
                && !strncmp(cmd->args[arg_idx], "offset", 6)) {
            offset_state_handler(cmd, arg_idx+1);
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
void offset_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len) {//not the last argument(?)
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
