void printlist(LinkedList*L)//打印链表 
{
	Node*move=L->head;
	while(move!=NULL)//一直移动到最后面,遍历 
	{
		//打印出订单信息 
		printf("data:");
		printf("%d\n",move->data); 		
		move=move->next;
	} 
	
	system("pause");//暂停程序
	system("cls");//清屏 	
}
