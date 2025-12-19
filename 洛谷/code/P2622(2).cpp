#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[105],b[105];
bool vis[1<<11];
int f[1<<11];
queue<int>q;

int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int x;
            cin>>x;
            if(x==1) a[i]|=(1<<j);
            if(x==-1) b[i]|=(1<<j);
        }
    }
    for(int i=0;i<(1<<n);i++){
        f[i]=INT_MAX;
    }
    f[0]=0;
    vis[0]=true;
    q.push(0);
    while(!q.empty()){
        int status=q.front();
        q.pop();
        for(int i=0;i<m;i++){
            int NEXT=(status|a[i])&(~b[i]);
            if(!vis[NEXT]){
                vis[NEXT]=true;
                f[NEXT]=f[status]+1;
                q.push(NEXT);
            }
        }
    }
    if(f[(1<<n)-1]==INT_MAX){
        cout<<-1;
    }
    else{
        cout<<f[(1<<n)-1];
    }
    return 0;
}
