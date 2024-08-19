#ifndef ThreadPool_H
#define ThreadPool_H

#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace ThreadPool
{
   class ThreadPool
   {
   private:
      // 총 Worker 쓰레드 갯수
      std::size_t num_threads_;
      // Worker 쓰레드를 보관하는 벡터
      std::vector<std::thread> worker_threads_;
      // 할 일을 보관하는 job queue
      std::queue<std::function<void()>> jobs_;
      // race condition 보호장치
      std::condition_variable cv_job_q_;
      std::mutex m_job_q_;
      // 모든 쓰레드 종료
      bool stop_all;

   public:
      // 생성자
      ThreadPool(std::size_t num_threads);
      // 쓰레드가 실행할 함수
      void WorkerThread();
      // 작업 추가 함수
      void EnqueueJob(std::function<void()> job);
      // 소멸자
      ~ThreadPool();
   };
}
#endif