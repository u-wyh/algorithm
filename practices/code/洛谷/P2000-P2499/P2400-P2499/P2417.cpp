// https://www.luogu.com.cn/problem/P2417
// 题意：T 组数据，每组有 m 个教室和 n 个学生，
// 给出每个教室可上课的学生列表。
// 每个学生至多在一个教室上课，判断能否使每个教室至少有一名学生。
// 每组输出 YES 或 NO。
// 数据范围：T <= 10，n, m <= 2*10^4。
// 算法标签：深度优先搜索、回溯、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

int n,m;
struct node{
    int cnt,sub;
}nums[MAXN];
vector<int>vec[MAXN];
bool vis[MAXN];
int t[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool cmp(node a,node b){
    return a.cnt<b.cnt;
}

bool dfs(int now){
    if(now==m+1){
        return true;
    }
    bool flag=false;
    for(int i=0;i<nums[now].cnt;i++){
        if(vis[vec[nums[now].sub][i]])
            continue;
        vis[vec[nums[now].sub][i]]=true;
        if(dfs(now+1)){
            flag=true;
            break;
        }
        vis[vec[nums[now].sub][i]]=false;
    }
    return flag;
}

bool cmp2(int a,int b){
    return t[a]>t[b];
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read(),m=read();
        for(int i=1;i<=n;i++){
            vis[i]=false;
            t[i]=0;
        }
        for(int i=1;i<=m;i++){
            vec[i].clear();
        }
        for(int i=1;i<=m;i++){
            nums[i].sub=i;
            nums[i].cnt=read();
            for(int j=1;j<=nums[i].cnt;j++){
                int u=read();
                vec[j].push_back(u);
                t[u]++;
            }
        }
        sort(nums+1,nums+m+1,cmp);
        for(int i=1;i<=m;i++){
            sort(vec[i].begin(),vec[i].end(),cmp2);
        }
        bool flag=false;
        for(int i=0;i<nums[1].cnt;i++){
            //cout<<vec[nums[1].sub][i]<<endl;
            vis[vec[nums[1].sub][i]]=true;
            if(dfs(2)){
                flag=true;
                break;
            }
            vis[vec[nums[1].sub][i]]=false;
        }
        if(flag){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
