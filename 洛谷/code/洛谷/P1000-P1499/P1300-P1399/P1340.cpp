// https://www.luogu.com.cn/problem/P1340
// 题意：有 N 片草地，接下来 W 周每周新增一条带长度的双向路。
// 每周可任意选取目前已知的道路。
// 逐周输出把所有草地连通所需的最小道路总长度，无法连通输出 -1。
// 数据范围：1 ≤ N ≤ 200，1 ≤ W ≤ 6000，
// 路长在 [1,10000]，道路两端不同。
// 算法标签：最小生成树、并查集、二分查找

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5001;
const int MAXM = 200001;

int fa[MAXN];
int n,m;
struct node{
    int st,en,val;
}edge[MAXM];

void build(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

bool un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        return true;
    }else{
        return false;
    }
}
//如果这两个节点以前就不是一个组里面的  那么合并他们
//否则返回false

void update(int i,int k){
    if(edge[k].val<=edge[i].val){
        return ;
    }
    int l=1,r=k,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(edge[mid].val>=edge[i].val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    if(ans==k&&edge[k].val<edge[i].val){
        ans=k+1;
    }
    edge[0].val=edge[i].val;
    edge[0].st=edge[i].st;
    edge[0].en=edge[i].en;
    for(int i=k;i>=ans;i--){
        edge[i+1].val=edge[i].val;
        edge[i+1].st=edge[i].st;
        edge[i+1].en=edge[i].en;
    }
    edge[ans].val=edge[0].val;
    edge[ans].st=edge[0].st;
    edge[ans].en=edge[0].en;
}

bool cmp(node a,node b){
    return a.val<b.val;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i].st>>edge[i].en>>edge[i].val;
    }
    for(int i=1;i<=m;i++){
        build();
        update(i,i-1);
        //sort(edge+1,edge+i+1,cmp);
        int ans=0;
        int edgecnt=0;
        //edgecnt统计记录了多少条边
        for(int j=1;j<=i;j++){
            if(un(edge[j].st,edge[j].en)){
                //如果这条边的左右以前不在一个组里面   继续
                ans+=edge[j].val;
                edgecnt++;
                if(edgecnt==n-1){
                    break;
                }
            }
        }
        if(edgecnt==n-1){
            cout<<ans<<endl;
        }else{
            cout<<-1<<endl;
        }
    }
    return 0;
}
