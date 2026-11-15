// https://www.luogu.com.cn/problem/P1034
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int INF = 1005;

int n,k;
struct Point{
    int x,y;
};
Point p[MAXN];
int bel[MAXN];
int xmin[5];
int xmax[5];
int ymin[5];
int ymax[5];
int ans=1000000;

bool check(int x1,int x2,int y1,int y2,int x,int y){
    return x1<=x && x<=x2 && y1<=y && y<=y2;
}

void dfs(int u){
    if(u==n+1){
        for(int i=1;i<=k;i++){
            xmin[i]=ymin[i]=INF;
            xmax[i]=ymax[i]=0;
        }
        for(int i=1;i<=n;i++){
            int b=bel[i];
            xmin[b]=min(xmin[b],p[i].x);
            xmax[b]=max(xmax[b],p[i].x);
            ymin[b]=min(ymin[b],p[i].y);
            ymax[b]=max(ymax[b],p[i].y);
        }
        for(int i=1;i<=k;i++){
            for(int j=1;j<=k;j++){
                if(xmin[i]==INF||xmin[j]==INF||i==j){
                    continue;
                }
                bool flag=false;
                flag|=check(xmin[i],xmax[i],ymin[i],ymax[i],xmin[j],ymin[j]);
                flag|=check(xmin[i],xmax[i],ymin[i],ymax[i],xmin[j],ymax[j]);
                flag|=check(xmin[i],xmax[i],ymin[i],ymax[i],xmax[j],ymin[j]);
                flag|=check(xmin[i],xmax[i],ymin[i],ymax[i],xmax[j],ymax[j]);
                if(flag){
                    return ;
                }
            }
        }
        int res=0;
        for(int i=1;i<=k;i++){
            if(xmin[i]==INF){
                continue;
            }
            res+=(xmax[i]-xmin[i])*(ymax[i]-ymin[i]);
        }
        ans=min(ans,res);
        return ;
    }

    for(int i=1;i<=k;i++){
        if(i==1){
            cout<<"   "<<u<<endl;
        }
        bel[u]=i;
        dfs(u+1);
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    dfs(1);
    cout<<ans<<endl;
    return 0;
}