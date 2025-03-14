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
