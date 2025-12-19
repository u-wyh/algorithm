#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n;

struct node{
    int t,val;
};
node nums[MAXN];

bool cmp(node a,node b){
    if(a.t!=b.t){
        return a.t<b.t;
    }
    return a.val>b.val;
}

priority_queue<int,vector<int>,greater<int>>heap;

signed main()
{
    cin>>n;
    long long ans=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i].t>>nums[i].val;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        int t=nums[i].t;
        int val=nums[i].val;
        if(heap.size()<t){
            ans+=val;
            heap.push(val);
        }
        else if(heap.top()<val){
            ans-=heap.top();
            heap.pop();
            ans+=val;
            heap.push(val);
        }
    }
    cout<<ans<<endl;
    return 0;
}