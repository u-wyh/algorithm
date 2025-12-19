#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*130;

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
int addcnt;
int delcnt;

inline int lowbit(int x){
    return x&-x;
}

int find(int val){
    int l=1,r=m,ans=0;
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
        for(int i=1;i<=addcnt;i++){
            lt+=sum[ls[addtree[i]]];
        }
        for(int i=1;i<=delcnt;i++){
            lt-=sum[ls[deltree[i]]];
        }
        if(jobk<=lt){
            for(int i=1;i<=addcnt;i++){
                addtree[i]=ls[addtree[i]];
            }
            for(int i=1;i<=delcnt;i++){
                deltree[i]=ls[deltree[i]];
            }
            return inquery(jobk,l,mid);
        }
        else{
            for(int i=1;i<=addcnt;i++){
                addtree[i]=rs[addtree[i]];
            }
            for(int i=1;i<=delcnt;i++){
                deltree[i]=rs[deltree[i]];
            }
            return inquery(jobk-lt,mid+1,r);
        }
    }
}

void add(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        root[i]=inadd(val[x],v,1,m,root[i]);
    }
}

void update(int x,int y){
    add(x,-1);
    val[x]=find(y);
    add(x,1);
}

int getrank(int l,int r,int k){
    addcnt=delcnt=0;
    for(int i=r;i;i-=lowbit(i)){
        addtree[++addcnt]=root[i];
    }
    for(int i=l-1;i;i-=lowbit(i)){
        deltree[++delcnt]=root[i];
    }
    return arr[inquery(k,1,m)];
}

void prepare(){
    int len=0;
    for(int i=1;i<=n;i++){
        arr[++len]=val[i];
    }
    for(int i=1;i<=q;i++){
        if(ques[i][0]==2){
            arr[++len]=ques[i][2];
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
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    for(int i=1;i<=q;i++){
        char op;
        scanf(" %c %d %d",&op,&ques[i][1],&ques[i][2]);
        ques[i][0]=(op=='Q')?1:2;
        if(op=='Q'){
            scanf("%d",&ques[i][3]);
        }
    }
    prepare();
    for(int i=1;i<=q;i++){
        int op=ques[i][0];
        int x=ques[i][1];
        int y=ques[i][2];
        if(op==1){
            int z=ques[i][3];
            printf("%d\n",getrank(x,y,z));
        }
        else{
            update(x,y);
        }
    }
    return 0;
}