void printlist(LinkedList*L)//��ӡ���� 
{
	Node*move=L->head;
	while(move!=NULL)//һֱ�ƶ��������,���� 
	{
		//��ӡ��������Ϣ 
		printf("data:");
		printf("%d\n",move->data); 		
		move=move->next;
	} 
	
	system("pause");//��ͣ����
	system("cls");//���� 	
}
