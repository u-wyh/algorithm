#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 6e6+5;

int n;
char s[65];
int cnt;
int trie[MAXN][10];
int p[MAXN];
vector<int>vec[MAXN];

void insert(int id){
    int len=strlen(s);
    int cur=0;
    for(int i=0;i<len;i++){
        int path=s[i]-'a';
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
        p[cur]++;
        if(p[cur]>(int)vec[cur].size()){
            vec[cur].push_back(id);
        }
    }
}

void del(){
    int len=strlen(s);
    int cur=0;
    for(int i=0;i<len;i++){
        int path=s[i]-'a';
        cur=trie[cur][path];
        p[cur]--;
    }
}

int query(int a){
    int len=strlen(s);
    int cur=0;
    int ans=-1;
    for(int i=0;i<len;i++){
        int path=s[i]-'a';
        cur=trie[cur][path];
        if(cur==0){
            return ans;
        }
    }
    if((int)vec[cur].size()>a){
        ans=vec[cur][a];
    }
    return ans;
}

signed main()
{
    scanf("%d",&n);
    int lastans=0;
    for(int i=1;i<=n;i++){
        int op;
        scanf("%d %s",&op,s);
        if(op==1){
            insert(i);
        }
        else if(op==2){
            del();
        }
        else{
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            a=(a*abs(lastans)+b)%c;
            lastans=query(a);
            cout<<lastans<<endl;
        }
    }
    return 0;
}