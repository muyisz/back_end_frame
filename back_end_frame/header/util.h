#pragma once
#include<queue>
#include<mutex>
#include<vector>

namespace muyi {

	template<class TYPE>
	class mutexQueue {
	public:
		void Pop() {
			std::unique_lock<std::mutex> lock(mMutex);
			mQueue.pop();
		}
		void Push(TYPE data) {
			std::unique_lock<std::mutex> lock(mMutex);
			mQueue.push(data);
		}
		int Size() {
			std::unique_lock<std::mutex> lock(mMutex);
			return mQueue.size();
		}
		bool Empty() {
			std::unique_lock<std::mutex> lock(mMutex);
			return mQueue.empty();
		}
		TYPE Front() {
			std::unique_lock<std::mutex> lock(mMutex);
			return mQueue.front();
		}
	private:
		std::queue<TYPE>mQueue;
		std::mutex mMutex;
	};

	template<class TYPE>
	class mutexVector {
	public:
		void push_back(TYPE data) {
			std::unique_lock<std::mutex> lock(mMutex);
			return mVector.push_back(data);
		}
		TYPE& operator[](int i) {
			std::unique_lock<std::mutex> lock(mMutex);
			return mVector[i];
		}
	private:
		std::vector<TYPE>mVector;
		std::mutex mMutex;
	};
}
