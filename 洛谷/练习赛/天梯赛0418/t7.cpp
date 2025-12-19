#include<bits/stdc++.h>
using namespace std;

int n;

int maxans=INT_MIN,maxcnt;
int minans=INT_MAX,mincnt;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        int u;
        cin>>u;
        if(u>maxans){
            maxans=u;
            maxcnt=1;
        }
        else if(u==maxans){
            maxcnt++;
        }

        if(u<minans){
            minans=u;
            mincnt=1;
        }
        else if(u==minans){
            mincnt++;
        }
    }
    cout<<minans<<' '<<mincnt<<endl<<maxans<<' '<<maxcnt<<endl;
    return 0;
}