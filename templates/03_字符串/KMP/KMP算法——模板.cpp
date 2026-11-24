//https://www.luogu.com.cn/problem/P3375
//注意这道题中的next数组要算到m   也就是s[i]的border存储在next[i+1]
//这个程序中的next数组含义是 nxt[i]表示从0~i-1位置上的最大前后缀相同长度
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

char s1[MAXN];
char s2[MAXN];
int Next[MAXN];
int n,m;

// 计算next数组
//计算next数组时   存在一种nextval优化 
//即如果跳到下一个位置和这一个位置是一样的  那么这个位置不行  下一个位置也是不行的
//所以可以继续跳   但是这道题不行  因为这道题是多次匹配  即s2一个位置上的字符可能属于多个匹配
//比如  ababa   abababa
void nextArray() {
    if (m == 1) {
        Next[0] = -1;
        return ;
    }

    Next[0] = -1;
    Next[1] = 0;

    int i = 2, cn = 0;
    while (i <= m) {
        if (s2[i - 1] == s2[cn]) {
            Next[i++] = ++cn;
        } else if (cn > 0) {
            cn = Next[cn];
        } else {
            Next[i++] = 0;
        }
    }
}

// KMP算法的核心函数
void kmp() {
    n = strlen(s1), m = strlen(s2);
    int x = 0, y = 0;
    nextArray();
    // s1中当前比对的位置是x
    // s2中当前比对的位置是y
    while (x < n) {
        if (s1[x] == s2[y]) {
            x++;
            y++;
        } else if (y == 0) {
            x++;
            //表示s2已经在第一个位置了
        } else {
            y = Next[y];
            //表示s2往前跳
        }
        if(y==m){
            cout<<x-y+1<<endl;
            y=Next[y];
        }
        if((n-x)<(m-y)){
            //根据长度进行剪枝
            break;
        }
    }
}

int main()
{
    cin>>s1>>s2;
    kmp();
    for(int i=1;i<=m;i++){
        printf("%d ",Next[i]);
    }
    cout<<endl;
    return 0;
}