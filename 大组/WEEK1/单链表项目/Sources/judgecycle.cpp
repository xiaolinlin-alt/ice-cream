int judgecycle(LinkedList* L)//判断成环 
{
    if(L->head==NULL||L->head->next==NULL) 
	{
        return 0; //链表为空或只有一个节点，不可能成环
    }
    Node* slow=L->head;
    Node* fast= L->head;
    while (fast!=NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//慢指针每次移动一个，快指针每次移动两个 
        fast = fast->next->next;   
        if(slow==fast) 
		{
            return 1; //如果快慢指针值相等就是碰到一起了，说明链表有环
        }
    }
    return 0; // 快指针到达链表末尾，说明链表无环
}
