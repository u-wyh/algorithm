#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
string s[5];

int to[5]={0,0,50,100,200};

int score[5];
int cnt[5];
bool dead[5];

int op[5];

int change(char c){
    if(c=='H'){
        return 0;
    }
    else if(c=='C'){
        return 1;
    }
    else if(c=='J'){
        return 2;
    }
    else if(c=='A'){
        return 3;
    }
    else{
        return 4;
    }
}

void calc(){
    int all=0;
    for(int i=1;i<=4;i++){
        score[i]-=to[op[i]];
        if(op[i]==0){
            cnt[i]++;
            if(cnt[i]==100){
                cnt[i]=0;
                all+=30;
                score[i]-=30;
            }
        }
        else{
            cnt[i]=0;
        }
    }
    for(int i=1;i<=4;i++){
        score[i]+=all;
        if(score[i]<=0){
            dead[i]=true;
        }
        score[i]=min(score[i],2000);
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=4;i++){
        cin>>s[i];
        score[i]=2000;
        cnt[i]=0;
        dead[i]=false;
    }

    for(int i=0;i<n;i++){
        for(int j=1;j<=4;j++){
            op[j]=change(s[j][i]);
            // cout<<op[j]<<' ';
        }
        // cout<<endl;
        calc();
    }

    for(int i=1;i<=4;i++){
        if(dead[i]){
            cout<<0<<' ';
        }
        else{
            cout<<score[i]<<' ';
        }
    }
    cout<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
/*
3
5
CCCCC
JJJJJ
AAAAA
MMMMM
10
HCJAMHCJAM
CHCHCHCHCH
JAMJAMJAMJ
MAJHAMMACH
103
MMMMMMMMMMCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
CJCJCJCJHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHJJJCJCJCJCJCJCJCJCJCJCJCJCJCJCJCJCJCJC
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
*/