#include<bits/stdc++.h>
using namespace::std;

/*
	Autor: Racso Galvan

	Idea:

	- Programación Dinámica

	- Basta con definir una recursión DP(pos, happy, full) que dará la máxima cantidad

	  de platos a comer dado que hemos considerado los primeros "pos" platos

	  y hemos elegido de manera que nuestra felicidad es mayor o igual a "happy"

	  y tenemos una llenura "full".

	- Para no usar mucha memoria, notemos que nuestra condición para que una 

	  serie de elecciones sea válida es que happy >= 100, así que cuando hacemos

	  una elección, el happy del nuevo estado es min(happy + f[pos], 100).

	- Complejidad: O(n * max_felicidad * max_llenura).
*/

const int N = 51;
const int M = 101;

int n;
int l[N];
int f[N];
bool vis[N][M][M];
int memo[N][M][M];

int DP(int pos, int happy, int full){
	if(pos == n){
		return happy == 100? 0 : -100;
	}
	if(vis[pos][happy][full]) return memo[pos][happy][full];
	int ans = DP(pos + 1, happy, full);
	if(full + l[pos] <= 100){
		ans = max(ans, 1 + DP(pos + 1, min(happy + f[pos], 100), full + l[pos]));
	}
	vis[pos][happy][full] = true;
	return memo[pos][happy][full] = ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d %d", l + i, f + i);
	}
	printf("%d\n", DP(0, 0, 0));
	return 0;
}
