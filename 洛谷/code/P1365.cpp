// https://www.luogu.com.cn/problem/P1365
// 题意：给一串点击结果，o 是成功，x 是失败，每个问号独立等概率变为 o 或 x。每段极大的连续成功长度为 a，就得 a² 分。
// 求总分期望，四舍五入保留四位小数。
// 数据范围：n ≤ 3 × 10^5，字符串只由 o、x 和问号组成。
// 算法标签：期望动态规划、递推

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
char s[MAXN];

int main()
{
    scanf("%d %s",&n,s+1);
    long double ans=0,len=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='o'){
            ans+=2*len+1;
            len+=1;
        }
        else if(s[i]=='x'){
            len=0;
        }
        else{
            ans+=len+0.5;
            len=(len+1)/2;;
        }
    }
    printf("%.4Lf",ans);
    return 0;
}