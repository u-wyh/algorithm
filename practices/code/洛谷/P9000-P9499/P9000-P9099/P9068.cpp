// https://www.luogu.com.cn/problem/P9068
// 题意：给定长 n 的序列 a
// 定义两个逆序对 (i_1, j_1) 与
// (i_2, j_2)（满足 i<j, a_i>a_j）本质不同当
// 且仅当 a_{i_1} != a_{i_2} 或
// a_{j_1} != a_{j_2}。
// 支持 q 次非独立单点修改 a_x = y，
// 在初始及每次修改后输出本质不同逆序对个数。
// 数据范围：1 <= n <= 10^5，0 <= q <= 10^5，
// 1 <= a_i, x, y <= n（部分测试点空间限制 50MB）。
// 算法标签：CDQ分治、树状数组、双指针
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = MAXN*6;

int n,q;
int val[MAXN];
int lt[MAXN];
int rt[MAXN];
long long ans[MAXN];
set<int>pos[MAXN];

struct node{
    int x,y,t,k;
};
node nums[MAXM];
int cntm;

bool cmp(node &a,node &b){
    return a.x<b.x;
}

int tree[MAXN];

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void push(int x,int y,int t,int k){
    if(y==0){
        return ;
    }
    nums[++cntm]={x,y,t,k};
}

void change(int x,int t){
    int l=0,r=0;
    if(!pos[x].empty()){
        l=*pos[x].begin();
        r=*pos[x].rbegin();
    }

    if(l!=lt[x]){
        push(x,l,t,1);
        push(x,lt[x],t,-1);
        lt[x]=l;
    }
    if(r!=rt[x]){
        push(x,r,t,2);
        push(x,rt[x],t,-2);
        rt[x]=r;
    }
}

int sgn(int x){
    return x>0?1:-1;
}

void merge(int l,int mid,int r){
    int p1=mid;
    for(int p2=r;p2>mid;p2--){
        while(p1>=l && nums[p1].x>nums[p2].x){
            if(abs(nums[p1].k)==1){
                add(nums[p1].y,sgn(nums[p1].k));
            }
            p1--;
        }

        if(abs(nums[p2].k)==2){
            ans[nums[p2].t]+=1ll*sgn(nums[p2].k)*query(nums[p2].y-1);
        }
    }
    while(p1<mid){
        p1++;
        if(abs(nums[p1].k)==1){
            add(nums[p1].y,-sgn(nums[p1].k));
        }
    }

    int all=0;
    p1=l;
    for(int p2=mid+1;p2<=r;p2++){
        while(p1<=mid && nums[p1].x<nums[p2].x){
            if(abs(nums[p1].k)==2){
                int v=sgn(nums[p1].k);
                add(nums[p1].y,v);
                all+=v;
            }
            p1++;
        }

        if(abs(nums[p2].k)==1){
            ans[nums[p2].t]+=1ll*sgn(nums[p2].k)*(all-query(nums[p2].y));
        }
    }
    while(p1>l){
        p1--;
        if(abs(nums[p1].k)==2){
            add(nums[p1].y,-sgn(nums[p1].k));
        }
    }

    sort(nums+l,nums+r+1,cmp);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        pos[val[i]].insert(i);
    }

    for(int i=1;i<=n;i++){
        change(val[i],0);
    }

    cin>>q;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        if(val[x]==y){
            continue;
        }
        int old=val[x];

        pos[old].erase(x);
        change(old,i);
        val[x]=y;
        pos[y].insert(x);
        change(y,i);
    }

    cdq(1,cntm);

    for(int i=0;i<=q;i++){
        if(i){
            ans[i]+=ans[i-1];
        }
        cout<<ans[i]<<endl;
    }
    return 0;
}