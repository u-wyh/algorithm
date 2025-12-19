#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e6+5;

int n,m;
int cnt;
int pos[MAXN];//记录符合要求的水晶位置
int dis[MAXN];//记录初始时目标水晶到目标点的距离
int tot;
int ans[MAXN];//记录输出顺序
int del[MAXN];//记录非目标的水晶位置


//线段树部分
int tree[MAXN<<2];//记录这个区间离可以结束的位置最近的距离
int tag[MAXN<<2];

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

void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=dis[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    tree[i]-=v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int l,int r,int i){
    if(l==r){
        tree[i]=1e9;//表示在也不会选到了
        return l;
    }
    else{
        int mid=(l+r)/2;
        down(i);
        int ans=0;
        if(!tree[i<<1|1]){
            //先找后面的在目标位置的
            ans=query(mid+1,r,i<<1|1);
        }
        else{
            ans=query(l,mid,i<<1);
        }
        up(i);//因为更新了一个节点
        return ans;
    }
}

int main()
{
    int p=1,sum=0;//p是当前点前面的最近目标点位置  sum只是用于完成del数组的填充
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int v=read();
        if((p<<1)==i){
            p=i;
        }
        if(v==m){
            //符合要求的
            pos[++cnt]=i;
            dis[cnt]=i-p;//新加一个符合要求的水晶
        }
        else{
            del[++sum]=i;
        }
    }
    build(1,cnt,1);
    sum=0;
    for(int i=1;i<=cnt;i++){
        //每次一定会减少一个目标  所以cnt次就一定可以
        if(tree[1]){
            tag[1]+=tree[1];//最近的那个距离是tree[1]  说明一定会至少一定这么多个
            //那么一定会将最前面的非目标水晶移除 因为如果前面不是非目标  那么距离就是0
            for(int j=1;j<=tree[1];j++){
                ans[++tot]=del[++sum];
            }
            tree[1]=0;
        }
        int x=query(1,cnt,1);
        ans[++tot]=pos[x];
        if(x<cnt){
            //表示在这个节点后面的节点前进一步
            update(x+1,cnt,1,1,cnt,1);
        }
    }
    cout<<tot<<endl;
    for(int i=1;i<=tot;i++){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
    return 0;
}
