// https://www.luogu.com.cn/problem/P3623
// 题意：输入村庄数 N、道路数 M、目标鹅卵石路数 K，以及每条无向边 (u_i, v_i, c_i)（c_i=0 为鹅卵石路，c_i=1 为水泥路）。
// 需选出一条连通所有村庄的生成树（恰好 N-1 条边且任意两点间路径唯一），使得其中恰好包含 K 条鹅卵石路。
// 若不存在合法方案输出 no solution，否则输出所选的 N-1 条边（格式同输入），有多解可任选其一。
// 数据范围：1 <= N <= 2*10^4，1 <= M <= 10^5，0 <= K <= N-1，任意两村间至多一条路。
#include<bits/stdc++.h>
// 算法标签：Kruskal、并查集、贪心
using namespace std;
const int MAXN = 2e4+5;
const int MAXM = 1e5+5;

int n,m,k;
int fa[MAXN];
struct node{
    int u,v;
    int op;
};
int cnt1;
node nums1[MAXM];
int cnt2;
node nums2[MAXM];

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u,v,op;
        u=read(),v=read(),op=read();
        if(op==0){
            nums2[++cnt2]={u,v,0};
        }
        else{
            nums1[++cnt1]={u,v,0};
        }
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=cnt1;i++){
        int fx=find(nums1[i].u);
        int fy=find(nums1[i].v);
        if(fx!=fy){
            fa[fx]=fy;
        }
    }
    int now=0;
    for(int i=1;i<=cnt2;i++){
        int fx=find(nums2[i].u);
        int fy=find(nums2[i].v);
        if(fx!=fy){
            fa[fx]=fy;
            nums2[i].op=1;
            now++;
        }
    }
    if(now>k){
        cout<<"no solution"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=cnt2;i++){
        if(nums2[i].op==1){
            int fx=find(nums2[i].u);
            int fy=find(nums2[i].v);
            if(fx!=fy){
                fa[fx]=fy;
            }
        }
    }
    int i=1;
    while(now<k&&i<=cnt2){
        if(!nums2[i].op){
            int fx=find(nums2[i].u);
            int fy=find(nums2[i].v);
            if(fx!=fy){
                fa[fx]=fy;
                nums2[i].op=true;
                now++;
            }
        }
        i++;
    }
    if(now!=k){
        cout<<"no solution"<<endl;
        return 0;   
    }
    for(int i=1;i<=cnt1;i++){
        int fx=find(nums1[i].u);
        int fy=find(nums1[i].v);
        if(fx!=fy){
            fa[fx]=fy;
            nums1[i].op=true;
        }
    }
    for(int i=1;i<=cnt1;i++){
        if(nums1[i].op){
            cout<<nums1[i].u<<' '<<nums1[i].v<<' '<<1<<endl;
        }
    }
    for(int i=1;i<=cnt2;i++){
        if(nums2[i].op){
            cout<<nums2[i].u<<' '<<nums2[i].v<<' '<<0<<endl;
        }
    }
    return 0;
}