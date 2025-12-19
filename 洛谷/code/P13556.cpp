#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,m,k;


struct node{
    int u,v;
};
node nums[MAXM];

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

int find(vector<int>&fa,int x){
    return fa[x]==x?x:fa[x]=find(fa,fa[x]);
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        k=(m+n-2)/(n-1);
        vector<vector<int>>fa(k,vector<int>(n+1));
        vector<vector<vector<int>>>vec(k,vector<vector<int>>(n+1));
        for(int i=0;i<k;i++){
            for(int j=1;j<=n;j++){
                fa[i][j]=j;
            }
        }

        for(int i=1;i<=m;i++){
            nums[i].u=read(),nums[i].v=read();
        }
        for(int i=1;i<=m;i++){
            int u=nums[i].u,v=nums[i].v;
            int l=0,r=k-1,ans=k;
            while(l<=r){
                int mid=(l+r)>>1;
                if(find(fa[mid],u)!=find(fa[mid],v)){
                    ans=mid;
                    r=mid-1;
                }
                else{
                    l=mid+1;
                }
            }
            if(ans!=k){
                int fu=find(fa[ans],u);
                int fv=find(fa[ans],v);
                fa[ans][fu]=fv;
                vec[ans][u].push_back(v);
                vec[ans][v].push_back(u);
            }
        }

        int u,v;
        for(int i=1;i<=n;i++){
            if(fa[k-1][i]!=i){
                u=i;
                v=fa[k-1][i];
                break;
            }
        }

        cout<<u<<' '<<v<<endl;

        for(int i=0;i<k;i++){
            vector<int> pre(n+1,-1); // 前驱数组
            queue<int> q;
            
            q.push(u);
            pre[u]=-1;
            
            // BFS找路径
            while(!q.empty()){
                int cur=q.front();
                q.pop();
                
                if(cur==v) break;
                
                for(int neighbor:vec[i][cur]){
                    if(neighbor!=pre[cur]){
                        pre[neighbor]=cur;
                        q.push(neighbor);
                    }
                }
            }
            
            vector<int> path;
            for(int node=v;node!=-1;node=pre[node]){
                path.push_back(node);
            }
            reverse(path.begin(),path.end());
            
            cout<<path.size();
            for(int node:path){
                cout<<" "<<node;
            }
            cout<<endl;
        }
    }
    return 0;
}