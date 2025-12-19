#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int INF = 1e9+5;

int n;
int pos[MAXN];
int goal[MAXN];
int dir[MAXN];
int ans[MAXN];

struct node{
    int id,dis;
};
node nums[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

bool cmp(node a,node b){
    return a.dis<b.dis;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>goal[i];
        addedge(goal[i],i);
    }
    for(int i=1;i<=n;i++){
        cin>>pos[i];
    }
    for(int i=1;i<=n;i++){
        if(pos[goal[i]]<pos[i]){
            // 表示向左走
            dir[i]=0;
        }
        else{
            dir[i]=1;
        }
    }
    for(int i=1;i<=n;i++){
        if(dir[i]==dir[goal[i]]){
            nums[i]={i,INF};
        }
        else{
            nums[i]={i,abs(pos[i]-pos[goal[i]])};
        }
    }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<dir[i]<<' ';
    // }
    // cout<<endl;
    sort(nums+1,nums+n+1,cmp);
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(ans[nums[i].id]){
            continue;
        }
        ans[nums[i].id]=nums[i].dis;
        q.push(nums[i].id);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                if(ans[v]){
                    continue;
                }
                if(dir[v]==dir[u]){
                    ans[v]=ans[u]+2*abs(pos[u]-pos[v]);
                }
                else{
                    int d=abs(pos[u]-pos[v]);
                    if(d<=ans[u]){
                        ans[v]=d;
                    }
                    else{
                        ans[v]=2*d-ans[u];
                    }
                }
                q.push(v);
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}