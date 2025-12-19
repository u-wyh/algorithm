#include<bits/stdc++.h>
using namespace std;

int ans=INT_MAX,n;

void dfs(int dep,int num){
    if(dep>ans){
        return ;
    }
    if(num==0){
        ans=min(ans,dep);
        return ;
    }
    num--;
    for(int i=2;i<=9;i++){
        if(num%i==0){
            dfs(dep+1,num/i);
        }
    }
}

int main()
{
	cin>>n;
	for(int i=1;i<=sqrt(n);i++){
        if(n%i==0){
            if(i!=1)
                dfs(0,i);
            dfs(0,n/i);
        }
	}
	if(ans!=INT_MAX)
        cout<<ans<<endl;
	else
        cout<<-1<<endl;
	return 0;
}
