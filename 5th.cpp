#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

template<typename T>
class Stack {
    T array[10];
    int top;
public:
    Stack() {
        top = -1;
    }

    void push(T value) {
        if (top == 9) {
            cout << "Stack Overflow\n";
            return;
        }
        array[++top] = value;
    }

    T peek() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return T();
        }
        return array[top];
    }

    void pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }

    bool empty() {
        return top == -1;
    }
};

struct Node {
    char val;
    Node* left;
    Node* right;
    Node(char c) {
        val = c;
        left = nullptr;
        right = nullptr;
    }
};

class Tree {
    Node* root;
public:
    Tree() {
        root = nullptr;
    }

    void prefixToTree(string prefix) {
        Stack<Node*> st;
        for (int i = prefix.length() - 1; i >= 0; i--) {
            Node* node = new Node(prefix[i]);
            if (isalpha(prefix[i]) || isdigit(prefix[i])) {
                st.push(node);
            } else {
                node->left = st.peek(); st.pop();
                node->right = st.peek(); st.pop();
                st.push(node);
            }
        }
        if (!st.empty())
            root = st.peek();
    }

    void postorderTraversal() {
        if (!root) return;

        stack<Node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            Node* node = s1.top(); s1.pop();
            s2.push(node);
            if (node->left) s1.push(node->left);
            if (node->right) s1.push(node->right);
        }

        while (!s2.empty()) {
            cout << s2.top()->val << " ";
            s2.pop();
        }
        cout << endl;
    }

    void deleteTree() {
        if (!root) return;
        stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* node = s.top(); s.pop();
            if (node->left) s.push(node->left);
            if (node->right) s.push(node->right);
            delete node;
        }
        root = nullptr;
    }
};

int main() {
    Tree tree;
    while (true) {
        int ch;
        cout << "MAIN MENU\n1. Create tree from prefix equation\n2. Print post order traversal\n3. EXIT\n";
        cin >> ch;
        cin.ignore();

        if (ch == 1) {
            string pre;
            cout << "Enter the prefix equation: ";
            getline(cin, pre);
            tree.prefixToTree(pre);
        } else if (ch == 2) {
            cout << "Postorder Traversal: ";
            tree.postorderTraversal();
        } else if (ch == 3) {
            tree.deleteTree();
            break;
        } else {
            cout << "Invalid Choice!\n";
        }
    }
    return 0;
}
