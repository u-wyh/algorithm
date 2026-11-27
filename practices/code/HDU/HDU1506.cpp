// https://acm.hdu.edu.cn/showproblem.php?pid=1506
// 题意：多组数据，每组给 n 个宽为 1、高为 h_i 的条。
// 将各条相邻排成直方图，输入以 n=0 结束。
// 输出：每组输出底边贴合直方图底边的最大矩形面积。
// 数据范围：1 <= n <= 10^5，0 <= h_i <= 10^9。
// 算法标签：笛卡尔树、单调栈、深度优先搜索
#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

const int MAXN = 10000001;

int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int n;
int ans=0;
int sz[MAXN];

//如果没有变小的数字  那么建树就是一直往右边节点建立
//也不会有节点从栈中弹出
void build() {
    ans=0;
    for(int i=1;i<=n;i++){
        sz[i]=0;
        ls[i]=0;
        rs[i]=0;
    }
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            //单调栈  弹出不符合的元素
            pos--;
        }
        if (pos > 0) {
            //那么就是没有弹干净   那么当前节点就会成为栈顶节点的右孩子
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            //表示有元素弹出 那么一定是当前节点的左孩子节点
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;//加入栈中
        top = pos;
    }
}

void dfs(int u){
    sz[u]=1;
    if(ls[u]!=0){
        dfs(ls[u]);
    }
    if(rs[u]!=0){
        dfs(rs[u]);
    }
    sz[u]+=(sz[ls[u]]+sz[rs[u]]);
    //cout<<u<<' '<<sz[u]<<endl;
    ans=max(ans,sz[u]*arr[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    while(n!=0){
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        build();
        dfs(sta[1]);
        cout<<ans<<endl;
        cin>>n;
    }
    return 0;
}