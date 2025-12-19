#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;

int m,p;
int f[MAXN<<1][MAXN];
int sum1[MAXN];
int sum2[MAXN];

int pay(int st,int len,int res){
    res-=sum1[st+len-1]-sum1[st-1];
    if(res<0){
        return -1;
    }
    return sum2[st+len-1]-sum2[st-1];
}

int main()
{
    cin>>m>>p;
    for(int i=1;i<=p;i++){
        int x,y;
        cin>>x>>y;
        sum1[i]=sum1[i-1]+x;
        sum2[i]=sum2[i-1]+y;
    }
    for(int i=0;i<=2*p+2;i++){
        for(int j=0;j<=p;j++){
            f[i][j]=INT_MAX;
        }
    }
    for(int i=0;i<p;i++){
        int t=pay(1,i,m);
        if(t==-1){
            break;
        }
        f[1][i]=t;
    }
    for(int i=2;;i++){
        for(int j=0;j<p;j++){
            for(int k=0;k+j<=p;k++){
                if(f[i-1][j]<=m){
                    int t=pay(j+1,k,m-f[i-1][j]);
                    if(t==-1){
                        break;
                    }
                    f[i][j+k]=min(f[i][j+k],t);
                }
            }
        }
        if(f[i][p]<=m){
            cout<<(i+2)<<endl;
            return 0;
        }
    }
    return 0;
}