#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int INF = 1e12;

int n,m,k;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

// dis[u]偶数最短路
// dis[u+n]奇数最短路
int dis[MAXN<<1];
int vis[MAXN<<1];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

void init(){
    cntg=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        dis[i]=dis[i+n]=INF;
        vis[i]=vis[i+n]=false;
    }
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dijkstra(){
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        // cout<<u<<":     "<<dis[u]<<endl;
        for(int i=head[(u<=n)?u:u-n];i;i=nxt[i]){
            int v=to[i];
            if(u<=n){
                v+=n;
            }
            if(dis[v]>dis[u]+1){
                dis[v]=dis[u]+1;
                heap.push({v,dis[v]});
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        init();
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        dijkstra();

        // for(int i=1;i<=n;i++){
        //     cout<<i<<":   "<<dis[i]<<' '<<dis[i+n]<<endl;
        // }

        for(int i=1;i<=n;i++){
            // d1 d2分别表示到达1的最近偶数长度  和 奇数长度
            int d1=dis[i];
            int d2=dis[i+n];

            if(d1!=INF&&d2!=INF){
                int dmax = max(d1, d2); 
                int dmin = min(d1, d2); 
                int res1 = (dmax + k - 1) / k;
                if(k % 2 == 0){
                    int res2 = INF;
                    if(d2 < d1){
                        cout << res1*k << " ";    
                    }else{
                        res2 = (dmin + k -1 ) / k;
                        cout << min(res1, res2)*k << " "; 
                    }
                }
                else{
                    int res2 = (dmin + k - 1)/k; 
                    if(d2 < d1){
                        if((k * res2) % 2 == 0){
                            res2++; 
                        }
                    }else{
                        if((k * res2) % 2 == 1){
                            res2++;
                        }
                    }
                    cout << min(res1, res2) * k << " "; 
                }
            }
            else if(d1==INF&&d2!=INF){
                // 只有奇数长度
                if(k%2==1){
                    if(d2%k==0){
                        cout<<d2<<' ';
                    }
                    else{
                        int val=(d2+k-1)/k*k;
                        if(val%2==0){
                            cout<<(val+k)<<' ';
                        }
                        else{
                            cout<<val<<' ';
                        }
                    }
                }
                else{
                    cout<<-1<<' ';
                }
            }
            else if(d2==INF&&d1!=INF){
                // 只有偶数长度
                if(k%2==1){
                    int val=(d1+k-1)/k*k;
                    if(val%2==0){
                        cout<<val<<' ';
                    }
                    else{
                        cout<<(val+k)<<' ';
                    }
                }
                else{
                    if(d1%k==0){
                        cout<<d1<<' ';
                    }
                    else{
                        cout<<(d1+k-1)/k*k<<' ';
                    }
                }
            }
            else{
                cout<<-1<<' ';
            }
        }
        cout<<endl;
    }
    return 0;
}
/*

7
4 4 3
1 2
2 3
3 4
4 2
5 4 2
1 2
2 3
3 4
4 5
3 3 4
1 2
2 3
3 1
2 1 5
1 2
4 1 2
1 2
2 2 2
1 2
2 2
2 0 1
*/