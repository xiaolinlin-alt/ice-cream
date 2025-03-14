void deletelist(LinkedList* L)//删除指定元素
{
    printf("请输入要删除的data：");
    int data;
    scanf("%d", &data);//确定要删除的数据data 
    Node* current=L->head;//创建指针现在和先前的 
    Node* previous=NULL;
    
    if(current==NULL)//如果链表为空，直接返回
	{
        printf("链表为空，无法删除\n");
        return;
    }
    if (current!=NULL&&current->data==data)//如果要删除的结点是头结点
	{
        L->head=current->next; //将头指针指向下一个结点 
        free(current); // 释放头结点内存，删除东西了要free 
        printf("删除成功！\n");
        return;
    }
    while(current!=NULL&&current->data!=data)//遍历链表，寻找要删除的data 
	{
        previous=current;
        current=current->next;
    }
    if(current==NULL)//如果没有找到要删除的节点
	{
        printf("未找到data！！！\n");
        return;
    }
    // 找到了的情况 
    previous->next=current->next; // 将前一个结点的next指向当前节点的下一个节点head 
    free(current);//释放当前节点内存
    printf("删除成功！\n");
}
