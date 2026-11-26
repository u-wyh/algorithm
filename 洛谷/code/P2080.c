// https://www.luogu.com.cn/problem/P2080
// 题意：两人的好感值起初都是 0。
// 做第 i 件事会分别给两人增加 a_i、b_i，可以任选若干件。
// 要求两人的好感值之和至少为 v，求两者差的绝对值最小是多少，无解输出 -1。
// 数据范围：1 ≤ n ≤ 30，a_i 和 b_i 的绝对值都在 [1,100]，v 为正整数。

#include<stdio.h>
#include<math.h>

int n,m;
int a[35],b[35],ans=10000000;

int min(int a,int b){
    return a<b?a:b;
}

void dfs(int x,int A,int B){
    if(x>n){
        if((A+B)>=m)
            ans=min(ans,abs(A-B));
        return ;
    }
    dfs(x+1,A,B);
    dfs(x+1,A+a[x],B+b[x]);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&a[i],&b[i]);
    }
    dfs(1,0,0);
    if(ans==10000000)
        printf("-1\n");
    else
        printf("%d\n",ans);
    return 0;
}
