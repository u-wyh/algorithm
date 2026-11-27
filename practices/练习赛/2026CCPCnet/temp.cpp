
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN=1e6+5;

int n,m,k;
int a[MAXN];
int f[MAXN];
int head[MAXN],nxt[MAXN];
int st[MAXN];

// 检查最大段和不超过 X 时，
// 是否能把环形数组划分成不超过 k 段
bool check(int X){
    int len=2*n;

    // 1. 双指针预处理每个位置的后继
    int r=1,sum=0;
    for(int i=1;i<=len;i++){
        while(r<=len&&sum+a[r]<=X){
            sum+=a[r];
            r++;
        }
        f[i]=r;
        sum-=a[i];
    }

    // 2. 反向建树
    // 原图 i -> f[i]
    // 反向图 f[i] -> i
    // 以 2n+1 为根
    fill(head+1,head+len+2,0LL);

    for(int i=1;i<=len;i++){
        nxt[i]=head[f[i]];
        head[f[i]]=i;
    }

    // 3. 非递归 DFS
    // st[dep] 表示当前 DFS 路径上的节点
    // st[0] 为根节点
    int dep=0;
    st[0]=len+1;

    while(dep>=0){
        int u=st[dep];

        // 只检查原数组的 n 个起点
        if(u<=n){
            // dep<k 表示 k 次跳跃已经到达终点
            // 否则查询当前节点的第 k 级祖先
            if(dep<k||st[dep-k]>=u+n){
                return true;
            }
        }

        if(head[u]==0){
            // 当前节点没有尚未访问的儿子
            dep--;
        }
        else{
            // 取出一个儿子，继续 DFS
            int v=head[u];
            head[u]=nxt[v];
            st[++dep]=v;
        }
    }

    return false;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m>>k;

    int S=0,mx=0;

    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i+n]=a[i];    // 破环成链
        S+=a[i];
        mx=max(mx,a[i]);
    }

    // 只有一道工序，答案就是工作量总和
    if(m==1){
        cout<<S<<'\n';
        return 0;
    }

    // 4. 二分最小的最大段和
    int l=mx,r=S;

    while(l<r){
        int mid=(l+r)/2;

        if(check(mid)){
            r=mid;
        }
        else{
            l=mid+1;
        }
    }

    // 5. 根据流水线公式计算答案
    cout<<S+(m-1)*l<<'\n';

    return 0;
}
