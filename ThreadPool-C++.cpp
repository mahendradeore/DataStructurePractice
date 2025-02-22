#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>
using namespace std;

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