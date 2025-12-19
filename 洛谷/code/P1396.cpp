#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+1;
const int maxm=1e5+1;

priority_queue< pair<int,int> > q;//大根堆（后变小根堆）
int n,m,s,t,head[maxm],tot,dis[maxm],vis[maxm];
struct Edge {
	int next,now,w;
}edge[maxn];

inline int gi() {
    int x=0,w=0;char ch=0;
    while(!(ch>='0'&&ch<='9')) {
        if(ch=='-') w=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return w?-x:x;
}

void make(int from,int to,int t) {
	edge[++tot].next=head[from];
	edge[tot].now=to;
	edge[tot].w=t;
	head[from]=tot;
}

void dijkstra() {
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()) {
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].next) {
			int k=max(dis[x],edge[i].w),r=edge[i].now;
            //取max而不取和
				if(k<dis[r]) {
					dis[r]=k;
					q.push(make_pair(-dis[r],r));
                    //取一个负就可以变为小根堆！！
				}
		}
	}

}
int main()
{
	n=gi(); m=gi(); s=gi(); t=gi();
	for(int i=1,x,y,z;i<=m;i++) {
		x=gi(); y=gi(); z=gi();
		make(x,y,z);
		make(y,x,z);
        //构无向图
	}
	dijkstra();
	printf("%d",dis[t]);
	return 0;
}
