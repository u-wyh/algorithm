#include<bits/stdc++.h>
using namespace std;

int n,m,len;
int nums[1005][1005],sum[1005][1005];

int fun(int a,int b,int c,int d){
    return sum[c][d]+sum[a-1][b-1]-sum[a-1][d]-sum[c][b-1];
}

int main()
{
    cin>>n>>m>>len;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+nums[i][j];
        }
    }
    int ans=sum[len][len],L=1,H=1;
    for(int a=1,c=a+len-1;c<=n;a++,c++){
        for(int b=1,d=b+len-1;b<=m;b++,d++){
            if(fun(a,b,c,d)>ans){
                ans=fun(a,b,c,d);
                L=a,H=b;
            }
        }
    }
    cout<<L<<' '<<H;
    return 0;
}
