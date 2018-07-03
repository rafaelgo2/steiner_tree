#include <bits/stdc++.h>
using namespace std;

random_device rd;  
mt19937 gen(rd());
 
double rand_d(double l, double r){
	uniform_real_distribution<double> dis(0, 1);
	return dis(gen);
}

int rand_int(int l, int r, int ex = -1){
	if (l == r && l == ex){
		cerr << "err00: " << l << " " << r << " " << ex << endl;
		throw runtime_error("x_x");
	}
	uniform_int_distribution<int> dis(l, r);
	int it;
	while ((it = dis(gen)) == ex);
	return it;
}

int main(int argc, char *argv[]){
	ostream &out = cout;
	int v, c;
	double p;
	/*
	sz = v/c
	clusters vao ser {
		{0, ..., (v/c)},
		{v/c, ..., 2*(v/c) - 1},
		{sz*v/c, ..., v-1}		
	}
	*/
	cin >> v >> c >> p;
	int sz = v/c;
	int left = v%c;
	vector<vector<int>> m(v, vector<int>(v, 0));
	vector<int> clus(v);
	for (int i = 0; i < v - left; i++)
		clus[i] = i/sz;
	for (int i = 0; i < left; i++){
		clus[v-left+i] = i;
	}
	sort(clus.begin(), clus.end());
	int count_m = 0;
	for (int i = 0; i < v; i++){
		for (int j = i+1; j < v; j++){
			double d = rand_d(0, 1);
			if ((clus[i] == clus[j]) && (d <= p)){
				m[i][j] = m[j][i] = 1;
				count_m++;
			}
		}
	}

	out << "Adj Matrix" << endl;
	for (int i = 0; i < v; i++)
		m[i][i] = 1;
	for (int i = 0; i < v; i++){
		for (int j = 0; j < v; j++){
			out << m[i][j] << " ";
		}
		out << endl;
	}
	out << endl;
	out << "List of edges" << endl;
	out << v << " " << count_m << endl; 
	for (int i = 0; i < v; i++)
		for (int j = i+1; j < v; j++)
			if (m[i][j]) out << i << " " << j << " " << 1 << endl;

	out  << "Randon2:" << endl
		 << '\t' << v << endl
		 << '\t' << c << endl
		 << '\t' << p << endl;
	return 0;
}

