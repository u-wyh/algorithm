#include<bits/stdc++.h>
using namespace std;
int n,sol,x,y;
stack<int>s;
int main()
{
    scanf("%d",&n);
    while(n--)
	{
        scanf("%d %d",&y,&x);
        while(!s.empty()&&s.top()>x)
            s.pop();
        if(!s.empty()&&s.top()==x)
            continue;
        if(x)
            sol++,s.push(x);
    }
    printf("%d",sol);
    return 0;
}
