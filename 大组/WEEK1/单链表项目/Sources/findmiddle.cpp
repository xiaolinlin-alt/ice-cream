void findmiddle(LinkedList* L)//����ָ�뷨 
{
    if (L->head==NULL) 
	{
        printf("����Ϊ�գ�û���м�ֵ\n");
        return;
    }
    Node* slow=L->head;//����һ����ָ�룬��ʼʱָ��head 
    Node* fast=L->head;//����һ����ָ�룬��ʼʱҲָ��head 
    
    while (fast!= NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//��ָ��ÿ�ƶ�һ������ָ���ƶ����� 
        fast = fast->next->next;//�ȿ�ָ��ָ������β����ʱ����ָ��պ�ָ��������м�ֵ 
    }
    printf("������м�ֵ��: %d\n", slow->data);
    
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
}
