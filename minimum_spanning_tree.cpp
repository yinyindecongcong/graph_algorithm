//最小生成树 kruskal算法
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
		/*edgenode * e2 = new edgenode(k, w, G.VL[j].firstnode);
		G.VL[j].firstnode = e2;*/
	}
}
//不相交集合森林
class DSF{
	int rank[max];//sort by rank,高度
	int parent[max];//存放元素index的父节点
public:
	DSF(){ for (int i = 0; i < max; i++) rank[i] = -1; }
	void MAKE_SET(int v){ parent[v] = v; rank[v] = 0; }
	int FIND_SET(int v){
		if (parent[v] == v) return v;
		return FIND_SET(parent[v]);
	}
	void UNION(int a, int b){
		int pa = FIND_SET(a), pb = FIND_SET(b);
		if (pa == pb) return;
		if (rank[pa] < rank[pb]) parent[pa] = pb;
		else parent[pb] = pa; 
		if (rank[pa] == rank[pb]) rank[pa]++;
	}
};
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
//根据权值对边排序
bool compare(edge & e1, edge & e2){
	return e1.weight < e2.weight;
}
//从图获取边的组合
void get_E(adjGraph & G, edge E[], int count){
	for (int i = 0; i < G.vex_num; i++){
		edgenode * e = G.VL[i].firstnode;
		while(e){
			E[count++] = edge(i, e->adjvex, e->weight);
			e = e->next;
		}
	}
}
//
void print(vector <edge *> &E1){
	for (int i = 0; i < E1.size(); i++) cout << (*E1[i]);
}
int main(){
	adjGraph G;
	create_adjGraph(G);
	edge E[G.edge_num];
	int count = 0;
	vector <edge * > E1;
	get_E(G, E, count);
	sort(E, E + G.edge_num, compare);
	DSF F;
	for (int i = 0; i < G.vex_num; i++) F.MAKE_SET(i);
	for (int i = 0; i < G.edge_num; i++) 
		if(F.FIND_SET(E[i].u) != F.FIND_SET(E[i].v)){
			E1.push_back(new edge(E[i].u, E[i].v, E[i].weight));
			F.UNION(E[i].u, E[i].v);
		}
	print(E1);
}