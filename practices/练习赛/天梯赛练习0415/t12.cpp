#include<bits/stdc++.h>
using namespace std;

int n,m;
int ans=0;

void dfs(vector<vector<int>>mat,int row,int col){
    if(row==m){
        for(int i=0;i<m;i++){
            int sum=0;
            for(int j=0;j<m;j++){
                sum+=mat[j][i];
            }
            if(sum!=n){
                return ;
            }
        }
        ans++;
        return ;
    }
    if(col==m){
        int sum=0;
        for(int i=0;i<m;i++){
            sum+=mat[row][i];
        }
        if(sum!=n){
            return ;
        }
        dfs(mat,row+1,0);
        return ;
    }
    int sum=0;
    for(int i=0;i<col;i++){
        sum+=mat[row][i];
    }
    int maxval=n-sum;
    sum=0;
    for(int i=0;i<row;i++){
        sum+=mat[i][col];
    }
    maxval=min(maxval,n-sum);
    for(int i=0;i<=maxval;i++){
        mat[row][col]=i;
        dfs(mat,row,col+1);
    }
}

int main()
{
    // for(int i=2;i<=9;i++){
    //     for(int j=3;j<=4;j++){
    //         n=i,m=j;
    //         vector<vector<int>>mat(m,vector<int>(m,0));
    //         ans=0;
    //         dfs(mat,0,0);
    //         cout<<n<<' '<<m<<' '<<ans<<endl;
    //     }
    // }
    cin>>n>>m;
    int a[]={0,0,21,55,120,231,406,666,1035,1540};
    int b[]={0,0,282,2008,10147,40176,132724,381424,981541,2309384};
    if(m==3){
        cout<<a[n];
    }
    else if(m==4){
        cout<<b[n];
    }
    else if(m==2){
        cout<<(n+1)<<endl;
        return 0;
    }
    return 0;
}