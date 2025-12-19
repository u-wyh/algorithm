#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;
vector<vector<int >>graph;
queue<int >q;
int indegree[MAXN];

int main()
{
    cin>>n;
    graph.resize(n+1);
    int i=1;
    while(i<=n){
        int val;
        cin>>val;
        if(val!=0){
            indegree[val]++;
            graph[i].push_back(val);
        }else{
            i++;
            continue;
        }
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
        //printf("%3d",indegree[i]);
    }
    //cout<<endl;
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
