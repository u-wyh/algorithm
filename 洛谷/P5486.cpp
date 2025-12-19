#include<bits/stdc++.h>
using namespace std;
const int MAXM = 101;
const int MAXN = 27;

int n,m;
int st,en;
int arr[MAXM][MAXN];

int main()
{
    int flag=0;
    while(cin>>m>>n){
        if(flag){
            cout<<endl;
        }
        flag++;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                char c;
                arr[i][j]= c=='O';
            }
        }
        cin>>st>>en;
        en--;
    }
    return 0;
}