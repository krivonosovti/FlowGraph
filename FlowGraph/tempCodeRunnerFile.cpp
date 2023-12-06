#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int V = 5;


struct Vertex
{
	int Num;
	int MerIn;
	int MerOut;
	int dif;
	float y;
};
bool comp (Vertex a, Vertex b) {
  return a.dif > b.dif;
}


// To add an edge
void addEdge(vector <pair<int, int > > adj[], int u,
									int v, int wt)
{
	adj[u].push_back(make_pair(v, wt));
	//adj[v].push_back(make_pair(u, wt));
}

// // Print adjacency list representation of graph
void printGraph(vector<pair<int,int> > adj[], int V)
{
	for (int u = 0; u < V; u++)
	{
		cout << "Node " << u << " makes an edge with \n";
		for (int i = 0; i<adj[u].size(); i++)
		{
			cout << "\tNode " << adj[u][i].first << " with edge weight ="
				<< adj[u][i].second<< "\n";
		}
		cout << "\n";
	}
}

Vertex calculate(int numVertex,vector<pair<int, int> > adj[])  // считаю дисбаланс и множитель y 
{

    int MerIn = 0,MerOut = 0;
   	for (int j = 0; j < adj[numVertex].size(); j++){
    MerOut += adj[numVertex][j].second;
	}

    for (int i = 0; i<V;i++ )
    {
        if(i == numVertex)
            continue;
		for (int j = 0; j < adj[numVertex].size(); j++){
			if (adj[i][j].first == numVertex)
			MerIn += adj[i][j].second;
		}
    }
	// if (MerIn == 0)
	// 	return 0.0;
	// Для удобства загрузим все в струтурку вершин
	Vertex res;
	res.Num = numVertex;
	res.MerIn = MerIn;
	res.MerOut = MerOut;
	res.dif = abs(MerOut - MerIn);
	res.y = sqrt(float(MerOut)/(float(MerIn)));
	return res;
}

void print_vector( vector<Vertex> V)
{
	int size = V.size();
	for (int i = 0; i<size; i++)
	{
		cout << V[i].dif << " ";
	}
	cout << endl;
}


// Driver code
int main()
{
	vector<pair<int, int> > adj[V]; //создаем исходный связный и взв 9ешанный граф
	addEdge(adj, 0, 1, 10);
	addEdge(adj, 0, 4, 20);
	addEdge(adj, 1, 2, 30);
	addEdge(adj, 1, 3, 40);
	addEdge(adj, 1, 4, 50);
	addEdge(adj, 2, 3, 60);
	addEdge(adj, 3, 4, 70);
	addEdge(adj, 3, 0, 30);
	addEdge(adj, 4, 1, 30);
	printGraph(adj, V);

	vector<Vertex> Metric;
	for (int i = 0; i< V; i++){
    	Metric.push_back(calculate(i,adj));  //сортируем очередь по дисбалансу
	}
	sort(Metric.begin(),Metric.end(),comp);

	cout<< " Дисбаланс вершин по убыванию: ";
	print_vector(Metric);
	cout << endl;

	for(int i =0; i<V; i++)  //строим стационарное распределение
	{
		float y = Metric[i].y;
		if (y==0) {
		;
		}
		int n = Metric[i].Num;
		for (int j = 0; j < adj[n].size(); j++)
		{
			adj[n][j].second /= y;  //делим все исходящие меры 
		}

		for (int k = 0; k<V;k++)
		{
			if  (n == 4){;}
			if(k == n)
				continue;
			for (int j = 0; j < adj[k].size(); j++)
			{
				if (adj[k][j].first == n)
					adj[k][j].second *= y; // умножаем все входящие меры
			}
		}
	}

	printGraph(adj, V); //выводим стац граф

	return 0;
}