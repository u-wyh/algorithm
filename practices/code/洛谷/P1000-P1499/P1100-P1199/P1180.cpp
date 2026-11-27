// https://www.luogu.com.cn/problem/P1180
// 题意：给出全程距离、油箱容量、每升续航、起点加满的费用，以及沿路各站位置和油价。
// 出发时满油，每次停站都加满并花 20 元吃饭。
// 剩油至少一半且能到下一站或终点时不能停。
// 求最低总费用，按题意把每次油费四舍五入到 0.1 元。
// 数据范围：1 ≤ n ≤ 50，加油站按距起点距离递增，位置不超过终点。
// 算法标签：深度优先搜索、剪枝

#include<bits/stdc++.h>
using namespace std;

double dis,maxn,s1,money,ans;
int n;
double s[55],d[55];

void dfs(int now,double oil,double paid){
    if(paid>ans)
        return ;
    if(now==n+1){
        ans=min(ans,paid);
        return ;
    }
    if(oil*s1>=s[now+1]-s[now]){
        if(oil*2>maxn){
            dfs(now+1,oil-(s[now+1]-s[now])/s1,paid);
        }else{
            dfs(now+1,maxn-(s[now+1]-s[now])/s1,paid+(maxn-oil)*d[now]+20);
            dfs(now+1,oil-(s[now+1]-s[now])/s1,paid);
        }
    }else{
        dfs(now+1,maxn-(s[now+1]-s[now])/s1,paid+(maxn-oil)*d[now]+20);
    }
}

int main()
{
    cin>>dis>>maxn>>s1>>money;
    ans=money;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i]>>d[i];
        ans+=20+maxn*d[i];
    }
    s[n+1]=dis;
    dfs(1,maxn-s[1]/s1,money);
    printf("%.1lf\n",ans);
    return 0;
}
