#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXT = MAXN*160;
const int INF = INT_MAX;

int n,q,m;
int val[MAXN];
int ques[MAXN][4];
int arr[MAXN<<1];

int root[MAXN];
int sum[MAXT];
int ls[MAXT];
int rs[MAXT];
int cnt;

int addtree[MAXN];
int deltree[MAXN];
int cntadd;
int cntdel;

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

inline int lowbit(int x){
    return x&-x;
}

int inadd(int pos,int jobv,int l,int r,int i){
    if(i==0){
        i=++cnt;
    }
    if(l==r){
        sum[i]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[i]=inadd(pos,jobv,l,mid,ls[i]);
        }
        else{
            rs[i]=inadd(pos,jobv,mid+1,r,rs[i]);
        }
        sum[i]=sum[ls[i]]+sum[rs[i]];
    }
    return i;
}

int inquery(int jobk,int l,int r){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int lt=0;
        for(int i=1;i<=cntadd;i++){
            lt+=sum[ls[addtree[i]]];
        }
        for(int i=1;i<=cntdel;i++){
            lt-=sum[ls[deltree[i]]];
        }
        if(lt>=jobk){
            for(int i=1;i<=cntadd;i++){
                addtree[i]=ls[addtree[i]];
            }
            for(int i=1;i<=cntdel;i++){
                deltree[i]=ls[deltree[i]];
            }
            return inquery(jobk,l,mid);
        }
        else{
            for(int i=1;i<=cntadd;i++){
                addtree[i]=rs[addtree[i]];
            }
            for(int i=1;i<=cntdel;i++){
                deltree[i]=rs[deltree[i]];
            }
            return inquery(jobk-lt,mid+1,r);
        }
    }
}

int insmall(int jobv,int l,int r){
    if(l==r){
        return 0;
    }
    else{
        int mid=(l+r)>>1;
        if(jobv<=mid){
            for(int i=1;i<=cntadd;i++){
                addtree[i]=ls[addtree[i]];
            }
            for(int i=1;i<=cntdel;i++){
                deltree[i]=ls[deltree[i]];
            }
            return insmall(jobv,l,mid);
        }
        else{
            int lt=0;
            for(int i=1;i<=cntadd;i++){
                lt+=sum[ls[addtree[i]]];
                addtree[i]=rs[addtree[i]];
            }
            for(int i=1;i<=cntdel;i++){
                lt-=sum[ls[deltree[i]]];
                deltree[i]=rs[deltree[i]];
            }
            return lt+insmall(jobv,mid+1,r);
        }
    }
}

void add(int i,int cnt){
    for(int j=i;j<=n;j+=lowbit(j)){
        root[j]=inadd(val[i],cnt,1,m,root[j]);
    }
}

void update(int pos,int v){
    add(pos,-1);
    val[pos]=find(v);
    add(pos,1);
}

int small(int l,int r,int val){
    cntadd=0;
    cntdel=0;
    for(int i=r;i;i-=lowbit(i)){
        addtree[++cntadd]=root[i];
    }
    for(int i=l-1;i;i-=lowbit(i)){
        deltree[++cntdel]=root[i];
    }
    return insmall(val,1,m);
}

int getrank(int l,int r,int k){
    cntadd=0;
    cntdel=0;
    for(int i=r;i;i-=lowbit(i)){
        addtree[++cntadd]=root[i];
    }
    for(int i=l-1;i;i-=lowbit(i)){
        deltree[++cntdel]=root[i];
    }
    return arr[inquery(k,1,m)];
}

int pre(int l,int r,int val){
    int rank=small(l,r,val)+1;
    if(rank==1){
        return -INF;
    }
    return getrank(l,r,rank-1);
}

int post(int l,int r,int val){
    if(val==m){
        return INF;
    }
    int sml=small(l,r,val+1);
    if(sml==r-l+1){
        return INF;
    }
    return getrank(l,r,sml+1);
}

void prepare(){
    int len=0;
    for(int i=1;i<=n;i++){
        arr[++len]=val[i];
    }
    for(int i=1;i<=q;i++){
        if(ques[i][0]==3){
            arr[++len]=ques[i][2];
        }
        else if(ques[i][0]!=2){
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
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
        add(i,1);
    }
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=q;i++){
        ques[i][0]=read(),ques[i][1]=read(),ques[i][2]=read();
        if(ques[i][0]!=3){
            ques[i][3]=read();
        }
    }
    prepare();
    for(int i=1;i<=q;i++){
        int op=ques[i][0];
        int x=ques[i][1];
        int y=ques[i][2];
        if(op==3){
            update(x,y);
        }
        else{
            int z=ques[i][3];
            if(op==1){
                printf("%d\n",small(x,y,find(z))+1);
            }
            else if(op==2){
                printf("%d\n",getrank(x,y,z));
            }
            else if(op==4){
                printf("%d\n",pre(x,y,find(z)));
            }
            else{
                printf("%d\n",post(x,y,find(z)));
            }
        }
    }
    return 0;
}