// https://www.luogu.com.cn/problem/P1111
// 题意：给 N 个村庄和 M 条双向公路，每条路在时刻 t 修好。只用已修好的路，求整张图最早何时连通，所有路修完仍不连通则输出 -1。
// 数据范围：1 ≤ N ≤ 1000，1 ≤ M,t ≤ 10^5，端点在 [1,N]。
// 算法标签：并查集、排序、Kruskal

#include<bits/stdc++.h>
using namespace std;

struct hh
{
	int x,y,t;
}a[200000];
int f[200000],n,m;

int cmp(const hh &a,const hh &b){
    return a.t<b.t;
}

int find(int x){
    return f[x]==x?x:(f[x]=find(f[x]));
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
        cin>>a[i].x>>a[i].y>>a[i].t;
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=n;i++)
        f[i]=i;
	for(int i=1;i<=m;i++){
		int fx=find(a[i].x),fy=find(a[i].y);
		if(fx!=fy)
            f[fx]=fy,n--;
		if(n==1){
		    cout<<a[i].t;
            return 0;
        }
	}
	cout<<-1<<endl;
    return 0;
}
