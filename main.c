#include"tongxunlu.h"
int main(int argc,const char *argv[])
{
    linklist *head=TongxunluCreate();
    //文件里写入链表里
    Insert(head);
    welcome();
    int choice;
    while(1)
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
               Addinfo(head);
               break;
            case 2:
               LinklistPrint(head);
               break;
            case 3:
               Search(head);
               break;
            case 4:
               Delete(head);
               break;
            case 5:
               Change(head);
               break;
            case 6:
               SaveFile(head);
               printf("退出通讯录\n");
               return 0;
            default:
                printf("输入错误，请重新选择\n");
                break;
        }
    }
    return 0;
}