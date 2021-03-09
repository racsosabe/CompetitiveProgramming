#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Notice that since we want the sum of values of all the intervals that have

	  a non-empty intersection with [A, B], the answer is equivalent to the total

	  sum of values minus the sum of values of the intervals that don't intersect

	  at all with [A, B].

	- An interval [l, r] doesn't intersect with [A, B] if and only if:

	  1) r < A or

	  2) B < l

	- We can mantain two Fenwick Trees:

	  1) This one will store the sum of values of the intervals that end in position x

	  2) This one will store the sum of values of the intervals that start in position x

	- Thus, the answer for query [A, B] will be:

	  Ans = Total sum - query(1, 0, A - 1) - query(2, B + 1, MAX)

	  Where query(id, l, r) gives the sum of the positions [l, r] in the Fenwick

	  Tree with id "id". MAX = 10^6 due to constraints.

	- Complexity: O(nlogMAX)

*/

const int N = 100000 + 5;
const int limit = 1000000;

int n;
int q;
int lower[N];
int upper[N];
int price[N];
long long ft[2][10 * N];

void update(int id, int pos, int val){
	pos += 1;
	while(pos <= limit + 1){
		ft[id][pos] += val;
		pos += (-pos) & pos;
	}
}

long long getSum(int id, int pos){
	pos += 1;
	long long res = 0LL;
	while(pos > 0){
		res += ft[id][pos];
		pos &= pos - 1;
	}
	return res;
}

long long query(int id, int l, int r){
	return getSum(id, r) - getSum(id, l - 1);
}

int main(){
	scanf("%d", &n);
	long long total_sum = 0LL;
	for(int i = 1; i <= n; i++){
		scanf("%d %d %d", &lower[i], &upper[i], &price[i]);
		total_sum += price[i];
		update(0, upper[i], price[i]);
		update(1, lower[i], price[i]);
	}
	scanf("%d", &q);
	int op;
	int i, l, r, c;
	while(q--){
		scanf("%d", &op);
		if(op == 1){
			scanf("%d %d", &l, &r);
			printf("%lld\n", total_sum - query(0, 0, l - 1) - query(1, r + 1, limit + 1));
		}
		else{
			scanf("%d", &i);
			scanf("%d %d %d", &l, &r, &c);
			total_sum -= price[i];
			update(0, upper[i], -price[i]);
			update(1, lower[i], -price[i]);
			lower[i] = l;
			upper[i] = r;
			price[i] = c;
			total_sum += price[i];
			update(0, upper[i], price[i]);
			update(1, lower[i], price[i]);
		}
	}
	return 0;
}
