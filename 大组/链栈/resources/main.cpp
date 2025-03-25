#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>

typedef struct StackNode//����ջ�ڵ�
{
    double data;//������洢����
    struct StackNode*next;//ָ����,ָ����һ���ڵ�
}StackNode;

typedef struct//������ջ
{
    StackNode*top;//ջ��ָ�룬���ջ��ָ��ָ��գ���˵����ջΪ�� 
    int count;//ջ��Ԫ�ظ���
} LinkStack;

void InitStack(LinkStack*stack);
bool IsEmpty(LinkStack* stack);
void Push(LinkStack*stack,double data);
double Pop(LinkStack* stack);
double Peek(LinkStack* stack);
int Precedence(char op);
double ApplyOperation(double a,double b,char op) ;
bool ValidateExpression(char*expr);
double EvaluateExpression(char* expression);
void menu();

// ������
int main() 
{
    char expression[100];
    menu();
    while(1) 
	{
        printf("\n��������ʽ(������0�˳�):");
        if(fgets(expression,sizeof(expression),stdin)==NULL) 
		{
            printf("\n��лʹ�ã��ټ���\n");
            break; 
        }
        
        size_t len=strlen(expression);// �����з�
        if(len>0&&expression[len-1]=='\n') 
		{
            expression[len-1] = '\0';
        }
        
        // ����˳�����
        if(strcmp(expression, "0") == 0) {
            printf("\n��лʹ�ã��ټ���\n");
            break;
        }
        else if(expression[0] == '\0') {
            continue;
        }
        
        // ��֤���ʽ
        if(!ValidateExpression(expression)) {
            continue;
        }
        
        // ������ʽ
        double result;
        printf("\n����: %s\n", expression);
        result = EvaluateExpression(expression);
        printf("���: %.2f\n", result);
    }
    return 0;
}
