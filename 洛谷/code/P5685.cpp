#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int ALPHA = 26;

struct PAM{
    int tree[MAXN][ALPHA];
    int fail[MAXN];
    int len[MAXN];
    int num[MAXN];
    int cnt;
    int last;
    char s[MAXN];

    void init(){
        cnt=1;
        last=0;
        len[0]=0,len[1]=-1;
        fail[0]=1,fail[1]=1;
        num[0]=0,num[1]=0;
        s[0]='#';
        for(int k=0;k<26;k++){
            tree[0][k]=0;
            tree[1][k]=0;
        }
    }

    int getfail(int x,int i){
        while(s[i-len[x]-1]!=s[i]){
            x=fail[x];
        }
        return x;
    }

    void insert(int i){
        int c=s[i]-'A';
        // 查找合适的节点  其实这里找的是一个类似于父亲节点
        int cur=getfail(last,i);

        // 如果该节点不存在，创建新节点
        if(!tree[cur][c]){
            int x=++cnt;
            len[x]=len[cur]+2;

            // 这里要找的是fail指针指向的节点  意思是最长的回文后缀  但不能是整体  即子回文后缀
            // 所以这里必须是cur的fail指针所指向的节点
            int p=getfail(fail[cur],i);
            fail[x]=tree[p][c];

            tree[cur][c]=x;
            for(int k=0;k<26;k++){
                tree[x][k]=0;
            }
        }
        last=tree[cur][c];
        num[last]++;
    }

    void compute(){
        for(int i=cnt;i>=1;i--){
            num[fail[i]]+=num[i];
        }
    }
};
PAM pama,pamb;

char a[MAXN];
char b[MAXN];

int main()
{
    scanf("%s %s",a+1,b+1);
    int lena=strlen(a+1);
    int lenb=strlen(b+1);
    // cout<<888<<endl;
    for(int i=1;i<=lena;i++){
        pama.s[i]=a[i];
    }
    pama.init();
    for(int i=1;i<=lenb;i++){
        pamb.s[i]=b[i];
    }
    pamb.init();

    // cout<<777<<endl;
    for(int i=1;i<=lena;i++){
        pama.insert(i);
    }
    pama.compute();
    for(int i=1;i<=lenb;i++){
        pamb.insert(i);
    }
    pamb.compute();

    // cout<<999<<endl;
    long long ans=0;
    queue<pair<int,int>>q;
    q.push({0,0});
    q.push({1,1});

    while(!q.empty()){
        pair<int,int>tmp=q.front();
        q.pop();
        int u=tmp.first;
        int v=tmp.second;
        for(int i=0;i<26;i++){
            if(pama.tree[u][i]&&pamb.tree[v][i]){
                int nu=pama.tree[u][i];
                int nv=pamb.tree[v][i];
                ans+=1ll*pama.num[nu]*pamb.num[nv];
                q.push({nu,nv});
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}