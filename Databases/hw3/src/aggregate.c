#include<stdlib.h>
#include<string.h>
#include"Util.h"
#include"User.h"
#include"Table.h"
#include"aggregate.h"
/*
 *Don't think i need to calculate wheres again for each user if i do that already in 
 *the handle select statement, we just need to get the id of each user in idxList.
 * */
double average(Table_t *table, int *idxList, int idx_length, Command_t *cmd, int curr_arg){
		double sum=0;
		size_t count=0;
		

		if(!strncmp(cmd->args[curr_arg],"avg(age)",8)){
			for(size_t j=0; j<idx_length;j++){
				if(check_where(table, idxList[j], cmd)){
					User_t *tmp =get_User(table,idxList[j]);
					sum+=tmp->age;
					count++;
				}	
			}
			return (double)(sum/count);
		}
		return 0;
}
double count(Table_t *table,int *idxList, int idx_length, Command_t *cmd){
	if(cmd->has_where == 0){return table->len;}
	double count =0;
	for(int j=0; j<idx_length;j++){
		if(check_where(table, idxList[j],cmd)){
			count++;	
		}
	}
	return count;
}
void handle_aggreg(Table_t *table, Command_t *cmd, int *idxList, int idx_length){

	for(int i =0; i<cmd->args_len;i++){
		if(!strncmp(cmd->args[i],"count(",6)){
			double quantity = count(table,idxList,idx_length,cmd);
			printf("(%lf) ", quantity);
		}else if (!strncmp(cmd->args[i],"avg(",3)){
			double avg = average(table, idxList, idx_length, cmd, i);	
			printf("(%lf) ", avg);
		}
	}
	printf("\n");
	return;
}

