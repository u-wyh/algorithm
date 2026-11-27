// https://www.luogu.com.cn/problem/P7988
// 题意：给定 N 和一个 1..N 的排列。
// 对每个整数 x ∈ [0, N]（对应目标数 x + 0.5）
// 按排列顺序依次处理元素 i：
// 若此前已猜过某个 j < i 且回答为 "HI"（j > x+0.5）
// 或猜过某个 j > i 且回答为 "LO"（j < x+0.5），则跳过 i；
// 否则猜 i 并由 x+0.5 给出回答 "HI"（i > x+0.5）
// 或 "LO"（i < x+0.5）。
// 将所有回答拼接成字符串 S，对每个 x = 0..N，
// 求 S 中等于 "HILO" 的长度为 4 的连续子串个数。
// 第一行输入 N，第二行输入排列。
// 输出 N + 1 行对应 x = 0..N 的答案。
// 数据范围：1 <= N <= 2*10^5。
// 算法标签：笛卡尔树、单调栈、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int val[MAXN];

int ls[MAXN];
int rs[MAXN];
int st[MAXN];
int sta[MAXN];
int cnt[MAXN];

int ans[MAXN];

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

void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

void build(){
    int top=0;
    for(int i=1;i<=n;i++){
        int pos=top;
        while(pos>0&&val[st[pos]]>val[i]){
            pos--;
        }
        if(pos>0){
            rs[st[pos]]=i;
        }
        if(pos<top){
            ls[i]=st[pos+1];
        }
        st[++pos]=i;
        top=pos;
    }
}

void dfs(int u,int fa){
    // cout<<u<<' '<<fa<<' '<<sta[u]<<endl;
    cnt[u]=cnt[fa]+(sta[fa]==1&&sta[u]==0);
    // cout<<u<<":   "<<cnt[u]<<endl;
    if(ls[u]){
        sta[ls[u]]=1;
        dfs(ls[u],u);
    }
    else{
        ans[u-1]=cnt[u];
        // cout<<u<<' '<<u-1<<endl;
    }
    if(rs[u]){
        sta[rs[u]]=0;
        dfs(rs[u],u);
    }
    else{
        ans[u]=cnt[u]+(sta[u]==1);
        // cout<<u<<' '<<u<<endl;
    }
}

int main()
{
    n=read();
    int root=0;
    for(int i=1;i<=n;i++){
        int k=read();
        val[k]=i;
        if(i==1){
            root=k;
        }
    }
    build();
    dfs(root,0);
    for(int i=0;i<=n;i++){
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}