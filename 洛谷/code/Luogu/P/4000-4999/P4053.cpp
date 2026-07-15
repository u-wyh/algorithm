#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 150005;

int n;
struct node{
    int t1,t2;
};
node nums[MAXN];
priority_queue<int,vector<int>>heap;
int t,ans;

bool cmp(node a,node b){
    return a.t2<b.t2;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].t1>>nums[i].t2;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        if(t+nums[i].t1<=nums[i].t2){
            t+=nums[i].t1;
            ans++;
            heap.push(nums[i].t1);
            continue;
        }
        if(!heap.empty()){
            int maxx=heap.top();
            if(maxx>nums[i].t1){
                if(t-maxx+nums[i].t1<=nums[i].t2){
                    heap.pop();
                    t=t-maxx+nums[i].t1;
                    heap.push(nums[i].t1);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}