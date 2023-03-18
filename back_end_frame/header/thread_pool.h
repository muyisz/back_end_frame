#pragma once
#include <future>
#include<thread>
#include <winsock2.h>
#include"util.h"
#include"const.h"
#if _WIN32

#pragma comment(lib, "ws2_32.lib")

#endif // _WIN32

namespace muyi {
	struct threadNode {
		std::thread* thread;
		int ID;
	};

	class threadPool {
	public:
		threadPool(int size);
		~threadPool();
		template<class... TYPES>
		void Commit(void(*func)(TYPES... types), TYPES... types) {
			auto newTask = [this, func, ...type = types](int threadID) {
				func(type...);
				resetThread(threadID);
				PulseEvent(threadHandle);
			};
			taskQueue.Push(newTask);
			PulseEvent(taskHandle);
		}
	private:
		using TASK = std::function<void(int)>;
		const int threadNumber;
		mutexQueue<TASK> taskQueue;
		mutexQueue<threadNode> readyThreadQueue;
		mutexVector<threadNode> threadList;
		std::mutex threadMutex;
		HANDLE taskHandle;
		HANDLE threadHandle;

		void check();
		void resetThread(int threadID);
	};
}
