// https://www.luogu.com.cn/problem/P1406
// 题意：给 n² 个整数，把它们全部填进 n×n 的方格，
// 让每行、每列和两条主对角线的和都一样。先输出这个和，再输出填法。
// 多解时按逐行展开后的数字序列取字典序最小者。
// 数据范围：1 ≤ n ≤ 4，-10^8 ≤ a[i] ≤ 10^8，保证有解。
// 难度评分：1300（洛谷分级换算）
// 算法标签：深度优先搜索、剪枝

#include<bits/stdc++.h>
using namespace std;
int n,i,a[6][6],b[30],vis[30],sum;//vis数组用于标记
void dfs(int x,int y,int z){
    if (y>n){
        if (z!=sum) return;
        x++,y=1,z=0;
    }
    if (x>n){
        for (int i=1;i<=n;i++){
            for (int j=1;j<n;j++) printf("%d ",a[i][j]);
            printf("%d\n",a[i][n]);
        }
        exit(0);//优化3
    }
    for (int i=1;i<=n*n;i++)
        if (!vis[i]){//优化2
            if (y==n && z+b[i]!=sum) continue;
            if (x==n){
                int s=0;
                for (int j=1;j<n;j++) s+=a[j][y];
                if (s+b[i]!=sum) continue;
            }
            if (x==n && y==1){
                int s=0;
                for (int j=1;j<n;j++) s+=a[j][n-j+1];
                if (s+b[i]!=sum) continue;
            }
            if (x==n && y==n){
                int s=0;
                for (int j=1;j<n;j++) s+=a[j][j];
                if (s+b[i]!=sum) continue;
            }
            a[x][y]=b[i];
            vis[i]=1;
            dfs(x,y+1,z+b[i]);
            vis[i]=0;
        }
}
int main(){
    cin>>n;
    for (i=1;i<=n*n;i++) scanf("%d",&b[i]),sum+=b[i];//优化1
    sum/=n;
    cout<<sum<<endl;
    sort(b+1,b+n*n+1);//把b数组从小到大排序后第一次查找到的结果即为字典序最小的
    dfs(1,1,0);
}
