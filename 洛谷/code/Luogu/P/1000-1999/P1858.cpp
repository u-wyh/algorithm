#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXV = 5005;
const int MAXK = 55;

int m,v,n;
int f[MAXV][MAXK];
int tmp[MAXK];
int val[MAXN],cost[MAXN];

int main()
{
    cin>>m>>v>>n;
    memset(f,128,sizeof(f));//初始化为比较小值
    for(int i=1;i<=n;i++){
        cin>>cost[i]>>val[i];
    }
    f[0][1]=0;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=cost[i];j--){
            int t1=1,t2=1,len=0;
            while(t1+t2<=m+1){
                if (f[j][t1]>f[j-cost[i]][t2]+val[i])
                    tmp[++len]=f[j][t1++];
                else
                    tmp[++len]=f[j-cost[i]][t2++]+val[i];
            }
            for(int k=1;k<=m;k++){
                f[j][k]=tmp[k];
            }
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        ans+=f[v][i];
    }
    cout<<ans<<endl;
    return 0;
}
