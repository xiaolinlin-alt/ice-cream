void deletelist(LinkedList* L)//ɾ��ָ��Ԫ��
{
    printf("������Ҫɾ����data��");
    int data;
    scanf("%d", &data);//ȷ��Ҫɾ��������data 
    Node* current=L->head;//����ָ�����ں���ǰ�� 
    Node* previous=NULL;
    
    if(current==NULL)//�������Ϊ�գ�ֱ�ӷ���
	{
        printf("����Ϊ�գ��޷�ɾ��\n");
        return;
    }
    if (current!=NULL&&current->data==data)//���Ҫɾ���Ľ����ͷ���
	{
        L->head=current->next; //��ͷָ��ָ����һ����� 
        free(current); // �ͷ�ͷ����ڴ棬ɾ��������Ҫfree 
        printf("ɾ���ɹ���\n");
        return;
    }
    while(current!=NULL&&current->data!=data)//��������Ѱ��Ҫɾ����data 
	{
        previous=current;
        current=current->next;
    }
    if(current==NULL)//���û���ҵ�Ҫɾ���Ľڵ�
	{
        printf("δ�ҵ�data������\n");
        return;
    }
    // �ҵ��˵���� 
    previous->next=current->next; // ��ǰһ������nextָ��ǰ�ڵ����һ���ڵ�head 
    free(current);//�ͷŵ�ǰ�ڵ��ڴ�
    printf("ɾ���ɹ���\n");
}
