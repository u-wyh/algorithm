#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 505;
const int MOD = 1e9+7;

int n,m;
long long nums[MAXN];

long long pre[MAXB][MAXB];
long long suf[MAXB][MAXB];
long long sum[MAXB];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

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
        for(int j=bl[i];j<=br[i];j++){
            sum[i]+=nums[j];
        }
    }
}

void add(int x,int y,long long z){
    if(x<=blen){
        for(int i=y;i<=x;i++){
            pre[x][i]+=z;
        }
        for(int i=y;i>=1;i--){
            suf[x][i]+=z;
        }
    }
    else{
        for(int i=y;i<=n;i+=x){
            nums[i]+=z;
            sum[bi[i]]+=z;
        }
    }
}

long long querysum(int x,int y){
    int lb=bi[x],rb=bi[y];
    long long ans=0;
    if(lb==rb){
        for(int i=x;i<=y;i++){
            ans+=nums[i];
        }
    }
    else{
        for(int i=x;i<=br[lb];i++){
            ans+=nums[i];
        }
        for(int i=bl[rb];i<=y;i++){
            ans+=nums[i];
        }
        for(int i=lb+1;i<=rb-1;i++){
            ans+=sum[i];
        }
    }
    return ans;
}

long long query(int x,int y){
    long long ans=querysum(x,y);
    for(int i=1;i<=blen;i++){
        int lth=(x-1)/i+1;
        int rth=(y-1)/i+1;
        int cnt=rth-lth-1;
        if(lth==rth){
            ans=ans+pre[i][(y-1)%i+1]-pre[i][(x-1)%i];
        }   
        else{
            ans=ans+suf[i][(x-1)%i+1]+pre[i][(y-1)%i+1]+pre[i][i]*cnt;
        }
    }
    return ans%MOD;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    while(m--){
        int op,x,y,z;
        op=read(),x=read(),y=read();
        if(op==1){
            z=read();
            add(x,y,z);
        }
        else{
            printf("%lld\n",query(x,y));
        }
    }
    return 0;
}