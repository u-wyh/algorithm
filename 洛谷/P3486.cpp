#include<bits/stdc++.h>
using namespace std;
const int MAXN = 605;

int n,m;
int arr[MAXN][MAXN];
int sum[MAXN][MAXN];
int pre[MAXN];
int f[MAXN][MAXN];
int last[MAXN][MAXN];
stack<int>st;

int fun(int X1,int Y1,int X2,int Y2){
    if(X1>X2){
        return 0;
    }
    return sum[X2][Y2]+sum[X1-1][Y1-1]-sum[X2][Y1-1]-sum[X1-1][Y2];
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            cin>>arr[i][j];
            pre[i]+=arr[i][j];
        }
        pre[i]+=pre[i-1];
        //cout<<i<<' '<<pre[i]<<endl;
    }
    //cout<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+arr[i][j];
            //cout<<setw(3)<<sum[i][j];
        }
        //cout<<endl;
    }
    for(int i=1;i<n;i++){
        f[i][1]=pre[i]-sum[i-1][i];
        last[i][1]=0;
        for(int j=2;j<=min(i,m);j++){
            int ans1=0,ans2=0;
            for(int k=1;k<i;k++){
                if(f[k][j-1]&&f[k][j-1]+pre[i]-pre[k]-fun(k+1,k+2,i-1,i)>ans1){
                    ans1=f[k][j-1]+pre[i]-pre[k]-fun(k+1,k+2,i-1,i);
                    ans2=k;
                }
            }
            f[i][j]=ans1,last[i][j]=ans2;
        }
        //cout<<i<<": "<<f[i][1]<<endl;
    }
//    for(int i=1;i<n;i++){
//        cout<<i<<": ";
//        for(int j=1;j<=m;j++){
//            cout<<f[i][j]<<' '<<last[i][j]<<"      ";
//        }
//        cout<<endl;
//    }
    int ans1=0,ans2=n-1;
    for(int i=m;i<n;i++){
        if(f[i][m]>ans1){
            ans1=f[i][m];
            ans2=i;
        }
    }
    //cout<<ans2<<' '<<f[ans2][m]<<endl;
    for(int i=m;i>=1;i--){
        st.push(ans2);
        ans2=last[ans2][i];
    }
    while(!st.empty()){
        cout<<st.top()<<' ';
        st.pop();
    }
    return 0;
}
