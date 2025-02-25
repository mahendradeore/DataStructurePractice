#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>
using namespace std;
/*
ThreadPool Class Implementation few take aways in C++
Need headers for thread, mutex, condition_variable, queue, functional, chrono
1. std::mutex is used to protect shared data from
   being simultaneously accessed by multiple threads.
2. std::condition_variable is used to block a thread until notified to wake.
3. std::queue is used to store the tasks that need to be executed.
4. std::function is used to store the tasks that need to be 
5. used vector to create thread pool
6. using emplace_back to create thread pool used lambda function to create thread
7. used unique_lock and condition_variable to block thread until notified
8. used lock_guard to lock the mutex
6. used unordered_map to store thread id and thread number
7. used notify_one to notify one thread to wake up  
8. used notify_all to notify all threads to wake up
9. used join to join all threads
10. used sleep_for to sleep thread for some time
11. used lambda function to send function to thread pool
12. used destructor to join all threads and stop all threads    

in lamda functipn [] is used to capture the surrounding variables
in lamda function we can pass the arguments to function
in lamda function we can return the value from function
in lamda function we can use the return type of function
in lamda function we can use the return type of function
in lamda function we can use the return type of function
syntax of lamda function is [capture](parameters)->return_type{body}
in lamda function we can use the return type of function
example of lamda function is
auto f = [](int x, int y)  int { return x + y; };
with surrounding variables
int x = 10;
auto f = [x](int y) -> int { return x + y; };
with return type

direct use as argumnt   
explain emplace and lambda function
emplace_back is used to create thread pool  how signature of lambda function is used
how to use lamda function in thread pool
how to use lamda function in thread pool    
as below with signature and used 
std::this_thread 





*/ 

class ThreadPool {

    std::mutex mtx;
    std::condition_variable cv;
    //C++ provides provision for std::fucntion to assign function
    std::queue<std::function<void(int)>> task;
    int size;
    std::vector<std::thread> pool;
    bool stop;
    std::unordered_map<std::thread::id, int> threadIDs;  
    public:
    ThreadPool(int threadsize);
    void enque(std::function<void(int)> task);
    void threadFunction(int id);
    ~ThreadPool();
    
};

ThreadPool::~ThreadPool(){
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto & th : pool){
             th.join();
        }
    }
void ThreadPool::threadFunction(int id){
        while(true){
            std::function<void(int)> tk;
            {
             std::cout << "In thread "<< id << std::endl;
            //conditional variable can only used with unique_lock
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock,[this] { return ! task.empty() || stop;});
            //get tasks from task queue front/
              if (stop && task.empty()) 
           return;  // Stop if no tasks remain
                tk = task.front();
             //remove task from queue list
             task.pop();
           
        
             std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            //execute task
            tk(id);
        }
    
}
 

ThreadPool::ThreadPool(int numofthreads):stop(false){

    for(int i =0 ;i < numofthreads; i++){
        //wecan call this thread as this or 
        //pool.emplace_back(std::thread(&ThreadPool::threadFunction,this,i));
        //like this 
       pool.emplace_back( [this,i] { threadIDs[std::this_thread::get_id()] = i;
       threadFunction(i);
       });
        
        
    }
}
void ThreadPool::enque(std::function<void(int)> f){
    {
        std::lock_guard<std::mutex> lock(mtx);
        task.push(f);
    }
    cv.notify_one();
}

int main(){
    
    ThreadPool pool(5);
    
    // for(int i = 0 ; i < 10; i++){
    //     //calling enque function. using lamda function sending function
    //     pool.enque([i](int id){
    //         std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //         std::cout << "Task " << i << " executed by thread " << id << "\n";
    //     });
    // }
    int i = 0;
    while (true) {
        pool.enque([i](int threadID) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Task " << i << " executed by Thread " << threadID << "\n";
        });

        i++; // Increment task ID
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Simulate task arrival delay
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(4)); 
    
}