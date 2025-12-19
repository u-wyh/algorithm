#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<int>dp[55][55];

// 移除前导零
void removeLeadingZeros(vector<int>& num) {
    while(num.size()>1&&num.back()==0){
		num.pop_back();
	}
}

// 大整数加法
vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int>res;
	int diff=0;
	for(int i=0;i<(int)a.size()||i<(int)b.size()||diff;i++){
		if(i<(int)a.size()) diff+=a[i];
		if(i<(int)b.size()) diff+=b[i];
		res.push_back(diff%10);
		diff/=10;
	}
	return res;
}

// 大整数乘以小整数
vector<int> mul(const vector<int>& a, int b) {
    vector<int>res;
	int diff=0;
	for(int i=0;i<(int)a.size()||diff;i++){
		if(i<(int)a.size()) diff+=b*a[i];
		res.push_back(diff%10);
		diff/=10;
	}
	removeLeadingZeros(res);
	return res;
}

vector<int> strToNum(const string& s) {
    vector<int>num;
	for(int i=s.length()-1;i>=0;i--){
		if(s[i]>='0'&&s[i]<='9'){
			num.push_back(s[i]-'0');
		}
	}
	return num;
}

// 大整数转字符串
string numToStr(const vector<int>& num) {
    string s;
	for(int i=(int)num.size()-1;i>=0;i--){
		s+=to_string(num[i]);
	}
	return s;
}

int main()
{
    cin>>n>>m;
    for(int i=2;i<=m;i++){
        dp[1][i].push_back(0);
    }
    dp[1][1].push_back(1);
    for(int i=2;i<=n;i++){
        for(int j=1;j<=min(i,m);j++){
            dp[i][j]=add(dp[i-1][j-1],mul(dp[i-1][j],j));
        }
        for(int j=min(i,m)+1;j<=m;j++){
            dp[i][j].push_back(0);
        }
    }
    cout<<numToStr(dp[n][m])<<endl;
    return 0;
}