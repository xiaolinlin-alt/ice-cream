void modifylist(LinkedList* L)//�޸� 
{
    printf("������Ҫ�޸ĵ�data��");
    int oldData;
    scanf("%d", &oldData);//����Ҫ�޸ĵ�data�������Ϊolddata 
    Node* move=L->head;
    while (move != NULL) 
	{
        if(move->data==oldData)
		{
            printf("�������µ�data��");
            int newData;
            scanf("%d", &newData);
            move->data=newData;
            printf("�޸ĳɹ����µ�dataΪ��%d\n", newData);
            return;
        }
        move = move->next;
    }
    printf("δ�ҵ�ָ��data������\n");
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
}
