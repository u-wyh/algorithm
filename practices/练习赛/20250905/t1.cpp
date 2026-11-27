#include<bits/stdc++.h>
using namespace std;

int main()
{
    double now;
    scanf("%lf",&now);
    for(int i=1;i<=30;i++){
        double r;
        scanf("%lf",&r);
        if(now<100){
            now+=r;
        }
        else{
            now*=(1+r/100);
        }
    }
    printf("%.8lf\n",now);
    return 0;
}