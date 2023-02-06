/* header guard */
#ifndef TEACHER_H
#define TEACHER_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* global variable for storing course names */
char course_names[20][20];

/* function pre-declaration*/
void show_available_courses_for_teacher();
void save_to_course_names(int number_of_string, char *str);

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
        /* opening file in both read and write mode */
        FILE *file = fopen("student_course_data.txt", "r+");
        if (file != NULL)
        {
            char str[100];
            while (fgets(str, 100, file) != NULL)
            {
                
            }
        }
        fclose(file);
    }
    else
    {
        /* change student data */
    }
}

#endif