#include "ThreadPool.h"


ThreadPool::ThreadPool(std::size_t numThreads)
{
	start(numThreads);
}


ThreadPool::~ThreadPool()
{
	stop();
}

void ThreadPool::start(std::size_t numThreads)
{
	for (auto i = 0u; i < numThreads; i++)
	{

		threads.emplace_back([=] {
			while (true)
			{
				//create new task
				//scope created here so mutex is not locked during task execution
				//locks mutex during tasks list editing and task allocation only
				Task task;
				{				

					std::unique_lock<std::mutex> lock{ eventMutex };

					//condition variable wakes up if stopping or task not empty
					eventVar.wait(lock, [=] {return stopping || !tasks.empty();  });
				
					if (stopping && tasks.empty())
					{
						break;
					}

					//get task from front of the queue of tasks
					task = std::move(tasks.front());
					//remove front most task
					tasks.pop();
				}

				task();

			}
		});
	}

}

void ThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> lock{ eventMutex };

		stopping = true;
	}
	//notify threads event happening and need to stop;
	eventVar.notify_all();


	for (auto &thread : threads)
	{
		thread.join();
	}
}

void ThreadPool::addToQ(Task task)
{
	//create queue, scope restricts scope of LOCKS FOR MUTEXS. very useful and important
	{
		std::unique_lock<std::mutex> lock{ eventMutex };
		tasks.emplace(std::move(task));
	}

	//notify thread that event occurred
	eventVar.notify_one();
}

