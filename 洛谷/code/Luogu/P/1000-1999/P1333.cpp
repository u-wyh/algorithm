#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250005;

map<string,int>graph;
int cnt=0;
int degree[MAXN<<1];
int fa[MAXN<<1];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

int main()
{
    string s1,s2;
    for(int i=1;i<500000;i++){
        fa[i]=i;
    }
    while(cin>>s1>>s2){
        int u,v;
        if(graph.find(s1)==graph.end()){
            graph[s1]=++cnt;
            u=cnt;
        }
        else{
            u=graph[s1];
        }

        if(graph.find(s2)==graph.end()){
            graph[s2]=++cnt;
            v=cnt;
        }
        else{
            v=graph[s2];
        }
        degree[u]++,degree[v]++;
        un(u,v);
    }
    int father=0;
    for(int i=1;i<=cnt;i++){
        if(father==0){
            father=find(i);
        }
        else{
            if(father!=find(i)){
                cout<<"Impossible"<<endl;
                return 0;
            }
        }
    }
    int cntt=0;
    for(int i=1;i<=cnt;i++){
        if(degree[i]%2){
            cntt++;
        }
    }
    if(cntt==0||cntt==2){
        cout<<"Possible"<<endl;
    }
    else{
        cout<<"Impossible"<<endl;
    }
    return 0;
}
