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
	printf("*      7.�ҵ�˫������е�              *\n");
	printf("*      8.����                          *\n");
	printf("*      9.�ж�˫�����Ƿ�ɻ�            *\n");
	printf("*      10.�˳�����                     *\n");
	printf("*      ����1234                        *\n"); 
	printf("****************************************\n"); 
}  

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
		exit(1);
	}
    L->head->next=NULL;//�����ָ����Ϊ�� 
	L->head->prior=NULL;//��ǰ��ָ����Ϊ�� 
}

void inputdata(DuLinkedList*L)//����¼��data���� β�巨 
{
	int n,data;
    printf("������Ҫ�����Ԫ�صĸ�����");
    if(scanf("%d",&n)!=1||n<= 0) 
	{
        printf("�������������һ��������\n");
        return;
    }
    // �ҵ������β��
    DuLNode* tail=L->head;
    while(tail->next!=NULL) 
	{
        tail=tail->next;
    }
    for(int i=0;i<n;i++) 
	{
        printf("�������%d��Ԫ�أ�",i + 1);
        if(scanf("%d", &data)!=1) 
		{
            printf("�������������һ������\n");
            while(getchar()!='\n'); // ������뻺����
            continue;
        }
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
}

void searchlist(DuLinkedList* L)
{
	printf("������Ҫ���ҵ�data��");
	int data;
	if(scanf("%d", &data)!=1) 
	{
        printf("�������������һ������\n");
        return;
    }
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
}

void modifylist(DuLinkedList* L)//�޸� 
{
    printf("������Ҫ�޸ĵ�data��");
    int oldData;
    if(scanf("%d",&oldData)!=1) //����Ҫ�޸ĵ�data�������Ϊolddata 
	{
        printf("������Ч��������һ������\n");
        return;
    }
    DuLNode* move=L->head;
    while(move!=NULL) 
	{
        if(move->data==oldData)
		{
            printf("�������µ�data��");
            int newData;
            if(scanf("%d", &newData)!=1) 
			{
                printf("�������������һ������\n");
                return;
            }
            move->data=newData;
            printf("�޸ĳɹ����µ�dataΪ��%d\n", newData);
            return;
        }
        move = move->next;
    }
    printf("δ�ҵ�ָ��data������\n");
    system("pause"); // ��ͣ����
}

void deletelist(DuLinkedList* L)//ɾ��ָ��Ԫ��
{
	printf("������Ҫɾ����data:\n");
    int data;
    if(scanf("%d", &data)!= 1) 
	{
        printf("�������������һ������\n");
        return;
    }

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
} 

void findmiddle(DuLinkedList* L)//����ָ�뷨 
{
	if(L->head==NULL||L->head->next==NULL) 
	{
        printf("����Ϊ�ջ�ֻ��һ���ڵ㣬û���м�ֵ\n");
        return;
    }
    DuLNode* slow=L->head->next;//��ָ��ָ���һ��ʵ�����ݽڵ�
    DuLNode* fast=L->head->next;//��ָ��ָ���һ��ʵ�����ݽڵ�

    while(fast!=NULL&&fast->next!=NULL) 
	{
        slow=slow->next;         // ��ָ���ƶ�һ��
        fast=fast->next->next;   // ��ָ���ƶ�����
    }

    printf("������м�ֵ��: %d\n", slow->data);
    system("pause"); // ��ͣ����
}

void insertlist(DuLinkedList* L)//���������½����뵽��һ������β������һ������ͷ�� 
{
    int position,data;
    printf("������Ҫ�����λ�ã�\n");
    if(scanf("%d",&position)!=1||position<=0) 
	{
        printf("�������������һ��������\n");
        return;
    }
    printf("������Ҫ��������ݣ�\n");
    if(scanf("%d",&data)!=1) 
	{
        printf("�������������һ������\n");
        return;
    }
    DuLNode* newNode=(DuLNode*)malloc(sizeof(DuLNode)); // �����ڴ���½ڵ�
    if(newNode==NULL) 
	{
        printf("�ڴ����ʧ��\n");
        return;
    }
    newNode->data=data; // �½ڵ�����
    newNode->next=NULL; // �½ڵ� next ָ��ָ���
    newNode->prior=NULL; // �½ڵ� prior ָ��ָ���

    // ���뵽ͷ�������
    if(position == 1) 
	{
        newNode->next=L->head; // �½ڵ�� next ָ��ԭͷ�ڵ�
        if(L->head!=NULL) 
		{
            L->head->prior=newNode; // ԭͷ�ڵ�� prior ָ���½ڵ�
        }
        L->head=newNode; // ����ͷ�ڵ�Ϊ�½ڵ�
        printf("����ɹ���\n");
        return;
    }

    // ���뵽����λ��
    DuLNode* current=L->head; // ����һ��ָ�� current ָ������ͷ�ڵ�
    for(int i=1;i<position-1&&current!=NULL;i++) 
	{
        current=current->next; // �ƶ� current ָ�뵽����λ�õ�ǰһ���ڵ�
    }
    if(current==NULL) 
	{
        printf("λ�ó���������\n");
        free(newNode); // �ͷ��½ڵ���ڴ�
        return;
    }
    // �����½ڵ�
    newNode->next=current->next; // �½ڵ�� next ָ�� current ����һ���ڵ�
    newNode->prior=current; // �½ڵ�� prior ָ�� current
    if(current->next!=NULL) 
	{
        current->next->prior=newNode; // current ����һ���ڵ�� prior ָ���½ڵ�
    }
    current->next = newNode; // current �� next ָ���½ڵ�
    printf("����ɹ���\n");
}

int judgecycle(DuLinkedList* L)//�жϳɻ� 
{
	if(L->head==NULL||L->head->next==NULL) 
	{
		printf("����Ϊ�ջ�ֻ��һ���ڵ㣬�����ܳɻ�\n");
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

int main() 
{

    system("color F0"); //���ô�����ɫ 
	char password[20];//����һ���ַ�����password�����ڴ洢�û����������
	DuLinkedList L;
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
           		case 3:clearlist(&L);// ��� 
						break; 
				case 4:searchlist(&L);//���� 
						break; 
				case 5:modifylist(&L);//�޸� 
						break;
				case 6:deletelist(&L);//ɾ�� 
						break; 
				case 7:findmiddle(&L);//�ҵ�˫������е�
						break;
				case 8:insertlist(&L);//��������
						break; 
				case 9:judgecycle(&L);//�ж�˫�����Ƿ�ɻ� 
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
    printf("��ѡ����\n");
    return 0;
}



