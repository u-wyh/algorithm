#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility> // 用于pair
using namespace std;

// 移除前导零
void removeLeadingZeros(vector<int>& num) {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

// 比较两个大整数的大小，返回1表示a>b，0表示a==b，-1表示a<b
int compare(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) {
        return a.size() > b.size() ? 1 : -1;
    }
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] != b[i]) {
            return a[i] > b[i] ? 1 : -1;
        }
    }
    return 0;
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

// 大整数减法 (假设a >= b)
vector<int> sub(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    for (int i = 0; i <(int) a.size(); ++i) {
        carry = a[i] - carry;
        if (i < (int)b.size()) carry -= b[i];
        res.push_back((carry + 10) % 10);
        carry = carry < 0 ? 1 : 0;//如果carry<0  说明要向上借位
    }
    removeLeadingZeros(res);
    return res;
}

// 大整数乘以小整数
vector<int> mul(const vector<int>& a, int b) {
    vector<int> res;
    int carry = 0;
    for (int i = 0; i <(int) a.size() || carry; ++i) {
        if (i <(int64_t) a.size()) carry += a[i] * b;
        res.push_back(carry % 10);
        carry /= 10;
    }
    removeLeadingZeros(res);
    return res;
}

// 大整数乘以大整数
vector<int> mul(const vector<int>& a, const vector<int>& b) {
    vector<int> res(a.size() + b.size(), 0);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            res[i + j] += a[i] * b[j];
            res[i + j + 1] += res[i + j] / 10;
            res[i + j] %= 10;
        }
    }
    removeLeadingZeros(res);
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

// 大整数除以大整数 (简单实现，效率不高)
vector<int> div(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    vector<int> current;
    
    for (int i = a.size() - 1; i >= 0; --i) {
        current.insert(current.begin(), a[i]);
        removeLeadingZeros(current);
        
        int quotient = 0;
        while (compare(current, b) >= 0) {
            current = sub(current, b);
            quotient++;
        }
        res.push_back(quotient);
    }
    
    reverse(res.begin(), res.end());
    removeLeadingZeros(res);
    return res;
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

// 大整数转字符串
string numToStr(const vector<int>& num) {
    string s;
    for (int i = num.size() - 1; i >= 0; --i) {
        s += to_string(num[i]);
    }
    return s;
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int find(int val){
    int l=1,r=n,ans=n+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

const int MAXN = 2e5+5; 
int n,q;
int nums[MAXN];

vector<int>p[MAXN];
vector<int>f[MAXN];

int main() 
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    p[0].push_back(1);
    for(int i=1;i<=n+1;i++){
        p[i]=mul(p[i-1],2);
    }
    f[0].push_back(0);
    for(int i=1;i<=n;i++){
        f[i]=mul(p[i],nums[i]);
        f[i]=add(f[i],f[i-1]);
    }
    while(q--){
        int x,y;
        x=read(),y=read();
        y=n-y+1;
        int rk=find(x);
        if(rk>y){
            cout<<0<<endl;
            continue;
        }
        vector<int>ans=div(add(add(mul(p[rk],x),sub(f[y],f[rk-1])),div(p[y+1],p[rk])),p[y+1]);
        
    }
    return 0;
}