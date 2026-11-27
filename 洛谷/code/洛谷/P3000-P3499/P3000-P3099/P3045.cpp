// https://www.luogu.com.cn/problem/P3045
// 题意：输入奶牛数 N、优惠券数 K、总预算 M，
// 以及每头牛的原价 P_i 和用券后价格 C_i。
// 每头奶牛最多使用一张优惠券将购买价从 P_i 降为 C_i，
// 在总花费不超过 M 的前提下尽可能多买奶牛。
// 计算最多能买到的奶牛数量。
// 输出一行一个整数，表示最多购买的奶牛数。
// 数据范围：对于 100% 的数据，1 <= K <= N <= 5*10^4，
// 1 <= C_i <= P_i <= 10^9
// 1 <= M <= 10^14。
// 算法标签：反悔贪心、优先队列
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 5e4+5;

int n,k,m;
int p[MAXN],c[MAXN];
bool bought[MAXN];
int ans=0;

priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>price,coupon;
priority_queue<int,vector<int>,greater<>>delta;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

signed main()
{
    n=read(),k=read(),m=read();
    for(int i=1;i<=n;i++){
        p[i]=read(),c[i]=read();
        price.push({p[i],i});
        coupon.push({c[i],i});
    }
    for(int i=1;i<=k;i++){
        delta.push(0);
    }
    while(!price.empty()){
        pair<int,int>tmp1=price.top();
        pair<int,int>tmp2=coupon.top();

        if(bought[tmp1.second]){
            price.pop();
            continue;
        }
        if(bought[tmp2.second]){
            coupon.pop();
            continue;
        }

        int d=delta.top();
        if(d+tmp2.first<=tmp1.first){
            m-=d+tmp2.first;
            delta.pop();
            coupon.pop();
            bought[tmp2.second]=true;
            delta.push(p[tmp2.second]-c[tmp2.second]);
        }
        else{
            m-=tmp1.first;
            price.pop();
            bought[tmp1.second]=true;
        }

        if(m>=0){
            ans++;
        }
        else{
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}