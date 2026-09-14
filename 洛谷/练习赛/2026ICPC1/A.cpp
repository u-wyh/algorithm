#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

int n;
char op[MAXN];
int a[MAXN];
char lst[MAXN];

void solve(){
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> op[i] >> a[i];
    }

    // lst[i] 表示第 i 个操作之后，
    // 下一个关于同一个 x 的操作是什么
    map<int, char> last;

    for(int i = n; i >= 1; i--){
        int x = a[i];

        if(last.count(x))
            lst[i] = last[x];
        else
            lst[i] = 'E';

        last[x] = op[i];
    }

    stack<int> st;
    map<int, bool> ex;
    map<int, char> nxt;

    string ans;

    for(int i = 1; i <= n; i++){
        char ch = op[i];
        int x = a[i];

        nxt[x] = lst[i];

        if(ch == '+'){
            // 如果旧的 x 还在栈里，必须先弹掉
            while(ex[x]){
                ex[st.top()] = false;
                st.pop();
                ans += '-';
            }

            ans += '+';

            // 如果下一次关于 x 的操作不是 T，
            // 那么这个 x 已经没有保留的必要
            if(lst[i] == 'T'){
                st.push(x);
                ex[x] = true;
            }else{
                ans += '-';
            }
        }
        else if(ch == 'T'){
            ans += '?';

            // 把栈顶已经不再需要的元素全部删除
            while(!st.empty()){
                int y = st.top();

                if(nxt[y] == 'T') break;

                st.pop();
                ex[y] = false;
                ans += '-';
            }
        }
        else{ // F
            // F x 要求 x 当前不存在
            while(ex[x]){
                ex[st.top()] = false;
                st.pop();
                ans += '-';
            }

            ans += '?';
        }
    }

    while(!st.empty()){
        st.pop();
        ans += '-';
    }

    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--){
        solve();
    }

    return 0;
}