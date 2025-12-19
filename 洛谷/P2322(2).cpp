#include<bits/stdc++.h>
using namespace std;

const int MAXN = 12;//字符数量
const int MAXS = 605;//所有字符的总数

int state[MAXS];//表示到达这个节点后，就会有什么样的状态

// AC自动机
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

// 可以用作队列或者栈，一个容器而已 设立fail指针
int box[MAXS];
string s;
int path;

int n;//字符串数量

struct node{
    int now,status;
};
queue<node>q;

bool vis[600][1<<12];
int ans[600*(1<<12)],fa[600*(1<<12)],c[605];

void insert(int i,string word){
    //i是目标串的编号
    int cur=0;//头结点设置为0
    for (char ch : word){
        path=ch-'A';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
    }
    state[cur]|=(1<<i);
    //cout<<i<<' '<<state[cur]<<endl;
}

void setFail() {
    // box当做队列来使用
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 25; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0节点中只有有孩子的节点加入队列中
            //这个队列里面存储过的所有节点都要有fail
        }
    }
    while (l < r) {
        int u = box[l++];
        for (int i = 0; i <= 25; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];//设置这个孩子节点的fail指针   直通表辅助不用绕环
                state[tree[u][i]]|=state[tree[fail[u]][i]];//它的fail指针包含的字符串它也包含
                box[r++] = tree[u][i];//表示有这条支路  加入到队列中
                //cout<<state[tree[u][i]]<<endl;
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s;
        //cout<< "   "<<i<<endl;
        insert(i,s);
    }
    setFail();
    //cout<<endl;
    q.push({0,0});
    vis[0][0]=true;
    int t=0,nod=0,tot=0;
    while(!q.empty()){
        int now=q.front().now;
        int status=q.front().status;
        q.pop();
        if(status==((1<<n)-1)){
            while(t){
                c[++nod]=ans[t];
                t=fa[t];
            }//递归回去求答案
            for(int i=nod;i>0;i--)
                putchar(c[i]+'A');
            return 0;
        }
        for(int i=0;i<26;i++){
            if(!vis[tree[now][i]][status|state[tree[now][i]]]){
                vis[tree[now][i]][status|state[tree[now][i]]]=true;
                q.push({tree[now][i],status|state[tree[now][i]]});
                //找出现新的状态
                fa[++tot]=t;
                ans[tot]=i;
                //记录当前搜到的字符,同时建1棵关于答案的树,便于最后查询
            }
        }
        t++;//Ti表示当前的搜索到的编号
    }
    return 0;
}
