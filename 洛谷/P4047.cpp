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
