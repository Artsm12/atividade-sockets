#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class Thread_pool {
public:
  Thread_pool(int num_threads);
  ~Thread_pool();

  void enqueue(std::function<void()> task);

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::mutex queue_mutex;
  std::condition_variable cv;
  bool stop;
};