#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int dp[105][1][2][3][4][5][6][7][8];
//dp[i][a1][a2][a3][a4][a5][a6][a7][a8]：第 p 位，且上一个 x 到第 p 位的距离为 ax 时，填的方案个数
int n;
bool b[10];

int dfs(int p,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8){
	//cout<<p<<" "<<a1<<" "<<a2<<" "<<a3<<" "<<a4<<" "<<a5<<" "<<a6<<" "<<a7<<" "<<a8<<endl;
	if(dp[p][a1][a2][a3][a4][a5][a6][a7][a8]!=-1)
        return dp[p][a1][a2][a3][a4][a5][a6][a7][a8];
	if(p==n+1)
        return 1;
	//枚举这一位填的数
	int ans=0;
	int a[10]={0,a1+1,a2+1,a3+1,a4+1,a5+1,a6+1,a7+1,a8+1};//到 i+1 的距离
	for(int i=1;i<=8;i++){
        if(b[i]){
            if(a[i]==i){//可以填 i
                int tmp=a[i];
                a[i]=0;//方便下一行
                ans+=dfs(p+1,min(a[1],0),min(a[2],1),min(a[3],2),min(a[4],3),
                             min(a[5],4),min(a[6],5),min(a[7],6),min(a[8],7));
                ans%=mod;
                a[i]=tmp;//还原
            }
        }
    }
	return dp[p][a1][a2][a3][a4][a5][a6][a7][a8]=ans;
}

int main()
{
	memset(dp,-1,sizeof(dp));
	int m;
	cin>>n>>m;
	while(m--){
		int x;
		cin>>x;
		b[x]=1;
	}
	cout<<dfs(1,0,1,2,3,4,5,6,7);
	return 0;
}
