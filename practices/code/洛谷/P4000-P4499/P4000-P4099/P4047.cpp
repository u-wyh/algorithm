// https://www.luogu.com.cn/problem/P4047
// 题意：第一行输入居住点数量 n 和部落数 k，
// 接下来 n 行输入各居住点的二维整数坐标 (x, y)。
// 将 n 个点划分为 k 个非空部落，
// 部落间距离定义为两个部落中最近居住点对的欧氏距离；
// 求使最近两个部落的距离尽可能大的最大距离。
// 输出一行实数，精确到小数点后两位。
// 数据范围：对于 100% 的数据，2 <= k <= n <= 10^3，
// 0 <= x, y <= 10^4。
// 难度评分：1500（洛谷分级换算）
// 算法标签：最小生成树、Kruskal、并查集
#include<bits/stdc++.h>
using namespace std;

int n,k;
int fa[1005];
struct node{
    int st,en;
    double dis;
};
int pos[1005][2];
vector<node>nums;
int num,flag;

bool cmp(node a,node b){
    return a.dis<b.dis;
}

double fun(int x,int y,int xx,int yy){
    return sqrt(pow(x-xx,2)+pow(y-yy,2));
}

int find(int a){
	if(fa[a]!=a)
		fa[a] = find(fa[a]);
	return fa[a];
}

void un(int a,int b){
    fa[find(b)] = find(a);
}

void kruskal(){
	for(int i=0;i<nums.size();i++){
		if(num==n-k)
            flag = 1;
		if(find(nums[i].st)!=find(nums[i].en)){
			num++;
			un(nums[i].st,nums[i].en);
		if(flag){
			printf("%.2lf",nums[i].dis);
			return ;
			}
		}
	}
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>pos[i][0]>>pos[i][1];
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=n;j++){
            nums.push_back({i,j,fun(pos[i][0],pos[i][1],pos[j][0],pos[j][1])});
        }
    }
    sort(nums.begin(),nums.end(),cmp);
    kruskal();
    return 0;
}
