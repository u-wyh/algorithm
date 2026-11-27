// https://www.luogu.com.cn/problem/P3286
// 题意：
// 给定一行三个整数 L, R, K。
// 位置 i 处的人面前第 j 堆石子数量等于 i 写成 K 进制后的第 j
// 位数字。
// 需把位置在 [L, R] 内的每个人的石子各自合并成一堆。
// 每次将某人某堆的若干石子移到另一堆，代价为石子数乘移动距离。
// 输出所有人合并石子的最小总代价。
// 数据范围：
// 1 <= L <= R <= 10^15
// 2 <= K <= 20
// 算法标签：数位动态规划、记忆化搜索
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXH = 70;

int x,y,k;
int nums[MAXH];
int len;
int f[MAXH][7000][2];

int dfs(int x,int sum,int p,int free){
    if(sum<0){
        // 因为如果继续向下遍历的话  那么sum只会变得更小
        return 0;
    }
    if(x==0){
        return sum;
    }
    if(f[x][sum][free]!=-1){
        return f[x][sum][free];
    }
    int ans=0;
    int up=free?k-1:nums[x];
    for(int i=0;i<=up;i++){
        if(p==1){
            // 最初的时候 我们将所有的数字全部合并到最右边 也就是最低位
            ans+=dfs(x-1,sum+x*i-i,p,free||i<nums[x]);
        }
        else{
            if(x<p){
                // 目前合并位置左移  也就是往高位移动  那么右边的距离增加
                ans+=dfs(x-1,sum-i,p,free||i<nums[x]);
            }
            else{
                // 目前合并位置左移  也就是往高位移动  那么左边的距离减少
                ans+=dfs(x-1,sum+i,p,free||i<nums[x]);
            }
        }
    }
    f[x][sum][free]=ans;
    return ans;
}

int compute(int x){
    if(x==0){
        return 0;
    }
    len=0;
    while(x){
        nums[++len]=x%k;
        x/=k;
    }
    int ans=0;
    for(int i=1;i<=len;i++){
        memset(f,-1,sizeof(f));
        if(i==1){
            ans+=dfs(len,0,i,0);
        }
        else{
            ans-=dfs(len,0,i,0);
        }
    }
    return ans;
}

signed main()
{
    cin>>x>>y>>k;
    cout<<(compute(y)-compute(x-1))<<endl;
    return 0;
}