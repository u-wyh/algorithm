#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 2e3+5;

int n,q;
int val[MAXN];
int num[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];
int cnt[MAXB][101];
int maxval[MAXB];
int minval[MAXB];

long long preval[MAXN];
long long prenum[MAXN];

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
    blen=100;
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        maxval[i]=0;
        minval[i]=100;
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=1;i<=n;i++){
        preval[i]=preval[i-1]+1ll*val[i]*num[i];
        prenum[i]=prenum[i-1]+num[i];
        cnt[bi[i]][val[i]]+=num[i];
        maxval[bi[i]]=max(val[i],maxval[bi[i]]);
        minval[bi[i]]=min(val[i],minval[bi[i]]);
    }
    for(int i=1;i<=bnum;i++){
        for(int j=1;j<=100;j++){
            cnt[i][j]+=cnt[i-1][j];
        }
    }
}

void average(int l,int r){
    long long ans1=preval[r]-preval[l-1];
    long long ans2=prenum[r]-prenum[l-1];
    printf("%.2lf\n",1.0*ans1/ans2);
}

long long t[101];
void mode(int l,int r){
    for(int i=1;i<=100;i++){
        t[i]=0;
    }
    int ans1=0;
    long long ans2=0;
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        for(int i=l;i<=r;i++){
            t[val[i]]+=num[i];
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            t[val[i]]+=num[i];
        }
        for(int i=bl[rb];i<=r;i++){
            t[val[i]]+=num[i];
        }
        for(int i=1;i<=100;i++){
            t[i]+=(cnt[rb-1][i]-cnt[lb][i]);
        }
    }
    for(int i=1;i<=100;i++){
        if(t[i]>ans2){
            ans1=i;
            ans2=t[i];
        }
    }
    printf("%d\n",ans1);
}

void maxmin(int l,int r){
    int maxx=0,minn=100;
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        for(int i=l;i<=r;i++){
            maxx=max(maxx,val[i]);
            minn=min(minn,val[i]);
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            maxx=max(maxx,val[i]);
            minn=min(minn,val[i]);
        }
        for(int i=bl[rb];i<=r;i++){
            maxx=max(maxx,val[i]);
            minn=min(minn,val[i]);
        }
        for(int i=lb+1;i<rb;i++){
            maxx=max(maxx,maxval[i]);
            minn=min(minn,minval[i]);
        }
    }
    printf("%d\n",maxx-minn);
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        num[i]=read();
    }
    prepare();
    while(q--){
        int op,l,r;
        op=read(),l=read(),r=read();
        if(op==1){
            average(l,r);
        }
        else if(op==2){
            mode(l,r);
        }
        else{
            maxmin(l,r);
        }
    }
    return 0;
}