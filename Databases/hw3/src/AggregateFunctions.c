#ifndef AGGREGATE_FUNCTIONS
#define SELECT_STATE_H

#include "AggregateFunctions.h"

double avg(Table_t * table, int * idxList, size_t listSize, char * fieldName){
    size_t idx;
    double avg = 0;
    size_t searchLen =  (idxList != NULL)? listSize: table->len;
    User_t *  usr_ptr;
    for (idx = 0; idx < searchLen; idx++) {
        if (idxList) {
            usr_ptr = get_User(table, idxList[idx]);
        }else{
            usr_ptr = get_User(table, idx);
        }
        //Check if age or id
        if(!strncmp(fieldName,"id",2)){
            avg = ((avg*(idx)) + usr_ptr->id)/(idx+1);
        }else if(!strncmp(fieldName,"age",3)){
            avg = ((avg*(idx)) + usr_ptr->age)/(idx+1);
        }
    }
    return avg;
}
int sum(Table_t * table, int * idxList, size_t listSize, char * fieldName){
    size_t idx;
    unsigned int sum = 0;
    size_t searchLen =  (idxList != NULL)? listSize: table->len;
    User_t *  usr_ptr;
    for (idx = 0; idx < searchLen; idx++) {
        if (idxList) {
            usr_ptr = get_User(table, idxList[idx]);
        }else{
            usr_ptr = get_User(table, idx);
        }
        //heck if age or id
        if(!strncmp(fieldName,"id",2)){
            sum += usr_ptr->id;
        }else if(!strncmp(fieldName,"age",3)){
            sum += usr_ptr->age;
        }
    }
    return sum;
}
int count(Table_t * table, Command_t *cmd, int * idxList, size_t listSize){
    if(idxList)
        return listSize;
    else
        return table->len;
        

}
void display_agg_info(Table_t * table, Command_t *cmd, int * idxList,size_t listSize ){
    printf("(");
    for (int idx = 1/*Ignoreing "Select"*/; idx < cmd->cmd_args.sel_args.aggregatorAmount+1; idx++) {
        char * paramName =  get_aggregator_param(cmd->args[idx]);

        if (idx > 1) printf(", ");
        if (!strncmp(cmd->args[idx], "sum", 3)) {
            printf("%d",sum(table, idxList, listSize, paramName));
        } else if (!strncmp(cmd->args[idx], "count", 5)) {
            printf("%d",count(table,cmd, idxList, listSize));
        } else if (!strncmp(cmd->args[idx], "avg", 3)) {
            printf("%.3f",avg(table, idxList, listSize,paramName));//TODO Dont know if this works for doubles
        }
    }
    printf(")\n");
}

char* get_aggregator_param(char * argValue){
   size_t charIdx = 0; 
   while(argValue[charIdx++] != '(');
   return &argValue[charIdx];
}

#endif
