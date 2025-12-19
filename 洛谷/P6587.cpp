#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;
const int MAXT = MAXN*30;
const int BIT = 30;

int arr[MAXN];
int n,m,ans;

int cnt=1;
int tree[MAXT][2];
int lazy[MAXT];
int sum[MAXT];
int pass[MAXT];

//插入数组中下标为num的数字
void insert(int num){
    int cur=1;
    pass[1]++;
    sum[1]+=arr[num];
    for(int i=0;i<=BIT;i++){
        int path=(num>>i)&1;
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
        pass[cur]++;
        sum[cur]+=arr[num];
    }
}

//查询二进制的前x位和y一样的有几个
int querypass(int x,int y){
    int cur=1;
    for(int i=0;i<x;i++){
        int path=(y>>i)&1;
        cur=tree[cur][path];
    }
    return pass[cur];
}

void downlazy(int i,int v){
    if(i==0){
        return ;
    }
    lazy[i]+=v;
    sum[i]+=pass[i]*v;
}

void down(int i){
    if(i==0){
        return ;
    }
    if(lazy[i]){
        downlazy(tree[i][0],lazy[i]);
        downlazy(tree[i][1],lazy[i]);
        lazy[i]=0;
    }
}

//将二进制的前x位和y一样的节点  加上v*k  其中k是实际上会加上v的数字个数
void add(int x,int y,int k,int v){
    int cur=1;
    down(1);
    sum[1]+=v*k;
    for(int i=0;i<x;i++){
        int path=(y>>1)&1;
        cur=tree[cur][path];
        down(cur);
        sum[cur]+=v*k;
    }
    if(cur!=0){
        lazy[cur]+=v;
    }
}

int querysum(int x,int y){
    int cur=1;
    for(int i=0;i<x;i++){
        int path=(y>>i)&1;
        down(cur);
        cur=tree[cur][path];
    }
    return sum[cur];
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
    }
    for(int i=1;i<=n;i++){
        insert(i);
    }
    for(int i=1;i<=m;i++){
        int op;
        scanf("%d",&op);
        int u,v,w;
        op=(ans+op)%2+1;
        if(op==1){
            scanf("%d %d %d",&u,&v,&w);
            int k=querypass(u,v);
            add(u,v,k,w);
        }
        else{
            scanf("%d %d",&u,&v);
            ans=querysum(u,v);
            cout<<ans<<endl;
        }
    }
    return 0;
}
