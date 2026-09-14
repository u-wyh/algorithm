#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n;

int cntt=1;
int trie[MAXN][26];
int pass[MAXN];
int f[MAXN];
int ans;

void update(int x,int v){
    if(f[x]>=v){
        return ;
    }
    if(f[x]!=-1){
        ans-=f[x]^x;
    }
    f[x]=v;
    ans+=f[x]^x;
}

void insert(string str){
    int cur=1;
    int len=str.length();
    for(int i=0;i<len;i++){
        int path=str[i]-'a';
        if(trie[cur][path]==0){
            trie[cur][path]=++cntt;
        }
        cur=trie[cur][path];
        pass[cur]++;
        update(pass[cur],i+1);
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;i++){
        f[i]=0;
        ans+=i;
        string str;
        cin>>str;
        insert(str);
        cout<<ans<<endl;
    }
    return 0;
}
/*
4
a
ab
abc
abcd

8
ab
b
ba
ab
aa
ba
a
bb
*/