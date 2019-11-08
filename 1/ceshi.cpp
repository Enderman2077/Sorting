#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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
    for(i=1;i<65536;i++) C[i]=0;
	for(j=0;j<length;j++) C[a[j]]++;
	for(i=2;i<65536;i++) C[i]+=C[i-1];
	for(j=length-1;j>=0;j--){
		B[C[a[j]]-1]=a[j];
		C[a[j]]--;
	} 
	for(i=0;i<length;i++) a[i]=B[i];
}

int main(){
	FILE *fpr=fopen("../input/input_integer.txt","r");
	FILE *fpw,*fpw2;
	int start_t,finish_t,run_time;
	int a[131072],flag,scale,key;
	long i,j,length;
	for(i=0;i<131072;i++) fscanf(fpr,"%d",&a[i]);
	printf("Please input the algorithm:\n1.Insertion-Sort\n2.HeapSort\n3.QuickSort\n4.Radix-Sort\n5.Counting-Sort\n");
	scanf("%d",&flag);
	printf("Please input the scale of the input data:2^x x=2 5 8 11 14 17\n");
	scanf("%d",&scale);
	length=pow(2,scale);
	switch(flag){
		case 1:{//insertion
			start_t=clock();
			for(j=1;j<length;j++){
				key=a[j];
				i=j-1;
				while(i>=0&&a[i]>key){
					a[i+1]=a[i];
					i--;
				}
				a[i+1]=key;
			}
			finish_t=clock();
			break;
		}
		case 2:{//heap
			start_t=clock();
			HeapSort(a,length);
			finish_t=clock();
			break;
		}
		case 3:{//quick
			start_t=clock();
			QuickSort(a,0,length-1);
			finish_t=clock();
			break;
		}
		case 4:{//radix
			start_t=clock();
			Radix_Sort(a,length,1);
			finish_t=clock();
			break;
		}
		case 5:{//counting
			start_t=clock();
			Counting_Sort(a,length);
			finish_t=clock();
			break;
		}
	}
	switch(flag){
		case 1:{
			if(scale==2) fpw=fopen("../output/insert_sort/result_2.txt","w");
			else if(scale==5) fpw=fopen("../output/insert_sort/result_5.txt","w");
			else if(scale==8) fpw=fopen("../output/insert_sort/result_8.txt","w");
			else if(scale==11) fpw=fopen("../output/insert_sort/result_11.txt","w");
			else if(scale==14) fpw=fopen("../output/insert_sort/result_14.txt","w");
			else if(scale==17) fpw=fopen("../output/insert_sort/result_17.txt","w");
			for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
			break;
		}
		case 2:{
			if(scale==2) fpw=fopen("../output/heapsort/result_2.txt","w");
			else if(scale==5) fpw=fopen("../output/heapsort/result_5.txt","w");
			else if(scale==8) fpw=fopen("../output/heapsort/result_8.txt","w");
			else if(scale==11) fpw=fopen("../output/heapsort/result_11.txt","w");
			else if(scale==14) fpw=fopen("../output/heapsort/result_14.txt","w");
			else if(scale==17) fpw=fopen("../output/heapsort/result_17.txt","w");
			for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
			break;
		}
		case 3:{
			if(scale==2) fpw=fopen("../output/quicksort/result_2.txt","w");
			else if(scale==5) fpw=fopen("../output/quicksort/result_5.txt","w");
			else if(scale==8) fpw=fopen("../output/quicksort/result_8.txt","w");
			else if(scale==11) fpw=fopen("../output/quicksort/result_11.txt","w");
			else if(scale==14) fpw=fopen("../output/quicksort/result_14.txt","w");
			else if(scale==17) fpw=fopen("../output/quicksort/result_17.txt","w");
			for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
			break;
		}
		case 4:{
			if(scale==2) fpw=fopen("../output/radix_sort/result_2.txt","w");
			else if(scale==5) fpw=fopen("../output/radix_sort/result_5.txt","w");
			else if(scale==8) fpw=fopen("../output/radix_sort/result_8.txt","w");
			else if(scale==11) fpw=fopen("../output/radix_sort/result_11.txt","w");
			else if(scale==14) fpw=fopen("../output/radix_sort/result_14.txt","w");
			else if(scale==17) fpw=fopen("../output/radix_sort/result_17.txt","w");
			for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
			break;
		}
		case 5:{
			if(scale==2) fpw=fopen("../output/counting_sort/result_2.txt","w");
			else if(scale==5) fpw=fopen("../output/counting_sort/result_5.txt","w");
			else if(scale==8) fpw=fopen("../output/counting_sort/result_8.txt","w");
			else if(scale==11) fpw=fopen("../output/counting_sort/result_11.txt","w");
			else if(scale==14) fpw=fopen("../output/counting_sort/result_14.txt","w");
			else if(scale==17) fpw=fopen("../output/counting_sort/result_17.txt","w");
			for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
			break;
		}
	}
	run_time=finish_t-start_t;
	if(flag==1){
		fpw2=fopen("../output/insert_sort/time.txt","a");
		fprintf(fpw2,"2^%d runtime:%dms\n",scale,run_time);
	}
	printf("run_time£º%dms\n",run_time);
	fclose(fpw);
	fclose(fpr);
} 
