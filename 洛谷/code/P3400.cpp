// https://www.luogu.com.cn/problem/P3400
// 题意：输入矩阵行数 n、列数 m，以及 n×m 的 0/1 矩阵（0 表示破坏，1 表示完好）。
// 统计内部完全不含 0（全部由完好格子组成）的子矩阵总数。
// 输出一个正整数表示子矩阵个数。
// 数据范围：n, m <= 3000。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int n,m;
int arr[MAXN][MAXN];

int sta[MAXN];
int top;
int f[MAXN];
long long sum[MAXN];
long long ans;

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
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            arr[i][j]=read();
        }
    }

    for(int i=1;i<=n;i++){
        int top=0;
        for(int j=1;j<=m;j++){
            if(arr[i][j]==0){
                f[j]=i;
            }

            while(top&&f[sta[top]]<f[j]){
                top--;
            }
            sta[++top]=j;

            sum[top]=sum[top-1]+(i-f[j])*(sta[top]-sta[top-1]);
            ans+=sum[top];
        }
    }
    printf("%lld",ans);
    return 0;
}