#include <iostream>
#include <vector>
#include <stack>
// using namespace std;
using std::string;

#pragma region 动态规划 金字塔

constexpr int max_len = 5;
/*
 * 7               金字塔求解
 * 3 8 
 * 8 1 0 
 * 2 7 4 4 
 * 4 5 2 6 5
 */ 
int array[max_len][max_len] = {{7},{3,8},{8,1,0},{2,7,4,4},{4,5,2,6,5}};
int max_ar[max_len][max_len] = {0};
//递归法  重复计算偏多
int getmax(int i, int j)
{
    const int mx = max_len - 1;
    if(i == mx)
        return array[mx][mx];
    else
    {
        int x = getmax( i + 1, j);
        int y = getmax( i + 1, j + 1);
        max_ar[i][j] = std::max(x,y) + array[i][j];
        return max_ar[i][j];
    }

}

#pragma endregion

#pragma region 双栈队列
template<typename T>
class Equeue
{
public:
    using Stack = std::stack<int> ;

    inline void toOrigin()
    {
        swap(_inverse, _origin);
    }
    inline void toInverse()
    {
        swap(_origin, _inverse);
    }
    
    T pop_front() 
    {
        toInverse();
        if(_inverse.empty())exit(-1);
        const auto v = _inverse.top();
        _inverse.pop();
        return v;
    }

    T push_back(const T &t)
    {
        toOrigin();
        _origin.push(t);
    }

    bool empty()
    {
        toInverse();
        return _inverse.empty();
    }
protected:
    void swap(Stack &st1, Stack &st2)
    {
        while(!st1.empty())
        {
            st2.push(st1.top());
            st1.pop();
        }
    }

protected:
    Stack _origin;
    Stack _inverse;
};


#pragma endregion

#pragma region 排序
using IntVec    = std::vector<int>;

/*----sort----*/
IntVec vecs({10,3,33,12,21,39,18,6,1,17});


void swap(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

/* 气派排序 */
 void bubbleSort( IntVec &arr)
 {
     for(int i = 0; i < arr.size() ; ++i)
     {
         for(int j = 0; j < arr.size() - i; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
            }
        }
     }
 }

/* 快速排序 */
void quickSort( IntVec &arr)
{
 
}

void insertSort( IntVec &arr)
{
    for(int i = 0; i < arr.size(); ++i)
    {
        for(int j = i; j > 0 ; --j)
        {
            if(arr[j] < arr[j-1])
            {
                swap(arr[j], arr[j-1]);
            }
            else
                break;
        }
    }
}
#pragma endregion





int main(int argc, char **argv)
{

#if 0 //动态规划
    string dd;
    std::cout << "--------" << std::endl;
    std::cout << getmax(0,0) << std::endl;
    std::cout << "--------" << std::endl;

    std::cout << "--------" << std::endl;
    int n = 1;
    for( int i = 0; i < std::min(n++,max_len); ++i )
    {
        for(int j = 0; j <= i; ++j)
            std::cout << array[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << "--------" << std::endl;
    for( int i = n; i >= 1; --i )
    {
        for(int j = 1; j < i; ++j)
        {
            max_ar[i][j] = array[i][j] + std::max(max_ar[i + 1][j], max_ar[i + 1][j  + 1]);
        }
    }
    std::cout << max_ar[0][0] << std::endl;
#endif

#if 0  //队列
    Equeue<int> eq;

    eq.push_back(10);
    eq.push_back(13);
    eq.push_back(15);
    eq.push_back(33);

    while(!eq.empty())
        std::cout << eq.pop_front() << " ";
    std::cout << eq.pop_front() << std::endl;
#endif

    //bubbleSort(vecs);
    insertSort(vecs);
    for(auto i : vecs)
    {
        std::cout << i << " ";
    }

    return 0;
}