#include <bits/stdc++.h>
using namespace std;

// 移除前导零
void removeLeadingZeros(vector<int>& num) {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

// 大整数加法
vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    for (int i = 0; i < (int)a.size() || i <(int) b.size() || carry; ++i) {
        if (i < (int)a.size()) carry += a[i];
        if (i < (int)b.size()) carry += b[i];
        res.push_back(carry % 10);
        carry /= 10;
    }
    return res;
}

// 大整数除以小整数，返回商和余数
pair<vector<int>, int> div(const vector<int>& a, int b) {
    vector<int> res;
    int remainder = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        remainder = remainder * 10 + a[i];
        res.push_back(remainder / b);
        remainder %= b;
    }
    reverse(res.begin(), res.end());
    removeLeadingZeros(res);
    return make_pair(res, remainder);
}

// 字符串转大整数
//这里有点问题  就是没有考虑负数
vector<int> strToNum(const string& s) {
    vector<int> num;
    for (int i =(int) s.size() - 1; i >= 0; --i) {
        if(s[i]>='0'&&s[i]<='9')
            num.push_back(s[i] - '0');
    }
    removeLeadingZeros(num);
    return num;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        int k,p;
        string str;
        cin>>k>>p>>str;
        vector<int>vec=strToNum(str);
        int ans=(p==0)?1:0;
        vector<int>two;
        two.push_back(2);
        while(!(vec.size()==1&&vec[0]<=3)){
            vec=add(vec,two);
            vec=div(vec,3).first;
            ans++;
        }
        ans++;
        cout<<ans<<endl;
    }
    return 0;
}