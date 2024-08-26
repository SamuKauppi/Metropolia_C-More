#include <iostream>
#include <future>
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
	const int starting_value = 10000000;
	account = starting_value;

	future<void> fut_add = async(launch::async, editing_account, starting_value, 1);
	future<void> fut_take = async(launch::async, editing_account, starting_value, -1);

	fut_add.get();
	fut_take.get();

	cout << "Starting value: " << starting_value;
	cout << "\nCurrent value: " << account;
}