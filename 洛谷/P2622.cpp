#include<bits/stdc++.h>
#define il inline
#define ll long long
#define RE register
#define For(i,a,b) for(RE int (i)=(a);(i)<=(b);(i)++)
#define Bor(i,a,b) for(RE int (i)=(b);(i)>=(a);(i)--)
using namespace std;
const int N=105;
int n,m,a[N],b[N],f[1<<11];
bool vis[1<<11];
queue<int>q;

int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m; int x,lim=(1<<n)-1;
	For(i,1,m) For(j,1,n) {
		cin>>x;
		if(x==1) a[i]|=(1<<j-1);
		if(x==-1) b[i]|=(1<<j-1);
	}
	memset(f,0x3f,sizeof(f));
	f[0]=0;q.push(0);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		For(i,1,m) {
			int sta=(u|a[i])&(~b[i]);
			if(f[sta]>f[u]+1) {
				f[sta]=f[u]+1;
				if(!vis[sta]) vis[sta]=1,q.push(sta);
			}
		}
	}
	cout<<(f[lim]==0x3f3f3f3f?-1:f[lim]);
	return 0;
}
