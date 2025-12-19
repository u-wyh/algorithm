#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250005;
const int MAXB = 505;
const int MAXM = MAXB*2;

int n,q,m;
int army[MAXN];
int bel[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int op[MAXN];
int ql[MAXN];
int qr[MAXN];
int qx[MAXN];
int qy[MAXN];

int cnt;
int fa[MAXN];
int f[MAXM];
int sz[MAXM];
int col[MAXM];
long long tag[MAXM];
long long sum;

long long ans[MAXN];

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
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
}

void compute(int l,int r){
    for(int i=1;i<=m;i++){
        fa[i]=0;
    }
    for(int i=l;i<=r;i++){
        tag[i-l+1]=army[i];
        col[i-l+1]=bel[i];
    }
    int len=r-l+1;
    sum=0;
    for(int i=len+1;i<=cnt;i++){
        f[i]=0;
        tag[i]=0;
    }
    cnt=len;
    for(int i=1;i<=len;i++){
        f[i]=0;
        sum+=tag[i];
        sz[i]=1;
    }
    for(int i=1;i<=len;i++){
        if(!fa[col[i]]){
            fa[col[i]]=i;
        }
        else{
            int u=fa[col[i]];
            if(u<=len){
                ++cnt;
                fa[col[i]]=cnt;
                f[u]=cnt;
                u=cnt;
                sz[cnt]=1;
                col[cnt]=col[i];
            }
            f[i]=u;
            ++sz[u];
        }
    }

    for(int i=1;i<=q;i++){
        if(ql[i]>r||qr[i]<l){
            continue;
        }
        if(ql[i]<=l&&r<=qr[i]){
            if(op[i]==1){
                if(qx[i]==qy[i]||!fa[qx[i]]){
                    continue;
                }
                else if(!fa[qy[i]]){
                    col[fa[qx[i]]]=qy[i];
                    fa[qy[i]]=fa[qx[i]];
                    fa[qx[i]]=0;
                }
                else{
                    int u=++cnt;
                    f[fa[qx[i]]]=u;
                    f[fa[qy[i]]]=u;
                    col[u]=qy[i];
                    sz[u]=sz[fa[qx[i]]]+sz[fa[qy[i]]];
                    fa[qy[i]]=u;
                    fa[qx[i]]=0;
                }
            }
            else if(op[i]==2){
                if(fa[qx[i]]){
                    tag[fa[qx[i]]]+=qy[i];
                    sum+=1ll*qy[i]*sz[fa[qx[i]]];
                }
            }
            else{
                ans[i]+=sum;
            }
        }
        else{
            for(int u=cnt;u;u--){
                if(f[u]){
                    tag[u]+=tag[f[u]];
                    col[u]=col[f[u]];
                }
            }
            for(int u=len+1;u<=cnt;u++){
                tag[u]=0,f[u]=0;
            }
            cnt=len;
            for(int j=1;j<=len;j++){
                fa[col[j]]=0;
                f[j]=0;
            }
            int lt=max(ql[i],l)-l+1;
            int rt=min(qr[i],r)-l+1;
            if(op[i]==1){
                for(int u=lt;u<=rt;u++){
                    if(col[u]==qx[i]){
                        col[u]=qy[i];
                    }
                }
            }
            else if(op[i]==2){
                for(int u=lt;u<=rt;u++){
                    if(col[u]==qx[i]){
                        sum+=qy[i];
                        tag[u]+=qy[i];
                    }
                }
            }
            else{
                for(int u=lt;u<=rt;u++){
                    ans[i]+=tag[u];
                }
            }

            for(int p=1;p<=len;p++){
                if(!fa[col[p]]){
                    fa[col[p]]=p;
                }
                else{
                    int u=fa[col[p]];
                    if(u<=len){
                        ++cnt;
                        fa[col[p]]=cnt;
                        f[u]=cnt;
                        u=cnt;
                        sz[cnt]=1;
                        col[cnt]=col[p];
                    }
                    f[p]=u;
                    ++sz[u];
                }
            }
        }
    }
}

int main()
{
    n=read(),q=read(),m=read();
    for(int i=1;i<=n;i++){
        army[i]=read();
    }
    for(int i=1;i<=n;i++){
        bel[i]=read();
    }
    for(int i=1;i<=q;i++){
        op[i]=read(),ql[i]=read(),qr[i]=read();
        if(op[i]!=3){
            qx[i]=read(),qy[i]=read();
        }
    }
    prepare();
    for(int i=1;i<=bnum;i++){
        compute(bl[i],br[i]);
    }
    for(int i=1;i<=q;i++){
        if(op[i]==3){
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}