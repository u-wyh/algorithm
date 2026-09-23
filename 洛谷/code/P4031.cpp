// https://www.luogu.com.cn/problem/P4031
#include<bits/stdc++.h>
using namespace std;
#define int long long

int i,l,r,k,p,m;

int x,y,d;
int px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

// 矩阵相乘
// a的列数一定要等于b的行数
vector<vector<int>> multiply(vector<vector<int>>& a, const vector<vector<int>>& b,int mod) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]%=mod;
            }
        }
    }
    return ans;
}

// 矩阵快速幂
vector<vector<int>> power(vector<vector<int>>& m, int p,int mod) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//单位矩阵 相当于乘法快速幂中的1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m,mod);
        }
        m = multiply(m, m,mod);//每次都是倍增
    }
    return ans;
}

int compute(int n,int x,int dx){
    if(n<x){
        return 0;
    }
    return (n-x)/dx+1;
}

void solve(){
    vector<vector<int>> base={{0,1}};
    vector<vector<int>> vec={{0,1},{1,1}};
    vector<vector<int>> ans=multiply(base,power(vec,k-2,p),p);
    int a=ans[0][0];
    int b=ans[0][1];
    m=(m-(((__int128)a*i)%p)+p)%p;
    exgcd(b,p);
    if(m%d==0){
        x=m/d*x;
        int dx=p/d;
        if(x<=0){
            int delta=(dx-x)/dx;
            x+=delta*dx;
        }
        else{
            int delta=(x-1)/dx;
            x-=delta*dx;
        }

        int ans=0;
        if(l>0){
            ans=compute(r,x,dx)-compute(l-1,x,dx);
        }
        else{
            ans=compute(r,x,dx);
        }
        cout<<ans<<endl;
    }
    else{
        cout<<0<<endl;
    }
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>i>>l>>r>>k>>p>>m;
        solve();
    }
    return 0;
}