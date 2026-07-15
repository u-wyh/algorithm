#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e4+5;
const int MAXM = 5e4+5;
const int MAXV = 1e5+5;
const int INF = 1e9;

int n,m,v;

struct node{
    int op,x,y,id;
};
int cnt;
node nums[MAXN*2+MAXM];
node tmp[MAXN*2+MAXM];

int pos[MAXN];

int cntq;
int ans[MAXN];
int limit[MAXN];

int tree[MAXV+MAXN];

bool cmp(node a,node b){
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int val){
    while(x<=m){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void merge(int l,int mid,int r){
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&tmp[p1+1].x<=tmp[p2].x){
            p1++;
            if(tmp[p1].op==1){
                add(tmp[p1].x+tmp[p1].y,1);
            }
        }
        if(tmp[p2].op==2){
            ans[tmp[p2].id]+=(query(min(m,limit[tmp[p2].id]+tmp[p2].x+tmp[p2].y))-query(max(1,tmp[p2].x+tmp[p2].y-limit[tmp[p2].id])-1));
        }
    }
    for(int i=l;i<=p1;i++){
        if(tmp[i].op==1){
            add(tmp[i].x+tmp[i].y,-1);
        }
    }
    sort(tmp+l,tmp+r+1,cmp);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

void to1(){
    for(int i=1;i<=cnt;i++){
        tmp[i]=nums[i];
    }
    cdq(1,cnt);
}

void to2(){
    for(int i=1;i<=cnt;i++){
        tmp[i]=nums[i];
        tmp[i].x=n+1-tmp[i].x;
    }
    cdq(1,cnt);
}

void to3(){
    for(int i=1;i<=cnt;i++){
        tmp[i]=nums[i];
        tmp[i].y=v-tmp[i].y;
        tmp[i].x=n+1-tmp[i].x;
    }
    cdq(1,cnt);
}

void to4(){
    for(int i=1;i<=cnt;i++){
        tmp[i]=nums[i];
        tmp[i].y=v-tmp[i].y;
    }
    cdq(1,cnt);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>pos[i];
        nums[++cnt]={1,i,pos[i],0};
        v=max(pos[i],v);
    }
    for(int i=1;i<=m;i++){
        string op;
        int x,k;
        cin>>op>>x>>k;
        if(op[0]=='Q'){
            nums[++cnt]={2,x,pos[x],++cntq};
            limit[cntq]=k;
        }
        else{
            nums[++cnt]={1,x,k,0};
            pos[x]=k;
            v=max(v,k);
        }
    }
    v++;
    m=v+n+1;
    to1();
    to2();
    to3();
    to4();
    for(int i=1;i<=cntq;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}