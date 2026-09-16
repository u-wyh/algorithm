// 扩展KMP模版，又称Z算法或Z函数
// 给定两个字符串a、b，求出两个数组
// b与b每一个后缀串的最长公共前缀长度，z数组
// b与a每一个后缀串的最长公共前缀长度，e数组
// 计算出要求的两个数组后，输出这两个数组的权值即可
// 对于一个数组x，i位置的权值定义为 : (i * (x[i] + 1))
// 数组权值为所有位置权值的异或和
// 测试链接 : https://www.luogu.com.cn/problem/P5410
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20000001;

int n,m;
char a[MAXN];
char b[MAXN];
// b与b每一个后缀串的最长公共前缀长度
int z[MAXN];
// b与a每一个后缀串的最长公共前缀长度
int e[MAXN];

// 这个过程和Manacher算法大致流程是一样的 
// 判断此时的“对称点”和此时扩展到的右边界的位置的关系
// 对于右边界r和扩展到这个右边界的c而言 对称关系有c-0  c+1-1 c+2-2 '''
// 而对于此时的i而言  如果i在r的范围内  我们想要求的是的i-0 i+1-1 i+2-2 ''' i+len-len 的最大len
// 对于c而言  存在i-i-c i+1-i-c+1 '''   
// 那么它的对称点是 0-i-c  1-i-c+1 '''  也就是对称点为i-c
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

// 1based
// void zarray(){
//     z[1]=n;
//     for(int i=2,c=2,r=2,len;i<=n;i++){
//         len=r>i?min(r-i,z[i-c+1]):0;
//         while (i + len <= n && s[i + len] == s[len+1]) {
//             len++;
//         }
//         if (i + len > r) {
//             r = i + len;
//             c = i;
//         }
//         z[i] = len;
//     }
// }

// e数组需要在b字符串的z数组已经求出来的情况下进行计算得到
// 这个过程和求z数组大同小异
void eArray(char* a, char* b, int n, int m) {
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && len < m && a[i + len] == b[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
}

long eor(int* arr, int n) {
    long ans = 0;
    for (int i = 0; i < n; i++) {
        ans ^= (long) (i + 1) * (arr[i] + 1);
    }
    return ans;
}

int main()
{
    scanf("%s",a);
    n=strlen(a);
    scanf("%s",b);
    m=strlen(b);
    zArray(b,m);
    eArray(a,b,n,m);
    cout<<eor(z,m)<<endl;
    cout<<eor(e,n)<<endl;
    return 0;
}