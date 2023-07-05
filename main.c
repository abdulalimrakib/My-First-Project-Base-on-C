#include<stdio.h>

struct login
{
    char fn[50];
    char ln[50];
    char username[50];
    char password[50];
} log;

FILE *fp,*ft;

struct student
{
    int month,day;
    int clas,roll;
    char name[50];
    float fee, advance, due, total;
} stud;

struct teacher
{
    int month,day;
    int id,no;
    char name[50];
    float salary, advance, total;
} tech;

int global_month,global_day;

void registe()
{
    FILE *fp;

    fp=fopen("login.txt","w");

    printf("Enter first name : ");
    scanf(" %s",&log.fn);
    fflush(stdin);
    printf("Enter last name : ");
    scanf(" %s",&log.ln);
    fflush(stdin);
    printf("\n\nEnter username : ");
    scanf(" %s",&log.username);
    fflush(stdin);
    printf("\nEnter password : ");
    scanf(" %s",&log.password);

    fflush(stdin);

    fwrite(&log,sizeof(log),1,fp);

    fclose(fp);

    printf("\nYour user name is user ID\n\n");


    system("pause");
    system("CLS");

    login();
}

void login()
{
    char userid[50],password[50];
    int s_month,s_day;

    FILE *fp;
    fp=fopen("login.txt","r");

    printf("User ID : ");
    scanf(" %s",&userid);

    printf("\nPassword : ");
    scanf(" %s",&password);

    while(fread(&log,sizeof(log),1,fp));
    {
        if(strcmp(userid,log.username)==0 && strcmp(password,log.password)==0)
        {
            system("CLS");

            printf("Enter current date(month/day) : ");
            scanf("%d/%d",&global_month,&global_day);

            global_month = check_date(global_month,global_day);

            system("CLS");

            category();
        }
        else
        {
            system("CLS");
            printf("Try again........\n\n");
            system("pause");
            main();
        }

    }

    fclose(fp);
}

int check_date(int mon,int day)
{
    int m,d;
    if (mon>12 || mon<1 || day<1 || day>32)
    {
        printf("Invalid Date......\nTry again : ");
        scanf("%d%d",&m,&d);
        m=check_date(m,d);
    }
    else
        return (mon);
}

void category()
{
    int choice;
    system("CLS");
    printf(" 1 . Student\n 2 . Teacher or staffs\n 0 . exit\n\n");
    printf("Enter category : ");
    scanf("%d",&choice);
    do
    {
        if(choice==1)
            menu();
        else if(choice==2)
            T_menu();
        else if(choice==0)
            exit(1);
        else
            printf("Invalid input !!!Try again : ");
    }
    while(choice==0);
}

void add_record()
{
    int difference,mon;
    float fees;

    system("CLS");
    printf("******************************************************\n");
    printf("                        ADD RECORD                        \n");
    printf("******************************************************\n\n\n");


    while(1)
    {
        stud.advance=0;
        printf("Enter the name of student(press Enter and go back) : ");
        fflush(stdin);
        gets(stud.name);

        if(strcmp(stud.name,"")==0)
        {
            break;
        }

        printf("\nEnter the class: ");
        fflush(stdin);
        scanf("%d",&stud.clas);

        printf("\nEnter the Roll No.:");
        fflush(stdin);
        scanf("%d",&stud.roll);

        printf("\nEnter month number till which fee is paid(only month):");
        scanf("%d",&mon);
        mon=check_date(mon,1);
        stud.month=mon;
        fees=stud.clas/10.0;
        stud.fee =1000*(fees);
        difference=global_month-stud.month;
        stud.due=(difference)*stud.fee;
        if(stud.due<0)
        {
            stud.advance = (-1)*stud.due;
            stud.due=0;
        }

        stud.total = stud.due;

        printf("\n\n--------------------------------------------------------------\n\n");

        fp=fopen("student","ab");
        fwrite(&stud,sizeof(stud),1,fp);
        fclose(fp);
    }
    menu();

}

void T_add_record()
{
    int mon;
    float fees;

    system("CLS");
    printf("******************************************************\n");
    printf("                        ADD RECORD                        \n");
    printf("******************************************************\n\n\n");


    while(1)
    {
        printf("Enter the name of Teacher/Staff(press Enter and go back) : ");
        fflush(stdin);
        gets(tech.name);

        if(strcmp(tech.name,"")==0)
        {
            break;
        }

        printf("\nEnter Teacher/Staff ID : ");
        fflush(stdin);
        scanf("%d",&tech.id);

        printf("\nEnter number of class/shift per month :");
        fflush(stdin);
        scanf("%d",&tech.no);

        printf("\nEnter month number till which salary is paid(only month):");
        scanf("%d",&mon);
        mon=check_date(mon,1);
        tech.month=mon;
        tech.salary =1000*(tech.no);
        tech.advance=(tech.month-global_month)*tech.salary;
        if (tech.advance<0)
            tech.advance=0;
        tech.total = tech.salary;

        printf("\n\n--------------------------------------------------------------\n\n");

        ft=fopen("teacher","ab");
        fwrite(&tech,sizeof(tech),1,ft);
        fclose(ft);
    }
    T_menu();
}

void view_record()
{
    int count = 0;
    system("CLS");
    printf("******************************************************\n");
    printf("                    VIEW RECORD                     \n");
    printf("******************************************************\n\n\n");

    fp=fopen("student","rb+");
    while(fread(&stud,sizeof(stud),1,fp)==1)
    {
        printf("\nName = %s",stud.name);
        printf("\nClass = %d",stud.clas);
        printf("\nRoll no = %d",stud.roll);
        printf("\nLast fee paid in month =%d\n",stud.month);
        printf("Monthly fee = %0.2f\n",stud.fee);
        printf("Due = %0.2f\n",stud.due);
        printf("Need to pay = %0.2f\n",stud.total);
        printf("Advance = %0.2f",stud.advance);
        count++;
        printf("\n\n-----------------------------------------------------\n\n");
    }
    printf("\n\nThere are %d records\n\n",count);
    fclose(fp);
    system("pause");
    menu();
}

void T_view_record()
{
    int count = 0;
    system("CLS");
    printf("******************************************************\n");
    printf("                    VIEW RECORD                     \n");
    printf("******************************************************\n\n\n");

    ft=fopen("teacher","rb+");
    while(fread(&tech,sizeof(tech),1,ft)==1)
    {
        printf("\nName = %s",tech.name);
        printf("\nID = %d",tech.id);
        printf("\nTotal class/shift time = %d",tech.no);
        printf("\nSalary of month : %.2f",tech.salary);
        printf("\nLast salary paid in month =%d\n",tech.month);
        count++;
        printf("\n\n-----------------------------------------------------\n\n");
    }
    printf("\n\nThere are %d records\n\n",count);
    fclose(ft);
    system("pause");
    T_menu();
}

void search_record()
{
    char name[50];
    int choice,a=1,clas,roll;
    system("CLS");
    printf("******************************************************\n");
    printf("                    SEARCH RECORD                     \n");
    printf("******************************************************\n\n\n");

    printf(" 1 . Search by name");
    printf("\n 2 . Search by class");
    printf("\n 3 . Go to main menu\n\n");

    printf("\nEnter your choice : ");
    scanf("%d",&choice);

    if(choice==1)
    {
        system("cls");
        printf("Enter student name to search : ");
        fflush(stdin);
        scanf("%[^\n]",name);
        printf("Enter student class to search : ");
        fflush(stdin);
        scanf("%d",&clas);
        printf("Enter student roll to search : ");
        fflush(stdin);
        scanf("%d",&roll);

        fp = fopen("student","rb+");
        while(fread(&stud,sizeof(stud),1,fp)==1)
        {
            if(strcmp(name,stud.name)==0 && stud.clas==clas && stud.roll==roll)
            {
                a=0;
                printf("\n\nStudent name = %s\n",stud.name);
                printf("Student class = %d\n",stud.clas);
                printf("Student roll = %d\n",stud.roll);
                printf("Last fee paid of month = %d\n",stud.month);
                printf("Monthly fee = %0.2f\n",stud.fee);
                printf("Due = %0.2f\n",stud.due);
                printf("Need to pay = %0.2f\n",stud.total);
                printf("Advance paid = %0.2f\n\n",stud.advance);
            }
        }
        if(a==1)
            printf("Record not found\n\n");
        fclose(fp);

    }

    else if(choice==2)
    {
        system("cls");
        printf("\nEnter student class to search : ");
        scanf("%d",&clas);

        fp = fopen("student","rb");
        while(fread(&stud,sizeof(stud),1,fp)==1)
        {
            if(stud.clas==clas)
            {
                a=0;
                printf("\n\nStudent name = %s\n",stud.name);
                printf("Student class = %d\n",stud.clas);
                printf("Student roll = %d\n",stud.roll);
                printf("Last fee paid of month = %d\n",stud.month);
                printf("Monthly fee = %0.2f\n",stud.fee);
                printf("Due = %0.2f\n",stud.due);
                printf("Need to pay = %0.2f\n",stud.total);
                printf("Advance paid = %0.2f\n\n",stud.advance);
            }
        }
        if(a==1)
            printf("Record not found\n\n");
        fclose(fp);
    }

    else if(choice==3)
    {
        menu();
    }
    else
    {
        printf("\n\nInvalid input......\n\n");
        search_record();
    }
    system("pause");
    menu();
}

void T_search_record()
{
    char name[50];
    int a=1,id;
    system("CLS");
    printf("******************************************************\n");
    printf("                    SEARCH RECORD                     \n");
    printf("******************************************************\n\n\n");

    printf("\n\nEnter Teacher/Staff name to search : ");
    fflush(stdin);
    scanf("%[^\n]",name);
    printf("\nEnter Teacher/Staff ID to search : ");
    scanf("%d",&id);


    ft = fopen("teacher","rb+");
    while(fread(&tech,sizeof(tech),1,ft)==1)
    {
        if(strcmp(name,tech.name)==0 && id==tech.id)
        {
            a=0;
            printf("\n\Teacher/Staff name = %s\n",tech.name);
            printf("Teacher/Staff ID = %d\n",tech.id);
            printf("month till when salary is paid = %d\n",tech.month);
            printf("Monthly salary = %.2f\n",tech.salary);
            printf("Advance paid = %.2f\n\n",tech.advance);
        }
    }
    if(a==1)
        printf("Record not found\n\n");
    fclose(ft);
    system("pause");
    T_menu();

}

void modify_record()
{
    char name[50];
    int clas,roll,choice;
    system("CLS");

    printf(" 1 . Modify record");
    printf("\n 2 . Delete record");

    printf("\nEnter your choice : ");
    scanf("%d",&choice);

    if(choice==1)
    {
        system("CLS");
        printf("******************************************************\n");
        printf("                           MODIFY RECORD                     \n");
        printf("******************************************************\n\n\n");

        printf("\n\nEnter name of student to modify: ");
        fflush(stdin);
        scanf("%[^\n]",name);
        printf("Enter class of student to modify: ");
        fflush(stdin);
        scanf("%d",&clas);
        printf("Enter roll of student to modify: ");
        fflush(stdin);
        scanf("%d",&roll);

        fp = fopen("student","rb+");
        while(fread(&stud,sizeof(stud),1,fp)==1)
            if(strcmp(name,stud.name)==0 && stud.clas==clas && stud.roll==roll)
            {
                printf("\nEnter new name of student: ");
                fflush(stdin);
                scanf("%[^\n]",stud.name);
                printf("\nEnter new class of student: ");
                fflush(stdin);
                scanf("%d",&stud.clas);
                printf("\nEnter new roll of student: ");
                fflush(stdin);
                scanf("%d",&stud.roll);

                fseek(fp,-sizeof(stud),1);
                fwrite(&stud,sizeof(stud),1,fp);
                fclose(fp);
            }
    }

    else if(choice==2)
    {
        delete_record();
    }

    else
    {
        printf("Invalid input.........try again......\n\n");
        modify_record();
    }
    system("pause");
    menu();
}

void T_modify_record()
{
    char name[50];
    int choice,id;
    system("CLS");

    printf(" 1 . Modify record");
    printf("\n 2 . Delete record");

    printf("\nEnter your choice : ");
    scanf("%d",&choice);

    if(choice==1)
    {
        system("CLS");
        printf("******************************************************\n");
        printf("                           MODIFY RECORD                     \n");
        printf("******************************************************\n\n\n");

        printf("\n\nEnter name of Teacher/staff to modify: ");
        fflush(stdin);
        scanf("%[^\n]",name);
        printf("Enter ID of Teacher/staff to modify: ");
        fflush(stdin);
        scanf("%d",&id);

        ft = fopen("teacher","rb+");
        while(fread(&tech,sizeof(tech),1,ft)==1)
        {
            if(strcmp(name,tech.name)==0 && tech.id==id)
            {
                printf("\n\nEnter NEW name of teacher/Staff: ");
                fflush(stdin);
                scanf("%[^\n]",tech.name);
                printf("\nEnter NEW id of teacher/Staff: ");
                fflush(stdin);
                scanf("%d",&tech.id);
                fseek(ft,-sizeof(tech),1);
                fwrite(&tech,sizeof(tech),1,ft);
                fclose(ft);
            }
        }
    }
    else if(choice==2)
        T_delete_record();
    else
    {
        printf("Invalid Input !!! ");
        T_modify_record();
    }
    system("\npause");
    T_menu();
}

void delete_record()
{

    char name[50];
    int roll,clas,a=1;
    FILE *temp;

    system("CLS");
    printf("******************************************************\n");
    printf("                    DELETE RECORD                     \n");
    printf("******************************************************\n\n\n");

    printf("\n\nEnter name of student to delete: ");
    fflush(stdin);
    scanf("%[^\n]",name);
    printf("Enter class of student to delete: ");
    fflush(stdin);
    scanf("%d",&clas);
    printf("Enter roll of student to delete: ");
    fflush(stdin);
    scanf("%d",&roll);

    fp = fopen("student","rb");
    temp = fopen("tempfile","wb");
    while(fread(&stud,sizeof(stud),1,fp)==1)
    {
        if(strcmp(name,stud.name)==0 && stud.clas==clas && stud.roll==roll)
        {
            a=0;
            continue;
        }
        else
        {
            fwrite(&stud,sizeof(stud),1,temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if(a==1)
    {
        printf("\n\nRecord not found\n\n");
    }
    else
    {
        printf("\n\nDeleted\n\n");
    }

    system("del student");
    system("ren tempfile, student");

}

void T_delete_record()
{
    int a=1;
    char name[50];
    FILE *temp;

    system("CLS");
    printf("******************************************************\n");
    printf("                           DELETE RECORD                     \n");
    printf("******************************************************\n\n\n");

    printf("\n\nEnter name of teacher/Staff to delete record: ");
    fflush(stdin);
    scanf("%[^\n]",name);
    ft=fopen("teacher","rb");
    temp=fopen("tempfile1","wb");
    while (fread(&tech,sizeof(tech),1,ft)==1)
    {
        if (strcmp(tech.name,name)==0)
        {
            a=0;
            continue;
        }
        else
        {
            fwrite(&tech,sizeof(tech),1,temp);
        }
    }

    if (a==1)
        printf("\n\nRECORD NOT FOUND");
    else
        printf("\n\n  DELETED");
    printf("\n\n");
    fflush(stdin);

    fclose(ft);
    fclose(temp);
    system("del teacher");
    system("ren tempfile1, teacher");
}

void fee()
{
    system("CLS");


    printf("******************************************************\n");
    printf("                      FEE CALCULATE                     \n");
    printf("******************************************************\n\n\n");

    int a=1,month,difference,clas,roll;
    char name[50];
    FILE *temp;

    printf("Enter name : ");
    fflush(stdin);
    scanf("%[^\n]",&name);
    printf("Enter class of student : ");
    fflush(stdin);
    scanf("%d",&clas);
    printf("Enter roll of student : ");
    fflush(stdin);
    scanf("%d",&roll);

    fp = fopen("student","rb");
    temp = fopen("tempfile1","wb");
    while (fread(&stud,sizeof(stud),1,fp)==1)
    {
        if (strcmp(stud.name,name)==0 && stud.roll==roll && stud.clas==clas)
        {
            a=0;
            difference=global_month-stud.month;

            printf("\n\nUnpaid month's number = %d\n",difference);
            stud.due=(difference)*stud.fee;
            if (stud.due<0)
            {
                printf("Advance paid = %0.2f\n\n",stud.due*(-1));
                stud.due=0;
            }
            else
            {
            printf("\nShould be paid : %.2f\n\n",stud.due);
            stud.month+=difference;
            stud.total=0;
            stud.due=0;
            }

            fwrite(&stud,sizeof(stud),1,temp);
        }
        else
        {
            fwrite(&stud,sizeof(stud),1,temp);
        }
    }

    if (a==1)
        printf("\n\nRECORD NOT FOUND");
    printf("\n\n");
    system("pause");
    fflush(stdin);

    fclose(fp);
    fclose(temp);
    system("del student");
    system("ren tempfile1, student");

    menu();
}

void T_salary()
{
    system("CLS");


    printf("******************************************************\n");
    printf("                              SALARY                    \n");
    printf("******************************************************\n\n\n");

    int a=1,month,id;
    char name[50];
    FILE *temp;

    printf("Enter name : ");
    fflush(stdin);
    scanf("%[^\n]",&name);
    printf("Enter ID : ");
    fflush(stdin);
    scanf("%d",&id);

    ft=fopen("teacher","rb");
    temp=fopen("tempfile1","wb");
    while (fread(&tech,sizeof(tech),1,ft)==1)
    {
        if (strcmp(tech.name,name)==0 && tech.id==id)
        {
            a=0;
            float last_month;
            printf("\nEnter the month till which salary is to be paid(only month) : ");
            fflush(stdin);
            scanf("%d",&month);
            month=check_date(month,1);
            tech.advance = (month-global_month)*tech.salary;
            if(tech.advance<0)
                tech.advance=0;
            last_month=global_month-tech.month;
            if(last_month<0)
                last_month=0;
            tech.total=tech.advance+tech.salary*(last_month);
            if(month==tech.month)
                tech.total=0;
            printf("\n\nMonthly salary left to be paid : %.2f",last_month);
            printf("\nTotal : %.2f",tech.total);
            printf("\nAdvance : %.2f\n\n",tech.advance);
            tech.month=month;

            fwrite(&tech,sizeof(tech),1,temp);
        }
        else
        {
            fwrite(&tech,sizeof(tech),1,temp);
        }
    }

    if (a==1)
        printf("\n\nRECORD NOT FOUND");
    printf("\n\n");
    system("pause");
    fflush(stdin);

    fclose(ft);
    fclose(temp);
    system("del teacher");
    system("ren tempfile1, teacher");

    T_menu();
}

void menu()
{
    int choice;

    system("CLS");

    do
    {
        printf(" 1 . Add New Student Record");
        printf("\n 2 . View Student Record");
        printf("\n 3 . Search Student Record");
        printf("\n 4 . Delete/Modify Student Record");
        printf("\n 5 . Calculate Fee");
        printf("\n 6 . Go to category");
        printf("\n 0 . Exit\n");

        printf("\nEnter your choice : ");
        scanf("%d",&choice);
        if(choice==0)
            exit(1);
        else if(choice==1)
        {
            add_record();
            break;
        }
        else if(choice==2)
        {
            view_record();
            break;
        }
        else if(choice==3)
        {
            search_record();
            break;
        }

        else if(choice==4)
        {
            modify_record();
            break;
        }

        else if(choice==5)
        {
            fee();
            break;
        }

        else if(choice==6)
        {
            category();
            break;
        }

        else
            printf("Invalid input......\n Try again...");

    }
    while(choice!=0);

    getch();
}

void T_menu()
{
    int choice;

    system("CLS");

    do
    {
        printf(" 1 . Add New Teacher/staff Record");
        printf("\n 2 . View Teacher/staff Record");
        printf("\n 3 . Search Teacher/staff Record");
        printf("\n 4 . Delete/Modify Teacher/staff Record");
        printf("\n 5 . Calculate Salary");
        printf("\n 6 . Go to category");
        printf("\n 0 . Exit\n");

        printf("\nEnter your choice : ");
        scanf("%d",&choice);
        if(choice==0)
            exit(1);
        else if(choice==1)
        {
            T_add_record();
            break;
        }
        else if(choice==2)
        {
            T_view_record();
            break;
        }
        else if(choice==3)
        {
            T_search_record();
            break;
        }
        else if(choice==4)
        {
            T_modify_record();
            break;
        }

        else if(choice==5)
        {
            T_salary();
            break;
        }

        else if(choice==6)
        {
            category();
            break;
        }

        else
            printf("Invalid input......\n Try again...");

    }
    while(choice!=0);

    getch();
}

int main()
{
    system("CLS");

    int choise;

    printf(" 1 . register \n 2 . login \n");
    printf("\nEnter your choice : ");
    scanf("%d",&choise);

    if(choise == 1)
    {
        system("CLS");
        registe();
    }
    else if(choise == 2)
    {
        system("CLS");
        login();
    }
}
