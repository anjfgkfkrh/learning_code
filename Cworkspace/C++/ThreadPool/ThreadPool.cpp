#include "ThreadPool.h"
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
   ThreadPool::ThreadPool(size_t num_threads)
       : num_threads_(num_threads), stop_all(false)
   {
      worker_threads_.reserve(num_threads_);
      for (size_t i = 0; i < num_threads_; ++i)
      {
         worker_threads_.emplace_back([this]()
                                      { this->WorkerThread(); });
      }
   }

   void ThreadPool::WorkerThread()
   {
      while (true)
      {
         // mutex를 잠궈 다른 스레드의 접근을 막음
         std::unique_lock<std::mutex> lock(m_job_q_);
         // 조건 확인 후 lock 해제
         // 조건이 참일때까지 스레드 대기
         cv_job_q_.wait(lock, [this]()
                        { return !this->jobs_.empty() || stop_all; });
         // stop_all이 참이고 큐가 비어있을시 스레드 종료
         if (stop_all && this->jobs_.empty())
         {
            return;
         }

         // 맨 앞의 job을 뺀다.
         std::function<void()> job = std::move(jobs_.front());
         jobs_.pop();
         lock.unlock();

         // 해당 job을 실행
         job();
      }
   }

   void ThreadPool::EnqueueJob(std::function<void()> job)
   {
      if (stop_all)
      {
         throw std::runtime_error("ThreadPool 사용 중지됨");
      }
      {
         std::lock_guard<std::mutex> lock(m_job_q_);
         jobs_.push(std::move(job));
      }
      cv_job_q_.notify_one();
   }

   ThreadPool::~ThreadPool()
   {
      stop_all = true;
      cv_job_q_.notify_all();

      for (auto &t : worker_threads_)
      {
         t.join();
      }
   }
}