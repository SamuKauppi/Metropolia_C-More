#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

void reduce_by_100(int& i)
{
	i = i <= 100 ? 0 : i - 100;
}

struct myclass
{
	void operator() (int& i) { i = i <= 100 ? 0 : i - 100; }
} myobject;

int main()
{
	srand(time(0));
	vector<int> hit_points(100);
	for_each(hit_points.begin(), hit_points.end(), [](int& i) { i = rand() % 151 + 50;});

	// Tavallisella funktiolla
	vector<int> hits1(hit_points);
	for_each(hits1.begin(), hits1.end(), reduce_by_100);

	// Funktio objektilla
	vector<int> hits2(hit_points);
	for_each(hits2.begin(), hits2.end(), myobject);

	// Lambda funktiolla
	vector<int> hits3(hit_points);
	for_each(hits3.begin(), hits3.end(), [](int& i) { i = i <= 100 ? 0 : i - 100; });

	// Nimetty lambda funktiolla
	vector<int> hits4(hit_points);
	auto lammas = [&](int& i)
		{
			i = i <= 100 ? 0 : i - 100;
		};
	for_each(hits4.begin(), hits4.end(), lammas);

	return 0;
}