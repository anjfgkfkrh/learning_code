#include <future>
#include <iostream>
#include <string>
#include <thread>
using std::string;

// 기본적인 사용법
// void worker(std::promise<string>* p) {
//    // 약속을 이행하는 모습. 해당 결과는 future에 들어간다.
//    p->set_value("some data");
// }
// int main() {
//    std::promise<string> p;

//    // 미래에 string 데이터를 돌려주겠다는 약속.
//    std::future<string> data = p.get_future();

//    std::thread t(worker, &p);

//    //미래에 약속된 데이터를 받을 때 까지 기다린다.
//    data.wait();

//    // wait이 리턴했다는 뜻이 future 에 데이터가 준비되었다는 의미.
//    // 참고로 wait 없이 그냥 get 해도 wait 한 것 과 같다.
//    std::cout << "받은 데이터: " << data.get() << std::endl;

//    t.join();
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// promise-future 패턴

// conditon_variable mutex 사용
#include <condition_variable>
#include <mutex>

// std::condition_variable cv;
// std::mutex m;
// bool done = false;
// std::string info;

// void worker() {
//    {
//       std::lock_guard<std::mutex> lk(m);
//       info = "some data";   // 위의 p->set_value("some data")에 대응
//       done = true;
//    }
//    cv.notify_all();
// }

// int main() {
//    std::thread t(worker);

//    std::unique_lock<std::mutex> lk(m);
//    cv.wait(lk, [] {return done;});
//    lk.unlock();

//    std::cout << "받은 데이터 : " << info << std::endl;

//    t.join();
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 예외 전달
#include <exception>

// void worker(std::promise<string>* p) {
//    try {
//       throw std::runtime_error("Some Error!");
//    }
//    catch (...) {
//       // set_exception 에는 exception_ptr를 전달해야 한다.
//       p->set_exception(std::current_exception());
//    }
// }

// int main() {
//    std::promise<string> p;

//    // 미래에 string 데이터를 돌려 주겠다는 약속.
//    std::future<string> data = p.get_future();

//    std::thread t(worker, &p);

//    // 미래에 약속된 데이터를 받을 때 까지 기다린다.
//    data.wait(); // 없어도 됨 data.get()이 wait()역할을 할 수 있음

//    try {
//       data.get();
//    }
//    catch (const std::exception& e) {
//       std::cout << "예외: " << e.what() << std::endl;
//    }
//    t.join();
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// wait_for()
#include <chrono>

// void worker(std::promise<void>* p) {
//    std::this_thread::sleep_for(std::chrono::seconds(10));
//    p->set_value();
// }

// int main() {
//    // void의 경우 어떠한 객체도 전달하지 않지만, future가 set이 되었냐
//    // 안되었느냐의 유무로 마치 플래그의 역할을 수행할 수 있습니다.
//    std::promise<void> p;

//    // 미래에 string 데이터를 돌려 주겠다는 약속

//    std::future<void> data = p.get_future();

//    std::thread t(worker, &p);
//    // 미래에 약속된 데이터를 받을 때 까지 기다린다.
//    while (true) {
//       std::future_status status = data.wait_for(std::chrono::seconds(1));

//       // 아직 준비가 안됨
//       if (status == std::future_status::timeout)
//          std::cerr << ">";

//       // promise가 future를 설정항.
//       else if (status == std::future_status::ready)
//          break;
//    }
//    t.join();
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
using std::thread;

// void runner(std::shared_future<void>* start) {
//    start->get();
//    std::cout << "출발" << std::endl;
// }

// int main() {
//    std::promise<void> p;
//    std::shared_future<void> start = p.get_future();

//    thread t1(runner, &start);
//    thread t2(runner, &start);
//    thread t3(runner, &start);
//    thread t4(runner, &start);

//    //참고로 cerr는 std::cout 과는 다르게 버퍼를 사용하지 않기 때문에 터미널에 바로 출력된다.
//    std::cerr << "준비...";
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::cerr << "땅!" << std::endl;

//    p.set_value();

//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* packaged_task */
// 쓰레드에 promise를 전달하지 않아도 됨
// 람다 함수형태로 비동기 실행 가능

// int some_task(int x) { return 10 + x; }

// int main() {
//    // int(int) : int 를 리턴하고 인자로 int를 받는 함수. (std::function 참조) 
//    std::packaged_task<int(int, int)> task([](int x, int y) {return 10 + x + y;});

//    std::future<int> start = task.get_future();

//    thread t(std::move(task), 5, 5);

//    std::cout << "결과값: " << start.get() << std::endl;
//    t.join();
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* async */
// 쓰레드를 직접 만들지 않아도 됨

// // std::accumulate 와 동일
// int sum(const std::vector<int>& v, int start, int end) {
//    int total = 0;
//    for (int i = start; i < end; ++i)
//       total += v[i];

//    return total;
// }

// int parallel_sum(const std::vector<int>& v) {
//    //lower_half_future 는 1~500 까지 비동기적으로 더함
//    // 참고로 람다 함수를 사용하면 좀 더 깔끔하게 표현할 수 도 있다.
//    // --> std::async([&v]() { return sum(v, 0, v.size() / 2); });
//    // std::future<int> lower_half_future = std::async(std::launch::async, sum, cref(v), 0, v.size() / 2);

//    std::future<int> a0 = std::async([&v]() { return sum(v, 0, v.size() / 10); });
//    std::future<int> a1 = std::async([&v]() { return sum(v, v.size() / 10, v.size() / 10 * 2); });
//    std::future<int> a2 = std::async([&v]() { return sum(v, v.size() / 10 * 2, v.size() / 10 * 3); });
//    std::future<int> a3 = std::async([&v]() { return sum(v, v.size() / 10 * 3, v.size() / 10 * 4); });
//    std::future<int> a4 = std::async([&v]() { return sum(v, v.size() / 10 * 4, v.size() / 10 * 5); });
//    std::future<int> a5 = std::async([&v]() { return sum(v, v.size() / 10 * 5, v.size() / 10 * 6); });
//    std::future<int> a6 = std::async([&v]() { return sum(v, v.size() / 10 * 6, v.size() / 10 * 7); });
//    std::future<int> a7 = std::async([&v]() { return sum(v, v.size() / 10 * 7, v.size() / 10 * 8); });
//    std::future<int> a8 = std::async([&v]() { return sum(v, v.size() / 10 * 8, v.size() / 10 * 9); });
//    int a9 = sum(v, v.size() / 10 * 9, v.size());

//    //upper_half 는 501 부터 1000까지 더함
//    // int upper_half = sum(v, v.size() / 2, v.size());

//    return a0.get() + a1.get() + a2.get() + a3.get() + a4.get() + a5.get() + a6.get() + a7.get() + a8.get() + a9;
// }

// int main() {
//    std::vector<int> v;
//    v.reserve(1000);
//    for (int i = 0; i < 1000; ++i)
//       v.push_back(i + 1);

//    std::cout << "1부터 1000까지의 합: " << parallel_sum(v) << std::endl;
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// async2

int do_work(int x) {
   // x를 가지고 무슨 일을 한다.
   std::this_thread::sleep_for(std::chrono::seconds(3));
   return x;
}

void do_work_parallel() {
   auto f1 = std::async([]() {do_work(3);});
   auto f2 = std::async([]() {do_work(3);});
   do_work(3);

   f1.get();
   f2.get();
}

void do_work_sequential() {
   do_work(3);
   do_work(3);
   do_work(3);
}

int main() {
   // do_work_parallel(); 
   do_work_sequential();
}