#include<bits/stdc++.h>
using namespace std;

int m,n,p;
map<string,int>mp;
string str[105];
string name[22];
int ok[105];
int ans[22];

string guil;
string date[]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

string s1="I am guilty";
string s2="I am not guilty";
string s3="is guilty";
string s4="is not guilty";
string s5="Today is ";

int main()
{
    cin>>m>>n>>p;
    for(int i=1;i<=m;i++){
        cin>>name[i];
        mp[name[i]]=i;
    }
    getchar();
    for(int i=1;i<=p;i++){
        getline(cin,str[i]);
        int pos=str[i].find(':');
        int num=mp[str[i].substr(0,pos)];
        str[i].replace(0,pos,to_string(num));
        cout<<str[i]<<endl;
    }
    for(int i=1;i<=p;i++){
        if(str[i].find(s1)!=string::npos){
            ok[i]=1;
        }
        else if(str[i].find(s2)!=string::npos){
            ok[i]=2;
        }
        else if(str[i].find(s3)!=string::npos){
            ok[i]=3;
        }
        else if(str[i].find(s4)!=string::npos){
            ok[i]=4;
        }
        else if(str[i].find(s5)!=string::npos){
            ok[i]=5;
        }
        cout<<ok[i]<<' ';
    }
    cout<<endl;
    int res=0;
    string pos;
    for(int i=1;i<=m;i++){
        for(int j=0;j<=6;j++){
            if(res>=2){
                break;
            }
            bool flag=1;
            for(int k=1;k<=m;k++){
                ans[k]=0;
            }
            for(int k=1;k<=p;k++){
                int peo=str[k][0]-'0';
                if(ok[k]==0){
                    continue;
                }
                if(ok[k]==5){
                    if(str[k].find(date[j])!=string::npos){
                        if(ans[peo]==1){
                            flag=0;
                            break;
                        }
                        ans[peo]=2;
                    }
                    else{
                        if(ans[peo]==2){
                            flag=0;
                            break;
                        }
                        ans[peo]=1;
                    }
                }
                else if(ok[k]==1){
                    if(peo==i){
                        if(ans[peo]==1){
                            flag=0;
                            break;
                        }
                        ans[peo]=2;
                    }
                    else{
                        if(ans[peo]==2){
                            flag=0;
                            break;
                        }
                        ans[peo]=1;
                    }
                }
                else if(ok[k]==2){
                    if(peo!=i){
                        if(ans[peo]==1){
                            flag=0;
                            break;
                        }
                        ans[peo]=2;
                    }
                    else{
                        if(ans[peo]==2){
                            flag=0;
                            break;
                        }
                        ans[peo]=1;
                    }
                }
                else if(ok[k]==3){
                    if(str[k].find(name[i])!=string::npos){
                        if(ans[peo]==1){
                            flag=0;
                            break;
                        }
                        ans[peo]=2;
                    }
                    else{
                        if(ans[peo]==2){
                            flag=0;
                            break;
                        }
                        ans[peo]=1;
                    }
                }
                else{
                    if(str[k].find(name[i])==string::npos){
                        if(ans[peo]==1){
                            flag=0;
                            break;
                        }
                        ans[peo]=2;
                    }
                    else{
                        if(ans[peo]==2){
                            flag=0;
                            break;
                        }
                        ans[peo]=1;
                    }
                }
            }

            if(!flag){
                continue;
            }
            int cnt=0;
            for(int i=1;i<=m;i++){
                if(ans[i]==2){
                    cnt++;
                }
            }   
            if(p-cnt==n){
                res++;
                pos=name[i];
            }
            
        }
    }
    if(res==0){
        cout<<"Impossible";
    }
    else if(res==1){
        cout<<pos;
    }
    else{
        cout<<"Cannot Determine";
    }
    return 0;
}