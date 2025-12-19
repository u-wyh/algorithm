#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXM = 1e5+5;
const int BASE = 499;
const int MAXS = 2e5+5;

int n;
string a,c;
int clen;
int cval;
string b1,b2;

long long p[MAXM];
long long t[MAXN];

bool vis[MAXM];
int id[MAXN];
bool ok[MAXS];

int box[MAXS];
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

void prepare(){
    p[0]=1;
    for(int i=1;i<=100000;i++){
        p[i]=p[i-1]*BASE;
    }
}

long long hashString(string str) {
    if (str.empty()) {
        return 0;
    }
    int n = str.length();
    long long ans = str[0] - 'a' + 1;
    for (int j = 1; j < n; ++j) {
        ans = ans * BASE + str[j] - 'a' + 1;
    }
    return ans;
}

void build2(string str){
    t[0]=str[0]-'a'+1;
    for (int j = 1; j <(int) str.length(); ++j) {
        t[j] = t[j - 1] * BASE + str[j] - 'a' + 1;
    }
}

long long getHash2(int l, int r) {
    long long ans = t[r];
    if (l > 0) {
        ans -= t[l - 1] * p[r - l+1];
    }
    return ans;
}

bool fun2(string str){
    build2(str);
    for(int l=0,r=clen-1;r<(int)str.length();l++,r++){
        if(cval==getHash2(l,r)){
            return true;
        }
    }
    return false;
}

int head[MAXS];
int Next[MAXS];
int to[MAXS];
int edge = 0;

void addEdge(int u, int v) {
    Next[++edge] = head[u];
    head[u] = edge;
    to[edge] = v;
}

void insert(int i,string word){
    //i是目标串的编号
    int cur=0;//头结点设置为0
    for (char ch : word){
        int path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
    }
    id[i]=cur;
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
                box[r++] = tree[u][i];//表示有这条支路  加入到队列中
            }
        }
    }
}

void f1(int u) {
    for (int i = head[u]; i > 0; i = Next[i]) {
        f1(to[i]);
        ok[u] += ok[to[i]];
    }
}

void clear(){
    memset(head,0,sizeof(head));
    memset(ok,0,sizeof(ok));
    memset(tree,0,sizeof(tree));
    memset(fail,0,sizeof(fail));
    memset(vis,0,sizeof(vis));
    memset(id,0,sizeof(id));
    cnt=0;
    edge=0;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    prepare();
    while(T--){
        clear();
        cin>>n;
        cin>>a>>c;
        clen=c.length();
        cval=hashString(c);

        for(int i=1;i<=n;i++){
            cin>>b1>>b2;
            insert(i,b1);
            if(fun2(b2)){
                vis[i]=true;
            }
        }
        setFail();

        int u=0;
        for (char ch:a) {
            u = tree[u][ch - 'a'];
            ok[u]=1;
        }

        for (int i = 1; i <= cnt; i++) {
            addEdge(fail[i], i);
        }
        f1(0);

        for(int i=1;i<=n;i++){
            if(ok[id[i]]&&vis[i]){
                vis[i]=true;
            }
            else{
                vis[i]=false;
            }
        }

        bool flag=false;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    cout<<i;
                    flag=true;
                }
                else{
                    cout<<' '<<i;
                }
            }
        }
        cout<<endl;
    }
    return 0;
}