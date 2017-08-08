//最小生成树 prim算法
#include <iostream>
#include <algorithm>
using namespace std;
//邻接表
#define max 128
//边集
struct edgenode{
	int adjvex;
	int weight;
	edgenode * next;
	edgenode(int a = 0, int w = 0, edgenode * n = NULL):adjvex(a), weight(w), next(n){}
};
//顶点
struct vertexnode{
	char data;
	edgenode * firstnode;
	vertexnode(char c = '0', edgenode *n = NULL):data(c), firstnode(n){}
};
//图
class adjGraph{
public:
	vertexnode VL[max];
	int vex_num, edge_num;
};
//邻接表的创建
void create_adjGraph(adjGraph & G){
	cin >> G.vex_num >> G.edge_num;
	for (int i = 0; i < G.vex_num; i++){
		char c;
		cin >> c;
		G.VL[i].data = c;
	}
	int j, k, w;
	for (int i = 0; i < G.edge_num; i++){
		cin >> j >> k >> w;
		edgenode * e1 = new edgenode(j, w, G.VL[k].firstnode);
		G.VL[k].firstnode = e1;
		edgenode * e2 = new edgenode(k, w, G.VL[j].firstnode);
		G.VL[j].firstnode = e2;
	}
}
//边的信息
struct edge
{
	int u, v;
	int weight;
	friend ostream & operator << (ostream & out, const edge & e){
		out << e.u << " -> " << e.v << " : " << e.weight << endl;
		return out;
	}
	edge(int a = 0, int b = 0, int c = 0):u(a), v(b), weight(c){}
};
//
void print(vector <edge *> &E1){
	for (int i = 0; i < E1.size(); i++) cout << (*E1[i]);
}
void MST_PRIM(adjGraph & G, vector <edge*> & E, int r){
	//辅助数组key,为0时表示已访问,key[i]表示可以出发的点通往i的最短距离，parent[i]表示对应的起点
	//初始化
	int key[G.vex_num], parent[G.vex_num];
	for (int i = 0; i < G.vex_num; i++) { key[i] = 65355; parent[i] = r; }
	key[r] = 0;
	edgenode * e = G.VL[r].firstnode;
	while(e){
		key[e->adjvex] = e->weight;
		e = e->next;
	}
	//
	for (int i = 1; i < G.vex_num; i++){
		//找最短
		int min = 65355; int k;
		for (int i = 0; i < G.vex_num; i++) 
			if (key[i] && key[i] < min) {
				min = key[i];
				k = i;
			}
		cout << parent[k] << " -> " << k << " : " << min << endl;
		key[k] = 0;
		//更新两个数组
		edgenode * e = G.VL[k].firstnode;
		while(e){
			if (key[e->adjvex] && e->weight < key[e->adjvex]){
				key[e->adjvex] = e->weight;
				parent[e->adjvex] = k;
			}
			e = e->next;
		}
	}
}
int main(int argc, char const *argv[])
{
	adjGraph G;
	create_adjGraph(G);
	vector <edge*> E;
	MST_PRIM(G, E, 0);
	return 0;
}