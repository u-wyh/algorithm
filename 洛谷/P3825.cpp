#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 2e5+5;
const int MAXD = 10;

int n,d,m;
char s[MAXN];

int pos[MAXD];
int poscnt;

struct rule{
    int i,j;
    char hi,hj;
};
rule xrules[MAXM];
int xcnt;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int head1[MAXN];
int nxt1[MAXM<<1];
int to1[MAXM<<1];
int cnt1=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int st[MAXN];
bool instack[MAXN];
int top;
int color;
int col[MAXN];

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void Addedge(int u,int v){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
}

void prepare(){
    cnt1=1;
    for(int i=0;i<=n*2+1;i++){
        head1[i]=0;
        dfn[i]=0;
        low[i]=0;
        col[i]=0;
        instack[i]=false;
    }
    top=0;
    dfncnt=0;
    color=0;
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    instack[u]=true;
    st[++top]=u;
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[v],low[u]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[v],low[u]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        col[u]=++color;
        instack[u]=false;
        while(st[top]!=u){
            int to=st[top];
            instack[to]=false;
            col[to]=color;
            top--;
        }
        top--;
    }
}

int main()
{
    scanf("%d %d",&n,&d);
    scanf("%s",s+1);

    for(int i=1;i<=n;i++){
        if(s[i]=='x'){
            pos[++poscnt]=i;
        }
    }

    scanf("%d",&m);
    for(int k=1;k<=m;k++){
        int i,j;
        char hi,hj;
        scanf("%d %c %d %c",&i,&hi,&j,&hj);
        if(s[i]=='x'||s[j]=='x'){
            xrules[++xcnt]={i,j,hi,hj};
        }
        else{
            char ci=s[i];
            char cj=s[j];

            char ci1,ci0,cj1,cj0;
            if(ci=='a'){
                ci1='B',ci0='C';
            }
            else if(ci=='b'){
                ci1='A',ci0='C';
            }
            else{
                ci1='A',ci0='B';
            }

            if(hi!=ci1&&hi!=ci0){
                continue;
            }

            if(cj=='a'){
                cj1='B',cj0='C';
            }
            else if(cj=='b'){
                cj1='A',cj0='C';
            }
            else{
                cj1='A',cj0='B';
            }

            int u=2*i+(hi==ci1?0:1);
            if(hj!=cj1&&hj!=cj0){
                addedge(u,u^1);
            }
            else{
                int v=2*j+(hj==cj1?0:1);
                addedge(u,v);
                addedge(v^1,u^1);
            }
            
        }
    }

    int status=1;
    for(int i=1;i<=d;i++){
        status*=3;
    }

    for(int st=0;st<status;st++){
        int tmp=st;
        for(int i=1;i<=d;i++){
            s[pos[i]]='a'+tmp%3;
            tmp/=3;
        }

        prepare();

        for(int k=1;k<=xcnt;k++){
            int i=xrules[k].i,j=xrules[k].j;
            char hi=xrules[k].hi,hj=xrules[k].hj;

            char ci=s[i];
            char cj=s[j];

            char ci1,ci0,cj1,cj0;
            if(ci=='a'){
                ci1='B',ci0='C';
            }
            else if(ci=='b'){
                ci1='A',ci0='C';
            }
            else{
                ci1='A',ci0='B';
            }

            if(cj=='a'){
                cj1='B',cj0='C';
            }
            else if(cj=='b'){
                cj1='A',cj0='C';
            }
            else{
                cj1='A',cj0='B';
            }

            if(hi!=ci1&&hi!=ci0){
                continue;
            }
            else{
                int u=2*i+(hi==ci1?0:1);
                if(hj!=cj1&&hj!=cj0){
                    Addedge(u,u^1);
                }
                else{
                    int v=2*j+(hj==cj1?0:1);
                    Addedge(u,v);
                    Addedge(v^1,u^1);
                }
            }

        }

        for(int i=2;i<=2*n+1;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }

        bool flag=false;
        for(int i=1;i<=n;i++){
            if(col[2*i]==col[2*i+1]){
                flag=true;
                break;
            }
        }

        if(!flag){
            for(int i=1; i<=n; i++) {
                char ci = s[i];
                char opt1, opt2;
                if(ci=='a') opt1='B', opt2='C';
                else if(ci=='b') opt1='A', opt2='C';
                else opt1='A', opt2='B';
                
                // 根据拓扑序选择字符
                if(col[2*i] < col[2*i+1]) {
                    putchar(opt1);
                } else {
                    putchar(opt2);
                }
            }
            putchar('\n');
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}