#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include<string.h>
int main(){
	FILE *fpr,*fpw;
	FILE *fpw2=fopen("../output/insert_sort/time.txt","a");
	double run_time[6];
	_LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	int a[131072],scale,key;
	long i,j,length;
	for(scale=2;scale<=17;scale+=3){
		length=pow(2,scale);
		fpr=fopen("../input/input_integer.txt","r");
		for(i=0;i<length;i++) fscanf(fpr,"%d",&a[i]);
		QueryPerformanceCounter(&time_start);
		for(j=1;j<length;j++){
			key=a[j];
			i=j-1;
			while(i>=0&&a[i]>key){
				a[i+1]=a[i];
				i--;
			}
			a[i+1]=key;
		}
		QueryPerformanceCounter(&time_over);
		run_time[((scale+1)/3)-1]=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
		if(scale==2) fpw=fopen("../output/insert_sort/result_2.txt","w");
		else if(scale==5) fpw=fopen("../output/insert_sort/result_5.txt","w");
		else if(scale==8) fpw=fopen("../output/insert_sort/result_8.txt","w");
		else if(scale==11) fpw=fopen("../output/insert_sort/result_11.txt","w");
		else if(scale==14) fpw=fopen("../output/insert_sort/result_14.txt","w");
		else if(scale==17) fpw=fopen("../output/insert_sort/result_17.txt","w");
		for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
		fprintf(fpw2,"2^%d runtime:%fus\n",scale,run_time[((scale+1)/3)-1]);
	}
}
