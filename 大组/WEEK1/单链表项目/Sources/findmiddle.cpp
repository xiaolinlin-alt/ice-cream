void findmiddle(LinkedList* L)//快慢指针法 
{
    if (L->head==NULL) 
	{
        printf("链表为空，没有中间值\n");
        return;
    }
    Node* slow=L->head;//定义一个慢指针，开始时指向head 
    Node* fast=L->head;//定义一个快指针，开始时也指向head 
    
    while (fast!= NULL&&fast->next!=NULL) 
	{
        slow = slow->next;//慢指针每移动一个，快指针移动两个 
        fast = fast->next->next;//等快指针指向链表尾部的时候，慢指针刚好指向链表的中间值 
    }
    printf("链表的中间值是: %d\n", slow->data);
    
    system("pause"); // 暂停程序
    system("cls"); // 清屏 
}
