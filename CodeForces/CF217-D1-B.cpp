#include<bits/stdc++.h>
using namespace::std;

int n;
int r;
vector<int> v;

int get(int a, int b){
	if(b == 0) return a == 1 ? 0 : 1e9;
	return a / b + get(b, a % b);
}

void build(int a, int b){
	if(b == 1){
		v.emplace_back(1);
		if(a > 1) v.emplace_back(a - 1);
		return;
	}
	int len = a / b;
	build(b, a % b);
	if(len > 0) v.emplace_back(len);
}

void compute(int i, int moves){
	v.clear();
	build(i, r);
}

int getCost(char c){
	int ans = 0;
	for(auto x : v){
		ans += x - 1;
	}
	return ans;
}

void answer(int i){
	int moves = get(i, r);
	compute(i, moves);
	char cur = n > moves ? 'B' : 'T';
	printf("%d\n", getCost(cur));
	for(auto x : v){
		for(int j = 0; j < x; j++) putchar(cur);
		cur ^= 'T' ^ 'B';
	}
	putchar('\n');
}

int main(){
	scanf("%d %d", &n, &r);
	bool found = false;
	int best = -1;
	int bcost = -1;
	vector<int> res;
	for(int i = 0; i <= r; i++){
		int moves = get(i, r);
		if(i == 0 and n > 1) continue;
		if(moves == n){
			compute(i, moves);
			int cost = getCost('T');
			if(best == -1 or bcost > cost){
				bcost = cost;
				best = i;
			}
			found = true;
		}
	}
	if(not found){
		puts("IMPOSSIBLE");
		return 0;
	}
	answer(best);
	return 0;
}
