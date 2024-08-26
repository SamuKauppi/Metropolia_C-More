#include <vector>
#include <thread>
#include <iostream>
#include <numeric>

using namespace std;

void calculate_partial_sum(vector<int>& nums, int& result, size_t start, size_t end)
{
	result = accumulate(nums.begin() + start, nums.begin() + end, 0);
}


int main()
{

	// M‰‰ritell‰‰n numeroiden m‰‰r‰
	const int num_count = 100000;

	// M‰‰ritell‰‰n s‰ikeiden m‰‰r‰t ja numeroiden arvot
	const size_t thread_count = thread::hardware_concurrency();
	vector<int> nums(num_count, 1);

	// Vaihtoehtoinen satunnainen arvojen m‰‰ritys
	//srand(time(0));
	//for (int& num : nums)
	//{
	//	num = rand() % 11;
	//}

	vector<thread> threads;	// M‰‰ritell‰‰n s‰ikeet vektoriin
	vector<int> results(thread_count);	// M‰‰ritell‰‰n osasummien palautus vektori
	size_t elements_in_threads = num_count / thread_count;	// M‰‰ritell‰‰n osasummien m‰‰r‰

	for (size_t i = 0; i < thread_count; i++)
	{
		// M‰‰ritell‰‰n seuraavan s‰ikeen aloitus ja lopetus piste
		size_t start = i * elements_in_threads;
		size_t end = (i == thread_count - 1) ? num_count : start + elements_in_threads;

		// Aloiteaan funktiokutsu s‰ikeess‰
		threads.emplace_back(calculate_partial_sum, ref(nums), ref(results[i]), start, end);
	}

	// Odotetaan, ett‰ s‰ikeet ovat suorittaneet loppuun
	for (auto& thread : threads)
	{
		thread.join();
	}

	int sum = accumulate(results.begin(), results.end(), 0);

	cout << "Laskettujen arvojen summa: " << sum << "\n";
	cout << "Arvojen m‰‰r‰: " << num_count;
}