// Inlcude
#include <vector>
#include <future>
#include <iostream>
#include <numeric>

// Using
using std::vector;
using std::cout;

/// <summary>
/// Calculates partial sum from vector
/// </summary>
/// <param name="nums">vector containing values</param>
/// <param name="result">partial sum</param>
/// <param name="start">starting point of the partial sum</param>
/// <param name="end">ending point of the partial sum</param>
void calculate_partial_sum(vector<int>& nums, int& result, size_t start, size_t end)
{
    result = accumulate(nums.begin() + start, nums.begin() + end, 0);
}

/// <summary>
/// Main function for calculating sum async
/// </summary>
/// <returns></returns>
int main()
{

    // Define number of values
    const int num_count = 1000000;

    // Define how many threads will be used
    const size_t thread_count = static_cast<size_t>(std::thread::hardware_concurrency()) - 1;

    // Initialize vector containing the values
    vector<int> nums(num_count, 1);

    // Randomly define values in nums
    srand(time(0));
    for (int& num : nums)
    {
        num = rand() % 11;
    }

    // Define futures
    vector<std::future<void>> futures;
    // Define partial sums into a vector
    vector<int> results(thread_count);
    // Define how many values are calculated for each partial sum
    size_t elements_in_threads = num_count / thread_count;

    for (size_t i = 0; i < thread_count; i++)
    {
        // Define the starting point of this partial sum
        size_t start = i * elements_in_threads;
        // Define the ending point of this partial sum
        size_t end = (i == thread_count - 1) ? num_count : start + elements_in_threads;

        // Start async process
        futures.emplace_back(async(std::launch::async, calculate_partial_sum, ref(nums), std::ref(results[i]), start, end));
    }

    // Wait until async process to finish
    for (auto& thread : futures)
    {
        thread.get();
    }

    // Calculate final sum
    int sum = accumulate(results.begin(), results.end(), 0);

    // Print the final sum
    cout << "Calculated Sum: " << sum << "\n";
    cout << "Number of calculated values: " << num_count;

    return 0;
}