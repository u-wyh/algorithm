// https://www.luogu.com.cn/problem/P12213
// 题意：在给定字符串中选一个前缀与一个后缀拼接成回文串，求最大长度。
// 输入：一行一个小写字母串 S。
// 规则：从 S 中取一个前缀和后缀顺次拼接，使新串为回文串。
// 输出：输出一行一个整数，表示能拼出的最长回文串长度。
// 数据范围：1 <= |S| <= 10^5，S 仅含小写英文字母。
// 算法标签：Manacher
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

char s[MAXN];
char t[MAXN];
char ss[MAXN<<1];
int ps[MAXN<<1];
int pt[MAXN<<1];
int rs[MAXN<<1];
int rt[MAXN<<1];

int n;

void manacherss(char *s) {
    n=strlen(s)*2+1;
    for(int i=0,j=0;i<n;i++){
        ss[i]=(i&1)==0?'#':s[j++];
    }
}

void manacher(char *s,int *p) {
    manacherss(s);
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(p[2 * c - i], r - i) : 1;
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        p[i] = len;
    }
}


int main()
{
    scanf("%s",s);
    int len=strlen(s);
    for(int i=0;i<len;i++){
        t[i]=s[len-1-i];
    }
    manacher(s,ps);
    manacher(t,pt);
    for(int i=n-1,j=n-1;i>=0;i--){
        while(i-ps[i]<j){
            rs[j]=i-j;
            j-=2;
        }
    }
    for(int i=n-1,j=n-1;i>=0;i--){
        while(i-pt[i]<j){
            rt[j]=i-j;
            j-=2;
        }
    }
    int ans=max(rs[0],rt[0]);
    for(int i=1;i<=len;i++){
        if(s[i-1]!=t[i-1]){
            break;
        }
        ans=max(ans,2*i+max(rs[2*i],rt[2*i]));
    }
    cout<<ans<<endl;
    return 0;
}