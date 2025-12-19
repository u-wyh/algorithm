#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 250500;

int n,m;
int arr[MAXN][MAXN];

vector<int>vec[MAXM];
int dfn[MAXM],low[MAXM];
int st[MAXM],top;
int color,Time;
int col[MAXM];
bool instack[MAXM];

int in[MAXM],out[MAXM];

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=0;i<vec[x].size();i++){
        int v=vec[x][i];
        if(!dfn[v]){
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int u=(i-1)*m+j;
            if(i>=2){
                if(arr[i-1][j]<=arr[i][j]){
                    vec[u].push_back((i-2)*m+j);
                }
            }
            if(i<n){
                if(arr[i+1][j]<=arr[i][j]){
                    vec[u].push_back(i*m+j);
                }
            }
            if(j>=2){
                if(arr[i][j-1]<=arr[i][j]){
                    vec[u].push_back((i-1)*m+j-1);
                }
            }
            if(j<m){
                if(arr[i][j+1]<=arr[i][j]){
                    vec[u].push_back((i-1)*m+j+1);
                }
            }
        }
    }
    for(int i=1;i<=n*m;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int u=(i-1)*m+j;
            if(i>=2){
                if(col[u]!=col[(i-2)*m+j]){
                    if(arr[i][j]>arr[i-1][j]){
                        in[col[(i-2)*m+j]]++,out[col[u]]++;
                    }
                    else{
                        out[col[(i-2)*m+j]]++,in[col[u]]++;
                    }
                }
            }
            if(i<n){
                if(col[u]!=col[i*m+j]){
                    if(arr[i][j]>arr[i+1][j]){
                        in[col[i*m+j]]++,out[col[u]]++;
                    }
                    else{
                        out[col[i*m+j]]++,in[col[u]]++;
                    }
                }
            }
            if(j>=2){
                if(col[u]!=col[(i-1)*m+j-1]){
                    if(arr[i][j]>arr[i][j-1]){
                        in[col[(i-1)*m+j-1]]++,out[col[u]]++;
                    }
                    else{
                        out[col[(i-1)*m+j-1]]++,in[col[u]]++;
                    }
                }
            }
            if(j<m){
                if(col[u]!=col[(i-1)*m+j+1]){
                    if(arr[i][j]>arr[i][j+1]){
                        in[col[(i-1)*m+j+1]]++,out[col[u]]++;
                    }
                    else{
                        out[col[(i-1)*m+j+1]]++,in[col[u]]++;
                    }
                }
            }
        }
    }
    if(color==1){
        cout<<0<<endl;
        return 0;
    }
    int cnt1=0,cnt2=0;
    for(int i=1;i<=color;i++){
        if(in[i]==0){
            cnt1++;
        }
        else if(out[i]==0){
            cnt2++;
        }
    }
    cout<<max(cnt1,cnt2)<<endl;
    return 0;
}
