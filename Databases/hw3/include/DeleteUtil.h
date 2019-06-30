#ifndef DELETEUTIL_H
#define DELETEUTIL_H
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Command.h"
#include "User.h" //Justo get some constants
#include "Table.h"

void doDeleteFromTable(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd);
void del_cmd_handler(Command_t * cmd);//En el de select tambien reciben un id pero no estoy seguro por que.
void del_condition_state_handler(Command_t *cmd, size_t arg_idx);
#endif
