#include<bits/stdc++.h>
using namespace::std;

const int E = 2;
const int SUML = 2 * 30 + 10;

int nodes;
string a, b;
int suf[SUML];
int posi[SUML];
bool pat[SUML];
int go[E][SUML];
vector<int> terms;
vector<int> states;
long double I[SUML][SUML];
long double R[SUML][SUML];
long double Q[SUML][SUML];

void add_node(){
	for(int i = 0; i < E; i++) go[i][nodes] = 0;
	pat[nodes] = false;
	nodes++;
}

void insert(string &s){
	int pos = 0;
	for(int i = 0; i < s.size(); i++){
		int c = s[i] - '0';
		if(go[c][pos] == 0){
			go[c][pos] = nodes;
			add_node();
		}
		pos = go[c][pos];
	}
	pat[pos] = true;
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		for(int c = 0; c < E; c++){
			if(go[c][u]){
				int v = go[c][u];
				Q.emplace(v);
				suf[v] = u == 0 ? 0 : go[c][suf[u]];
			}
			else go[c][u] = u == 0 ? 0 : go[c][suf[u]];
		}
	}
}

void build_matrix(){
	terms.clear();
	states.clear();
	for(int i = 0; i < nodes; i++){
		if(pat[i]) terms.emplace_back(i);
		else states.emplace_back(i);
	}
	for(int i = 0; i < terms.size(); i++){
		posi[terms[i]] = i;
	}
	for(int i = 0; i < states.size(); i++){
		posi[states[i]] = i;
		for(int j = 0; j < states.size(); j++){
			Q[i][j] = 0;
		}
	}
	for(int i = 0; i < states.size(); i++){
		for(int c = 0; c < E; c++){
			int j = posi[go[c][states[i]]];
			if(pat[go[c][states[i]]]) R[i][j] += 0.5;
			else Q[i][j] += 0.5;
		}
	}
}

void print(){
	int n = states.size();
	cout << "Q:" << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << Q[i][j] << " ";
		}
		cout << endl;
	}
	cout << "I:" << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << I[i][j] << " ";
		}
		cout << endl;
	}
}

void get_inverse(){
	int n = states.size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			I[i][j] = i == j;
			Q[i][j] = (i == j) - Q[i][j];
		}
	}
	for(int i = 0; i < n; i++){
		int best = -1;
		for(int j = i; j < n; j++){
			if(fabs(Q[i][j]) < 1e-9) continue;
			if(best == -1 or fabs(Q[best][i]) < fabs(Q[j][i])) best = j;
		}
		assert(~best);
		if(best ^ i){
			for(int j = 0; j < n; j++){
				swap(Q[best][j], Q[i][j]);
				swap(I[best][j], I[i][j]);
			}
		}
		long double coef = 1 / Q[i][i];
		for(int j = 0; j < n; j++){
			Q[i][j] *= coef;
			I[i][j] *= coef;
		}
		for(int j = i + 1; j < n; j++){
			long double coef = Q[j][i] / Q[i][i];
			for(int k = 0; k < n; k++){
				Q[j][k] -= coef * Q[i][k];
				I[j][k] -= coef * I[i][k];
			}
		}
	}
	for(int i = n - 1; i >= 0; i--){
		for(int j = i - 1; j >= 0; j--){
			long double coef = Q[j][i] / Q[i][i];
			for(int k = 0; k < n; k++){
				Q[j][k] -= coef * Q[i][k];
				I[j][k] -= coef * I[i][k];
			}
		}
	}
}

long double solve(){
	get_inverse();
	int n = states.size();
	long double ans = 0;
	for(int i = 0; i < n; i++){
		ans += I[0][i] * R[i][0];
	}
	return ans;
}

void clear(){
	for(int i = 0; i < nodes; i++){
		for(int j = 0; j < nodes; j++){
			Q[i][j] = I[i][j] = R[i][j] = 0;
		}
	}
}

int main(){
	while(cin >> a >> b){
		if(a == "0" and b == "0") break;
		nodes = 0;
		add_node();
		insert(a);
		insert(b);
		BFS(0);
		build_matrix();
		cout << setprecision(3) << fixed << solve() << '\n';
		clear();
	}
	return 0;
}
