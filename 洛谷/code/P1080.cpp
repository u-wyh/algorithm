// https://www.luogu.com.cn/problem/P1080
// 题意：国王固定站队首，后面 n 名大臣可以重排。每人的奖励是前面所有人的左手数乘积除以自己右手数后向下取整。求重排后最大个人奖励能降到多少。
// 数据范围：1 ≤ n ≤ 1000，所有左手数、右手数均在 [1,9999]。

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
