#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 15;
const long long INF = 1e18;

int n,k;

struct node{
    int len;
    int d[MAXM];
    int val;
};
node nums[MAXN];

struct state{
    long long cost;
    int x,y;
};
struct compare{
    bool operator()(const state&a,const state&b){
        return a.cost>b.cost;
    }
};
priority_queue<state,vector<state>,compare>heap;

bool cmp(node a,node b){
    return a.val<b.val;
}

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

int main()
{
    n=read(),k=read();
    long long base=0;
    for(int i=1;i<=n;i++){
        nums[i].len=read();
        for(int j=1;j<=nums[i].len;j++){
            nums[i].d[j]=read();
        }
        sort(nums[i].d+1,nums[i].d+nums[i].len+1);
        nums[i].d[nums[i].len+1]=1e9;
        nums[i].val=nums[i].d[2]-nums[i].d[1];
        base+=nums[i].d[1];
    }
    if(k==1){
        cout<<base<<endl;
        return 0;
    }
    sort(nums+1,nums+n+1,cmp);
    long long all=base;
    heap.push({base+nums[1].d[2]-nums[1].d[1],1,2});
    for(int i=1;i<k;i++){
        state tmp=heap.top();
        heap.pop();
        all+=tmp.cost;

        int x=tmp.x;
        int y=tmp.y;
        if(y+1<=nums[x].len){
            long long now=tmp.cost-nums[x].d[y]+nums[x].d[y+1];
            heap.push({now,x,y+1});
        }
        if(x+1<=n&&nums[x+1].len>=2){
            long long now=tmp.cost-nums[x+1].d[1]+nums[x+1].d[2];
            heap.push({now,x+1,2});
        }
        if(y==2&&x+1<=n&&nums[x+1].len>=2){
            long long now=tmp.cost-nums[x].d[2]+nums[x].d[1]+nums[x+1].d[2]-nums[x+1].d[1];
            heap.push({now,x+1,2});
        }
    }
    cout<<all<<endl;
    return 0;
}