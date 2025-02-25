#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include <mutex>    
#include <condition_variable>
#include <sstream>

// Types of File Streams in C++
// ifstream (Input File Stream)

// Used for reading from files.
// Example: std::ifstream file("input.txt");
// ofstream (Output File Stream)

// Used for writing to files.
// Example: std::ofstream file("output.txt");
// fstream (File Stream)

// Used for both reading and writing.
// Example: std::fstream file("data.txt", std::ios::in | std::ios::out);
// using namespace std;
// //std::ifsteam used to read from file
// int wordcount = 0;
// std::mutex mtx;
// Common File Open Modes (std::ios::)
// Mode	Description
// std::ios::in	Open file for reading.
// std::ios::out	Open file for writing (overwrites existing content).
// std::ios::app	Open file in append mode (writes at the end).
// std::ios::ate	Open file and move to the end.
// std::ios::binary	Open file in binary mode.
// std::ios::trunc	Truncate file (clear existing content before writing).
// std::ios::nocreate	Open file only if it exists.
// std::ios::noreplace	Open file only if it doesn't exist.


void thread_search(int i, std::string chunk, std::string str){
    int count = 0;
    std::stringstream ss(chunk);
    std::string token;
    while(ss >> token){
        if(token == str){
            count++;
        }
    }
    std::lock_guard<std::mutex> lock(mtx);
     wordcount+= count;
    
    std::cout << "Thread " << i << " found " << count << " occurences of " << str << std::endl;
}

void processFile(std::string &filename, std::string &str, int &numofthreads){

    std::ifstream file(filename);
    //std::ifstream file(file,ios::in,ios::ate);

    if(!file.is_open()){
        std::cout << "File not found" << std::endl;
        return;
    }
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    std::cout << "File size: " << file_size << std::endl;

    file.seekg(0, ios::beg);

    //read complete file
    std::string file_content;
   //std::string file_content(isreambuf_iterator<char>(file), {});
    file_content.resize(file_size); 
    file.read(&file_content[0], file_size);

    int chunk_size = file_size/numofthreads;

    std::vector<thread> threads;
    for(int i = 0; i< numofthreads; i++){
        int start = i*chunk_size;
        int end = (i+1)*chunk_size;
        if(i == numofthreads - 1){
            end = file_size;
        }
        std::string chunk = file_content.substr(start, end-start);
        threads.emplace_back([i,chunk,str]{thread_search(i,chunk,str);});
    }

}
int main(){

    std::string str("india");

    std::string filename("C:\\Users\\iMandy\\Desktop\\file.txt");
    int numofthreads = 4;
    processFile(filename, str , numofthreads);
    return 0;
}