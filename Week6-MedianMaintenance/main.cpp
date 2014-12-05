#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

int median(std::vector<int> &array)
{
    size_t index = array.size()%2==0?array.size()/2-1:array.size()/2;
    std::nth_element(array.begin(),array.begin()+index,array.end());
    return array[index];
}

int main(int argc,char**argv)
{
    //Test 1
//    {
//        int myints[] = {10,20,30,5,15};

//        for (int i=1;i<=5;++i)
//        {
//            int result = median(std::vector<int>(myints,myints+i));
//            std::cout<<"i="<<i<<" result="<<result<<std::endl;
//        }
//    }

    try{
        if (argc<2)
            throw std::invalid_argument("Params error!");

        std::ifstream fin(argv[1]);
        if (fin.bad())
            throw std::ios_base::failure("Open file failed!");

        std::vector<int> array;
        int sum = 0;
        for(std::istream_iterator<int> iter = std::istream_iterator<int>(fin);iter!=std::istream_iterator<int>();++iter)
        {
            array.push_back(*iter);
            int m = median(array);
            sum = (sum+m)%10000;
        }
        std::cout<<sum<<std::endl;
        std::cout<<array.size()<<std::endl;

        fin.close();
    }
    catch(const std::exception &e)
    {
        std::cerr<<e.what()<<std::endl;
        return 0;
    }
    return 0;
}
