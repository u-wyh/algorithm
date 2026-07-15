#include<bits/stdc++.h>
using namespace std;

struct
{
    char l,r;
}nums[100];

void dfs(char x){
    if(x=='*')
        return;
    cout<<x;
    dfs(nums[x].l);
    dfs(nums[x].r);
}

int main()
{
    int n;
    cin>>n;
    char a,b;
    for(int i=1;i<=n;i++){
        cin>>a;
        if(i==1)
            b=a;
        cin>>nums[a].l>>nums[a].r;
    }
    dfs(b);
    return 0;
}
