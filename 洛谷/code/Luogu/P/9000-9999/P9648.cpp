#include<bits/stdc++.h>
using namespace std;
int T;
int n,head[200005],nex[400005],to[400005],cnt = 0;
char w[400005];
bool can[200005];
int num;
//清空
void qk() {
	cnt = 0,num = n;
	for(int i = 0;i <= 200000;i++) head[i] = 0,can[i] = true;
	for(int i = 0;i <= 400000;i++) nex[i] = 0,to[i] = 0,w[i] = ' ';
	return;
}
//加边
void add(int x,int y,char z) {
	nex[++cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
	w[cnt] = z;
}
bool dfs(int now,int fa,bool ok) {
	//ok 代表当前点是否合法
	int xt = 0;
	if(!ok) xt++;
	bool get = ok;
	if(num == 0) return false;
	bool return_ok = true,return_ok2 = true;
	int have[27][3];
	for(int i = 0;i <= 26;i++) have[i][1] = -1,have[i][2] = -1;
	// 找到与父亲连接的边对应的字符
	for(int i = head[now];i;i = nex[i]) {
		if(to[i] == fa) {
			have[int(w[i] - 'a')][1] = fa;
			break;
		}
	}
	//找到剩下的边
	for(int i = head[now];i;i = nex[i]) {
		if(to[i] == fa) continue;
		if(have[int(w[i] - 'a')][1] == -1) have[int(w[i] - 'a')][1] = to[i];
		else if (have[int(w[i] - 'a')][2] != -1) {
			num = 0;
			return false;
		}
		else {
			have[int(w[i] - 'a')][2] = to[i];
			if(!(have[int(w[i] - 'a')][1] == fa and !ok)) xt++;
			if(have[int(w[i] - 'a')][1] == fa) return_ok2 = true;
			else return_ok2 = false;
			if(xt == 2) {
				num = 0;
				return false;
			}
		}
	}
	if(xt) ok = false;
	for(int i = head[now];i;i = nex[i]) {
		if(to[i] == fa) continue;
		if(!return_ok) {
			dfs(to[i],now,return_ok);
			continue;
		}
		if(ok) {
			if(!dfs(to[i],now,ok)) {
				return_ok = false;
				for(int j = head[now];j != i;j = nex[j]) {
					if(to[j] != fa) dfs(to[j],now,return_ok);
				}
			}
		}
		else {
			if(have[int(w[i] - 'a')][2] == to[i]) {
				if(!dfs(to[i],now,get)) {
					return_ok = false;
					for(int j = head[now];j != i;j = nex[j]) {
						if(to[j] != fa) dfs(to[j],now,return_ok);
					}
				}
			}
			else if(have[int(w[i] - 'a')][1] == to[i] and have[int(w[i] - 'a')][2] != -1){
				if(!dfs(to[i],now,get)) {
					return_ok = false;
					for(int j = head[now];j != i;j = nex[j]) {
						if(to[j] != fa) dfs(to[j],now,return_ok);
					}
				}
			}
			else if(!dfs(to[i],now,ok)) {
				return_ok = false;
				for(int j = head[now];j != i;j = nex[j]) {
					if(to[j] != fa) dfs(to[j],now,return_ok);
				}
			}
		}
		if(num == 0) return false;
	}
	if(!ok or !return_ok or !return_ok2) {
		if(num == 0) return false;
		if(can[now]) can[now] = false,num--;
	}
	return (return_ok && return_ok2);
}
signed main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		qk();
		for(int i = 1;i < n;i++) {
			int x,y;
			char z;
			scanf("%d %d",&x,&y);
			cin >> z;
			add(x,y,z),add(y,x,z);
		}
		dfs(1,1,1);
		printf("%d\n",num);
	}
    return 0;
}
