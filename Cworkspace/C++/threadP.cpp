#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
using std::thread;
using std::vector;

void func1() {
   for (int i = 0; i < 10; i++)
      std::cout << "쓰레드 1 작동중! \n";
}

void func2() {
   for (int i = 0; i < 10; i++)
      std::cout << "쓰레드 2 작동중! \n";
}

void func3() {
   for (int i = 0; i < 10; i++)
      std::cout << "쓰레드 3 작동중! \n";
}

// int main() {
//    thread t1(func1);
//    thread t2(func2);
//    thread t3(func3);

//    // t1.join();
//    // t2.join();
//    // t3.join();

//    t1.detach();
//    t2.detach();
//    t3.detach();

//    std::cout << "메인 함수 종료 \n";
// }

void worker(vector<int>::iterator start, vector<int>::iterator end, int* result) {
   int sum = 0;
   for (auto itr = start; itr < end; ++itr)
      sum += *itr;

   *result = sum;

   // 쓰레드의 id를 구한다.
   thread::id this_id = std::this_thread::get_id();
   // printf()는 출력 중 다른 쓰레드가 출력하지 못하게막는다.
   // std::cout은 << 마다 다른 쓰레드가 출력권을 가져감
   printf("쓰레드 %x 에서 %d 부터 %d 까지 계산한 결과 : %d \n", this_id, *start, *(end - 1), sum);
}

// int main() {
//    vector<int> data(10000);
//    for (int i = 0; i < 10000; i++)
//       data[i] = i;

//    vector<int> partial_sums(4);

//    vector<thread> workers;
//    for (int i = 0; i < 4; i++)
//       workers.push_back(thread(worker, data.begin() + i * 2500, data.begin() + (i + 1) * 2500, &partial_sums[i]));

//    for (int i = 0; i < 4; i++)
//       workers[i].join();

//    int total = 0;
//    for (int i = 0; i < 4; i++)
//       total += partial_sums[i];

//    std::cout << "전체 합: " << total << std::endl;
// }


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// 쓰레드들의 변수 동시 접근 실험
void workeri(int& counter) {
   for (int i = 0; i < 10000; i++)
      counter += 1;
}

int main() {
   int counter = 0;

   vector<thread> workers;
   for (int i = 0; i < 4; i++)
      workers.push_back(thread(workeri, std::ref(counter)));

   for (int i = 0; i < 4; i++)
      workers[i].join();

   std::cout << "Counter 최종 값: " << counter << std::endl;
}