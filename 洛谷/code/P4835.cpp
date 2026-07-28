#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;
const int MAXM = 2e6+5;

int n;

int teacher[MAXN];
int allow[MAXN][2];
int rk[MAXN][MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg;

int dfn[MAXN];
int low[MAXN];
int cntd;

int sta[MAXN];
int top;

int belong[MAXN];
int sccCnt;

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cntd;
    sta[++top] = u;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else {
            if (belong[v] == 0) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    if (dfn[u] == low[u]) {
        sccCnt++;
        int pop;
        do {
            pop = sta[top--];
            belong[pop] = sccCnt;
        } while (pop != u);
    }
}

int getnode(int x,int c){
    if(allow[x][0]==c){
        return x;
    }
    else{
        return x+n;
    }
}

int rev(int x){
    if(x<=n){
        return x+n;
    }
    return x-n;
}

bool check(int limit){
    for(int i=1;i<=2*n;i++){
        head[i]=0;
        dfn[i]=0;
        low[i]=0;
        belong[i]=0;
    }
    cntg=1;
    cntd=0;
    top=0;
    sccCnt=0;

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(rk[i][j]<=limit&&rk[j][i]<=limit){
                continue;
            }

            for(int c=0;c<3;c++){
                if(c==teacher[i]||c==teacher[j]){
                    continue;
                }

                int x=getnode(i,c);
                int y=getnode(j,c);

                addEdge(x,rev(y));
                addEdge(y,rev(x));
            }
        }
    }

    for(int i=1;i<=2*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }

    for(int i=1;i<=n;i++){
        int x=i,y=i+n;
        if(belong[x]==belong[y]){
            return false;
        }
    }

    return true;
}

int compute(){
    int l=0,r=n-1,ans=n-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>teacher[i];
        allow[i][0]=(teacher[i]+1)%3;
        allow[i][1]=(teacher[i]+2)%3;

        for(int p=1;p<=n-1;p++){
            int x;
            cin>>x;
            rk[i][x]=p;
        }
    }

    cout<<compute()<<endl;

    return 0;
}