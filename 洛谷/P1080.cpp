#include<bits/stdc++.h>
using namespace std;

int n;
long long a,b;
struct node{
    int l,r,v;
}nums[1005];

bool cmp(node a,node b){
    return a.v<b.v;
}

int main()
{
    cin>>n;
    cin>>a>>b;
    b=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].v=nums[i].l*nums[i].r;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        b=max(a/nums[i].r,b);
        a*=nums[i].l;
    }
    cout<<b<<endl;
    return 0;
}
