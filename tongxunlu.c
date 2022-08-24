#include "tongxunlu.h"

//进入界面
void welcome()
{
    //system("clear");
    printf("***************************************\n");
    printf("******************WELCOME**************");
    printf("***************************************\n");
}
//菜单
void menu()
{

    //system("clear");
    printf("***************************************************\n");
    printf("********1、添加用户**************2、查看用户***********\n");
    printf("********3、搜索用户**************4、删除用户***********\n");
    printf("********5、修改用户**************6、退出通讯录*********\n");
    printf("*****************************************************\n");

}
//判断通讯录是否为空
bool linklistisempty(linklist *head)
{
    return head->next == NULL?1:0;
}
//创造一个通讯录链表
linklist* TongxunluCreate()
{
    linklist *head=(linklist*)malloc(sizeof(linklist));
    if(NULL==head)
    {
      printf("创建失败\n");
      exit(-1);
    }
    head->next=NULL;
    return head;
}
//将上次文件里的信息写入链表里
void Insert(linklist *head)
{
  //只读方式打开文件
  FILE *fp=fopen("./tongxunlu.txt","r");
  if(NULL==fp)
  {
    perror("fopen");
    return;
  }
  //循环读取文件
  while(1)
    {
    //创建一个结点
      linklist* p=TongxunluCreate();
      //将文件的内容读到结点里
      if(fread(p,sizeof(linklist)-sizeof(linklist*),1,fp)==0)//如果读取失败就释放该结点
       {
          perror("fread");
          free(p);
          return;
       } 
      //文件指针往后偏移一个，因为读到文件里换行读的
      fseek(fp,1,SEEK_CUR);
      //看链表是否为空，空就直接插入
      if(linklistisempty(head))
      {   
           p->next=head->next;
           head->next=p;
      }
      else//如果不为空，插入排序
      {
        //p1为头指针的地址
        linklist* p1=head;
        int flag=0;
        while(p1->next!=NULL)
        {   //比较插入
          if(strcmp(p1->next->name,p->name)>0)
          {
            p1->next=p->next;
            p->next=p1;
            flag++;
            break;
          }
          p1=p1->next;
        }
        if(0==flag)
        {
            p->next=p1->next;
            p1->next=p;
        }
        }
        //如果读到文件末尾
        if(feof(fp))
        {
           break;
        }
    }
    fclose(fp);
    return;
}
//判断通讯录是否为空
bool Linklistisempty(linklist *head)
{
    return head->next == NULL?1:0;
}

//遍历单链表
void LinklistPrint(linklist *head)
{   
  
  if(Linklistisempty(head))
   {
    printf("通讯录为空\n");
    return;
   }
    linklist *p=head->next;
    while(p->next != NULL)
    {
        printf("id   姓名  电话        年龄\n");
        printf("%-5s%-5s %-6s %-5s\n",p->id,p->name,p->tel,p->age);
        p=p->next;
    }
    printf("id   姓名  电话        年龄\n");
    printf("%-5s%-5s %-6s %-5s\n",p->id,p->name,p->tel,p->age);
}

//增加信息
void Addinfo(linklist *head)
{
    linklist *tmp = (linklist *)malloc(sizeof(linklist));
    tmp->next = NULL;
    printf("请输入号码:\n");
    scanf("%s",tmp->tel);
    printf("请输入英文名字:\n");
    scanf("%s",tmp->name);
    printf("请输入id:\n");
    scanf("%s",tmp->id);
    printf("请输入年龄：\n");
    scanf("%s",tmp->age);
    if(strlen(tmp->tel)<10 || strlen(tmp->id)<4)
        {
            printf("请输入正确的信息\n");
            return;
        }
   linklist *p=head;
   int flag=0;
   //插入时就按首字母排序
   while(p->next!=NULL)
    {
      if(strcmp(p->next->name,tmp->name)>0)
      {
        //插入到p->next的前面
        tmp->next=p->next;
        p->next=tmp;
        flag++;
        break;
      }
     p=p->next;
    }
      if(flag!=0)
     {
      printf("添加成功!\n");
      return;   
     }
      tmp->next=p->next;
      p->next=tmp;
      linklist *t=head->next;
    while(t->next != NULL)
    {
      if(strcmp(tmp->id,t->id)==0)
     {
       printf("id重复,请重新输入！\n");
       printf("请输入id:");
       scanf("%s",tmp->id); 
       printf("添加成功!\n");
       return; 
     }
    t=t->next; 
    }
    printf("写入成功!\n");
    return;
}
//id搜索
void SearchByID(linklist *head)
{
    if(linklistisempty(head))
    {
        printf("该通讯录为空\n");
        return;
    }
    int i = 0;
    char num[32]={0};
    printf("请输入id\n");
    scanf("%s",num);
    linklist *p=head->next;
    FILE *fp=fopen("./tongxunlu.txt","r");
    if(fp==NULL)
     {
        perror("fopen");
        return;
     }
    while(1)
     {
        if(0==fread(&p,sizeof(p),1,fp))
        {
            perror("fread");
            return;
        }
        if(strcmp(p->id,num)==0)
        {
            printf("id   姓名    电话      年龄\n");
            printf("%-5s %-5s %-6s   %-5s\n",p->id,p->name,p->tel,p->age); 
            return;
        }
            p=p->next;
     }
}
//姓名搜索
void SearchByName(linklist *head)
{
     int i = 0;
     char name[32]={0};
     printf("请输入姓名\n");
     scanf("%s",name);
     linklist *p=head->next;
     FILE *fp=fopen("./tongxunlu.txt","r");
     if(fp==NULL)
     {
       perror("fopen");
       return;
     }
    while(1)
     {
       if(fread(&p,sizeof(p),1,fp)==0)
      {
         
      }
       if(strcmp(name,p->name)==0)
      {
         printf("id    姓名    电话      年龄\n");
         printf("%-5s %-5s %-6s %-5s\n",p->id,p->name,p->tel,p->age); 
         return;
      }
        p=p->next;
     }
}

//搜索用户
void Search(linklist *head)
{
    if(linklistisempty(head))
    {
        printf("该通讯录为空\n");
        return;
    }
      int num = 0;
      printf("选择id搜索请输入1\n");
      printf("选择姓名搜索请输入2\n");
      scanf("%d",&num);
      switch(num)
        {
         case 1:
           SearchByID(head);
           break;
         case 2:
           SearchByName(head);
           break;
         default:
           printf("输入错误，请重新选择\n");
           break;
       }
}

//删除用户
void Delete(linklist *head)
{
   if(linklistisempty(head))
    {
        printf("该通讯录为空\n");
        return;
    }
   int i=0;
   char num[32] = {0};
   printf("请输入要删除用户的id\n");
   scanf("%s",num);
   linklist *p=head;
   linklist *q=NULL;
   while(p->next != NULL)
   {
    //p=p->next;
    if(strcmp(p->next->id,num)==0)
    {
        q=p->next;
        p->next=q->next;
        q->next=NULL;
        free(q);
        printf("删除成功!\n");
        return;
    }
    p=p->next;
   }
}

//修改
void Change(linklist *head)
{
    int i = 0;
    char id[32] = {0};
    printf("请输入要修改信息的id\n");
    scanf("%s",id);
    linklist *p = head;
    while(p->next != NULL)
    {
        //printf("********************************\n");
        if(strcmp(p->next->id,id)==0)
        {
            printf("请输入id\n");
            scanf("%s",p->next->id);
            printf("请输入姓名\n");
            scanf("%s",p->next->name);
            printf("请输入年龄\n");
            scanf("%s",p->next->age);
            printf("请输入电话\n");
            scanf("%s",p->next->tel);
            if(strlen(p->next->tel)<10 || strlen(p->next->id)<4)
           {
            printf("请输入正确的信息\n");
            return;
           } 
            printf("修改成功\n");
            return;
        }
        p=p->next;
    }
}

//写入文件
void SaveFile(linklist *head)
{
   if(Linklistisempty(head))
   {
     return;
   }
   FILE *fp=fopen("./tongxunlu.txt","w");
   if(fp == NULL)
   {
    perror("fopen");
    return;
   }
   linklist *p=head->next;
   while(1)
   {
    if(p == NULL)
    {
        break;
    }
    if(1!=fwrite(p,sizeof(linklist)-sizeof(linklist*),1,fp))
    {
        perror("fwrite");
        break;
    }
    char ch='\n';
    if(1!=fwrite(&ch,sizeof(char),1,fp))
    {
        perror("fwrite");
        break;
    }
    p=p->next;
   }
   fclose(fp);
   return;
}