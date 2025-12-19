#include<bits/stdc++.h>
using namespace std;
int n,m,f[40001],x,y;
struct data
{
    int a,b,c;
} e[100001];

int gz(const data &a,const data &b){
    if(a.c>b.c)
        return 1;
    else
        return 0;
}

int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1; i<=m; i++)
        scanf("%d %d %d",&e[i].a,&e[i].b,&e[i].c);
    for(int i=1; i<=n*2; i++)
        f[i]=i;
    sort(e+1,e+m+1,gz);
    for(int i=1; i<=m; i++){
        x=find(e[i].a);
        y=find(e[i].b);
        if(x==y){
            printf("%d\n",e[i].c);
            return 0;
        }
        //这里是模拟了第二所监狱    y和b是敌人   x和a是敌人
        f[y] = find(e[i].a + n);//写成f[find(e[i].b)]=find(e[i].a+n)更好理解
        f[x] = find(e[i].b + n);
    }
    puts("0");
    return 0;
}
//这里为什么要加上n   因为一个犯人不加入这所监狱 就必须加入另外一所监狱
//但是我们只能确定他不加入的监狱的并查集   但是他加入的我们查不到
//所以要加上n   加n与否使得相同位置（+n）分开成敌人和朋友
//在第一对人的时候  实现了两个并查集的有效建立  即a和b+n  组合
