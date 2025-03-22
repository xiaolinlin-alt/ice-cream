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

