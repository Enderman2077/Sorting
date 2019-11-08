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

int main(){
	FILE *fpr,*fpw;
	FILE *fpw2=fopen("../output/heapsort/time.txt","a");
	int start_t,finish_t,run_time[6];
	int a[131072],scale,key;
	long i,j,length;
	for(scale=2;scale<=17;scale+=3){
		length=pow(2,scale);
		fpr=fopen("../input/input_integer.txt","r");
		for(i=0;i<length;i++) fscanf(fpr,"%d",&a[i]);
		start_t=clock();
		HeapSort(a,length); 
		finish_t=clock();
		run_time[((scale+1)/3)-1]=finish_t-start_t;
		if(scale==2) fpw=fopen("../output/heapsort/result_2.txt","w");
		else if(scale==5) fpw=fopen("../output/heapsort/result_5.txt","w");
		else if(scale==8) fpw=fopen("../output/heapsort/result_8.txt","w");
		else if(scale==11) fpw=fopen("../output/heapsort/result_11.txt","w");
		else if(scale==14) fpw=fopen("../output/heapsort/result_14.txt","w");
		else if(scale==17) fpw=fopen("../output/heapsort/result_17.txt","w");
		for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
		fprintf(fpw2,"2^%d runtime:%dms\n",scale,run_time[((scale+1)/3)-1]);
	}
}
