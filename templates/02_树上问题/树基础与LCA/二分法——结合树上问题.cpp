//P5021
//这道题是二分并充分利用了树的结构特性 很好的一道题目
//很容易想到二分答案
//因为每一条边都只能用一次  对于树形结构而言
//那么节点u及其子树最多可以为u的父亲节点贡献一条链  或者0条  因为要是超过了一条  那么u到fa的那条边就被用了两次
//u子树内部如果有两条链组合后可以满足要求  那么need就减去一

//如果现在树只有两层（一个树根和一堆儿子），我们的肯定希望这个子树多出现赛道。
//我们把边全部排序，然后从最小的边开始，用分界线mid减去这个边的边权，设为x。
//显然，给这个边找一条比x大一点或者等于的边即可，
//因为比x长的边虽然也能和当前匹配，但是后面我们其他的匹配或者是要向上贡献的机会可能就少了，因此可能会不优。
//我们现在已经完成子树内的最大匹配了，
//我们找出链中没有用过的最长链（可以是空链，也就是0），作为向上的贡献
//（具体做法也就是记一个点权，点权也就是那个最长链的长度）。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n,m;

int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];

int need;//目前还要建立多少条目标边
int tag[MAXN<<1];
int que[MAXN<<1];
int tail;
int dp[MAXN];//表示这个节点可以向上贡献的最大边是多少

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int f,int limit){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u,limit);
        }
    }
    tail=0;//相当于每次清空数组
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            que[++tail]=dp[v]+weight[i];
        }
    }
    //que数组统计的是u的所有有效边
    sort(que+1,que+tail+1);
    for(int i=tail;i>=1&&que[i]>=limit;i--){
        need--,tail--;
    }
    for(int i=1;i<=tail;i++){
        if(tag[i]!=u){
            int l=i+1,r=tail,nxt=tail+1;
            while(l<=r){
                int mid=(l+r)/2;
                if(que[mid]>=limit-que[i]){
                    nxt=mid;
                    r=mid-1;
                }
                else{
                    l=mid+1;
                }
            }
            while(tag[nxt]==u&&nxt<=tail){
                nxt++;
            }
            if(nxt<=tail){
                tag[nxt]=u;
                tag[i]=u;
                need--;
            }
        }
    }
    dp[u]=0;
    for(int i=tail;i>=1;i--){
        if(tag[i]!=u){
            dp[u]=que[i];
            break;
        }
    }
}

bool check(int limit){
    need=m;
    dfs(1,0,limit);
    if(need<=0)
        return true;
    else
        return false;
}

int main()
{
    cin>>n>>m;
    int l=0,r,ans=0;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
        r+=w;
    }
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
        memset(tag,0,sizeof(tag));
    }
    cout<<ans<<endl;
    return 0;
}
