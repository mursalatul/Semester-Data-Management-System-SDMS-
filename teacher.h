/* header guard */
#ifndef TEACHER_H
#define TEACHER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//
#include "checker.h"

/* global variable for storing course names */
char course_names[20][20];

void show_available_courses_for_teacher();
void save_to_course_names(int number_of_string, char *str);
// void update_course_data(int course_number);
// void ask_teacher_for_update_cud(struct CUD cud_data);
void publish_notice(char *notice);
char *find_user_name_of_roll(char *roll);
char *find_user_name_at_line_x(int target_line);

//
//
//

int TOP = -1;
char stack[100][1000];

void push(char *value)
{
    if (TOP == 100 - 1)
    {
        printf("Stack overflow!\n");
        return;
    }
    TOP++;
    strcpy(stack[TOP], value);
}

void pop()
{
    if (TOP == -1)
        printf("Stack underflow!\n");
    else
        TOP--;
}

char *top()
{
    if (TOP == -1)
    {
        printf("Error: Stack is empty\n");
        return NULL;
    }
    return stack[TOP];
}

//
//
//

void publish_notice(char *notice)
{
    /* storing notices into stack */
    FILE *file = fopen("notice.txt", "a+");
    if (file != NULL)
    {
        /* add notice last of the notice.txt */
        fputs(notice, file);
        fputc('\n', file);
    }
    fclose(file);
}

void show_notice()
{
    /* storing notices into stack */
    FILE *file = fopen("notice.txt", "r");
    if (file != NULL)
    {
        char str[1000];
        while (fgets(str, 1000, file) != NULL)
        {
            push(str);
        }
    }
    printf("\nAll Notices:\n");
    int total_print = TOP + 1;
    for (int i = 0; i < total_print; i++)
    {
        printf("%d. %s", TOP + 1, top());
        pop();
    }
}

char *find_user_name_of_roll(char *roll)
{
    FILE *file = fopen("student_basic_data.txt", "r");
    if (file != NULL)
    {
        char str[100];
        int count_line_number = 1;
        int target_line = 0;
        while (fgets(str, 100, file) != NULL)
        {
            if (custom_strcmp(str, roll) == 0)
            {
                /* username at the 1 line up from the roll line */
                target_line = count_line_number - 2;
                break;
            }
            count_line_number++;
        }
        if (target_line)
        {
            /*if target_line found search for the username*/
            fclose(file);
            return find_user_name_at_line_x(target_line);
        }
    }
    fclose(file);
    return "NOT FOUND";
}

char *find_user_name_at_line_x(int target_line)
{
    FILE *file1 = fopen("student_basic_data.txt", "r");
    if (file1 != NULL)
    {
        static char str1[100];
        int count_line_number1 = 1;
        while (fgets(str1, 100, file1) != NULL)
        {
            if (count_line_number1 == target_line)
            {
                fclose(file1);
                static char final_str[100];
                int i = 0;
                int start = 0;
                while (1)
                {
                    char x = str1[i++];
                    if (x == '\n')
                    {
                        final_str[start] = '\0';
                        break;
                    }
                    else
                        final_str[start++] = x;
                }
                return final_str;
            }
            else
                ++count_line_number1;
        }
    }
}

/* show availble courses */
void show_available_courses_for_teacher()
{
    FILE *file;
    file = fopen("student_course_data.txt", "r");
    char str[100];
    /* store number of courses */
    int number_of_string = 0;
    if (file != NULL)
    {
        /* ignoring username */
        fgets(str, 100, file);
        while (fgets(str, 100, file) != NULL)
        {
            if (strlen(str) == 1)
                break;
            save_to_course_names(number_of_string++, str);
        }
    }
    fclose(file);
    /* printing available courses of a student */
    printf("Courses:\n");
    for (int i = 0; i < number_of_string; i++)
    {
        printf("\t%d. %s", i + 1, course_names[i]);
    }
    printf("\n");
}

/*save course names in course_names array(2D)*/
void save_to_course_names(int number_of_string, char *str)
{
    /* index of the adding position of the string member. always starts from 0 in the case of every member */
    int i = 0;
    while (1)
    {
        char x = str[i];
        if (x != ' ')
        {
            /* adding data course_names */
            course_names[number_of_string][i++] = x;
        }
        else
        {
            /* when x  = space that means data complete. so now add a null character after the member string indicating that the string is over now*/
            course_names[number_of_string][i] = '\0';
            break;
        }
    }
}

#endif