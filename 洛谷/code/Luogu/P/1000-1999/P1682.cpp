#include<bits/stdc++.h>
using namespace std;

int n,m,k,f;
int father[255],sz[255];
int boys[255*255+5][2];
bool boy[255][255];

void build(){
    for(int i=1;i<=n;i++){
        father[i]=i;
        sz[i]=0;
    }
}

int find(int i){
    if (i != father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

void un(int x,int y){
    father[find(x)] = find(y);
}

int main()
{
    cin>>n>>m>>k>>f;
    build();
    for(int i=1;i<=m;i++){
        cin>>boys[i][0]>>boys[i][1];
    }
    for(int i=1;i<=f;i++){
        int a,b;
        cin>>a>>b;
        un(a,b);
    }
    for(int i=1;i<=m;i++){
        int g=find(boys[i][0]);
        if(!boy[g][boys[i][1]]){
            sz[g]++;
            boy[g][boys[i][1]]=true;
        }
    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        if(find(i)==i){
            ans=min(ans,sz[i]);
        }
    }
    cout<<min(ans+k,n);
    return 0;
}
