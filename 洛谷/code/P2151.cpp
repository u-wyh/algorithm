#include<bits/stdc++.h>
using namespace std;
const int MOD = 45989;
const int MAXM = 125;

int n,m,t,a,b;

struct Edge{
    int from,to;
};
Edge edge[MAXM];
int cnt=-1;

vector<vector<int>> multiply(vector<vector<int>> a,const vector<vector<int>> b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]=((ans[i][j]%MOD)+MOD)%MOD;
            }
        }
    }
    return ans;
}

// 矩阵快速幂
vector<vector<int>> power(vector<vector<int>> m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//单位矩阵 相当于乘法快速幂中的1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//每次都是倍增
    }
    return ans;
}

int main()
{
    cin>>n>>m>>t>>a>>b;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        edge[++cnt]={u,v};
        edge[++cnt]={v,u};
    }

    if(t==0){
        cout<<(a==b?1:0)<<endl;
        return 0;
    }
    if(m==0){
        cout<<0<<endl;
        return 0;
    }

    vector<vector<int>>base(cnt+1,vector<int>(cnt+1,0));
    for(int i=-0;i<=cnt;i++){
        for(int j=0;j<=cnt;j++){
            if(edge[i].to==edge[j].from){
                if(i!=(j^1)){
                    base[i][j]=1;
                }
            }
        }
    }

    vector<vector<int>>init(1,vector<int>(cnt+1,0));
    for(int i=0;i<=cnt;i++){
        if(edge[i].from==a){
            init[0][i]=1;
        }
    }

    vector<vector<int>>vec=multiply(init,power(base,t-1));
    int ans=0;
    for(int i=0;i<=cnt;i++){
        if(edge[i].to==b){
            ans=(ans+vec[0][i])%MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}