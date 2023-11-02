#include<bits/stdc++.h>
using namespace::std;

int a[2];
string s[] = {"Vladik", "Valera"};

int main(){
	scanf("%d %d", a, a + 1);
	int pos = 1;
	int turn = 0;
	while(true){
		if(a[turn] < pos){
			break;
		}
		a[turn] -= pos;
		pos += 1;
		turn ^= 1;
	}
	printf("%s\n", s[turn].c_str());
	return 0;
}
