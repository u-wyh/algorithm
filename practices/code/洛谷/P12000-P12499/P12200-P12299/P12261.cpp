// https://www.luogu.com.cn/problem/P12261
// 题意：用一条下端在 x 轴上的竖直线段挡住所有激光炮线段，求最短长度。
// 输入：首行给激光炮数 n，后 n 行每行给 a_i, b_i。
// 规则：第 i 条激光是从 (-10^5, a_i) 连向 (10^5, b_i)
// 的线段。
// 规则：需选某横坐标放置竖直线段（底端在 y=0），与所有线段相交。
// 输出：输出一行浮点数表示最短长度，四舍五入保留 2 位小数。
// 数据范围：1 <= n <= 10^5，
// 0 <= a_i, b_i <= 10^6。
// 难度评分：1400（洛谷分级换算）
// 算法标签：三分搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const double eps = 1e-6;

int n;
int a[MAXN],b[MAXN];

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

double compute(double x){
    double ans=INT_MIN;
    for(int i=1;i<=n;i++){
        ans=max(ans,a[i]-(a[i]-b[i])*1.0/200000*(100000+x));
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read(),b[i]=read();
    }
    double l=-100000,r=100000,ans;
    while(r-l>=eps){
        double midl=l+(r-l)/3;
        double midr=l+(r-l)*2/3;
        double k1=compute(midl);
        double k2=compute(midr);
        if(k1<k2){
            r=midr;
            ans=midl;
        }
        else{
            l=midl;
            ans=midr;
        }
    }
    printf("%.2lf\n",compute(ans));
    return 0;
}