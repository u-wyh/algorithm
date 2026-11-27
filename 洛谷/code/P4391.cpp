// https://www.luogu.com.cn/problem/P4391
// 题意：已知长度为 L 的字符串 S 是某个原串 S' 不断自我循环连接后的子串，求 S' 的最小可能长度。
// 数据范围：1 <= L <= 10^6，S 由小写字母组成。
#include<bits/stdc++.h>
// 算法标签：KMP
using namespace std;
const int MAXN = 1e6+5;

int n;
int nxt[MAXN];
char s2[MAXN];

// 计算1-based next数组
void calcnext(){
    nxt[1]=0;
    for(int i=2,j=0;i<=n;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&s2[i]!=s2[j+1]){
            j=nxt[j];
        }
        // 如果当前字符匹配，j增加
        if(s2[i]==s2[j+1]){
            j++;
        }
        // 设置当前位置的next值
        nxt[i]=j;
    }
}

int main()
{
    scanf("%d %s",&n,s2+1);
    calcnext();
    cout<<(n-nxt[n])<<endl;
    return 0;
}