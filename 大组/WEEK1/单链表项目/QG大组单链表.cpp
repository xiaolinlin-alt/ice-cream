#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

void menu()//选择功能界面 
{
	printf("****************************************\n"); 
	printf("***************欢迎进入*****************\n");
	printf("****************************************\n"); 
	printf("*      1.录入                          *\n");
	printf("*      2.打印                          *\n");
	printf("*      3.清空                          *\n");
	printf("*      4.查找                          *\n");
	printf("*      5.修改                          *\n");
	printf("*      6.删除                          *\n");
	printf("*      7.找到单链表的中点              *\n");
	printf("*      8.插入                          *\n");
	printf("*      9.判断单链表是否成环            *\n");
	printf("*      10.退出程序                     *\n");
	printf("*      密码1234                        *\n"); 
	printf("****************************************\n"); 
} 
typedef struct Node//定义单链表节点结构
{
    int data;//定义一块数据 
    struct Node* next;//定义指向下一个数据的指针 
}Node;

typedef struct//定义单链表结构
{
    Node* head; //定义头结点 
}LinkedList; //定义单链表名字 


void initList(LinkedList* L) //初始化链表
{
    L->head=NULL;//将头指针设为空 
}

void inputdata(LinkedList*L) //定义录入data函数 尾插法 
{
	Node*fresh=(Node*)malloc(sizeof(Node));//动态分配内存，创建新结点fresh 
	if(fresh==NULL) 
	{
        printf("内存分配失败\n");
        return;
    }
	fresh->next=NULL;//将其指向空 
	
	printf("请输入data：");
    scanf("%d",&fresh->data);//新输入data
	if(L->head==NULL) 
	{
        L->head=fresh;//如果链表为空,将新节点设置为头节点
    } 
	else
	{
        Node* move=L->head; // 再定义一个，初始化为头结点，尾插法 
        while(move->next!=NULL) // 一直移动到最后面
		{ 
            move=move->next; // 往后走,遍历链表，目的是将那个新输入的data移到链表尾部 
        }
        // 将data插入到尾部
        move->next =fresh;
    }
    system("pause"); // 暂停程序
    system("cls"); // 清屏 
}

void printlist(LinkedList*L)//打印链表 
{
	Node*move=L->head;
	while(move!=NULL)//一直移动到最后面,遍历 
	{
		//打印出订单信息 
		printf("data:");
		printf("%d\n",move->data); 		
		move=move->next;
	} 
	
	system("pause");//暂停程序
	system("cls");//清屏 	
}

void clearlist(LinkedList* L)//清空链表 
{
    Node*p=L->head;//指向当前节点
    Node*q=NULL;//指向下一个节点
    while(p!=NULL)//遍历链表并释放节点
	{
        q=p->next;//获取下一个节点
        free(p);//释放当前节点
        p = q;//移动到下一个节点
    }
    // 重置头结点
    L->head = NULL;
    
	system("pause");//暂停程序
	system("cls");//清屏 	
}
void searchOrder(LinkedList* L)//定义查询订单信息的函数
{
	printf("请输入要查找的data：");
	int data;
	scanf("%d",&data);
	Node*move=L->head;
	while(move!=NULL)//查询对应的data
	{
		if(data==move->data)
		{
			printf("确实存在这么一个data"); 
			printf("%d\n",move->data); 
			return;//找到对应的订单ID就返回，不用break，好走下一步 
		}	
		move=move->next;
	} 
	printf("未找到指定data！！！\n");
	system("pause");//暂停程序
	system("cls");//清屏 
} 

void modifylist(LinkedList* L)//修改 
{
    printf("请输入要修改的data：");
    int oldData;
    scanf("%d", &oldData);//输入要修改的data，这里称为olddata 
    Node* move=L->head;
    while (move != NULL) 
	{
        if(move->data==oldData)
		{
            printf("请输入新的data：");
            int newData;
            scanf("%d", &newData);
            move->data=newData;
            printf("修改成功！新的data为：%d\n", newData);
            return;
        }
        move = move->next;
    }
    printf("未找到指定data！！！\n");
    system("pause"); // 暂停程序
    system("cls"); // 清屏 
}

void deletelist(LinkedList* L)//删除指定元素
{
    printf("请输入要删除的data：");
    int data;
    scanf("%d", &data);//确定要删除的数据data 
    Node* current=L->head;//创建指针现在和先前的 
    Node* previous=NULL;
    
    if(current==NULL)//如果链表为空，直接返回
	{
        printf("链表为空，无法删除\n");
        return;
    }
    if (current!=NULL&&current->data==data)//如果要删除的结点是头结点
	{
        L->head=current->next; //将头指针指向下一个结点 
        free(current); // 释放头结点内存，删除东西了要free 
        printf("删除成功！\n");
        return;
    }
    while(current!=NULL&&current->data!=data)//遍历链表，寻找要删除的data 
	{
        previous=current;
        current=current->next;
    }
    if(current==NULL)//如果没有找到要删除的节点
	{
        printf("未找到data！！！\n");
        return;
    }
    // 找到了的情况 
    previous->next=current->next; // 将前一个结点的next指向当前节点的下一个节点head 
    free(current);//释放当前节点内存
    printf("删除成功！\n");
}

void findmiddle(LinkedList* L)//快慢指针法 
{
    if (L->head==NULL) 
	{
        printf("链表为空，没有中间值\n");
        return;
    }
    Node* slow=L->head;//定义一个慢指针，开始时指向head 
    Node* fast=L->head;//定义一个快指针，开始时也指向head 
    
    while (fast!= NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//慢指针每移动一个，快指针移动两个 
        fast = fast->next->next;//等快指针指向链表尾部的时候，慢指针刚好指向链表的中间值 
    }
    printf("链表的中间值是: %d\n", slow->data);
    
    system("pause"); // 暂停程序
    system("cls"); // 清屏 
}

void insertlist(LinkedList* L, int data)//遍历链表，新结点插入到上一个结点的尾部，下一个结点的头部 
{
    Node* fresh=(Node*)malloc(sizeof(Node)); //动态分配内存，创建新结点fresh
    if (fresh==NULL) 
	{
        printf("内存分配失败\n");
        return;
    }
    fresh->data=data;//设置新节点的数据
    fresh->next=NULL; //将其指向空
    if(L->head==NULL) 
	{
        L->head=fresh;//如果链表为空,将新节点设置为头节点
    } else 
	{
        Node* move=L->head;//定义一个指针，初始化为头结点
        while(move->next!=NULL) //一直移动到最后面
		{ 
            move=move->next; // 往后走,遍历链表
        }  
        move->next = fresh;//将新节点插入到尾部
    }
}

int judgecycle(LinkedList* L)//判断成环 
{
    if(L->head==NULL||L->head->next==NULL) 
	{
        return 0; //链表为空或只有一个节点，不可能成环
    }
    Node* slow=L->head;
    Node* fast= L->head;
    while (fast!=NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//慢指针每次移动一个，快指针每次移动两个 
        fast = fast->next->next;   
        if(slow==fast) 
		{
            return 1; //如果快慢指针值相等就是碰到一起了，说明链表有环
        }
    }
    return 0; // 快指针到达链表末尾，说明链表无环
}

int main() 
{

    system("color F0"); //设置窗口颜色 
	char password[20];//声明一个字符数组password，用于存储用户输入的密码
	LinkedList L;
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
           		case 3:clearlist(&L); //清空 
						break; 
				case 4:searchOrder(&L);//查找 
						break; 
				case 5:modifylist(&L);//修改 
						break;
				case 6:deletelist(&L);//删除 
						break; 
				case 7:findmiddle(&L);//找到单链表的中点
						break;
				case 8:insertlist(&L,77);//插入数据77 
						break; 
				case 9:judgecycle(&L);//判断单链表是否成环 
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

