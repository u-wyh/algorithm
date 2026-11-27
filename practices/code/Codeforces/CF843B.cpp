// https://codeforces.com/problemset/problem/843/B
// 题意：交互题。给一条值严格递增的单链表，
// 已知节点数 n、头节点编号 start 和目标 x。
// 询问 ? i 得到节点 i 的值和后继编号，末尾返回 -1。
// 至多询问 1999 次。
// 输出：用 ! ans 报告不小于 x 的最小值，无则为 -1。
// 数据范围：1 <= n <= 5*10^4，
// 1 <= start, i <= n。
// 0 <= x, value_i <= 10^9。
// 后继编号为 -1 或 1 到 n。
// 算法标签：随机采样、链表遍历
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int val[MAXN];
bool vis[MAXN];
int n,st,x;

mt19937 rng(time(0));

int main()
{
    scanf("%d %d %d",&n,&st,&x);
    if(n<2000){
        int ans=2e9;
        for(int i=1;i<=n;i++){
            printf("? %d\n",i);
            fflush(stdout);
            int val,nxt;
            scanf("%d %d",&val,&nxt);
            if(val>=x){
                ans=min(ans,val);
            }
        }
        if(ans==2e9){
            ans=-1;
        }
        printf("! %d",ans);
        fflush(stdout);
    }
    else{
        int cnt=0;
        while(cnt<=1000){
            val[++cnt]=rng()%n+1;
            if(vis[val[cnt]]){
                cnt--;
            }
        }
        int p=st,ans=0;
        for(int i=1;i<=1000;i++){
            printf("? %d\n",val[i]);
            fflush(stdout);
            int v,nxt;
            scanf("%d %d",&v,&nxt);
            if(v<x&&v>ans){
                p=val[i];
                ans=v;
            }
        }
        while(p!=-1&&ans<x){
            printf("? %d\n",p);
            fflush(stdout);
            int v,nxt;
            scanf("%d %d",&v,&nxt);
            ans=v;
            p=nxt;
        }
        if(ans<x){
            ans=-1;
        }
        printf("! %d",ans);
        fflush(stdout);
    }
    return 0;
}