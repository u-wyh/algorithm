#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
typedef long long ll;

struct node{
    ll voi,dis,id;
}nums[MAXN];
ll tree[MAXN];
ll tree1[MAXN];
ll n,m=1;

bool cmp(node a,node b){
    return a.voi<b.voi;
}

bool cmp1(node a,node b){
    return a.dis<b.dis;
}

void add(ll *tree,ll i, ll c) {
    while (i <= m) {
        tree[i] += c;
        i += i & -i;
    }
}

ll sum(ll *tree,ll i) {
    ll ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= i & -i;
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].voi>>nums[i].dis;
    }
    sort(nums+1,nums+n+1,cmp1);
    nums[1].id=1;
    for(int i=2;i<=n;i++){
        if(nums[i].dis!=nums[i-1].dis){
            ++m;
        }
        nums[i].id=m;
    }
    //cout<<' '<<m<<endl;
    sort(nums+1,nums+n+1,cmp);
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].voi<<' '<<nums[i].dis<<' '<<nums[i].id<<endl;
//    }
//    cout<<endl;
    ll ans=0;
    for(int i=1;i<=n;i++){
        ll k1=sum(tree1,nums[i].id-1);
        ll k2=sum(tree,nums[i].id-1);
        ll k3=sum(tree,m);
        ll k4=i-1-k1;
        //cout<<k1<<' '<<k2<<' '<<k3<<' '<<k4<<' ';
        ans+=nums[i].voi*(nums[i].dis*k1-k2+ k3-k2-nums[i].dis*k4);
        add(tree,nums[i].id,nums[i].dis);
        add(tree1,nums[i].id,1);
        //cout<<i<<' '<<ans<<endl;
    }
    cout<<ans<<endl;
    return 0;
}
