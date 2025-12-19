#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,k;

int v[MAXN];
int lt[MAXN],rt[MAXN],all[MAXN];
int sz[MAXN];
int son[MAXN];

vector<int>edge[MAXN];
vector<int>extra[MAXN];
vector<int>cur;

int ans[MAXN];

int tree1[MAXN];
int tree2[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int *tree,int x,int v){
    while(x<=n+1){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int *tree,int x){
    if(x<=0){
        return 0;
    }
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void buildtree(){
    stack<int>st;
    st.push(0);
    for(int i=1;i<=n;i++){
        while(v[st.top()]<v[i]){
            st.pop();
        }
        edge[st.top()].push_back(i);
        st.push(i);
    }
}

void dfs1(int u){
    sz[u]=1;

    int allson=edge[u].size();
    for(int i=0;i<allson;i++){
        int v=edge[u][i];
        rt[v]=rt[u]+allson-i-1;
        lt[v]=lt[u]+i+1;
        all[v]=all[u]+edge[v].size();
        dfs1(v);
        sz[u]+=sz[v];
        if(son[u]==0||sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

void effect(int u){
    cur.push_back(u);
    for(auto v:edge[u]){
        effect(v);
    }
}

void cancel(int u){
    if(u){
        add(tree1,lt[u],-1);
    }
    for(auto v:edge[u]){
        cancel(v);
    }
}

void dfs2(int u,int keep){
    int heavy=-1;
    for(int i=0;i<(int)edge[u].size();i++){
        int v=edge[u][i];
        if(v==son[u]){
            heavy=i;
        }
        else{
            dfs2(v,0);
        }
    }
    if(son[u]){
        dfs2(son[u],1);
    }

    vector<int>light;
    for(int i=(int)edge[u].size()-1;i>heavy;i--){
        int v=edge[u][i];
        cur.clear();
        effect(v);
        for(auto node:cur){
            int allowed=min(n+1,k-rt[node]+all[u]);
            ans[node]+=query(tree2,allowed);
        }
        for(auto node:cur){
            add(tree2,lt[node],1);
            if(son[u]){
                if(k-lt[node]+all[u]>=0)
                    extra[son[u]].push_back(k-lt[node]+all[u]);
            }
            light.push_back(node);
        }
    }

    for(int node:light){
        add(tree2,lt[node],-1);
        add(tree1,lt[node],1);
    }

    for(int i=heavy-1;i>=0;i--){
        int v=edge[u][i];
        cur.clear();
        effect(v);

        for(auto node:cur){
            int allowed=min(n+1,k-rt[node]+all[u]);
            ans[node]+=query(tree1,allowed);
        }

        for(int node:cur){
            add(tree1,lt[node],1);
        }
    }

    ans[u]+=query(tree1,min(k+lt[u],n+1));
    if(u){
        add(tree1,lt[u],1);
    }
    if(!keep){
        cancel(u);
    }
}

void dfs3(int u){
    for(auto val:extra[u]){
        if(val>=0){
            add(tree2,min(val+1,n+1),1);
        }
    }
    ans[u]+=query(tree2,n+1)-query(tree2,rt[u]);
    for(int v:edge[u]){
        dfs3(v);
    }
    for(auto val:extra[u]){
        if(val>=0){
            add(tree2,min(val+1,n+1),-1);
        }
    }
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<n;i++){
        v[i]=read();
    }
    v[n]=n+1,v[0]=n+2;

    buildtree();

    all[0]=edge[0].size();
    dfs1(0);
    // for(int i=0;i<=n;i++){
    //     cout<<i<<":   "<<lt[i]<<' '<<rt[i]<<' '<<all[i]<<endl;
    // }

    dfs2(0,0);
    dfs3(0);
    for(int i=1;i<=n;i++){
        cout<<(ans[i]+1)<<' ';
    }
    return 0;
}