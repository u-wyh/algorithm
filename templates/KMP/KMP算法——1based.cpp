// https://www.luogu.com.cn/problem/P3375
//这是一个1based的kmp算法
//在这里  next数组表示的是从1~i位置最大的前后缀匹配长度
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;
// nxt[i]表示的是从1到i这些字符串  前后缀匹配的最大长度（不能是整体）
// 因为我们用s2[i+1]来匹配s1[j]  如果匹配不上  那么i变成的是nxt[i]
int nxt[MAXN];
char s1[MAXN],s2[MAXN];

// 计算1-based next数组
void calcnext(){
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
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

void kmp(){
    n=strlen(s1+1);
    m=strlen(s2+1);
    calcnext();
    for(int i=1,j=0;i<=n;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&s1[i]!=s2[j+1]){
            j=nxt[j];
        }
        // 如果当前字符匹配，j增加
        //否则 说明无法匹配上当前的s1字符  只能向下移动一位
        if(s1[i]==s2[j+1]){
            j++;
        }
        // 完全匹配成功
        if (j == m) {
            // 输出匹配位置(1-based)
            cout << i - m + 1 << endl;
            // 继续寻找下一个匹配
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