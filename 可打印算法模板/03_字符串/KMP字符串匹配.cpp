// 用途：输出文本中模式串的所有匹配起点及 next 数组。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 注意：字符串不含空白；下标从 1 开始。
// 例题：https://www.luogu.com.cn/problem/P3375
// 题意：输出模式串在文本中的所有匹配位置。
// 思路：next 数组记录失配后的最长可复用前缀，扫描时免去回退文本指针。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;
// nxt[i] 是模式串前 i 位的最长真前后缀长度。
int nxt[MAXN];
char s1[MAXN],s2[MAXN];

void calcnext(){
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
        while(j>0&&s2[i]!=s2[j+1]){
            j=nxt[j];
        }
        if(s2[i]==s2[j+1]){
            j++;
        }
        nxt[i]=j;
    }
}

void kmp(){
    n=strlen(s1+1);
    m=strlen(s2+1);
    calcnext();
    for(int i=1,j=0;i<=n;i++){
        while(j>0&&s1[i]!=s2[j+1]){
            j=nxt[j];
        }
        if(s1[i]==s2[j+1]){
            j++;
        }
        if (j == m) {
            cout << i - m + 1 << endl;
            j = nxt[j];
        }
    }
}

int main()
{
    scanf("%s %s",s1+1,s2+1);
    kmp();
    for(int i=1;i<=m;i++){
        printf("%d ",nxt[i]);
    }
    cout<<endl;
    return 0;
}
