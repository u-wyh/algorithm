#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int arr[MAXN];

int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
int ans;

int f[MAXN][105];
bool ok[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

bool dfs(int u){
    int maxx=-1,cnt=0;
    bool flag=0;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(!dfs(v)){
            return false;
        }
        if(arr[v]>maxx){
            maxx=arr[v];
            cnt=1;
        }
        else if(arr[v]==maxx){
            cnt++;
        }
        flag|=ok[v];
    }
    if(cnt==0&&arr[u]==-1){
        arr[u]=0;
        ok[u]=1;
    }//不确定的叶子结点
    else if(cnt){
        int x=maxx+(cnt>1);//这是最低的标准
        if(arr[u]!=-1){
            if(arr[u]<x){
                //最低标准都无法满足 那么更高的就不可能了
                return 0;
            }
            if(!flag&&arr[u]!=x){
                //这个值是被固定的了 改不了了
                return 0;
            }
            return 1;
        }
        if(arr[u]==-1&&flag){
            //自己是可以灵活的  孩子也是可以灵活的  那么才能算作是灵活的
            ok[u]=1;
        }
        arr[u]=x;//表示这个点最低是多少  如果ok[u]=0那么就是这个值 否则上不封顶
    }
    return 1;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        n=read();
        cnt=1;
        for(int i=1;i<=n;i++){
            head[i]=0;
            ok[i]=false;
        }
        for(int i=1;i<=n;i++){
            arr[i]=read();
        }
        for(int i=1;i<n;i++){
            int u=read(),v=read();
            addedge(u,v);
        }
        if(dfs(1)){
            cout<<"Reasonable"<<endl;
        }
        else{
            cout<<"Unreasonable"<<endl;
        }
    }
    return 0;
}
