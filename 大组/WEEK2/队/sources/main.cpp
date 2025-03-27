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
int main()
{
	Queue q;
	int data_type;
	printf("��ѡ�����Ԫ������:\n");
    printf("1.int\n");
    printf("2.float\n");
    printf("3.double\n");
    printf("4.char\n");
    printf("ѡ��: ");
    
    if(scanf("%d",&data_type)!=1||data_type< 1||data_type>4) 
	{
        printf("��Чѡ��!\n");
        return 1;
    }
    clear_input_buffer();
    size_t element_size;
    switch (data_type) 
	{
        case 1: element_size=sizeof(int); break;
        case 2: element_size=sizeof(float); break;
        case 3: element_size=sizeof(double); break;
        case 4: element_size=sizeof(char); break;
        default:return 1;
    }
	init_queue(&q,element_size);
    while(1)
	{
        menu();
        int choice;
        if(scanf("%d",&choice)!=1) 
		{
			printf("��Ч����!\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) 
		{
            case 1:handle_enqueue(&q,data_type);
            		break;
            case 2:handle_dequeue(&q,data_type);
            		break;
            case 3:
            {
                Destroy_queue(&q);
                printf("����������\n");
                break;
            }
            case 4: 
			{ 
                Clear_queue(&q);
                printf("���������\n");
                break;
            }
            case 5: 
			{ 
                print_queue_status(&q);
                break;
            }
            
            case 6: 
			{ 
                if (Isempty_queue(&q)) 
				{
                    printf("����Ϊ��!\n");
                } 
				else 
				{
                    switch(data_type) 
					{
                        case 1: {int value; Gethead_queue(&q, &value); printf("����Ԫ��: %d\n", value); break;}
                        case 2: {float value; Gethead_queue(&q, &value); printf("����Ԫ��: %f\n", value); break;}
                        case 3: {double value; Gethead_queue(&q, &value); printf("����Ԫ��: %lf\n", value); break;}
                        case 4: {char value; Gethead_queue(&q, &value); printf("����Ԫ��: %c\n", value); break;}
                    }
                }
                break;
            }
            case 7:
            {
            	printf("ллʹ�ã���ӭ�´����ã�\n");
				exit(0); 
			}
            default:
			{
                printf("��Чѡ��!\n");
                break;
            }
        }
    }
    return 0;
}
