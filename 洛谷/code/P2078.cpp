// https://www.luogu.com.cn/problem/P2078
// 题意：给定两家公司内部的朋友关系，朋友关系可传递，小明 1 和小红 −1 也是朋友。每人最多配对一次，求通过他们能认识的人最多能配成几对异性情侣，包含他们自己。
// 数据范围：1 ≤ N,M ≤ 10^4，1 ≤ P,Q ≤ 2×10^4，公司员工编号分别使用正数和负数。

#include<bits/stdc++.h>
using namespace std;
#define Max 10005

int father[Max],size[Max],stac[Max];

void build(int n){
    for(int i=0;i<=n;i++){
        father[i]=i;
        size[i]=1;
    }
}

int find(int i){
    int size=0;
    while(i!=father[i]){
        stac[size++]=i;
        i=father[i];
    }
    while(size>0){
        father[stac[--size]]=i;
    }
    return i;
}

bool issameset(int x,int y){
    return find(x)==find(y);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(size[fx]>=size[fy]){
            size[fx]+=size[fy];
            father[fy]=fx;
        }else{
            size[fy]+=size[fx];
            father[fx]=fy;
        }
    }
}


int main()
{
    int n,m,p,q;
    cin>>n>>m>>p>>q;
    build(n);
    int a,b;
    for(int i=1;i<=p;i++){
        cin>>a>>b;
        un(a,b);
    }
    int ans1=size[find(1)];
    build(m);
    for(int i=1;i<=q;i++){
        cin>>a>>b;
        un(abs(a),abs(b));
    }
    int ans2=size[find(1)];
    //printf("%d %d\n",ans1,ans2);
    printf("%d\n",min(ans1,ans2));
    return 0;
}

