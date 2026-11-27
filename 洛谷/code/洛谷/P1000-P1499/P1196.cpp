// https://www.luogu.com.cn/problem/P1196
// 题意：有 30000 艘战舰，开始时各自成列。
// M i j 把 i 所在整列接到 j 所在列的尾部，列内顺序保持原样。
// C i j 查询同列时两舰之间的战舰数，不同列输出 -1。
// 数据范围：1 ≤ T ≤ 5 × 10^5，
// 1 ≤ i, j ≤ 30000，i ≠ j，合并前两舰分属不同列。
// 算法标签：并查集

#include<bits/stdc++.h>
using namespace std;

int fa[30005],sz[30005],last[30005];
int father[30005];


int find(int i){
    if (i != father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

void un(int x,int y){
    if(find(x)==find(y)){
        return ;
    }
    else{
        fa[y]=x;
        while(fa[x]!=x){
            //fa[y]=x;
            sz[x]+=sz[y];
            x=fa[x];
        }
        father[y]=x;
        sz[x]+=sz[y];
        last[x]=last[y];
    }
}

int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=30000;i++){
        fa[i]=i;
        sz[i]=1;
        last[i]=i;
        father[i]=i;
    }
    while(t--){
        char c;
        int a,b;
        cin>>c>>a>>b;
        if(c=='M'){
            un(last[find(b)],find(a));
        }
        else{
            if(find(a)!=find(b)){
                cout<<-1<<endl;
            }
            else{
                cout<<abs(sz[a]-sz[b])-1<<endl;
            }
        }
    }
    return 0;
}
