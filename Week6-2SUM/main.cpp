#include <assert.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
//#include <QSet>

template<typename T>
int compute2SUM(const std::set<T> &array,T minSum,T maxSum,bool showProgress = false)
{
    static int count = 0;
    count ++;

    std::clock_t start = std::clock();

    int result = 0;
    for (T sum = minSum;sum<=maxSum;++sum)
    {
        for (std::set<T>::iterator iter = array.begin();iter!=array.end();++iter)
        {
            T anotherAdder = sum-(*iter);
            std::set<T>::iterator iterFind = array.find(anotherAdder);
            if (iterFind!=array.end() && *iter<*iterFind )
            {
//                std::cout<<*iter<<"+"<<*iterFind<<"="<<sum<<std::endl;
                ++result;
                break;
            }
        }
        std::cout<<sum<<"\t";
    }

    std::clock_t end = std::clock();
    std::cout<<"\nIt's "<<count<<"th example which cost time "<<static_cast<double>(end-start)/CLOCKS_PER_SEC<<"s. Input array's count is "<<array.size()<<". Result is "<<result<<std::endl;
    return result;
}

int main(int argc,char**argv)
{
    //Test 1
    {
        int array[] = {3,5,7,2,9};
        std::set<int> testVector(array,array+sizeof(array)/sizeof(array[0]));
        int result = compute2SUM(testVector,0,100);
        assert(result==9);
    }

    //Test 2
    {
        long long array[] = {3,5,7,2,9};
        std::set<long long> testVector(array,array+sizeof(array)/sizeof(array[0]));
        int result = compute2SUM(testVector,0LL,100LL);
        assert(result==9);
    }

    //Test 3
    {
        long long array[] = {3,5,7,2,9};
        std::set<long long> testVector(array,array+sizeof(array)/sizeof(array[0]));
        int result = compute2SUM(testVector,10LL,20LL);
        assert(result==5);
    }

    //Read File
    {
        try{
            if(argc<2)
                throw std::invalid_argument("Params error!");

            std::ifstream fin(argv[1]);
            if (fin.bad())
                throw std::ios_base::failure("Open file failed!");

            std::vector<long long> inputArray;
            std::copy(std::istream_iterator<long long>(fin),std::istream_iterator<long long>(),std::back_inserter(inputArray));
            fin.close();
            assert(inputArray.size()==1000000);

            int result = compute2SUM(std::set<long long>(inputArray.begin(),inputArray.end()),-10000LL,10000LL);
        }
        catch(const std::exception& e){
            std::cerr<<e.what()<<std::endl;
            return 0;
        }
    }

    return 0;
}

