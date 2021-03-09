#include<bits/stdc++.h>
using namespace::std;

/*
	Autor: Racso Galvan

	Idea:

	- Implementación.

	- Basta con implementar lo que propone el problema, rompiendo empates según corresponda

	- Complejidad: O(nk).

*/

const int N = 1000 + 5;
const int S = 100 + 5;

int n, k, M;
int cap[N];
int times[N][S];

int main(){
	scanf("%d %d %d", &n, &M, &k);
	for(int i = 1; i <= n; i++){
		cap[i] = M;
	}
	int res = 0;
	for(int i = 0; i < k; i++){
		int s, m;
		scanf("%d %d", &s, &m);
		int best = -1;
		for(int i = 1; i <= n; i++){
			if(cap[i] >= m){
				if(best == -1) best = i;
				else{
					if(times[best][s] > times[i][s]){
						best = i;
					}
					else if(times[best][s] == times[i][s]){
						if(cap[best] < cap[i]){
							best = i;
						}
					}
				}
			}
		}
		if(best >= 1){
			times[best][s] += 1;
			cap[best] -= m;
			res += 1;
		}
	}
	printf("%d\n", res);
	for(int i = 1; i <= n; i++){
		printf("%d%c", M - cap[i], " \n"[i == n]);
	}
	return 0;
}
