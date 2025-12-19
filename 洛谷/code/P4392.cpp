#include<bits/stdc++.h>
using namespace std;

int n,m,c;
int maxqueue[10005],minqueue[10005],arr[1000005];
int maxhead=0,maxtail=0,minhead=0,mintail=0;
bool p=false;

int main()
{
    cin>>n>>m>>c;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n;i++){
        while(maxhead<maxtail&&i-maxqueue[maxhead]>=m){
            maxhead++;
        }
        while(minhead<mintail&&i-minqueue[minhead]>=m){
            minhead++;
        }
        while(maxhead<maxtail&&arr[maxqueue[maxtail-1]]<=arr[i]){
            maxtail--;
        }
        maxqueue[maxtail++]=i;
        while(minhead<mintail&&arr[minqueue[mintail-1]]>=arr[i]){
            mintail--;
        }
        minqueue[mintail++]=i;
        if(i>=m){
            if(arr[maxqueue[maxhead]]-arr[minqueue[minhead]]<=c){
                cout<<i-m+1<<endl;
                p=true;
            }
        }
    }
    if(!p)
        cout<<"NONE";
    return 0;
}
