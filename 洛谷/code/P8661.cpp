// https://www.luogu.com.cn/problem/P8661
// 题意：输入 N, D, K 和 N 条记录 (ts, id)；
// 若某 id 在某个左闭右开时间区间 [T, T+D) 内出现至少 K 次，则按 id 从小到大逐行输出所有满足条件的 id。
// 数据范围：1 <= K <= N <= 10^5，0 <= id, ts <= 10^5（题面未单独标注 D 的上界）。
#include<bits/stdc++.h>
using namespace std;

int n,d,k;
struct tiezi{
    int ts,id;
}nums[100005];
int sz=0;
int ans[100005];
int q[100005],cnt[100005];

int cmp(tiezi a,tiezi b){
    return a.ts<b.ts;
}

int main()
{
    cin>>n>>d>>k;
    for(int i=0;i<n;i++)
        cin>>nums[i].ts>>nums[i].id;
    sort(nums,nums+n,cmp);
    int h=0,t=0;
    for(int i=0;i<n;i++){
        while(h<t&&nums[i].ts-nums[q[h]].ts>=d){
            cnt[nums[q[h]].id]--;
            h++;
        }
        q[t]=i;
        cnt[nums[i].id]++;
        if(cnt[nums[i].id]>=k)
            ans[sz++]=nums[i].id;
        t++;
    }
    sort(ans,ans+sz);
    cout<<ans[0]<<endl;
    for(int i=1;i<sz;i++){
        if(ans[i]!=ans[i-1])
            cout<<ans[i]<<endl;
    }
    return 0;
}
