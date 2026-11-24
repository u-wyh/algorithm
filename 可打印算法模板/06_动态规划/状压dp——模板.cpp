// 用途：判断先后从 1..n 取不同数字、累计到目标值的游戏中先手能否获胜。
// 时间：O(n2^n)。
// 空间：O(2^n)。
// 注意：使用第 1..n 位表示可选数字，n 不能超过 20。
// 例题：https://leetcode.cn/problems/can-i-win/
// 题意：轮流从 1..n 取未用数字，累计先到目标值者获胜，判先手胜负。
// 思路：用位集表示已取数字，记忆化搜索是否存在让对手必败的选择。
#include<bits/stdc++.h>
using namespace std;

int n,m;
int dp[1<<21];//表示在i的状态下 如今的先手可不可以赢

// 如果1~7范围的数字都能选，那么status的状态为：
// 1 1 1 1 1 1 1 1
// 7 6 5 4 3 2 1 0
// 0位弃而不用
// 如果1~7范围的数字，4、2已经选了不能再选，那么status的状态为：
// 1 1 1 0 1 0 1 1
// 7 6 5 4 3 2 1 0
// 0位弃而不用
// f的含义 :
// 数字范围1~n，当前的先手，面对status给定的数字状态
// 在累加和还剩rest的情况下
// 返回当前的先手能不能赢，能赢返回true，不能赢返回false
bool f(int status, int rest) {
    if(rest<=0)
        return false;
    if(dp[status]!=0)
        return dp[status]==1;
    bool ans=false;
    for(int i=1;i<=n;i++){
        if((status & (1<<i)) != 0 && !f(status^(1<<i),rest-i)){
            //表示当前这意味的数字可以选 并且选了之后的状况使得 如今的后手输（即下一轮的先手）
            ans=true;
            break;
        }
    }
    dp[status]=ans?1:-1;
    return ans;
}

bool canIWin() {
    if (m == 0) {
        // 来自题目规定
        return true;
    }
    if (n * (n + 1) / 2 < m) {
        // 如果1~n数字全加起来
        // 累加和和是n * (n+1) / 2，都小于m
        // 那么不会有赢家，也就意味着先手不会获胜
        return false;
    }
    // dp[status] == 0 代表没算过
    // dp[status] == 1 算过，答案是true
    // dp[status] == -1 算过，答案是false
    return f((1<<(n+1))-1,m);
}

int main()
{
    cin>>n>>m;
    if(canIWin()){
        cout<<"yes"<<endl;
    }
    else
        cout<<"no"<<endl;
    return 0;
}
