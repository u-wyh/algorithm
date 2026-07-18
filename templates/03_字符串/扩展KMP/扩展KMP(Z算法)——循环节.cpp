//https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=396
// 这里使用扩展KMP求解最短循环节的长度的原理是z数组的含义是以i为首的的后缀子串与字符串的最大匹配的长度
// 利用的原理是 如果1~len = n-len+1~n   那么循环节长度就是n-len
// 基于此可以使用KMP的nxt数组（表示以i为首的后缀子串的前缀 和后缀的 最大匹配长度）
// 也同样可以使用哈希枚举最长的后缀  时间复杂度都是O(n)
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN = 101;

int z[MAXN];
char a[MAXN];
int n;

void zArray(char* s, int n) {
    z[0] = 0;
    for (int i = 1, c = 1, r = 1, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && s[i + len] == s[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        scanf("%s",a);
        n=strlen(a);
        zArray(a,n);
        int ans=n;
        for(int i=1;i<n;i++){
            if(n%i==0&&i+z[i]==n){
                ans=i;
                break;
            }
        }
        cout<<ans<<endl<<endl;
    }
    return 0;
}