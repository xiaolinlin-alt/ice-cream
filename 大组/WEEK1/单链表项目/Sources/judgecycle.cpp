int judgecycle(LinkedList* L)//�жϳɻ� 
{
    if(L->head==NULL||L->head->next==NULL) 
	{
        return 0; //����Ϊ�ջ�ֻ��һ���ڵ㣬�����ܳɻ�
    }
    Node* slow=L->head;
    Node* fast= L->head;
    while (fast!=NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//��ָ��ÿ���ƶ�һ������ָ��ÿ���ƶ����� 
        fast = fast->next->next;   
        if(slow==fast) 
		{
            return 1; //�������ָ��ֵ��Ⱦ�������һ���ˣ�˵�������л�
        }
    }
    return 0; // ��ָ�뵽������ĩβ��˵�������޻�
}
