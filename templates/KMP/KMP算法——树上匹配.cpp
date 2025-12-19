// 二叉树中的链表
// 给你一棵以root为根的二叉树、一个以head为头的链表
// 在二叉树中，有很多一直向下的路径
// 如果某个路径上的数值等于以head为头的整个链表
// 返回True，否则返回False
// 测试链接 : https://leetcode.cn/problems/linked-list-in-binary-tree/
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> nextArray(vector<int>& s) {
    int m = s.size();
    vector<int> next(m, 0);
    if (m == 0) return next;
    
    next[0] = -1;
    if (m == 1) return next;
    
    next[1] = 0;
    int i = 2, cn = 0;
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            next[i++] = ++cn;
        } else if (cn > 0) {
            cn = next[cn];
        } else {
            next[i++] = 0;
        }
    }
    return next;
}

bool find(vector<int>& s2, vector<int>& next, TreeNode* cur, int i) {
    if (i == s2.size()) return true;
    if (!cur) return false;
    
    while (i >= 0 && cur->val != s2[i]) {
        i = next[i];
    }
    return find(s2, next, cur->left, i + 1) || 
           find(s2, next, cur->right, i + 1);
}

bool isSubPath(ListNode* head, TreeNode* root) {
    vector<int> s2;
    while (head) {
        s2.push_back(head->val);
        head = head->next;
    }
    if (s2.empty()) return true;
    
    vector<int> next = nextArray(s2);
    return find(s2, next, root, 0);
}

TreeNode* buildTree(const vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;
    
    queue<TreeNode*> q;
    TreeNode* root = new TreeNode(nodes[0]);
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* cur = q.front();
        q.pop();
        
        if (i < nodes.size() && nodes[i] != -1) {
            cur->left = new TreeNode(nodes[i]);
            q.push(cur->left);
        }
        i++;
        
        if (i < nodes.size() && nodes[i] != -1) {
            cur->right = new TreeNode(nodes[i]);
            q.push(cur->right);
        }
        i++;
    }
    return root;
}

int main() {
    int n, m;
    cin >> n;
    
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        ListNode* node = new ListNode(val);
        if (!head) head = node;
        else tail->next = node;
        tail = node;
    }
    
    cin >> m;
    vector<int> treeNodes(m);
    for (int i = 0; i < m; i++) {
        cin >> treeNodes[i];
    }
    
    TreeNode* root = buildTree(treeNodes);
    cout << (isSubPath(head, root) ? "true" : "false") << endl;
    
    // 清理内存
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    // 注意：二叉树内存清理需要递归删除，这里省略
    return 0;
}