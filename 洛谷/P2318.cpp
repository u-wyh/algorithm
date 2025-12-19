#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 1e6+5;

int n,m;
struct node{
    int val;//记录值
    int sub;//记录位置
    int time;//记录最早进入时间
    int visit;//记录访问次数
}tree[MAXN<<4];
map<int,int>pos;//记录该页最后出现的位置
int cnt;

void up(int i){
    if(tree[i<<1].visit<tree[i<<1|1].visit||(tree[i<<1].visit==tree[i<<1|1].visit&&tree[i<<1].time<tree[i<<1|1].time)){
        tree[i].val=tree[i<<1].val;
        tree[i].sub=tree[i<<1].sub;
        tree[i].visit=tree[i<<1].visit;
        tree[i].time=tree[i<<1].time;
    }
    else{
        tree[i].val=tree[i<<1|1].val;
        tree[i].sub=tree[i<<1|1].sub;
        tree[i].visit=tree[i<<1|1].visit;
        tree[i].time=tree[i<<1|1].time;
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].val=INT_MAX;
        tree[i].sub=0;
        tree[i].visit=INT_MAX;
        tree[i].time=0;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
    up(i);
}

void update(int pos,int time,int val,int l,int r,int i){
    if(l==r){
        tree[i].time=time;
        tree[i].val=val;
        tree[i].visit=1;
        tree[i].sub=pos;
    }
    else{
        int mid=(l+r)/2;
        if(mid>=pos){
            update(pos,time,val,l,mid,i<<1);
            up(i);
        }
        else{
            update(pos,time,val,mid+1,r,i<<1|1);
            up(i);
        }
    }
}

void query(int time,int val){
    pos[val]=tree[1].sub;
    update(tree[1].sub,time,val,1,n,1);
}

bool find(int pos,int jobv,int l,int r,int i){
    if(l==r){
        if(tree[i].val==jobv){
            tree[i].visit++;
            return true;
        }
        return false;
    }
    int mid=(l+r)/2;
    if(mid>=pos){
        if(find(pos,jobv,l,mid,i<<1)){
            up(i);
            return true;
        }
    }
    else{
        if(find(pos,jobv,mid+1,r,i<<1|1)){
            up(i);
            return true;
        }
    }
    return false;
}

int main()
{
    int ans=0;
    cin>>n>>m;
    cnt=n;
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        if(pos[x]!=0&&find(pos[x],x,1,n,1)){
            //表示第一种情况
            ans++;
        }
        else if(pos[x]==0&&cnt>0){
            //第二种情况
            update(n-cnt+1,i,x,1,n,1);
            pos[x]=n-cnt+1;
            cnt--;
        }
        else{
            query(i,x);
        }
    }
    cout<<ans<<endl;
    return 0;
}
