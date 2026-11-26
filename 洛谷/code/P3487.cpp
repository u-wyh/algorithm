// https://www.luogu.com.cn/problem/P3487
// 题意：输入目标子序列长度 k，以及长度未知（以单独 0 结尾，或按原交互库生成）的正整数序列 a_1..a_n。
// 在序列 a 中选出一个长度为 k 的子序列 a_{b_1}, ..., a_{b_k}（1 <= b_1 < ... < b_k <= n）
// 使其字典序最大。
// 输出 k 行，每行一个整数表示所选子序列的第 i 个元素；
// 注：洛谷评测需按提示粘贴交互封装代码并通过 inicjuj()/wczytaj()/wypisz() 读写。
// 数据范围：1 <= n <= 1.5*10^7，1 <= k <= min(n, 10^6)，1 <= a_i <= 10^9。
#include<bits/stdc++.h>
using namespace std;
const int MAXK = 1e6+5;
const int MAXN = 1e7+5e6+5;

int n,k;
vector<int>vec;
int sta[MAXN];
int top;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    k=read();
    n=read();
    while(n!=0){
        vec.push_back(n);
        n=read();
    }
    n=vec.size();
    for(int i=0;i<n;i++){
        while(top>0&&vec[i]>sta[top-1]&&(top-1+n-i)>=k){
            top--;
        }
        sta[top++]=vec[i];
    }
    for(int i=0;i<k;i++){
        printf("%d\n",sta[i]);
    }
    return 0;
}