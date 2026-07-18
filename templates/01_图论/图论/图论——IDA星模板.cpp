//https://acm.hdu.edu.cn/showproblem.php?pid=1560
//https://www.cnblogs.com/LuckyGlass-blog/p/9061081.html
//IDA*实际上可以看成是 dfs的A*算法  即增强了吸引力
//关键是怎么求预测函数  以及怎么样的预测函数最好
//D()为当前深度；令A[i],C[i],G[i],T[i]方便表示ACGT在第i个序列中未匹配的序列里的个数，则启发函数
//G()=max(A[])+max(G[])+max(C[])+max(T[])
//（比如未匹配序列为"ACA","GG","ACG",则max A[]=2,max G[]=2,max C[]=1,所以G()=5）
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

int n,depth;
int len[10];
int chr[10][4];//统计词频
int mat[10];//表示这些字符串目前来到的位置
char DNA[10][10];

//这个函数是用于估计限度的
inline int GetPri(){
	int ret=0;
	for(int j=0;j<4;j++){
		int Max=0;
		for(int i=0;i<n;i++)
			Max=max(Max,chr[i][j]);
		ret+=Max;
	}
	return ret;
}

bool ID_A_Star(int dep)
{
	int pri=GetPri();
	if(dep+pri>depth)
        return false;
	if(!pri){
        //表示所有任务都完成  返回true
		return true;
    }
	for(int i=0;i<4;i++){
		char ch=i+'0';
        bool chg[10]={};//这是回溯标志
        bool flag=true;
		for(int j=0;j<n;j++){
			if(DNA[j][mat[j]]==ch){
				chr[j][DNA[j][mat[j]]-'0']--;//表示这个字符串的这个字母减少1
				mat[j]++;//这个字符串指针右移一位
				chg[j]=true;//用于标记 准备回溯
				flag=false;//表示这个有效果
			}
		}
		if(!flag){
            //如果有效果  那么这个位置就是当前i的字母  继续向下搜
            //如果没有效果 说明这个位置在已有的基础上是没有作用的  是不应该的
			if(ID_A_Star(dep+1)){
				return true;
			}
		}
		if(!flag){
			//复原操作  只有操作了才有必要复原
			for(int j=0;j<n;j++){
				if(chg[j]){
					mat[j]--,chr[j][DNA[j][mat[j]]-'0']++;
				}
			}
		}
	}
	return false;
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		memset(DNA,'\0',sizeof DNA);
		memset(chr,0,sizeof chr);
		memset(len,0,sizeof len);
		memset(mat,0,sizeof mat);
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%s",DNA[i]);
			len[i]=strlen(DNA[i]);
			for(int j=0;j<len[i];j++){
				switch(DNA[i][j]){
					//将字符改成1 2 3 4  并增加相应词频
					case 'A': DNA[i][j]='0';chr[i][0]++;break;
					case 'C': DNA[i][j]='1';chr[i][1]++;break;
					case 'G': DNA[i][j]='2';chr[i][2]++;break;
					case 'T': DNA[i][j]='3';chr[i][3]++;break;
				}
			}
		}
		depth=GetPri();//作为最初的深度判断
		while(!ID_A_Star(0)){
			memset(mat,0,sizeof mat);
			depth++;
			//当前深度不够 需要加一
		}
		printf("%d\n",depth);
	}
	return 0;
}
