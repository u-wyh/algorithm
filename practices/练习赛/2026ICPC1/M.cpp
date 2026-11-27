#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
map<string,int>mp;
int sta[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string str;
        cin>>str;
        mp[str]=i;
        sta[i]=0;
    }
    for(int i=1;i<=m;i++){
        string str;
        cin>>str;
        int id=mp[str];
        if(id==0){
            cout<<"WRONG"<<endl;
        }
        else if(sta[id]){
            cout<<"REPEAT"<<endl;
        }
        else{
            cout<<"OK"<<endl;
            sta[id]=1;
        }
    }
    return 0;
}
/*
5 9
RebornAsaVegetableDog
LetItRot
NaiveBirds
OpenYourBrain
CaptainTakesMeNot
CaptainTakesMeNot
OpenYourBrain
NaiveBirds
LetItRot
RebornAsaVegetableDog
NaiveBirds
OneStepAway
Metempsychosis
CaptainTakesMeNot
*/