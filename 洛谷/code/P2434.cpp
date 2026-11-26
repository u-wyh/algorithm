// https://www.luogu.com.cn/problem/P2434
// 题意：给定 n 个闭区间 [a_i, b_i]，求它们的并集。
// 将并集表示为最少个数的不相交闭区间，按升序每行输出一个区间。
// 数据范围：3 <= n <= 50000，1 <= a_i <= b_i <= 10^6。
#include<bits/stdc++.h>
using namespace std;

int n;
struct range{
    long long l,r;
};

bool cmp(range a,range b){
    return a.l<b.l;
}

int main()
{
    cin>>n;
    range nums[n];
    for(int i=0;i<n;i++){
        cin>>nums[i].l>>nums[i].r;
    }
    sort(nums,nums+n,cmp);
    long long L=nums[0].l,R=nums[0].r;
    long long ans=0;
    ans+=R-L+1;
    for(int i=1;i<n;i++){
        if(nums[i].l>R){
            L=nums[i].l;
            R=nums[i].r;
            ans+=(R-L+1);
        }else{
            if(nums[i].r>R){
                L=R+1;
                R=nums[i].r;
                ans+=(R-L+1);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
