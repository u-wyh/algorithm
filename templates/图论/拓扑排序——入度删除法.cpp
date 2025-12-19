// 拓扑排序模版（Leetcode）
// 邻接表建图（动态方式）
// 课程表II
// 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1
// 给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi]
// 表示在选修课程 ai 前 必须 先选修 bi
// 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1]
// 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序
// 你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组
// 测试链接 : https://leetcode.cn/problems/course-schedule-ii/
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5005;
const int MAXM = 500005;
const int MOD = 80112002;

int n,m,cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int edge[MAXM][2];
int indegree[MAXN];
int line[MAXN];
int ans=0;
queue<int >pq;

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    for(int i=1;i<=m;i++){
        //连边 建图
        Next[cnt]=head[edge[i][0]];
        to[cnt]=edge[i][1];
        head[edge[i][0]]=cnt++;
        indegree[edge[i][1]]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            pq.push(i);
            line[i]=1;
        }
        //printf("%3d %3d %3d\n",indegree[i],line[i],head[i]);
    }
    while(!pq.empty()){
        int cur=pq.front();
        pq.pop();
        if(head[cur]==0){
            ans=(ans+line[cur])%MOD;
        }else{
            for(int i=head[cur];i>0;i=Next[i]){
                indegree[to[i]]--;
                line[to[i]]=(line[cur]+line[to[i]])%MOD;
                if(indegree[to[i]]==0){
                    pq.push(to[i]);
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
