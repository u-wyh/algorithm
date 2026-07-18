// 将单词恢复初始状态所需的最短时间II
// 给你一个下标从0开始的字符串word和一个整数k
// 在每一秒，必须执行以下操作
// 移除word的前k个字符
// 在word的末尾添加k个任意字符
// 添加的字符不必和移除的字符相同
// 返回将word恢复到初始状态所需的最短时间
// 该时间必须大于零
// 测试链接 : https://leetcode.cn/problems/minimum-time-to-revert-word-to-initial-state-ii/
// 这道题的思路很巧妙  第一秒是从第k个字符开头  第二秒从第2*k个字符开头  以此类推（下标从0开始）
// 如果这个开头字符后面的字符和从0开头等长的字符相同  那么这个时间就是可以的
// 否则就是全部删除  然后用新来的建立出一个完整的字符串
// 还有一道很好的题目  P10716
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int z[MAXN];
char s[MAXN];
int k,n;

void zArray(char* s, int n) {
    z[0] = n;
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
    scanf("%s",s);
    n=strlen(s);
    cin>>k;
    zArray(s,n);
    int f=0;
    int ans=0;
//    for(int i=0;i<n;i++){
//        cout<<z[i]<<' ';
//    }
//    cout<<endl;
    for (int i = k; i < n; i += k) {
        if (z[i] == n - i) {
            f=1;
            ans=i / k;
            break;
        }
    }
    if(!f){
        ans=(n+k-1)/k;
    }
    cout<<ans;
    return 0;
}