// https://www.luogu.com.cn/problem/P2436
// 题意：T 组数据，
// 表由 A 位神犇与 B
// 位蒟蒻间隔循环构成（1..A 神犇，A+1..A+B 蒟蒻...）。
// 给定 N 名神犇和 M 名蒟蒻的编号，
// 求满足条件的 A, B（优先 A 最小，其次 B 最小）。
// 每组输出 A B，无解输出 NO。
// 数据范围：1 <= T <= 10，1 <= N, M <= 1000，
// 编号 <= 10*(N+M)。
// 算法标签：深度优先搜索、剪枝
#include<bits/stdc++.h>
using namespace std;
#define MAX 1005

int n,m;
int a[MAX],b[MAX];
int ansa,ansb;
int maxans;

void dfs(int x,int y){
    if(x+y>maxans){
        return ;
    }
    int i=1;
    while(i<=n){
        if((a[i]%(x+y))>x||(a[i]%(x+y))==0){
            dfs(x+1,y);
            dfs(x+1,y+1);
            dfs(x,y+1);
            break;
        }
        i++;
    }
    if(i==n+1){
        i=1;
        while(i<=m){
            if((b[i]%(x+y))<x&&(b[i]%(x+y))!=0){
                dfs(x+1,y);
                dfs(x+1,y+1);
                dfs(x,y+1);
                break;
            }
            i++;
        }
    }
    if(i==m+1){
        if(x<=ansa){
            ansa=x;
            ansb=min(y,ansb);
        }
    }
}

int main()
{
    while(scanf("%d %d",&n,&m)==2){
        memset(a,-1,sizeof(a));
        memset(b,-1,sizeof(b));
        maxans=0;
        ansa=1e9,ansb=1e9;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=m;i++){
            scanf("%d",&b[i]);
        }
        maxans=a[1]+b[1];
        dfs(1,1);
        if(ansa==-1&&ansb==-1){
            printf("No\n");
        }else{
            printf("%d %d\n",ansa,ansb);
        }
    }
    return 0;
}
