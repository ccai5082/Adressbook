#ifndef _TONGXUNLU_H_  
#define _TONGXUNLU_H_
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<sys/types.h>
#define MAX 1024
typedef int DataType;
typedef struct node
{
   char id[6];
   char name[4];
   char age[3];
   char tel[12];
   //指针域
   struct node *next; 
   
}linklist;

//struct linklist p1;//录入时使用的结构体
//struct linklist p2;//读取时使用的结构体
void welcome();
void menu();
//创造一个通讯录链表
linklist* TongxunluCreate();
//将上次文件里的信息写道链表里
void Insert(linklist *head);
//判断通讯录是否为空
bool Linklistisempty(linklist *head);
//遍历通讯录
void LinklistPrint(linklist *head);
//增加信息
void Addinfo(linklist *head);
//查看信息
void View(linklist *head);
//搜索用户
void Search(linklist *head);
//id搜索
void SearchByID(linklist *head);
//姓名搜索
void SearchByName(linklist *head);
//删除用户
void Delete(linklist *head);
//修改
void Change(linklist *head);
//写入文件
void SaveFile(linklist *head);
#endif