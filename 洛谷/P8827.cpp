#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int fa[MAXN];
struct node{
    int u,v;
}nums[MAXN];
struct ques{
    int op,u,v,tmp;
}arr[MAXN];
bool vis[MAXN];
bool ok[MAXN<<1];
int val[MAXN];
int sum[MAXN];
stack<int>ans;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void dfs(int u,int f){
    fa[u]=f;
    sum[u]=val[u];
    vis[u]=true;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(ok[i]||v==f){
            continue;
        }
        dfs(v,u);
        sum[u]+=sum[v];
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        nums[i].u=read(),nums[i].v=read();
        addedge(nums[i].u,nums[i].v);
        addedge(nums[i].v,nums[i].u);
    }
    for(int i=1;i<=m;i++){
        arr[i].op=read(),arr[i].u=read();
        if(arr[i].op==2){
            arr[i].v=read();
            arr[i].tmp=val[arr[i].u];
            val[arr[i].u]=arr[i].v;
        }
        else if(arr[i].op==1){
            ok[arr[i].u*2]=ok[arr[i].u*2-1]=true;
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i,i);
        }
    }
    for(int i=m;i>=1;i--){
        if(arr[i].op==1){
            int u=nums[arr[i].u].u;
            int v=nums[arr[i].u].v;
            v=find(v);
            u=find(u);
            fa[u]=v;
            sum[v]+=sum[u];
        }
        else if(arr[i].op==2){
            int u=find(arr[i].u);
            sum[u]+=(arr[i].tmp-arr[i].v);
            val[arr[i].u]=arr[i].tmp;
        }
        else{
            int u=find(arr[i].u);
            ans.push(sum[u]);
        }
    }
    while(!ans.empty()){
        cout<<ans.top()<<endl;
        ans.pop();
    }
    return 0;
}
