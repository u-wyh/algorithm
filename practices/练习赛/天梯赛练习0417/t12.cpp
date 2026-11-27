#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = MAXN*MAXN;
const int INF = 1e9;

int n;

int sex[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

int dis[MAXN][MAXN];

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void floyd(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
}

int d[MAXN];

int ans1[MAXN];
int top1=0;
int res1=INT_MAX;

int ans2[MAXN];
int top2;
int res2=INT_MAX;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=INF;
        }
        dis[i][i]=0;
    }
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        sex[i]=(c=='F')?1:0;
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int u,v;
            scanf("%d:%d",&u,&v);
            dis[i][u]=v;
        }
    }
    floyd();

    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<dis[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(sex[i]!=sex[j]){
                d[i]=max(dis[j][i],d[i]);
            }
        }
    }

    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<d[i]<<' ';
    // }
    // cout<<endl;

    for(int i=1;i<=n;i++){
        if(sex[i]==1){
            if(d[i]<res1){
                top1=0;
                res1=d[i];
                ans1[++top1]=i;
            }
            else if(d[i]==res1){
                ans1[++top1]=i;
            }
        }
        else{
            if(d[i]<res2){
                top2=0;
                res2=d[i];
                ans2[++top2]=i;
            }
            else if(d[i]==res2){
                ans2[++top2]=i;
            }
        }
    }

    cout<<ans1[1];
    for(int i=2;i<=top1;i++){
        cout<<' '<<ans1[i];
    }
    cout<<endl;
    cout<<ans2[1];
    for(int i=2;i<=top2;i++){
        cout<<' '<<ans2[i];
    }
    cout<<endl;
    return 0;
}