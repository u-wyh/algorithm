#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = -1e15;

int n,m,k,r;
int h[7],c[7];
int hurt[100];
// int cost[100];

vector<vector<int>> multiply(vector<vector<int>> a,const vector<vector<int>> b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, INF));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                if(a[i][c]!=INF&&b[c][j]!=INF)
                    ans[i][j]=max(ans[i][j],a[i][c]+b[c][j]);
            }
        }
    }
    return ans;
}

vector<vector<int>> power(vector<vector<int>> m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 0;//单位矩阵 相当于乘法快速幂中的1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//每次都是倍增
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>k>>r;
        for(int i=0;i<n;i++){
            cin>>h[i]>>c[i];
        }
        // for(int i=0;i<n;i++){
        //     cin>>c[i];
        // }
        int N=1<<n;
        for(int i=0;i<N;i++){
            hurt[i]=0;
        }
        for(int s=0;s<N;s++){
            for(int i=0;i<n;i++){
                if(s&(1<<i)){
                    hurt[s]+=h[i];
                }
            }
        }
        vector<vector<int>>base(N,vector<int>(N,INF));
        for(int s=0;s<N;s++){
            for(int t=0;t<N;t++){
                int total=0;
                for(int i=0;i<n;i++){
                    if(t&(1<<i)){
                        total+=c[i];
                        if(s&(1<<i)){
                            total+=k;
                        }
                    }
                }
                if(total<=m){
                    base[s][t]=hurt[t];
                }
            }
        }
        vector<vector<int>>res=power(base,r);
        int ans=0;
        for(int j=0;j<N;j++){
            ans=max(ans,res[0][j]);
        }
        cout<<ans<<endl;
    }
    return 0;
}
/*
 3
 3 7 1 5
 59 3
 13 2
 81 4
 5 14 2 9
 66 8
 20 2
 25 4
 39 6
 57 7
 4 13 7 16
 18 2
 13 5
 33 4
 7 1
 */ 