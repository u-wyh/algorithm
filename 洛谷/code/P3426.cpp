// https://www.luogu.com.cn/problem/P3426
// 题意：输入一个仅由小写字母组成的非空目标字符串。
// 制作一个尽量短的字符串印章，每次盖章可将印章全部字符印到纸上任意一段等长区间；同位置允许重复印相同字符，不允许覆盖不同字符。
// 输出一个整数，表示能印出目标串的最短印章长度。
// 数据范围：目标字符串长度不超过 5*10^5，仅包含小写英文字母。
#include<bits/stdc++.h>
// 算法标签：KMP、动态规划
using namespace std;
const int MAXN = 5e5+5;

int n;
char s[MAXN];
int nxt[MAXN];

int f[MAXN];
int g[MAXN];

// 计算1-based next数组
void calcnext(){
    nxt[1]=0;
    for(int i=2,j=0;i<=n;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&s[i]!=s[j+1]){
            j=nxt[j];
        }
        // 如果当前字符匹配，j增加
        if(s[i]==s[j+1]){
            j++;
        }
        // 设置当前位置的next值
        nxt[i]=j;
    }
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    calcnext();
    for(int i=1;i<=n;i++){
        f[i]=i;
        int k=nxt[i];
        int candidate=f[k];
        if(g[candidate]>=i-candidate){
            f[i]=candidate;
        }
        g[f[i]]=i;
    }
    cout<<f[n]<<endl;
    return 0;
}