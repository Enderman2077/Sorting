#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include<string.h>
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
	FILE *fpr,*fpw;
	FILE *fpw2=fopen("../output/counting_sort/time.txt","a");
	double run_time[6];
	_LARGE_INTEGER time_start;	//��ʼʱ��
	_LARGE_INTEGER time_over;	//����ʱ��
	double dqFreq;		//��ʱ��Ƶ��
	LARGE_INTEGER f;	//��ʱ��Ƶ��
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	int a[131072],scale,key;
	long i,j,length;
	for(scale=2;scale<=17;scale+=3){
		length=pow(2,scale);
		fpr=fopen("../input/input_integer.txt","r");
		for(i=0;i<length;i++) fscanf(fpr,"%d",&a[i]);
		QueryPerformanceCounter(&time_start);
		Counting_Sort(a,length);
		QueryPerformanceCounter(&time_over);
		run_time[((scale+1)/3)-1]=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
		if(scale==2) fpw=fopen("../output/counting_sort/result_2.txt","w");
		else if(scale==5) fpw=fopen("../output/counting_sort/result_5.txt","w");
		else if(scale==8) fpw=fopen("../output/counting_sort/result_8.txt","w");
		else if(scale==11) fpw=fopen("../output/counting_sort/result_11.txt","w");
		else if(scale==14) fpw=fopen("../output/counting_sort/result_14.txt","w");
		else if(scale==17) fpw=fopen("../output/counting_sort/result_17.txt","w");
		for(i=0;i<length;i++) fprintf(fpw,"%d\n",a[i]);
		fprintf(fpw2,"2^%d runtime:%fus\n",scale,run_time[((scale+1)/3)-1]);
	}
}
