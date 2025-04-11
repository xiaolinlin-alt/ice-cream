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

void swap(int* a,int*b)//交换 
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void PrintArray(int arr[],int n) 
{
    for(int i=0;i<n&&i<20;i++) //数据短就都打印出来 
	{
        printf("%d ",arr[i]);
    }
    if(n>20) 
	{
		printf("...(%d more)",n-20);//数据长的就打印局部的 
	}
    printf("\n");
}

int IsSorted(int arr[], int n) //判断是否排序了 
{
    for(int i=0;i<n-1;i++) 
	{
        if(arr[i]>arr[i+1]) return 0;
    }
    return 1;
}

// 生成随机数组
void GenerateRandomArray(int arr[],int n,int min,int max) 
{
    srand(time(NULL));
    for(int i=0;i<n;i++) 
	{
        arr[i]=rand()%(max-min+1)+min;
    }
}

//插入 
void InsertSort(int arr[],int n)//数组，数组长度 
{
	for(int i=1;i<n;i++)//从第一个开始,第0个本身就是有序的 
	{
		int key=arr[i];//要比较的元素 
		int j=i-1;//往前比较 
		while(j>=0&&arr[j]>key)//比较大小 
		{
			arr[j+1]=arr[j];//大就往后排 
			j--;
		}
		arr[j+1]=key;
	}
}


//选择排序
void SelectionSort(int arr[],int n) //每次选取最小的放在已经排序的数后面 
{
	int i,j,min;//控制循环，记录最小的 
	for(i=0;i<n;i++)
	{
		min=i;//假定第一个元素是最小的 
		for(j=i+1;j<n;j++)//扫描后面的元素 
		{
			if(arr[j]<arr[min])//如果后面的元素小于它，就将最小的定点，然后遍历下来找到最小的，再进行交换 
			{
				min=j;
			}
		}
		swap(&arr[min],&arr[i]); 
	}
}

//冒泡排序
void BubbleSort(int arr[],int n) 
{
	for(int i=n;i>1;i--)
	{
		int swapped=0;//是否发生了交换的标志
		for(int j=1;j<i;j++)
		{
			if(arr[j-1]>arr[j])
			{
				swap(&arr[j-1],&arr[j]);
				swapped=1;	
			}	
		}
		if(!swapped)
			break;//若无交换发生，结束 
	}
} 

//希尔排序，每趟排序的间距逐渐缩小
void ShellSort(int arr[],int n)
{
	int i,j,inc,key;
	//初始增量：n/2,每一趟之后除以2 
	for(inc=n/2;inc>0;inc/=2)
	{
		//每一趟采用插入排序 
		for(i=inc;i<n;i++)
		{
			key=arr[i];
			for(j=i;j>=inc&&key<arr[j-inc];j-=inc)
			{
				arr[j]=arr[j-inc];
			}
			arr[j]=key;
		}
	}
} 

//归并排序，分治和递归 
void merge(int arr[],int tempArr[],int left,int mid,int right)
{
	//标记左半区第一个未排序的元素
	int l_pos=left; 
	//标记右半去第一个未排序的元素
	int r_pos=mid+1;
	//临时数组元素的下标
	int pos=left;
	
	//合并 
	while(l_pos<=mid&&r_pos<=right)
	{
		if(arr[l_pos]<arr[r_pos])//左半区第一个剩余元素更小
		{
			tempArr[pos++]=arr[l_pos++];	
		} 
		else 
			tempArr[pos++]=arr[r_pos++];//右半区第一个剩余元素更小 
	}
	//合并左半区剩余的元素
	while(l_pos<=mid)
	{
		tempArr[pos++]=arr[l_pos++];	
	} 
	//合并右半区剩余的元素
	while(r_pos<=right)
	{
		tempArr[pos++]=arr[r_pos++];	
	} 
	//把临时数组中合并后的元素复制回原来的数组 
	for(int i=left;i<=right;i++) 
	{
        arr[i]=tempArr[i];
    }
} 
void msort(int arr[],int tempArr[],int left,int right)
{
	//如果只有一个元素，那么就不需要划分
	//只有一个元素的区域，本身就是有序的，归并即可 
	if(left<right)
	{
		//找中间点 
		int mid=(left+right)/2;	
		//递归划分左半部分
		msort(arr,tempArr,left,mid);
		//递归划分右半部分 
		msort(arr,tempArr,mid+1,right);
		//合并已经排序的部分 
		merge(arr,tempArr,left,mid,right);
	}	
	
}
void MergeSort(int arr[],int n)
{
	//分配一个辅助的数组 
	int* tempArr=(int*)malloc(n * sizeof(int));
	if(tempArr)
	{
		msort(arr,tempArr,0,n-1);
		free(tempArr);
	}	
	else
	{
		printf("分配内存失败！\n"); 
	}
} 

//计数排序，非比较式
//统计每个元素出现的次数，然后根据这些次数来排序 
void CountSort(int arr[],int n) 
{
    if(n<=1) return;
    
    int max=arr[0],min=arr[0];
    for(int i=1;i<n;i++) 
	{
        if(arr[i]>max) 
		{
			max = arr[i];
		}
        if(arr[i]<min) 
		{
			min=arr[i];
		}
    }//找到最大值和最小值，确定计数数组的大小
    int range=max-min+1; 
    int* count=(int*)calloc(range,sizeof(int));
    int* output=(int*)malloc(n *sizeof(int));
    
    for(int i=0; i<n;i++) count[arr[i]-min]++;//统计每个元素出现的次数 
    for(int i=1; i<range;i++) count[i]+=count[i-1];//确定每个元素在排序后数组中的位置。
    for(int i=n-1;i>= 0;i--) output[--count[arr[i]-min]]=arr[i];//逆序遍历，以保持排序的稳定性
    for(int i=0;i<n;i++) arr[i]=output[i];//将排序后的结果从输出数组output复制回原始数组arr
    
    free(count);
    free(output);
}

//快排，分治思想 
int Partition(int arr[],int low,int high) //划分的实现 
{
    int pivot=arr[high];//最后一个元素作为基准 
    int i=low-1;//用于记录小于基准的元素的位置。
    
    for(int j=low;j<=high-1;j++) //遍历 
	{
        if(arr[j]<pivot) //如果当前元素小于基准，则增加 i，并将arr[i]和arr[j]交换
		{
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);//将基准元素放到正确的位置
    return i+1;//返回基准元素的位置
}
void quickSort(int arr[],int high,int low) 
{
    if(low<high) //如果子数组长度大于1
	{
        int pi=Partition(arr,low,high);//对数组进行分区
        quickSort(arr,low,pi-1);//递归地对左子数组进行排序
        quickSort(arr,pi+1,high);//递归地对右子数组进行排序
    }
}
void QuickSort(int arr[],int n)
{
	quickSort(arr,0,n-1);
}

// 基数计数排序,非比较 ，逐位处理 ，从最低有效位开始，但是还有另外一种是从最高的开始 
void RadixCountSort(int arr[],int n) 
{
    int max=arr[0];
    for(int i=1;i<n;i++) //找到数组中的最大值，以确定需要处理的最大位数 
	{
		if(arr[i]>max)
		{
			max=arr[i];
		}
	} 
    for(int exp=1;max/exp>0;exp*=10) //处理位数 
	{
        int output[n];//用于存储当前位排序后的结果
        int count[10]={0};
        for(int i=0;i<n;i++) count[(arr[i]/exp)%10]++;//用于统计每个数字在当前位上出现的次数
        for(int i=1; i<10;i++) count[i]+=count[i-1];//将计数数组更新为实际位置。
        for(int i=n-1;i>=0;i--) output[--count[(arr[i]/exp)%10]]=arr[i];//根据计数数组中的位置信息，将原始数组中的元素放入输出数组中。
        for(int i=0; i<n;i++) arr[i]=output[i];//将排序后的结果复制回原始数组
    }
}
//大数据量测试
void RunBigDataTest() 
{
    const int sizes[]={10000,50000,200000};//不同的大数据量 
    const char* test_names[]={"InsertSort","MergeSort","QuickSort","CountSort","RadixCountSort"};
    void (*sort_funcs[])(int[],int)={InsertSort,MergeSort,QuickSort,CountSort,RadixCountSort};
    
    printf("\n=== 性能测试 ===\n");
    printf("算法\t\t10000\t\t50000\t\t200000\n");
    printf("--------------------------------------------------------\n");
    
    for(int i=0;i<5;i++) 
	{
        printf("%-12s",test_names[i]);//输出测试结果的标题和表头
        
        for(int j=0;j<3;j++) //遍历每一种排序算法
		{
            int n=sizes[j];
            int* arr=(int*)malloc(n*sizeof(int));
            GenerateRandomArray(arr,n,0,n*10);
            //记录时间 
            clock_t start=clock();
            sort_funcs[i](arr,n);
            clock_t end=clock();
            
            double time_spent=(double)(end-start)/CLOCKS_PER_SEC*1000;
            printf("\t%.4fms\t",time_spent);
            free(arr);
        }
        printf("\n");
    }
}

// 小数据量多次测试
void RunSmallDataTest() 
{
    const int small_size=100;//小数据量 
    const int iterations=100000;//迭代次数 
    const char* test_names[]={"InsertSort","MergeSort","QuickSort","CountSort","RadixCountSort"};
    void (*sort_funcs[])(int[],int)={InsertSort,MergeSort,QuickSort,CountSort,RadixCountSort};
    
    printf("\n=== 小数据量测试 (%d个元素 × %d次) ===\n",small_size,iterations);
    printf("算法\t\t平均时间(ms)\n");
    printf("------------------------\n");
    
    int* arr=(int*)malloc(small_size * sizeof(int));
    for(int i=0;i<5;i++) 
	{
        clock_t total_time=0;
        
        for(int j=0;j<iterations;j++) 
		{
            GenerateRandomArray(arr,small_size,0,1000);
            
            clock_t start=clock();
            sort_funcs[i](arr,small_size);
            clock_t end=clock();
            
            total_time+=(end-start);
        }
        
        double avg_time=(double)total_time/iterations/CLOCKS_PER_SEC*1000;
        printf("%-12s\t%.4fms\n",test_names[i],avg_time);
    }
    free(arr);
}

// 保存数组到文件
void SaveArrayToFile(int arr[],int n,const char*filename) 
{
    FILE* file=fopen(filename,"w");
    if(file==NULL) 
	{
        printf("无法打开文件 %s\n", filename);
        return;
    }
    
    fprintf(file,"%d\n",n); // 先写入数组大小
    for(int i=0; i<n;i++) 
	{
        fprintf(file,"%d ",arr[i]); // 写入数组元素
    }
    
    fclose(file);
    printf("数组已保存到 %s\n",filename);
}

// 从文件加载数组
int* LoadArrayFromFile(const char* filename,int* n) 
{
    FILE* file=fopen(filename,"r");
    if(file==NULL) 
	{
        printf("无法打开文件 %s\n",filename);
        return NULL;
    }
    
    if(fscanf(file,"%d",n)!=1) 
	{ // 读取数组大小
        fclose(file);
        return NULL;
    }
    
    int* arr=(int*)malloc(*n * sizeof(int));
    if(arr==NULL) 
	{
        fclose(file);
        return NULL;
    }
    
    for(int i=0;i<*n;i++) 
	{
        if(fscanf(file,"%d",&arr[i])!=1) 
		{ // 读取数组元素
            free(arr);
            fclose(file);
            return NULL;
        }
    }
    
    fclose(file);
    return arr;
}

// 显示菜单
void menu() 
{
    printf("\n=== 排序算法测试程序 ===\n");
    printf("1.运行大数据量测试\n");
    printf("2.运行小数据量测试\n");
    printf("3.生成随机数组并保存到文件\n");
    printf("4.从文件加载数组并排序\n");
    printf("5.手动输入数组并排序\n");
    printf("6.退出\n");
    printf("请选择: ");
}

