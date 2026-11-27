#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;

int n,d;
int nums[MAXN][MAXN];

int main()
{
    cin>>n>>d;
    for(int i=1;i<=n-d;i++){
        for(int j=1;j<=n-d;j++){
            nums[i][j]=0;
        }
    }
    for(int i=1;i<=n-d;i++){
        for(int j=1;j<=d;j++){
            nums[i][j+n-d]=j-1;
        }
    }
    for(int j=1;j<=n-d;j++){
        for(int i=1;i<=d;i++){
            nums[i+n-d][j]=i-1;
        }
    }
    for(int i=1;i<=d;i++){
        for(int j=1;j<=d;j++){
            nums[i+n-d][j+n-d]=(i+j-2)%d;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<nums[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}