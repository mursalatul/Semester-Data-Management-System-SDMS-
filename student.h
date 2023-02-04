/* header guard */
#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>
#include "checker.h" /* custom_strcmp(array string, pointer string) */

/* basic information storing structure */
struct student
{
    char fullname[100];
    char roll[100];
    char registration[50];
    char batch[10];
    char semester[5];
    char department[10];
};

/* return student's basic infos(full name, roll, reg, batch, semester, department) */
struct student basic_info(char *username)
{
    struct student student_basic_info;
    FILE *file;
    file = fopen("student_basic_data.txt", "r");
    char str[100];
    if (file != NULL)
    {
        while (fgets(str, 100, file) != NULL)
        {
            if (custom_strcmp(str, username) == 0)
            {
                fgets(str, 100, file);
                strcpy(student_basic_info.fullname, str);
                fgets(str, 100, file);
                strcpy(student_basic_info.roll, str);
                fgets(str, 100, file);
                strcpy(student_basic_info.registration, str);
                fgets(str, 100, file);
                strcpy(student_basic_info.batch, str);
                fgets(str, 100, file);
                strcpy(student_basic_info.semester, str);
                fgets(str, 100, file);
                strcpy(student_basic_info.department, str);
                break;
            }
        }
    }
    fclose(file);
    return student_basic_info;
}

#endif