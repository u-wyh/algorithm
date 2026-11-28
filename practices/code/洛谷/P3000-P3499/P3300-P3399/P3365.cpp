// https://www.luogu.com.cn/problem/P3365
// 题意：输入二叉树节点数 n、各节点初始正整数 a_i，
// 以及节点 2..n 的父亲编号和左右儿子标记（根节点为 1）。
// 每次可将一个节点的值修改为任意整数（可为 0 或负数），
// 要求改造成严格的二叉搜索树（左子树均小于根、右子树均大于根）。
// 输出最少需要修改的节点数。
// 数据范围：n <= 10^5，a_i < 2^31。
// 难度评分：1600（洛谷分级换算）
// 算法标签：中序遍历、最长不下降子序列、二分查找
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];

//中序遍历数组
int m;
int arr[MAXN];
int f[MAXN];
int help[MAXN];

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

void inorder(int i){
    if(ls[i]){
        inorder(ls[i]);
    }
    arr[++m]=key[i];
    if(rs[i]){
        inorder(rs[i]);
    }
    return ;
}

//找到help数组中第一个比这个元素大或相等的位置
int find(int x){
    int l=1,r=m,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        key[i]=read();
    }
    for(int i=2;i<=n;i++){
        int fa,op;
        fa=read(),op=read();
        if(op==0){
            ls[fa]=i;
        }
        else{
            rs[fa]=i;
        }
    }
    inorder(1);
    for(int i=1;i<=n;i++){
        arr[i]-=i;
    }
    m=0;
    for(int i=1;i<=n;i++){
        int sub=find(arr[i]);
        if(sub==-1){
            help[++m]=arr[i];
        }
        else{
            help[sub]=arr[i];
        }
    }
    cout<<(n-m)<<endl;
    return 0;
}
