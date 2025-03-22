#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

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

void initList(DuLinkedList* L) //初始化链表
{
	L->head=(DuLNode*)malloc(sizeof(DuLNode));
	if(L->head==NULL)//如果头结点为空，就是内存分配失败的情况 
	{
		printf("内存分配失败\n");
		return;
	}
    L->head->next=NULL;//将后继指针设为空 
	L->head->prior=NULL;//将前驱指针设为空 
}

void inputdata(DuLinkedList*L)//定义录入data函数 尾插法 
{
	int n,data;
	printf("请输入要输入的元素的个数：");
	scanf("%d",&n);
	
	DuLNode* tail=L->head;//尾指针指向头结点
	for(int i=0;i<n;i++)//每次循环，会读取一个data插入到链表的末尾 
	{
		printf("请输入第%d个元素：",i+1);
		scanf("%d",&data);
		DuLNode* newNode=(DuLNode*)malloc(sizeof(DuLNode));
		if(newNode==NULL)
		{
			printf("内存分配失败\n");
			return;	
		}	
		
		newNode->data=data;//将输入的数据给新结点的数据 
        newNode->next=NULL;//将新结点的next指针置为NULL 
        newNode->prior=tail;//将新结点的prior指针指向当前的尾结点 
        tail->next=newNode;//将当前结点的next指针指向新结点 
        tail=newNode;//更新尾结点 
	} 
    system("pause"); // 暂停程序
    system("cls"); // 清屏 
    menu();
}

void printlist(DuLinkedList* L) //打印链表 
{
    DuLNode* current = L->head->next;//从头结点的下一个结点开始遍历
    if (current==NULL)//考虑链表为空的情况 
	{
        printf("链表为空\n");
        return;
    }
    printf("链表中的元素为：\n");
    while(current!=NULL)//不是空的情况 
	{
        printf("%d",current->data);//打印当前结点的数据
        current=current->next;//移动到下一个节点
		printf("\n");
    }
    
    system("pause"); // 暂停程序
    system("cls"); // 清屏 
    menu();
}

void clearlist(DuLinkedList* L)
{
    DuLNode*p=L->head;//指向当前节点
    DuLNode*q=NULL;//指向下一个节点
    while(p!=NULL)//遍历链表并释放节点
	{
        q=p->next;//获取下一个节点
        free(p);//释放当前节点
        p = q;//移动到下一个节点
    }
    // 重置头结点
    L->head = NULL;
    printf("已成功清空链表！\n");
	system("pause");//暂停程序
	system("cls");//清屏 	
	menu();
}

void searchlist(DuLinkedList* L)
{
	printf("请输入要查找的data：");
	int data;
	scanf("%d",&data);
	DuLNode* move=L->head->next;//从头结点的下一个结点开始遍历
    while(move!=NULL)//不是空的情况
    {
        if(move->data==data) //查询对应的data 
        {
			printf("确实存在这么一个data\n"); 
			printf("%d\n",move->data); 
			return;//返回找到的节点指针
        }
        move=move->next; //移动到下一个节点
    }
	printf("未找到指定data！！！\n");
	system("pause");//暂停程序
	system("cls");//清屏 
	menu();
}

void modifylist(DuLinkedList* L)//修改 
{
    printf("请输入要修改的data：");
    int oldData;
    scanf("%d", &oldData);//输入要修改的data，这里称为olddata 
    DuLNode* move=L->head;
    while(move!=NULL) 
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
    menu();
}

void deletelist(DuLinkedList* L)//删除指定元素
{
	printf("请输入要删除的data:\n");
    int data;
    scanf("%d",&data);
    DuLNode* move=L->head;//move指针用于遍历链表，指向链表头结点 
    DuLNode* prev=NULL;//prev用于记录前一个结点，指向空 
    while(move!=NULL) //遍历链表 
	{
        if(move->data==data) 
		{
            if(prev==NULL) //如果要删除的是头结点
			{ 
                L->head=move->next;//将链表的头指针 L->head 指向当前节点的下一个节点 move->next
                if(L->head!=NULL) //如果新的头节点不为 NULL，则将其 prior 指针设置为 NULL
				{
                    L->head->prior=NULL;
                }
            } 
			else //要删除的是中间结点或者尾结点 
			{
                prev->next=move->next;//将前一个节点 prev 的 next 指针指向当前节点的下一个节点 move->next
                if(move->next!=NULL) 
				{
                    move->next->prior=prev;//如果当前节点的下一个节点不为 NULL，则将其 prior 指针设置为 prev
                }
            }
            free(move);//释放内存空间。
            printf("删除成功！\n");
            return;
        }
        prev=move;//如果当前结点不是要删除的节点
        move=move->next;//prev更新为当前节点 move并将 move更新为下一个节点 move->next
    }
    printf("未找到指定data！！！\n");//如果前面的都没找到，那么就是没有找到data了 
    system("pause"); // 暂停程序
    system("cls"); // 清屏
    menu();
} 

void findmiddle(DuLinkedList* L)//快慢指针法 
{
	if (L->head==NULL) 
	{
        printf("链表为空，没有中间值\n");
        return;
    }
    DuLNode* slow=L->head;//定义一个慢指针，开始时指向head 
    DuLNode* fast=L->head;//定义一个快指针，开始时也指向head 
    
    while (fast!= NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//慢指针每移动一个，快指针移动两个 
        fast = fast->next->next;//等快指针指向链表尾部的时候，慢指针刚好指向链表的中间值 
    }
    printf("链表的中间值是: %d\n", slow->data);
    
    system("pause"); // 暂停程序
    system("cls"); // 清屏 
    menu();
}

void insertlist(DuLinkedList* L,int data)//遍历链表，新结点插入到上一个结点的尾部，下一个结点的头部 
{
	printf("请输入要插入的位置：\n");
    int position;
    scanf("%d", &position);//读取输入的位置
    DuLNode* newNode=(DuLNode*)malloc(sizeof(DuLNode));//分配内存给新结点 
    if(newNode==NULL)//判断内存是否分配成功 
	{
        printf("内存分配失败\n");
        return;
    }
    newNode->data=data;//新结点数据 
    newNode->next=NULL;//新结点next指针指向空 
    newNode->prior=NULL;//prior指针指向空 

    if(position==1)//插入到头结点的情况 
	{ 
        newNode->next=L->head;//新结点next指针指向头结点 
        if(L->head != NULL)//链表不为空的情况 
		{
            L->head->prior=newNode;//prior指向新结点 
        }
        L->head=newNode;// 新链表头指针为新节点
        printf("插入成功！\n");
        return;
    }

    DuLNode* current=L->head; //定义一个指针current指向链表头结点
    for(int i=1;i<position-1&&current!=NULL;i++) //找到插入位置的前一个节点
	{
        current = current->next;//移动current指针到下一个节点
    }
    if(current==NULL) 
	{
        printf("位置超出链表长度\n");
        free(newNode);//释放新结点的内存 
        return;
    }

    newNode->next=current->next;//新结点的next指针指向current的下一个结点 
    newNode->prior=current;//新结点的prior指针指向current结点 
    if(current->next!=NULL) //如果current的下一个结点不为空
	{
        current->next->prior=newNode;//让current的下一个结点的prior指针指向新的 
    }
    current->next=newNode;//current的next指针指向新节点
    printf("插入成功！\n");
}

int judgecycle(DuLinkedList* L)//判断成环 
{
	if(L->head==NULL||L->head->next==NULL) 
	{
        return 0; //链表为空或只有一个节点，不可能成环
    }
    DuLNode* slow=L->head;
    DuLNode* fast= L->head;
    while (fast!=NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//慢指针每次移动一个，快指针每次移动两个 
        fast = fast->next->next;   
        if(slow==fast) 
		{
			printf("链表成环\n"); 
            return 1; //如果快慢指针值相等就是碰到一起了，说明链表有环
        }
    }
    printf("链表不成环\n");
    return 0; // 快指针到达链表末尾，说明链表无环
}
