#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 250005;

int n,k,m,num;

signed main()
{
    cin>>n>>k;
    //这道题最大的问题就是加入1不是加入到 k<n-m为止   而是尽可能的多加1   
    // 这样可以尽量减轻后面的压力
    while(m<n){
        if(k<(n-m-1)){
            break;
        }
        k-=(n-m-1);
        m++;
        cout<<1<<' ';
    }

    num=n-m+1;

    while(k!=0){
        while((num*(num-1)/2)>k){
            num--;
        }
        k-=(num*(num-1))/2;
        m+=num;
        // while(m>n){
        //     cout<<888<<endl;
        // }
        for(int i=1;i<=num;i++){
            cout<<(n+m-1)<<' ';
        }
    }

    for(int i=m+1;i<=n;i++){
        cout<<(i+n-1)<<' ';
    }

    return 0;
}