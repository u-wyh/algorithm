// https://www.luogu.com.cn/problem/P7866
// 题意：给定从两副不含大小王的扑克牌中取出的 n
// 张牌（每张以花色 S/H/C/D + 点数 A,2..9,T,J,Q,K 表示）
// 。
// 每次可从剩余牌中取走 3 张点数相同且花色恰好有 2 种的牌（取走后不可再用），
// 求最多能组成的组数。
// 第一行输入 n，接下来 n 行每行一张牌。
// 输出一行一个整数。
// 数据范围：1 <= n <= 10^4，输入的牌均存在于两副无大小王的扑克牌中。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、排序
#include<bits/stdc++.h>
using namespace std;

struct node{
    char u,v;
}nums[110];
int n;

bool cmp(node a,node b){
    return a.v==b.v?a.u<b.u:a.v<b.v;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].u>>nums[i].v;
    }
    sort(nums+1,nums+n+1,cmp);
    int u=0,v=0,ans=0;
    for(int i=1;i<=n+1;i++){
        if(nums[i].v==nums[i-1].v){
            u++;
            if(nums[i].u==nums[i-1].u){
                v++;
            }
        }
        else{
            //cout<<u<<' '<<v<<endl;
            int k=u-2*v;
            if(k>v){
                ans+=v;
            }
            else{
                ans+=(k+(v-(u-2*v))*2/3);
            }
            u=1,v=0;
        }
    }
    cout<<ans<<endl;
    return 0;
}
