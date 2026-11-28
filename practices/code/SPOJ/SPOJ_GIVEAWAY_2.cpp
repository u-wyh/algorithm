// https://new3.spoj.com/problems/GIVEAWAY/
// 题意：给长度为 n 的数组和 q 次操作，下标从 1 开始。
// 0 a b c 查询 [a, b] 中大于等于 c 的元素个数。
// 1 a b 把下标 a 的元素改为 b。
// 输出：逐行输出 0 类查询的答案。
// 数据范围：1 <= n <= 5*10^5，
// 1 <= q <= 10^5，1 <= X_i, c <= 10^9。
// 查询满足 1 <= a <= b <= n。
// 修改满足 1 <= a <= min(n, 10^5)，
// 1 < b <= 10^9。
// 难度评分：1800（估算）
// 算法标签：分块、二分查找
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXB = 1e3+5;

int n,m;
int val[MAXN];
int sortv[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }

    for(int i=1;i<=n;i++){
        sortv[i]=val[i];
    }
    for(int i=1;i<=bnum;i++){
        sort(sortv+bl[i],sortv+br[i]+1);
    }
}

int query(int i,int val){
    int l=bl[i],r=br[i],ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sortv[mid]>=val){
            ans=br[i]-mid+1;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int compute(int l,int r,int v){
    int lb=bi[l];
    int rb=bi[r];
    int ans=0;
    if(lb==rb){
        for(int i=l;i<=r;i++){
            if(val[i]>=v){
                ans++;
            }
        }
    }
    else{
        for(int i=lb+1;i<rb;i++){
            ans+=query(i,v);
        }
        for(int i=l;i<=br[lb];i++){
            if(val[i]>=v){
                ans++;
            }
        }
        for(int i=bl[rb];i<=r;i++){
            if(val[i]>=v){
                ans++;
            }
        }
    }
    return ans;
}

void update(int pos,int v){
    int lb=bl[bi[pos]];
    int rb=br[bi[pos]];
    val[pos]=v;
    for(int i=lb;i<=rb;i++){
        sortv[i]=val[i];
    }
    sort(sortv+lb,sortv+rb+1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    prepare();

    cin>>m;
    for(int i=1;i<=m;i++){
        int op,a,b,c;
        cin>>op>>a>>b;
        if(op==0){
            cin>>c;
            cout<<compute(a,b,c)<<endl;
        }
        else{
            update(a,b);
        }
    }
    return 0;
}