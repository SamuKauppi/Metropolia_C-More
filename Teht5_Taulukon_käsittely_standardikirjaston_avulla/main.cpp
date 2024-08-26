#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>
#include <chrono>
#include <numeric>
using namespace std;

int main()
{
	const long long int N = 100000000;
	cout << "Annettujen alkioiden m‰‰r‰: " << N;
	vector<int> t(N);

	auto t1 = chrono::high_resolution_clock::now();
	// For each sequenced_policy. 
	// T‰m‰ suoritusm‰‰re tarkoittaa, ett‰ algoritmi suoritetaan yksitt‰isess‰ s‰ikeess‰, 
	// per‰kk‰in, kuten tavallisessa sekventiaalisessa ohjelmoinnissa.
	for_each(execution::seq, t.begin(), t.end(), [](int& n) { n++;});

	auto t2 = chrono::high_resolution_clock::now();
	int timer1 = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
	cout << "\nsequenced_policy suoritusaika: " << timer1 << " ms\n";
	cout << "summa: " << reduce(t.begin(), t.end()) << "\n";

	auto t3 = chrono::high_resolution_clock::now();
	// For each parallel_policy. 
	// T‰m‰ suoritusm‰‰re mahdollistaa algoritmin suorittamisen rinnakkaisesti useissa s‰ikeiss‰. 
	// Se ei takaa, ett‰ elementtej‰ k‰sitell‰‰n tietyss‰ j‰rjestyksess‰.
	for_each(execution::par, t.begin(), t.end(), [](int& n) {n++;});

	auto t4 = chrono::high_resolution_clock::now();
	int timer2 = chrono::duration_cast<chrono::milliseconds>(t4 - t3).count();
	cout << "parallel_policy suoritusaika: " << timer2 << " ms\n";
	cout << "summa: " << reduce(t.begin(), t.end()) << "\n";


	auto t5 = chrono::high_resolution_clock::now();
	// For each parallel_unsequenced_policy. 
	// T‰m‰ suoritusm‰‰re yhdist‰‰ rinnakkais- ja sekventiaalisuorituksen hyˆdyt. 
	for_each(execution::par_unseq, t.begin(), t.end(), [](int& n) {n++;});

	auto t6 = chrono::high_resolution_clock::now();
	int timer3 = chrono::duration_cast<chrono::milliseconds>(t6 - t5).count();
	cout << "parallel_unsequenced_policy suoritusaika: " << timer3 << " ms\n";
	cout << "summa: " << reduce(t.begin(), t.end()) << "\n";

	return 0;
}