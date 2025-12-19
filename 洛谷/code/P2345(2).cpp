#include<bits/stdc++.h>
using namespace std;
const int MAXN =20005;
#define int long long

struct Cow{
    int x;
    int v;
}cow[MAXN];
int n;
int tree1[MAXN],tree2[MAXN],ans=0;

bool cmp(Cow a,Cow b){
    return a.v<b.v;
}

int lowbit(int x){
    return x & -x;
}

void add(int *tree,int i,int v){
    while(i<=MAXN){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
    }
}

int sum(int i,int *tree){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
    }
    return ans;
}

void Add(int i){
    add(tree1,cow[i].x,1);
    add(tree2,cow[i].x,cow[i].x);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>cow[i].v>>cow[i].x;
    }
    sort(cow+1,cow+n+1,cmp);
//    for(int i=1;i<=n;i++){
//        printf("%4d %4d\n",cow[i].v,cow[i].x);
//    }
    int maxx=0;
    for(int i=1;i<=n;i++){
        maxx=max(maxx,cow[i].x);
        ans+=cow[i].v*((sum(cow[i].x-1,tree1)*cow[i].x-sum(cow[i].x-1,tree2))+
                       (sum(maxx,tree2)-sum(cow[i].x-1,tree2)-(sum(maxx,tree1)-sum(cow[i].x-1,tree1))*cow[i].x));
        //printf("%5d %5d %5d %5d %5d",sum(cow[i].x-1,tree1),sum(cow[i].x-1,tree2),sum(maxx,tree2)-sum(cow[i].x-1,tree2),sum(maxx,tree1)-sum(cow[i].x-1,tree1),ans);
        Add(i);
        //printf("%5d %5d\n",tree1[cow[i].x],tree2[cow[i].x]);
    }
    cout<<ans;
    return 0;
}
