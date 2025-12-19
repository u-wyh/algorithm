#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3500000;

int n,m;
int k[7],p[7];
int lsum[MAXN],lsize=0;
int rsum[MAXN],rsize=0;
int size=0;

inline int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans*=a;
        }
        b>>=1;
        a*=a;
    }
    return ans;
}

void dfs(int u,int st,int en,int sum,int *num){
    if(u==en+1){
        num[++size]=sum;
        return ;
    }
    for(int i=1;i<=m;i++){
        dfs(u+1,st,en,sum+k[u]*power(i,p[u]),num);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>k[i]>>p[i];
    }
    size=0;
    dfs(1,1,n/2,0,lsum);
    lsize=size;
    size=0;
    dfs(n/2+1,n/2+1,n,0,rsum);
    rsize=size;
    sort(lsum+1,lsum+lsize+1);
    sort(rsum+1,rsum+rsize+1);
    int ans=0;
    int last=0;
    int r=rsize;
    lsum[0]=lsum[1]+1;//表示他们不一样  防止偶然相同
    for(int i=1;i<=lsize;i++){
        if(lsum[i]==lsum[i-1]){
            ans+=last;
            continue;
        }
        last=0;
        while(r&&(lsum[i]+rsum[r]>=0)){
            if(lsum[i]+rsum[r]==0){
                last++;
            }
            r--;
        }
        ans+=last;
    }
    cout<<ans<<endl;
    return 0;
}