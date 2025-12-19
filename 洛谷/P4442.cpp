#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 300000;

int walk[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
int arr[MAXN][MAXN];
int st,en;
int n,m;

int lt[MAXM];
int rt[MAXM];
int up[MAXM];
int dn[MAXM];

int dis[MAXM];
bool vis[MAXM];

int cnt = 1;
int head[MAXM];
int nxt[MAXM << 2];
int to[MAXM << 2];
int weight[MAXM << 2];

struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> heap;

inline void addedge(int u, int v, int w) {
    // cout<<u<<' '<<v<<' '<<w<<endl;
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dijkstra(int st) {
    for (int i = 1; i <= n*m ; i++) {
        dis[i] = INT_MAX;
        vis[i]=false;
    }
    dis[st] = 0;
    heap.push({st, 0});
    while (!heap.empty()) {
        int u = heap.top().first;
        heap.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = weight[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                heap.push({v, dis[v]});
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c!='#'){
                arr[i][j]=1;
            }
            if(c=='C'){
                st=(i-1)*m+j;
            }
            if(c=='F'){
                en=(i-1)*m+j;
            }
        }
    }

    // cout<<st<<' '<<en<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         cout<<arr[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }

    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++){
            if(arr[i][j]){
                for(int k=0;k<4;k++){
                    int x=i+walk[k][0],y=j+walk[k][1];
                    if(arr[x][y]==0){
                        continue;
                    }
                    addedge((i-1)*m+j,(x-1)*m+y,1);
                }
            }
        }
    }
    for(int i=2;i<n;i++){
        int pos=(i-1)*m+1;
        for(int j=2;j<m;j++){
            if(arr[i][j]==0){
                pos=(i-1)*m+j;
            }
            else{
                lt[(i-1)*m+j]=pos;
            }
        }
    }
    for(int i=2;i<n;i++){
        int pos=(i-1)*m+m;
        for(int j=m-1;j>=2;j--){
            if(arr[i][j]==0){
                pos=(i-1)*m+j;
            }
            else{
                rt[(i-1)*m+j]=pos;
            }
        }
    }
    for(int j=2;j<m;j++){
        int pos=j;
        for(int i=2;i<n;i++){
            if(arr[i][j]==0){
                pos=(i-1)*m+j;
            }
            else{
                up[(i-1)*m+j]=pos;
            }
        }
    }
    for(int j=2;j<m;j++){
        int pos=(n-1)*m+j;
        for(int i=n-1;i>=2;i--){
            if(arr[i][j]==0){
                pos=(i-1)*m+j;
            }
            else{
                dn[(i-1)*m+j]=pos;
            }
        }
    }

    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         cout<<(i-1)*m+j<<' '<<lt[(i-1)*m+j]<<' '<<rt[(i-1)*m+j]<<' '<<up[(i-1)*m+j]<<' '<<dn[(i-1)*m+j]<<endl;
    //     }
    // }

    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++){
            if(arr[i][j]==0){
                continue;
            }

            int tmp;
            for(int k=0;k<4;k++){
                int x=i+walk[k][0],y=j+walk[k][1];
                tmp+=arr[x][y];
            }
            if(tmp==4){
                continue;
            }

            addedge((i-1)*m+j,(i-1)*m+j,0);
            addedge((i-1)*m+j,lt[(i-1)*m+j]+1,1);
            addedge((i-1)*m+j,rt[(i-1)*m+j]-1,1);
            addedge((i-1)*m+j,up[(i-1)*m+j]+m,1);
            addedge((i-1)*m+j,dn[(i-1)*m+j]-m,1);
        }
    }
    dijkstra(st);
    if(dis[en]==INT_MAX){
        cout<<"nemoguce"<<endl;
        return 0;
    }
    cout<<dis[en];
    return 0;
}