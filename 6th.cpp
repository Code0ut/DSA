/*There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey. Represent this as a graph. The node can be represented by airport name or name of the city. Use adjacency list representation of the graph or use adjacency matrix representation of the graph. Check
whether the graph is connected or not. Justify the storage representation used.*/

#include<iostream>
#include<cstring>
using namespace std;

const int MAX=50;

struct Node{
	char name[40];
	char connected[MAX][40];
	int cost[MAX];
	int nC;
	 Node() {
        strcpy(name, "");
        nC = 0;
    }

    void inputConnections() {
        cout << "Enter number of connections for " << name << ": ";
        cin >> nC;
        for (int i = 0; i < nC; i++) {
            cout << "Enter name of city connected to " << name << ": ";
            cin >> connected[i];
            cout << "Enter cost of travel to " << connected[i] << ": ";
            cin >> cost[i];
        }
    }
};

class Graph{
	Node list[MAX];
	int visited[MAX];
	int countCities;
 public:
	Graph(){
		countCities=0;
		for(int i=0;i<MAX;i++) visited[i]=0;
	}	
		
	void createGraph(){
		cout<<"Enter no of cities in Graph:";
		cin>>countCities;
		
		for(int i=0;i<countCities;i++){
			cout<<"Enter "<<i+1<<" city in graph:";
			cin>>list[i].name;	
		}
		for(int i=0;i<countCities;i++){
			list[i].inputConnections();
		}
	}
		
	int getCityIndex(char city[]){
		for(int i=0;i<countCities;i++){
			if(strcmp(list[i].name,city)==0){
				return i;
			}
		}
		return -1;
	}
	
	void DFS(int index){
		visited[index]=1;
		for(int i=0;i<list[index].nC;i++){
			int nextIndex=getCityIndex(list[index].connected[i]);
			if(nextIndex != -1 && visited[nextIndex]==0){
				DFS(nextIndex);
			}
		}
	}

	bool isConnected(){
		for(int i=0;i<countCities;i++){
			visited[i]=0;
		}
		DFS(0);
		for(int i=0;i<countCities;i++){
			if(visited[i]==0) return false;
		}
		return true;
	}

	void display(){
		cout<<"\nAdjency List Representation:\n";
		for(int i=0;i<countCities;i++){
			cout<<list[i].name<<"->";
			for(int j=0;j<list[i].nC;j++){
				cout<<list[i].connected[j]<<"("<<list[i].cost[j]<<"), ";
			}
			cout<<endl;
		}
	}
};

int main(){
	Graph g;
	int ch;
	while(true){
		cout<<"MAIN MENU\n1.Create graph\n.2.Check Connectivity\n3.Display Graph\n4.EXIT\n";
		cin>>ch;
		if(ch==1){
			g.createGraph();
		}
		else if(ch==2){
			if(g.isConnected()) cout<<"Graph is Connected.\n";
			else cout<<"Graph is not Connected.\n";
		}
		else if(ch==3) g.display();
		else if(ch==4) break;
		else cout<<"Invalid Choice";
	}
	return 0;
}