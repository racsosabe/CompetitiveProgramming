#include<bits/stdc++.h>
using namespace::std;

/*
	Autor: Racso Galvan

	Idea:
	
	- Problema de mezclas

	- Si en un momento hay C de café y L de leche, se extrae C/2 de café y L/2 de leche

	  para agregar (L + C) / 2 de la letra que corresponda

	- Observación 1: Luego del procedimiento anterior, solo quedan:

	  Caso L: Cafe = C / 2, Leche = L + (L + C) / 2

	  Caso C: Cafe = C + (L + C) / 2, Leche = L / 2

	- Observación 2: Solo pueden haber la misma cantidad en un momento cuando

	  alguno de ellos es 0 y sale su letra en el movimiento.

	- Debido a la observación 2, solo son iguales cuando se da un patrón de Ls

	  y termina con una C.

	- En caso contrario, L > 0 y C > 0 da que:

	  Caso L: L > 0 -> 3 L / 2 > 0 -> 3 L / 2 + C / 2 > C / 2.

	  Caso C: C > 0 -> 3 C / 2 > 0 -> 3 C / 2 + L / 2 > L / 2.

	  Así que imprimiremos la última letra.

	- Complejidad: O(n)
*/

const int N = 100000 + 5;

int n;
char s[N];

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	bool eqifC = true;
	for(int i = 0; i + 1 < n; i++){
		if(s[i] != 'L') eqifC = false;
	}
	if(eqifC and s[n - 1] == 'C') puts("D");
	else puts(s[n - 1] == 'C'? "C" : "L");
	return 0;
}
