#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int n;
string str;
int f[105][105];
int cnt[105];

bool check(int l,int r,int t,int len){
    for(int i=l;i<=r;i++){
        for(int j=2;j<=t;j++){
            if(str[i]!=str[i+(j-1)*len]){
                return false;
            }
        }
    }
    return true;
}

int main()
{
    cin>>str;
    n=str.length();
    str=' '+str;//使得可以从1开始
    for(int i=1;i<=9;i++){
        cnt[i]=1;
    }
    for(int i=10;i<=99;i++){
        cnt[i]=2;
    }
    cnt[100]=3;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            f[i][j]=INF;
        }
    }
    for(int i=1;i<=n;i++){
        f[i][i]=1;
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
            }
            for(int l=1;l<len;l++){
                if(len%l==0){
                    if(check(i,i+l-1,len/l,l)){
                        f[i][j]=min(f[i][j],f[i][i+l-1]+2+cnt[len/l]);
                    }
                }
            }
        }
    }
    cout<<f[1][n];
    return 0;
}