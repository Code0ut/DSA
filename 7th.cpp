/*You have a business with several offices; you want to lease phone lines to connect them up with each other; and the phone company charges different amounts of money to connect different pairs of cities. You want a set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting appropriate data structures.*/
#define MAX 1000
#include<iostream>
using namespace std;

class Edge{
	public:
	int u,v,cost;
	Edge(){};
	Edge(int u,int v, int cost){
		this->u=u;this->v=v;this->cost=cost;
	}
};


class DisjointSet{
	int* parent;
	int* rank;
 public:
	DisjointSet(int n){
		parent=new int[n];
		rank=new int[n];
		for(int i=0; i<n; i++){
			parent[i]=i;
			rank[i]=0;
		}
	}

	int ultimateParent(int node){
		if(parent[node]!=node){
			parent[node]=ultimateParent(parent[node]);
		}
		return parent[node];
	}
	
	bool unionSet(int u,int v){
		int pu=ultimateParent(u);
		int pv=ultimateParent(v);
		if(pu==pv) return false;
		if(rank[pu]<rank[pv])
			parent[pu]=pv;
		else if(rank[pv]<rank[pu])
			parent[pv]=parent[pu];
		else{
			parent[pv]=pu;
			rank[pu]++;
		}
		return true;
	}
	
	~DisjointSet(){
		delete[] parent;
		delete[] rank;
	}
};

class Graph{
	Edge edges[MAX];
	int V;
	int totalNodes;
 public:
	void createGraph(){
		cout << "Enter total number of nodes (offices): ";
        	cin >> totalNodes;
		cout<<"Enter total no. of edges in graph:";
		cin>>V;
		for(int i=0;i<V;i++){
			int startCity,endCity,cost;
			cout<<"Enter the start city of the edge:";
			cin>>startCity;
			cout<<"Enter the end city of the edge:";
			cin>>endCity;
			cout<<"Enter the cost of the path";
			cin>>cost;
			edges[i]=Edge(startCity,endCity,cost);
		}	
	}

	void findMinimumCost(){
		for (int i = 0; i < V - 1; ++i) {
    			for (int j = 0; j < V- i - 1; ++j) {
        			if (edges[j].cost > edges[j + 1].cost) {
            				Edge temp=edges[j];
					edges[j]=edges[j + 1];
					edges[j+1]=temp;
				}
        		}	
    		}
		
		DisjointSet ds(totalNodes);
		int totalCost=0;
		
		cout<<"Edges in MST:\n";
		for(int i = 0; i < V; i++){
			if(ds.unionSet(edges[i].u,edges[i].v)){
				cout<<edges[i].u<<" - "<<edges[i].v<<" : "<<edges[i].cost<<"\n";
				totalCost+=edges[i].cost;
			}
		}
		cout<<"Total minimum cost:"<<totalCost<<"\n";
	}
};

int main() {
    Graph g;
    g.createGraph();
    g.findMinimumCost();
    return 0;
}