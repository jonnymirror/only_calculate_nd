#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <intrin.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>  

using namespace std;

//定数開始.
vector<vector<long long int>> G;//入力されるグラフ.
long long int n;//頂点数.
long long int m;//枝数.
vector<long long int> Place_of_vertices;//頂点iが属するタイプパーティションを表す配列,Place_of_vertices[i]=-1の時はその頂点はまだどのタイプパーティションにも属していないことを表す,Place_of_vertices[i]=jの時は頂点iがタイプパーティションjに属していることを表す.
vector<vector<long long int>> Type_partitions;//タイプパーティション.
long long int nd = -1;//グラフの近傍多様性の値を格納する変数.
//定数終了.

//2つの頂点u,vの近傍を比較する関数(グラフの隣接リストが値の小さい順にsortしている前提で前から比較していく).
bool check_neighbor(long long int u, long long int v) {
	//cout << "check_neighbor開始" << endl;
	//cout << "u:" << u << "  v:" << v << endl;
	//グラフの隣接リスト確認.
	/*
	for (long long int i = 0; i < G.size(); i++) {
		for (long long int j = 0; j < G[i].size(); j++) {
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
	*/
	vector<long long int> U_neighbourhood;//uの近傍(vは取り除く).
	vector<long long int> V_neighbourhood;//vの近傍(uは取り除く).
	for (long long int i = 0; i < G[u].size(); i++) {
		if (G[u][i] != v)U_neighbourhood.push_back(G[u][i]);
	}
	for (long long int i = 0; i < G[v].size(); i++) {
		if (G[v][i] != u)V_neighbourhood.push_back(G[v][i]);
	}
	/*
	cout << "U_neighbourhood" << endl;
	for (long long int i = 0; i < U_neighbourhood.size(); i++) {
		cout << U_neighbourhood[i] << " ";
	}
	cout << endl;
	cout << "V_neighbourhood" << endl;
	for (long long int i = 0; i < U_neighbourhood.size(); i++) {
		cout << V_neighbourhood[i] << " ";
	}
	cout << endl;
	*/
	if (U_neighbourhood.size() != V_neighbourhood.size())return false;
	for (long long int i = 0; i < U_neighbourhood.size(); i++) {
		if (U_neighbourhood[i] != V_neighbourhood[i])return false;
	}
	//cout << "check_neighbor終了" << endl;
	return true;
}

//近傍多様性を計算する(ナイーブ)
void making_Type_partitions() {
	long long int count = 0;
	for (long long int i = 0; i < n; i++) {
		for (long long int j = i; j < n; j++) {
			if (check_neighbor(i, j)) {
				if (Place_of_vertices[i] == -1) {
					Place_of_vertices[i] = count;
					count++;
				}
				Place_of_vertices[j] = Place_of_vertices[i];
			}
		}
	}
	nd = count;
	Type_partitions.resize(count);
	for (long long int i = 0; i < n; i++) {
		Type_partitions[Place_of_vertices[i]].push_back(i);
	}
}

//メイン関数.
int main() {
	//入力開始.
	ifstream ifs1("Infectious.txt");

	if (!ifs1) {
		std::cout << "Errer!";
		return 1;
	}

	string s;
	long long int count = 0;
	long long int x = 0;
	long long int y = 0;

	while (getline(ifs1, s, ' ')) {     // スペース（' '）で区切って，格納
		if (count == 0) {//頂点数
			n = stoll(s);
			G.resize(n); //グラフの大きさ確保
			count++;
		}
		else if (count == 1) {//枝数
			m = stoll(s);
			count++;
		}
		else if (count > 1 && count % 2 == 0) {//グラフの枝の端点
			x = stoll(s);
			x--;
			count++;
		}
		else if (count > 1 && count % 2 == 1) {//グラフの枝のもう一つの端点
			y = stoll(s);
			y--;
			count++;
			G[x].push_back(y);
			G[y].push_back(x);
		}
	}

	ifs1.close();

	for (int i = 0; i < n; i++) {
		Place_of_vertices.push_back(-1);
	}
	//入力終了.

	//入力整理開始.
	for (int i = 0; i < n; i++) {
		sort(G[i].begin(), G[i].end());//グラフの隣接リストを値が小さい順に並べる(近傍多様性が合っているかどうかの確認をする時のために).
	}
	//入力整理終了.
	//入力確認開始.
	/*
	for (long long int i = 0; i < G.size(); i++) {
		for (long long int j = 0; j < G[i].size(); j++) {
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
	cout << "頂点数:" << n << endl;
	cout << "枝数:" << m << endl;
	cout << "k:" << k << endl;
	cout << "l:" << l << endl;
	long long int edge_number = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < G[i].size(); j++) {
			cout << "枝" << edge_number + 1 << "本目:" << i << " " << G[i][j] << endl;
			edge_number++;
		}
	}
	*/
	clock_t start = clock();    // 開始時間

	making_Type_partitions();

	clock_t end = clock();//終了時間

	cout<<"処理時間:"<< (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";

	cout << "nd: " << nd << endl;

	return 0;
}