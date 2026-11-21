// https://www.luogu.com.cn/problem/P1691
#include<bits/stdc++.h>
using namespace std;
#define int long long
using i127 = __int128_t;
const int MAXN = 2e3+5;

int n;
struct node{
    int l,r,y,w;
};
node nums[MAXN];

struct Event{
    int p,q,val;
};
Event event[MAXN<<1];
int cnte;

int ans;

bool cmp(Event a,Event b){
    int c=a.p*b.q-a.q*b.p;
    if(c){
        return c<0;
    }
    return a.val>b.val;
}

void compute(int x,int y,int id){
    cnte=0;
    int now=nums[id].w;
    ans=max(now,ans);
    for(int i=1;i<=n;i++){
        if(i==id|| nums[i].y==y){
            continue;
        }

        int dy=nums[i].y-y;
        int p1=nums[i].l-x;
        int p2=nums[i].r-x;
        if(dy<0){
            dy=-dy;
            p1=-p1;
            p2=-p2;
        }
        if(p1>p2){
            swap(p1,p2);
        }
        event[++cnte]={p1,dy,nums[i].w};
        event[++cnte]={p2,dy,-nums[i].w};
    }
    sort(event+1,event+cnte+1,cmp);
    for(int i=1;i<=cnte;i++){
        now+=event[i].val;
        ans=max(ans,now);
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r>>nums[i].y;
        if(nums[i].l>nums[i].r){
            swap(nums[i].l,nums[i].r);
        }
        nums[i].w=nums[i].r-nums[i].l;
    }
    for(int i=1;i<=n;i++){
        compute(nums[i].l,nums[i].y,i);
        compute(nums[i].r,nums[i].y,i);
    }
    cout<<ans<<endl;
    return 0;
}