#include<bits/stdc++.h>
using namespace std;

int u[910],v[910],val[460];
bool conn[460][460];

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    for(int i=0;i<m;i++){
        scanf("%d%d",&u[i],&v[i]);
        conn[v[i]][u[i]]=conn[u[i]][v[i]]=true;
    }
    int ans=0;
    for(int i=0;i<m;i++)
    {
        int res=val[u[i]]+val[v[i]];
        ans=max(ans,res);
        for(int j=1;j<=n;j++)
            if(conn[v[i]][j]&&conn[u[i]][j])
                ans=max(ans,res+val[j]);
        for(int j=0;j<i;j++)
            if(conn[u[i]][u[j]]&&conn[u[i]][v[j]]&&conn[v[i]][u[j]]&&conn[v[i]][v[j]])
                ans=max(ans,res+val[u[j]]+val[v[j]]);
    }
    printf("%d\n",ans);
    return 0;
}
