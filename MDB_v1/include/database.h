/*************************************************************************
	> File Name: database.h
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2024 06:19:00 PM CST
 ************************************************************************/

#ifndef _DATABASE_H
#define _DATABASE_H

struct Database;

typedef void (*InitTable_T)(struct Database *);

enum OP_TYPE {
    CHOOSE_TABLE,
    TABLE_USAGE,
    OP_END,
    LIST_TABLE,
    ADD_TABLE,
    MODIFY_TABLE,
    DELETE_TABLE
};

struct table_data {
    void *data;
    long offset;
    struct table_data *next;
};


struct Database {
    FILE *table;
    const char *table_name;  
    const char *table_file;
    
    const char **header_name;
    int header_cnt;
    int *header_len;


    struct table_data head;
    size_t (*getDataSize)();
    void (*printData)(void *);
    void (*scanData)(void *);
};

struct TableInfo {
    const char *table_name;
    InitTable_T init_table;
};

void run_database();
void register_table(const char *, InitTable_T);

extern struct Database db;

#endif
