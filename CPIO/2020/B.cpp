#include<bits/stdc++.h>
using namespace::std;

/*
	Autor: Racso Galvan

	Idea:

	- Sliding Window

	- Un string a es anagrama de b si las frecuencias de sus caracteres son iguales.

	- Podemos mantener las frecuencias de los substrings de tamaño |a| usando 

	  un arreglo de frecuencias por cada letra (o tal vez un mapa) y una cola doble.

	- Cuando agregas la letra de la posición i, debes quitar la de la posición

	  i - |a| (si es que esta existe), así que insertas b[i] al final de la cola doble

	  y extraes el primer elemento de la misma para hacer las modificaciones.

	- Basta con comparar las frecuencias y sumar 1 si es que coinciden.

	- Complejidad: O(n + m * |E|), donde E es el alfabeto, n es la longitud de

	  la cadena s1 y m es la longitud de la cadena s2.

*/

const int E = 65;

int F1[E];
int F2[E];
int id[256];

void init(){
	int pos = 0;
	for(char i = 'a'; i <= 'z'; i++) id[i] = pos++;
	for(char i = 'A'; i <= 'Z'; i++) id[i] = pos++;
	for(char i = '0'; i <= '9'; i++) id[i] = pos++;
}

int main(){
	init();
	char c = getchar();
	int len = 0;
	while(c != '\n'){
		len += 1;
		F1[id[c]] += 1;
		c = getchar();
	}
	deque<char> Q;
	c = getchar();
	for(int i = 0; i + 1 < len; i++){
		Q.emplace_back(c);
		F2[id[c]] += 1;
		c = getchar();
	}
	int ans = 0;
	while(c != '\n'){
		Q.emplace_back(c);
		F2[id[c]] += 1;
		if(Q.size() > len){
			F2[id[Q.front()]] -= 1;
			Q.pop_front();
		}
		bool act = true;
		for(int j = 0; j < E; j++){
			act &= F1[j] == F2[j];
		}
		ans += act;
		c = getchar();
	}
	printf("%d\n", ans);
	return 0;
}
