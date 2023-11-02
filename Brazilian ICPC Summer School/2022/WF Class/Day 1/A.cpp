#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;
const int B[] = {311, 257};
const int L = 1;
const int MOD = 1000000000 + 7;

int add(int a, int b){
	return (a + b) % MOD;
}

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int pow_mod(int a, int b){
	int r = 1;
	while(b){
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int pot[2][N];
int poti[2][N];

int a;
int b;
int c;
int d;
char pat[N][N];
char text[N][N];
vector<int> p[N];
vector<int> v[N][N];

void init(){
	for(int id = 0; id < L; id++){
		pot[id][0] = 1;
		for(int i = 1; i < N; i++) pot[id][i] = (1ll * B[id] * pot[id][i - 1]) % MOD;
		// Primo p, entero a tal que gcd(a, p) = 1
		// a^(p - 1) = a^0 mod p
		// a^(p - 2) = a^(-1) mod p
		poti[id][N - 1] = pow_mod(pot[id][N - 1], MOD - 2);
		for(int i = N - 2; i >= 0; i--) poti[id][i] = (1ll * B[id] * poti[id][i + 1]) % MOD;
	}
}

void build_matrix(){
	for(int i = 0; i < a; i++){
		vector<int> cur_hash(L, 0);
		for(int j = 0; j < b; j++){
			int c = pat[i][j] == 'x';
			for(int id = 0; id < L; id++){
				cur_hash[id] = add(cur_hash[id], mul(c, pot[id][j]));
			}
		}
		p[i] = cur_hash;
	}
	for(int i = 0; i < c; i++){
		// Independiente
		vector<int> cur_hash(L, 0);
		for(int j = 0; j + 1 < b; j++){
			int c = text[i][j] == 'x';
			for(int id = 0; id < L; id++){
				cur_hash[id] = add(cur_hash[id], mul(c, pot[id][j]));
			}
		}
		for(int j = b - 1; j < d; j++){
			// a_0 * B^0 + a_1 * B^1 + ... + a_(b - 1) * B^(b - 1)
			// (a_1 * B^1 + ... + a_b * B^b) * B^(-1)
			int c = text[i][j] == 'x';
			for(int id = 0; id < L; id++){
				cur_hash[id] = add(cur_hash[id], mul(c, pot[id][j]));
			}
			if(j - b >= 0){
				int c = text[i][j - b] == 'x';
				for(int id = 0; id < L; id++){
					cur_hash[id] = add(cur_hash[id], MOD - mul(c, pot[id][j - b]));
				}
			}
			v[i][j - b + 1] = cur_hash;
			for(int id = 0; id < L; id++){
				v[i][j - b + 1][id] = mul(v[i][j - b + 1][id], poti[id][j - b + 1]);
			}
		}
	}
}

int solve(){
	vector<int> pi(a, 0);
	int k = 0;
	for(int i = 1; i < a; i++){
		while(k > 0 and p[k] != p[i]) k = pi[k - 1];
		if(p[k] == p[i]) k++;
		pi[i] = k;
	}
	int ans = 0;
	for(int col = 0; col + b - 1 < d; col++){
		k = 0;
		for(int i = 0; i < c; i++){
			while(k > 0 and p[k] != v[i][col]) k = pi[k - 1];
			if(p[k] == v[i][col]) k++;
			if(k == a) ans++;
		}
	}
	return ans;
}

int main(){
	init();
	while(scanf("%d %d %d %d", &a, &b, &c, &d) == 4){
		for(int i = 0; i < a; i++){
			scanf("%s", pat[i]);
		}
		for(int i = 0; i < c; i++){
			scanf("%s", text[i]);
		}
		build_matrix();
		printf("%d\n", solve());
	}
	return 0;
}
