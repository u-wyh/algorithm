// https://www.luogu.com.cn/problem/P10390
// 题意：给 n 个正整数，求有多少个有序下标四元组 (i,j,k,l)，
// 满足四个下标互不相同，a[i] 整除 a[k]，且 a[j] 整除 a[l]。
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ a[i] ≤ 10^5。
// 算法标签：枚举倍数、计数统计

#include<iostream>
#define int __int128
using namespace std;
const int N=1e5+10;
const int P=1e5;

int read() {
    int s=0, w=1;
    char ch; ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0', ch=getchar();
    return s*w;
}

void print(int x) {
    if(x>=10) print(x/10);
    putchar(x%10+'0');
}

int n, ans, t[N], s[N], b[N];

signed main() {
    n=read();
    for(int i=1; i<=n; i++) t[read()]++;
    
    for(int i=1; i<=P; i++) {
        if(t[i]) {
            for(int j=i*2; j<=P; j+=i) {
                if(t[j]) {
                    b[i] += t[j];
                    s[j] += t[i];
                }
            }
            b[i] += (t[i]-1);
            s[i] += (t[i]-1);
            ans += (t[i] * b[i]);
        }
    }
    
    ans *= (ans + 1); // 无限制和 i=k && j=l 
    
    for(int i=1; i<=P; i++) {
        if(t[i]) {
            ans -= (t[i] * b[i] * b[i]); // i=j
            ans -= (t[i] * s[i] * s[i]); // k=l
            ans -= (2 * t[i] * b[i] * s[i]); // i=l || j=k
            ans += (t[i] * (t[i]-1)); // i=l && j=k 
        }
    }
    
    print(ans);
    return 0;
}