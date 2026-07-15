#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,m;
int nums[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

long long pre[MAXB];
long long suf[MAXB];
long long all[MAXB];
long long sum[MAXB];
long long tag[MAXB];

long long anspre;
long long anssuf;
long long ansall;
long long anssum;
long long anstag;

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

void buildblock(int i){
    int l=bl[i],r=br[i];
    tag[i]=-1;//初始化为全1
    sum[i]=all[i]=suf[i]=pre[i]=0;

    long long cur=0;
    for(int j=l;j<=r;j++){
        sum[i]+=nums[j];
        tag[i]&=nums[j];
        cur+=nums[j];
        if(cur>pre[i]){
            pre[i]=cur;
        }
    }

    cur=0;
    for(int j=r;j>=l;j--){
        cur+=nums[j];
        if(cur>suf[i]){
            suf[i]=cur;
        }
    }

    cur=0;
    for(int j=l;j<=r;j++){
        cur+=nums[j];
        if(cur<0){
            cur=0;
        }
        if(all[i]<cur){
            all[i]=cur;
        }
    }
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
    for(int i=1;i<=bnum;i++){
        buildblock(i);
    }
}

void update(int l,int r,int k){
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        for(int i=l;i<=r;i++){
            nums[i]|=k;
        }
        buildblock(lb);
    }
    else{
        for(int i=l;i<=br[lb];i++){
            nums[i]|=k;
        }
        buildblock(lb);
        for(int i=bl[rb];i<=r;i++){
            nums[i]|=k;
        }
        buildblock(rb);
        for(int i=lb+1;i<rb;i++){
            if((tag[i]&k)!=k){
                for(int j=bl[i];j<=br[i];j++){
                    nums[j]|=k;
                }
                buildblock(i);
            }
        }
    }
}

long long query(int l,int r){
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        long long ans=0,cur=0;
        for(int i=l;i<=r;i++){
            cur+=nums[i];
            if(cur<0){
                cur=0;
            }
            if(ans<cur){
                ans=cur;
            }
        }
        return ans;
    }
    else{
        long long ans=0,cur=0,tmp=0,suffix=0;

        for(int i=l;i<=br[lb];i++){
            cur+=nums[i];
            if(cur<0){
                cur=0;
            }
            if(ans<cur){
                ans=cur;
            }
        }
        for(int i=br[lb];i>=l;i--){
            tmp+=nums[i];
            if(suffix<tmp){
                suffix=tmp;
            }
        }

        for(int i=lb+1;i<rb;i++){
            if(ans<all[i]){
                ans=all[i];
            }
            if(ans<suffix+pre[i]){
                ans=suffix+pre[i];
            }

            if(suffix+sum[i]>suf[i]){
                suffix+=sum[i];
            }
            else{
                suffix=suf[i];
            }
        }

        cur=0;
        for(int i=bl[rb];i<=r;i++){
            cur+=nums[i];
            if(cur<0){
                cur=0;
            }
            if(ans<cur){
                ans=cur;
            }
            suffix+=nums[i];
            if(ans<suffix){
                ans=suffix;
            }
        }

        return ans;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    while(m--){
        int op,l,r,k;
        op=read(),l=read(),r=read();
        if(op==1){
            cout<<query(l,r)<<endl;
        }
        else{
            k=read();
            update(l,r,k);
        }
    }
    return 0;
}