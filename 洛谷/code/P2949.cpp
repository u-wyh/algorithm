// https://www.luogu.com.cn/problem/P2949
// 题意：输入工作总数 N，以及每项工作的截止时间 D_i 和利润 P_i。
// 工作从时间 0 开始，每项工作只需消耗 1 个时间单位且同一单位时间只能做一项；
// 当前时间为 t 时，仅当 D_i > t 才能做工作 i，完成后时间变为 t+1 并获得 P_i 利润。
// 在总时长 10^9 单位内挑选工作并安排顺序，使总利润最大化（可能超出 32 位整数范围）。
// 输出一个整数，表示能获得的最大总利润。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，1 <= D_i <= 10^9，1 <= P_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：贪心、反悔贪心、优先队列
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