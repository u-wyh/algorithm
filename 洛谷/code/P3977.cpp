#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD = 1ll<<32;

int n,m,p,k;
int nums[3][6];
int val[65];
int cnt;

bool check(int sta){
    int s[6];
    for(int i=0;i<m;i++){
        s[i]=0;
        s[i]=(sta>>i)&1;
    }
    for(int i=0;i<m;i++){
        if(sta&(1<<i)){
            for(int j=0;j<p;j++){
                if(j!=k&&nums[1][j]==1){
                    int v=i-k+j;
                    if(v>=0&&v<m){
                        if(s[v]==1){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool check(int sta1,int sta2){
    int s2[6],s1[6];
    for(int i=0;i<m;i++){
        s1[i]=0;s2[i]=0;
        s1[i]=(sta1>>i)&1;
        s2[i]=(sta2>>i)&1;
    }

    for(int i=0;i<m;i++){
        if(sta1&(1<<i)){
            for(int j=0;j<p;j++){
                if(nums[2][j]==1){
                    int v=i-k+j;
                    if(v>=0&&v<m){
                        if(s2[v]==1){
                            return false;
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<m;i++){
        if(sta2&(1<<i)){
            for(int j=0;j<p;j++){
                if(nums[0][j]==1){
                    int v=i-k+j;
                    if(v>=0&&v<m){
                        if(s1[v]==1){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

vector<vector<int>> multiply(vector<vector<int>> a,const vector<vector<int>> b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += (a[i][c] * b[c][j])%MOD;
                ans[i][j]=((ans[i][j]%MOD)+MOD)%MOD;
            }
        }
    }
    return ans;
}

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

signed main()
{
    cin>>n>>m>>p>>k;
    for(int i=0;i<3;i++){
        for(int j=0;j<p;j++){
            cin>>nums[i][j];
        }
    }
    for(int i=0;i<(1<<m);i++){
        if(check(i)){
            val[cnt++]=i;
            // cout<<cnt<<' '<<val[cnt-1]<<endl;
        }
    }
    if(n==1){
        cout<<cnt<<endl;
        return 0;
    }
    vector<vector<int>>vec(cnt,vector<int>(cnt,0));
    for(int i=0;i<cnt;i++){
        for(int j=0;j<cnt;j++){
            if(check(val[i],val[j])){
                // cout<<val[i]<<' '<<val[j]<<endl;
                vec[j][i]=1;
            }
        }
    }
    vec=power(vec,n-1);
    int ans=0;
    for(int i=0;i<cnt;i++){
        for(int j=0;j<cnt;j++){
            ans+=vec[i][j];
            ans%=MOD;
        }
    }
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}