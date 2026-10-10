// https://www.luogu.com.cn/problem/P2347
#include<bits/stdc++.h>
using namespace std;

int a[7];
int b[7]={0,1,2,3,5,10,20};
int ans;
int m;
int c[1005];
int d[1005];

void compute(){
    for(int i=0;i<=a[1];i++){
        c[i]=1;
        m=a[1];
    }
    for(int i=2;i<=6;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=b[i]*a[i];k+=b[i]){
                d[j+k]+=c[j];
            }
        }
        m+=b[i]*a[i];
        for(int j=0;j<=m;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }
    for(int i=1;i<=m;i++){
        if(c[i]){
            ans++;
        }
    }
}

int main()
{
    for(int i=1;i<=6;i++){
        cin>>a[i];
    }
    compute();
    cout<<"Total="<<ans<<endl;
    return 0;
}