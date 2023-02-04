/* header guard */
#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>
#include "checker.h" /* custom_strcmp(array string, pointer string) */

/* function pre-declaration */
struct course_data transfer_course_data_into_A(char *str);
struct student basic_info(char *username);
struct course_data *course_data(char *username);

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

/* course information storing struct */
struct course_data
{
    char course_name[20];
    char total_class[4];
    char attendence[4];
    char total_assignment[4];
    char assignment_completed[4];
    char total_presentation[4];
    char presentation_completed[4];
    char total_classtest[4];
    char classtest_completed[4];
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

/* return an array of struct course_data */
struct course_data *course_data_retriver(char *username)
{
    static struct course_data course_data_arr[10];
    FILE *file;
    file = fopen("student_course_data.txt", "r");
    char str[100];
    if (file != NULL)
    {
        while (fgets(str, 100, file) != NULL)
        {
            if (custom_strcmp(str, username) == 0)
            {
                fgets(str, 100, file);
                int arr_idx = 0;
                while (1)
                {
                    course_data_arr[arr_idx++] = transfer_course_data_into_A(str);
                    fgets(str, 100, file);
                    if (strlen(str) == 1)
                        break;
                }
                break;
            }
        }
    }
    fclose(file);
    return course_data_arr;
}

/* transfer course data from string to coursa_data_A(type = struct coruse_data) */
struct course_data transfer_course_data_into_A(char *str)
{
    struct course_data course_data_A;
    int i = 0;
    int start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            course_data_A.course_name[start++] = x;
            i++;
        }
        else
            break;
    }
    i++;
    start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            course_data_A.total_class[start++] = x;
            i++;
        }
        else
            break;
    }
    i++;
    start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            course_data_A.attendence[start++] = x;
            i++;
        }
        else
            break;
    }
    i++;
    start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            course_data_A.total_assignment[start++] = x;
            i++;
        }
        else
            break;
    }
    i++;
    start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            course_data_A.assignment_completed[start++] = x;
            i++;
        }
        else
            break;
    }
    i++;
    start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            course_data_A.total_presentation[start++] = x;
            i++;
        }
        else
            break;
    }
    i++;
    start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            course_data_A.presentation_completed[start++] = x;
            i++;
        }
        else
            break;
    }
    i++;
    start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            course_data_A.total_classtest[start++] = x;
            i++;
        }
        else
            break;
    }
    i++;
    start = 0;
    while (i < strlen(str))
    {
        char x = str[i];
        if (x != ' ' && x != '\0')
        {
            course_data_A.classtest_completed[start++] = x;
            i++;
        }
        else
            break;
    }
    return course_data_A;
}

#endif