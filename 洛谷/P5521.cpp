#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;

struct node{
    int val,ans;
}nums[MAXN],tmp[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

bool cmp(node a,node b){
    return a.val-a.ans<b.val-b.ans;
}

void dfs(int u){
    int sum=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
    int len=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        sum+=nums[v].val;
        tmp[++len]=nums[v];
    }
    if(len==0){
        nums[u].ans=nums[u].val;
        return ;
    }
    sum+=nums[u].val;
    sort(tmp+1,tmp+len+1,cmp);
    int now=0;
    nums[u].ans=max(nums[u].ans,sum);
    for(int i=1;i<=len;i++){
        nums[u].ans=max(nums[u].ans,now+tmp[i].ans);
        now+=tmp[i].val;
    }
}

int main()
{
    n=read();
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        addedge(u,i);
    }
    for(int i=1;i<=n;i++){
        nums[i].val=read();
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        printf("%d ",nums[i].ans);
    }
    return 0;
}