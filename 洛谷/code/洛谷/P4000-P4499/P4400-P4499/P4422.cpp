// https://www.luogu.com.cn/problem/P4422
// 题意：1..N 岁的 N 个孩子在编号 >= 1 的车站下车，
// 实时处理 Q 条语句：M X A 表示 A 岁孩子在第 X 站下车；
// D Y B 查询当前已知在第 Y 站及之前下车
// 且年龄 >= B 的最年轻孩子年龄（无解输出 -1）。
// 数据范围：2 <= N, Q <= 2 * 10^5，
// 1 <= X, Y <= 10^9，1 <= A, B <= N。
// 算法标签：线段树、线段树上二分
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int tree[MAXN<<2];
int n,m;

void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=INT_MAX;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int pos,int val,int l,int r,int i){
    if(l==r){
        tree[i]=min(val,tree[i]);
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,val,l,mid,i<<1);
        }
        else{
            update(pos,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int pos,int age,int l,int r,int i){
    if(l==r){
        if(l>=age){
            return l;
        }
        return INT_MAX;
    }
    int mid=(l+r)/2;
    int ans=INT_MAX;
    if(age<=mid&&tree[i<<1]<=pos){
        ans=min(ans,query(pos,age,l,mid,i<<1));
    }
    if(ans!=INT_MAX)
        return ans;
    if(tree[i<<1|1]<=pos){
        ans=min(ans,query(pos,age,mid+1,r,i<<1|1));
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    build(1,n,1);
    for(int i=1;i<=m;i++){
        char op;
        int age,pos;
        cin>>op>>pos>>age;
        if(op=='M'){
            update(age,pos,1,n,1);
        }
        else{
            int ans=-1;
            if(tree[1]>pos){
                cout<<ans<<endl;
                continue;
            }
            ans=query(pos,age,1,n,1);
            if(ans==INT_MAX)
                ans=-1;
            cout<<ans<<endl;
        }
    }
    return 0;
}
