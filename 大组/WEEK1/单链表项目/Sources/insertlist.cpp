void insertlist(LinkedList* L, int data)//���������½����뵽��һ������β������һ������ͷ�� 
{
    Node* fresh=(Node*)malloc(sizeof(Node)); //��̬�����ڴ棬�����½��fresh
    if (fresh==NULL) 
	{
        printf("�ڴ����ʧ��\n");
        return;
    }
    fresh->data=data;//�����½ڵ������
    fresh->next=NULL; //����ָ���
    if(L->head==NULL) 
	{
        L->head=fresh;//�������Ϊ��,���½ڵ�����Ϊͷ�ڵ�
    } else 
	{
        Node* move=L->head;//����һ��ָ�룬��ʼ��Ϊͷ���
        while(move->next!=NULL) //һֱ�ƶ��������
		{ 
            move=move->next; // ������,��������
        }  
        move->next = fresh;//���½ڵ���뵽β��
    }
}
