//利用深度搜索求有向图各强连通分支
/*
1.对图G,若存在边（u,v）,且u在连通分支C1,v在连通分支C2中，则有f(C1) > f(C2)
2.由1，有对图G的转置GT,若存在边（u,v）,且u在连通分支C1,v在连通分支C2中，则有f(C1) < f(C2)
因此，先深度搜索求G的完成时间，再对GT按完成时间从大到小进行深度搜索----->由2推出得到的即为各强连通分支
*/
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
	G.vex_num = 8, G.edge_num = 13;
	//建立顶点集
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	for (int i = 0; i < G.vex_num; i++){
		G.VL[i].data = a[i];
		G.VL[i].firstedge = NULL;
	}
	//建立边集
	int b[] = {0, 1, 2, 3, 4, 1, 1, 2, 3, 4, 5, 6, 6};
	int c[] = {1, 2, 3, 2, 0, 4, 5, 6, 7, 5, 6, 5, 7};
	int j, k;
	for (int i = 0; i < G.edge_num; i++){
		j = b[i], k = c[i];
		edgenode * n = new edgenode(k, G.VL[j].firstedge);
		G.VL[j].firstedge = n;
		/*edgenode * n1 = new edgenode(j, G.VL[k].firstedge);
		G.VL[k].firstedge = n1;*/
	}
}
//根据G建立GT
void create_adjGraphT(adjGraph & G, adjGraph & GT){
	GT.vex_num = G.vex_num;
	GT.edge_num = G.edge_num;
	for(int i = 0; i < GT.vex_num; i++) {
		GT.VL[i].data = G.VL[i].data;
		edgenode * e = G.VL[i].firstedge;
		while(e){
			int u = e->adjvex;
			edgenode * n = new edgenode(i, GT.VL[u].firstedge);
			GT.VL[u].firstedge = n;
			e = e->next;
		}
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
void DFS(adjGraph & G, COLOR c[], int d[], int f[], int p[], int index[]){
	for(int i = 0; i < G.vex_num; i++){
		c[i] = WHITE;
		p[i] = -1;
	}
	for(int i = 0; i < G.vex_num; i++){
		if (c[index[i]] == WHITE) DFS_VISIT(G, c, d, f, p, index[i]);
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

template <class T>
void print(T array[], int n){
	for(int i = 0; i < n; i++) cout << array[i] << ' ';
	cout << endl;
}

void printi(int p[], bool c1[], adjGraph & G, int i){
	if (p[i] == -1) { cout << G.VL[i].data << ' '; c1[i] = 1; }
	else if(c1[i] == 0) {
		c1[i] = 1;
		printi(p, c1, G, p[i]);
		cout << "-> " << G.VL[i].data << ' ';
	}
}
void printSCC(int p[], adjGraph &G){
	cout << "各连通分支如下：" << endl;
	bool c1[G.vex_num] = {0};
	for(int i = 0; i < G.vex_num; i++){
		if (p[i] != -1 && c1[i] == 0) { printi(p, c1, G, i); cout << endl; }
		
	}
	for (int i = 0; i < G.vex_num; i++)
		if (c1[i] == 0) cout << G.VL[i].data << endl;
}
int main(){
	adjGraph G, GT;
	create_adjGraph2(G);
	create_adjGraphT(G, GT);
	//深度遍历G,求得完成时间
	COLOR c[G.vex_num];
	int d[G.vex_num], f[G.vex_num], p[G.vex_num];
	int index[G.vex_num];
	for(int i = 0; i < G.vex_num; i++) index[i] = i;
	DFS(G, c, d, f, p, index);
	print(c, G.vex_num);
	print(d, G.vex_num);
	print(f, G.vex_num);
	print(p, G.vex_num);
	//排序完成时间
	quick_sort(f, 0, G.vex_num - 1, index);
	//深度遍历GT,得到各强连通子图
	DFS(GT, c, d, f, p, index);
	print(c, G.vex_num);
	print(d, G.vex_num);
	print(f, G.vex_num);
	print(p, G.vex_num);
	
	//输出各子图成员
	printSCC(p, G);
}