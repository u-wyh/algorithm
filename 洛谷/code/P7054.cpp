// https://www.luogu.com.cn/problem/P7054
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;
int in[MAXN];

int ans[MAXN];
int addu[MAXN];
int addv[MAXN];
int cnt;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        in[v]++;
    }

    priority_queue<int,vector<int>,greater<int>>q1;
    priority_queue<int>q2;

    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q1.push(i);
        }
    }

    for(int i=1;i<=n;i++){
        while(k && !q1.empty()){
            if(q1.size()==1  &&  (q2.empty()||q1.top()>q2.top())){
                break;
            }
            q2.push(q1.top());
            q1.pop();
            k--;
        }

        int u;
        if(!q1.empty()){
            u=q1.top();
            q1.pop();
        }
        else{
            u=q2.top();
            q2.pop();

            ++cnt;
            addu[cnt]=ans[i-1];
            addv[cnt]=u;
        }

        ans[i]=u;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(--in[v]==0){
                q1.push(v);
            }
        }
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<addu[i]<<' '<<addv[i]<<endl;
    }
    return 0;
}