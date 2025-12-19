#include<stdio.h>
#include<string.h>

#define MAXN 26
#define MAXM 16

int n,need[MAXN],now[MAXN];
int m,vitamin[MAXM][MAXN],ans;

void dfs(int u,int v){
    if(v>=ans)
        return ;
    //结束条件  如果选的饲料种数比目前的ans还要大，那么必然不对
    if(u>m){
        int i;
        for (i = 1; i <= n; i++) {
            if (now[i] < need[i]) {
                return ;
            }
        }
        ans=v;
        //如果已经u>m了  说明没有可以选择得了   那么判断目前选择的饲料能否满足题目要求
        //如果可以  ans=v  否则退出
    }
    dfs(u+1,v);//表示不选u这一种饲料
    for(int i=1;i<=n;i++){
        now[i]+=vitamin[u][i];
    }
    dfs(u+1,v+1);//表示选择这一种饲料
    for(int i=1;i<=n;i++){
        now[i]-=vitamin[u][i];
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&need[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&vitamin[i][j]);
        }
    }
    //我的数组下标都是从1开始的

    ans=m;
    //先把ans设置为最大的  ans=m的时候一定可以实现题目要求
    //在dfs中进行比较ans是否有更好的答案
    memset(now,0,sizeof(now));
    //全部实现初始化
    dfs(1,0);
    //dfs(u,v)的含义是目前到了第u种饲料，已经选择了v种
    //dfs(1,0)就是最初的状态  即：现在是第1中饲料   已经选择的是0种
    printf("%d\n",ans);
    return 0;
}
