#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 1e3+5;

int n,m;
int nums[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int f[MAXN];
int g[MAXN];

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
    for(int i=n;i>=1;i--){
        int nxt=i+nums[i];
        if(nxt>n){
            f[i]=1;
            g[i]=n+1;
        }
        else if(nxt>br[bi[i]]){
            f[i]=1;
            g[i]=nxt;
        }
        else{
            f[i]=f[nxt]+1;
            g[i]=g[nxt];
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    m=read();
    while(m--){
        int op,pos,val;
        op=read(),pos=read();
        pos++;
        if(op==1){
            int ans=0;
            while(pos<=n){
                ans+=f[pos];
                pos=g[pos];
            }
            printf("%d\n",ans);
        }
        else{
            val=read();
            nums[pos]=val;
            for(int i=br[bi[pos]];i>=bl[bi[pos]];i--){
                int nxt=i+nums[i];
                if(nxt>n){
                    f[i]=1;
                    g[i]=n+1;
                }
                else if(nxt>br[bi[i]]){
                    f[i]=1;
                    g[i]=nxt;
                }
                else{
                    f[i]=f[nxt]+1;
                    g[i]=g[nxt];
                }
            }
        }
    }
    return 0;
}