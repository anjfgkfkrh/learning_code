#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


// // mutex 기본적인 사용방법
// void worker(int& result, std::mutex& m) {
//    for (int i = 0; i < 10000; i++) {
//       m.lock();
//       result += 1;
//       m.unlock();
//    }
// }

// mutex lock 자동 해제
// void worker(int& result, std::mutex& m) {
//    for (int i = 0; i < 10000; i++) {
//       std::lock_guard<std::mutex> lock(m);
//       result += 1;
//    }
// }

// int main() {
//    int counter = 0;
//    std::mutex m;

//    std::vector<std::thread> workers;
//    for (int i = 0; i < 4; i++)
//       workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));

//    for (int i = 0; i < 4; i++)
//       workers[i].join();

//    std::cout << "Counter 최종 값: " << counter << std::endl;
// }

void worker1(std::mutex& m1, std::mutex& m2) {
   for (int i = 0; i < 10000; i++) {
      m1.lock();
      m2.lock();
      std::cout << "Worker1 Hi! " << i << std::endl;

      m2.unlock();
      m1.unlock();
   }
}

void worker2(std::mutex& m1, std::mutex& m2) {
   for (int i = 0; i < 10000; i++) {
      while (true) {
         m2.lock();

         // m1이 이미 lock 되어 있다면 "야 차 빼"를 수행하게 된다.
         if (!m1.try_lock()) {
            m2.unlock();
            continue;
         }
         std::cout << "Worker2 Hi! " << i << std::endl;
         m1.unlock();
         m2.unlock();
         break;
      }
   }
}

int main() {
   std::mutex m1, m2;

   std::thread t1(worker1, std::ref(m1), std::ref(m2));
   std::thread t2(worker2, std::ref(m1), std::ref(m2));

   t1.join();
   t2.join();

   std::cout << "끝!" << std::endl;
}