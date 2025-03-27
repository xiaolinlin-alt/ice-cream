#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<windows.h>

typedef struct QueueNode//������нڵ�ṹ 
{
	void* data;//���巺������ָ�� 
	struct QueueNode*next;	//����ָ����һ���ڵ��ָ�� 
}QueueNode;

typedef struct//������нṹ 
{
	QueueNode* head;//�����ͷָ�� 
	QueueNode* tail;//�����βָ�� 
	size_t element_size;//����ÿ��Ԫ�ش�С 
	size_t length;//��ǰ���г��� 
}Queue;

void menu();//�˵� 
void init_queue(Queue* q,size_t element_size);//��ʼ���� 
void Destroy_queue(Queue* q);////���ٶ� 
bool En_queue(Queue*q,void* data);//��� 
bool De_queue(Queue* q,void* data);//���� 
void Clear_queue(Queue* q);//��ն� 
bool Gethead_queue(Queue* q,void* data);//�õ�����Ԫ�� 
bool Isfull_queue(Queue* q);//�ж϶��Ƿ����� 
bool Isempty_queue(Queue* q);//�ж϶��Ƿ�Ϊ�� 
size_t Length_queue(Queue* q);//��ӳ��� 
void print_queue_status(Queue* q);//��ӡ����״̬ 
void clear_input_buffer();//������뻺�� 
bool get_input(void* value,char* format,char* data_type);//�õ�������������� 
void handle_enqueue(Queue* q,int data_type);//������� 
void handle_dequeue(Queue* q,int data_type);//������� 


void menu()//��ӡ�˵� 
{
	printf("-------------------------\n");
	printf("---------��ӭ����--------\n");
	printf("---------1.���----------\n");
	printf("---------2.����----------\n");
	printf("---------3.���ٶ�--------\n");
	printf("---------4.��ն�--------\n");
	printf("---------5.�鿴����״̬--\n");
	printf("---------6.�ö���Ԫ��----\n");
	printf("---------7.�˳�ϵͳ------\n");
	printf("��ѡ�����:");
}

void init_queue(Queue* q,size_t element_size)//��ʼ���� 
{
	q->head=q->tail=NULL;//����Ϊ�յı�־����head��tail��Ϊ�� 
	q->element_size=element_size;//���Ͳ������� 
	q->length=0;//����ֱ�Ӽ�¼���г��� 
}
//����һ�����Ͷ�����Ҫ�����ͷ����ж�̬������ڴ棬�����Ҫ������ 
void Destroy_queue(Queue* q)//���ٶ� 
{
	QueueNode* current=q->head;//����һ��ָ�����������ӣ���ͷ�ڵ㿪ʼ 
	while(current!=NULL)//��ָ�벻Ϊ�գ�����û����β��ʱ�� 
	{
		QueueNode* temp=current;//���浱ǰ�ڵ�ָ�� 
		current=current->next;//�ƶ�����һ���ڵ� 
		free(temp->data);//�ͷŽڵ��ڵ��������ڴ� 
		free(temp);	///�ͷŽڵ㱾����ڴ� 
	} 
	q->head=q->tail=NULL;//���ö���״̬�����������Ѿ����ٵĶ� 
	q->length=0;
}

bool En_queue(Queue* q,void* data)//Ԫ����� 
{
	QueueNode* new_node=(QueueNode*)malloc(sizeof(QueueNode));//Ϊ�½ڵ�����ڴ� 
	if(new_node==NULL)
	{
		return false;//�ڴ����ʧ�ܵ����	
	} 
	new_node->data=malloc(q->element_size);//���������ڴ� 
	if(new_node->data==NULL)//�������ʧ�ܵĻ���Ӧ�������ͷ��ڴ� 
	{
		free(new_node);//�ͷ��ڴ� 
		return false;
	}
	memcpy(new_node->data,data,q->element_size);//�����ݿ������½ڵ��data���� 
	new_node->next=NULL;//�ǴӶ�β��ģ�Ӧ�ñ�֤��β��nextָ��Ϊ�� 
	if(q->tail==NULL)//�����������ǿն��У���ô����ͷ��β��ָ�����Ψһ���½ڵ� 
	{
		q->head=q->tail=new_node;
	}
	else//���������в��ǿն��У���ô�ͼӵ���β�ϣ�����½ڵ��Ϊ�µĶ�β 
	{
		q->tail->next=new_node;//ԭ��β��nextָ���½ڵ� 
		q->tail=new_node;//���¶�βָ��Ϊ�½ڵ� 
	}
	q->length++;//���¶��г��� 
	return true;
}

bool De_queue(Queue* q,void*data)//Ԫ�س��� 
{
	if(q->head==NULL)//�������Ƿ�Ϊ�� 
	{
		return false;;
	}
	QueueNode* temp=q->head;//����һ����ʱָ�룬ָ����е�ͷ�ڵ� 
	if(data!=NULL)//���data��Ϊ�գ�������������������������ͷŵ� 
	{
		memcpy(data,temp->data,q->element_size);
	}
	q->head=q->head->next;//q->head�ƶ�����һ���ڵ� 
	if(q->head==NULL)//����ƶ����ͷָ��Ϊ�գ���˵��û��Ԫ���ˣ����ʱ��ҲӦ������βָ��Ϊ�� 
	{
		q->tail=NULL;
	}
	free(temp->data);//�ͷű�ɾ���ڵ�������ڴ� 
	free(temp);//�ͷŽڵ㱾����ڴ� 
	q->length--;//���г��ȼ�1 
	return true;
}

void Clear_queue(Queue* q)//��ն��� 
{
	while(De_queue(q,NULL))//ѭ������������Ӻ���ֱ������Ϊ�� 
	{
	}
}

bool Gethead_queue(Queue*q,void* data)//�õ�����Ԫ�� 
{
	if(q->head==NULL||data==NULL)//�������Ƿ�Ϊ�� 
	{
		return false;
	}
	//������в�Ϊ�գ���ͷ�ڵ�����ݸ��Ƶ�dataָ����ڴ��� 
	memcpy(data,q->head->data,q->element_size);
	return true;
}

bool Isfull_queue(Queue* q)//�ж϶����Ƿ����� 
{
	QueueNode* test_node=(QueueNode*)malloc(sizeof(QueueNode));//�ڴ���� 
	if(test_node==NULL)
	{
		return true;//˵�������Ѿ����� 
	}
	test_node->data=malloc(q->element_size);
	bool is_full=(test_node->data==NULL);//�ж� 
	free(test_node);//�ͷŲ��Խڵ��ڴ� 
	return is_full;//�������ֵ 
}

bool Isempty_queue(Queue* q)//�ж϶����Ƿ�Ϊ�� 
{
	return q->length==0;//�������Ϊ�գ�����true�������Ϊ�գ�����false 
}

size_t Length_queue(Queue* q)//���г��� 
{
	return q->length;//���ض��г��� 
}

void print_queue_status(Queue* q)//��ӡ����״̬ 
{
    printf("����״̬\n");
    printf("����: %zu\n", q->length);//��ӡ���г��� 
    printf("����: %s\n",Isfull_queue(q)?"����":"δ��");//�ж϶������� 
    printf("״̬: %s\n",Isempty_queue(q)?"��":"�ǿ�");//�ж϶����Ƿ�Ϊ�� 
}

void clear_input_buffer()//������뻺����
{
    while(getchar()!='\n');
}

bool get_input(void* value,const char* format,const char* type_name) //������������ 
{
    while(1) //ֱ��������Ч����Ϊֹ 
	{
        printf("������%sֵ: ",type_name); //��ʾ����ָ������������ 
        if(scanf(format,value)==1) 
		{
            clear_input_buffer();//������� 
            return true;
        } 
		else 
		{
            printf("������Ч�����������룡\n");
            clear_input_buffer();
        }
    }
}

// ������Ӳ���
void handle_enqueue(Queue* q, int data_type) 
{
    if (q == NULL) return;//�������ָ��ΪNULL��ֱ�ӷ��� 
    if (Isfull_queue(q)) //�������Ƿ����� 
	{
        printf("�����������޷����!\n");
        return;
    }
    bool success = false;//���ڼ�¼��Ӳ����Ƿ�ɹ� 
    switch (data_type) //���ݲ�ͬ��data_type������ͬ�Ĳ��� 
	{
        case 1: 
		{
            int value;//���� 
            if(get_input(&value, "%d", "����������ֵ")) 
			{
                success=En_queue(q, &value);
                printf("���%s: %d\n",success?"�ɹ�":"ʧ��",value);
            }
            break;
        }
        case 2:
		{
            float value;//������ 
            if (get_input(&value,"%f","�����븡����ֵ")) 
			{
                success=En_queue(q,&value);
                printf("���%s: %f\n",success?"�ɹ�":"ʧ��",value);
            }
            break;
        }
        case 3: 
		{
            double value;//˫���ȸ����� 
            if(get_input(&value,"%lf", "������˫���ȸ�����ֵ")) 
			{
                success=En_queue(q,&value);
                printf("���%s: %lf\n",success?"�ɹ�":"ʧ��",value);
            }
            break;
        }
        case 4: 
		{
            char value;//�ֽ��� 
            if(get_input(&value, " %c", "�������ַ�")) 
			{
                success=En_queue(q, &value);
                printf("���%s: %c\n",success?"�ɹ�":"ʧ��",value);
            }
            break;
        }
    }
}

// ������Ӳ���
void handle_dequeue(Queue* q,int data_type) 
{
    if(q==NULL) return;
    if(Isempty_queue(q)) 
	{
        printf("����Ϊ�գ��޷�����!\n");
        return;
    }
    switch (data_type) 
	{
        case 1: 
		{
            int value;
            if(De_queue(q, &value)) 
			{
                printf("����Ԫ��: %d\n",value);
            }
            break;
        }
        case 2: 
		{
            float value;
            if(De_queue(q, &value)) 
			{
                printf("����Ԫ��: %f\n",value);
            }
            break;
        }
        case 3: 
		{
            double value;
            if(De_queue(q,&value)) 
			{
                printf("����Ԫ��: %lf\n", value);
            }
            break;
        }
        case 4: 
		{
            char value;
            if(De_queue(q, &value)) 
			{
                printf("����Ԫ��: %c\n",value);
            }
            break;
        }
    }
}
