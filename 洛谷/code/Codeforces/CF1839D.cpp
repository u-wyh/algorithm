// https://codeforces.com/problemset/problem/1839/D
// 题意：每组给 1..n 的排列作为一行彩球的颜色。
// 可在任一位置插入 0 号球，至多插 k 个。
// 花 1 枚硬币可将紧挨着 0 号球的彩球移至任意位置。
// 最后移除所有 0 号球，要使彩球按颜色升序排列。
// 输出：对 k = 1..n 依次输出最少硬币数。
// 数据范围：1 <= t, n <= 500。
// 所有组的 n 之和不超过 500。
// 算法标签：动态规划、树状数组
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int n;
int arr[MAXN];
int f[MAXN][MAXN];

int tree[MAXN];

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

inline int lowbit(int x){
    return x&(-x);
}

void update(int x,int val){
    while(x<=n){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            arr[i]=read();
        }
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                f[i][j]=0;
            }
        }
        for(int j=1;j<=n;j++){
            if(arr[j]>arr[j-1]){
                f[0][j]=j;
            }
            else{
                break;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(arr[j]>arr[j-1]){
                    f[i][j]=f[i][j-1]+1;
                }
                f[i][j]=max(f[i][j],query(arr[j])+1);
                update(arr[j],f[i-1][j]);
            }
            int res=n-f[i][n];
            for(int j=1;j<n;j++){
                res=min(res,j-f[i-1][j]+n-j);
            }
            printf("%d ",res);
            for(int i=1;i<=n;i++){
                tree[i]=0;
            }
        }
        printf("\n");
    }
    return 0;
}