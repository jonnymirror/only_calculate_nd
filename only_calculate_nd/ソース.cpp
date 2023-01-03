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

//�萔�J�n.
vector<vector<long long int>> G;//���͂����O���t.
long long int n;//���_��.
long long int m;//�}��.
vector<long long int> Place_of_vertices;//���_i��������^�C�v�p�[�e�B�V������\���z��,Place_of_vertices[i]=-1�̎��͂��̒��_�͂܂��ǂ̃^�C�v�p�[�e�B�V�����ɂ������Ă��Ȃ����Ƃ�\��,Place_of_vertices[i]=j�̎��͒��_i���^�C�v�p�[�e�B�V����j�ɑ����Ă��邱�Ƃ�\��.
vector<vector<long long int>> Type_partitions;//�^�C�v�p�[�e�B�V����.
long long int nd = -1;//�O���t�̋ߖT���l���̒l���i�[����ϐ�.
//�萔�I��.

//2�̒��_u,v�̋ߖT���r����֐�(�O���t�̗אڃ��X�g���l�̏���������sort���Ă���O��őO�����r���Ă���).
bool check_neighbor(long long int u, long long int v) {
	//cout << "check_neighbor�J�n" << endl;
	//cout << "u:" << u << "  v:" << v << endl;
	//�O���t�̗אڃ��X�g�m�F.
	/*
	for (long long int i = 0; i < G.size(); i++) {
		for (long long int j = 0; j < G[i].size(); j++) {
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
	*/
	vector<long long int> U_neighbourhood;//u�̋ߖT(v�͎�菜��).
	vector<long long int> V_neighbourhood;//v�̋ߖT(u�͎�菜��).
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
	//cout << "check_neighbor�I��" << endl;
	return true;
}

//�ߖT���l�����v�Z����(�i�C�[�u)
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

//���C���֐�.
int main() {
	//���͊J�n.
	ifstream ifs1("Infectious.txt");

	if (!ifs1) {
		std::cout << "Errer!";
		return 1;
	}

	string s;
	long long int count = 0;
	long long int x = 0;
	long long int y = 0;

	while (getline(ifs1, s, ' ')) {     // �X�y�[�X�i' '�j�ŋ�؂��āC�i�[
		if (count == 0) {//���_��
			n = stoll(s);
			G.resize(n); //�O���t�̑傫���m��
			count++;
		}
		else if (count == 1) {//�}��
			m = stoll(s);
			count++;
		}
		else if (count > 1 && count % 2 == 0) {//�O���t�̎}�̒[�_
			x = stoll(s);
			x--;
			count++;
		}
		else if (count > 1 && count % 2 == 1) {//�O���t�̎}�̂�����̒[�_
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
	//���͏I��.

	//���͐����J�n.
	for (int i = 0; i < n; i++) {
		sort(G[i].begin(), G[i].end());//�O���t�̗אڃ��X�g��l�����������ɕ��ׂ�(�ߖT���l���������Ă��邩�ǂ����̊m�F�����鎞�̂��߂�).
	}
	//���͐����I��.
	//���͊m�F�J�n.
	/*
	for (long long int i = 0; i < G.size(); i++) {
		for (long long int j = 0; j < G[i].size(); j++) {
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
	cout << "���_��:" << n << endl;
	cout << "�}��:" << m << endl;
	cout << "k:" << k << endl;
	cout << "l:" << l << endl;
	long long int edge_number = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < G[i].size(); j++) {
			cout << "�}" << edge_number + 1 << "�{��:" << i << " " << G[i][j] << endl;
			edge_number++;
		}
	}
	*/
	clock_t start = clock();    // �J�n����

	making_Type_partitions();

	clock_t end = clock();//�I������

	cout<<"��������:"<< (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";

	cout << "nd: " << nd << endl;

	return 0;
}