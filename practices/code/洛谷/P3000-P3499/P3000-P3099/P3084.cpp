// https://www.luogu.com.cn/problem/P3084
// 题意：输入排成一排的奶牛数量 N（编号 1 到 N）、照片数量 M，
// 以及每张照片覆盖的连续编号区间 [a_i, b_i]。
// 已知每张照片拍到的区间内有且仅有 1 头斑点奶牛。
// 求整群奶牛中最多可能有多少头斑点奶牛；若条件矛盾无解则输出 -1。
// 输出一个整数表示最大数量或 -1。
// 数据范围：1 <= N <= 2*10^5，1 <= M <= 10^5，
// 1 <= a_i <= b_i <= N。
// 难度评分：2500（洛谷分级换算）
// 算法标签：动态规划、单调队列
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int minl[MAXN];
int maxl[MAXN];
int f[MAXN];
int q[MAXN];
int head,tail;

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
    n=read(),m=read();
    for(int i=1;i<=n+1;i++){
        minl[i]=i;
    }
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        minl[r]=min(minl[r],l);
        maxl[r+1]=max(maxl[r+1],l);
    }
    for(int i=n;i>=1;i--){
        minl[i]=min(minl[i],minl[i+1]);
    }
    for(int i=1;i<=n+1;i++){
        maxl[i]=max(maxl[i],maxl[i-1]);
    }
    f[0]=1;
    head=1,tail=0;
    q[++tail]=0;
    int j=1;
    for(int i=1;i<=n+1;i++){
        while(j<minl[i]){
            if(f[j]==0){
                j++;
                continue;
            }
            while(head<=tail&&f[q[tail]]<f[j]){
                tail--;
            }
            q[++tail]=j;
            j++;
        }
        while(head<=tail&&q[head]<maxl[i]){
            head++;
        }

        if(head<=tail){
            f[i]=f[q[head]]+(i!=(n+1));
        }
    }
    printf("%d\n",f[n+1]-1);
    return 0;
}