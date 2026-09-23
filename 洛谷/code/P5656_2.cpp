// https://www.luogu.com.cn/problem/P5656
#include<bits/stdc++.h>
using namespace std;
#define int long long

int x,y,d,px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int a,b,c;
        cin>>a>>b>>c;
        exgcd(a,b);
        if(c%d==0){
            x=c/d*x;
            y=c/d*y;
            int dx=b/d;
            int dy=a/d;

            if(x<=0){
                int delta=(dx-x)/dx;
                x+=delta*dx;
                y-=delta*dy;
            }
            else{
                int delta=(x-1)/dx;
                x-=delta*dx;
                y+=delta*dy;
            }

            if(y<=0){
                cout<<x<<' ';
                y+=(dy-y)/dy*dy;
                cout<<y<<endl;
            }
            else{
                cout<<((y-1)/dy+1)<<' ';
                int xmin,xmax,ymin,ymax;
                xmin=x;
                ymax=y;

                int delta=(y-1)/dy;
                y-=dy*delta;
                x+=dx*delta;
                xmax=x;
                ymin=y;
                cout<<xmin<<' '<<ymin<<' '<<xmax<<' '<<ymax<<endl;
            }
        }
        else{
            cout<<-1<<endl;
        }
    }
    return 0;
}