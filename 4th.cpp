/*Beginning with an empty binary search tree, Construct binary search tree by inserting the
values in the order given. d. After constructing a binary tree – i. Insert new node ii. Find
number of nodes in longest path from root iii. Minimum data value found in the tree iv.
Change a tree so that the roles of the left and right pointers are swapped at every node v.
Search a value.*/

#include<iostream>
#include<string>
using namespace std;

struct Node{
	string name;
	Node* left;
	Node* right;
	Node(string nm){
		name=nm;
		left=nullptr;
		right=nullptr;
	}
};

class binTree{
	Node* head;
	public:
		binTree(){
			head=nullptr;
		}
		void insert(string value){
			Node* temp=new Node(value);			
			if (head==nullptr){
				head=temp;
				return;
			}
			Node* pointer=head;
			while(true){
				if(value<pointer->name){
					if(pointer->left==nullptr){ 
						pointer->left=temp;
						break;
						}
					else{
						pointer=pointer->left;
					}
				}
				else{
					if(pointer->right==nullptr){ 
						pointer->right=temp;
						break;
						}
					else{
						pointer=pointer->right;
					}
				}
			}
			return;
		}
		int height(){return heightHelp(head);}
		int heightHelp(Node* temp){
			if(temp==nullptr) return 0;
			return max(1+heightHelp(temp->left),1+heightHelp(temp->right));
		}
		
		string minValue(){
			Node* temp=head;
			while(temp->left!=nullptr){
				temp=temp->left;
			}
			return temp->name;
		}
		void swap(){return swapHelp(head);}
		void swapHelp(Node* temp){
			if(temp==nullptr) return;
			swapHelp(temp->left);
			swapHelp(temp->right);
			Node* buffer=temp->right;
			temp->right=temp->left;
			temp->left=buffer;
			return;
		}
		
		bool search(string value){
			Node* pointer=head;
			while(pointer!=nullptr){
			if(value<pointer->name){
				pointer=pointer->left;
			} 
			else if(value>pointer->name){
				pointer=pointer->right;
			}
			else{
				return true;
			}
			}
			return false;
		}
		void display() {
    			displayTree(head, 0);
		}

		void displayTree(Node* temp, int space) {
    			if (temp == nullptr) return;
			space += 5;  // increase distance between levels

		    	displayTree(temp->right, space);

    			cout << endl;
    			for (int i = 5; i < space; i++) cout << " ";
    			cout << temp->name << "\n";

    			displayTree(temp->left, space);
			}
			
};


int main(){
	binTree tree;
	int ch;
	while(true){
	cout << "MAIN MENU\n";
cout << "1. Insert new node\n";
cout << "2. Find number of nodes in longest path from root\n";
cout << "3. Minimum data value found in the tree\n";
cout << "4. Change a tree so that the roles of the left and right pointers are swapped at every node\n";
cout << "5. Search a value\n";
cout << "6. EXIT\n";

	cin>>ch;
	cin.ignore();
	if(ch==1){
		string val;
		cout<<"Enter the value:";
		getline(cin,val);
		tree.insert(val);
	}
	else if(ch==2){
		cout<<"Maximum length:"<<tree.height()<<endl;
	}
	else if(ch==3){
		cout<<"Minimum Value"<<tree.minValue()<<endl;
	}
	else if(ch==4){
		tree.swap();	
	}
	else if(ch==5){
		string value;
		cout<<"Enter value to search:";
		getline(cin,value);
		bool ans=tree.search(value);
		if(ans) cout<<"Value foun\n";
		else cout<<"Value not found\n";
	}
	else if(ch==6){
		break;
	}
	else {
		cout<<"Invalid Chooice\n";
	}
	cout<<"\nCURRENT TREE";
	tree.display();
	cout<<endl;
	}

}