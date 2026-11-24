// 最短循环节的长度
// 给你一个字符串s，它一定是由某个循环节不断自我连接形成的
// 题目保证至少重复2次，但是最后一个循环节不一定完整
// 现在想知道s的最短循环节是多长
// 测试链接 : https://www.luogu.com.cn/problem/P4391
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
//最短循环节长度就是总长度减去整个字符串最大匹配的前后缀长度
//比如  abcabcabcabca
//前面 abcabcabca   后面abcabcabca
//原因是我们假设有k个循环节  一个不足一个的循环节
//那么最大匹配的前缀后缀一定是 (k-1)个循环节加上不足一个的循环节尾巴
//总长度是  k个循环节加上一个小尾巴  那么相减得到最终的最短结果
#include<bits/stdc++.h>
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