#include <iostream>
#include <queue>
using namespace std;
//图的邻接表表示
#define max 100
//边表
class edgenode{
public:
	int adjvex;//存储下标
	edgenode * next;
	edgenode(int a = 0, edgenode * n = NULL):adjvex(a), next(n){}
};
//顶点
class vertexnode{
public:
	int data;
	edgenode * firstedge;
	vertexnode(int d = 0):data(d), firstedge(NULL){}
};
//
class adjGraph{
public:
	vertexnode VL[max];
	int vex_num, edge_num;
};
//建立邻接表
void create_adjGraph(adjGraph & G){
	//输入顶点数和边数
	cin >> G.vex_num >> G.edge_num;
	//建立顶点集
	int j, k;
	for (int i = 0; i < G.vex_num; i++){
		cin >> j;
		G.VL[i].data = j;
		G.VL[i].firstedge = NULL;
	}
	//建立边集
	for (int i = 0; i < G.edge_num; i++){
		cin >> j >> k;
		edgenode * n = new edgenode(k, G.VL[j].firstedge);
		G.VL[j].firstedge = n;
		edgenode * n1 = new edgenode(j, G.VL[k].firstedge);
		G.VL[k].firstedge = n1;
	}
}
void create_adjGraph1(adjGraph & G){
	G.vex_num = 8, G.edge_num = 10;
	//建立顶点集
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	for (int i = 0; i < G.vex_num; i++){
		G.VL[i].data = a[i];
		G.VL[i].firstedge = NULL;
	}
	//建立边集, 
	int b[] = {0, 2, 0, 1, 2, 2, 3, 3, 5, 6};
	int c[] = {1, 3, 4, 5, 5, 6, 6, 7, 6, 7};
	int j, k;
	for (int i = 0; i < G.edge_num; i++){
		j = b[i], k = c[i];
		edgenode * n = new edgenode(k, G.VL[j].firstedge);
		G.VL[j].firstedge = n;
		edgenode * n1 = new edgenode(j, G.VL[k].firstedge);
		G.VL[k].firstedge = n1;
	}
}
void create_adjGraph2(adjGraph & G){
	G.vex_num = 6, G.edge_num = 7;
	//建立顶点集
	int a[] = {1, 2, 3, 4, 5, 6};
	for (int i = 0; i < G.vex_num; i++){
		G.VL[i].data = a[i];
		G.VL[i].firstedge = NULL;
	}
	//建立边集, 
	int b[] = {0, 0, 3, 1, 2, 2, 4};
	int c[] = {1, 3, 1, 4, 4, 5, 3};
	int j, k;
	for (int i = 0; i < G.edge_num; i++){
		j = b[i], k = c[i];
		edgenode * n = new edgenode(k, G.VL[j].firstedge);
		G.VL[j].firstedge = n;
		/*edgenode * n1 = new edgenode(j, G.VL[k].firstedge);
		G.VL[k].firstedge = n1;*/
	}
}
enum COLOR {WHITE, GRAY, BLACK};
//广度优先搜索，得到广度优先树，s到v的路径即为边数最少路径，d[v]为最少边数
void BFS(adjGraph & G, int s, COLOR c[], int d[], int p[]){
	//初始化颜色全为白色,白色表示未访问，灰色表示访问一次，黑色表示所有邻接点全部被访问
	for (int i = 0; i < G.vex_num; i++) { c[i] = WHITE; p[i] = -1; }
	c[s] = GRAY;
	d[s] = 0;
	p[s] = s;
	queue<int> Q;
	Q.push(s);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		edgenode * e = G.VL[u].firstedge;
		while(e){
			if(c[e->adjvex] == WHITE){
				c[e->adjvex] = GRAY;
				d[e->adjvex] = d[u] + 1;
				p[e->adjvex] = u;
				Q.push(e->adjvex);
			}
			e = e->next;
		}
		c[u] = BLACK;
	}
}
//深度优先搜索，得到深度优先森林（不相交集合森林），并给出每个顶点的时间戳
void DFS_VISIT(adjGraph & G, COLOR c[], int d[], int f[], int p[], int s){
	static int t = 0;
	t++;
	d[s] = t;
	c[s] = GRAY;
	edgenode * e = G.VL[s].firstedge;
	while(e){
		if (c[e->adjvex] == WHITE){
			p[e->adjvex] = s;
			DFS_VISIT(G, c, d, f, p, e->adjvex);
		}
		e = e->next;
	}
	c[s] = BLACK;
	f[s] = ++t;
}
void DFS(adjGraph & G, COLOR c[], int d[], int f[], int p[]){
	//初始化
	for(int i = 0; i < G.vex_num; i++) {c[i] = WHITE; p[i] = -1; }
	for(int i = 0; i < G.vex_num; i++) 
		if (c[i] == WHITE)
			DFS_VISIT(G, c, d, f, p, i); 
}
template <class T>
void print(T array[], int n){
	for(int i = 0; i < n; i++) cout << array[i] << ' ';
	cout << endl;
}
void printG(adjGraph & G){
	for(int i = 0; i < G.vex_num; i++){
		edgenode * n = G.VL[i].firstedge;
		while(n){
			cout << n->adjvex << ' ';
			n = n->next;
		}
		cout << endl;
	}
}
int main(int argc, char const *argv[])
{
	adjGraph G;
	//create_adjGraph(G);
	create_adjGraph1(G);
	COLOR c[G.vex_num];
	int d[G.vex_num], p[G.vex_num];
	BFS(G, 1, c, d, p);
	print(c, G.vex_num);
	print(d, G.vex_num);
	print(p, G.vex_num);
	//
	adjGraph G1;
	create_adjGraph2(G1);
	COLOR c1[G1.vex_num];
	int d1[G1.vex_num], p1[G1.vex_num], f1[G1.vex_num];
	DFS(G1, c1, d1, f1, p1);
	print(c1, G1.vex_num);
	print(d1, G1.vex_num);
	print(f1, G1.vex_num);
	print(p1, G1.vex_num);
	return 0;
}