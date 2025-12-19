#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

struct node{
    int val,id;
}nums[MAXN];
int tree[MAXN];
int n;

bool cmp(node a,node b){
    if(a.val!=b.val){
        return a.val<b.val;
    }
    else{
        return a.id<b.id;
    }
}

bool cmp1(node a,node b){
    return a.id<b.id;
}

// 树状数组模板代码，无需修改
void add(int i) {
    while (i <= n) {
        tree[i] ++;
        i += i & -i;
    }
}

// 树状数组模板代码，无需修改
int sum(int i) {
    int ans = 0;
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
        cin>>nums[i].val;
        nums[i].id=i;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        nums[i].val=i;
    }
    sort(nums+1,nums+n+1,cmp1);
    int ans=1;
    for(int i=1;i<=n;i++){
        add(nums[i].val);
        int k=i-sum(i);
        //cout<<i<<' '<<k<<endl;
        ans=max(ans,k);
    }
    cout<<ans<<endl;
    return 0;
}
