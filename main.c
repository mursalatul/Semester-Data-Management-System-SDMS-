#include <stdio.h>
#include <string.h>
/*structures*/
struct user
{
    char username[20]; /* store username*/
    char password[20]; /* store password*/
    char stu_teac;     /* store if user is student or teacher*/
};

/*function pre-declaration*/
struct user login();
int password_format_checker(char *p);
int username_format_checker(char *p);

/* main function*/
int main()
{
    struct user user = login();
    printf("%s, %s, %c", user.username, user.password, user.stu_teac);
    return 0;
}

/*handle login section*/
struct user login()
{
    struct user user;
    /* check if the username valid or not*/
    while (1)
    {
        printf("Login\nUsername     : ");
        scanf("%s", &user.username);
        if (username_format_checker(user.username) == 1)
            break;
        else
            printf("\033[31mUsername is not in valid format.\nOnly lowercase english letter, underscore and numbers are allowed.\n\033[30m\n\n");
    }
    /* this loop will continue untill user enter valid format password*/
    while (1)
    {
        printf("Password     : ");
        scanf("%s", &user.password);
        if (password_format_checker(user.password) == 1)
            break;
        else
            printf("\033[31mPassword is not in valid format.\nPlease Include 1 number, 1 uppercase and lowercase letter and 1 special character.\n\033[30m\n\n");
    }
    /*this while lop will continue untill user enter S or T*/
    while (1)
    {
        printf("Login as student/Teacher\nPress 'S' for student and 'T' for teacher\n          : ");
        /*bug: if we insert multiple char in same line it take each of the letter as indivitual input causeing loop*/
        scanf(" %c", &user.stu_teac);
        /*checking if the input is s or T*/
        if (user.stu_teac == 's' || user.stu_teac == 'S' || user.stu_teac == 't' || user.stu_teac == 'T')
            break;
        else
            printf("\033[31mValid input is 'S' or 'T', Try again\033[30m\n\n");
    }
    return user;
}

/*check if the password in valid format or not*/
int password_format_checker(char *p)
{
    /* 1. has atleast 1 number*/
    /* 2. has atleast 1 uppercase letter*/
    /* 3. has atleast 1 lowercase letter*/
    /* 4. has atleast 1 special character*/

    /* here 0 represent false*/
    int num = 0, upperl = 0, lowerl = 0, specl = 0;
    int password_len = strlen(p);
    /* password lenth will be 4 to 10*/
    for (int i = 0; i < password_len && (password_len >= 4 && password_len <= 10); i++)
    {
        if (p[i] >= '1' && p[i] <= '9')
            num = 1;
        else if (p[i] >= 'A' && p[i] <= 'Z')
            upperl = 1;
        else if (p[i] >= 'a' && p[i] <= 'z')
            lowerl = 1;
        else if ((p[i] >= 33 && p[i] <= 47) || (p[i] >= 58 && p[i] <= 64) || (p[i] >= 91 && p[i] <= 96) || (p[i] >= 123 && p[i] <= 126))
            specl = 1;
    }
    if (num == 1 && upperl == 1 && lowerl == 1 && specl == 1)
        /* return 1 means return true*/
        return 1;
    else
        /* return 0 means return false*/
        return 0;
}

/* check if the username in valid format or not*/
int username_format_checker(char *u)
{
    /* checking if first letter is number or not*/
    /* in the username, first letter cant be a number*/
    if (u[0] >= '1' && u[0] <= '9')
        return 0;
    int valid = 1;
    int username_len = strlen(u);
    for (int i = 0; i < username_len; i++)
    {
        if ((u[i] >= 'A' && u[i] <= 'Z') || ((u[i] >= 33 && u[i] <= 47) || (u[i] >= 58 && u[i] <= 64) || (u[i] >= 91 && u[i] <= 96) || (u[i] >= 123 && u[i] <= 126)))
        {
            valid = 0;
            break;
        }
        /* 95 = decimal value of under score*/
        if (u[i] == 95)
            valid = 1;
    }
    return valid;
}
