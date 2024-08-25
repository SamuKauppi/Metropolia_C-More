#include <iostream>
#include <future>
#include <vector>
#include <chrono>

using namespace std;

class Game_Task
{
public:
	virtual void perform() = 0;
	virtual ~Game_Task() = default;
};

class Character : public Game_Task
{
private:
	int hp = 1000000;
public:
	void perform() override
	{
		for (size_t i = 0; i < 1000000000; i++)
		{
			take_damage(i);
		}
	}

	void take_damage(int value)
	{
		hp -= value;
	}
};

class Game_Map : public Game_Task
{
public:
	void perform() override
	{
		for (size_t i = 0; i < 10000000; i++)
		{
			int x = i * i * i;
		}
	}
};


int perform_with_threads(vector<Game_Task*>& tasks)
{
	int max_threads = thread::hardware_concurrency() - 1;

	if (max_threads < 1)
		return -1;

	auto t1 = chrono::high_resolution_clock::now();
	vector<future<void>> futures;
	for (size_t i = 0; i < tasks.size(); i++)
	{
		futures.emplace_back(async(launch::async, &Game_Task::perform, tasks[i]));
	}
	for (auto& t : futures)
	{
		t.get();
	}
	auto t2 = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
}

int perform_without_threads(vector<Game_Task*>& tasks)
{
	auto t3 = chrono::high_resolution_clock::now();
	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks[i]->perform();
	}
	auto t4 = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::milliseconds>(t4 - t3).count();
}

int main()
{
	vector<Game_Task*> tasks;

	tasks.push_back(new Character());
	tasks.push_back(new Character());
	tasks.push_back(new Game_Map());
	tasks.push_back(new Game_Map());


	// Measure time taken without threads
	int time1 = perform_without_threads(tasks);
	cout << "Without threading: " << time1 << " ms\n";

	// Measure time taken with threads
	int time2 = perform_with_threads(tasks);
	cout << "With threading: " << time2 << " ms\n";

	// Clean up allocated memory
	for (auto task : tasks)
	{
		delete task;
	}
	return 0;
}