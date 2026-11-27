// https://www.luogu.com.cn/problem/P2307
// 题意：多组数据（以 -1 -1 结束），每组给出若干无向边（以 0 0 结束）。
// 判断每组数据中任意两个出现过的房间是否都有
// 且仅有一条简单路径相通（即构成一棵树）。
// 每组输出 1（是）或 0（否）。
// 数据范围：房间编号在 [1, 10^5] 内。
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

struct node{
    int st,en;
}edge[MAXN];
int cnt=0;
int used=MAXN;
int fa[MAXN];

void init(){
    for(int i=1;i<=used;i++){
        fa[i]=i;
    }
    cnt=0;
    used=0;
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

bool un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        return true;
    }else{
        return false;
    }
}

int main()
{
    while(true){
        init();
        int a,b;
        cin>>a>>b;
        while(a+b!=0&&a+b!=-2){
            used=max(used,max(a,b));
            edge[++cnt].st=a;
            edge[cnt].en=b;
            cin>>a>>b;
        }
        if(a+b==-2){
            break;
        }
        int flag=1;
        for(int i=1;i<=cnt;i++){
            if(!un(edge[i].st,edge[i].en)){
                cout<<0<<endl;
                flag=0;
                break;
            }
        }
        if(flag){
            int f=find(edge[1].st),flag1=1;
            for(int i=2;i<=cnt;i++){
                if(find(edge[i].st)!=f){
                    cout<<0<<endl;
                    flag1=0;
                    break;
                }
            }
            if(flag1){
                cout<<1<<endl;
            }
        }
    }
    return 0;
}
