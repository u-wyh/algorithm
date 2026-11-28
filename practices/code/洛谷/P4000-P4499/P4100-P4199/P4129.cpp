// https://www.luogu.com.cn/problem/P4129
// 题意：第一行输入无向图点数 n 和路径数 m；
// 接下来 m 行每行先输入 k_i，
// 后接 k_i 个顶点序列表示一条由相邻点边组成的路径（边不重复出现且覆盖全图）。
// 判断该图是否为仙人掌图（连通且每条边至多属于一个简单环），
// 若是则输出其连通支撑子图个数（「仙人数」，可能很大，需高精度），否则输出 0。
// 输出一个整数表示结果。
// 数据范围：1 <= n <= 20000，0 <= m <= 1000，
// 2 <= k_i <= 1000。
// 难度评分：1900（洛谷分级换算）
// 算法标签：Tarjan、仙人掌、高精度
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXM = 1e6+5;

int n,m;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cntg=2;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int top;

int edgecnt[MAXN];
int cntc;

int cyclecnt[MAXN];

string ans;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void multiply(int x) {
    int carry = 0;
    for (int i = ans.size() - 1; i >= 0; i--) {
        int cur = (ans[i] - '0') * x + carry;
        ans[i] = cur % 10 + '0';
        carry = cur / 10;
    }
    string pre = "";
    while (carry > 0) {
        pre += carry % 10 + '0';
        carry /= 10;
    }
    reverse(pre.begin(), pre.end());
    ans = pre + ans;
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        if((i^1)==preedge){
            continue;
        }
        int v=to[i];
        if(dfn[v]==0){
            tarjan(v,i);
            if(low[v]<dfn[u]){
                low[u]=min(low[u],low[v]);
                cyclecnt[u]++;
            }
            else if(low[v]>dfn[u]){
                top--;
            }
            else{
                cntc++;
                edgecnt[cntc]=1;
                int pop;
                do{
                    pop=sta[top--];
                    edgecnt[cntc]++;
                }while(pop!=v);
            }
        }
        else if(dfn[v]<dfn[u]){
            // 这里表示的是合围成环前的最后一个节点 下一个节点就是入环顶点了
            low[u]=min(low[u],dfn[v]);
            cyclecnt[u]++;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int k,x,y;
        cin>>k>>x;
        for(int j=2;j<=k;j++){
            cin>>y;
            addedge(x,y);
            addedge(y,x);
            x=y;
        }
    }

    tarjan(1,0);

    bool flag=true;
    for(int i=1;i<=n;i++){
        if(dfn[i]==0||cyclecnt[i]>=2){
            flag=false;
            break;
        }
    }

    if(flag){
        ans="1";
        for(int i=1;i<=cntc;i++){
            multiply(edgecnt[i]+1);
        }
        cout<<ans<<endl;
    }
    else{
        cout<<0<<endl;
    }

    return 0;
}