
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n,x,y;
int a[MAXN],b[MAXN];

struct node{
    int pos,val;
};
node nums[MAXN<<1];
int cnt;

bool cmp(node a,node b){
    return a.pos<b.pos;
}

void add(int l,int r){
    if(l>=r) return;
    nums[++cnt]={l,1};
    nums[++cnt]={r,-1};
}

void solve(){
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }

    cnt=0;
    int mx=0;
    int sum=0;

    for(int i=1;i<=n;i++){
        int d=max(0LL,mx-a[i]);

        sum+=max(0LL,b[i]-d)*y;

        add(d,b[i]);

        mx=max(mx,a[i]+b[i]);
    }

    sort(nums+1,nums+cnt+1,cmp);

    int ans=sum;
    int now=0;
    int cover=0;

    for(int i=1;i<=cnt;){
        int pos=nums[i].pos;

        sum+=(pos-now)*(x-cover*y);
        ans=min(ans,sum);

        while(i<=cnt&&nums[i].pos==pos){
            cover+=nums[i].val;
            i++;
        }

        now=pos;
    }

    cout<<ans<<"\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
