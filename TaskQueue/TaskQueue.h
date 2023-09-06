#include <initializer_list>
#include <functional>
#include <string>
#include <atomic>
#include <thread>
#include <queue>
#include <mutex>



namespace algs
{
	/// Queue of void() functions (lambda []()->void)
	/// When created, starts a thread waiting for tasks in the queue
	/// You can wait/break complited task in the main thread
	class TaskQueue {
	private:
		std::mutex mutex;
		std::thread target;

		std::atomic<bool> pause, quit;
		std::queue<std::function<void()>> queue;

		void start();

	public:
		TaskQueue();
		~TaskQueue();

		TaskQueue(TaskQueue&&) = delete;
		TaskQueue(const TaskQueue&) = delete;
		TaskQueue& operator=(TaskQueue&&) = delete;
		TaskQueue& operator=(const TaskQueue&) = delete;

		void addTask(const std::function<void()> &task);
		void addTasks(const std::initializer_list<std::function<void()>> &tasks);


		// Return target queue status
		bool empty() noexcept;

		// Freeze target thread and activly waiting of unfreezing
		void freeze() noexcept;

		// Unfreeze the target thread if it has been frozen
		void unfreeze() noexcept;

		// Waiting for all tasks in the main thread
		void wait();

		// Break the target thread after running the current task (abort active waiting tasks)
		void crash();

		// Start/restart target thread
		void run() noexcept;
	};
}
