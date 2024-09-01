#include "pch.h"
#include "CppUnitTest.h"
#include "../Teht4_Summa_asynkronisilla_funktiokutsuilla/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
        TEST_METHOD(TestCalculatePartialSum)
        {
            // Prepare the test data
            std::vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // Test vector
            int result = 0;
            size_t start = 3; // Starting index for partial sum
            size_t end = 7;   // Ending index (exclusive) for partial sum

            // Calculate the expected result
            int expected = std::accumulate(nums.begin() + start, nums.begin() + end, 0);

            // Call the function
            calculate_partial_sum(nums, result, start, end);

            // Assert the result
            Assert::AreEqual(expected, result, L"Partial sum calculation failed.");
        }
	};
}
