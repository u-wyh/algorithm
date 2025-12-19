#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9+7;
const int MAXN = 1e5+5;
const int MAXM = 5e5+5;
const int MAXB = 405;

int n,m;
int blen;
int col[MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cnt=1;

struct point{
    int t,sub;
}arr[MAXN];
int vis[MAXN];
int id[MAXB];

multiset<int>st[7];
multiset<int>node[MAXB][4];

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool cmp(point a,point b){
    return a.t>b.t;
}

int compute(int a,int b){
    if(a>b){
        swap(a,b);
    }
    if(a==1){
        return b;
    }
    else if(a==2){
        return a+b;
    }
    else{
        return 6;
    }
}

void prepare(){
    blen=sqrt(n);
    sort(arr+1,arr+n+1,cmp);
    for(int i=1;i<=blen;i++){
        vis[arr[i].sub]=i;
        id[i]=arr[i].sub;
    }
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v<u){
                continue;
            }
            if(vis[v]||vis[u]){
                if(vis[v]){
                    node[vis[v]][1].insert(weight[i]);
                }
                if(vis[u]){
                    node[vis[u]][1].insert(weight[i]);
                }
            }
            else{
                st[1].insert(weight[i]);
            }
        }
    }
}

void query(int u,int v){
    int ans=INF;

    if(!st[compute(u,v)].empty()){
        ans=*st[compute(u,v)].begin();
    }
    for(int i=1;i<=blen;i++){
        if(col[id[i]]==u||col[id[i]]==v){
            if(!node[i][u+v-col[id[i]]].empty()){
                ans=min(ans,*node[i][u+v-col[id[i]]].begin());
            }
        }
    }

    if(ans==INF){
        cout<<"No Found!"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
}

void update(int u,int c){
    if(!vis[u]){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            // if(u==v){
            //     int op=compute(col[u],col[u]);
            //     auto it=st[op].find(weight[i]);
            //     st[op].erase(it);
            //     op=compute(c,c);
            //     st[op].insert(weight[i]);
            //     continue;
            // }
            if(!vis[v]){
                // if(v<u){
                //     continue;
                // }
                int op=compute(col[u],col[v]);
                auto it=st[op].find(weight[i]);
                if(it != st[op].end()) st[op].erase(it);
                op=compute(col[v],c);
                st[op].insert(weight[i]);
            }
            else{
                auto it=node[vis[v]][col[u]].find(weight[i]);
                if(it != node[vis[v]][col[u]].end()) node[vis[v]][col[u]].erase(it);
                node[vis[v]][c].insert(weight[i]);
            }
        }
    }
    else{
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            // if(u==v){

            // }
            if(vis[v]){
                auto it=node[vis[v]][col[u]].find(weight[i]);
                node[vis[v]][col[u]].erase(it);
                node[vis[v]][c].insert(weight[i]);
            }
        }
    }
    col[u]=c;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
        arr[u].t++,arr[v].t++;
    }
    for(int i=1;i<=n;i++){
        col[i]=1;
        arr[i].sub=i;
    }
    prepare();
    int T;
    cin>>T;
    while(T--){
        string op;
        int x;
        cin>>op;
        if(op[0]=='A'){
            int u=op[3]-'A'+1;
            int v=op[4]-'A'+1;
            query(u,v);
        }
        else{
            cin>>x;
            int to=op[4]-'A'+1;
            if(col[x]==to){
                continue;
            }
            update(x,to);
        }
    }
    return 0;
}