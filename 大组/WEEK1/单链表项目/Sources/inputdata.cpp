void inputdata(LinkedList*L) //����¼��data���� β�巨 
{
	Node*fresh=(Node*)malloc(sizeof(Node));//��̬�����ڴ棬�����½��fresh 
	if(fresh==NULL) 
	{
        printf("�ڴ����ʧ��\n");
        return;
    }
	fresh->next=NULL;//����ָ��� 
	
	printf("������data��");
    scanf("%d",&fresh->data);//������data
	if(L->head==NULL) 
	{
        L->head=fresh;//�������Ϊ��,���½ڵ�����Ϊͷ�ڵ�
    } 
	else
	{
        Node* move=L->head; // �ٶ���һ������ʼ��Ϊͷ��㣬β�巨 
        while(move->next!=NULL) // һֱ�ƶ��������
		{ 
            move=move->next; // ������,��������Ŀ���ǽ��Ǹ��������data�Ƶ�����β�� 
        }
        // ��data���뵽β��
        move->next =fresh;
    }
    system("pause"); // ��ͣ����
    system("cls"); // ���� 
}

