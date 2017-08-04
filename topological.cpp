//拓扑排序--根据深度遍历得出的完成时间从大到小输出即可
#include <iostream>
using namespace std;
#define max 100
//边集
class edgenode{
public:
	int adjvex;
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
//图
class adjGraph{
public:
	vertexnode VL[max];
	int vex_num, edge_num;
};
//建立书中深度遍历的有向图
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
//进行深度遍历得到完成时间
enum COLOR {WHITE, GRAY, BLACK};
void DFS_VISIT(adjGraph & G, COLOR c[], int d[], int f[], int p[], int s){
	static int t = 0;
	d[s] = ++t;
	c[s] = GRAY;
	edgenode * e = G.VL[s].firstedge;
	while(e){
		if (c[e->adjvex] == WHITE) {
			p[e->adjvex] = s;
			DFS_VISIT(G, c, d, f, p, e->adjvex);
		}
		e = e->next;
	}
	f[s] = ++t;
	c[s] = BLACK;
}
void DFS(adjGraph & G, COLOR c[], int d[], int f[], int p[]){
	for(int i = 0; i < G.vex_num; i++){
		c[i] = WHITE;
		p[i] = -1;
	}
	for(int i = 0; i < G.vex_num; i++){
		if (c[i] == WHITE) DFS_VISIT(G, c, d, f, p, i);
	}
}
//快排完成时间
int partition(int f[], int s, int n, int index[]){
	int key = f[n], p = s - 1;
	for(int i = s; i < n; i++)
		if(f[i] > key){
			p++;
			int temp = f[i];
			f[i] = f[p];
			f[p] = temp;
			temp = index[i];
			index[i] = index[p];
			index[p] = temp;
		}
	p++;
	f[n] = f[p];
	f[p] = key;
	int temp = index[n];
	index[n] = index[p];
	index[p] = temp;
	return p;
}
void quick_sort(int f[], int s, int n, int index[]){
	if (s >= n) return;
	int q = partition(f, s, n, index);
	quick_sort(f, s, q - 1, index);
	quick_sort(f, q + 1, n, index);
}
int main(){
	adjGraph G;
	create_adjGraph2(G);
	COLOR c[G.vex_num];
	int d[G.vex_num], f[G.vex_num], p[G.vex_num];
	DFS(G, c, d, f, p);
	for(int i = 0; i < G.vex_num; i++) cout << f[i] << ' ';
	cout << endl;
	int index[] = {0, 1, 2, 3, 4, 5};
	quick_sort(f, 0, 5, index);
	for(int i = 0; i < G.vex_num; i++) cout << f[i] << ' ';
	cout << endl;
	for(int i = 0; i < G.vex_num; i++) cout << G.VL[index[i]].data << ' ';
	cout << endl;
}