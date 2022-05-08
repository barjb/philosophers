#include <iostream>
#include <thread>
#include <array>
#include <algorithm>
#include <atomic>

constexpr int NUM_THREADS = 5;

std::array<std::atomic<int>, NUM_THREADS> states;

void think(int id)
{
	states[id].store(0);
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void hungry(int id)
{
	states[id].store(1);
	int l = id - 1 >= 0 ? id - 1 : NUM_THREADS - 1;
	int r = (id + 1) % NUM_THREADS;

	while (states[l].load() == 2 || states[r].load() == 2)
	{
		;
	}
}

void eat(int id)
{
	states[id].store(2);
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void philosopher(int id)
{
	while (true)
	{
		think(id);
		hungry(id);
		eat(id);
	}
}

void logger()
{
	int j = 0;
	auto lam = [&j](std::atomic<int> &x)
	{
		std::cout << j << " ";
		switch (x.load())
		{
		case 0:
			std::cout << "T\t";
			break;
		case 1:
			std::cout << "H\t";
			break;
		case 2:
			std::cout << "EAT\t";
			break;
		}
		j++;
		if (j == NUM_THREADS)
		{
			std::cout << std::endl;
		}
	};
	while (true)
	{
		std::for_each(states.begin(), states.end(), lam);
		j = 0;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main()
{
	std::thread t0(philosopher, 0);
	std::thread t1(philosopher, 1);
	std::thread t2(philosopher, 2);
	std::thread t3(philosopher, 3);
	std::thread t4(philosopher, 4);
	std::thread log(logger);

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	log.join();
}