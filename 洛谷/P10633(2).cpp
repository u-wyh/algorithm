#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e4+5;
const int MAXV = 1e5+5;
const int INF = 1e9;

int n,m,v;

int val[MAXN];

struct node{
    int op,x,y,v,id;
};
int cnt;
node nums[MAXN*6];

int cntq;
int ans[MAXN];

int tree[MAXN*3];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    v=MAXV*2+n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        nums[++cnt]={1,i+val[i]+MAXV,i-val[i]+MAXV,0,0};
    }
    for(int i=1;i<=m;i++){
        string op;
        int x,k;
        cin>>op>>x>>k;
        if(op[0]=='Q'){
            cntq++;
            nums[++cnt]={2,min(x+val[x]+k+MAXV,v),x-val[x]+k+MAXV,1,cntq};
            nums[cnt]={2,min(x+val[x]+k+MAXV,v),x-val[x]-k+MAXV-1,-1,cntq};
            nums[cnt]={2,min(x+val[x]+k+MAXV-1,v),x-val[x]+k+MAXV,-1,cntq};
            nums[cnt]={2,min(x+val[x]+k+MAXV-1,v),x-val[x]-k+MAXV-1,1,cntq};
        }
        else{
            cnt++;
            val[x]=k;
            nums[++cnt]={1,x+k+n,x-k+n,0,0};
        }
    }
    return 0;
}