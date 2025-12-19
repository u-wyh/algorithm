#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;

struct node{
    int x1,y1,x2,y2;
}nums[MAXN];
int n;
int indegree[MAXN];
vector<vector<int>>graph;
int check(node u,node v){
    int op=1;
	if(u.x1>v.x1) swap(u,v),op=-op;
	if(u.x2<v.x1) return 0;
	double K,B,tmp;
	if(!(u.x2-u.x1)){
		K=1.0*(v.y2-v.y1)/(v.x2-v.x1);
		B=(double)v.y1-K*v.x1;
		tmp=K*u.x1+B;
		if(u.y1>tmp) return op;
		return -op;
	}
	K=1.0*(u.y2-u.y1)/(u.x2-u.x1);
	B=(double)u.y1-K*u.x1;
	tmp=K*v.x1+B;   //Çóº¯Êý
	if(tmp>v.y1) return op;
	return -op;
}
queue<int>q;

int main()
{
    cin>>n;
    graph.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>nums[i].x1>>nums[i].y1>>nums[i].x2>>nums[i].y2;
        if(nums[i].x1>nums[i].x2){
            swap(nums[i].x1,nums[i].x2);
            swap(nums[i].y1,nums[i].y2);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1+i;j<=n;j++){
            int op=check(nums[i],nums[j]);
            if(op==1){
                graph[j].push_back(i);
                indegree[i]++;
            }
            if(op==-1){
                graph[i].push_back(j);
                indegree[j]++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        printf("%d ",cur);
        q.pop();
        for(int i=0;i<graph[cur].size();i++){
            indegree[graph[cur][i]]--;
            if(indegree[graph[cur][i]]==0){
                q.push(graph[cur][i]);
            }
        }
    }
    return 0;
}

