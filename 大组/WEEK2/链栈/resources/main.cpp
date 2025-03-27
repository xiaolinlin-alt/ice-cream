#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>

typedef struct StackNode//定义栈节点
{
    double data;//数据域存储数据
    struct StackNode*next;//指针域,指向下一个节点
}StackNode;

typedef struct//定义链栈
{
    StackNode*top;//栈顶指针，如果栈顶指针指向空，就说明链栈为空 
    int count;//栈中元素个数
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

// 主函数
int main() 
{
    char expression[100];
    menu();
    while(1) 
	{
        printf("\n请输入表达式(或输入0退出):");
        if(fgets(expression,sizeof(expression),stdin)==NULL) 
		{
            printf("\n感谢使用，再见！\n");
            break; 
        }
        
        size_t len=strlen(expression);// 处理换行符
        if(len>0&&expression[len-1]=='\n') 
		{
            expression[len-1] = '\0';
        }
        
        // 检查退出命令
        if(strcmp(expression, "0") == 0) {
            printf("\n感谢使用，再见！\n");
            break;
        }
        else if(expression[0] == '\0') {
            continue;
        }
        
        // 验证表达式
        if(!ValidateExpression(expression)) {
            continue;
        }
        
        // 计算表达式
        double result;
        printf("\n计算: %s\n", expression);
        result = EvaluateExpression(expression);
        printf("结果: %.2f\n", result);
    }
    return 0;
}
