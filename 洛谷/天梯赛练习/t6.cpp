#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int u=2*n*n+n;
    printf("%d^2 ",u);
    u++;
    for(int i=1;i<=n;i++){
        printf("+ %d^2 ",u);
        u++;
    }
    cout<<"=\n";
    printf("%d^2",u);
    if(n>1){
        cout<<' ';
    }
    u++;
    for(int i=2;i<n;i++){
        printf("+ %d^2 ",u);
        u++;
    }
    if(n>=2)
        printf("+ %d^2",u);
    return 0;
}