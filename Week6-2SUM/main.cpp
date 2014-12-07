#include <assert.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <hash_set>
#include <QSet>

struct Node
{
    int val;
    Node *next;
    Node(int n)
    {
        this->val = n;
        this->next = NULL;
    }
};
class hash_table
{
public:
    hash_table(const int ntablesize);
    ~hash_table();
    bool insert(int n);
    void insert(int *pFirst, int *pLast);
    bool find(int n);
    int  size();
    int HashFun(int n);
public:
    int      m_nTableSize;
    int      m_nTableDataCount;
    Node**   m_ppTable;
};

hash_table::hash_table(const int ntablesize)
{
    m_nTableSize = ntablesize;
    m_ppTable = (Node**)malloc(sizeof(Node*) * m_nTableSize);
    if (m_ppTable == NULL)
        return ;
    m_nTableDataCount = 0;
    memset(m_ppTable, 0, sizeof(Node*) * m_nTableSize);
}
hash_table::~hash_table()
{
    free(m_ppTable);
    m_ppTable = NULL;
    m_nTableDataCount = 0;
    m_nTableSize = 0;
}
int inline hash_table::HashFun(int n)
{
    return (n ^ 0xdeadbeef) % m_nTableSize;
}
int hash_table::size()
{
    return m_nTableDataCount;
}
bool hash_table::insert(int n)
{
    int key = HashFun(n);
    //在该链表中查找该数是否已经存在
    for (Node *p = m_ppTable[key]; p != NULL; p = p->next)
        if (p->val == n)
            return true;
    //在链表的头部插入
    Node *pNode = new Node(n);
    if (pNode == NULL)
        return false;
    pNode->next = m_ppTable[key];
    m_ppTable[key] = pNode;
    m_nTableDataCount++;
    return true;
}
bool hash_table::find(int n)
{
    int key = HashFun(n);
    for (Node *pNode = m_ppTable[key]; pNode != NULL; pNode = pNode->next)
        if (pNode->val == n)
            return true;
    return false;
}
void hash_table::insert(int *pFirst, int *pLast)
{
    for (int *p = pFirst; p != pLast; p++)
        this->insert(*p);
}


template<typename T>
int compute2SUM(const std::vector<T> &array,T minSum,T maxSum,bool showProgress = false)
{
    static int count = 0;
    count ++;

    std::clock_t start = std::clock();

//    std::hash_set<int> result;
//    std::set<int> result;
    QSet<int> result;
//    hash_table result(array.size());
    int index = 0;
    for(std::vector<T>::const_iterator i = array.begin();i!=array.end();++i)
    {
        for(std::vector<T>::const_iterator j = i;j!=array.end();++j)
        {
            if (i!=j)
            {
                int sum = *i + *j;
                if (sum<=maxSum && sum>=minSum)
                {
                    result.insert(sum);
                }
            }
        }
        index++;
        if (index%1000==0)
            std::cout<<index<<" left:"<<static_cast<double>(std::clock()-start)*array.size()/index/CLOCKS_PER_SEC<<std::endl;
    }

    std::clock_t end = std::clock();
    std::cout<<"\nIt's "<<count<<"th example which cost time "<<static_cast<double>(end-start)/CLOCKS_PER_SEC<<"s. Input array's count is "<<array.size()<<". Result is "<<result.size()<<std::endl;
    return result.size();
}

int main(int argc,char**argv)
{
    //Test 1
    {
        int array[] = {3,5,7,2,9};
        std::vector<int> testVector(array,array+sizeof(array)/sizeof(array[0]));
        int result = compute2SUM(testVector,0,100);
        assert(result==9);
    }

    //Test 2
    {
        long long array[] = {3,5,7,2,9};
        std::vector<long long> testVector(array,array+sizeof(array)/sizeof(array[0]));
        int result = compute2SUM(testVector,0LL,100LL);
        assert(result==9);
    }

    //Test 3
    {
        long long array[] = {3,5,7,2,9};
        std::vector<long long> testVector(array,array+sizeof(array)/sizeof(array[0]));
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

            int result = compute2SUM(inputArray,-10000LL,10000LL);
        }
        catch(const std::exception& e){
            std::cerr<<e.what()<<std::endl;
            return 0;
        }
    }

    return 0;
}

