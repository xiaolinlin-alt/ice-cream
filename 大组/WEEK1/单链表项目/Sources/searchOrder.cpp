void searchOrder(LinkedList* L)//�����ѯ������Ϣ�ĺ���
{
	printf("������Ҫ���ҵ�data��");
	int data;
	scanf("%d",&data);
	Node*move=L->head;
	while(move!=NULL)//��ѯ��Ӧ��data
	{
		if(data==move->data)
		{
			printf("ȷʵ������ôһ��data"); 
			printf("%d\n",move->data); 
			return;//�ҵ���Ӧ�Ķ���ID�ͷ��أ�����break��������һ�� 
		}	
		move=move->next;
	} 
	printf("δ�ҵ�ָ��data������\n");
	system("pause");//��ͣ����
	system("cls");//���� 
} 

