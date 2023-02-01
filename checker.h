/* header guard */
#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>
#include <math.h>

struct user
{
    char username[20]; /* store username*/
    char password[20]; /* store password*/
    char stu_teac;     /* store if user is student or teacher*/
};

/*function pre-declaration*/
int user_present(struct user user);
int is_catagory_in_file(char *username, char *password, char catagory);
int custom_strcmp(char *s1, char *s2);

/* check if the login data present in the dataset or not, return 1 for all ok,
return 10 if wrong password, 0 if wrong username */
int user_present(struct user user)
{
    return is_catagory_in_file(user.username, user.password, user.stu_teac);
}

int is_catagory_in_file(char *username, char *password, char catagory)
{
    FILE *file;
    if (catagory == 's')
        file = fopen("student_user_pass.txt", "r");
    else
        file = fopen("teacher_user_pass.txt", "r");

    char str[20];
    int username_found = 0, password_found = 0;
    /* file found */
    if (file != NULL)
    {
        char *holding = "user";
        char *holding2 = "pass";
        while (fgets(str, 20, file) != NULL)
        {
            /* blank line handling */
            if (strlen(str) == 1)
                continue;
            /* if holding user form the file, compare with username parameter, else vice versa */
            if (strcmp(holding, "user") == 0)
            {
                if (custom_strcmp(str, username) == 0)
                {
                    username_found = 1;
                    /* if username found then next line should be its password*/
                    fgets(str, 20, file);
                    if (custom_strcmp(str, password) == 0)
                    {
                        password_found = 1;
                    }
                    break;
                }
            }
            /* swaping holding and holding2 cause next is password and we dont want to run above if in this case */
            char *temp = holding;
            holding = holding2;
            holding2 = temp;
        }
    }
    fclose(file);
    if (username_found + password_found == 0)
        /* 0 means username not found */
        return 0;
    else if (username_found == 1 && password_found == 0)
        /* 10 means wrong password */
        return 10;
    else
        /* 1 means username and password found */
        return 1;
}

/* compare two strings and return 1 if they are not same, else return 0 */
int custom_strcmp(char *s1, char *s2)
{
    /* we are reducing size of s1 by 1 cause s1 is str[]
    and this type of string ends with \n which also added
    to the size. x[4] = "ab", then actually it is {'a', 'b', '\n'}
    so the lenth is 3, but in general lenth is 2.
    but s2 is come as reference. so it is not end with \n. so 
    it gives actual size */
    if (strlen(s1) - 1 != strlen(s2))
        return 1;
    for (int i = 0; i < (int)strlen(s2); i++)
        if (s1[i] != s2[i])
            return 1;
    return 0;
}

#endif