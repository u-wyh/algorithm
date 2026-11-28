// https://www.luogu.com.cn/problem/P3455
// 题意：输入询问组数 n，接下来 n 行每行给出三个整数 a, b, d。
// 对每组询问，
// 求满足 1 <= x <= a、1 <= y <= b
// 且 gcd(x, y) = d 的有序整数对 (x, y) 的数量。
// 输出 n 行，每行一个整数表示对应询问的答案。
// 数据范围：1 <= n <= 5*10^4，
// 1 <= d <= a, b <= 5*10^4。
// 难度评分：2100（洛谷分级换算）
// 算法标签：莫比乌斯反演、线性筛、整除分块
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int mu[MAXN];

bool vis[MAXN];
int prime[MAXN];
int cnt;

void prepare(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            else{
                mu[i*prime[j]]=-mu[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        mu[i]+=mu[i-1];
    }
}

long long compute(int a,int b){
    long long ans=0;
    if(a>b){
        swap(a,b);
    }
    for(int l=1,r;l<=a;l=r+1){
        r=min(a/(a/l),b/(b/l));
        ans+=1ll*(mu[r]-mu[l-1])*(a/l)*(b/l);
    }
    return ans;
}

int main()
{
    prepare(MAXN-1);
    int T;
    cin>>T;
    while(T--){
        int a,b,d;
        cin>>a>>b>>d;
        cout<<compute(a/d,b/d)<<endl;
    }
    return 0;
}