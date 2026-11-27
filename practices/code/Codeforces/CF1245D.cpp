// https://codeforces.com/problemset/problem/1245/D
// 题意：给 n 座城市的坐标、建站费 c_i 和布线系数 k_i。
// 城市可建电站，或通过已铺电线连到有电站的城市。
// 两城连线费用为曼哈顿距离乘两城的 k_i 之和。
// 输出：使所有城市通电的最低费用，
// 以及一组最优方案的电站数量、编号和连线数量、端点。
// 数据范围：1 <= n <= 2000，
// 1 <= x_i, y_i <= 10^6，
// 1 <= c_i, k_i <= 10^9。
// 算法标签：Kruskal、并查集
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;
const int MAXM = 2e6+4000;

struct node{
    int x,y,c,k;
}nums[MAXN];
struct edge{
    int st,en,val;
}arr[MAXM];
int cnt=0;
int fa[MAXN];
int n,sum;
vector<int>ans;
vector<pair<int,int>>res;

bool cmp(edge a,edge b){
    return a.val<b.val;
}

int find(int i){
    return fa[i]==i?i:fa[i]=find(fa[i]);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].c;
        arr[++cnt].st=0;//超级源点建边
        arr[cnt].en=i;
        arr[cnt].val=nums[i].c;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].k;
        for(int j=i-1;j>=1;j--){
            arr[++cnt].st=j;
            arr[cnt].en=i;
            arr[cnt].val=(abs(nums[i].x-nums[j].x)+abs(nums[i].y-nums[j].y))*(nums[i].k+nums[j].k);
        }
    }
    sort(arr+1,arr+cnt+1,cmp);
    for(int i=1;i<=cnt;i++){
        int x=find(arr[i].st);
        int y=find(arr[i].en);
        if(x==y){
            continue;
        }
        if(arr[i].st==0){
            ans.push_back(arr[i].en);
        }
        else{
            res.push_back({arr[i].st,arr[i].en});
        }
        fa[x]=y;
        sum+=arr[i].val;
    }
    cout << sum << endl << ans.size() << endl;
	for(auto i:ans)
        cout <<i << ' ';
	cout << endl;
	cout << res.size() << endl;
	for(auto t:res){
		cout <<t.first <<" "<<t.second <<endl;
	}
    return 0;
}
