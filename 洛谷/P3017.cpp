#include<bits/stdc++.h>
using namespace std;
const int N = 505;

int r,c,A,B;
int a[N][N],s[N][N];

int fun(int X1,int Y1,int X2,int Y2){
    return s[X2][Y2]+s[X1-1][Y1-1]-s[X2][Y1-1]-s[X1-1][Y2];
}

bool check(int m){
    int col=1,row=1;
    int cnta=0;
    for(int i=1;i<=r;i++){
        int cntb=0;
        col=1;
        for(int j=1;j<=c;j++){
            if(fun(row,col,i,j)>=m){
                col=j+1;
                cntb++;
            }
        }
        if(cntb>=B){
            row=i+1;
            cnta++;
        }
    }
    return cnta>=A;
}

int main()
{
    cin>>r>>c>>A>>B;
    int L=0,R=0,mid,ans=0;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin>>a[i][j];
            s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
        }
    }
    R=s[r][c];
    while(L<=R){
        mid=L+((R-L)/2);
        if(check(mid)){
            ans=mid;
            L=mid+1;
        }else{
            R=mid-1;
        }
    }
    cout<<ans;
    return 0;
}
