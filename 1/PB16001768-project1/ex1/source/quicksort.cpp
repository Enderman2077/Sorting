#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
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

int main(){
	FILE *fpr,*fpw;
	FILE *fpw2=fopen("../output/quicksort/time.txt","a");
	int start_t,finish_t,run_time[6];
	int a[131072],scale,key;
	long i,j,length;
	for(scale=2;scale<=17;scale+=3){
		length=pow(2,scale);
		fpr=fopen("../input/input_integer.txt","r");
		for(i=0;i<length;i++) fscanf(fpr,"%d",&a[i]);
		start_t=clock();
		QuickSort(a,0,length-1);
		finish_t=clock();
		run_time[((scale+1)/3)-1]=finish_t-start_t;
		if(scale==2) fpw=fopen("../output/quicksort/result_2.txt","w");
		else if(scale==5) fpw=fopen("../output/quicksort/result_5.txt","w");
		else if(scale==8) fpw=fopen("../output/quicksort/result_8.txt","w");
		else if(scale==11) fpw=fopen("../output/quicksort/result_11.txt","w");
		else if(scale==14) fpw=fopen("../output/quicksort/result_14.txt","w");
		else if(scale==17) fpw=fopen("../output/quicksort/result_17.txt","w");
		for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
		fprintf(fpw2,"2^%d runtime:%dms\n",scale,run_time[((scale+1)/3)-1]);
	}
}
