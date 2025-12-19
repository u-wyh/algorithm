// https://www.luogu.com.cn/problem/P2536
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250005;
const int MAXV = 1005;

int en[MAXN];
bitset<MAXV>vis[MAXN];

string temp;
int n,m;
string s;

int tree[MAXN][4];
int cnt=0;
int ans=0;

void insert(string word){
    //i是目标串的编号
    int cur=0;//头结点设置为0
    for (char ch : word){
        int p;
        if(ch=='A')p=0;
		if(ch=='C')p=1;
		if(ch=='T')p=2;
		if(ch=='G')p=3;
        if(tree[cur][p]==0){
            tree[cur][p]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][p];
    }
    en[cur]++;
}

//匹配成功就减去这个字符串
//这是为了不使通配符可以无限循环下去
void dfs(int now,int cur){
    //now表示现在到了模版串的第几个字符
    //cur表示现在到了字典树的那个节点
    if(vis[cur][now]){
        return ;
    }
    vis[cur][now]=1;
    if(now==m){
        //temp[m]无法到达  也是最终判断
        ans+=en[cur];
		return;
    }
    if(temp[now]=='?'){
        for(int i=0;i<4;i++){
            if(tree[cur][i]){
                dfs(now+1,tree[cur][i]);
            }
        }
    }
    else if(temp[now]=='*'){
        dfs(now+1,cur);
        for(int i=0;i<4;i++){
            if(tree[cur][i]){
                dfs(now+1,tree[cur][i]);
                dfs(now,tree[cur][i]);
            }
        }
    }
    else {
        char ch=temp[now];
        int p;
        if(ch=='A')p=0;
		if(ch=='C')p=1;
		if(ch=='T')p=2;
		if(ch=='G')p=3;
		if(tree[cur][p])
            dfs(now+1,tree[cur][p]);
    }
}

int main()
{
    cin>>temp;
    m=temp.length();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s);
    }
    dfs(0,0);
    cout<<(n-ans);
    return 0;
}