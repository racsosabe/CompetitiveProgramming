#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int z[N];
int pi[N];
int cnt[N];
vector<int> Q[N];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &z[i]);
		if(z[i] > 0) Q[i + z[i]].emplace_back(i);
	}
	int mini = 0;
	int total = 0;
	for(int i = 0; i < n; i++){
		for(auto r : Q[i]){
			cnt[r] -= 1;
			total -= 1;
		}
		if(z[i] > 0){
			cnt[i] += 1;
			total += 1;
		}
		if(total > 0){
			while(cnt[mini] == 0) mini += 1;
			pi[i] = i - mini + 1;
		}
		else{
			pi[i] = 0;
		}
	}
	for(int i = 0; i < n; i++){
		printf("%d%c", pi[i], " \n"[i + 1 == n]);
	}
	return 0;
}
