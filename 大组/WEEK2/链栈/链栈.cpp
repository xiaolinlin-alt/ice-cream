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

void InitStack(LinkStack*stack)//初始化栈
{
    stack->top=NULL;//此时栈为空 
    stack->count=0;//栈内元素个数为0 
}

bool IsEmpty(LinkStack* stack) //判断栈是否为空
{
    return stack->top==NULL;
}


void Push(LinkStack*stack,double data)//压栈，将元素压入栈内，就是让新节点的next指向原来栈的顶部，然后top指针指向新节点 
{
    StackNode*newNode=(StackNode*)malloc(sizeof(StackNode));//开辟内存 
    if(!newNode) 
	{
        printf("内存分配失败\n");//如果开辟内存失败，打印错误信息，退出系统 
        exit(1);
    }
    newNode->data=data;//将传入的data值赋给新节点的数据域 
    newNode->next=stack->top;//next指针指向当前栈顶节点 
    stack->top=newNode;//更新top指针，新节点成为新的栈顶顶点 
    stack->count++;//增加栈内元素个数 
}


double Pop(LinkStack* stack)//弹栈
{
    if(IsEmpty(stack)) 
	{
        printf("栈为空，无法弹栈\n");
        exit(1);//如果栈为空，无法弹栈，打印错误信息，并终止程序 
    }
    StackNode* temp=stack->top;//保存栈顶指针 
    double value=temp->data;//保存栈顶指针的值 
    stack->top=temp->next;//更新栈顶指针，使之指向之前栈顶节点的下一个节点 
    free(temp);//释放被移除栈顶节点所占的内存 
    stack->count--;//减小栈内元素的个数 
    return value;//返回被弹出的元素的值 
}

double Peek(LinkStack* stack)//查看栈顶元素
{
    if(IsEmpty(stack)) 
	{
        printf("栈为空，无法查看栈顶元素\n");
        exit(1);//如果栈为空，没有栈顶元素，打印错误信息 
    }
    return stack->top->data;//如果不为空，就返回栈顶节点的数据 
}

int Precedence(char op)//确定给定运算符的优先级
{
    if(op=='+'||op =='-') return 1;//如果是+或者-，说明运算符优先级较低 
    if(op=='*'||op=='/') return 2;//如果是*挥着/，说明运算符优先级较高 
    return 0;//如果是其他，比如(或者)，不区分 
}

//根据给定的运算符对两个操作数进行相应的运算。
double ApplyOperation(double a,double b,char op) 
{
    switch(op)//根据符号进行相应的计算 
	{
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':
			if(b==0)
			{
				printf("注意除数不能为0\n");
				exit(1);	
			}
			return a/b;
        default:
            printf("无效的运算符: %c\n", op);
            exit(1);
    }
}

bool ValidateExpression(char*expr)
{
	int parenCount=0;//计算左括号，排除左括号未闭合的情况 
    bool expectOperand=true;//标记当前操作的数或者运算符 
    for(int i=0;expr[i]!='\0'&&expr[i]!='\n';i++) //遍历表达式 
	{
        if(expr[i]==' ') continue;//跳过空格 
        if(expectOperand) 
		{
            if(expr[i]=='(') 
			{
                parenCount++;//如果是左括号，计算左括号的加1 
            } 
			else if(isdigit(expr[i])||expr[i]=='.') 
			{
                expectOperand=false;
                // 验证数字格式
                bool hasDecimal=false;//记录是否有小数点
				//如果一个数字中包含多个小数点，应该报错提醒 
                while(isdigit(expr[i])||expr[i]=='.') 
				{
                    if(expr[i]=='.') 
					{
                        if(hasDecimal) 
						{
                            printf("错误,数字中包含多个小数点\n");
                            return false;
                        }
                        hasDecimal=true;
                    }
                    i++;
                }
                i--;
            } 
			else //找到既不是数字也不是左括号的了 
			{
                printf("错误,期望数字或左括号，但找到 '%c'\n", expr[i]);
                return false;
            }
        } 
		else //如果没有出现一对括号的话，也应该报错 
		{
            if(expr[i]==')') 
			{
                if(--parenCount<0) 
				{
                    printf("错误,括号不匹配\n");
                    return false;
                }
            } 
			else if(expr[i]=='+'||expr[i]=='-'||expr[i]=='*'||expr[i]=='/') 
			{
                expectOperand=true;
            } 
			else 
			{
                printf("错误,无效字符 '%c'\n", expr[i]);
                return false;
            }
        }
    }
    if(parenCount!=0)//括号是否匹配 
	{
        printf("错误,括号不匹配\n");
        return false;
    }
    if(expectOperand) //表达式不能以运算符为结尾 
	{
        printf("错误,表达式不完整\n");
        return false;
    }
    return true;
}

double EvaluateExpression(char* expression) // 计算表达式
{
    LinkStack values;    //操作数栈
    LinkStack operators; //运算运算符栈
    InitStack(&values);//初始化数栈 
    InitStack(&operators);//初始化符号栈 

    for(int i=0;expression[i]!='\0';i++) //遍历表达式 
	{
        if(expression[i]==' ') continue; //跳过空格，继续下一次循环 
    	//如果当前字符是数字或者小数点，开始解析完整的数字 
        if(isdigit(expression[i])||expression[i]=='.') //isdigit用来判断当前字符是否为数字 
		{
            double num=0;
            int decimal=0;
            while(expression[i]!='\0'&&(isdigit(expression[i])||expression[i]=='.')) 
			{
                if(expression[i]=='.')//如果是小数点的话，就设置decimal为1 
				{
                    decimal=1;//标记小数部分开始 
                } 
				else //如果不是小数点的话，就转化成数字 
				{
                    num=num*10+(expression[i]-'0');//拼接整数部分 
                    if(decimal)
                    {
						decimal=decimal*10;//记录小数点位数 
					}		
                }
                i++;//移到下一个字符 
            }
            i--; //回退一步，因为 
            if(decimal)
			{
				num/=decimal;//处理小数部分 
			} 
            Push(&values, num);//将解析到的数字压入数字栈中 
        }
        // 如果是左括号，压入运算符栈
        else if(expression[i]=='(') 
		{
            Push(&operators,expression[i]);
        }
        //如果是右括号，计算括号内的表达式
        //这里我们用右括号来触发计算 
        else if(expression[i]==')') 
		{
            while(!IsEmpty(&operators)&&Peek(&operators)!='(')
			{
                double b=Pop(&values);
                double a=Pop(&values);
                char op=(char)Pop(&operators);////如果碰到右括号，将一些数字都压如数字栈，符号压入运算符栈，然后应用和计算表达式的函数 
                Push(&values,ApplyOperation(a,b,op));
            }
            Pop(&operators); // 弹出 '('
        }
        // 如果是运算符
        else if(expression[i]=='+'||expression[i]=='-'||expression[i]=='*'||expression[i]=='/') 
		{
            while(!IsEmpty(&operators)&&Precedence(Peek(&operators))>=Precedence(expression[i])) 
			{
                double b = Pop(&values);
                double a = Pop(&values);
                char op = (char)Pop(&operators);
                Push(&values, ApplyOperation(a,b,op));
            }
            Push(&operators, expression[i]);
        }
    }

    // 处理剩余的运算符
    while (!IsEmpty(&operators)) 
	{
        double b = Pop(&values);
        double a = Pop(&values);
        char op = (char)Pop(&operators);
        Push(&values, ApplyOperation(a, b, op));
    }
    if(values.count!=1)
    {
    	printf("表达式格式不正确\n");
    	exit(1);
	}
    return Pop(&values);
}

void menu()
{
	printf("------------------------------\n");
	printf("----四则运算表达式的计算器----\n");
	printf("------------------------------\n");
	printf("-------支持运算符：+-*/-------\n");
	printf("-----支持带括号的优先级-------\n");
	printf("------------------------------\n");
	printf("------------------------------\n"); 
	
}

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
