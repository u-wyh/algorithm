#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9+1;
const int MAXN = 1e5+5;
const int MAXH = 20;

int n,q,p;
int val[MAXN];

int lt[MAXN],rt[MAXN];
long long fl[MAXN],fr[MAXN];
long long gl[MAXN],gr[MAXN];
int sta[MAXN];
int top;
int f[MAXN][MAXH];
int g[MAXN][MAXH];

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

void prepare(){
    val[0]=-INF;
    val[n+1]=-INF;

    sta[++top]=0;
    for(int i=1;i<=n;i++){
        while(top&&val[sta[top]]>=val[i]){
            top--;
        }
        lt[i]=sta[top];
        sta[++top]=i;
    }
    
    top=0;
    sta[++top]=n+1;
    for(int i=n;i>=1;i--){
        while(top&&val[sta[top]]>=val[i]){
            top--;
        }
        rt[i]=sta[top];
        sta[++top]=i;
    }
    
    for(int i=1;i<=n;i++){
        fl[i]=fl[lt[i]]+1ll*val[i]*(i-lt[i]);
    }
    for(int i=n;i>=1;i--){
        fr[i]=fr[rt[i]]+1ll*val[i]*(rt[i]-i);
    }

    for(int i=1;i<=n;i++){
        gl[i]=gl[i-1]+fl[i];
    }
    for(int i=n;i>=1;i--){
        gr[i]=gr[i+1]+fr[i];
    }

    for(int i=1;i<=n;i++){
        f[i][0]=val[i];
        g[i][0]=i;
    }

    for(int j=1;j<=p;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            int mid=i+(1<<(j-1));
            if(f[i][j-1]<f[mid][j-1]){
                f[i][j]=f[i][j-1];
                g[i][j]=g[i][j-1];
            }
            else{
                f[i][j]=f[mid][j-1];
                g[i][j]=g[mid][j-1];
            }
        }
    }
}

int query(int l,int r){
    int k=log2(r-l+1);
    int mid=r-(1<<k)+1;
    if(f[l][k]<f[mid][k]){
        return g[l][k];
    }
    else{
        return g[mid][k];
    }
}

int main()
{
    n=read(),q=read();
    p=log2(n)+1;
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    prepare();

    while(q--){
        int l,r;
        l=read(),r=read();
        int pos=query(l,r);
        long long ans=0;
        ans=1ll*val[pos]*(pos-l+1)*(r-pos+1);
        ans+=gl[r]-gl[pos]-fl[pos]*(r-pos);
        ans+=gr[l]-gr[pos]-fr[pos]*(pos-l);
        printf("%lld\n",ans);
    }
    return 0;
}