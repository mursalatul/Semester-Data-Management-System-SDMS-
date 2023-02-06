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

/* structs */
/* CUS = Course Universal Data */
struct CUD
{
    char total_classes[10];
    char total_assignments[10];
    char total_presentations[10];
    char total_class_tests[10];
};
/* function pre-declaration*/
void show_available_courses_for_teacher();
void save_to_course_names(int number_of_string, char *str);
void update_course_data(int course_number);
void ask_teacher_for_update_cud(struct CUD cud_data);
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

char *pop()
{
    if (TOP == -1)
    {
        printf("Stack underflow!\n");
        return NULL;
    }
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
    }
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
    for (int i = 0; i < TOP + 1; i++)
    {
        printf("%d. %s", TOP + 1 - i, top());
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
                target_line = count_line_number - 2;
                break;
            }
            count_line_number++;
        }
        return find_user_name_at_line_x(target_line);
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
            save_to_course_names(number_of_string++, str);
            if (strlen(str) == 1)
                break;
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

/* update stdent_course_data.txt */
void update_course_data(int course_number)
{
    char *course_name = course_names[course_number];
    char uni_parti;
    while (1)
    {
        /* asking if teacher wants to change a data for all student or just want to change a particular data of a student */
        int universal_data_change = 0;
        printf("Do you want to change universal data or Particular student's data?\nSelect U for universal or P for particular: ");
        scanf(" %c", &uni_parti);
        uni_parti = tolower(uni_parti);
        if (uni_parti == 'u' || uni_parti == 'p')
            break;
        else
            printf("Wrong selection.Redirecting to above section again......\n");
    }
    if (uni_parti == 'u')
    {
        /* change universal data */
        printf("Here you can edit, ");
        printf("\n\tTC = Total Classes\n\tAs = Total Assignments\n\tPr = Total Presentations\n\tCT = Total Class Tests\n");

        /* opening file in both read and write mode */
        FILE *file;
        file = fopen("student_course_data.txt", "r");
        if (file != NULL)
        {
            char str[100];
            while (fgets(str, 100, file) != NULL)
            {
                if (cmp_with_course_name(str, course_name) == 0)
                {
                    struct CUD uni_data;

                    /* extract universal datas and return CUD object */
                    int i = 0;

                    /* skipping course name here */
                    while (1)
                    {
                        char x = str[i++];
                        if (x == ' ')
                            break;
                    }

                    /* total_classes */
                    int start = 0;
                    while (1)
                    {
                        char x = str[i++];
                        if (x != ' ')
                        {
                            /* adding data to member of the uni_data */
                            uni_data.total_classes[start++] = x;
                        }
                        else
                        {
                            /* when x  = space that means data complete. so now add a null character after the member string indicating that the string is over now*/
                            uni_data.total_classes[start] = '\0';
                            break;
                        }
                    }

                    /* increase i by 1 after reading a whole block of data, as i still pointing to the index of the new line. */

                    /* skip */
                    start = 0;
                    while (1)
                    {
                        char x = str[i++];
                        if (x == ' ')
                            break;
                    }

                    /* adding total assigment */
                    start = 0;
                    while (1)
                    {
                        char x = str[i++];
                        if (x != ' ')
                        {
                            uni_data.total_assignments[start++] = x;
                        }
                        else
                        {
                            uni_data.total_assignments[start] = '\0';
                            break;
                        }
                    }

                    /* skip */
                    while (1)
                    {
                        char x = str[i++];
                        if (x == ' ')
                            break;
                    }

                    /* adding presentation */
                    start = 0;
                    while (1)
                    {
                        char x = str[i++];
                        if (x != ' ')
                        {
                            uni_data.total_presentations[start++] = x;
                        }
                        else
                        {
                            uni_data.total_presentations[start] = '\0';
                            break;
                        }
                    }

                    /* skip */
                    while (1)
                    {
                        char x = str[i++];
                        if (x == ' ')
                            break;
                    }

                    /* adding total class tests */
                    start = 0;
                    while (1)
                    {
                        char x = str[i++];
                        if (x != ' ')
                        {
                            uni_data.total_class_tests[start++] = x;
                            i++;
                        }
                        else
                        {
                            uni_data.total_class_tests[start] = '\0';
                            break;
                        }
                    }

                    //
                    //
                    //
                    ask_teacher_for_update_cud(uni_data);
                    break;
                }
                if (strlen(str) == 1)
                    break;
            }
        }
        fclose(file);
    }
    else
    {
        /* change a student data */
    }
}

void ask_teacher_for_update_cud(struct CUD cud_data)
{
    printf("Total Classes:  %s\tTotal Assignments:  %s\nTotal Presentations:  %s\tTotal Class Tests:  %s\n", cud_data.total_classes, cud_data.total_assignments, cud_data.total_presentations, cud_data.total_class_tests);
    int update_cud_data = 0;
    printf("Do you want to update? (Press 1 for Yes / 0 for No)");
    scanf("%d", &update_cud_data);
    // if (update_cud_data)
}

#endif