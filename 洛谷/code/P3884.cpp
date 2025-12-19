#include<bits/stdc++.h>
using namespace std;

int l[105],r[105],d[105],cnt[105],father[105],vis[105];
int n,x,y;

void dfs(int x){
    if(l[x]!=0){
        d[l[x]]=d[x]+1;
        dfs(l[x]);
    }
    if(r[x]!=0){
        d[r[x]]=d[x]+1;
        dfs(r[x]);
    }
}

int lca(int x,int y){
    vis[x]=1;
    while(father[x]!=0){
        x=father[x];
        vis[x]=1;
    }
    while(vis[y]!=1){
        y=father[y];
    }
    return y;
}

int main()
{
    cin>>n;
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    int u,v;
    for(int i=1;i<=n-1;i++){
        cin>>u>>v;
        if(l[u]==0)
            l[u]=v;
        else
            r[u]=v;
        father[v]=u;
    }
    /*
    printf("-------------------------\n");
    for(int i=1;i<=n;i++){
        printf("%d %d %d\n",l[i],r[i],father[i]);
    }
    printf("-------------------------\n");
    */
    cin>>x>>y;
    int k=lca(x,y),num=0,num1=0;
	while(x!=k){                //记录s到最近公共祖先有多少条边
		x=father[x];
		num++;
	}
	num*=2;   //结点间距离的定义：由结点向根方向（上行方向）时的边数×2，
	while(y!=k){               //记录t到最近公共祖先有多少条边
		y=father[y];
		num1++;
	}
    d[1]=1;//d[i]表示第i号节点到跟的距离+1
    dfs(1);
    int ans1=0,ans2=0;
    for(int i=1;i<=n;i++){
        cnt[d[i]]++;
        ans2=max(ans2,d[i]);
        ans1=max(ans1,cnt[d[i]]);
    }
    //printf("%d %d %d %d\n",k,d[k],d[x],d[y]);
    printf("%d\n%d\n%d\n",ans2,ans1,num+num1);
    return 0;
}
