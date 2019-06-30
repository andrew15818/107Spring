#include "DeleteUtil.h"

//
// We take all information and organize it into cmd itself
//
void del_cmd_handler(Command_t * cmd){
    size_t arg_idx =0;//Hmm doent have to be 0 but a reasonably smalll number will find where if it exists
    //TODO im not sure if i have to initialize ALL values as in select file, maybe some
    //values may be carried accross queries and create some nasty logical errors
    cmd->condArgs.whereConditions = -1;
    cmd->condArgs.ANDsAmount = 0;
    cmd->condArgs.ORsAmount = 0;

    while(arg_idx < cmd->args_len){
        //TODO AQUI TE QUEDASTE TERMINA DE ORGANIZAR TAL COMO SELECT STATE 
        //if(!strncmp(cmd->args[arg_idx],"j)){
        if (!strncmp(cmd->args[arg_idx], "where", 5)) {
            del_condition_state_handler(cmd,arg_idx+1);
        }
        arg_idx++;
    }

}

void doDeleteFromTable(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd){
    // We will create a new buffer without the users we wish to delete
    //   We will make the buffer the same size of the table since of course are not adding
    //   anything thus we need no expansion, delallocation space could be wastefull since
    //   we might need it later
    User_t *new_user_buf = (User_t*)malloc(sizeof(User_t)*(table->capacity));//For user info
    //   also create a new cache buffer
    unsigned char *new_cache_buf = (unsigned char *)malloc(sizeof(unsigned char)*(table->capacity));//For the cache MAP(?)
    memset(new_cache_buf, 0, sizeof(unsigned char)*(table->capacity));

    size_t new_table_idx = 0;
    // THIS assumes the incoming idxList is in increasing order 
    size_t curDelListIdx = 0;
    size_t oldTableIdx = 0;
    if(!(idxListLen == 0 || idxList==NULL)){
        for (oldTableIdx = 0; oldTableIdx < table->len; oldTableIdx++) {
            /*printf("Cur oldTableIdx:%d and cur new table idx : %d with idxValu:%d \n",oldTableIdx,new_table_idx,idxList[curDelListIdx]);*/
            // Here we can assume that we have an idxList of non-zero length
            if(curDelListIdx< idxListLen){//if there are still rows to delete
                if(oldTableIdx != (size_t)idxList[curDelListIdx]/* Check that this user is not one to be deleted */){
                    memcpy((new_user_buf)+new_table_idx, table->users+oldTableIdx, sizeof(User_t));
                    new_cache_buf[new_table_idx] = 1;
                    new_table_idx++;
                }else{// If it is equal to an id we want to delete then
                    // We increase the searching indenx
                    curDelListIdx++;
                }
            }else{
                    memcpy((new_user_buf)+new_table_idx, table->users+oldTableIdx, sizeof(User_t));
                    new_cache_buf[new_table_idx] = 1;
                    new_table_idx++;
            }
        }
    }
    free(table->users);
    free(table->cache_map);
    table->users = new_user_buf;
    table->cache_map = new_cache_buf;
    table->len = new_table_idx;
    //Perhaps here we should delete it from the external file as well or simply archive
    //it(not sure if direct archive-ation will work though)
    //Table capacity remains the same

}

//TODO pretty much identical i thik to update, not much to see here
void del_condition_state_handler(Command_t *cmd, size_t arg_idx) {//TODO modificiaste por aca
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


