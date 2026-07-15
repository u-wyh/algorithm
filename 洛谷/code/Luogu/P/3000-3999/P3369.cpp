// FHQ-Treap，不用词频压缩，FHQ-Treap最常规的实现，C++版
// 实现一种结构，支持如下操作，要求单次调用的时间复杂度O(log n)
// 1，增加x，重复加入算多个词频
// 2，删除x，如果有多个，只删掉一个
// 3，查询x的排名，x的排名为，比x小的数的个数+1
// 4，查询数据中排名为x的数
// 5，查询x的前驱，x的前驱为，小于x的数中最大的数，不存在返回整数最小值
// 6，查询x的后继，x的后继为，大于x的数中最小的数，不存在返回整数最大值
// 所有操作的次数 <= 10^5
// -10^7 <= x <= +10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3369
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//词频不压缩的一个巨大优势是在删除和加入节点时非常方便  这也是fhq最常用的方法
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int head=0;
int cnt=0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];

void up(int x){
    sz[x]=sz[ls[x]]+sz[rs[x]]+1;
}

void split(int l,int r,int i,int val){
    if(i==0){
        rs[l]=ls[r]=0;
    }
    else{
        if(key[i]<=val){
            rs[l]=i;
            split(i,r,rs[i],val);
        }
        else{
            ls[r]=i;
            split(l,i,ls[i],val);
        }
        up(i);
    }
}

int merge(int l,int r){
    if(l==0||r==0){
        return l+r;
    }
    if(priority[l]>priority[r]){
        rs[l]=merge(rs[l],r);
        up(l);
        return l;
    }
    else{
        ls[r]=merge(l,ls[r]);
        up(r);
        return r;
    }
}

void add(int val){
    key[++cnt]=val;
    priority[cnt]=(double)rand()/RAND_MAX;
    sz[cnt]=1;
    split(0,0,head,val);
    head=merge(merge(rs[0],cnt),ls[0]);
}

void del(int val){
    split(0,0,head,val);
    int lm=rs[0];
    int r=ls[0];
    split(0,0,lm,val-1);
    int l=rs[0];
    int m=ls[0];
    head=merge(merge(l,merge(rs[m],ls[m])),r);
}

int getrank(int val){
    split(0,0,head,val-1);
    int ans=sz[rs[0]]+1;
    head=merge(rs[0],ls[0]);
    return ans;
}

int index(int i,int x){
    if(sz[ls[i]]>=x){
        return index(ls[i],x);
    }
    else if(sz[ls[i]]+1<x){
        return index(rs[i],x-sz[ls[i]]-1);
    }
    else{
        return key[i];
    }
}

int pre(int i,int val){
    if(i==0){
        return INT_MIN;
    }
    if(key[i]>=val){
        return pre(ls[i],val);
    }
    else{
        return max(key[i],pre(rs[i],val));
    }
}

int pre(int val){
    return pre(head,val);
}

int suf(int i,int val){
    if(i==0){
        return INT_MAX;
    }
    if(key[i]<=val){
        return suf(rs[i],val);
    }
    else{
        return min(key[i],suf(ls[i],val));
    }
}

int suf(int val){
    return suf(head,val);
}

int index(int x){
    return index(head,x);
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int op,x;
        cin>>op>>x;
        if(op==1){
            add(x);
        }
        else if(op==2){
            del(x);
        }
        else if(op==3){
            cout<<getrank(x)<<endl;
        }
        else if(op==4){
            cout<<index(x)<<endl;
        }
        else if(op==5){
            cout<<pre(x)<<endl;
        }
        else if(op==6){
            cout<<suf(x)<<endl;
        }
    }
    return 0;
}