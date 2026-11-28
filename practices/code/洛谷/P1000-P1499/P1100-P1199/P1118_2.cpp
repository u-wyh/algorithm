// https://www.luogu.com.cn/problem/P1118
// 题意：第一排是 1 到 N 的一个排列。
// 从下一排开始，每项是上一排相邻两项的和，反复直到只剩一个数。
// 已知最后的数，构造第一排，若有多解输出字典序最小者。
// 数据范围：1 ≤ N ≤ 12，1 ≤ 最终和 ≤ 12345。
// 难度评分：1300（洛谷分级换算）
// 算法标签：深度优先搜索、剪枝、数学

#include <cstdio>
using namespace std;

int n,sum;
int visited[25]={0};
int ans[25];
int pc[25];

int dfs(int i,int num,int v){
    if (v>sum)
        return 0;
    if (i==n){
        if (v==sum){
            ans[i]=num;
            return 1;
        }
        else
            return 0;
    }
    visited[num]=1;
    for (int j=1;j<=n;j++){
        if (!visited[j] && dfs(i+1,j,v+pc[i]*j)){
            ans[i]=num;
            return 1;
        }
    }
    visited[num]=0;
    return 0;
}

int main(void){
    scanf("%d%d",&n,&sum);
    //下面构造杨辉三角(即组合数表)
    pc[0]=pc[n-1]=1; //杨辉三角性质,两边都是1
    if (n>1)
        for (int i=1;i*2<n;i++)
            pc[i]=pc[n-1-i]=(n-i)*pc[i-1]/i; //利用杨辉三角对称性和组合数公式计算
    //下面枚举计算
    if (dfs(0,0,0)) //0 仅起占位符作用
        for (int i=1;i<=n;i++)
            printf("%d ",ans[i]); //输出答案
    return 0;
}
