#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;
int arr[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;
int in[MAXN];

priority_queue<int,vector<int>,greater<int>>heap;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
    in[v]++;
}

void init(){
    for(int i=1;i<=n;i++){
        in[i]=0;
        head[i]=0;
    }
    cntg=1;
    while(!heap.empty()){
        heap.pop();
    }
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        int pre,now;
        cin>>pre;
        for(int i=l+1;i<=r;i++){
            cin>>now;
            addedge(pre,now);
            pre=now;
        }
    }

    for(int i=1;i<=n;i++){
        if(in[i]==0){
            heap.push(i);
        }
    }
    int now=0;
    while(!heap.empty()){
        int u=heap.top();
        heap.pop();
        arr[u]=++now;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            in[v]--;
            if(in[v]==0){
                heap.push(v);
            }
        }
    }
    if(now==n){
        for(int i=1;i<=n;i++){
            cout<<arr[i]<<' ';
        }
        cout<<endl;
    }
    else{
        cout<<-1<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
/*
4
4 1
2 4 3 2 4
3 2
1 3 1 2 3
1 3 3 2 1
5 2
2 4 4 2 3
2 4 4 2 3
4 2
2 2 2
1 4 2 1 4 3
*/