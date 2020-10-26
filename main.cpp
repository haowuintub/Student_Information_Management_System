#include <stdio.h>/*标准输入/输出库函数*/
#include <stdlib.h>/*标准函数库*/
#include<string.h>/*字符串函数库*/
#define TITLE "Student Information Management System"/*标题文字*/
#define MAX 32
#define MENU_MAIN_COUNT 7/*主函数菜单的选项个数*/

#define MAX_NUMBER 10
#define MAX_NAME 11
#define MAX_SEX 3
#define MAX_NATIVE 11
#define MAX_BIRTHDAY 9
#define MAX_QQ 21
#define MAX_MOBILE 21
#define MAX_EMOTION 11
/*数据类型定义*/
typedef struct _person/*定义了新类型_person*/
{
    char number[MAX_NUMBER];/*学号*/
    char name[MAX_NAME]; /*名字*/
    char sex[MAX_SEX]; /*性别*/
    char native[MAX_NATIVE]; /*籍贯*/
    char birthday[MAX_BIRTHDAY]; /*生日*/
    char qq[MAX_QQ]; /*qq*/
    char mobile[MAX_MOBILE]; /*手机*/
    char emotion[MAX_EMOTION]; /*感情状况*/
}person;
typedef struct _addr_book/*定义结构体类型_addr_book*/
{
    person per;
    struct _addr_book *next;
}addr_book;
addr_book *first =NULL;/*addr_book结构体，链表的节头，置空*/
/*主要函数声明*/
void input_record();/*输入学生信息的处理*/
void show_record();/*显示学生信息的处理*/
void search_record();/*查询学生信息的处理*/
void update_record();/*更新学生信息*/
void delete_record();/*删除学生信息*/
void save_to_file();/*保存到文件的处理*/
void exit_system();/*退出系统*/
/*辅助函数声明*/
int print_menu();/*打印主菜单界面*/
addr_book *get_last(addr_book *from);/*取得链表最后一个值*/
void print_person(person *P);/*显示一个学生的信息*/
void input_person(person *P);/*提示输入一个学生的具体信息*/
/*常量声明*/
char menu_main[]=/*储存主菜单要显示的字符*/
        "|\n"
        "| 1 Enter student personal information\n"
        "| 2 Show student personal information\n"
        "| 3 Query student personal information\n"
        "| 4 Update student personal information\n"
        "| 5 Delete student personal information\n"
        "| 6 Save document\n"
        "| 7 Exit system\n"
        "|\n";
void (*menu_main_func[])() =/*函数指针数组 menu_main_func 存储的是主菜单项中7个功能函数的地址，分别对应1~7菜单项。*/
        {
                input_record,
                show_record,
                search_record,
                update_record,
                delete_record,
                save_to_file,
                exit_system,

        };



char menu[]=   /*显示菜单字符*/
        "+=================================================+\n"
        "| Student Information Management System                           |\n"
        "+------------------------------------------------------+\n"
        "| 1 Add contacts                             |\n"
        "| 2 Show all students                          |\n"
        "| 3 Query students                               |\n"
        "| 4 Update students                               |\n"
        "| 5 Delete student                               |\n"
        "| 6 Save                                   |\n"
        "| 7 Exit system                               |\n"
        "+=================================================+\n";
int  main()
{
    int flg =1;
    while (flg)
    {
        switch(print_menu()){
            case 1:        /*输入1，调用input_record ()函数，添加信息*/
                input_record ();
                break;
            case 2:       /*输入2，调用show_record ()函数，显示信息*/
                show_record ();
                break;
            case 3:       /*输入3，调用search_record ()函数，查询信息*/
                search_record ();
                break;
            case 4:      /*输入4，调用update_record ()函数，更新信息*/
                update_record ();
                break;
            case 5:      /*输入5，调用delete_record ()函数，删除信息*/
                delete_record ();
                break;
            case 6:      /*输入6，调用save_to_file ()函数，保存信息*/
                save_to_file ();
                break;
            case 7:     /*输入7，调用exit_system ()函数，退出*/
                exit_system ();
                break;
        }
    }
}

void input_record ()    /*输入1，调用input_record ()函数，添加信息*/
{
    char input = 'N';
    addr_book *last=NULL;
    addr_book *new_addr=(addr_book*)malloc(sizeof(addr_book));
/*将中new_addr的前addr_book个长度的初值置为0*/
    memset(new_addr,0,sizeof(addr_book));
    new_addr->next=NULL;
    if (first==NULL)
    {
        first= new_addr;
    }
    else
    {
        last=get_last(first);
        last->next=new_addr;
    }
    input_person(&(new_addr->per));
    printf(">Continue typing? (Y to continue, N to return to the menu)");
    getchar();
    input=getchar();
    if (input=='Y'|| input=='y')
    {
        input_record ();
    }
}

void show_record ()     /*输入2，调用show_record ()函数，显示信息*/

{
    int i=0;
    addr_book *p=first;
    while (p!=NULL)
    {
        i++;
        printf("******Student %d************************************************\n",i);
        print_person(&(p->per));
        p = p->next;
    }
    if(i==0)
    {
        printf("No students!");

    }
    printf("Press any key to return to the menu...");
    getchar();
    getchar();
}
void search_record ()      /*输入3，调用search_record ()函数，查询信息*/

{
    int count=0;
    char input ='N';
    char name [MAX_NAME]={0};
    addr_book *p=first;
    printf(">Please enter the name of the student you want to know(maximal %d characters):",MAX_NAME - 1);
    scanf("%s",name);
    while (p!=NULL)
    {
        if (strcmp(p->per.name,name)==0)
        {print_person(&(p->per));
            count++;

        }
        p=p->next;
    }
    if (count==0)
    {
        printf("There is no student called %s.",name);
    }
    printf("Continue searching? (Y to continue searching, N to return to the menu)");
    getchar();
    input = getchar();
    if (input == 'Y'|| input =='y')
    {
        search_record ();
    }
}
void update_record ()       /*输入4，调用update_record ()函数，更新信息*/


{
    int count=0;
    char input = 'N';
    char name[MAX_NAME]={0};
    addr_book *p=first;
    printf(">Please enter the name of the student you want to update(maximal %d characters):",MAX_NAME-1);
    scanf("%s",name);
    while (p !=NULL)
    {
        if(strcmp(p->per.name,name)==0)
        {
            print_person(&(p->per));
            count++;
            break;
        }
        p=p->next;
    }
    if (count==0)
    {
        printf("There is no student called %s.",name);
    }
    else
    {
        input_person(&(p->per));
    }
    printf("Continue to update other students? (Y to continue to update, N to return to the menu)");
    getchar();
    input= getchar();
    if (input =='Y'|| input =='y')
    {
        update_record ();
    }

}
void delete_record ()          /*输入5，调用delete_record ()函数，删除信息*/

{
    int count=0;
    char input='N';
    char name[MAX_NAME]={0};
    addr_book *p=first;
    addr_book *p1=NULL;
    printf(">Please enter the name of the student you want to delete(maximal %d characters):",MAX_NAME-1);
    scanf("%s",name);
    while (p!=NULL)
    {
        if(strcmp(p->per.name,name)==0)
        {
            print_person(&(p->per));
            count++;
            break;
        }
        p=p->next;
    }
    if (count==0)
    {
        printf("There is no student called %s.",name);
    }
    else
    {
        printf("Are you sure you want to delete the contact whose name is [%d]?(Y confirm, N cancel)",name);
        getchar();
        input = getchar();
        if (input =='Y'|| input =='y')
        {
            if (p==first)
            {
                first = p->next;
            }
            else
            {
                p1 =first;
                while (p1 !=NULL)
                {
                    if (p1->next==p)
                    {
                        p1->next = p->next;
                        break;
                    }
                    p1 = p1->next;
                }
            }
            free(p);
        }
    }
    printf("Continue to delete other students? (Y Continue to delete, N Return to the menu)");
    getchar();
    input = getchar();
    if (input =='Y'|| input =='y')
    {
        delete_record ();
    }
}
void save_to_file ()          /*输入6，调用save_to_file ()函数，保存信息*/
{
    FILE *fp;
    char file[100];
    addr_book *p=first;
    printf("Please enter the file name:");
    scanf("%s",file);
    fp=fopen(file,"w");
    while(p !=NULL)
    {
        fprintf(fp,"%s,%s,%s,%s,%s,%s,%s,%s\n",
                p->per.number,p->per.name,p->per.sex,p->per.native,p->per.birthday,p->per.qq,p->per.mobile,p->per.emotion);
        p=p->next;
    }
    fclose(fp);
    printf("Successfully saved!\nPress any key to return to the menu..\n");
    getchar();
    getchar();
}
void exit_system ()           /*输入7，调用exit_system ()函数，退出*/

{
    addr_book *pdel=first;
    addr_book *p=NULL;
    if (pdel ==NULL)
    {
        exit(0);
    }
    while (pdel->next !=NULL)
    {
        p=pdel->next;
        free(pdel);
        pdel =p;
    }
    free(pdel);
    exit(0);
}

/*辅助函数功能介绍*/
/*显示主菜单界面*/
int print_menu()
{
    int selected=0;
    system("cls");
    printf(menu);
    printf(">Please choose[1~7]:");
    scanf("%d",&selected);
    if(selected<1 || selected >7)
    {
        printf("Wrong choice!(Please enter 1~7).Press any key to continue...");
        getchar();
        getchar();
    }
    return selected;
}
void input_person(person *p)    /*提示输入相关同学的信息*/
{
    printf(">Please enter student information:\n");
    printf("Please enter student ID(Maximum length %d characters):",MAX_NUMBER-1);
    scanf("%s",p->number);
    printf("Please enter the name of student(Maximum length %d characters):",MAX_NAME-1);
    scanf("%s",p->name);
    printf("Please enter the gender of student(Maximum length %d characters):",MAX_SEX-1);
    scanf("%s",p->sex);
    printf("Please enter the birthplace of student(Maximum length %d characters):",MAX_NATIVE-1);
    scanf("%s",p->native);
    printf("Please enter the birthday of student(Maximum length %d characters):",MAX_BIRTHDAY -1);
    scanf("%s",p->birthday);
    printf("Please enter the Email of student(Maximum length %d characters):",MAX_QQ-1);
    scanf("%s",p->qq);
    printf("Please enter the phone number of student(Maximum length %d characters):",MAX_MOBILE-1);
    scanf("%s",p->mobile);
    printf("Please enter the marital status of student(Maximum length %d characters):",MAX_EMOTION-1);
    scanf("%s",p->emotion);
}
void print_person(person *p)   /*显示一个同学的信息*/
{
    printf("student ID:%s\t name:%s\t gender:%s\n ",p->number,p->name,p->sex);
    printf("birthplace:%s\n",p->native);
    printf("birthday:%s\n",p->birthday);
    printf("Email:%s\n",p->qq);
    printf("phone number:%s\n",p->mobile);
    printf("marital status:%s\n",p->emotion);
    printf("\n");

}

/*取得链表最后一个值*/
addr_book *get_last(addr_book *from)
{
    addr_book *p=from;
    while (p->next !=NULL)
    {
        p=p->next;
    }
    return p;
}
