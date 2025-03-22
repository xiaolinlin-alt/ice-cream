void searchOrder(LinkedList* L)//定义查询订单信息的函数
{
	printf("请输入要查找的data：");
	int data;
	scanf("%d",&data);
	Node*move=L->head;
	while(move!=NULL)//查询对应的data
	{
		if(data==move->data)
		{
			printf("确实存在这么一个data"); 
			printf("%d\n",move->data); 
			return;//找到对应的订单ID就返回，不用break，好走下一步 
		}	
		move=move->next;
	} 
	printf("未找到指定data！！！\n");
	system("pause");//暂停程序
	system("cls");//清屏 
} 

