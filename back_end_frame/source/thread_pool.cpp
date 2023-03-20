#include"../header/thread_pool.h"
namespace muyi {
	threadPool::threadPool(int size) :threadNumber(size) {
		taskHandle = CreateEvent(NULL, TRUE, FALSE, TEXT("taskEvent"));
		threadHandle = CreateEvent(NULL, TRUE, FALSE, TEXT("threadEvent"));

		for (int i = 0; i < threadNumber; i++) {
			threadNode node;
			node.ID = i;
			node.thread = new std::thread;
			readyThreadQueue.Push(node);
			threadList.push_back(node);
		}

		std::thread checkThread(&threadPool::check, this);
		checkThread.detach();
	}

	threadPool::threadPool() :threadNumber(DefaultMaxThread) {
		taskHandle = CreateEvent(NULL, TRUE, FALSE, TEXT("taskEvent"));
		threadHandle = CreateEvent(NULL, TRUE, FALSE, TEXT("threadEvent"));

		for (int i = 0; i < threadNumber; i++) {
			threadNode node;
			node.ID = i;
			node.thread = new std::thread;
			readyThreadQueue.Push(node);
			threadList.push_back(node);
		}

		std::thread checkThread(&threadPool::check, this);
		checkThread.detach();
	}

	threadPool::~threadPool() {
		for (int i = 0; i < threadNumber; i++) {
			delete threadList[i].thread;
			threadList[i].thread = nullptr;
		}
	}


	void threadPool::resetThread(int threadID) {
		threadMutex.lock();
		readyThreadQueue.Push(threadList[threadID]);
		threadMutex.unlock();
	}

	void threadPool::check() {
		while (true) {
			if (!taskQueue.Empty()) {
				threadPool::TASK task = taskQueue.Front();
				threadMutex.lock();
				if (!readyThreadQueue.Empty()) {
					taskQueue.Pop();
					threadNode node = readyThreadQueue.Front();
					readyThreadQueue.Pop();
					*node.thread = move(std::thread(task, node.ID));
					node.thread->detach();
					threadMutex.unlock();
				}
				else {
					threadMutex.unlock();
					WaitForSingleObject(threadHandle, INFINITE);
				}
			}
			else {
				WaitForSingleObject(taskHandle, TaskWaitMaxTime);
			}
		}
	}
}
