#include "../include/thread_pool.hpp"
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <vector>

Thread_pool::Thread_pool(int num_threads) {
  stop = false;

  for (int i = 0; i < num_threads; i++) {
    workers.emplace_back([this] {
      while (true) {
        std::function<void()> task;

        {
          std::unique_lock<std::mutex> lock(this->queue_mutex);

          this->cv.wait(lock,
                        [this] { return this->stop || !this->tasks.empty(); });

          if (this->stop && this->tasks.empty()) {
            return;
          }

          task = std::move(this->tasks.front());
          this->tasks.pop();
        }

        task();
      }
    });
  }
}

Thread_pool::~Thread_pool() {
  std::unique_lock<std::mutex> lock(queue_mutex);
  stop = true;

  cv.notify_all();

  for (std::thread &worker : workers) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

void Thread_pool::enqueue(std::function<void()> task) {
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    if (stop)
      return;
    tasks.push(task);
  }

  cv.notify_one();
}
