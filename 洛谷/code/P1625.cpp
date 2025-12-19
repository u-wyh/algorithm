#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<int>a,b;

void removeleadingzeros(vector<int>&a){
    while(a.size()>1&&a.back()==0){
        a.pop_back();
    }
}

int compare(const vector<int>&a,const vector<int>&b){
    if(a.size()!=b.size()){
        return a.size()>b.size()?1:-1;
    }
    for(int i=a.size()-1;i>=0;i--){
        if(a[i]!=b[i]){
            return a[i]>b[i]?1:-1;
        }
    }
    return 0;
}

vector<int> add(const vector<int>&a,const vector<int>&b){
    vector<int>res;
    int diff=0;
    for(int i=0;i<(int)a.size()||i<(int)b.size()||diff;i++){
        if(i<(int)a.size()) diff+=a[i];
        if(i<(int)b.size()) diff+=b[i];
        res.push_back(diff%10);
        diff/=10;
    }
    removeleadingzeros(res);
    return res;
}

vector<int> mul(const vector<int>&a,int b){
    vector<int>res;
    int diff=0;
    for(int i=0;i<(int)a.size()||diff;i++){
        if(i<(int)a.size()) diff+=b*a[i];
        res.push_back(diff%10);
        diff/=10;
    }
    removeleadingzeros(res);
    return res;
}

vector<int> sub(const vector<int>&a,const vector<int>&b){
    vector<int>res;
    int diff=0;
    for(int i=0;i<(int)a.size();i++){
        diff=a[i]-diff;
        if(i<(int)b.size()) diff-=b[i];
        res.push_back((diff+10)%10);
        diff=(diff<0)?1:0; 
    }
    removeleadingzeros(res);
    return res;
}

pair<vector<int>,vector<int>> div(const vector<int>&a,const vector<int>&b){
    vector<int>res;
    vector<int>diff;
    for(int i=a.size()-1;i>=0;i--){
        diff.insert(diff.begin(),a[i]);
        removeleadingzeros(diff);
        int ans=0;
        while(compare(diff,b)>=0){
            diff=sub(diff,b);
            ans++;
        }
        res.push_back(ans);
    }
    reverse(res.begin(),res.end());
    removeleadingzeros(res);
    return make_pair(res,diff);
}

string numtostr(const vector<int>&a){
    string s;
    for(int i=a.size()-1;i>=0;i--){
        s+=to_string(a[i]);
    }
    return s;
}

vector<int> strtonum(const string &s){
    vector<int>res;
    for(int i=0;i<(int)s.length();i++){
        res.push_back(s[i]-'0');
    }
    return res;
}

vector<int>gcd(const vector<int>&a,const vector<int>&b){
    // cout<<numtostr(a)<<' '<<numtostr(b)<<endl;
    if(b.size()==1&&b[0]==0){
        return a;
    }
    return gcd(b,div(a,b).second);
}

int main()
{
    cin>>n>>m;
    b.push_back(1);
    for(int i=2;i<=(m+n-1);i++){
        b=mul(b,i);
    }
    a.push_back(0);
    for(int i=1;i<=n;i++){
        vector<int>c;
        c.push_back(1);
        for(int j=1;j<i;j++){
            c=mul(c,j);
        }
        for(int j=m+i;j<=(m+n-1);j++){
            c=mul(c,j);
        }
        a=add(a,c);
    }
    vector<int>e=gcd(a,b);
    // cout<<numtostr(a)<<' '<<numtostr(b)<<' ';
    // cout<<numtostr(e)<<endl;
    cout<<numtostr(div(a,e).first)<<endl;
    cout<<numtostr(div(b,e).first);
    return 0;
}