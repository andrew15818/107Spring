#ifndef AGGREGATE_H
#define AGGREGATE_H
#include "Table.h"
#include "Command.h"
#include "User.h"

void handle_aggreg(Table_t *table,Command_t *cmd, int *idxList, int idx_length);
double average(Table_t *table,int *idxList, int idx_length, Command_t *cmd, int curr_arg);
double count(Table_t *table, int *idxList, int idx_length, Command_t *cmd);
double sum(Table_t *table,int *idxList, int idx_length);

#endif
