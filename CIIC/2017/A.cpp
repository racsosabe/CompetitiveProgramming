#include<bits/stdc++.h>
using namespace::std;

/*
	Autor: Racso Galvan

	Idea:

	- Podemos armar la recurrencia memo[i] = sum(j = 1, ... k) memo[i - j]

	  considerando memo[x] = 0 para x <= 0.

	- Ya que no hay suficiente ML para guardar el arreglo completo, solo guardaremos

	  los últimos k valores procesados y la suma actual, de manera que podemos pasar

	  de i a (i + 1) en O(1) usando una cola doble.

	- Complejidad: O(n)

*/

const int MOD = 1000000;

inline int add(int a, int b){
	return a + b < MOD ? a + b : a + b - MOD;
}

int n;
int k;

int main(){
	scanf("%d %d", &k, &n);
	deque<int> Q;
	int suma = 1;
	Q.push_back(1);
	for(int i = 2; i <= n; i++){
		Q.push_back(suma);
		suma = add(suma, suma);
		if(Q.size() > k){
			suma = add(suma, MOD - Q.front());
			Q.pop_front();
		}
	}
	printf("%d\n", suma);
	return 0;
}
