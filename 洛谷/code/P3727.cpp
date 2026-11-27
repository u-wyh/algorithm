// https://www.luogu.com.cn/problem/P3727
// 题意：输入测试组数 T，每组输入树点数 n、n-1 条树边、各点初始稳定值 w_1..w_n 及博弈规则 k（k=2 或 3 时还输入参数 s）。
// 艾登先从树上任选一条链并拆下其上节点，随后双方轮流对稳定值 > 0 的节点操作（dedsec 先手，操作后不能 < 0
// 不能操作者败）：k=1 每次可减任意正整数；
// k=2 每次可减 s 的非负整数幂；
// k=3 每次可减 >= s 的整数；
// k=4 每次可减任意正整数或将 >= 2 的点裂为两个正整数之和相同的点；
// k=5 双方均不能操作。
// 对每组数据输出一行：若存在链使艾登必胜则输出 Mutalisk ride face how to lose?
// 否则输出 The commentary cannot go on!。
// 数据范围：T <= 5，n <= 3*10^4，w_i <= 10^9，输入均为正整数。
#include<bits/stdc++.h>
// 算法标签：点分治、博弈论(SG函数)、哈希表
using namespace std;
const int MAXN = 3e4+5;

int n;
int k,s;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int sz[MAXN];
bool vis[MAXN];

int sg(int x){
    if(x==0){
        return 0;
    }
    if(k==1){
        return x;
    }
    if(k==2){
        if(s&1){
            return x&1;
        }
        else{
            int v=x%(s+1);
            if(v==s){
                return 2;
            }
            return v&1;
        }
    }
    if(k==3){
        return x/s;
    }
    if(k==4){
        if(x%4==0){
            return x-1;
        }
        if(x%4==3){
            return x+1;
        }
    }
    return x;
}

void init(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        vis[i]=false;
    }
    cntg=1;
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool flag=false;
    while(!flag){
        flag=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                flag=true;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

bool ans;

unordered_set<int>seen;
vector<int>cur;

void dfs(int u,int fa,int va){
    cur.push_back(va^val[u]);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,va^val[u]);
        }
    }
}

void calc(int u){
    seen.clear();
    if(val[u]==0){
        ans=true;
        return ;
    }
    seen.insert(val[u]);

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            cur.clear();
            dfs(v,u,0);
            for(int i=0;i<(int)cur.size();i++){
                int v=cur[i];
                if(seen.find(v)!=seen.end()){
                    ans=true;
                    break;
                }
            }
            for(int i=0;i<(int)cur.size();i++){
                int v=cur[i];
                seen.insert(v^val[u]);
            }
        }
    }
}

void solve(int u){
    vis[u]=true;
    calc(u);
    if(ans){
        return ;
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=u&&!vis[v]){
            solve(getcentroid(v,u));
            if(ans){
                break;
            }
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        init();
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        cin>>k;
        if(k==2||k==3){
            cin>>s;
        }
        for(int i=1;i<=n;i++){
            val[i]=sg(val[i]);
        }

        ans=false;
        int centroid=getcentroid(1,0);
        solve(centroid);

        if(ans){
            cout<<"Mutalisk ride face how to lose?"<<endl;
        }
        else{
            cout<<"The commentary cannot go on!"<<endl;
        }
    }
    return 0;
}


// int val[105];
// int tmp[105];

// void test(int x){
//     for(int i=1;i<=x;i++){
//         for(int j=0;j<=100;j++){
//             tmp[j]=0;
//         }
//         for(int j=0;j<i;j++){
//             tmp[val[j]]=1;
//         }
//         if(i>=2){
//             for(int a=1,b=i-1;a<=b;a++,b--){
//                 tmp[val[a]^val[b]]=1;
//             }
//         }
//         for(int j=0;j<=100;j++){
//             if(tmp[j]==0){
//                 val[i]=j;
//                 break;
//             }
//         }
//         cout<<i<<" "<<val[i]<<endl;
//     }
// }
