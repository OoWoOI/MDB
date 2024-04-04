/*************************************************************************
	> File Name: student_table.c
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2024 09:00:36 PM CST
 ************************************************************************/

#include<stdio.h>
#include<database.h>

static const char *table_name = "class table";
static const char *table_file = "./data/class_data.dat";
static const char *header_name[] = {
    "name",
    "NoStu",
    "Master"
};
static int header_len[] = {
    15,
    7,
    15,
};


typedef struct {
    char name[20];
    int NoStu;
    char master[20];
} table_data;

#include "./table_unit.h"

void printData(void *__data) {
    table_data *data = (table_data *)(__data);
    char frm[100];
    sprintf(frm, "%%%ds|%%%dd|%%%ds|\n", 
        header_len[0], header_len[1], header_len[2]
    );
    printf(frm, 
        data->name, data->NoStu, data->master);
    return ;
}

void scanData(void *__Data) {
    table_data *data = (table_data *)(__Data);
    scanf("%s%d%s", data->name, &(data->NoStu), data->master);
    return ;
}
