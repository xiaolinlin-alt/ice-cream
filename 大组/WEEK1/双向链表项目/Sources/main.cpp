#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include "function.h"

typedef struct DuLNode 
{
	int data;
	struct DuLNode* next;//˫�������뵥����������� 
	struct DuLNode* prior;//����һ��next��˫����ǰ��ָ��ͺ��ָ�� 
}DuLNode;

typedef struct//���嵥����ṹ
{
    DuLNode* head; //����ͷ��� 
}DuLinkedList;

int main() 
{

    system("color F0"); //���ô�����ɫ 
	char password[20];//����һ���ַ�����password�����ڴ洢�û����������
	DuLinkedList L;
    initList(&L);   
    menu();//���ô�ӡ�˵��ĺ��� 
	printf("�������������룺\n");
	scanf("%s",password);

    system("pause");//ʹ������ִͣ��
	system("cls");
	
    if(strcmp(password,"1234")==0)
    {
    	printf("��ӭ���룡����\n"); 
   		menu();
   		while (1) // �������ܽ������� 
		{ 
        	int chose;
        	scanf("%d", &chose);
       		switch (chose) 
			{
				case 1:inputdata(&L);//¼�� 
						break;
       	 	    case 2:printlist(&L);//��ӡ 
						break;
           		case 3:clearlist(&L);// ��� 
						break; 
				case 4:searchlist(&L);//���� 
						break; 
				case 5:modifylist(&L);//�޸� 
						break;
				case 6:deletelist(&L);//ɾ�� 
						break; 
				case 7:findmiddle(&L);//�ҵ�˫������е�
						break;
				case 8:insertlist(&L,77);//��������77 
						break; 
				case 9:judgecycle(&L);//�ж�˫�����Ƿ�ɻ� 
						break; 
            	case 10: printf("�˳�����л����ʹ�ã���ӭ�´�ʹ��\n"); exit(0); // �˳�ϵͳ 
            	default:printf("���������������������룡����\n"); 
						system("pause"); system("cls"); // ��ͣ�����û��鿴������� ,���Ž����������� 
			}
  		 }
  	}
	else if(strcmp(password, "1234")!= 0)
    {
   		printf("�����������������\n");
    }
    return 0;
}
