/* header guard */
#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>

/* basic information storing structure */
struct student 
{
    char username[20];
    char fullname[100];
    int roll;
    char registration[50];
    char batch[8];
    int semester;
    char department;
};

struct student basic_info(char *username)
{
    
}

#endif