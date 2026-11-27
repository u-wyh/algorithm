// https://www.luogu.com.cn/problem/P4053
// 题意：第一行输入受损建筑数 N，接下来 N 行每行输入修理第 i 个建筑所需时间 T_1 和其报废截止时间 T_2。
// 只有一个修理工人，每次只能修一个建筑且不能中断，必须在 T_2 秒内修完才算抢修成功。
// 输出最多可抢修成功的建筑数量 S。
// 数据范围：对于 100% 的数据，1 <= N < 150000，1 <= T_1 < T_2 < 2^{31}。
#include<bits/stdc++.h>
// 算法标签：反悔贪心、优先队列
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