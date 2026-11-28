// https://www.luogu.com.cn/problem/P3506
// 题意：输入整数序列长度 n、符号序列长度 k，整数序列 a_1..a_n，
// 以及由 <、>、= 构成的符号序列 s_1..s_k。
// 选出 a 的最长子序列 a_{i_1}, ..., a_{i_m}，
// 使任意相邻两项大小关系依次匹配符号 s_{((j-1) mod k) + 1}。
// 第一行输出最长子序列长度 m，
// 第二行输出任意一个满足条件的长度为 m 的子序列元素值。
// 数据范围：1 <= n, k <= 500000，
// 1 <= a_i <= 1000000，s_j 属于 {<, >, =}。
// 难度评分：2500（洛谷分级换算）
// 算法标签：动态规划、树状数组
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e6+5;

int n,m;
int maxval;
int val[MAXN];
char sign[MAXN];

int f[MAXN];
int pre[MAXN];
int tree1[MAXM];
int tree2[MAXM];
int eql[MAXM];

int anslen;
int endpos;

int lowbit(int x){
    return x&-x;
}

int calc(int x,int y){
    return f[x]>f[y]?x:y;
}

void update(int x,int val,int *tree){
    while(x<=maxval){
        tree[x]=calc(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x,int *tree){
    int ans=0;
    while(x){
        ans=calc(tree[x],ans);
        x-=lowbit(x);
    }
    return ans;
}

void compute(){
    for(int i=1;i<=n;i++){
        int best=eql[val[i]];

        best=calc(best,query(val[i]-1,tree1));
        best=calc(best,query(maxval-val[i],tree2));

        f[i]=f[best]+1;
        pre[i]=best;

        int nxtpos=(f[i]-1)%m+1;

        if(sign[nxtpos]=='<'){
            update(val[i],i,tree1);
        }
        else if(sign[nxtpos]=='='){
            eql[val[i]]=calc(eql[val[i]],i);
        }
        else{
            update(maxval-val[i]+1,i,tree2);
        }

        if(f[i]>anslen){
            anslen=f[i];
            endpos=i;
        }
    }
}

void dfs(int pos){
    if(pos){
        dfs(pre[pos]);
        cout<<val[pos]<<' ';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        maxval=max(maxval,val[i]);
    }
    for(int i=1;i<=m;i++){
        cin>>sign[i];
    }
    compute();
    cout<<anslen<<endl;
    dfs(endpos);
    return 0;
}