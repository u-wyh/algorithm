// https://www.luogu.com.cn/problem/P10686
// 题意：
// 多组测试数据。每组有 N 名小朋友（0..N-1）玩 M 轮猜拳，给出胜负平关系（>, =, <）。
// 其中恰有 1 名裁判可出任意手势，其余人分属 3 组（可空）且各自只能固定出石头、剪子或布。
// 唯一确定裁判输出 Player x can be determined to be the judge after y lines（y 为最少轮数）。
// 若可能裁判多于 1 人输出 Can not determine；若仅有一名裁判也无法成立输出 Impossible。
// 数据范围：
// 1 <= N <= 500
// 0 <= M <= 2000
// 算法标签：扩展域并查集、枚举
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int n,m;
int fa[MAXN*3];
int cnt=0;
int ans,turn;
int alter[5],alternum=0;

void build(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        fa[i+n]=n+i;
        fa[i+2*n]=2*n+i;
    }
    cnt=0;
    ans=-1;
    turn=0;
    alternum=0;
    for(int i=0;i<5;i++){
        alter[i]=0;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    fa[find(x)] = find(y);
}

bool issameset(int x,int y){
    return find(x)==find(y);
}

void join(int u,int v,int i){
    cout<<666<<endl;
    int f=0;
    for(int i=0;i<alternum;i++){
        if(alter[i]==u){
            cout<<"ans:"<<u<<endl;
            f=1;
            ans=u;
            turn=i;
            cnt++;
        }
    }
    if(!f){
        alter[alternum++]=u;
    }
    f=0;
    for(int i=0;i<alternum;i++){
        if(alter[i]==v){
            cout<<"ans:"<<v<<endl;
            f=1;
            ans=v;
            turn=i;
            cnt++;
        }
    }
    if(!f){
        alter[alternum++]=v;
    }
    if(alternum>3)
        cnt=2;
}

int main()
{
    while(scanf("%d %d",&n,&m)==2){
        n++;
        build();
        for(int i=1;i<=m;i++){
            int u,v;
            char c;
            cin>>u>>c>>v;
            u++,v++;
            if(c=='>'){
                int temp=u;
                u=v;
                v=temp;
            }
            if(cnt>1)
                continue;
            if(issameset(v,u+n)||issameset(u,v+n)){
                cout<<777<<endl;
                join(u,v,i);
            }
            else{
                un(u+2*n,v);
                un(u,v+n);
                un(u+n,v+2*n);
            }
        }
        for(int i=0;i<alternum;i++){
            cout<<alter[i]<<' ';
        }
        cout<<endl;
        if(cnt>1){
            cout<<"Impossible"<<endl;
        }
        if(cnt==0){
            cout<<"Can not determine"<<endl;
        }
        ans--;
        if(cnt==1){
            cout<<"Player "<<ans<<" can be determined to be the judge after "<<turn<<" lines"<<endl;
        }
    }
    return 0;
}
