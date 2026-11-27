// https://www.luogu.com.cn/problem/P3820
// 题意：第一行输入行列数 N, M，
// 接下来 N 行每行 M 个字符描述地形（. 为温泉，* 为土），
// 随后输入操作数 Q 及 Q 行操作。
// 操作 1 w x1 y1 ... xw yw：在指定的 w 个位置中，
// 求各自所在四连通温泉块大小最大的位置编号
// （若为土则大小为 0，并列取输入靠前的编号
// 1..w）。
// 操作 2 w x1 y1 ... xw yw：
// 按顺序翻转这 w 个位置的地形（. 变 * 或 * 变 .），
// 且题目保证将温泉变土时不会把一个连通区域分割。
// 对每个操作 1 输出一行答案。
// 数据范围：对于 100% 的数据，
// 1 <= N*M, Q <= 10^6，sum
// w <= 10^6，w >= 1。
// 算法标签：并查集、深度优先搜索
#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[1000005],fa[1000005],sz[1000005];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct node {
    int x,y;
}num[1000005];

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx] = fy;
        sz[fy]+=sz[fx];
    }
}

void dfs(int x,int y,int k){
    for(int i=0;i<4;i++){
        int ux=x+walk[i][0];
        int uy=y+walk[i][1];
        int uk=(ux-1)*m+uy;
        if(ux>=1&&ux<=n&&uy>=1&&uy<=m&&nums[uk]==1&&fa[uk]==uk){
            un(uk,k);
            dfs(ux,uy,uk);
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n*m;i++){
        char c;
        cin>>c;
        if(c=='.'){
            nums[i]=1;
        }
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int k=(i-1)*m+j;
            if(fa[k]==k&&nums[i]==1){
                dfs(i,j,k);
            }
        }
    }
    int t;
    cin>>t;
    while(t--){
        int opt,w;
        cin>>opt>>w;
        if(opt==1){
            int ans=1,maxans=0;
            for(int i=1;i<=w;i++){
                cin>>num[i].x>>num[i].y;
                int k=(num[i].x-1)*m+num[i].y;
                int f=find(k);
                if(sz[f]>maxans){
                    ans=i;
                    maxans=sz[f];
                }
            }
            cout<<ans<<endl;
        }
        else{
            for(int i=1;i<=w;i++){
                cin>>num[i].x>>num[i].y;
                int k=(num[i].x-1)*m+num[i].y;
                if(nums[k]==0){
                    nums[k]=1;
                    for(int j=0;j<4;i++){
                        int ux=num[i].x+walk[j][0];
                        int uy=num[i].y+walk[j][1];
                        int uk=(ux-1)*m+uy;
                        if(ux>=1&&ux<=n&&uy>=1&&uy<=m&&nums[uk]==1){
                            un(uk,k);
                        }
                    }
                }
                else{
                    nums[k]=0;
                    sz[k]=1;

                }
            }
        }
    }
    return 0;
}
