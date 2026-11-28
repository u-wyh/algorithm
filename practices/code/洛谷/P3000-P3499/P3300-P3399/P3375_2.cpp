// https://www.luogu.com.cn/problem/P3375
// 题意：给主串 s1 和模式串 s2，
// 按从小到大的顺序输出 s2 在 s1 中每次出现的起点。
// 最后一行输出 |s2| 个数。
// 对 s2 的每个非空前缀，求它最长的相同真前缀和真后缀的长度。
// 这里的真前缀、真后缀都必须比正在处理的那段字符串短。
// 数据范围：1 ≤ |s1|, |s2| ≤ 10^6，两个串都只含大写英文字母。
// 难度评分：1500（洛谷分级换算）
// 算法标签：KMP

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;
char s[MAXN];
char t[MAXN];

int nxt[MAXN];

void calcnxt(){
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
        while(j>0&&t[i]!=t[j+1]){
            j=nxt[j];
        }
        if(t[i]==t[j+1]){
            j++;
        }
        nxt[i]=j;
    }
}

void kmp(){
    calcnxt();
    for(int i=1,j=0;i<=n;i++){
        while(j>0&&s[i]!=t[j+1]){
            j=nxt[j];
        }
        if(s[i]==t[j+1]){
            j++;
        }
        if(j==m){
            cout<<(i-m+1)<<endl;
            j=nxt[j];
        }
    }
}

int main()
{
    scanf("%s %s",s+1,t+1);
    n=strlen(s+1);
    m=strlen(t+1);

    kmp();
    for(int i=1;i<=m;i++){
        cout<<nxt[i]<<' ';
    }
    return 0;
}