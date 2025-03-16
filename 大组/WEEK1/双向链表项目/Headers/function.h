#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

typedef struct DuLNode 
{
	int data;
	struct DuLNode* next;//˫�������뵥����������� 
	struct DuLNode* prior;//����һ��next��˫����ǰ��ָ��ͺ��ָ�� 
}DuLNode;

typedef struct//���嵥����ṹ
{
    DuLNode* head; //����ͷ��� 
}DuLinkedList;

void initList(DuLinkedList* L) //��ʼ������
{
	L->head=(DuLNode*)malloc(sizeof(DuLNode));
	if(L->head==NULL)//���ͷ���Ϊ�գ������ڴ����ʧ�ܵ���� 
	{
		printf("�ڴ����ʧ��\n");
		return;
	}
    L->head->next=NULL;//�����ָ����Ϊ�� 
	L->head->prior=NULL;//��ǰ��ָ����Ϊ�� 
}

void inputdata(DuLinkedList*L)//����¼��data���� β�巨 
{
	int n,data;
	printf("������Ҫ�����Ԫ�صĸ�����");
	scanf("%d",&n);
	
	DuLNode* tail=L->head;//βָ��ָ��ͷ���
	for(int i=0;i<n;i++)//ÿ��ѭ�������ȡһ��data���뵽�����ĩβ 
	{
		printf("�������%d��Ԫ�أ�",i+1);
		scanf("%d",&data);
		DuLNode* newNode=(DuLNode*)malloc(sizeof(DuLNode));
		if(newNode==NULL)
		{
			printf("�ڴ����ʧ��\n");
			return;	
		}	
		
		newNode->data=data;//����������ݸ��½������� 
        newNode->next=NULL;//���½���nextָ����ΪNULL 
        newNode->prior=tail;//���½���priorָ��ָ��ǰ��β��� 
        tail->next=newNode;//����ǰ����nextָ��ָ���½�� 
        tail=newNode;//����β��� 
	} 
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
    menu();
}

void printlist(DuLinkedList* L) //��ӡ���� 
{
    DuLNode* current = L->head->next;//��ͷ������һ����㿪ʼ����
    if (current==NULL)//��������Ϊ�յ���� 
	{
        printf("����Ϊ��\n");
        return;
    }
    printf("�����е�Ԫ��Ϊ��\n");
    while(current!=NULL)//���ǿյ���� 
	{
        printf("%d",current->data);//��ӡ��ǰ��������
        current=current->next;//�ƶ�����һ���ڵ�
		printf("\n");
    }
    
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
    menu();
}

void clearlist(DuLinkedList* L)
{
    DuLNode*p=L->head;//ָ��ǰ�ڵ�
    DuLNode*q=NULL;//ָ����һ���ڵ�
    while(p!=NULL)//���������ͷŽڵ�
	{
        q=p->next;//��ȡ��һ���ڵ�
        free(p);//�ͷŵ�ǰ�ڵ�
        p = q;//�ƶ�����һ���ڵ�
    }
    // ����ͷ���
    L->head = NULL;
    printf("�ѳɹ��������\n");
	system("pause");//��ͣ����
	system("cls");//���� 	
	menu();
}

void searchlist(DuLinkedList* L)
{
	printf("������Ҫ���ҵ�data��");
	int data;
	scanf("%d",&data);
	DuLNode* move=L->head->next;//��ͷ������һ����㿪ʼ����
    while(move!=NULL)//���ǿյ����
    {
        if(move->data==data) //��ѯ��Ӧ��data 
        {
			printf("ȷʵ������ôһ��data\n"); 
			printf("%d\n",move->data); 
			return;//�����ҵ��Ľڵ�ָ��
        }
        move=move->next; //�ƶ�����һ���ڵ�
    }
	printf("δ�ҵ�ָ��data������\n");
	system("pause");//��ͣ����
	system("cls");//���� 
	menu();
}

void modifylist(DuLinkedList* L)//�޸� 
{
    printf("������Ҫ�޸ĵ�data��");
    int oldData;
    scanf("%d", &oldData);//����Ҫ�޸ĵ�data�������Ϊolddata 
    DuLNode* move=L->head;
    while(move!=NULL) 
	{
        if(move->data==oldData)
		{
            printf("�������µ�data��");
            int newData;
            scanf("%d", &newData);
            move->data=newData;
            printf("�޸ĳɹ����µ�dataΪ��%d\n", newData);
            return;
        }
        move = move->next;
    }
    printf("δ�ҵ�ָ��data������\n");
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
    menu();
}

void deletelist(DuLinkedList* L)//ɾ��ָ��Ԫ��
{
	printf("������Ҫɾ����data:\n");
    int data;
    scanf("%d",&data);
    DuLNode* move=L->head;//moveָ�����ڱ�������ָ������ͷ��� 
    DuLNode* prev=NULL;//prev���ڼ�¼ǰһ����㣬ָ��� 
    while(move!=NULL) //�������� 
	{
        if(move->data==data) 
		{
            if(prev==NULL) //���Ҫɾ������ͷ���
			{ 
                L->head=move->next;//�������ͷָ�� L->head ָ��ǰ�ڵ����һ���ڵ� move->next
                if(L->head!=NULL) //����µ�ͷ�ڵ㲻Ϊ NULL������ prior ָ������Ϊ NULL
				{
                    L->head->prior=NULL;
                }
            } 
			else //Ҫɾ�������м������β��� 
			{
                prev->next=move->next;//��ǰһ���ڵ� prev �� next ָ��ָ��ǰ�ڵ����һ���ڵ� move->next
                if(move->next!=NULL) 
				{
                    move->next->prior=prev;//�����ǰ�ڵ����һ���ڵ㲻Ϊ NULL������ prior ָ������Ϊ prev
                }
            }
            free(move);//�ͷ��ڴ�ռ䡣
            printf("ɾ���ɹ���\n");
            return;
        }
        prev=move;//�����ǰ��㲻��Ҫɾ���Ľڵ�
        move=move->next;//prev����Ϊ��ǰ�ڵ� move���� move����Ϊ��һ���ڵ� move->next
    }
    printf("δ�ҵ�ָ��data������\n");//���ǰ��Ķ�û�ҵ�����ô����û���ҵ�data�� 
    system("pause"); // ��ͣ����
    system("cls"); // ����
    menu();
} 

void findmiddle(DuLinkedList* L)//����ָ�뷨 
{
	if (L->head==NULL) 
	{
        printf("����Ϊ�գ�û���м�ֵ\n");
        return;
    }
    DuLNode* slow=L->head;//����һ����ָ�룬��ʼʱָ��head 
    DuLNode* fast=L->head;//����һ����ָ�룬��ʼʱҲָ��head 
    
    while (fast!= NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//��ָ��ÿ�ƶ�һ������ָ���ƶ����� 
        fast = fast->next->next;//�ȿ�ָ��ָ������β����ʱ����ָ��պ�ָ��������м�ֵ 
    }
    printf("������м�ֵ��: %d\n", slow->data);
    
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
    menu();
}

void insertlist(DuLinkedList* L,int data)//���������½����뵽��һ������β������һ������ͷ�� 
{
	printf("������Ҫ�����λ�ã�\n");
    int position;
    scanf("%d", &position);//��ȡ�����λ��
    DuLNode* newNode=(DuLNode*)malloc(sizeof(DuLNode));//�����ڴ���½�� 
    if(newNode==NULL)//�ж��ڴ��Ƿ����ɹ� 
	{
        printf("�ڴ����ʧ��\n");
        return;
    }
    newNode->data=data;//�½������ 
    newNode->next=NULL;//�½��nextָ��ָ��� 
    newNode->prior=NULL;//priorָ��ָ��� 

    if(position==1)//���뵽ͷ������� 
	{ 
        newNode->next=L->head;//�½��nextָ��ָ��ͷ��� 
        if(L->head != NULL)//����Ϊ�յ���� 
		{
            L->head->prior=newNode;//priorָ���½�� 
        }
        L->head=newNode;// ������ͷָ��Ϊ�½ڵ�
        printf("����ɹ���\n");
        return;
    }

    DuLNode* current=L->head; //����һ��ָ��currentָ������ͷ���
    for(int i=1;i<position-1&&current!=NULL;i++) //�ҵ�����λ�õ�ǰһ���ڵ�
	{
        current = current->next;//�ƶ�currentָ�뵽��һ���ڵ�
    }
    if(current==NULL) 
	{
        printf("λ�ó���������\n");
        free(newNode);//�ͷ��½����ڴ� 
        return;
    }

    newNode->next=current->next;//�½���nextָ��ָ��current����һ����� 
    newNode->prior=current;//�½���priorָ��ָ��current��� 
    if(current->next!=NULL) //���current����һ����㲻Ϊ��
	{
        current->next->prior=newNode;//��current����һ������priorָ��ָ���µ� 
    }
    current->next=newNode;//current��nextָ��ָ���½ڵ�
    printf("����ɹ���\n");
}

int judgecycle(DuLinkedList* L)//�жϳɻ� 
{
	if(L->head==NULL||L->head->next==NULL) 
	{
        return 0; //����Ϊ�ջ�ֻ��һ���ڵ㣬�����ܳɻ�
    }
    DuLNode* slow=L->head;
    DuLNode* fast= L->head;
    while (fast!=NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//��ָ��ÿ���ƶ�һ������ָ��ÿ���ƶ����� 
        fast = fast->next->next;   
        if(slow==fast) 
		{
			printf("����ɻ�\n"); 
            return 1; //�������ָ��ֵ��Ⱦ�������һ���ˣ�˵�������л�
        }
    }
    printf("�����ɻ�\n");
    return 0; // ��ָ�뵽������ĩβ��˵�������޻�
}
