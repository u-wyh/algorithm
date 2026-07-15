#include<bits/stdc++.h>
using namespace std;

int n,m;

vector<int>a;
vector<int>b;
vector<int>c;
vector<int>d;

void removeleadingzeros(vector<int>&a){
    while(a.size()>1&&a.back()==0){
        a.pop_back();
    }
}

// 大整数减法 (假设a >= b)
vector<int> sub(const vector<int>& a, const vector<int>& b) {
    vector<int>res;
	int diff=0;
	for(int i=0;i<(int)a.size();i++){
		diff=a[i]-diff;
		if(i<(int)b.size()) diff-=b[i];
		res.push_back((diff+10)%10);
		diff=diff<0?1:0;
	}
	removeleadingzeros(res);
	return res;
}

vector<int>mul(const vector<int>&a,int b){
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

vector<int>mul(const vector<int>&a,const vector<int>&b){
    vector<int>res(a.size()+b.size(),0);
    for(int i=0;i<(int)a.size();i++){
        for(int j=0;j<(int)b.size();j++){
            res[i+j]+=a[i]*b[j];
            res[i+j+1]+=res[i+j]/10;
            res[i+j]%=10;
        }
    }
    removeleadingzeros(res);
    return res;
}

pair<vector<int>, int> div(const vector<int>& a, int b) {
    vector<int>res;
	int diff=0;
	for(int i=(int)a.size()-1;i>=0;i--){
		diff=diff*10+a[i];
		res.push_back(diff/b);
		diff%=b;
	}
	reverse(res.begin(),res.end());
	removeleadingzeros(res);
	return make_pair(res,diff);
}

string numtostr(vector<int>&a){
    string s;
    for(int i=a.size()-1;i>=0;i--){
        s+=to_string(a[i]);
    }
    return s;
}

int main()
{
    cin>>n>>m;
    if((n==0&&m==0)||(m-1>n+2)){
        cout<<0<<endl;
        return 0;
    }
    a.push_back(1);
    for(int i=1;i<=n+2;i++){
        a=mul(a,i);
    }
    for(int i=1;i<=m;i++){
        a=mul(a,i);
    }
    c.push_back(1);
    for(int i=1;i<=m;i++){
        c=mul(c,n+4-i);
        c=div(c,i).first;
    }
    a=mul(a,c);

    b.push_back(2);
    for(int i=1;i<=n+1;i++){
        b=mul(b,i);
    }
    for(int i=1;i<=m;i++){
        b=mul(b,i);
    }
    d.push_back(1);
    for(int i=1;i<=m;i++){
        d=mul(d,n+3-i);
        d=div(d,i).first;
    }
    b=mul(b,d);
    a=sub(a,b);
    cout<<numtostr(a);
    return 0;
}