// 用途：后缀数组求字典序与后缀排名。
// 时间：O(n log n)。
// 空间：O(n)。
// 注意：输入不含空白；n<=1e6，数组预留两倍下标空间。
// 例题：https://www.luogu.com.cn/problem/P3809
// 题意：把字符串所有后缀按字典序排序并输出顺序。
// 思路：按长度 1、2、4… 的前缀排名倍增排序。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n,m;
// 注意这里开的是二倍空间  这样可以减少很多判断语句
char s[MAXN];

//桶数组x[i] 辅助数组y[i] 计数数组c[i]
int x[MAXN];
int y[MAXN];
int c[MAXN];

// 后缀数组：排名第i的后缀的起始位置
int sa[MAXN];
// 排名数组：起始位置为i的后缀的排名
int rk[MAXN];
// height[i]表示的是排名为i和排名为i-1的最长公共前缀的长度
int height[MAXN];

void getsa(){
    for(int i=1;i<=n;i++){
        x[i]=s[i],c[x[i]]++;
    }
    for(int i=1;i<=m;i++){
        c[i]+=c[i-1];
    }
    for(int i=n;i>=1;i--){
        sa[c[x[i]]--]=i;
    }
    for(int k=1;k<=n;k<<=1){
        // 按照第二个关键字排序
        for(int i=0;i<=m;i++){
            c[i]=0;
        }
        for(int i=1;i<=n;i++){
            y[i]=sa[i];
        }
        for(int i=1;i<=n;i++){
            c[x[y[i]+k]]++;
        }
        for(int i=1;i<=m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n;i>=1;i--){
            sa[c[x[y[i]+k]]--]=y[i];
        }

        // 按照第一个关键字排序
        for(int i=0;i<=m;i++){
            c[i]=0;
        }
        for(int i=1;i<=n;i++){
            y[i]=sa[i];
        }
        for(int i=1;i<=n;i++){
            c[x[y[i]]]++;
        }
        for(int i=1;i<=m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n;i>=1;i--){
            sa[c[x[y[i]]]--]=y[i];
        }

        // 保存上一轮的组号到y数组
        for(int i=1;i<=n;i++){
            y[i]=x[i];
        }
        m=0;
        for(int i=1;i<=n;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]){
                // 第一个关键字组号相同  第二个关键字组号相同  那么这一次也是一个组
                x[sa[i]]=m;
            }
            else{
                x[sa[i]]=++m;
            }
        }
        if(m==n){
            break;
        }
    }
}

// 后缀i的前邻后缀是 sa[rk[i]-1]
void getheight(){
    for(int i=1;i<=n;i++){
        rk[sa[i]]=i;
    }
    for(int i=1,k=0;i<=n;i++){
        if(rk[i]==1){
            continue;
        }
        // 利用height性质：height[rk[i]] >= height[rk[i-1]] - 1
        if(k){
            k--;
        }
        int j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]){
            k++;
        }
        height[rk[i]]=k;
    }
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    m=122;
    getsa();
    getheight();
    for(int i=1;i<=n;i++){
        cout<<sa[i]<<' ';
    }
    return 0;
}
