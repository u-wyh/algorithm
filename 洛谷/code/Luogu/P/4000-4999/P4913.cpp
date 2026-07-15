#include<iostream>
using namespace std;

const int MAXN=2e5+7;

struct Node{
    int left,right;
}t[MAXN];

int n;
void build(){
    for(int i=1;i<=n;i++)
        cin>>t[i].left>>t[i].right;
}

int dfs(int x){
    if(!x)
        return 0;
    return max(dfs(t[x].left),dfs(t[x].right))+1;
}

int main()
{
    cin>>n;
    build();
    cout<<dfs(1);
    return 0;
}
