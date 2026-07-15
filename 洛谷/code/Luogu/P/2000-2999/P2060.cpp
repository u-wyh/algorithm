#include<bits/stdc++.h>
using namespace std;

int go(int x,int y)
{
    if (x == 1 && y == 0) { return 3; }
    if (x == 2 && y == 2) { return 4; }
    if(y<=x-y){
    	if(x%2==0) {
            return x/2+(x/2-y)%2;
        }
        if(x%2==1) {
            return (x+1)/2+((x+1)/2-y+1)%2;
        }
    }
    if(y>x-y) {
        return go(x+1,y-1);
    }
}

int main()
{
    int x1,x2,y1,y2;
    cin>>x1>>y1>>x2>>y2;
    int a,b;
    a=max(abs(x1-x2),abs(y1-y2));
    b=min(abs(x1-x2),abs(y1-y2));
    cout<<go(a,b);
    return 0;
}
