// https://www.luogu.com.cn/problem/P6824
// 题意：给定长为 n 的正整数序列 a 和整数 k，
// 选择一个非负整数 x 使得
// 满足 (a_i xor x) <= k 的 i 个数尽量多，求这个最大值。
// 数据范围：1 <= n, k, a_i <= 10^6。
// 算法标签：01字典树、枚举
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n,k;
int maxans=0;
int tree[MAXN][3];
int cnt=0;

void insert(int x){
    int u=0;
    //pass[u]++;
    for(int i=(1<<20);i>0;i>>=1){
        int a=x&i;
        if(!tree[u][a]){
            tree[u][a]=cnt++;
        }
        u=tree[u][a];
        tree[u][2]++;
    }
}

int query(int x){
    int u=0,ans=0;
    for(int i=(1<<20);i>0;i>>=1){
        int a=x&i;
        int b=k&i;
        if(b){
            ans+=tree[tree[u][1-(a^b)]][2];
        }
        u=tree[u][a^b];
        if(u==0){
            return ans;
        }
    }
    return ans+tree[u][2];
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        insert(num);
    }
    for(int i=1;i<=cnt;i++){
        cout<<setw(3)<<i<<": "<<tree[i][0]<<", "<<tree[i][1]<<", "<<tree[i][2]<<endl;
    }
    for(int i=0;i<=MAXN;i++){
        maxans=max(maxans,query(i));
        if(maxans==n)
            break;
    }
    cout<<maxans;
    return 0;
}
