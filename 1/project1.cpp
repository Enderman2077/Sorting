#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include<string.h>
void MAX_HEAPIFY(int a[],long i,long heapsize){
	long l,r,largest;
	int temp;
	l=2*i+1;
	r=2*i+2;
	if(l<heapsize&&a[l]>a[i]) largest=l;
	else largest=i;
	if(r<heapsize&&a[r]>a[largest]) largest=r;
	if(largest!=i){
		temp=a[i];
		a[i]=a[largest];
		a[largest]=temp;
		MAX_HEAPIFY(a,largest,heapsize);
	}
}

void BUILD_MAX_HEAP(int a[],long length){
	long i,heapsize;
	heapsize=length;
	for(i=length/2-1;i>=0;i--) MAX_HEAPIFY(a,i,heapsize);
}

void HeapSort(int a[],long length){
	long i,heapsize;
	heapsize=length;
	int temp;
	BUILD_MAX_HEAP(a,length);
	for(i=length-1;i>=1;i--){
		temp=a[0];
		a[0]=a[i];
		a[i]=temp;
		heapsize--;
		MAX_HEAPIFY(a,0,heapsize);
	}
}

long PARTITION(int a[],long p,long r){
	int x,temp;
	long i,j;
	x=a[r];
	i=p-1;
	for(j=p;j<r;j++){
		if(a[j]<=x){
			i++;
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	}
	temp=a[i+1];
	a[i+1]=a[r];
	a[r]=temp; 
	return i+1;
}

void QuickSort(int a[],long p,long r){
	long q;
	if(p<r){
		q=PARTITION(a,p,r);
		QuickSort(a,p,q-1);
		QuickSort(a,q+1,r);
	}
}

void Radix_Sort(int a[],long length,int k){
    int b[length]={0};
    int bucket[10]={0};
    int digit;
    long i,j;
    while(k<=5){
    	memset(bucket,0,10*sizeof(int));
    	memset(b,0,length*sizeof(int));
    	for(i=0;i<length;i++){
        	digit=a[i]/(int)pow(10,k-1)%10;
        	bucket[digit]++;
    	}
    	for(i=1;i<10;i++) bucket[i]+=bucket[i-1];
    	for(i=length-1;i>=0;i--){
      		digit=a[i]/(int)pow(10,k-1)%10;
      		bucket[digit]--;
      		j=bucket[digit];
     		b[j]=a[i];
    	}
    	for(i=0;i<length;i++) a[i]=b[i];
		k++;
	}
}

void Counting_Sort(int a[],long length){
    int B[length];
	int C[65536];
    long i,j;
    for(i=0;i<65536;i++) C[i]=0;
	for(j=0;j<length;j++) C[a[j]]++;
	for(i=1;i<65536;i++) C[i]+=C[i-1];
	for(j=length;j>=0;j--){
		B[C[a[j]]-1]=a[j];
		C[a[j]]--;
	} 
	for(i=0;i<length;i++) a[i]=B[i];
}

int main(){
	double run_time;
	_LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	int a[131072],flag,scale,key;
	long i,j,length;
	for(i=0;i<131072;i++){
		if(rand()%2) a[i]=rand();
		else a[i]=rand()+32768;
	}
	printf("Please input the algorithm:\n1.Insertion-Sort\n2.HeapSort\n3.QuickSort\n4.Radix-Sort\n5.Counting-Sort\n");
	scanf("%d",&flag);
	printf("Please input the scale of the input data:2^x x=2 5 8 11 14 17\n");
	scanf("%d",&scale);
	length=pow(2,scale);
	switch(flag){
		case 1:{//insertion
			QueryPerformanceCounter(&time_start);	//计时开始
			for(j=1;j<length;j++){
				key=a[j];
				i=j-1;
				while(i>=0&&a[i]>key){
					a[i+1]=a[i];
					i--;
				}
				a[i+1]=key;
			}
			QueryPerformanceCounter(&time_over);	//计时结束
			break;
		}
		case 2:{//heap
			QueryPerformanceCounter(&time_start);
			HeapSort(a,length);
			QueryPerformanceCounter(&time_over);
			break;
		}
		case 3:{//quick
			QueryPerformanceCounter(&time_start);
			QuickSort(a,0,length-1);
			QueryPerformanceCounter(&time_over);
			break;
		}
		case 4:{//radix
			QueryPerformanceCounter(&time_start);
			Radix_Sort(a,length,1);
			QueryPerformanceCounter(&time_over);
			break;
		}
		case 5:{//counting
			QueryPerformanceCounter(&time_start);
			Counting_Sort(a,length);
			QueryPerformanceCounter(&time_over);
			break;
		}
	}
	run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	printf("run_time：%fus\n",run_time);
	for(i=0;i<length;i++) printf("%d ",a[i]);
} 
