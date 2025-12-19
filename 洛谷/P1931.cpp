#include <bits/stdc++.h>
using namespace std;
int const N=35;
map<string,int>mp;
double a[N][N];
int n;
void addEdge(char str1[],double x,char str2[]){
	string s1=str1;
	string s2=str2;
	int u,v;
	u=mp[s1];
	v=mp[s2];
	a[u][v]=x;
}
bool floyd(){
	int i,j,k;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(a[i][j]<a[i][k]*a[k][j]){
					a[i][j]=a[i][k]*a[k][j];
				}
			}
	for(int i=1;i<=n;i++){
		if(a[i][i]>1)
			return true;
	}
	return false;
}//以上部分已经解释过了
int main(){
	int m,i,j,count,t=0;
	double x;
	char str[20],str1[20],str2[20];
	while(scanf("%d",&n)&&n){
		count=0;
		mp.clear();
		getchar();
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++){
				if(i==j)
					a[i][j]=1;
				else
					a[i][j]=0;
			}
		for(i=0;i<n;i++){
			scanf("%s",str);
			string s=str;
			mp[s]=++count;//用来记录货币的种类数量
			//cout<<"mp[s]="<<mp[s]<<endl;
		}
		scanf("%d",&m);
		getchar();
		for(i=0;i<m;i++){
			scanf("%s%lf%s",str1,&x,str2);
			addEdge(str1,x,str2);//建图
		}
		if(floyd())//跑一遍Floyed，输出即可
			printf("Case %d: Yes\n",++t);
		else
			printf("Case %d: No\n",++t);
	}
	return 0;
}
