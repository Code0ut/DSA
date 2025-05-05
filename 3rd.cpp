/*A book consists of chapters, chapters consists of sections and sections consist of
subsections. Construct a tree and print the nodes. Find the time and space requirements of
your method.*/

#include<iostream>
#include<string>
using namespace std;
class Node{
public:
	string name;
	Node* child;
	Node* sibling;
	Node(string name){
		this->name=name;
		child=nullptr;
		sibling=nullptr;
	}
};
void addChild(Node* parent,Node* nchild){
	if(parent->child==nullptr){
		parent->child=nchild;
	}
	else{
		Node* temp= parent->child;
		while(temp->sibling != nullptr){
			temp=temp->sibling;
		}
		temp->sibling=nchild;
	}
}

void printTree(Node* root,int level=0){
	if(root==nullptr) return;
	for(int i=0;i<level;i++){
		cout<<" ";
	}
	cout<<root->name<<endl;
	printTree(root->child,level+1);
	printTree(root->sibling,level);
}

int main(){
	string bookN;
	cout<<"Enter the name of the book:";
	getline(cin,bookN);
	Node* book=new Node(bookN);
	
	int nChaps;
	cout<<"Enter no. of chapters";
	cin>>nChaps;
	cin.ignore();
	cout<<endl;

	for(int i=0;i<nChaps;i++)
	{
		string cName;
		cout<<"Enter name of chapter"<<i+1<<":";
		getline(cin,cName);
		cout<<endl;
		Node* chapter=new Node(cName);
		addChild(book,chapter);

		int nSec;
		cout<<"Enter no. of sections";
		cin>>nSec;
		cin.ignore();
		cout<<endl;
		
		for(int j=0;j<nSec;j++)
		{
			string secName;
			cout<<"Enter name of section"<<j+1<<":";
			getline(cin,secName);
			cout<<endl;
			Node* section=new Node(secName);
			addChild(chapter,section);
			
			int nSubSec;
			cout<<"Enter no. of subsections";
			cin>>nSubSec;
			cin.ignore();
			cout<<endl;
		
			for(int k=0;k<nSubSec;k++)
			{
				string subsecName;
				cout<<"Enter name of subsection"<<k+1<<":";jhrfble

				getline(cin,subsecName);
				cout<<endl;
				Node* subsection=new Node(subsecName);
				addChild(section,subsection);
			}
		}

	}
	cout<<"Book Structure:\n";
	printTree(book);

}