// 用途：指数以十进制大整数给出时，计算 a^b mod m。
// 时间：O(log mod)。
// 空间：O(log mod)。
// 例题：https://www.luogu.com.cn/problem/P5091
// 题意：指数是十进制大整数，计算 a^b mod m。
// 思路：先求 φ(m)，读入大指数并根据扩展欧拉定理缩减指数。
#include<bits/stdc++.h>
using namespace std;
#define int long long

int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0){
                n/=i;
            }
        }
    }
    if(n>1){
        ans=ans/n*(n-1);
    }
    return ans;
}

int power(int a,int b,int p){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%p;
        }
        b>>=1;
        a=(a*a)%p;
    }
    return ans;
}

signed main()
{
    int a,m;
    string b;
    cin>>a>>m>>b;

    if(m==1){
        cout<<0<<endl;
        return 0;
    }

    int p=phi(m);
    int val=0;
    int num=0;
    bool big=false;

    for(char c:b){
        int x=c-'0';
        val=(val*10+x)%p;
        if(!big){
            num=num*10+x;
            if(num>=p){
                big=true;
            }
        }
    }

    if(big){
        val+=p;
    }
    else{
        val=num;
    }
    cout<<power(a,val,m)<<endl;
    return 0;
}
