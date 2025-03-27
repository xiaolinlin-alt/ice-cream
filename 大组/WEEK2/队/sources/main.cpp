#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<windows.h>

typedef struct QueueNode//定义队列节点结构 
{
	void* data;//定义泛型数据指针 
	struct QueueNode*next;	//定义指向下一个节点的指针 
}QueueNode;

typedef struct//定义队列结构 
{
	QueueNode* head;//定义队头指针 
	QueueNode* tail;//定义队尾指针 
	size_t element_size;//定义每个元素大小 
	size_t length;//当前队列长度 
}Queue;

void menu();//菜单 
void init_queue(Queue* q,size_t element_size);//初始化队 
void Destroy_queue(Queue* q);////销毁队 
bool En_queue(Queue*q,void* data);//入队 
bool De_queue(Queue* q,void* data);//出队 
void Clear_queue(Queue* q);//清空队 
bool Gethead_queue(Queue* q,void* data);//得到队首元素 
bool Isfull_queue(Queue* q);//判断队是否满了 
bool Isempty_queue(Queue* q);//判断队是否为空 
size_t Length_queue(Queue* q);//求队长度 
void print_queue_status(Queue* q);//打印队列状态 
void clear_input_buffer();//清空输入缓存 
bool get_input(void* value,char* format,char* data_type);//得到输入的数据类型 
void handle_enqueue(Queue* q,int data_type);//处理入队 
void handle_dequeue(Queue* q,int data_type);//处理出队 
int main()
{
	Queue q;
	int data_type;
	printf("请选择队列元素类型:\n");
    printf("1.int\n");
    printf("2.float\n");
    printf("3.double\n");
    printf("4.char\n");
    printf("选择: ");
    
    if(scanf("%d",&data_type)!=1||data_type< 1||data_type>4) 
	{
        printf("无效选择!\n");
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
			printf("无效输入!\n");
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
                printf("队列已销毁\n");
                break;
            }
            case 4: 
			{ 
                Clear_queue(&q);
                printf("队列已清空\n");
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
                    printf("队列为空!\n");
                } 
				else 
				{
                    switch(data_type) 
					{
                        case 1: {int value; Gethead_queue(&q, &value); printf("队首元素: %d\n", value); break;}
                        case 2: {float value; Gethead_queue(&q, &value); printf("队首元素: %f\n", value); break;}
                        case 3: {double value; Gethead_queue(&q, &value); printf("队首元素: %lf\n", value); break;}
                        case 4: {char value; Gethead_queue(&q, &value); printf("队首元素: %c\n", value); break;}
                    }
                }
                break;
            }
            case 7:
            {
            	printf("谢谢使用，欢迎下次再用！\n");
				exit(0); 
			}
            default:
			{
                printf("无效选项!\n");
                break;
            }
        }
    }
    return 0;
}
