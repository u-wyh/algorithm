// https://www.luogu.com.cn/problem/P8893
// 题意：输入题目数 N、目标题号 K、第 0 天初始推荐数 p 及这 p 道题号
// 再输入 R 条规则（每条给出目标题 v_i、前提题数 s_i 及 s_i 个前提题号 p_i）；
// 天数从 0 开始，每天可做任意道以前或当天已推荐且未做过的题；
// 若集合 s_i 中所有题均已做完且至少有一道是在第 d 天做的，则第 d+1 天会推荐 v_i（无前提时按规则若已在第 0 天推荐则第 0 天可做）；
// 输出做完第 K 题的最早天数，无法完成输出 -1。
// 数据范围：1 <= K, s_i, p_i, v_i <= N <= 5*10^3，0 <= R <= 5*10^3
// 所有 |s_i| 互不相同（原文写作 |s_i| 互不相同）且同一规则内 p_i 互不相同、各规则的 v_i 互不相同（未单独标注 p 上界）。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 5000000;

int n,k,p,m;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int Time[MAXN];
int cnt=1;
int indegree[MAXN];
int ans=0;
int cal=0;
queue<int> q;

int main()
{
    cin>>n>>k>>p;
    for(int i=1;i<=p;i++){
        int a;
        cin>>a;
        indegree[a]=0;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,k,w;
        cin>>u>>k;
        indegree[u]+=k;
        for(int j=1;j<=k;j++){
            cin>>w;
            Next[cnt]=head[w];
            to[cnt]=u;
            head[w]=cnt++;
        }
    }
    if(p+m<k){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        ans=max(ans,Time[cur]);
        cal++;
        if(cal>=k){
            cout<<ans;
            return 0;
        }
        for(int i=head[cur];i>0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                q.push(to[i]);
            }
            Time[to[i]]=max(Time[cur]+1,Time[to[i]]);
        }
    }
    cout<<-1;
    return 0;
}

