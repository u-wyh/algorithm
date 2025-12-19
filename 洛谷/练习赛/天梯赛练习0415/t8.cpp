#include<bits/stdc++.h>
using namespace std;

int arr[10][10];

int x[10][10];
int y[10][10];
int squ[10][10];

bool check(){
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            x[i][j]=y[i][j]=squ[i][j]=0;
        }
    }
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            x[i][arr[i][j]]=1;
            y[j][arr[i][j]]=1;
            squ[(i-1)/3*3+(j-1)/3+1][arr[i][j]]=1;
        }
    }
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(x[i][j]!=1)
                return false;
            if(y[i][j]!=1)
                return false;
            if(squ[i][j]!=1)
                return false;
        }
    }
    return true;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                cin>>arr[i][j];
            }
        }
        if(check()){
            cout<<1<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
    return 0;
}