// 用途：可持久化线段树支持历史版本单点修改。
// 时间：O((n+q)log n)。
// 空间：O((n+q)log n)。
// 例题：https://www.luogu.com.cn/problem/P3919
// 题意：单点修改生成新版本，查询任意版本的指定位置。
// 思路：仅复制根到修改点的路径，其余子树共享。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;
const int MAXT = MAXN * 23;

int n, m;

// 原始数组
int arr[MAXN];

// 可持久化线段树需要
// root[i] : i号版本线段树的头节点编号
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// value[i] : 节点i的值信息，只有叶节点有这个信息
int value[MAXT];

// 可持久化线段树的节点空间计数
int cnt = 0;

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

// 建树，返回头节点编号
int build(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        value[rt] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

// 线段树范围l~r，信息在i号节点里
// 在l~r范围上，jobi位置的值，设置成jobv
// 生成的新节点编号返回
int update(int jobi, int jobv, int l, int r, int i) {
    int rt = ++cnt;//新建一个节点（沿途节点）
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    value[rt] = value[i];
    //拷贝原有信息
    if (l == r) {
        //到达了要修改的节点位置
        value[rt] = jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
        } else {
            rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

// 线段树范围l~r，信息在i号节点里
// 返回l~r范围上jobi位置的值
int query(int jobi, int l, int r, int i) {
	if (l == r) {
		return value[i];
	}
	int mid = (l + r) >> 1;
	if (jobi <= mid) {
		return query(jobi, l, mid, ls[i]);
	} else {
		return query(jobi, mid + 1, r, rs[i]);
	}
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    root[0]=build(1,n);
    for(int i=1;i<=m;i++){
        int op,x,y,version;
        version=read(),op=read(),x=read();
        if(op==1){
            y=read();
            root[i]=update(x,y,1,n,root[version]);
        }
        else{
            root[i]=root[version];
            cout<<query(x,1,n,root[version])<<endl;
        }
    }
    return 0;
}
