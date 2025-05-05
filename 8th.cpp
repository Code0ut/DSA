/*Given sequence k = k1 < k2<…<kn of n sorted keys, with a search probability pi for each key ki. Build the binary search tree that has the least search cost given the access probability for each key*/

#include<iostream>
#include<vector>
#include<climits>

using namespace std;

struct Node{
	int key;
	Node* left;
	Node* right;
	Node(int k){
		key=k;
		left=right=nullptr;
	}
};
	
Node* buildTree(vector<vector<int>>& root,vector<int>& keys,int i,int j){
	if(i>j)return NULL;
	int r=root[i][j];
	Node* node=new Node(keys[r]);
	node->left=buildTree(root,keys,i,r-1);
	node->left=buildTree(root,keys,r+1,i);
	return node;
}

void inorder(Node* root){
	if(root==NULL) return;
	inorder(root->left);
	cout<<root->key<<" ";
	inorder(root->left);
}

int main(){
	 int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<int> keys(n);
    vector<float> prob(n);

    cout << "Enter the keys in sorted order:\n";
    for (int i = 0; i < n; i++) cin >> keys[i];

    cout << "Enter their corresponding search probabilities:\n";
    for (int i = 0; i < n; i++) cin >> prob[i];

	vector<vector<float>> cost(n, vector<float>(n, 0));
    	vector<vector<int>> root(n, vector<int>(n, 0));
	
	for (int i = 0; i < n; i++) {
        cost[i][i] = prob[i];
        root[i][i] = i;
    }

	for(int gap=1;gap<n;gap++){
		for(int i=0;i<n-gap;i++){
			int j=i+gap;
			cost[i][j]=INT_MAX;
			float sum=0;
			for(int k=i;k<=j;k++)sum+=prob[k];
			for(int r=i;r<=j;r++){
				float left=(r>i)?cost[i][r-1]:0;
				float right=(r>j)?cost[r+1][j]:0;
				float total=left+right+sum;

				if(total<cost[i][j]){
					cost[i][j]=total;
					root[i][j]=r;	
				}
			}

				
		}
	}
	 cout << "\nMinimum cost of OBST: " << cost[0][n - 1] << "\n";

    Node* treeRoot = buildTree(root, keys, 0, n - 1);
    cout << "Preorder traversal of Optimal BST:\n";
    inorder(treeRoot);
    cout << endl;
}