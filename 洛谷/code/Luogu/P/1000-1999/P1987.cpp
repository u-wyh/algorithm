#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

struct node{
    int val,cost;
}nums[MAXN];
int n,m;
int f[MAXN][MAXN];

bool cmp(node a,node b){
    return a.cost>b.cost;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    scanf("%d %d",&n,&m);
    while(n+m){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                f[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i].val);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i].cost);
        }
        sort(nums+1,nums+n+1,cmp);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=min(i,m);j++){
                f[i][j]=max(f[i-1][j],f[i-1][j-1]+max(0,nums[i].val-nums[i].cost*(j-1)));
            }
        }
        int ans=0;
        for (int i=1;i<=m;i++)
            ans = max(ans, f[n][i]);
        printf("%d\n",ans);
        scanf("%d %d",&n,&m);
    }
    return 0;
}
