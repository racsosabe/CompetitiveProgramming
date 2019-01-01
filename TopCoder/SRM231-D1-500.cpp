#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
	Author: Racso Galvan

	Idea:

		- Simple Math problem.

		- Just realize that all the numbers are huge

		  by themselves, but the actual answer isn't.

		  Then, we should think a way to get the direct

		  partial answer for each i not overflowing: 

		  Scale by logarithm will work correctly with

		  long double variables.

		- Complexity: O(N)

*/

class LargeSignTest {
public:
	string pvalue(int N, int K) {
		if(2*K == N){
			return "100.0%";
		}
		else{
			long double ans = 0.0;
			long double choose = 0.0;
			for(int i=0; i<=min(K,N-K); i++){
				if(i){
					choose += log(N-i+1);
					choose -= log(i);
				}
				long double exponent = choose - (N-1)*log(2);
				ans += expl(exponent);
			}
			stringstream msg;
			msg << setprecision(1) << fixed << 100.0*ans << "%";
			return msg.str();
		}
	}
};
