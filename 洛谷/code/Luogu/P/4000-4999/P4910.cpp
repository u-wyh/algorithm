#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;

vector<vector<int>> multiply(vector<vector<int>>a,vector<vector<int>>b){
    int n=a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int p = 0; p < k; p++) {
                ans[i][j] += a[i][p] * b[p][j];
                ans[i][j]%=mod;
            }
        }
    }
    return ans;
}

vector<vector<int>> power(vector<vector<int>> a,int p){
    int n=a.size();
    vector<vector<int>> base(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        base[i][i]=1;
    }
    while(p){
        if(p&1){
            base=multiply(base,a);
        }
        p>>=1;
        a=multiply(a,a);
    }
    return base;
}

signed main()
{
    vector<vector<int>>a={{2,1}};
    vector<vector<int>>base={{1,1},{1,0}};
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        if(n<=7){
            if(n==1){
                cout<<1<<endl;
            }
            else if(n==2){
                cout<<3<<endl;
            }
            else if(n==3){
                cout<<4<<endl;
            }
            else if(n==4){
                cout<<7<<endl;
            }
            else if(n==5){
                cout<<11<<endl;
            }
            else if(n==6){
                cout<<18<<endl;
            }
            else if(n==7){
                cout<<29<<endl;
            }
            continue;
        }
        int res=0;
        for(int i=0;i<=3;i++){
            vector<vector<int>>ans=multiply(a,power(base,n-i-3));
            res+=ans[0][0];
            res%=mod;
            //cout<<ans[0][0]<<' ';
        }
        //cout<<endl;
        cout<<res<<endl;
    }
    return 0;
}
