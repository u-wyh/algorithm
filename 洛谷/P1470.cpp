//关键词报警功能

#include<bits/stdc++.h>
using namespace std;
// 所有目标字符串的数量
const int MAXN = 200;
// 所有目标字符串的总字符数量
const int MAXS = 2005;

// 记录每个节点是否报警
bool alert[MAXS];
int len[MAXS];

// AC自动机
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

bool ok[200005];

// 可以用作队列或者栈，一个容器而已
int box[MAXS];

string s;
int path;

void insert(string word){
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
    alert[cur]=true;
    len[cur]=word.length();
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
        // 命中标记前移
        alert[u] |= alert[fail[u]];
        len[u]=max(len[fail[u]],len[u]);
    }
}
//报警标志的迁移

int main()
{
    int ans=0;
    string key;
    while(cin>>key&&key!="."){
        insert(key);
    }
    setFail();
    //cin>>s;
    string s;
	s=" ";
	string tp;
	while (cin>>tp){
		s=s+tp;//将所有的串合成一个
	}
    int u=0,k=0;
    for (char ch:s) {
        if(alert[u]){
            for(int i=max(k-len[u],0);i<k;i++){
                ok[i]=true;
            }
            //cout<<6<<endl;
        }
        k++;
        u = tree[u][ch - 'A'];//表示到达下一个节点
    }
    ok[0]=true;
    //cout<<s.length()<<endl;
    for(int i=1;i<s.length();i++){
        cout<<ok[i]<<' ';
    }
    for(int i=0;i<s.length();i++){
        if(!ok[i]){
            ans=i;
            break;
        }
    }
    cout<<ans;
    return 0;
}
