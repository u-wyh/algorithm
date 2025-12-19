#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,k;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

int dis[MAXN];
bool vis[MAXN];
queue<pair<int,int > >q;

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        Next[cnt]=head[i-1];
        to[cnt]=i;
        head[i-1]=cnt++;

        Next[cnt]=head[i-1];
        to[cnt]=(i-1+k)%n;
        head[i-1]=cnt++;
    }
    dis[0]=0;
    q.push({0,0});
//    dis[1]=1;
//    dis[k]=1;
//    q.push({1,1});
//    q.push({k,1});
    while(!q.empty()){
        int u=q.front().first;
        int w=q.front().second;
        q.pop();
        vis[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            if(!vis[v]){
                dis[v]=w+1;
                vis[v]=true;
                q.push({v,dis[v]});
            }else{
                continue;
            }
        }
    }
    int ans=INT_MIN;
    for(int i=0;i<n;i++){
        ans=max(ans,dis[i]);
        //printf("%3d",dis[i]);
    }
    //cout<<endl;
    cout<<ans;
    return 0;
}
