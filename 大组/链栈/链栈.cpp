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

void InitStack(LinkStack*stack)//��ʼ��ջ
{
    stack->top=NULL;//��ʱջΪ�� 
    stack->count=0;//ջ��Ԫ�ظ���Ϊ0 
}

bool IsEmpty(LinkStack* stack) //�ж�ջ�Ƿ�Ϊ��
{
    return stack->top==NULL;
}


void Push(LinkStack*stack,double data)//ѹջ����Ԫ��ѹ��ջ�ڣ��������½ڵ��nextָ��ԭ��ջ�Ķ�����Ȼ��topָ��ָ���½ڵ� 
{
    StackNode*newNode=(StackNode*)malloc(sizeof(StackNode));//�����ڴ� 
    if(!newNode) 
	{
        printf("�ڴ����ʧ��\n");//��������ڴ�ʧ�ܣ���ӡ������Ϣ���˳�ϵͳ 
        exit(1);
    }
    newNode->data=data;//�������dataֵ�����½ڵ�������� 
    newNode->next=stack->top;//nextָ��ָ��ǰջ���ڵ� 
    stack->top=newNode;//����topָ�룬�½ڵ��Ϊ�µ�ջ������ 
    stack->count++;//����ջ��Ԫ�ظ��� 
}


double Pop(LinkStack* stack)//��ջ
{
    if(IsEmpty(stack)) 
	{
        printf("ջΪ�գ��޷���ջ\n");
        exit(1);//���ջΪ�գ��޷���ջ����ӡ������Ϣ������ֹ���� 
    }
    StackNode* temp=stack->top;//����ջ��ָ�� 
    double value=temp->data;//����ջ��ָ���ֵ 
    stack->top=temp->next;//����ջ��ָ�룬ʹָ֮��֮ǰջ���ڵ����һ���ڵ� 
    free(temp);//�ͷű��Ƴ�ջ���ڵ���ռ���ڴ� 
    stack->count--;//��Сջ��Ԫ�صĸ��� 
    return value;//���ر�������Ԫ�ص�ֵ 
}

double Peek(LinkStack* stack)//�鿴ջ��Ԫ��
{
    if(IsEmpty(stack)) 
	{
        printf("ջΪ�գ��޷��鿴ջ��Ԫ��\n");
        exit(1);//���ջΪ�գ�û��ջ��Ԫ�أ���ӡ������Ϣ 
    }
    return stack->top->data;//�����Ϊ�գ��ͷ���ջ���ڵ������ 
}

int Precedence(char op)//ȷ����������������ȼ�
{
    if(op=='+'||op =='-') return 1;//�����+����-��˵����������ȼ��ϵ� 
    if(op=='*'||op=='/') return 2;//�����*����/��˵����������ȼ��ϸ� 
    return 0;//���������������(����)�������� 
}

//���ݸ����������������������������Ӧ�����㡣
double ApplyOperation(double a,double b,char op) 
{
    switch(op)//���ݷ��Ž�����Ӧ�ļ��� 
	{
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':
			if(b==0)
			{
				printf("ע���������Ϊ0\n");
				exit(1);	
			}
			return a/b;
        default:
            printf("��Ч�������: %c\n", op);
            exit(1);
    }
}

bool ValidateExpression(char*expr)
{
	int parenCount=0;//���������ţ��ų�������δ�պϵ���� 
    bool expectOperand=true;//��ǵ�ǰ����������������� 
    for(int i=0;expr[i]!='\0'&&expr[i]!='\n';i++) //�������ʽ 
	{
        if(expr[i]==' ') continue;//�����ո� 
        if(expectOperand) 
		{
            if(expr[i]=='(') 
			{
                parenCount++;//����������ţ����������ŵļ�1 
            } 
			else if(isdigit(expr[i])||expr[i]=='.') 
			{
                expectOperand=false;
                // ��֤���ָ�ʽ
                bool hasDecimal=false;//��¼�Ƿ���С����
				//���һ�������а������С���㣬Ӧ�ñ������� 
                while(isdigit(expr[i])||expr[i]=='.') 
				{
                    if(expr[i]=='.') 
					{
                        if(hasDecimal) 
						{
                            printf("����,�����а������С����\n");
                            return false;
                        }
                        hasDecimal=true;
                    }
                    i++;
                }
                i--;
            } 
			else //�ҵ��Ȳ�������Ҳ���������ŵ��� 
			{
                printf("����,�������ֻ������ţ����ҵ� '%c'\n", expr[i]);
                return false;
            }
        } 
		else //���û�г���һ�����ŵĻ���ҲӦ�ñ��� 
		{
            if(expr[i]==')') 
			{
                if(--parenCount<0) 
				{
                    printf("����,���Ų�ƥ��\n");
                    return false;
                }
            } 
			else if(expr[i]=='+'||expr[i]=='-'||expr[i]=='*'||expr[i]=='/') 
			{
                expectOperand=true;
            } 
			else 
			{
                printf("����,��Ч�ַ� '%c'\n", expr[i]);
                return false;
            }
        }
    }
    if(parenCount!=0)//�����Ƿ�ƥ�� 
	{
        printf("����,���Ų�ƥ��\n");
        return false;
    }
    if(expectOperand) //���ʽ�����������Ϊ��β 
	{
        printf("����,���ʽ������\n");
        return false;
    }
    return true;
}

double EvaluateExpression(char* expression) // ������ʽ
{
    LinkStack values;    //������ջ
    LinkStack operators; //���������ջ
    InitStack(&values);//��ʼ����ջ 
    InitStack(&operators);//��ʼ������ջ 

    for(int i=0;expression[i]!='\0';i++) //�������ʽ 
	{
        if(expression[i]==' ') continue; //�����ո񣬼�����һ��ѭ�� 
    	//�����ǰ�ַ������ֻ���С���㣬��ʼ�������������� 
        if(isdigit(expression[i])||expression[i]=='.') //isdigit�����жϵ�ǰ�ַ��Ƿ�Ϊ���� 
		{
            double num=0;
            int decimal=0;
            while(expression[i]!='\0'&&(isdigit(expression[i])||expression[i]=='.')) 
			{
                if(expression[i]=='.')//�����С����Ļ���������decimalΪ1 
				{
                    decimal=1;//���С�����ֿ�ʼ 
                } 
				else //�������С����Ļ�����ת�������� 
				{
                    num=num*10+(expression[i]-'0');//ƴ���������� 
                    if(decimal)
                    {
						decimal=decimal*10;//��¼С����λ�� 
					}		
                }
                i++;//�Ƶ���һ���ַ� 
            }
            i--; //����һ������Ϊ 
            if(decimal)
			{
				num/=decimal;//����С������ 
			} 
            Push(&values, num);//��������������ѹ������ջ�� 
        }
        // ����������ţ�ѹ�������ջ
        else if(expression[i]=='(') 
		{
            Push(&operators,expression[i]);
        }
        //����������ţ����������ڵı��ʽ
        //�������������������������� 
        else if(expression[i]==')') 
		{
            while(!IsEmpty(&operators)&&Peek(&operators)!='(')
			{
                double b=Pop(&values);
                double a=Pop(&values);
                char op=(char)Pop(&operators);////������������ţ���һЩ���ֶ�ѹ������ջ������ѹ�������ջ��Ȼ��Ӧ�úͼ�����ʽ�ĺ��� 
                Push(&values,ApplyOperation(a,b,op));
            }
            Pop(&operators); // ���� '('
        }
        // ����������
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

    // ����ʣ��������
    while (!IsEmpty(&operators)) 
	{
        double b = Pop(&values);
        double a = Pop(&values);
        char op = (char)Pop(&operators);
        Push(&values, ApplyOperation(a, b, op));
    }
    if(values.count!=1)
    {
    	printf("���ʽ��ʽ����ȷ\n");
    	exit(1);
	}
    return Pop(&values);
}

void menu()
{
	printf("------------------------------\n");
	printf("----����������ʽ�ļ�����----\n");
	printf("------------------------------\n");
	printf("-------֧���������+-*/-------\n");
	printf("-----֧�ִ����ŵ����ȼ�-------\n");
	printf("------------------------------\n");
	printf("------------------------------\n"); 
	
}

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
