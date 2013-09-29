#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
const int maxn1=100000;
const int maxn2=1000;
char ch; 
int row,col;
int mode;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int bit[maxn2][maxn2];
int map[maxn2][maxn2];
int sum[maxn2][maxn2];
int visit[maxn2][maxn2];
long long num[maxn1];
void getMode(int argc,char *argv[])//根据命令行参数选择mode,同时处理错误输入
{
	FILE *fp;
	if(argc==1)
	{
		printf("too few indexes!\n");
		exit(0);
	}
	else if(argc==2)
	{
		if(strcmp(argv[1],"input.txt")!=0)
		{
			printf("file name not correct!\n");
			exit(0);
		}
		freopen_s(&fp,argv[1],"r",stdin);
		if(scanf_s("%d,\n%d,\n",&row,&col)!=2)
		{
			printf("input row or col wrong!\n");
			exit(0);
		}
		if(row==1)
		{
			mode=1;
		}
		else
		{
			mode=2;
		}
	}
	else if(argc==3)
	{
		if(strcmp(argv[1],"/h")==0)
		{
			if(strcmp(argv[2],"input.txt")!=0)
			{
				printf("file name not correct!\n");
				exit(0);
			}
			freopen_s(&fp,argv[2],"r",stdin);
			if(scanf_s("%d,\n%d,\n",&row,&col)!=2)
			{
				cout<<"hehe";
				printf("input row or col wrong!\n");
				exit(0);
			}
			mode=3;
		}
		else if(strcmp(argv[1],"/v")==0)
		{
			if(strcmp(argv[2],"input.txt")!=0)
			{
				printf("file name not correct!\n");
				exit(0);
			}
			freopen_s(&fp,argv[2],"r",stdin);
			if(scanf_s("%d,\n%d,\n",&row,&col)!=2)
			{
				printf("input row or col wrong!\n");
				exit(0);
			}
			mode=4;
		}
		else if(strcmp(argv[1],"/a")==0)
		{
			if(strcmp(argv[2],"input.txt")!=0)
			{
				printf("file name not correct!\n");
				exit(0);
			}
			freopen_s(&fp,argv[2],"r",stdin);
			if(scanf_s("%d,\n%d,\n",&row,&col)!=2)
			{
				printf("input row or col wrong!\n");
				exit(0);
			}
			mode=7;
		}
		else
		{
			printf("index wrong!\n");
			exit(0);
		}	
	}
	else if(argc==4)
	{
		if(strcmp(argv[1],"/v")==0)
		{
			if(strcmp(argv[2],"/h")==0)
			{
				if(strcmp(argv[3],"input.txt")!=0)
				{
					printf("file name wrong!\n");
					exit(0);
				}
				freopen_s(&fp,argv[3],"r",stdin);
				if(scanf_s("%d,\n%d,\n",&row,&col)!=2)
				{
					printf("input row or col wrong!\n");
					exit(0);
				}
				mode=5;
			}
			else
			{
				printf("index wrong!\n");
				exit(0);
			}
		}
		else if(strcmp(argv[1],"/h")==0)
		{
			if(strcmp(argv[2],"/v")==0)
			{
				if(strcmp(argv[3],"input.txt")!=0)
				{
					printf("file name wrong!\n");
					exit(0);
				}
				freopen_s(&fp,argv[3],"r",stdin);
				if(scanf_s("%d,\n%d,\n",&row,&col)!=2)
				{
					printf("input row or col wrong!\n");
					exit(0);
				}
				mode=5;
			}
			else
			{
				printf("index wrong!\n");
				exit(0);
			}
		}
		else
		{
			printf("index wrong!\n");
			exit(0);
		}
	}
	else if(argc==5)
	{
		if(strcmp(argv[1],"/v")==0)
		{
			if(strcmp(argv[2],"/h")==0)
			{
				if(strcmp(argv[3],"/a")==0)
				{
					if(strcmp(argv[4],"input.txt")!=0)
					{
						printf("file name wrong!\n");
						exit(0);
					}
					freopen_s(&fp,argv[4],"r",stdin);
					if(scanf_s("%d,\n%d,\n",&row,&col)!=2)
					{
						printf("input row or col wrong!\n");
						exit(0);
					}
					mode=6;
				}
				else
				{
					printf("index wrong!\n");
					exit(0);
				}
			}
			else
			{
				printf("index wrong!\n");
				exit(0);
			}
		}
		else
		{
			printf("index wrong!\n");
			exit(0);
		}
	}
	else
	{
		printf("too many indexes!\n");
		exit(0);
	}
	
}
void input1()//一维long long 数组的输入
{
	for(int i=1;i<col;i++)
	{
		if(scanf_s("%lld,",&num[i])!=1)
		{
			printf("input matrix wrong!\n");
			exit(0);
		}
	}
	if(scanf_s("%lld",&num[col])!=1)
	{
		printf("input matrix wrong!\n");
		exit(0);
	}
}
void maxsum1()//一维O(n)求最大子数组
{
	long long tempsum=num[1];
	long long ans=tempsum;
	for(int i=2;i<=col;i++)
	{
		tempsum=max(num[i],tempsum+num[i]);
		ans=max(tempsum,ans);
	}
	printf("%lld\n",ans);
}
void input2()//二维输入
{
	for(int i=1;i<=row;i++)
	{
		for(int j=1;j<col;j++)
		{
			if(scanf_s("%d,",&map[i][j])!=1)
			{
				printf("input matrix wrong!\n");
				exit(0);
			}
		}
		if(scanf_s("%d",&map[i][col])!=1)
		{
			printf("input matrix wrong!\n");
			exit(0);
		}
	}
}
void init2()//二维初始化sum[][],sum[i][j]表示i,j左上方的和
{
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=row;i++)
	{
		for(int j=1;j<=col;j++)
		{
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+map[i][j];
		}
	}
}
void input4()//这里我将上下联通的情况转换为左右联通,将矩阵转置
{
	for(int j=1;j<=col;j++)
	{
		for(int i=1;i<row;i++)
		{
			if(scanf_s("%d,",&map[i][j])!=1)
			{
				printf("input matrix wrong!\n");
				exit(0);
			}
		}
		if(scanf_s("%d",&map[row][j])!=1)
		{
			printf("input matrix wrong!\n");
			exit(0);
		}
	}
}		
int getsum(int x1,int y1,int x2,int y2)//根据x1和x2的大小关系区分联通和不联通分别求和
{
	if(x1<=x2)
	{
		return sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
	}
	else
	{
		return sum[row][y2]-sum[row][y1-1]-getsum(x2,y2,x1,y1)+map[x1][y1]+map[x2][y2];
	}
}
void maxsum2()//二维最大子数组O(n^3)
{
	init2();
	int tempans=map[1][1];
	int ans=tempans;
	for(int i=1;i<=row;i++)
	{
		for(int j=i;j<=row;j++)
		{
			tempans=getsum(i,1,j,1);
			for(int k=2;k<=col;k++)
			{
				tempans=max(getsum(i,k,j,k),tempans+getsum(i,k,j,k));
				ans=max(tempans,ans);
			}
		}
	}
	printf("%d\n",ans);
}
void maxsum3()//左右联通情况的最大子数组
{
	init2();
	int sum1=sum[1][1];
	int sum2=sum[1][1];
	int all=sum[1][1];
	int tempmin=sum[1][1];
	int tempmax=sum[1][1];
	int ans=sum[1][1];
	for(int i=1;i<=row;i++)
	{
		for(int j=i;j<=row;j++)
		{
			sum1=sum2=tempmin=tempmax=all=getsum(i,1,j,1);
			for(int k=2;k<=col;k++)
			{
				int temp=getsum(i,k,j,k);
				all+=temp;
				sum2=min(sum2+temp,temp);
				/*
				if(sum2<0)
				{
					sum2+=temp;
				}
				else
				{
					sum2=temp;
				}
				*/
				tempmin=min(tempmin,sum2);
				sum1=max(sum1+temp,temp);
				/*
				if(sum1>0)
				{
					sum1+=temp;
				}
				else
				{
					sum1=temp;
				}
				*/
				tempmax=max(tempmax,sum1);
			}
			ans=max(max(tempmax,all-tempmin),ans);
			if(tempmin==all)
			{
				ans=max(ans,tempmax);
			}
		}
	}
	printf("%d\n",ans);
}
void maxsum5()//游泳圈形状的最大子数组
{
	init2();
	int sum1=sum[1][1];
	int sum2=sum[1][1];
	int all=sum[1][1];
	int tempmin=sum[1][1];
	int tempmax=sum[1][1];
	int ans=sum[1][1];
	for(int i=1;i<=row;i++)
	{
		for(int j=1;j<=row;j++)
		{
			sum1=sum2=tempmin=tempmax=all=getsum(i,1,j,1);
			for(int k=2;k<=col;k++)
			{
				int temp=getsum(i,k,j,k);
				all+=temp;
				sum2=min(sum2+temp,temp);
				/*
				if(sum2<0)
				{
					sum2+=temp;
				}
				else
				{
					sum2=temp;
				}
				*/
				tempmin=min(tempmin,sum2);
				sum1=max(sum1+temp,temp);
				/*
				if(sum1>0)
				{
					sum1+=temp;
				}
				else
				{
					sum1=temp;
				}
				*/
				tempmax=max(tempmax,sum1);
			}
			ans=max(max(tempmax,all-tempmin),ans);
			if(tempmin==all)
			{
				ans=max(ans,tempmax);
			}
		}
	}
	printf("%d\n",ans);
	/*
	for(int i=1;i<=row;i++)
	{
		int len=(i>1?row-1:row);
		for(int j=i;j-i<len;j++)
		{
			int begin=1;
			int temp=0;
			for(int end=1;end<col*2&&begin<=col;end++)
			{
				if(end-begin>=col)
				{
					end=++begin;
					temp=0;
				}
				temp=max(0,temp+sum[j][end]-sum[i-1][end]);
				if(temp<=0)
				{
					begin=end+1;
				}
				if(temp>ans)
				{
					ans=temp;
				}
			}
		}
	}
	printf("%d\n",ans);
	*/
}
bool check(int x,int y)
{
	if(x<0||x>=row||y<0||y>=col)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void dfs(int x,int y,int choice)
{
	visit[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int tx=choice?(x+dx[i]+row)%row:x+dx[i];
		int ty=choice?(y+dy[i]+col)%col:y+dy[i];
		if(check(tx,ty)&&!visit[tx][ty]&&bit[tx][ty])
		{
			dfs(tx,ty,choice);
		}
	}
}
void anotherwork(int choice)
{
	int ans=-INF;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col-1;j++)
		{
			if(scanf_s("%d,",&map[i][j])!=1)
			{
				printf("input matrix wrong!\n");
				exit(0);
			}
		}
		if(scanf_s("%d",&map[i][col-1])!=1)
		{
			printf("input matrix wrong!\n");
			exit(0);
		}
	}
	int N=row*col;
	for(int i=0;i<(1<<N);i++)//枚举2^nm种状态 
	{
		for(int j=0;j<row;j++)
		{
			for(int k=0;k<col;k++)
			{
				visit[j][k]=0;
				bit[j][k]=0;
			}
		}
		for(int j=0;j<N;j++)
		{
			bit[j/col][j%col]=(i&(1<<j))>>j;
		}
		bool ok=true;
		for(int j=0;j<row;j++)
		{
			if(!ok)
			{
				break;
			}
			for(int k=0;k<col;k++)
			{
				if(bit[j][k])//找到第一个1点进行dfs标记该联通块 
				{
					dfs(j,k,choice);
					ok=false;
					break;
				}
			}
		}
		ok=true;
		for(int j=0;j<row;j++)
		{
			if(!ok)
			{
				break;
			}
			for(int k=0;k<col;k++)
			{
				if(bit[j][k]&&!visit[j][k])
				{
					ok=false;
					break;
				}
			}
		}
		int s=-INF;
		if(ok)
		{
			s=0;
			for(int j=0;j<row;j++)
			{
				for(int k=0;k<col;k++)
				{
					if(bit[j][k])
					{
						s+=map[j][k];
					}
				}
			}
			ans=max(ans,s);
		}
	}
	printf("%d\n",ans);
}
int main(int argc,char *argv[])
{
	getMode(argc,argv);
	if(mode==1)
	{
		input1();
		maxsum1();
	}
	else if(mode==2)
	{
		input2();
		maxsum2();
	}
	else if(mode==3)
	{
		input2();
		maxsum3();
	}
	else if(mode==4)
	{
		swap(col,row);
		input4();
		maxsum3();
	}
	else if(mode==5)
	{
		input2();
		maxsum5();
	}
	else if(mode==6)
	{
		anotherwork(1);
	}
	else if(mode==7)
	{
		anotherwork(0);
	}
	else
	{
		exit(0);
	}
	return 0;
}
	