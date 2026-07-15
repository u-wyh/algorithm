#include<bits/stdc++.h>
using namespace std;

char a[20],b[20];

void dfs(int l1,int r1,int l2,int r2){
    for(int i=l1;i<=r1;i++){
        if(a[i]==b[r2]){
            cout<<b[r2];
            int cnt=i-l1;
            dfs(l1,i-1,l2,l2+cnt-1);
            dfs(i+1,r1,l2+cnt,r2-1);
            return ;
        }
    }
}

int main()
{
    cin>>a;
    cin>>b;
    //puts(a);
    //printf("%d\n",strlen(a));
    dfs(0,strlen(a)-1,0,strlen(b)-1);
}
