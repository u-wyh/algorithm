// https://onlinejudge.org/external/13/1391.pdf
// 题意：多组数据，每组给 n 名宇航员的年龄，
// 以及 m 对互相厌恶的人，输入以 0 0 结束。
// 每人分配到 A、B、C 中的一项，仇人不能同组。
// A 仅收年龄不低于平均值者，B 仅收低于者。
// C 对年龄不限。
// 输出：按输入顺序逐人输出任务字母。
// 若不存在合规分配，输出 No solution.。
// 数据范围：1 <= n, m <= 10^5。
// 年龄是 [0, 200] 内的整数，编号为 1 到 n。
// 难度评分：1900（估算）
// 算法标签：2-SAT、Tarjan
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 5e5+5;

int n,m;
int age[MAXN];
int sumage;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int sta[MAXN];
int top;

int belong[MAXN];
int scccnt;

void prepare(){
    sumage=0;
    cntg=1;
    dfncnt=0;
    top=0;
    scccnt=0;
    for(int i=1;i<=(n<<1);i++){
        head[i]=0;
        dfn[i]=low[i]=belong[i]=0;
    }
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

bool older(int x){
    return age[x]*n>=sumage;
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else{
            if(belong[v]==0){
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    if(dfn[u]==low[u]){
        scccnt++;
        int pop;
        do {
            pop = sta[top--];
            belong[pop] = scccnt;
        } while (pop != u);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    while(n!=0&&m!=0){
        prepare();
        for(int i=1;i<=n;i++){
            cin>>age[i];
            sumage+=age[i];
        }
        for(int i=1;i<=m;i++){
            int x,y;
            cin>>x>>y;
            addedge(y+n,x);
            addedge(x+n,y);
            if(older(x)==older(y)){
                addedge(x,y+n);
                addedge(y,x+n);
            }
        }

        for(int i=1;i<=n<<1;i++){
            if(dfn[i]==0){
                tarjan(i);
            }
        }
        bool check=true;
        for(int i=1;i<=n;i++){
            if(belong[i]==belong[i+n]){
                check=false;
                break;
            }
        }
        if(check){
            for(int i=1;i<=n;i++){
                if(belong[i]<belong[i+n]){
                    if(older(i)){
                        cout<<"A"<<endl;
                    }
                    else{
                        cout<<"B"<<endl;
                    }
                }
                else{
                    cout<<"C"<<endl;
                }
            }
        }
        else{
            cout<<"No solution."<<endl;
        }
        cin>>n>>m;
    }
    return 0;
}