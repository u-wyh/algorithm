#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;
const int LIMIT = 19;

int n,m,p;
int st[MAXN][LIMIT+1];
int t[LIMIT+1];
int fa[MAXN],sz[MAXN];

long long power(long long a,long long b,long long mod){
    long long ans=1;
    while(b>0){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;//a每次相当于倍增  只有b的这一位上有1的时候 才会将a乘进ans中
        b>>=1;//b想右移动一位
    }
    return ans;
}

int find(int i){
    return i==fa[i]?i:fa[i]=find(fa[i]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        sz[fy]+=sz[fx];
    }
}

signed main()
{
    cin>>n;
    p=log2(n);
    //cout<<p<<endl;
    for(int i=1;i<=n;i++){
        fa[i]=i,sz[i]=1;
    }
    for(int i=1;i<=n;i++){
        cin>>st[i][0];
        un(i,st[i][0]);
    }
    t[0]=1;
    for(int i=1;i<=p;i++){
        t[i]=t[i-1]*2;
    }
    for(int j=1;j<=p;j++){
        for(int i=1;i<=n;i++){
            st[i][j]=st[st[i][j-1]][j-1];
        }
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int s,t1,t2;
        cin>>s>>t1>>t2;
        int f=find(s);
        t1=power(t1,t2,sz[f]);
        int j=p;
        while(t1>0&&j>=0){
            if(t[j]>t1){
                j--;
            }
            else{
                t1-=t[j];
                s=st[s][j];
                j--;
            }
        }
        cout<<s<<endl;
    }
    return 0;
}
