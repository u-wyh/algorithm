// https://www.luogu.com.cn/problem/P6521
// 题意：给定 n 个互不相同的长度为 4 的字符串（字符为 a~z 或 0~9），求有多少对字符串恰好有 D 个对应位置的字符不同。
// 数据范围：2 <= n <= 5*10^4，1 <= D <= 4。
// 算法标签：容斥原理、二进制枚举、组合数学
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;

int n,k;
int c[5][5];
string str[MAXN];

signed main()
{
    for(int i=0;i<=4;i++){
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++){
            c[i][j]=c[i-1][j-1]+c[i-1][j];
        }
    }
    // for(int i=0;i<=4;i++){
    //     for(int j=0;j<=4;j++){
    //         cout<<c[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    cin>>n>>k;
    k=4-k;
    for(int i=1;i<=n;i++){
        cin>>str[i];
    }
    int res=0;
    for(int sta=0;sta<=15;sta++){
        int one=0;
        for(int i=0;i<4;i++){
            if(sta&(1<<i)){
                one++;
            }
        }
        if(one<k){
            continue;
        }
        map<string,int>cnt;
        int ans=0;
        for(int i=1;i<=n;i++){
            string key="";
            for(int j=0;j<4;j++){
                if(sta&(1<<j)){
                    key+=str[i][j];
                }
            }
            ans+=cnt[key];
            cnt[key]++;
        }
        int flag=((one-k)%2)?-1:1;
        res+=flag*c[one][k]*ans;
    }
    cout<<res<<endl;
    return 0;
}