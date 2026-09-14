#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int INF = 1e9;

int n;
int shift,limit;

struct node{
    int x,y,id;
};
node nums[MAXN];
node lt[MAXN];
node rt[MAXN];

int tree[MAXN<<1];
int dp[MAXN];

int lowbit(int x){
    return x&-x;
}

void update(int x,int v){
    while(x<=limit){
        tree[x]=max(tree[x],v);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=-INF;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

void clear(int x){
    while(x<=limit){
        tree[x]=-INF;
        x+=lowbit(x);
    }
}

bool cmp(node &a,node &b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

void merge(int l,int mid,int r){
    int cntl=0;
    int cntr=0;

    for(int i=l;i<=mid;i++){
        lt[++cntl]=nums[i];
    }
    for(int i=mid+1;i<=r;i++){
        rt[++cntr]=nums[i];
    }

    sort(lt+1,lt+cntl+1,cmp);
    sort(rt+1,rt+cntr+1,cmp);

    int p=1;
    for(int i=1;i<=cntr;i++){
        while(p<=cntl&&lt[p].x<=rt[i].x){
            int id=lt[p].id;
            update(lt[p].y,dp[id]-id);
            p++;
        }

        int best=query(rt[i].y);

        if(best!=-INF){
            int id=rt[i].id;
            dp[id]=max(dp[id],best+id);
        }
    }

    for(int i=1;i<p;i++){
        clear(lt[i].y);
    }
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    merge(l,mid,r);
    for(int i=mid+1;i<=r;i++){
        dp[i]=max(dp[i],dp[i-1]);
    }
    cdq(mid+1,r);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    shift=n+2;
    limit=2*n+5;

    nums[0]={shift,shift,0};
    int sumr=0,sumb=0,sumy=0;
    for(int i=1;i<=n;i++){
        int r,y,b;
        cin>>r>>y>>b;
        sumr+=r;
        sumy+=y;
        sumb+=b;

        nums[i]={sumr-sumy+shift,sumr-sumb+shift,i};
    }

    for(int i=0;i<=limit;i++){
        tree[i]=-INF;
    }
    for(int i=0;i<=n;i++){
        dp[i]=-INF;
    }
    dp[0]=0;

    cdq(0,n);

    cout<<dp[n]<<endl;
    return 0;
}
/*
10
1 0 0
0 1 1
0 1 1
1 1 0
0 1 1
1 0 1
0 1 0
0 1 1
1 1 1
1 0 1
*/