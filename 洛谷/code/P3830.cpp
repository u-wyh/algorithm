// https://www.luogu.com.cn/problem/P3830
// 题意：输入一行两个正整数 q 和 n，表示问题编号及目标叶结点个数。
// 从只有根节点的二叉树开始，每次等概率随机选择一个当前叶结点展开（添上左右两个子结点），重复直至共有 n 个叶结点（根节点深度为 0）。
// 若 q = 1，输出叶结点平均深度的数学期望；若 q = 2，输出树深度的数学期望，均保留 6 位小数。
// 数据范围：q in {1, 2}，2 <= n <= 100。
#include<bits/stdc++.h>
// 算法标签：概率动态规划、期望
using namespace std;
const int MAXN = 105;

int op,n;
double dp[MAXN][MAXN];

double solve1(){
    double result=0;
    for(int i=2;i<=n;i++){
        result+=2.0/i;
    }
    return result;
}

double solve2(){
    if(n==1){
        return 0;
    }
    for(int i=1;i<=n;i++){
        dp[i][0]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            double sum=0;
            for(int k=1;k<i;k++){
                sum+=dp[k][j-1]+dp[i-k][j-1]-dp[k][j-1]*dp[i-k][j-1];
            }
            dp[i][j]+=sum/(i-1);
        }
    }
    double res=0;
    for(int j=1;j<n;j++){
        res+=dp[n][j];
    }
    return res;
}

int main()
{
    cin>>op>>n;
    double ans;
    if(op==1){
        ans=solve1();
    }
    else{
        ans=solve2();
    }
    printf("%.6lf\n",ans);
    return 0;
}