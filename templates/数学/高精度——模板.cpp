//这个代码的缺点就是没有处理符号位
// 用的时候自己注意一下  如果是乘法除法最后改变一下符号位即可
// 加法的话  同号的话直接加  异号的话就是减
// 减法的话  同号直接减  异号直接加
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

// 示例使用
int main() {
    string s1, s2;
    cout << "输入两个大整数:" << endl;
    cin >> s1 >> s2;
    
    vector<int> a = strToNum(s1);
    vector<int> b = strToNum(s2);
    
    // 加法
    vector<int> sum = add(a, b);
    cout << "加法结果: " << numToStr(sum) << endl;
    
    // 减法 (确保a >= b)
    if (compare(a, b) >= 0) {
        vector<int> diff = sub(a, b);
        cout << "减法结果: " << numToStr(diff) << endl;
    } else {
        cout << "减法结果: -" << numToStr(sub(b, a)) << endl;
    }
    
    // 乘法
    vector<int> product = mul(a, b);
    cout << "乘法结果: " << numToStr(product) << endl;
    
    // 除法 (大数除以小数)
    if (b.size() == 1) {
        pair<vector<int>, int> divisionResult = div(a, b[0]);
        cout << "除法结果(商): " << numToStr(divisionResult.first) 
             << " 余数: " << divisionResult.second << endl;
    }
    
    // 除法 (大数除以大数)
    if (compare(b, vector<int>(1, 0)) != 0) {  // 除数不为0
        vector<int> quotient = div(a, b);
        cout << "除法结果(商): " << numToStr(quotient) << endl;
    } else {
        cout << "除数不能为0" << endl;
    }
    
    return 0;
}