#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Just notice that if we fix two opposite faces, the other 4 will be fixed as well.

	- We can map somehow the colors of each face to some value and add to a frequency map each of its rotations.

	- After that, we can choose each possible (i, j) with i < j and count the number

	  of ways we can build a cube for each of their rotations (consider that
	  
	  we delete i and j and all their rotations before doing the count).

	- Complexity: O(n^2 logn)
*/

const int N = 400 + 5;

int n;
int C[N][6];
long long v[N];
map<long long, int> F;

void add(long long x){
	for(int i = 0; i < 4; i++){
		F[x] += 1;
		x = ((x & 1023) << 30) + (x >> 10);
	}
}

void del(long long x){
	for(int i = 0; i < 4; i++){
		F[x] -= 1;
		x = ((x & 1023) << 30) + (x >> 10);
	}
}

void printFrec(){
	cout << "Frequency: " << endl;
	for(auto e : F) cout << e.first << " -> " << e.second << endl;
}

long long g(int i, int j){
	long long ans = 0;
	vector<long long> want(4);
	for(int r1 = 0; r1 < 4; r1++){
		for(int r2 = 0; r2 < 4; r2++){
			long long here = 1;
			for(int k = 0; k < 4; k++){
				long long cur = 0;
				if(k & 1){
					cur += C[i][(k + r1) & 3];
					cur += C[j][(k + r2 + 3) & 3] << 10;
					cur += C[j][(k + r2 + 2) & 3] << 20;
					cur += (long long)C[i][(k + r1 + 1) & 3] << 30;
				}
				else{
					cur += C[i][(k + r1) & 3];
					cur += C[j][(k + r2 + 1) & 3] << 10;
					cur += C[j][(k + r2) & 3] << 20;
					cur += (long long)C[i][(k + r1 + 1) & 3] << 30;
				}
				want[k] = cur;
				if(!F.count(cur)){
					here = 0;
				}
			}
			if(here == 0) continue;
			for(auto x : want){
				here *= F[x];
				del(x);
			}
			ans += here;
			for(auto x : want) add(x);
		}
	}
	return ans;
}

long long solve(){
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		del(v[i]);
		for(int j = i + 1; j <= n; j++){
			del(v[j]);
			ans += g(i, j);
			add(v[j]);
		}
	}
	return ans >> 2;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < 4; j++){
			scanf("%d", &C[i][j]);
		}
		for(int j = 3; j >= 0; j--){
			v[i] = (v[i] << 10) + C[i][j];
		}
		add(v[i]);
	}
	printf("%lld\n", solve());
	return 0;
}
