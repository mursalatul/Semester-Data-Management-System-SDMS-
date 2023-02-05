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
                /* if username found go to next line cause after the username course datas are present */
                fgets(str, 100, file);
                int arr_idx = 0;
                /* number of time looping = number of courses */
                while (1)
                {
                    /* extracting all the datas form str and string it into the array */
                    course_data_arr[arr_idx++] = transfer_course_data_into_A(str);
                    fgets(str, 100, file);
                    /* when course data ends there will be a empty line */
                    if (strlen(str) == 1)
                    {
                        /*ending_value is a special element in the course_data_arr which indicates that this is the end of the array*/
                        struct course_data ending_value;
                        ending_value.course_name[0] = 'E';
                        course_data_arr[arr_idx] = ending_value;
                        break;
                    }
                }
                /* dont need to check further, username already found */
                break;
            }
        }
    }
    fclose(file);
    return course_data_arr;
}

/* split datas from the str and add to the members of course_data_A structure data */
struct course_data transfer_course_data_into_A(char *str)
{
    struct course_data course_data_A;
    /* index of the char in the str */
    int i = 0;
    /* index of the adding position of the string member. always starts from 0 in the case of every member */
    int start = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            /* adding data to member of the course_data_A */
            course_data_A.course_name[start++] = x;
            i++;
        }
        else
        {
        /* when x  = space that means data complete. so now add a null character after the member string indicating that the string is over now*/
            course_data_A.course_name[start] = '\0';
            break;
        }
    }
    /* increase i by 1 after reading a whole block of data, as i still pointing to the index of the new line. */
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
        {
            course_data_A.total_class[start] = '\0';
            break;
        }
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
        {
            course_data_A.attendence[start] = '\0';
            break;
        }
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
        {
            course_data_A.total_assignment[start] = '\0';
            break;
        }
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
        {
            course_data_A.assignment_completed[start] = x;
            break;
        }
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
        {
            course_data_A.total_presentation[start] = '\0';
            break;
        }
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
        {
            course_data_A.presentation_completed[start] = '\0';
            break;
        }
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
        {
            course_data_A.total_classtest[start] = '\0';
            break;
        }
    }
    i++;
    start = 0;
    while (i < strlen(str))
    {
        char x = str[i];
        /* when character is space or \n or \0 it means this is the end of the str.
        in the above cases we just checked space, not \0 cause we were reading data inside the string,
        and inside a string there is no null character(\0). but now we are checking cause this is the last
        data checking and after this there will be a null character or end of line */
        if (x == ' ' || x == '\n' || x == '\0')
        {
            course_data_A.classtest_completed[start] = '\0';
            break;
        }
        else
        {
            course_data_A.classtest_completed[start++] = x;
            i++;
        }
    }
    return course_data_A;
}

#endif