#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void prims(vector<vector<int>> graph) {
	//gets size of graph
	int v = graph.size();

	//stores the parent of vertex
	vector<int> parent(v);

	//hold the weight/cost of the tree
	vector<int> key(v);
	
	//vector represents the set of vertices in the tree by if they have been visited or not
	vector<bool> vists(v);
	
	//sets up the queue for the graph
	std::priority_queue<std::pair<int, int>,
		std::vector<std::pair<int, int>>,
		std::greater<std::pair<int, int>>> pq;


	//sets the weight to max for everything and sets all visits to false
	for (int i = 0; i < v; i++) {
		key[i] = INT_MAX;
		vists[i] = false;
	}

	key[0] = 0;
	parent[0] = -1;

	pq.push({ 0,0 });

	//while there are still things in queue it compares the weight of adjacent vertices and takes the lighter weight
	while (!pq.empty()) {
		int node = pq.top().second;
		pq.pop();
		vists[node] = true;
		for (int i = 0; i < v; i++) {
			if (!vists[i] && graph[node][i] != 0 && graph[node][i] < key[i]) {
				pq.push({ graph[node][i], i });
				key[i] = graph[node][i];
				parent[i] = node;
			}
		}
	}

//prints the edges used and their weights as well as the final total
	cout << "Edge \tWeight\n";
	int count = 0;
	int weight = 0;
	for (int i = 1; i < v; i++) {
		cout << parent[i] << " - " << i
		<< " \t" << graph[i][parent[i]] << " \n";
		++count;
		weight = weight + graph[i][parent[i]];
	}
	cout << " \n";
	cout << "Total edges used: " << count << " \n";
	cout << "Total weight: " << weight << " \n";

}

int main() {
	string filename("TextFile.txt");
	int vertices;
	int edges;

	ifstream input_file(filename);

	input_file >> vertices;
	input_file >> edges;

	vector<vector<int>> graph;
	graph = vector<vector<int>>(vertices, vector<int>(vertices, 0));

	for (int i = 0; i < edges; i++) {
		int adj1;
		int adj2;
		int w;

		input_file >> adj1;
		input_file >> adj2;
		input_file >> w;

		graph[adj1][adj2] = w;
		graph[adj2][adj1] = w;
	}

	input_file.close();

	prims(graph);

	return 1;
}
