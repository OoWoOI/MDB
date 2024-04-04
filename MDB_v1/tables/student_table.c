/*************************************************************************
	> File Name: student_table.c
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2024 09:00:36 PM CST
 ************************************************************************/

#include<stdio.h>
#include<database.h>

static const char *table_name = "studen table";
static const char *table_file = "./data/student_data.dat";
static const char *header_name[] = {
    "name",
    "age",
    "class",
    "height"
};
static int header_len[] = {
    15,
    6,
    6,
    6
};


typedef struct {
    char name[20];
    int age;
    int class;
    double height;
} table_data;


#include "./table_unit.h"

void printData(void *__data) {
    table_data *data = (table_data *)(__data);
    char frm[100];
    sprintf(frm, "%%%ds|%%%dd|%%%dd|%%%d.2lf|\n", 
        header_len[0], header_len[1], header_len[2],  header_len[3]
    );
    printf(frm, 
        data->name, data->age, data->class, data->height);
    return ;
}

void scanData(void *__Data) {
    table_data *data = (table_data *)(__Data);
    scanf("%s%d%d%lf", 
        data->name, &(data->age), 
        &(data->class), &(data->height)
    );
    return ;
}
