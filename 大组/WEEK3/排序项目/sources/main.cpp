#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//�����㷨 
void InsertSort(int arr[],int n);//���� 
void MergeSort(int arr[],int n);//�鲢 
void QuickSort(int arr[],int n);//���� 
void CountSort(int arr[],int n);//���� 
void RadixCountSort(int arr[],int n);//���� 
void SelectionSort(int arr[],int n);//ѡ�� 
void BubbleSort(int arr[],int n);//ð�� 
void ShellSort(int arr[],int n);//ϣ�� 
//��������
void swap(int* a, int* b);//���� 
void PrintArray(int arr[],int n);//��ӡ 
int IsSorted(int arr[],int n);//�ж��Ƿ����� 
void GenerateRandomArray(int arr[],int n,int min,int max);//����������� 
void RunBigDataTest();
void RunSmallDataTest();
void SaveArrayToFile(int arr[], int n, const char* filename);
int* LoadArrayFromFile(const char* filename, int* n);
void menu(); 

// ������
int main() 
{
    int choice;
    do 
	{
        menu();
        scanf("%d",&choice);
        
        switch(choice) 
		{
            case 1: 
			{
                RunBigDataTest();
                break;
            }
            case 2: 
			{
                RunSmallDataTest();
                break;
            }
            case 3: 
			{
                int n;
                printf("���������С:");
                scanf("%d",&n);
                int* arr=(int*)malloc(n*sizeof(int));
                GenerateRandomArray(arr,n,0,n*10);
                
                char filename[100];
                printf("�����ļ���:");
                scanf("%s",filename);
                SaveArrayToFile(arr,n,filename);
                
                free(arr);
                break;
            }
            case 4: 
			{
                char filename[100];
                printf("�����ļ���:");
                scanf("%s",filename);
                
                int n;
                int* arr=LoadArrayFromFile(filename,&n);
                if(arr==NULL) break;
                
                printf("���ص�����:");
                PrintArray(arr,n);
                
                printf("ѡ�������㷨:\n");
                printf("1.InsertSort\n2.MergeSort\n3.QuickSort\n4.CountSort\n5.RadixCountSort\n");
                int algo;
                scanf("%d",&algo);
                
                clock_t start=clock();
                switch(algo) 
				{
                    case 1:InsertSort(arr,n);break;
                    case 2:MergeSort(arr,n);break;
                    case 3:QuickSort(arr,n);break;
                    case 4:CountSort(arr,n);break;
                    case 5:RadixCountSort(arr,n);break;
                    default:printf("��Чѡ��\n");break;
                }
                clock_t end=clock();
                
                printf("����������:");
                PrintArray(arr,n);
                printf("����״̬:%s\n",IsSorted(arr,n)?"������":"δ����");
                printf("��ʱ: %.2fms\n", (double)(end-start)/CLOCKS_PER_SEC*1000);
                
                free(arr);
                break;
            }
            case 5: 
			{
                int n;
                printf("���������С: ");
                scanf("%d",&n);
                
                int* arr=(int*)malloc(n*sizeof(int));
                printf("����%d������: ",n);
                for(int i=0;i<n;i++) 
				{
                    scanf("%d", &arr[i]);
                }
                
                printf("ѡ�������㷨:\n");
                printf("1.InsertSort\n2.MergeSort\n3.QuickSort\n4.CountSort\n5.RadixCountSort\n");
                int algo;
                scanf("%d",&algo);
                
                clock_t start=clock();
                switch(algo) 
				{
                    case 1:InsertSort(arr,n);break;
                    case 2:MergeSort(arr,n);break;
                    case 3:QuickSort(arr,n);break;
                    case 4:CountSort(arr,n);break;
                    case 5:RadixCountSort(arr,n);break;
                    default: printf("��Чѡ��\n");break;
                }
                clock_t end=clock();
                
                printf("����������:");
                PrintArray(arr,n);
                printf("����״̬: %s\n",IsSorted(arr,n)?"������":"δ����");
                printf("��ʱ:%.2fms\n",(double)(end - start)/CLOCKS_PER_SEC*1000);
                
                free(arr);
                break;
            }
            case 6: 
			{
                printf("�˳�����\n");
                break;
            }
            default: 
			{
                printf("��Чѡ������������\n");
                break;
            }
        }
    } while(choice!=6);
    return 0;
}

