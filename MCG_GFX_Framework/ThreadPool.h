#pragma once
#include <functional>
#include <vector>
#include <condition_variable>
#include <queue>

class ThreadPool
{
public:
	using Task = std::function<void()>;

	explicit ThreadPool(std::size_t numThreads);
	~ThreadPool();
	void start(std::size_t numThreads);
	void stop();
	void addToQ(Task task);
private:


	std::vector<std::thread> threads;
	std::condition_variable eventVar;
	std::mutex eventMutex;
	//holds list of tasks to be executed in thread pool
	std::queue<Task> tasks;
	//stopping flag
	bool stopping = false;


	
};

