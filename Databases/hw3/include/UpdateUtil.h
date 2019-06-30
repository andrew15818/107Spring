#ifndef UPDATEUTIL_H
#define UPDATEUTIL_H
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Command.h"
#include "User.h" //Justo get some constants
#include "Table.h"

void doUpdateToList(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd,char * fieldName, char * fieldValue);
void update_cmd_handler(Command_t * cmd);//En el de select tambien reciben un id pero no estoy seguro por que.
void upt_condition_state_handler(Command_t *cmd, size_t arg_idx);
#endif
