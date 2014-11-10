#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>


std::vector<int> inputArray;
std::vector<int> outputArray;

bool ReadInputFile(const std::string &filePath)
{
    try {
        std::ifstream fin(filePath.c_str());
        inputArray.clear();
        outputArray.clear();
        while (!fin.eof())
        {
            int tampVal = -1;
            fin>>tampVal;
            if (tampVal>0)
                inputArray.push_back(tampVal);
        }
        std::cout<<"Num:"<<inputArray.size()<<std::endl;
    }
    catch (const std::exception &e){
        std::cerr<<e.what()<<std::endl;
        return false;
    }
    return true;
}

unsigned int count_split_inv(const std::vector<int> &inputArray1,const std::vector<int> &inputArray2,std::vector<int> &outputArray)
{
    outputArray.resize(inputArray1.size()+inputArray2.size(),0);
    int i=0,j=0;
    unsigned int inv_count=0;
    for (int k=0;k<outputArray.size();++k)
    {
        //inputArray2 is done
        if (j==inputArray2.size())
        {
            std::copy(inputArray1.begin()+i,inputArray1.end(),outputArray.begin()+k);
            break;
        }
        //inputArray1 is done
        else if (i==inputArray1.size())
        {
            std::copy(inputArray2.begin()+j,inputArray2.end(),outputArray.begin()+k);
            inv_count += (inputArray1.size()-i);
            break;
        }


        if (inputArray1[i]<inputArray2[j])
        {
            outputArray[k] = inputArray1[i];
            ++i;
        }
        else
        {
            outputArray[k] = inputArray2[j];
            ++j;
            inv_count += inputArray1.size()-i;
        }
    }
    return inv_count;
}


unsigned int sort_and_count(const std::vector<int> &inputArray,std::vector<int> &outputArray)
{
    if (inputArray.size()==1)
    {
        outputArray = inputArray;
        return 0;
    }

    size_t half = inputArray.size()/2;
    std::vector<int> output1,output2;
    unsigned int x = sort_and_count(std::vector<int>(inputArray.begin(),inputArray.begin()+half),output1);
    unsigned int y = sort_and_count(std::vector<int>(inputArray.begin()+half,inputArray.end()),output2);

    unsigned int z = count_split_inv(output1,output2,outputArray);
    return x+y+z;
}

unsigned int Brute(const std::vector<int> &inputArray)
{
    unsigned int count = 0;
    for (int i=0;i<inputArray.size();++i)
    {
        for (int j=i+1;j<inputArray.size();++j)
        {
            if (inputArray[i]>inputArray[j])
                count ++;
        }
    }
    return count;
}

int main(int argc,char** argv)
{
    //Check arguments
    if (argc<=1)
    {
        std::cerr<<"Params invalid!"<<std::endl;
        return 0;
    }

    //ReadFile
    if (ReadInputFile(argv[1])==false)
    {
        std::cerr<<"Read file failed!"<<std::endl;
        return 0;
    }

    //Merge and get inversions' number
    clock_t t1 = clock();
    unsigned int count = sort_and_count(inputArray,outputArray);
    clock_t t2 = clock();
    std::cout<<"Merge_and_count:"<<count<<"\tcost time "<<static_cast<double>(t2-t1)/CLOCKS_PER_SEC<<"s"<<std::endl;

    //Brute
    clock_t t3 = clock();
    count = Brute(inputArray);
    clock_t t4 = clock();
    std::cout<<"Brute:"<<count<<"\tcost time "<<static_cast<double>(t4-t3)/CLOCKS_PER_SEC<<"s"<<std::endl;

    return 0;
}

