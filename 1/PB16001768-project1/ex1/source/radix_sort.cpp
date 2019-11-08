#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
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

int main(){
	FILE *fpr,*fpw;
	FILE *fpw2=fopen("../output/radix_sort/time.txt","a");
	int start_t,finish_t,run_time[6];
	int a[131072],scale,key;
	long i,j,length;
	for(scale=2;scale<=17;scale+=3){
		length=pow(2,scale);
		fpr=fopen("../input/input_integer.txt","r");
		for(i=0;i<length;i++) fscanf(fpr,"%d",&a[i]);
		start_t=clock();
		Radix_Sort(a,length,1);
		finish_t=clock();
		run_time[((scale+1)/3)-1]=finish_t-start_t;
		if(scale==2) fpw=fopen("../output/radix_sort/result_2.txt","w");
		else if(scale==5) fpw=fopen("../output/radix_sort/result_5.txt","w");
		else if(scale==8) fpw=fopen("../output/radix_sort/result_8.txt","w");
		else if(scale==11) fpw=fopen("../output/radix_sort/result_11.txt","w");
		else if(scale==14) fpw=fopen("../output/radix_sort/result_14.txt","w");
		else if(scale==17) fpw=fopen("../output/radix_sort/result_17.txt","w");
		for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
		fprintf(fpw2,"2^%d runtime:%dms\n",scale,run_time[((scale+1)/3)-1]);
	}
}
