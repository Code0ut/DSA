/*A Dictionary stores keywords & its meanings. Provide facility for adding new keywords,
deleting keywords, updating values of any entry. Provide facility to display whole data sorted
in ascending/ Descending order. Also find how many maximum comparisons may require for
finding any keyword. Use Height balance tree and find the complexity for finding a keyword*/
#include<iostream>
#include<string>
using namespace std;

class Node {
public:
    string keyword, meaning;
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    Node* balance(Node* node) {
        int balanceFactor = getBalance(node);
        if (balanceFactor > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);
        if (balanceFactor > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balanceFactor < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);
        if (balanceFactor < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* insert(Node* node, string key, string meaning) {
        if (!node) return new Node(key, meaning);
        if (key < node->keyword)
            node->left = insert(node->left, key, meaning);
        else if (key > node->keyword)
            node->right = insert(node->right, key, meaning);
        else {
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balance(node);
    }

    Node* findMin(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, string key) {
        if (!node) return nullptr;
        if (key < node->keyword)
            node->left = remove(node->left, key);
        else if (key > node->keyword)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = findMin(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = remove(node->right, temp->keyword);
            }
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balance(node);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->keyword << " : " << node->meaning << endl;
        inorder(node->right);
    }

    void reverseInorder(Node* node) {
        if (!node) return;
        reverseInorder(node->right);
        cout << node->keyword << " : " << node->meaning << endl;
        reverseInorder(node->left);
    }

    void update(Node* node, string key, string newMeaning) {
        if (!node) {
            cout << "Keyword not found.\n";
            return;
        }
        if (key < node->keyword)
            update(node->left, key, newMeaning);
        else if (key > node->keyword)
            update(node->right, key, newMeaning);
        else
            node->meaning = newMeaning;
    }

    int search(Node* node, string key, int& comparisons) {
        if (!node) return -1;
        comparisons++;
        if (key < node->keyword)
            return search(node->left, key, comparisons);
        else if (key > node->keyword)
            return search(node->right, key, comparisons);
        else
            return comparisons;
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void remove(string key) {
        root = remove(root, key);
    }

    void update(string key, string newMeaning) {
        update(root, key, newMeaning);
    }

    void displayAscending() {
        inorder(root);
    }

    void displayDescending() {
        reverseInorder(root);
    }

    void searchKeyword(string key) {
        int comparisons = 0;
        int result = search(root, key, comparisons);
        if (result == -1)
            cout << "Keyword not found.\n";
        else
            cout << "Keyword found with " << comparisons << " comparisons.\n";
    }

    void maxComparisons() {
        cout << "Maximum comparisons needed: " << getHeight(root) << "\n";
    }
};

int main() {
    AVLTree dict;
    int choice;
    string key, meaning;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add/Update Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Display in Ascending Order\n";
        cout << "5. Display in Descending Order\n";
        cout << "6. Search Keyword\n";
        cout << "7. Max Comparisons\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.insert(key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                dict.remove(key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.update(key, meaning);
                break;
            case 4:
                dict.displayAscending();
                break;
            case 5:
                dict.displayDescending();
                break;
            case 6:
                cout << "Enter keyword to search: ";
                cin >> key;
                dict.searchKeyword(key);
                break;
            case 7:
                dict.maxComparisons();
                break;
        }
    } while(choice != 0);

    return 0;
}
