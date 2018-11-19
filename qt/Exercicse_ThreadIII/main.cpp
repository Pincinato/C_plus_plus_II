#include <iostream>
#include <random>
#include <algorithm>
#include <thread>
#include <future>
#include <vector>
#include <chrono>

using namespace std;

int calcStats(int nbrElelements);

int main()
{
    cout << "Hello World!" << endl;
    //Record s t a r t time
    auto start = std::chrono::high_resolution_clock::now();
    int nbrElements = 1000000;
    int nbrThreads = thread::hardware_concurrency();
    vector<future<int>> myfutures;
    for (int i=0;i<nbrThreads;i++){
        myfutures.push_back(async(launch::async,calcStats,nbrElements));//emplce_back;
    }
    for( auto &it :myfutures ){
        //if(it.valid())
        cout<<endl<<100*it.get()/nbrElements<<"%  "<<endl;
    }
    // Record end time
    auto finish = std::chrono::high_resolution_clock::now();
    cout << "Elapsed time: "<< (finish-start).count()*1e-9 <<
    endl;
}

int calcStats(int nbrElelements)
 {
 vector<int> d(nbrElelements);
 random_device r;
 mt19937 gen{r()};
 uniform_int_distribution<int> dis(1, nbrElelements);
 auto rand_num ([=] () mutable { return dis(gen); });
 generate(d.begin(), end(d), rand_num);
 return count_if(begin(d), end(d), [&nbrElelements](int val){return val > nbrElelements/2;});
}
