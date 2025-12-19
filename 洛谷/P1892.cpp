#include<bits/stdc++.h>
using namespace std;

int n,m,fa[2005];

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    fa[find(x)] = find(y);
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<=2*n;i++){
        fa[i]=i;
    }
    char s;
    int a,b;
    while(m--){
        cin>>s>>a>>b;
        if(s=='F'){
            un(a,b);
            //un(a+n,b+n);
        }
        if(s=='E'){
            un(b+n,a);
            un(a+n,b);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
/*
为什么不要un(a+n,b+n)
比如2是3的敌人，4是5的敌人，3与4是朋友
我们不能说3和 5（或2）是敌人  所以我们不能说2与5是朋友
那么如果只有5个人  并且合并了a+n,b+n
就会有：
2是3的敌人  2和8  3和7 朋友
4是5的敌人  5和9  4和10朋友
3与4是盆友  9和8朋友
导致推出了2—8—9—5  即2和5朋友   所以错误
*/
