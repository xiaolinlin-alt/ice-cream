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

void swap(int* a,int*b)//���� 
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void PrintArray(int arr[],int n) 
{
    for(int i=0;i<n&&i<20;i++) //���ݶ̾Ͷ���ӡ���� 
	{
        printf("%d ",arr[i]);
    }
    if(n>20) 
	{
		printf("...(%d more)",n-20);//���ݳ��ľʹ�ӡ�ֲ��� 
	}
    printf("\n");
}

int IsSorted(int arr[], int n) //�ж��Ƿ������� 
{
    for(int i=0;i<n-1;i++) 
	{
        if(arr[i]>arr[i+1]) return 0;
    }
    return 1;
}

// �����������
void GenerateRandomArray(int arr[],int n,int min,int max) 
{
    srand(time(NULL));
    for(int i=0;i<n;i++) 
	{
        arr[i]=rand()%(max-min+1)+min;
    }
}

//���� 
void InsertSort(int arr[],int n)//���飬���鳤�� 
{
	for(int i=1;i<n;i++)//�ӵ�һ����ʼ,��0�������������� 
	{
		int key=arr[i];//Ҫ�Ƚϵ�Ԫ�� 
		int j=i-1;//��ǰ�Ƚ� 
		while(j>=0&&arr[j]>key)//�Ƚϴ�С 
		{
			arr[j+1]=arr[j];//��������� 
			j--;
		}
		arr[j+1]=key;
	}
}


//ѡ������
void SelectionSort(int arr[],int n) //ÿ��ѡȡ��С�ķ����Ѿ������������ 
{
	int i,j,min;//����ѭ������¼��С�� 
	for(i=0;i<n;i++)
	{
		min=i;//�ٶ���һ��Ԫ������С�� 
		for(j=i+1;j<n;j++)//ɨ������Ԫ�� 
		{
			if(arr[j]<arr[min])//��������Ԫ��С�������ͽ���С�Ķ��㣬Ȼ����������ҵ���С�ģ��ٽ��н��� 
			{
				min=j;
			}
		}
		swap(&arr[min],&arr[i]); 
	}
}

//ð������
void BubbleSort(int arr[],int n) 
{
	for(int i=n;i>1;i--)
	{
		int swapped=0;//�Ƿ����˽����ı�־
		for(int j=1;j<i;j++)
		{
			if(arr[j-1]>arr[j])
			{
				swap(&arr[j-1],&arr[j]);
				swapped=1;	
			}	
		}
		if(!swapped)
			break;//���޽������������� 
	}
} 

//ϣ������ÿ������ļ������С
void ShellSort(int arr[],int n)
{
	int i,j,inc,key;
	//��ʼ������n/2,ÿһ��֮�����2 
	for(inc=n/2;inc>0;inc/=2)
	{
		//ÿһ�˲��ò������� 
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

//�鲢���򣬷��κ͵ݹ� 
void merge(int arr[],int tempArr[],int left,int mid,int right)
{
	//����������һ��δ�����Ԫ��
	int l_pos=left; 
	//����Ұ�ȥ��һ��δ�����Ԫ��
	int r_pos=mid+1;
	//��ʱ����Ԫ�ص��±�
	int pos=left;
	
	//�ϲ� 
	while(l_pos<=mid&&r_pos<=right)
	{
		if(arr[l_pos]<arr[r_pos])//�������һ��ʣ��Ԫ�ظ�С
		{
			tempArr[pos++]=arr[l_pos++];	
		} 
		else 
			tempArr[pos++]=arr[r_pos++];//�Ұ�����һ��ʣ��Ԫ�ظ�С 
	}
	//�ϲ������ʣ���Ԫ��
	while(l_pos<=mid)
	{
		tempArr[pos++]=arr[l_pos++];	
	} 
	//�ϲ��Ұ���ʣ���Ԫ��
	while(r_pos<=right)
	{
		tempArr[pos++]=arr[r_pos++];	
	} 
	//����ʱ�����кϲ����Ԫ�ظ��ƻ�ԭ�������� 
	for(int i=left;i<=right;i++) 
	{
        arr[i]=tempArr[i];
    }
} 
void msort(int arr[],int tempArr[],int left,int right)
{
	//���ֻ��һ��Ԫ�أ���ô�Ͳ���Ҫ����
	//ֻ��һ��Ԫ�ص����򣬱����������ģ��鲢���� 
	if(left<right)
	{
		//���м�� 
		int mid=(left+right)/2;	
		//�ݹ黮����벿��
		msort(arr,tempArr,left,mid);
		//�ݹ黮���Ұ벿�� 
		msort(arr,tempArr,mid+1,right);
		//�ϲ��Ѿ�����Ĳ��� 
		merge(arr,tempArr,left,mid,right);
	}	
	
}
void MergeSort(int arr[],int n)
{
	//����һ������������ 
	int* tempArr=(int*)malloc(n * sizeof(int));
	if(tempArr)
	{
		msort(arr,tempArr,0,n-1);
		free(tempArr);
	}	
	else
	{
		printf("�����ڴ�ʧ�ܣ�\n"); 
	}
} 

//�������򣬷ǱȽ�ʽ
//ͳ��ÿ��Ԫ�س��ֵĴ�����Ȼ�������Щ���������� 
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
    }//�ҵ����ֵ����Сֵ��ȷ����������Ĵ�С
    int range=max-min+1; 
    int* count=(int*)calloc(range,sizeof(int));
    int* output=(int*)malloc(n *sizeof(int));
    
    for(int i=0; i<n;i++) count[arr[i]-min]++;//ͳ��ÿ��Ԫ�س��ֵĴ��� 
    for(int i=1; i<range;i++) count[i]+=count[i-1];//ȷ��ÿ��Ԫ��������������е�λ�á�
    for(int i=n-1;i>= 0;i--) output[--count[arr[i]-min]]=arr[i];//����������Ա���������ȶ���
    for(int i=0;i<n;i++) arr[i]=output[i];//�������Ľ�����������output���ƻ�ԭʼ����arr
    
    free(count);
    free(output);
}

//���ţ�����˼�� 
int Partition(int arr[],int low,int high) //���ֵ�ʵ�� 
{
    int pivot=arr[high];//���һ��Ԫ����Ϊ��׼ 
    int i=low-1;//���ڼ�¼С�ڻ�׼��Ԫ�ص�λ�á�
    
    for(int j=low;j<=high-1;j++) //���� 
	{
        if(arr[j]<pivot) //�����ǰԪ��С�ڻ�׼�������� i������arr[i]��arr[j]����
		{
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);//����׼Ԫ�طŵ���ȷ��λ��
    return i+1;//���ػ�׼Ԫ�ص�λ��
}
void quickSort(int arr[],int high,int low) 
{
    if(low<high) //��������鳤�ȴ���1
	{
        int pi=Partition(arr,low,high);//��������з���
        quickSort(arr,low,pi-1);//�ݹ�ض����������������
        quickSort(arr,pi+1,high);//�ݹ�ض����������������
    }
}
void QuickSort(int arr[],int n)
{
	quickSort(arr,0,n-1);
}

// ������������,�ǱȽ� ����λ���� ���������Чλ��ʼ�����ǻ�������һ���Ǵ���ߵĿ�ʼ 
void RadixCountSort(int arr[],int n) 
{
    int max=arr[0];
    for(int i=1;i<n;i++) //�ҵ������е����ֵ����ȷ����Ҫ��������λ�� 
	{
		if(arr[i]>max)
		{
			max=arr[i];
		}
	} 
    for(int exp=1;max/exp>0;exp*=10) //����λ�� 
	{
        int output[n];//���ڴ洢��ǰλ�����Ľ��
        int count[10]={0};
        for(int i=0;i<n;i++) count[(arr[i]/exp)%10]++;//����ͳ��ÿ�������ڵ�ǰλ�ϳ��ֵĴ���
        for(int i=1; i<10;i++) count[i]+=count[i-1];//�������������Ϊʵ��λ�á�
        for(int i=n-1;i>=0;i--) output[--count[(arr[i]/exp)%10]]=arr[i];//���ݼ��������е�λ����Ϣ����ԭʼ�����е�Ԫ�ط�����������С�
        for(int i=0; i<n;i++) arr[i]=output[i];//�������Ľ�����ƻ�ԭʼ����
    }
}
//������������
void RunBigDataTest() 
{
    const int sizes[]={10000,50000,200000};//��ͬ�Ĵ������� 
    const char* test_names[]={"InsertSort","MergeSort","QuickSort","CountSort","RadixCountSort"};
    void (*sort_funcs[])(int[],int)={InsertSort,MergeSort,QuickSort,CountSort,RadixCountSort};
    
    printf("\n=== ���ܲ��� ===\n");
    printf("�㷨\t\t10000\t\t50000\t\t200000\n");
    printf("--------------------------------------------------------\n");
    
    for(int i=0;i<5;i++) 
	{
        printf("%-12s",test_names[i]);//������Խ���ı���ͱ�ͷ
        
        for(int j=0;j<3;j++) //����ÿһ�������㷨
		{
            int n=sizes[j];
            int* arr=(int*)malloc(n*sizeof(int));
            GenerateRandomArray(arr,n,0,n*10);
            //��¼ʱ�� 
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

// С��������β���
void RunSmallDataTest() 
{
    const int small_size=100;//С������ 
    const int iterations=100000;//�������� 
    const char* test_names[]={"InsertSort","MergeSort","QuickSort","CountSort","RadixCountSort"};
    void (*sort_funcs[])(int[],int)={InsertSort,MergeSort,QuickSort,CountSort,RadixCountSort};
    
    printf("\n=== С���������� (%d��Ԫ�� �� %d��) ===\n",small_size,iterations);
    printf("�㷨\t\tƽ��ʱ��(ms)\n");
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

// �������鵽�ļ�
void SaveArrayToFile(int arr[],int n,const char*filename) 
{
    FILE* file=fopen(filename,"w");
    if(file==NULL) 
	{
        printf("�޷����ļ� %s\n", filename);
        return;
    }
    
    fprintf(file,"%d\n",n); // ��д�������С
    for(int i=0; i<n;i++) 
	{
        fprintf(file,"%d ",arr[i]); // д������Ԫ��
    }
    
    fclose(file);
    printf("�����ѱ��浽 %s\n",filename);
}

// ���ļ���������
int* LoadArrayFromFile(const char* filename,int* n) 
{
    FILE* file=fopen(filename,"r");
    if(file==NULL) 
	{
        printf("�޷����ļ� %s\n",filename);
        return NULL;
    }
    
    if(fscanf(file,"%d",n)!=1) 
	{ // ��ȡ�����С
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
		{ // ��ȡ����Ԫ��
            free(arr);
            fclose(file);
            return NULL;
        }
    }
    
    fclose(file);
    return arr;
}

// ��ʾ�˵�
void menu() 
{
    printf("\n=== �����㷨���Գ��� ===\n");
    printf("1.���д�����������\n");
    printf("2.����С����������\n");
    printf("3.����������鲢���浽�ļ�\n");
    printf("4.���ļ��������鲢����\n");
    printf("5.�ֶ��������鲢����\n");
    printf("6.�˳�\n");
    printf("��ѡ��: ");
}

