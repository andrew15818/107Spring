#ifndef AGGREGATE_FUNCTIONS_H
#define AGGREGATE_FUNCTIONS_H

#include "Table.h"
#include "Command.h"
#include "User.h"
#include <string.h>

int sum(Table_t * table, int * idxList, size_t listSize, char * fieldName);
int count(Table_t * table, Command_t *cmd, int * idxList,size_t listSize);
double  avg(Table_t * table, int * idxList, size_t listSize, char * fieldName);
void display_agg_info(Table_t * table,  Command_t *cmd, int * idxList,size_t listSize);

char * get_aggregator_param(char * argValue);

#endif
