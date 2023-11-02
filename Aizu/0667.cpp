#include<bits/stdc++.h>
using namespace::std;

const int N = 200 + 5;

int n;
int a;
int b;
char s[N];

int main(){
	scanf("%d %d %d", &n, &a, &b);
	scanf("%s", s + 1);
	reverse(s + a, s + b + 1);
	printf("%s\n", s + 1);
	return 0;
}
