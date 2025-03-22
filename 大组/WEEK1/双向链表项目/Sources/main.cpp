#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include "function.h"

typedef struct DuLNode 
{
	int data;
	struct DuLNode* next;//双向链表与单向链表的区别： 
	struct DuLNode* prior;//单向一个next，双向有前驱指针和后继指针 
}DuLNode;

typedef struct//定义单链表结构
{
    DuLNode* head; //定义头结点 
}DuLinkedList;

int main() 
{

    system("color F0"); //设置窗口颜色 
	char password[20];//声明一个字符数组password，用于存储用户输入的密码
	DuLinkedList L;
    initList(&L);   
    menu();//调用打印菜单的函数 
	printf("请输入您的密码：\n");
	scanf("%s",password);

    system("pause");//使程序暂停执行
	system("cls");
	
    if(strcmp(password,"1234")==0)
    {
    	printf("欢迎进入！！！\n"); 
   		menu();
   		while (1) // 交互功能界面设置 
		{ 
        	int chose;
        	scanf("%d", &chose);
       		switch (chose) 
			{
				case 1:inputdata(&L);//录入 
						break;
       	 	    case 2:printlist(&L);//打印 
						break;
           		case 3:clearlist(&L);// 清空 
						break; 
				case 4:searchlist(&L);//查找 
						break; 
				case 5:modifylist(&L);//修改 
						break;
				case 6:deletelist(&L);//删除 
						break; 
				case 7:findmiddle(&L);//找到双链表的中点
						break;
				case 8:insertlist(&L,77);//插入数据77 
						break; 
				case 9:judgecycle(&L);//判断双链表是否成环 
						break; 
            	case 10: printf("退出，感谢您的使用，欢迎下次使用\n"); exit(0); // 退出系统 
            	default:printf("您的输入有误，请重新输入！！！\n"); 
						system("pause"); system("cls"); // 暂停程序，用户查看操作结果 ,接着进行清屏操作 
			}
  		 }
  	}
	else if(strcmp(password, "1234")!= 0)
    {
   		printf("输入错误！请重新输入\n");
    }
    return 0;
}
