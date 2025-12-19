#include<bits/stdc++.h>
using namespace std;

int n,m,q;
int val[15];
int stat[15];//表示这个节点附近相邻的顶点
int attack[1<<15];
int cnt=1;
int head[16];
int nxt[300];
int to[300];
int weight[300];

int cost[1<<15][15][101];

struct node{
    int sta;
    int pos;
    int hq;
    int t;
};

struct cmp{
    bool operator()(const node& a,const node& b){
        return a.t<b.t;
    }
};
priority_queue<node,vector<node>,cmp>heap;

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int main()
{
    // int sum=0;
    cin>>n>>m>>q;
    for(int i=0;i<n;i++){
        cin>>val[i];
        // sum+=val[i];
    }
    // if(sum>)
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i&(1<<j)){
                attack[i]+=val[j];
            }
        }
        // cout<<i<<' '<<attack[i]<<endl;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
        stat[u]+=(1<<v);
        stat[v]+=(1<<u);
    }
    // for(int i=0;i<n;i++){
    //     cout<<stat[i]<<endl;
    // }
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            for(int k=1;k<=q;k++){
                cost[i][j][k]=INT_MAX;
            }
        }
    }
    cost[(1<<n)-1][0][q]=0;
    heap.push({(1<<n)-1,0,q,0});
    while(!heap.empty()){
        node u=heap.top();
        int sta=u.sta;
        int pos=u.pos;
        int hq=u.hq;
        int t=u.t;
        heap.pop();
        cout<<sta<<' '<<pos<<' '<<hq<<' '<<t<<endl;
        if(sta==0&&pos==(n-1)){
            cout<<t<<endl;
            return 0;
        }
        if(sta&(1<<pos)){
            int tmp=hq;
            tmp-=attack[sta&stat[pos]];
            if(tmp>0){
                for(int i=head[pos];i;i=nxt[i]){
                    int v=to[i];
                    int w=weight[i];
                    if(cost[sta-(1<<pos)][v][tmp]!=INT_MAX){
                        if(sta-(1<<pos)==0&&v==(n-1)){
                            cout<<cost[sta-(1<<pos)][v][tmp]<<endl;
                            return 0;
                        }
                        continue;
                    }
                    cost[sta-(1<<pos)][v][tmp]=w+cost[sta][pos][hq];
                    heap.push({sta-(1<<pos),v,tmp,w+cost[sta][pos][hq]});
                }
            }
        }
        for(int i=head[pos];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(cost[sta][v][hq]!=INT_MAX){
                if(sta==0&&v==n-1){
                    cout<<cost[sta][v][hq];
                    return 0;
                }
                continue;
            }
            cost[sta][v][hq]=w+cost[sta][pos][hq];
            heap.push({sta,v,hq,w+cost[sta][pos][hq]});
        }
    }
    return 0;
}