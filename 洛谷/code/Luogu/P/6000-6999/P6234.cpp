#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int INF = 1e5;

int n,m,all;
int val[MAXN];

int k;
int black[MAXN];
bool special[MAXN];
bool white[MAXN];

int fa[MAXN];
int sum[MAXN];
int bsz[MAXN];
int minval[MAXN];

int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int id(int x,int y){
    return (x-1)*m+y;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        sum[fx]+=sum[fy];
        bsz[fx]+=bsz[fy];
        fa[fy]=fx;
        minval[fx]=min(minval[fx],minval[fy]);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    all=n*m;
    for(int i=1;i<=all;i++){
        cin>>val[i];
        fa[i]=i;
        sum[i]=1;
        minval[i]=val[i];
    }

    cin>>k;
    for(int i=1;i<=k;i++){
        int x,y;
        cin>>x>>y;
        x++,y++;
        int node=id(x,y);
        special[node]=true;
        black[i]=node;
        bsz[node]++;
        minval[node]=INF;
        for(int j=0;j<4;j++){
            int nx=x+walk[j][0];
            int ny=y+walk[j][1];
            if(nx>n||ny>m||nx==0||ny==0){
                continue;
            }
            white[id(nx,ny)]=true;
        }
    }

    for(int i=1;i<=k;i++){
        int x=(black[i]-1)/m+1;
        int y=(black[i]-1)%m+1;
        int u=black[i];
        for(int j=0;j<4;j++){
            int nx=x+walk[j][0];
            int ny=y+walk[j][1];
            if(nx>n||ny>m||nx==0||ny==0||special[id(nx,ny)]){
                continue;
            }
            int v=id(nx,ny);
            un(u,v);
        }
    }

    int ans=0;
    for(int i=1;i<=all;i++){
        if(white[i]||special[i]){
            ans+=val[i];
        }
    }
    for(int i=1;i<=all;i++){
        if(i==find(i)){
            if(sum[i]<4*bsz[i]){
                cout<<"No"<<endl;
                return 0;
            }
            else if(sum[i]==4*bsz[i]){
                continue;
            }
            else{
                if(bsz[i])
                    ans-=minval[i];
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}