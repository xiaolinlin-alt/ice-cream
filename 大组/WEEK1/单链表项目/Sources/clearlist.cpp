void clearlist(LinkedList* L)//������� 
{
    Node*p=L->head;//ָ��ǰ�ڵ�
    Node*q=NULL;//ָ����һ���ڵ�
    while(p!=NULL)//���������ͷŽڵ�
	{
        q=p->next;//��ȡ��һ���ڵ�
        free(p);//�ͷŵ�ǰ�ڵ�
        p = q;//�ƶ�����һ���ڵ�
    }
    // ����ͷ���
    L->head = NULL;
    
	system("pause");//��ͣ����
	system("cls");//���� 	
}
