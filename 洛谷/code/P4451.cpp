#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;

vector<vector<int>> multiply(vector<vector<int>> &a,vector<vector<int>> &b){
    int n=a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int c=0;c<k;c++){
                ans[i][j]+=a[i][c]*b[c][j];
                ans[i][j]%=MOD;
            }
        }
    }
    return ans;
}

vector<vector<int>> power(vector<vector<int>> m,int b){
    int n=m.size();
    vector<vector<int>> ans(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        ans[i][i]=1;
    }
    while(b){
        if(b&1){
            ans=multiply(ans,m);
        }
        m=multiply(m,m);
        b>>=1;
    }
    return ans;
}

void add(vector<vector<int>> &a,vector<vector<int>> &b){
    int n=a.size();
    int m=b[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            a[i][j]+=b[i][j];
            a[i][j]%=MOD;
        }
    }
}

signed main()
{
    string n;
    cin>>n;
    int len=n.length();
    vector<vector<int>>base={{2,1},{1,0}};
    vector<vector<int>>pw[10];
    for(int i=0;i<10;i++){
        pw[i] = vector<vector<int>>(2,vector<int>(2,0));
    }
    pw[0]={{1,0},{0,1}};
    for(int i=1;i<=9;i++){
        pw[i]=multiply(pw[i-1],base);
    }

    vector<vector<int>>ans={{1,0},{0,1}};
    for(int i=0;i<len;i++){
        int d=n[i]-'0';
        ans=power(ans,10);
        ans=multiply(ans,pw[d]);
    }
    cout<<ans[0][1]<<endl;
    return 0;
}