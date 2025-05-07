#include <iostream>
#include <stack>
#include <unordered_map>
#include <cctype>

using namespace std;

// Tree Node definition
struct Node {
    char value;
    Node* left;
    Node* right;

    Node(char val) : value(val), left(nullptr), right(nullptr) {}
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Construct Expression Tree from Prefix
Node* constructTree(const string& prefix) {
    stack<Node*> st;

    for (int i = prefix.length() - 1; i >= 0; --i) {
        char c = prefix[i];

        if (!isOperator(c)) {
            st.push(new Node(c));
        } else {
            if (st.size() < 2) {
                cout << "Invalid prefix expression!" << endl;
                return nullptr;
            }
            Node* node = new Node(c);
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
            st.push(node);
        }
    }

    if (st.size() != 1) {
        cout << "Invalid prefix expression!" << endl;
        return nullptr;
    }

    return st.top();
}

// Non-recursive post-order traversal
void postOrderNonRecursive(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);

        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }

    cout << "Post-order Traversal (Non-Recursive): ";
    while (!s2.empty()) {
        cout << s2.top()->value << " ";
        s2.pop();
    }
    cout << endl;
}

// Recursive Evaluation
int evaluate(Node* root, unordered_map<char, int>& values) {
    if (!root) return 0;

    // Leaf node
    if (!root->left && !root->right) {
        char var = root->value;
        if (isdigit(var)) return var - '0';  // numeric value
        return values[var];
    }

    int leftVal = evaluate(root->left, values);
    int rightVal = evaluate(root->right, values);

    switch (root->value) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return rightVal != 0 ? leftVal / rightVal : 0;
    }
    return 0;
}

// Delete the tree
void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Main
int main() {
    string prefix;
    cout << "Enter prefix expression: ";
    cin >> prefix;

    Node* root = constructTree(prefix);

    if (!root) return 1;

    // Collect unique variables
    unordered_map<char, int> values;
    for (char c : prefix) {
        if (!isOperator(c) && !isdigit(c)) {
            if (values.find(c) == values.end()) {
                cout << "Enter value for '" << c << "': ";
                cin >> values[c];
            }
        }
    }

    // Post-order traversal
    postOrderNonRecursive(root);

    // Evaluate
    int result = evaluate(root, values);
    cout << "Final value of expression: " << result << endl;

    // Delete tree
    deleteTree(root);

    return 0;
}

