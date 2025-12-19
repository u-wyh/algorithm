#include<bits/stdc++.h>
using namespace std;

int n,m;
int colop=-1;
int col=1;
int row=1;
vector<vector<int>>vec;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

void compute(int st,int en){
    // cout<<col<<' '<<st<<' '<<en<<endl;
    vec[row][col]=st;
    row=(row+st-1)%n+1;
    int op=-1;
    for(int i=st+1;i<=en;i++){
        // cout<<i<<":  "<<col<<' '<<row<<endl;
        vec[row][col]=i;
        row=((row+i*op-1)%n+n)%n+1;
        op*=-1;
    }
    col=((col+colop*en-1)%m+m)%m+1;
    // cout<<col<<' '<<colop<<' '<<en<<' '<<m<<endl;
    colop*=-1;
}

int main()
{
    cin>>n>>m;
    if(gcd(n,m)!=1){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    vec.resize(n+1,vector<int>(m+1,0));
    for(int i=1;i<=m;i++){
        compute((i-1)*n+1,i*n);
    }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                printf("%d ",vec[i][j]);
            }
            printf("\n");
        }
    return 0;
}