#ifndef COMMAND_H
#define COMMAND_H

enum { 
    UNRECOG_CMD,
    BUILT_IN_CMD,
    QUERY_CMD,
};

enum {
    INSERT_CMD = 100,
    SELECT_CMD,
    UPDATE_CMD,
    DELETE_CMD,
};

typedef struct {
    char name[256];
    int len;
    unsigned char type;
} CMD_t;

extern CMD_t cmd_list[];

typedef struct SelectArgs {
    char **fields;
    size_t fields_len;
    int offset;
    int limit;
    int aggregatorAmount;
} SelectArgs_t;

typedef struct UpdateArgs {
    //char **fields; I dont think i need this, since we wiill only update one at a time
    //size_t fields_len; Creo que tampoco necesito esto
    char fieldNameToUpt[255+1];
    char valToUptTo[255+1];
} UpdateArgs_t;

typedef struct DelArgs {
    //char **fields; I dont think i need this, since we wiill only update one at a time
    //size_t fields_len; Creo que tampoco necesito esto
    //NOTHING here really
} DelArgs_t;
typedef struct CondArgs {
    int whereConditions;
    int ANDsAmount;
    int ORsAmount;
} CondArgs_t;
typedef union {
    SelectArgs_t sel_args;
    UpdateArgs_t upt_args;
    DelArgs_t del_args;
} CmdArg_t;

typedef struct Command {
    unsigned char type;
    char **args;
    size_t args_len;
    size_t args_cap;
    CmdArg_t cmd_args;
    CondArgs_t condArgs;
} Command_t;

Command_t* new_Command();
int add_Arg(Command_t *cmd, const char *arg);
int add_select_field(Command_t *cmd, const char *argument);
void cleanup_Command(Command_t *cmd);

#endif
