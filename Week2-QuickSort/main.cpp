#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

std::vector<int> inputArray;
typedef int (*CHOOSE_PIVOT)(std::vector<int> &array,int begin,int end);

void PrintVector(const std::vector<int> &array)
{
    std::cout<<"[";
    for(std::vector<int>::const_iterator iter = array.begin();iter!=array.end();++iter)
    {
        std::cout<<*iter<<",";
    }
    std::cout<<"]"<<std::endl;
}
bool ReadInputFile(const char* path)
{
    inputArray.clear();
    std::ifstream fin(path);
    if (fin.bad())
    {
        std::cerr<<"Read file failed!"<<std::endl;
        return false;
    }

    while(!fin.eof())
    {
        int i = -1;
        fin>>i;
        if (i>0) inputArray.push_back(i);
    }

    std::cout<<"Input array's size is :"<<inputArray.size()<<std::endl;
    return true;
}

void swap(std::vector<int> &array,int i,int j)
{
    if (i!=j)
    {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int ChooseFisrtAsPivot(std::vector<int> &array,int begin,int end)
{
    return array[begin];
}

int ChooseLastAsPivot(std::vector<int> &array,int begin,int end)
{
    swap(array,begin,end-1);
    return array[begin];
}

int ChooseMedianAsPivot(std::vector<int> &array,int begin,int end)
{
    int size = end-begin;
    if (size<=1)
        return array[begin];

    int half = (begin+end-1)/2;
    std::vector<int> candidates;
    candidates.push_back(array[begin]);
    candidates.push_back(array[end -1]);
    candidates.push_back(array[half]);

    if (std::max_element(candidates.begin(),candidates.end())==candidates.begin())
    {
        candidates.erase(candidates.begin());
        if (std::max_element(candidates.begin(),candidates.end())==candidates.begin())
        {
            swap(array,begin,end-1);
        }
        else
            swap(array,begin,half);
    }
    else if (std::min_element(candidates.begin(),candidates.end())==candidates.begin())
    {
        candidates.erase(candidates.begin());
        if (std::min_element(candidates.begin(),candidates.end())==candidates.begin())
        {
            swap(array,begin,end-1);
        }
        else
            swap(array,begin,half);
    }
    return array[begin];
}

size_t QuickSort(std::vector<int> &array,int begin,int end,CHOOSE_PIVOT choose_pivot_func)
{
    if (end-begin<=1)
        return 0;

    //Get pivot
    int pivot = choose_pivot_func(array,begin,end);

    //Partitioning
    int i=begin+1;
    for (int j=begin+1;j<end;++j)
    {
        if (array[j]<pivot)
        {
            swap(array,i,j);
            ++i;
        }
    }
    swap(array,begin,i-1);

    //Recursive
    size_t count1 = QuickSort(array,begin,i-1,choose_pivot_func);
    size_t count2 = QuickSort(array,i,end,choose_pivot_func);
    return count1 + count2 + end-begin-1;
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

    std::vector<int> array1(inputArray);
    std::vector<int> array2(inputArray);
    std::vector<int> array3(inputArray);

    //QuickSort: choose the fisrt one as pivot
    clock_t t1 = clock();
    std::cout<<QuickSort(array1,0,array1.size(),ChooseFisrtAsPivot)<<std::endl;
    clock_t t2 = clock();
    //QuickSort: choose the last one as pivot
    std::cout<<QuickSort(array2,0,array2.size(),ChooseLastAsPivot)<<std::endl;
    clock_t t3 = clock();
    //QuickSort: choose the median one as pivot
    std::cout<<QuickSort(array3,0,array3.size(),ChooseMedianAsPivot)<<std::endl;
    clock_t t4 = clock();

//    PrintVector(array3);
    std::cout<<"choose the fisrt one as pivot:"<<static_cast<double>(t2-t1)/CLOCKS_PER_SEC<<"s"<<std::endl;
    std::cout<<"choose the last one as pivot:"<<static_cast<double>(t3-t2)/CLOCKS_PER_SEC<<"s"<<std::endl;
    std::cout<<"choose the median one as pivot:"<<static_cast<double>(t4-t3)/CLOCKS_PER_SEC<<"s"<<std::endl;
    return 0;
}

