#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = MAXN*60;

int n,m;

int f[MAXN];

int cnt=1;
int path;
int tree[MAXM][55];

void insert(string word){
    int cur=1;
    for (char ch : word){
        if(ch>='a'&&ch<='z'){
            path=ch-'a';
        }
        else{
            path=26+ch-'A';
        }
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
    }
}

int preword(string word){
    int cur=1;
    for (char ch : word){
        if(ch>='a'&&ch<='z'){
            path=ch-'a';
        }
        else{
            path=26+ch-'A';
        }
        if(tree[cur][path]==0){
            return 0;
            //没有路说明走不通
        }
        cur=tree[cur][path];
    }
    return 1;
}

int main()
{
    cin>>n>>m;
    int ans=0;
    string str;
    for(int i=1;i<=n;i++){
        cin>>str;
        insert(str);
    }
    for(int i=1;i<=m;i++){
        cin>>str;
        ans+=preword(str);
    }
    cout<<ans<<endl;
    f[1]=1,f[2]=2;
    for(int i=3;i<=n;i++){
        f[i]=f[i-1]+f[i-2];
    }
    cout<<f[n];
    return 0;
}