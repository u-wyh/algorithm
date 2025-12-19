#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+1;
const int MAXT = MAXN*230;

int n,q,m;
int ques[MAXN][4];
int arr[MAXN];

int root[MAXN<<2];
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
int lazy[MAXT];
int cnt;

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

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void prepare(){
    int len=0;
    for(int i=1;i<=q;i++){
        if(ques[i][0]==1){
            arr[++len]=ques[i][3];
        }
    }
    sort(arr+1,arr+len+1);
    m=1;
    for(int i=2;i<=len;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=q;i++){
        if(ques[i][0]==1){
            ques[i][3]=find(ques[i][3]);
        }
    }
}

void up(int i){
    sum[i]=sum[ls[i]]+sum[rs[i]];
}

void down(int i,int ln,int rn){
    if(lazy[i]){
        if(!ls[i]){
            ls[i]=++cnt;
        }
        if(!rs[i]){
            rs[i]=++cnt;
        }
        sum[ls[i]]+=1ll*ln*lazy[i];
        sum[rs[i]]+=1ll*rn*lazy[i];
        lazy[ls[i]]+=lazy[i];
        lazy[rs[i]]+=lazy[i];
        lazy[i]=0;
    }
}

int inadd(int jobl,int jobr,int l,int r,int i){
    if(!i){
        i=++cnt;
    }
    if(jobl<=l&&r<=jobr){
        sum[i]+=(r-l+1);
        lazy[i]++;
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid){
            ls[i]=inadd(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            rs[i]=inadd(jobl,jobr,mid+1,r,rs[i]);
        }
        up(i);
    }
    return i;
}

long long inquery(int jobl,int jobr,int l,int r,int i){
    if(!i){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        long long ans=0;
        if(jobl<=mid){
            ans+=inquery(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=inquery(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

void outadd(int pos,int jobl,int jobr,int l,int r,int i){
    root[i]=inadd(jobl,jobr,1,n,root[i]);
    if(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            outadd(pos,jobl,jobr,l,mid,i<<1);
        }
        else{
            outadd(pos,jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

int outquery(int val,int jobl,int jobr,int l,int r,int i){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        long long rt=inquery(jobl,jobr,1,n,root[i<<1|1]);
        if(rt>=val){
            return outquery(val,jobl,jobr,mid+1,r,i<<1|1);
        }
        else{
            return outquery(val-rt,jobl,jobr,l,mid,i<<1);
        }
    }
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=q;i++){
        for(int j=0;j<4;j++){
            ques[i][j]=read();
        }
    }
    prepare();
    for(int i=1;i<=q;i++){
        if(ques[i][0]==1){
            outadd(ques[i][3],ques[i][1],ques[i][2],1,m,1);
        }
        else{
            int val=outquery(ques[i][3],ques[i][1],ques[i][2],1,m,1);
            printf("%d\n",arr[val]);
        }
    }
    return 0;
}