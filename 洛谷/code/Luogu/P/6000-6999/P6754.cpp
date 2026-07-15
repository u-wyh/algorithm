#include<bits/stdc++.h>
using namespace std;
#define int long long

int f[20][11][11][2][2];
int nums[20];
int len;

int dfs(int x,int pp,int p,int free,int lead){
    if(x==0){
        return 1;
    }
    if(f[x][pp][p][free][lead]!=-1){
        return f[x][pp][p][free][lead];
    }
    int ans=0;
    int up=free?9:nums[x];
    for(int i=0;i<=up;i++){
        if(i!=pp&&i!=p){
            ans+=dfs(x-1,p,(i||lead)?i:10,free||i<nums[x],lead||i);
        }
    }
    f[x][pp][p][free][lead]=ans;
    return ans;
}

int compute(int x){
    if(x<0){
        return 0;
    }
    len=0;
    while(x){
        nums[++len]=x%10;
        x/=10;
    }
    memset(f,-1,sizeof(f));
    return dfs(len,10,10,0,0);
}

signed main()
{
    int l,r;
    cin>>l>>r;
    cout<<(compute(r)-compute(l-1))<<endl;
    return 0;
}