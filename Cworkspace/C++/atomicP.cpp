#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
// mutex를 사용 안하고 여러 스레드에서 한 변수에 오류없이 접근 가능
// 때문에 mutex보다 속도가 빠름
// void worker(std::atomic<int>& counter) {
//    for (int i = 0; i < 10000; i++)
//       counter++;
// }

// int main() {
//    // 해당 변수는 동시에 하나의 스레드만 접근 가능함
//    std::atomic<int> counter(0);

//    std::vector<std::thread> workers;
//    for (int i = 0; i < 4; i++)
//       workers.push_back(std::thread(worker, ref(counter)));

//    for (int i = 0; i < 4; i++)
//       workers[i].join();
//    //흠.... 적응좀 해야할 듯 특히 백스페이스가 아직 위로가네
//    // 옆으로 가야되는데 ㅋㅋㅋㅋ 자꾸 위로감 ㅋ
//    std::cout << "Counter 최종 값: " << counter << std::endl;
// }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/*memory order relexed*/
// 메모리에서 읽거나 쓸 경우, 주위의 다른 메모리 접근들과 순서가 바뀌어도 무방함.

using std::memory_order_relaxed;

// void t1(std::atomic<int>* a, std::atomic<int>* b) {
//    b->store(1, memory_order_relaxed);         // b = 1(쓰기)
//    int x = a->load(memory_order_relaxed);  // x = a(읽기)

//    printf("x : %d\n", x);
// }

// void t2(std::atomic<int>* a, std::atomic<int>* b) {
//    a->store(1, memory_order_relaxed);
//    int y = b->load(memory_order_relaxed);

//    printf("y : %d\n", y);
// }

// int main() {
//    std::vector<std::thread> threads;
//    std::atomic<int> a(0);
//    std::atomic<int> b(0);

//    threads.push_back(std::thread(t1, &a, &b));
//    threads.push_back(std::thread(t2, &a, &b));

//    for (int i = 0; i < 2; i++)
//       threads[i].join();
// }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// void worker(std::atomic<int>* counter) {
//    for (int i = 0; i < 10000; i++) {
//       // 다른 연산들 수행

//       counter->fetch_add(1, memory_order_relaxed);
//    }
// }

// int main() {
//    std::vector<std::thread> threads;
//    std::atomic<int> counter(0);

//    for (int i = 0; i < 4; i++)
//       threads.push_back(std::thread(worker, &counter));

//    for (int i = 0; i < 4; i++)
//       threads[i].join();

//    std::cout << "Counter : " << counter << std::endl;
// }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// memory order relaxed 문제
// data의 값이 0이 나올수 도 있음
// void producer(std::atomic<bool>* is_ready, int* data) {
//    // 단일 스레드 결과 상 아래 두줄이 바뀌어도 상관 없기에 
//    // 아래의 코드는 실행 순서가 바뀔 수도 있다.
//    *data = 10;
//    // is_ready->store(true, memory_order_relaxed);
//    is_ready->store(true, std::memory_order_release); // 이전의 모든 메모리 명령들이 아래로 재배치 못함
// }

// void consumer(std::atomic<bool>* is_ready, int* data) {
//    //data 가 준비될 때 까지 기다린다.
//    // while (!is_ready->load(memory_order_relaxed)) {}
//    while (!is_ready->load(std::memory_order_acquire)) {} // 이후의 모든 메모리 명령들이 위로 재배치 못함

//    std::cout << "Data : " << *data << std::endl;
// }

// int main() {
//    std::vector<std::thread> threads;

//    std::atomic<bool> is_ready(false);
//    int data = 0;

//    threads.push_back(std::thread(producer, &is_ready, &data));
//    threads.push_back(std::thread(consumer, &is_ready, &data));

//    for (int i = 0; i < 2; i++)
//       threads[i].join();

// }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// memory_order_release 해당 코드 위에 있는 모든 메모리 명령들이 해당 코드 아래에 재배치 못함
// memory_order_acquire 해당 코드 아레에 있는 모든 메모리 명령들이 해당 코드 위로 재배치 못함

// std::atomic<bool> is_ready;
// std::atomic<int> data[3];

// void producer() {
//    data[0].store(1, memory_order_relaxed);
//    data[1].store(2, memory_order_relaxed);
//    data[2].store(3, memory_order_relaxed);
//    is_ready.store(true, std::memory_order_release);
// }

// void consumer() {
//    // data가 준비될 때 까지 기다린다.
//    while (!is_ready.load(std::memory_order_acquire)) {}

//    std::cout << "data[0] : " << data[0].load(memory_order_relaxed) << std::endl;
//    std::cout << "data[1] : " << data[1].load(memory_order_relaxed) << std::endl;
//    std::cout << "data[2] : " << data[2].load(memory_order_relaxed) << std::endl;
// }

// int main() {
//    std::vector<std::thread> threads;

//    threads.push_back(std::thread(producer));
//    threads.push_back(std::thread(consumer));

//    for (int i = 0; i < 2; i++)
//       threads[i].join();
// }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// memory_order_acq_rel release와 acquire의 역할을 동시에 수행한다
// memory_order_seq_cst 메모리 명령의 순차적 일관성을 보장한다

// std::atomic<bool> x(false);
// std::atomic<bool> y(false);
// std::atomic<int> z(0);

// void write_x() { x.store(true, std::memory_order_release); }
// void write_y() { y.store(true, std::memory_order_release); }

// void read_x_then_y() {
//    while (!x.load(std::memory_order_acquire)) {}

//    if (y.load(std::memory_order_acquire))
//       ++z;
// }

// void read_y_then_x() {
//    while (!y.load(std::memory_order_acquire)) {}

//    if (x.load(std::memory_order_acquire))
//       ++z;
// }

// int main() {
//    std::thread a(write_x);
//    std::thread b(write_y);
//    std::thread c(read_x_then_y);
//    std::thread d(read_y_then_x);
//    a.join();
//    b.join();
//    c.join();
//    d.join();
//    std::cout << "z : " << z << std::endl;
// }

using std::memory_order_seq_cst; // 해당 변수를 기준으로 다른 변수들을 옮겨다니지 못함
// ex)
// a = 10;
// b = 20;
// c.store(30, memory_order_seq_cst);
// a 와 b는 서로 순서가 바뀔 수 있으나
// c 아래로는 못내려감

// std::atomic<bool> x(false);
// std::atomic<bool> y(false);
// std::atomic<int> z(0);

// void write_x() { x.store(true, memory_order_seq_cst); }
// void write_y() { y.store(true, memory_order_seq_cst); }

// void read_x_then_y() {
//    while (!x.load(memory_order_seq_cst)) {}
//    if (y.load(memory_order_seq_cst))
//       ++z;
// }

// void read_y_then_x() {
//    while (!y.load(memory_order_seq_cst)) {}
//    if (x.load(memory_order_seq_cst))
//       ++z;
// }

// int main() {
//    std::thread a(write_x);
//    std::thread b(write_y);
//    std::thread c(read_x_then_y);
//    std::thread d(read_y_then_x);

//    a.join();
//    b.join();
//    c.join();
//    d.join();

//    std::cout << "Z : " << z << std::endl;
// }

//////////////////////////////////////////////////////////////
/* 생각해보기 문제 */
// atomic<bool> 사용해서 lock unlock 구현하기

// bool compare_exchange_strong( T& expected, T desired, std::memory_order order = std::memory_order_seq_cst);
// 사용하면 편함
// 만일 현재 atomic 객체의 값이 expected와 같다면 desired로 바꾸고 true를 리턴
// expected와 다르다면 desired로 바꾸지 않고 그냥 false를 리턴

void t1(int& a, std::atomic<bool>& lock) {
   std::cout << "t1 : " << a << std::endl;

   bool is_lock = false;
   while (lock.compare_exchange_strong(is_lock, true)) {}
   std::cout << "t1 lock" << std::endl;

   a = 10;

   std::cout << "t1 unlock" << std::endl;
   lock.store(false, memory_order_seq_cst);
}
void t2(int& a, std::atomic<bool>& lock) {
   std::cout << "t2 : " << a << std::endl;

   bool is_lock = false;
   while (lock.compare_exchange_strong(is_lock, true)) {};
   std::cout << "t2 lock" << std::endl;

   a = 20;

   std::cout << "t2 unlock" << std::endl;
   lock.store(false, std::memory_order_seq_cst);
}

int main() {
   std::atomic<bool> lock(false);
   int a = 0;

   std::thread c(t1, std::ref(a), std::ref(lock));
   std::thread b(t2, std::ref(a), std::ref(lock));
   c.join();
   b.join();

   std::cout << "final : " << a << std::endl;
}