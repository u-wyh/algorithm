// https://www.luogu.com.cn/problem/P1114
// 题意：给长度为 n 的 01 序列，0 表示女生，1 表示男生。找人数相等的最长连续区间，输出长度，找不到就输出 0。
// 数据范围：1 ≤ n ≤ 10^5，元素只可能为 0 或 1。
// 算法标签：前缀和

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int main()
{
    int n;
    cin>>n;
    int nums[n+1];
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        if(nums[i]==0){
            nums[i]=-1;
        }
    }
    map<int ,int >m;
    m[0]=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        nums[i]+=nums[i-1];
        auto it=m.find(nums[i]);
        if(it!=m.end()){
            ans=max(ans,i- it->second );
        }
        else{
            m[nums[i]]=i;
        }
    }
    cout<<ans;
    return 0;
}
