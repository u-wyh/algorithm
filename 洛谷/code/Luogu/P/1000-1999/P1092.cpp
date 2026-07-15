#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30;

int n;

int a[MAXN];
int b[MAXN];
int c[MAXN];

int val[MAXN];//记录每个元素对应的数字
int pritority[MAXN];//我们从最小数位上的数字开始枚举  更好的剪枝
int cnt;

bool vis[MAXN];//标记这个数字是否已经被别的字母占用了
char s1[MAXN],s2[MAXN],s3[MAXN];

void getnext(int x){
    if(!vis[x]){
        vis[x]=true;
        pritority[cnt++]=x;
    }
}

bool check(){
    if(val[a[0]]!=-1&&val[b[0]]!=-1){
        if(val[a[0]]+val[b[0]]>=n){
            return false;
        }
    }
    for(int i=n-1;i>=0;i--){
        int A=val[a[i]],B=val[b[i]],C=val[c[i]];
        if(A==-1||B==-1||C==-1){
            continue;
        }
        if((A+B)%n!=C&&(A+B+1)%n!=C){
            return false;
        }
    }
    return true;
}

bool ok(){
    int add=0;
    for(int i=n-1;i>=0;i--){
        int A=val[a[i]],B=val[b[i]],C=val[c[i]];
        if((A+B+add)%n!=C){
            return false;
        }
        add=(A+B+add)/n;
    }
    return add==0;
}

void dfs(int u){
    if(!check()){
        return ;
    }
    if(u==n){
        if(ok()){
            for(int i=0;i<n;i++){
                cout<<val[i]<<' ';
            }
            cout<<endl;
            exit(0);
        }
    }
    for(int i=n-1;i>=0;i--){
        if(!vis[i]){
            vis[i]=true;
            val[pritority[u]]=i;
            dfs(u+1);
            vis[i]=false;
            val[pritority[u]]=-1;
        }
    }
}

int main()
{
    scanf("%d",&n);
    scanf("%s %s %s",s1,s2,s3);
    for(int i=0;i<n;i++){
        val[i]=-1;
    }
    for(int i=0;i<n;i++){
        a[i]=s1[i]-'A';
        b[i]=s2[i]-'A';
        c[i]=s3[i]-'A';
    }
    for(int i=n-1;i>=0;i--){
        getnext(a[i]);
        getnext(b[i]);
        getnext(c[i]);
    }
    for(int i=0;i<n;i++){
        vis[i]=false;
    }
    dfs(0);
    return 0;
}