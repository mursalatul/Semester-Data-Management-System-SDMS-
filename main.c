#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* project headers */
#include "checker.h" //user_present(struct user user)
#include "student.h"
#include "teacher.h" /* show_available_courses_for_teacher() */
/*function pre-declaration*/

struct user login();
int password_format_checker(char *p);
int username_format_checker(char *p);
int login_confirmation(struct user user);

/* main function*/
int main()
{
    /* login section */
    struct user user = login();
    while (1)
    {
        /* if user confirm to login then procced. else ask for login data again. */
        if (login_confirmation(user) == 1)
        {
            /* check if login data correct or not */
            int user_status = user_present(user);
            if (user_status == 0)
                printf("Wrong username!\n\n\n");
            else if (user_status == 10)
                printf("Wrong password!\n\n\n");
            else
                /* user_status = 1, data found */
                break;
        }
        printf("You are redirecting to login section again.....\n");
        user = login();
    }
    if (user.stu_teac == 's')
    {
        /* student section */
        printf("\n********** Welcome To Your Portal **********\n");
        /* print basic information */
        struct student student_basic_info = basic_info(user.username);
        printf("Name       : %sRoll       : %sReg        : %sBatch      : %sSemester   : %sDepartment : %s\n", student_basic_info.fullname, student_basic_info.roll, student_basic_info.registration, student_basic_info.batch, student_basic_info.semester, student_basic_info.department);
        while (1)
        {
            int operation = 0;
            while (1)
            {
                printf("\nChoose an option: \n1. Show Course data.\n2. Show all notices\n3. Exit\n(Press 1 / 2 / 3) : ");
                scanf("%d", &operation);
                if (operation < 1 || operation > 3)
                    printf("Wrong input.\n");
                else
                    break;
            }
            if (operation == 1)
            {
                /* printing educational datas */
                printf("All Data About Course\n-----------------------------------------------------------------------\n");
                printf("CC = Course Code\t\tTC = Total Classes\t\tAt = Attendence\nAs = Assignment\t\t\tAC = Assignment Completed\tPr = Presentation\nPC = Presentation Completed\tCT = Class Tests\t\tCTA = Class Test Attended\n");
                printf("-----------------------------------------------------------------------\n");
                printf("CC\tTC\tAt\tAs\tAC\tPr\tPC\tCT\tCTA\n");
                struct course_data *all_course_data_arr = course_data_retriver(user.username);
                for (int i = 0; 1; i++)
                {
                    /* print until last last value */
                    if (all_course_data_arr[i].course_name[0] == 'E')
                        break;
                    printf("%s    %s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", all_course_data_arr[i].course_name, all_course_data_arr[i].total_class, all_course_data_arr[i].attendence, all_course_data_arr[i].total_assignment, all_course_data_arr[i].assignment_completed, all_course_data_arr[i].total_presentation, all_course_data_arr[i].presentation_completed, all_course_data_arr[i].total_classtest, all_course_data_arr[i].classtest_completed);
                }
            }
            else if (operation == 2)
            {
                show_notice();
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        /* teacher section */
        /* showing all the courses */
        show_available_courses_for_teacher();
        while (1)
        {
            int operation = 0;
            while (1)
            {
                printf("\nChoose an option: \n1. Show student data.\n2. Publish short notice.\n3. Show all notices\n4. Exit\n(Press 1 / 2 / 3 / 4) : ");
                scanf("%d", &operation);
                if (operation < 1 || operation > 4)
                    printf("Wrong input.\n");
                else
                    break;
            }
            if (operation == 1)
            {
                /* show student data */
                char roll[10];
                printf("Enter Roll: ");
                scanf(" %s", &roll);
                /* finding username of the spacific roll so the corse data of the username can be searched */
                char *username_of_the_roll = find_user_name_of_roll(roll);
                if (strcmp(username_of_the_roll, "NOT FOUND") == 0)
                    printf("Roll does not exist.\n");
                else
                {
                    /* printing educational datas */
                    printf("----------------------------------------\n");
                    printf("CC = Course Code\t\tTC = Total Classes\t\tAt = Attendence\nAs = Assignment\t\t\tAC = Assignment Completed\tPr = Presentation\nPC = Presentation Completed\tCT = Class Tests\t\tCTA = Class Test Attended\n");
                    printf("----------------------------------------\n");
                    printf("CC\tTC\tAt\tAs\tAC\tPr\tPC\tCT\tCTA\n");
                    struct course_data *all_course_data_arr = course_data_retriver(username_of_the_roll);
                    for (int i = 0; 1; i++)
                    {
                        /* print until last last value */
                        if (all_course_data_arr[i].course_name[0] == 'E')
                            break;
                        printf("%s    %s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", all_course_data_arr[i].course_name, all_course_data_arr[i].total_class, all_course_data_arr[i].attendence, all_course_data_arr[i].total_assignment, all_course_data_arr[i].assignment_completed, all_course_data_arr[i].total_presentation, all_course_data_arr[i].presentation_completed, all_course_data_arr[i].total_classtest, all_course_data_arr[i].classtest_completed);
                    }
                }
            }
            else if (operation == 2)
            {
                /* publish short notice */
                char notice[100];
                while (1)
                {
                    printf("Notice: ");
                    scanf(" %[^\n]%*c", notice);
                    printf("Your notice: %s\nPress 1 for procced / 0 for retake: ", notice);
                    int x = 0;
                    scanf("%d", &x);
                    if (x == 1)
                        break;
                }
                publish_notice(notice);
            }
            else if (operation == 3)
            {
                show_notice();
            }
            else
            {
                break;
            }
        }
    }
    printf("\n Closing Program\n----------------\n");

    return 0;
}

/*handle login section. return struct user type user data(username, password, Student/teacher)*/
struct user login()
{
    struct user user;
    /* check if the username valid or not*/
    while (1)
    {
        printf("\t\tLogin\n-----------------------------------\nUsername     : ");
        scanf("%s", &user.username);
        if (username_format_checker(user.username) == 1)
            break;
        else
            printf("Username is not in valid format.\nOnly lowercase english letter, underscore and numbers are allowed.\n\n\n");
    }
    /* this loop will continue untill user enter valid format password*/
    while (1)
    {
        printf("Password     : ");
        scanf("%s", &user.password);
        if (password_format_checker(user.password) == 1)
            break;
        else
            printf("Password is not in valid format.\nPassword size should be in 4 - 10.\nAnd contains 1 number, 1 uppercase and lowercase letter and 1 special character.\n\n\n");
    }
    /*this while lop will continue untill user enter S or T*/
    while (1)
    {
        printf("Login as student/Teacher.\nPress ('S' for student) and ('T' for teacher)\n             : ");
        /*bug: if we insert multiple char in same line it take each of the letter as indivitual input causeing loop*/
        scanf(" %c", &user.stu_teac);
        /* lowercasing user.stu_teac for simplicity */
        user.stu_teac = tolower(user.stu_teac);
        /*checking if the input is s or T*/
        if (user.stu_teac == 's' || user.stu_teac == 't')
            break;
        else
            printf("Valid input is 'S' or 'T', Try again\n\n");
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
        if (p[i] >= '0' && p[i] <= '9')
            num = 1;
        else if (p[i] >= 'A' && p[i] <= 'Z')
            upperl = 1;
        else if (p[i] >= 'a' && p[i] <= 'z')
            lowerl = 1;
        else if ((p[i] >= 33 && p[i] <= 47) || (p[i] >= 58 && p[i] <= 64) || (p[i] >= 91 && p[i] <= 96) || (p[i] >= 123 && p[i] <= 126))
            specl = 1;
        // if already num, upperl, lowerl and specl found then dont need to check further
        if (num == 1 && upperl == 1 && lowerl == 1 && specl == 1)
            /* return 1 means return true*/
            return 1;
    }
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
        /* 95 = decimal value of under score, other special characters are not allowed*/
        if ((u[i] >= 'A' && u[i] <= 'Z') || ((u[i] >= 33 && u[i] <= 47) || (u[i] >= 58 && u[i] <= 64) || (u[i] >= 91 && u[i] <= 96 && u[i] != 95) || (u[i] >= 123 && u[i] <= 126)))
        {
            valid = 0;
            break;
        }
    }
    return valid;
}

/* show final data and confirm if it is final data or not */
int login_confirmation(struct user user)
{
    char confirm[20];
    printf("\n-----------------------------------\nUsername         : %s\n", user.username);
    if (user.stu_teac == 's')
        printf("login as         : Student\nProceed?(YES/NO) : ");
    else
        printf("Login as         : Teacher\nProceed?(YES/NO) : ");
    scanf("%s", &confirm);
    if (!strcmp(confirm, "YES") || !strcmp(confirm, "yes") || !strcmp(confirm, "1") || !strcmp(confirm, "Yes") || !strcmp(confirm, "y") || !strcmp(confirm, "Y"))
        return 1;
    else
        return 0;
}