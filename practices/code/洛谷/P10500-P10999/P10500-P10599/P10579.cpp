// https://www.luogu.com.cn/problem/P10579
// 题意：给长为 n 的数组 s 和三个数 a,b,c。
// 找连续区间 [L,R]，要求区间和严格大于 a×(b×R-c×L)，
// 输出符合要求的最大区间长度。
// 数据范围：1 ≤ n ≤ 3 × 10^5，
// 1 ≤ a,b,c ≤ 1000，s[i] 的绝对值不超过 10^9，保证有解。
// 难度评分：1300（洛谷分级换算）
// 算法标签：二分答案、前缀和

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;

int n,a,b,c;
int nums[MAXN];

bool check(int limit){
    for(int i=limit;i<=n;i++){
        if(nums[i]-nums[i-limit]>a*(b*i-c*(i-limit+1))){
            return true;
        }
    }
    return false;
}

signed main()
{
    cin>>n>>a>>b>>c;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]+=nums[i-1];
    }
    int l=0,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}