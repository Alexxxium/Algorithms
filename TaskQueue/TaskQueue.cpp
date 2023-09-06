#include "TaskQueue.h"
#include <iostream>



namespace algs
{
	TaskQueue::TaskQueue():
		pause(false),
		quit(false),
		target(std::thread(&TaskQueue::start, this))
	{
	}

	TaskQueue::~TaskQueue() {
		wait();
		crash();
	}

	void TaskQueue::addTask(const std::function<void()> &task) {
		std::lock_guard<std::mutex> lock(mutex);
		queue.push(task);
	}

	void TaskQueue::addTasks(const std::initializer_list<std::function<void()>> &tasks) {
		std::lock_guard<std::mutex> lock(mutex);
		for (const auto &task: tasks) {
			queue.push(task);
		}
	}

	bool TaskQueue::empty() noexcept {
		std::lock_guard<std::mutex> lock(mutex);
		return queue.empty();
	}

	void TaskQueue::freeze() noexcept {
		pause.store(true);
	}

	void TaskQueue::unfreeze() noexcept {
		pause.store(false);
	}

	void TaskQueue::wait() {
		constexpr int milsec = 100;

		while (true) {
			{
				std::unique_lock<std::mutex> lock(mutex);
				if (queue.empty() || quit.load()) {
					break;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(milsec));
		}
	}

	void TaskQueue::crash() {
		quit.store(true);
		pause.store(false);
		target.join();
	}

	void TaskQueue::run() noexcept {
		if (quit.load()) {
			quit.store(false);
			pause.store(false);
			target = std::thread(&TaskQueue::start, this);
		}
	}

	void TaskQueue::start() {
		constexpr int milsec = 100;

		while (true) {
			if (quit.load()) {
				return;
			}

			std::function<void()> task = nullptr;
			{
				std::lock_guard<std::mutex> lock(mutex);
				if (!queue.empty()) {
					task = queue.front();
					queue.pop();
				}
			}

			if (task != nullptr) {
				task();
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(milsec));
			}

			while (pause.load()) {
				std::this_thread::sleep_for(std::chrono::milliseconds(milsec));
			}
		}
	}
}
