#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

void menu()//ѡ���ܽ��� 
{
	printf("****************************************\n"); 
	printf("***************��ӭ����*****************\n");
	printf("****************************************\n"); 
	printf("*      1.¼��                          *\n");
	printf("*      2.��ӡ                          *\n");
	printf("*      3.���                          *\n");
	printf("*      4.����                          *\n");
	printf("*      5.�޸�                          *\n");
	printf("*      6.ɾ��                          *\n");
	printf("*      7.�ҵ���������е�              *\n");
	printf("*      8.����                          *\n");
	printf("*      9.�жϵ������Ƿ�ɻ�            *\n");
	printf("*      10.�˳�����                     *\n");
	printf("*      ����1234                        *\n"); 
	printf("****************************************\n"); 
} 
typedef struct Node//���嵥����ڵ�ṹ
{
    int data;//����һ������ 
    struct Node* next;//����ָ����һ�����ݵ�ָ�� 
}Node;

typedef struct//���嵥����ṹ
{
    Node* head; //����ͷ��� 
}LinkedList; //���嵥�������� 


void initList(LinkedList* L) //��ʼ������
{
    L->head=NULL;//��ͷָ����Ϊ�� 
}

void inputdata(LinkedList*L) //����¼��data���� β�巨 
{
	Node*fresh=(Node*)malloc(sizeof(Node));//��̬�����ڴ棬�����½��fresh 
	if(fresh==NULL) 
	{
        printf("�ڴ����ʧ��\n");
        return;
    }
	fresh->next=NULL;//����ָ��� 
	
	printf("������data��");
    scanf("%d",&fresh->data);//������data
	if(L->head==NULL) 
	{
        L->head=fresh;//�������Ϊ��,���½ڵ�����Ϊͷ�ڵ�
    } 
	else
	{
        Node* move=L->head; // �ٶ���һ������ʼ��Ϊͷ��㣬β�巨 
        while(move->next!=NULL) // һֱ�ƶ��������
		{ 
            move=move->next; // ������,��������Ŀ���ǽ��Ǹ��������data�Ƶ�����β�� 
        }
        // ��data���뵽β��
        move->next =fresh;
    }
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
}

void printlist(LinkedList*L)//��ӡ���� 
{
	Node*move=L->head;
	while(move!=NULL)//һֱ�ƶ��������,���� 
	{
		//��ӡ��������Ϣ 
		printf("data:");
		printf("%d\n",move->data); 		
		move=move->next;
	} 
	
	system("pause");//��ͣ����
	system("cls");//���� 	
}

void clearlist(LinkedList* L)//������� 
{
    Node*p=L->head;//ָ��ǰ�ڵ�
    Node*q=NULL;//ָ����һ���ڵ�
    while(p!=NULL)//���������ͷŽڵ�
	{
        q=p->next;//��ȡ��һ���ڵ�
        free(p);//�ͷŵ�ǰ�ڵ�
        p = q;//�ƶ�����һ���ڵ�
    }
    // ����ͷ���
    L->head = NULL;
    
	system("pause");//��ͣ����
	system("cls");//���� 	
}
void searchOrder(LinkedList* L)//�����ѯ������Ϣ�ĺ���
{
	printf("������Ҫ���ҵ�data��");
	int data;
	scanf("%d",&data);
	Node*move=L->head;
	while(move!=NULL)//��ѯ��Ӧ��data
	{
		if(data==move->data)
		{
			printf("ȷʵ������ôһ��data"); 
			printf("%d\n",move->data); 
			return;//�ҵ���Ӧ�Ķ���ID�ͷ��أ�����break��������һ�� 
		}	
		move=move->next;
	} 
	printf("δ�ҵ�ָ��data������\n");
	system("pause");//��ͣ����
	system("cls");//���� 
} 

void modifylist(LinkedList* L)//�޸� 
{
    printf("������Ҫ�޸ĵ�data��");
    int oldData;
    scanf("%d", &oldData);//����Ҫ�޸ĵ�data�������Ϊolddata 
    Node* move=L->head;
    while (move != NULL) 
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
}

void deletelist(LinkedList* L)//ɾ��ָ��Ԫ��
{
    printf("������Ҫɾ����data��");
    int data;
    scanf("%d", &data);//ȷ��Ҫɾ��������data 
    Node* current=L->head;//����ָ�����ں���ǰ�� 
    Node* previous=NULL;
    
    if(current==NULL)//�������Ϊ�գ�ֱ�ӷ���
	{
        printf("����Ϊ�գ��޷�ɾ��\n");
        return;
    }
    if (current!=NULL&&current->data==data)//���Ҫɾ���Ľ����ͷ���
	{
        L->head=current->next; //��ͷָ��ָ����һ����� 
        free(current); // �ͷ�ͷ����ڴ棬ɾ��������Ҫfree 
        printf("ɾ���ɹ���\n");
        return;
    }
    while(current!=NULL&&current->data!=data)//��������Ѱ��Ҫɾ����data 
	{
        previous=current;
        current=current->next;
    }
    if(current==NULL)//���û���ҵ�Ҫɾ���Ľڵ�
	{
        printf("δ�ҵ�data������\n");
        return;
    }
    // �ҵ��˵���� 
    previous->next=current->next; // ��ǰһ������nextָ��ǰ�ڵ����һ���ڵ�head 
    free(current);//�ͷŵ�ǰ�ڵ��ڴ�
    printf("ɾ���ɹ���\n");
}

void findmiddle(LinkedList* L)//����ָ�뷨 
{
    if (L->head==NULL) 
	{
        printf("����Ϊ�գ�û���м�ֵ\n");
        return;
    }
    Node* slow=L->head;//����һ����ָ�룬��ʼʱָ��head 
    Node* fast=L->head;//����һ����ָ�룬��ʼʱҲָ��head 
    
    while (fast!= NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//��ָ��ÿ�ƶ�һ������ָ���ƶ����� 
        fast = fast->next->next;//�ȿ�ָ��ָ������β����ʱ����ָ��պ�ָ��������м�ֵ 
    }
    printf("������м�ֵ��: %d\n", slow->data);
    
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
}

void insertlist(LinkedList* L, int data)//���������½����뵽��һ������β������һ������ͷ�� 
{
    Node* fresh=(Node*)malloc(sizeof(Node)); //��̬�����ڴ棬�����½��fresh
    if (fresh==NULL) 
	{
        printf("�ڴ����ʧ��\n");
        return;
    }
    fresh->data=data;//�����½ڵ������
    fresh->next=NULL; //����ָ���
    if(L->head==NULL) 
	{
        L->head=fresh;//�������Ϊ��,���½ڵ�����Ϊͷ�ڵ�
    } else 
	{
        Node* move=L->head;//����һ��ָ�룬��ʼ��Ϊͷ���
        while(move->next!=NULL) //һֱ�ƶ��������
		{ 
            move=move->next; // ������,��������
        }  
        move->next = fresh;//���½ڵ���뵽β��
    }
}

int judgecycle(LinkedList* L)//�жϳɻ� 
{
    if(L->head==NULL||L->head->next==NULL) 
	{
        return 0; //����Ϊ�ջ�ֻ��һ���ڵ㣬�����ܳɻ�
    }
    Node* slow=L->head;
    Node* fast= L->head;
    while (fast!=NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//��ָ��ÿ���ƶ�һ������ָ��ÿ���ƶ����� 
        fast = fast->next->next;   
        if(slow==fast) 
		{
            return 1; //�������ָ��ֵ��Ⱦ�������һ���ˣ�˵�������л�
        }
    }
    return 0; // ��ָ�뵽������ĩβ��˵�������޻�
}

int main() 
{

    system("color F0"); //���ô�����ɫ 
	char password[20];//����һ���ַ�����password�����ڴ洢�û����������
	LinkedList L;
    initList(&L);   
    menu();//���ô�ӡ�˵��ĺ��� 
	printf("�������������룺\n");
	scanf("%s",password);

    system("pause");//ʹ������ִͣ��
	system("cls");
	
    if(strcmp(password,"1234")==0)
    {
    	printf("��ӭ���룡����\n"); 
   		menu();
   		while (1) // �������ܽ������� 
		{ 
        	int chose;
        	scanf("%d", &chose);
       		switch (chose) 
			{
				case 1:inputdata(&L);//¼�� 
						break;
       	 	    case 2:printlist(&L);//��ӡ 
						break;
           		case 3:clearlist(&L); //��� 
						break; 
				case 4:searchOrder(&L);//���� 
						break; 
				case 5:modifylist(&L);//�޸� 
						break;
				case 6:deletelist(&L);//ɾ�� 
						break; 
				case 7:findmiddle(&L);//�ҵ���������е�
						break;
				case 8:insertlist(&L,77);//��������77 
						break; 
				case 9:judgecycle(&L);//�жϵ������Ƿ�ɻ� 
						break; 
            	case 10: printf("�˳�����л����ʹ�ã���ӭ�´�ʹ��\n"); exit(0); // �˳�ϵͳ 
            	default:printf("���������������������룡����\n"); 
						system("pause"); system("cls"); // ��ͣ�����û��鿴������� ,���Ž����������� 
			}
  		 }
  	}
	else if(strcmp(password, "1234")!= 0)
    {
   		printf("�����������������\n");
    }
    return 0;
}

