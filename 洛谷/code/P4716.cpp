#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 1e4+5;

int n,m,root;

struct node{
    int u,v,w;
}nums[MAXM];

int pre[MAXN];
int in[MAXN];
int id[MAXN];
int vis[MAXN];//这里之所以不是bool类型  主要是为了判断环   如果是bool类型 可能会导致不是环上的点也被计算

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

void prepare(){
    for(int i=1;i<=n;i++){
        pre[i]=0;
        in[i]=INT_MAX;
        id[i]=0;
        vis[i]=false;
    }
}

int main()
{
    n=read(),m=read(),root=read();
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
    }
    long long ans=0;
    while(true){
        prepare();
        for(int i=1;i<=m;i++){
            int u=nums[i].u;
            int v=nums[i].v;
            int w=nums[i].w;
            if(u!=v&&w<in[v]){
                in[v]=w;
                pre[v]=u;
            }
        }

        for(int i=1;i<=n;i++){
            if(in[i]==INT_MAX){
                cout<<-1<<endl;
                return 0;
            }
        }

        for(int i=1;i<=n;i++){
            if(root==i){
                continue;
            }
            ans+=in[i];
        }

        int cnt=0;
        int idx=0;

        //注意 一个点只能有一条入边  所以如果被访问过了  
        //那么如果是环上的点  直接结束    不是环上的点  再次访问也没有什么用
        for(int i=1;i<=n;i++){
            if(vis[i]||i==root){
                //如果已经在环中  或者  是根节点（只能有出边）  那么直接结束
                continue;
            }
            idx++;
            int v=i;
            while(vis[v]!=idx&&!id[v]&&v!=root){
                vis[v]=idx;
                v=pre[v];
            }
            //处理环上的节点
            if(v!=root&&!id[v]){
                cnt++;
                id[v]=cnt;
                for(int u=pre[v];u!=v;u=pre[u]){
                    id[u]=cnt;
                }
            }
        }
        
        if(cnt==0){
            break;
        }

        for(int i=1;i<=n;i++){
            if(!id[i]){
                id[i]=++cnt;
            }
        }

        //更新权值
        for(int i=1;i<=m;i++){
            if(nums[i].u!=nums[i].v){
                nums[i].w-=in[nums[i].v];
            }
            nums[i].u=id[nums[i].u];
            nums[i].v=id[nums[i].v];
        }

        //更新变量
        n=cnt;
        root=id[root];
    }

    cout<<ans<<endl;
    return 0;
}