#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXH = 40;

int n,m,q;
int f[MAXN][MAXH];
int pre[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool check(int u,int step){
    int j=0;
    while(step){
        if(step&1){
            u=f[u][j];
        }
        j++;
        step>>=1;
    }
    return u==m+1;
}

int compute(int k){
    int all=min(n-m+1,n-k+1);//总共洗牌次数
    int st=max(1ll,m-k+1);//最后一次洗牌之后的位置 即最终位置

    if(!check(st,all-1)){
        int u=st;
        for(int i=30;i>=0;i--){
            if((all-1)&(1<<i)){
                u=f[u][i];
            }
        }
        return pre[u];
    }

    int l=1,r=all-1,res=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(st,mid)){
            res=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return all-res+m;
}

signed main()
{
    int p=log2(987654321)+1;
    cout<<p<<endl;
    n=read(),m=read(),q=read();
    for(int i=1;i<=m;i++){
        int u=read();
        pre[u]=i;
    }
    pre[m+1]=m;
    for(int i=1;i<=m+1;i++){
        f[i][0]=pre[i]+1;
    }
    for(int i=1;i<=30;i++){
        for(int j=1;j<=m+1;j++){
            f[j][i]=f[f[j][i-1]][i-1];
        }
    }
    while(q--){
        int u=read();
        cout<<compute(u)<<endl;
        // cout<<' '<<compute(u)<<endl;
    }
    return 0;
}