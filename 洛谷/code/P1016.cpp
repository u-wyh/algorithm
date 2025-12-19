#include <bits/stdc++.h>
using namespace std;
#define maxn 100000
#define db double
#define INF 9999999
int n;
db D1, D2, C, P, res, ans, maxx;

struct node
{
	db co, dis;
	bool friend operator <(const node& a, const node& b)
	{ return a.dis < b.dis; }
}pl[maxn];

int Solve(int now){
	int flag = INF; db d = pl[now].dis;
	for(int i = now + 1; i <= n && pl[i].dis - d <= maxx; i ++){
		if(pl[i].co < pl[now].co){
			ans += ((pl[i].dis - d - res) / D2) * pl[now].co;
			res = 0; return i;
		}
		if(flag == INF || pl[i].co < pl[flag].co) flag = i;
	}
	if(D1 - pl[now].dis <= maxx){
		ans += ((D1 - pl[now].dis - res) / D2) * pl[now].co;
		return INF;
	}
	if(flag == INF) {
        printf("No Solution\n"); return -1;
    }else{
		ans += C * pl[now].co; res += (maxx - (pl[flag].dis - d));
		return flag;
	}
}

int main()
{
	scanf("%lf%lf%lf%lf%d", &D1, &C, &D2, &P, &n);
	pl[0].dis = 0, pl[0].co = P;
	for(int i = 1; i <= n; i ++)
		scanf("%lf%lf", &pl[i].dis, &pl[i].co);
	sort(pl, pl + n + 1);
	maxx = C * D2;
	int k = 0, t;
	do
	{
		t = Solve(k), k = t;
		if(t == -1) return 0;
	}while(t != INF);
	printf("%.2lf", ans);
	return 0;
}
