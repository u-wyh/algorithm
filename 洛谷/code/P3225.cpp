#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1005;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt,color;
int st[MAXN];
int top;
vector<int>ans[MAXN];
bool cut[MAXN];

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void prepare(){
    for(int i=1;i<=1005;i++){
        head[i]=0;
        dfn[i]=0;
        low[i]=0;
        cut[i]=false;
    }
    cnt=1;
    top=0;
    m=0;
    dfncnt=0,color=0;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++dfncnt;
    st[++top]=u;
    int child=0;

    if(u==m&&head[u]==0){
        ans[++color].push_back(u);
        top--;
        return ;
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        if(!dfn[v]){
            child++;
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if((u==m&&child>=2)||(u!=m&&low[v]>=dfn[u])){
                cut[u]=true;
                color++;
                while(st[top]!=v){
                    ans[color].push_back(st[top--]);
                }
                ans[color].push_back(st[top--]);
                ans[color].push_back(u);
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }

}

signed main()
{
    int T=0;
    while(cin>>n&&n!=0){
        T++;
        prepare();
        for(int i=1;i<=n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
            m=max(m,max(u,v));
        }

        tarjan(m,0);
        if(top){
            color++;
            while(top){
                ans[color].push_back(st[top--]);
            }
        }

        int ans1=0,ans2=1;
        for(int i=1;i<=color;i++){
            int cnt1=0,cnt2=0;
            for(int j=0;j<(int)ans[i].size();j++){
                if(cut[ans[i][j]]){
                    cnt1++;
                }
                else{
                    cnt2++;
                }
            }
            if(cnt1==0){
                if(cnt2==1){
                    ans1+=1;
                }
                else{
                    ans1+=2;
                    ans2*=(cnt2*(cnt2-1))/2;
                }
            }
            else if(cnt1==1){
                ans1+=1;
                ans2*=cnt2;
            }
            ans[i].clear();
        }
        cout<<"Case "<<T<<": "<<ans1<<' '<<ans2<<endl;
    }
    return 0;
}