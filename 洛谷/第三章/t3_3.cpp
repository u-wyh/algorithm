#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;

int n;
int val[MAXN];
int sum[MAXN];
int minn[MAXN][MAXN];
int maxx[MAXN][MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        val[i+n]=val[i];
    }
    for(int i=1;i<=2*n;i++){
        sum[i]=sum[i-1]+val[i];
    }
    for(int i=1;i<=2*n;i++){
        for(int j=i+1;j<=2*n;j++){
            minn[i][j]=INT_MAX;
            maxx[i][j]=INT_MIN;
        }
    }

    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=2*n;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                int res=sum[j]-sum[i-1];
                minn[i][j]=min(minn[i][j],minn[i][k]+minn[k+1][j]+res);
                maxx[i][j]=max(maxx[i][j],maxx[i][k]+maxx[k+1][j]+res);
            }
        }
    }
    int minnans=INT_MAX;
    int maxxans=INT_MIN;
    for(int i=1;i<=n;i++){
        minnans=min(minnans,minn[i][i+n-1]);
        maxxans=max(maxxans,maxx[i][i+n-1]);
    }
    cout<<minnans<<' '<<maxxans<<endl;
    return 0;
}
/*
4
4 4 5 9
*/