#include<bits/stdc++.h>
using namespace std;

int a,b,n;
queue<int>q;

int main()
{
    cin>>a>>b>>n;
    q.push(b);
    cout<<a;
    if(a*b>=10){
        q.push(a*b/10);
    }
    q.push(a*b%10);
    for(int i=2;i<=n;i++){
        a=q.front();
        q.pop();
        b=q.front();
        cout<<' '<<a;
        if(a*b>=10){
            q.push(a*b/10);
        }
        q.push(a*b%10);
    }
    return 0;
}