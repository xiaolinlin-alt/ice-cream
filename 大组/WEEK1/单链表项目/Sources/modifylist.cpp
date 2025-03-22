void modifylist(LinkedList* L)//修改 
{
    printf("请输入要修改的data：");
    int oldData;
    scanf("%d", &oldData);//输入要修改的data，这里称为olddata 
    Node* move=L->head;
    while (move != NULL) 
	{
        if(move->data==oldData)
		{
            printf("请输入新的data：");
            int newData;
            scanf("%d", &newData);
            move->data=newData;
            printf("修改成功！新的data为：%d\n", newData);
            return;
        }
        move = move->next;
    }
    printf("未找到指定data！！！\n");
    system("pause"); // 暂停程序
    system("cls"); // 清屏 
}
