#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int a,b,c;
int mod;

vector<vector<int>> multiply(vector<vector<int>>a,vector<vector<int>>b){
    int n=a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int p=0;p<k;p++){
                ans[i][j]+=a[i][p]*b[p][j];
                ans[i][j]%=mod;
            }
        }
    }
    return ans;
}

vector<vector<int>> power(vector<vector<int>> a,int p){
    int n=a.size();
    vector<vector<int>>base(n,vector<int>(n,0));
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
    cin>>n>>a>>b>>c>>mod;
    vector<vector<int>>nums(1,vector<int>(3,1));
    vector<vector<int>>base(3,vector<int>(3,0));
    base[0][0]=a+b;
    base[1][0]=b,base[1][1]=a+b;
    base[2][0]=c,base[2][2]=1;
    nums=multiply(nums,power(base,n-1));
    //cout<<nums[0][0]<<' '<<nums[0][1]<<' '<<nums[0][2]<<endl;
    cout<<nums[0][0]<<endl;
    return 0;
}