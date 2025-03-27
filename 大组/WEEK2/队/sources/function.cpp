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


void menu()//打印菜单 
{
	printf("-------------------------\n");
	printf("---------欢迎进入--------\n");
	printf("---------1.入队----------\n");
	printf("---------2.出队----------\n");
	printf("---------3.销毁队--------\n");
	printf("---------4.清空队--------\n");
	printf("---------5.查看队列状态--\n");
	printf("---------6.得队首元素----\n");
	printf("---------7.退出系统------\n");
	printf("请选择操作:");
}

void init_queue(Queue* q,size_t element_size)//初始化队 
{
	q->head=q->tail=NULL;//队列为空的标志就是head和tail都为空 
	q->element_size=element_size;//泛型操作基础 
	q->length=0;//用于直接记录队列长度 
}
//销毁一个泛型队列需要彻底释放所有动态分配的内存，因此需要遍历队 
void Destroy_queue(Queue* q)//销毁队 
{
	QueueNode* current=q->head;//定义一个指针用来遍历队，从头节点开始 
	while(current!=NULL)//当指针不为空，就是没到队尾的时候 
	{
		QueueNode* temp=current;//保存当前节点指针 
		current=current->next;//移动到下一个节点 
		free(temp->data);//释放节点内迭代数据内存 
		free(temp);	///释放节点本身的内存 
	} 
	q->head=q->tail=NULL;//重置队列状态，避免误用已经销毁的队 
	q->length=0;
}

bool En_queue(Queue* q,void* data)//元素入队 
{
	QueueNode* new_node=(QueueNode*)malloc(sizeof(QueueNode));//为新节点分配内存 
	if(new_node==NULL)
	{
		return false;//内存分配失败的情况	
	} 
	new_node->data=malloc(q->element_size);//分配数据内存 
	if(new_node->data==NULL)//如果分配失败的话，应该立马释放内存 
	{
		free(new_node);//释放内存 
		return false;
	}
	memcpy(new_node->data,data,q->element_size);//将数据拷贝到新节点的data区域 
	new_node->next=NULL;//是从队尾入的，应该保证队尾的next指针为空 
	if(q->tail==NULL)//如果这个队列是空队列，那么它的头和尾都指向这个唯一的新节点 
	{
		q->head=q->tail=new_node;
	}
	else//如果这个队列不是空队列，那么就加到队尾上，这个新节点成为新的队尾 
	{
		q->tail->next=new_node;//原队尾的next指向新节点 
		q->tail=new_node;//更新队尾指针为新节点 
	}
	q->length++;//更新队列长度 
	return true;
}

bool De_queue(Queue* q,void*data)//元素出队 
{
	if(q->head==NULL)//检查队列是否为空 
	{
		return false;;
	}
	QueueNode* temp=q->head;//创建一个临时指针，指向队列的头节点 
	if(data!=NULL)//如果data不为空，就这样子做，方便后续把它释放掉 
	{
		memcpy(data,temp->data,q->element_size);
	}
	q->head=q->head->next;//q->head移动到下一个节点 
	if(q->head==NULL)//如果移动后的头指针为空，就说明没有元素了，这个时候也应该设置尾指针为空 
	{
		q->tail=NULL;
	}
	free(temp->data);//释放被删除节点的数据内存 
	free(temp);//释放节点本身的内存 
	q->length--;//队列长度减1 
	return true;
}

void Clear_queue(Queue* q)//清空队列 
{
	while(De_queue(q,NULL))//循环调用这个出队函数直到队列为空 
	{
	}
}

bool Gethead_queue(Queue*q,void* data)//得到队首元素 
{
	if(q->head==NULL||data==NULL)//检查队列是否为空 
	{
		return false;
	}
	//如果队列不为空，将头节点的数据复制到data指向的内存中 
	memcpy(data,q->head->data,q->element_size);
	return true;
}

bool Isfull_queue(Queue* q)//判断队列是否满了 
{
	QueueNode* test_node=(QueueNode*)malloc(sizeof(QueueNode));//内存分配 
	if(test_node==NULL)
	{
		return true;//说明队列已经满了 
	}
	test_node->data=malloc(q->element_size);
	bool is_full=(test_node->data==NULL);//判断 
	free(test_node);//释放测试节点内存 
	return is_full;//返回真假值 
}

bool Isempty_queue(Queue* q)//判断队列是否为空 
{
	return q->length==0;//如果队列为空，返回true，如果不为空，返回false 
}

size_t Length_queue(Queue* q)//队列长度 
{
	return q->length;//返回队列长度 
}

void print_queue_status(Queue* q)//打印队列状态 
{
    printf("队列状态\n");
    printf("长度: %zu\n", q->length);//打印队列长度 
    printf("容量: %s\n",Isfull_queue(q)?"已满":"未满");//判断队列容量 
    printf("状态: %s\n",Isempty_queue(q)?"空":"非空");//判断队列是否为空 
}

void clear_input_buffer()//清空输入缓冲区
{
    while(getchar()!='\n');
}

bool get_input(void* value,const char* format,const char* type_name) //输入数据类型 
{
    while(1) //直到输入有效数据为止 
	{
        printf("请输入%s值: ",type_name); //提示输入指定的数据类型 
        if(scanf(format,value)==1) 
		{
            clear_input_buffer();//清除缓存 
            return true;
        } 
		else 
		{
            printf("输入无效，请重新输入！\n");
            clear_input_buffer();
        }
    }
}

// 处理入队操作
void handle_enqueue(Queue* q, int data_type) 
{
    if (q == NULL) return;//如果队列指针为NULL，直接返回 
    if (Isfull_queue(q)) //检查队列是否已满 
	{
        printf("队列已满，无法入队!\n");
        return;
    }
    bool success = false;//用于记录入队操作是否成功 
    switch (data_type) //根据不同的data_type做出不同的操作 
	{
        case 1: 
		{
            int value;//整型 
            if(get_input(&value, "%d", "请输入整数值")) 
			{
                success=En_queue(q, &value);
                printf("入队%s: %d\n",success?"成功":"失败",value);
            }
            break;
        }
        case 2:
		{
            float value;//浮点型 
            if (get_input(&value,"%f","请输入浮点数值")) 
			{
                success=En_queue(q,&value);
                printf("入队%s: %f\n",success?"成功":"失败",value);
            }
            break;
        }
        case 3: 
		{
            double value;//双精度浮点型 
            if(get_input(&value,"%lf", "请输入双精度浮点数值")) 
			{
                success=En_queue(q,&value);
                printf("入队%s: %lf\n",success?"成功":"失败",value);
            }
            break;
        }
        case 4: 
		{
            char value;//字节型 
            if(get_input(&value, " %c", "请输入字符")) 
			{
                success=En_queue(q, &value);
                printf("入队%s: %c\n",success?"成功":"失败",value);
            }
            break;
        }
    }
}

// 处理出队操作
void handle_dequeue(Queue* q,int data_type) 
{
    if(q==NULL) return;
    if(Isempty_queue(q)) 
	{
        printf("队列为空，无法出队!\n");
        return;
    }
    switch (data_type) 
	{
        case 1: 
		{
            int value;
            if(De_queue(q, &value)) 
			{
                printf("出队元素: %d\n",value);
            }
            break;
        }
        case 2: 
		{
            float value;
            if(De_queue(q, &value)) 
			{
                printf("出队元素: %f\n",value);
            }
            break;
        }
        case 3: 
		{
            double value;
            if(De_queue(q,&value)) 
			{
                printf("出队元素: %lf\n", value);
            }
            break;
        }
        case 4: 
		{
            char value;
            if(De_queue(q, &value)) 
			{
                printf("出队元素: %c\n",value);
            }
            break;
        }
    }
}
