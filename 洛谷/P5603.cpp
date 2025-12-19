#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;
int indegree[MAXN],maxans;
int in[MAXN],minans;

int head[MAXN];
int to[MAXN];
int Next[MAXN];
int cnt=1;

priority_queue<int, vector<int>, greater<int>> minheap;
priority_queue<int, vector<int>, less<int>> maxheap;
queue<int>heap;

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

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        indegree[v]++;
        in[v]++;
    }
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            minheap.push(i);
            maxheap.push(i);
        }
    }
    int maxn=0;
    while(!minheap.empty()){
        int u=minheap.top();
        minheap.pop();
        if(u>maxn){
            maxans++;
            maxn=u;
        }
        for(int i=head[u];i!=0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                minheap.push(to[i]);
            }
        }
    }
    cout<<maxans<<endl;
    maxn=0;
    while(!maxheap.empty()){
        int u=maxheap.top();
        maxheap.pop();
        if(u>maxn){
            minans++;
            maxn=u;
        }
        for(int i=head[u];i!=0;i=Next[i]){
            in[to[i]]--;
            if(in[to[i]]==0){
                //cout<<u<<' '<<to[i]<<endl;
                maxheap.push(to[i]);
            }
        }
        //cout<<' '<<(int)maxheap.size()<<endl;
        while(!maxheap.empty()){
            heap.push(maxheap.top());
            maxheap.pop();
        }
        //cout<<' '<<heap.size()<<endl;
        while(!heap.empty()){
            int cur=heap.front();
            heap.pop();
            if(cur>maxn){
                maxheap.push(cur);
            }
            else{
                for(int i=head[cur];i>0;i=Next[i]){
                    in[to[i]]--;
                    if(in[to[i]]==0){
                        heap.push(to[i]);
                    }
                }
            }
        }
    }
    cout<<minans<<endl;
    return 0;
}
