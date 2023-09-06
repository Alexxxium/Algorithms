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
		bool empty();

		// Freeze target thread and active waiting of unfreezing
		void freeze();

		// Unfreeze target thread if he was freezed
		void unfreeze();

		// Waiting all tasks in main thread
		void wait();

		// Break targed thread before executing current task (break active waitin tasks)
		void crash();

		// Start/restart target thread
		void run();
	};
}
