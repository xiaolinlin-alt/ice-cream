#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//排序算法 
void InsertSort(int arr[],int n);//插入 
void MergeSort(int arr[],int n);//归并 
void QuickSort(int arr[],int n);//快排 
void CountSort(int arr[],int n);//计数 
void RadixCountSort(int arr[],int n);//基数 
void SelectionSort(int arr[],int n);//选择 
void BubbleSort(int arr[],int n);//冒泡 
void ShellSort(int arr[],int n);//希尔 
//辅助函数
void swap(int* a, int* b);//交换 
void PrintArray(int arr[],int n);//打印 
int IsSorted(int arr[],int n);//判断是否排序 
void GenerateRandomArray(int arr[],int n,int min,int max);//生成随机数组 
void RunBigDataTest();
void RunSmallDataTest();
void SaveArrayToFile(int arr[], int n, const char* filename);
int* LoadArrayFromFile(const char* filename, int* n);
void menu(); 

// 主函数
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
                printf("输入数组大小:");
                scanf("%d",&n);
                int* arr=(int*)malloc(n*sizeof(int));
                GenerateRandomArray(arr,n,0,n*10);
                
                char filename[100];
                printf("输入文件名:");
                scanf("%s",filename);
                SaveArrayToFile(arr,n,filename);
                
                free(arr);
                break;
            }
            case 4: 
			{
                char filename[100];
                printf("输入文件名:");
                scanf("%s",filename);
                
                int n;
                int* arr=LoadArrayFromFile(filename,&n);
                if(arr==NULL) break;
                
                printf("加载的数组:");
                PrintArray(arr,n);
                
                printf("选择排序算法:\n");
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
                    default:printf("无效选择\n");break;
                }
                clock_t end=clock();
                
                printf("排序后的数组:");
                PrintArray(arr,n);
                printf("排序状态:%s\n",IsSorted(arr,n)?"已排序":"未排序");
                printf("耗时: %.2fms\n", (double)(end-start)/CLOCKS_PER_SEC*1000);
                
                free(arr);
                break;
            }
            case 5: 
			{
                int n;
                printf("输入数组大小: ");
                scanf("%d",&n);
                
                int* arr=(int*)malloc(n*sizeof(int));
                printf("输入%d个整数: ",n);
                for(int i=0;i<n;i++) 
				{
                    scanf("%d", &arr[i]);
                }
                
                printf("选择排序算法:\n");
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
                    default: printf("无效选择\n");break;
                }
                clock_t end=clock();
                
                printf("排序后的数组:");
                PrintArray(arr,n);
                printf("排序状态: %s\n",IsSorted(arr,n)?"已排序":"未排序");
                printf("耗时:%.2fms\n",(double)(end - start)/CLOCKS_PER_SEC*1000);
                
                free(arr);
                break;
            }
            case 6: 
			{
                printf("退出程序\n");
                break;
            }
            default: 
			{
                printf("无效选择，请重新输入\n");
                break;
            }
        }
    } while(choice!=6);
    return 0;
}

