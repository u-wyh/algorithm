#include<bits/stdc++.h>
using namespace std;

int a[10];
int b[10];

int main()
{
    for(int i=1;i<=9;i++){
        cin>>a[i];
    }
    b[1]=a[1]%2;
    a[2]+=a[1]/2;

    b[2]=a[2]%3;
    a[3]+=a[2]/3;

    b[3]=a[3]%2;
    a[4]+=a[3]/2;

    b[4]=a[4]%3;
    a[5]+=a[4]/3;

    b[5]=a[5]%2;
    a[6]+=a[5]/2;

    b[6]=a[6]%3;
    a[7]+=a[6]/3;

    b[7]=a[7]%2;
    a[8]+=a[7]/2;

    b[8]=a[8]%3;
    a[9]+=a[8]/3;

    b[9]=a[9];

    for(int i=1;i<=8;i++){
        cout<<b[i]<<' ';
    }
    cout<<b[9]<<endl;
    return 0;
}