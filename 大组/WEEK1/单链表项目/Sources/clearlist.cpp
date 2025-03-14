void clearlist(LinkedList* L)//清空链表 
{
    Node*p=L->head;//指向当前节点
    Node*q=NULL;//指向下一个节点
    while(p!=NULL)//遍历链表并释放节点
	{
        q=p->next;//获取下一个节点
        free(p);//释放当前节点
        p = q;//移动到下一个节点
    }
    // 重置头结点
    L->head = NULL;
    
	system("pause");//暂停程序
	system("cls");//清屏 	
}
