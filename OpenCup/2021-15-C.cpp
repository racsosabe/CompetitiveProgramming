#include<bits/stdc++.h>
using namespace::std;

/*
	Grand Prix of China - Problem C "Random Shuffle"

	Author: Racso Galvan

	Idea:

	- 



*/

const int N = 100000 + 5;
const int LOG = 64;

int n;
int len;
int a[N];
int b[N];
vector<int> positions;
unsigned long long ans;
unsigned long long p[LOG];
unsigned long long bits[LOG];
pair<unsigned long long, bool> A[LOG];

bool check(unsigned long long x){
	for(int i = 1; i <= n; i++){
		x ^= x << 13;
		x ^= x >> 7;
		x ^= x << 17;
		if(b[i] != x % i) return false;
	}
	return true;
}

void getValues(){
	vector<int> pos(n + 1);
	for(int i = 1; i <= n; i++) pos[a[i]] = i;
	for(int i = n; i >= 1; i--){
		int to = pos[i];
		b[i] = to;
		if(i != to){
			swap(pos[a[i]], pos[a[to]]);
			swap(a[i], a[to]);
		}
	}
	for(int i = 1; i <= n; i++) b[i] -= 1;
}


void getEquations(){
	for(int i = 0; i < LOG; i++) bits[i] = p[i];
	for(int i = 1; i <= n; i++){
		for(int j = LOG - 14; j >= 0; j--){
			bits[j + 13] ^= bits[j];
		}
		for(int j = 7; j < LOG; j++){
			bits[j - 7] ^= bits[j];
		}
		for(int j = LOG - 18; j >= 0; j--){
			bits[j + 17] ^= bits[j];
		}
		int pos = 31 - __builtin_clz(i & (-i));
		for(int j = 0, x = b[i]; j < pos and len < 64; j++, x >>= 1){
			unsigned long long used = bits[j];
			int result = x & 1;
			for(int k = 0; k < len; k++){
				if((used ^ A[k].first) < used){
					used ^= A[k].first;
					result ^= A[k].second;
				}
			}
			if(used){
				A[len++] = make_pair(used, result);
			}
		}
	}
}

void reduce(){
	for(int i = 0; i < len; i++){
		int best = -1;
		unsigned long long cur = ULLONG_MAX;
		for(int j = i; j < len; j++){
			if(A[j].first == 0) continue;
			if(__builtin_ctzll(A[j].first) < cur){
				best = j;
				cur = __builtin_ctzll(A[j].first);
			}
		}
		if(best == -1) break;
		if(i != best){
			swap(A[i], A[best]);
		}
		for(int j = i + 1; j < len; j++){
			if(A[j].first & p[cur]){
				A[j].first ^= A[i].first;
				A[j].second ^= A[i].second;
			}
		}
	}
}

vector<int> getPositions(){
	vector<int> res;
	unsigned long long known = 0;
	for(int i = len - 1; i >= 0; i--){
		unsigned long long carry = A[i].first;
		for(int j = 0; j < LOG; j++){
			if(carry & p[j] and known & p[j]){
				carry ^= p[j];
			}
		}
		if(carry == 0) continue;
		int l = __builtin_ctzll(carry);
		for(int j = l + 1; j < LOG; j++){
			if(carry & p[j]){
				res.emplace_back(j);
				carry ^= p[j];
				known |= p[j];
			}
		}
		known |= p[l];
	}
	return res;
}

bool test(int mask){
	ans = 0;
	unsigned long long known = 0;
	for(int i = 0; i < positions.size(); i++){
		if((mask >> i) & 1) ans |= p[positions[i]];
		known |= p[positions[i]];
	}
	for(int i = len - 1; i >= 0; i--){
		unsigned long long carry = A[i].first;
		int result = A[i].second;
		unsigned long long already = carry & known;
		unsigned long long values = already & ans;
		if(__builtin_popcountll(values) & 1) result ^= 1;
		carry ^= already;
		known |= carry;
		if(result) ans |= carry;
	}
	return check(ans);
}

void solve(){
	positions = getPositions();
	int limit = 1 << positions.size();
	for(int mask = 0; mask < limit; mask++){
		if(test(mask)) break;
	}
}

void print(){
	for(int i = 0; i < len; i++){
		vector<int> positions;
		for(int j = 0; j < LOG; j++){
			if(A[i].first & p[j]) positions.emplace_back(j);
		}
		for(auto x : positions){
			printf("x_{%d}", x);
			if(x != positions.back()) printf(" + ");
			else printf(" = ");
		}
		printf("%d\n", (int)A[i].second);;
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	p[0] = 1;
	for(int i = 1; i < LOG; i++) p[i] = p[i - 1] << 1;
	getValues();
	getEquations();
	reduce();
	solve();
	printf("%llu\n", ans);
	return 0;
}
