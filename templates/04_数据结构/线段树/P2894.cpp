// 旅馆
// 一共有n个房间，编号1~n，一开始都是空房
// 实现如下两种操作，会一共调用m次
// 操作 1 x   : 找到至少有连续x个空房间的区域，返回最左编号
//              如果有多个满足条件的区域，返回其中最左区域的最左编号
//              如果找不到打印0，并且不办理入住
//              如果找到了打印最左编号，并且从最左编号开始办理x个人的入住
// 操作 2 x y : 从x号房间开始往下数y个房间，一律清空
// 操作1有打印操作，操作2没有
// 1 <= n 、m <= 50000
// 测试链接 : https://www.luogu.com.cn/problem/P2894
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;

int n,m;
//len表示区间上最长空置
int len[MAXN<<2];
//pre  suf数组还是左右起最长空置
int pre[MAXN<<2];
int suf[MAXN<<2];
int change[MAXN<<2];
bool update[MAXN<<2];

void up(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    len[i]=max(max(len[l],len[r]),suf[l]+pre[r]);
    pre[i]=len[l]<ln?pre[l]:pre[l]+pre[r];
    suf[i]=suf[r]<rn?suf[r]:suf[l]+suf[r];
}

void lazy(int i,int v,int n){
    len[i]=pre[i]=suf[i]= v==0 ?n:0;
    change[i]=v;
    update[i]=true;
}

void down(int i,int ln,int rn){
    if(update[i]){
        lazy(i<<1,change[i],ln);
        lazy(i<<1|1,change[i],rn);
        update[i]=false;
    }
}

void build(int l,int r,int i){
    if(l==r){
        len[i]=1;
        suf[i]=1;
        pre[i]=1;
    }else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i,mid-l+1,r-mid);
    }
}

void Update(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i, mid - l + 1, r - mid);
    }
}

int queryLeft(int x, int l, int r, int i) {
    if (l == r) {
        return l;
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        // 最先查左边
        if (len[i << 1] >= x) {
            return queryLeft(x, l, mid, i << 1);
        }
        // 然后查中间向两边扩展的可能区域
        if (suf[i << 1] + pre[i << 1 | 1] >= x) {
            return mid - suf[i << 1] + 1;
        }
        // 前面都没有再最后查右边
        return queryLeft(x, mid + 1, r, i << 1 | 1);
    }
}

int main()
{
    cin>>n>>m;
    build(1,n,1);
    for (int i = 1, op, x, y, left; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            cin>>x;
            if (len[1] < x) {
                left = 0;
            } else {
                left = queryLeft(x, 1, n, 1);
                Update(left, left + x - 1, 1, 1, n, 1);
            }
            cout<<left<<endl;
        } else {
            cin>>x>>y;
            Update(x, min(x + y - 1, n), 0, 1, n, 1);
        }
    }
    return 0;
}