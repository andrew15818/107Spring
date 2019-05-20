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
		if(cmd->has_where == 0 && (!strncmp(cmd->args[curr_arg],"avg(age)",8))){
			for(size_t j = 0; j<table->len; j++){
				User_t *tmp = get_User(table, j);
				sum+=tmp->age;
			}
			return (double)(sum/table->len);
		}
		if(!strncmp(cmd->args[curr_arg],"avg(age)",8)){
			for(size_t j=0; j<idx_length;j++){
				if(check_where(table, idxList[j], cmd,0)){
					User_t *tmp =get_User(table,idxList[j]);
					//printf("Checking the age of a user with id : %d\n", tmp->id);
					sum+=tmp->age;
					count++;
				}	
			}
			if(count==0){return 0;}
			return (double)(sum/count);
		}
		else if(!strncmp(cmd->args[curr_arg ],"avg(id)", 7)){
			for(int j=0; j<idx_length; j++){
				User_t *tmp = get_User(table, idxList[j]);
				sum+=tmp->id;
				count++;
			}
		}
			if(count==0){return 0;}
			return (double)(sum/count);
		
		return 0;
}
size_t sum(Table_t *table, int *idxList, int idx_length, Command_t *cmd , int curr_arg){
	size_t result =0;

	if(cmd->has_where ==0 && !strncmp(cmd->args[curr_arg],"sum(age)", 8)){	
		for(int j=0; j<table->len;j++){
			User_t *usr = get_User(table, j);
			result+=usr->age;
		
		}
	}
	else if(!strncmp(cmd->args[curr_arg],"sum(age)", 8 )){
		for(int j =0; j<idx_length; j++){
			User_t *tmp = get_User(table, idxList[j]);
			result+=tmp->age;
		}
	}
	return result;
}
int count(Table_t *table,int *idxList, int idx_length, Command_t *cmd){
	//printf("entering the count function\n");
	if(cmd->has_where == 0){return table->len;}
	int count =0;
	for(int j=0; j<idx_length;j++){
		if(check_where(table, idxList[j],cmd,0)){
			count++;	
		}
	}
	return count;
}
void handle_aggreg(Table_t *table, Command_t *cmd, int *idxList, int idx_length){
	//printf("Entering handle aggreg funct\n");
	for(int i =0; i<cmd->args_len;i++){
		if(!strncmp(cmd->args[i],"count(",6)){

			int quantity = count(table,idxList,idx_length,cmd);
			printf("(%d)\n", quantity);
		}else if (!strncmp(cmd->args[i],"avg(",3)){
		//	printf("Getting avg vibes from you :(\n");
			double avg = average(table, idxList, idx_length, cmd, i);	
			printf("(%.3lf)\n", avg);
		}else if(!strncmp(cmd->args[i],"sum(",4)){
			size_t summation = sum(table, idxList, idx_length,cmd,i);
			printf("(%ld)\n", summation);
		}
	}
	//printf("\n");

	return;
}

