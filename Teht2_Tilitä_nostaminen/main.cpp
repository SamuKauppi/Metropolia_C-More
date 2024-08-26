#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int account;
mutex account_mutex;

void editing_account(int count, int amount)
{
	for (int i = 0; i < count; i++)
	{
		lock_guard<mutex> lock(account_mutex);
		account += amount;
	}
}

int main()
{
	const int starting_value = 1000000000;
	account = starting_value;

	thread add(editing_account, starting_value, 1);
	thread take(editing_account, starting_value, -1);

	add.join();
	take.join();

	cout << "Starting value: " << starting_value;
	cout << "\nCurrent value: " << account;
}