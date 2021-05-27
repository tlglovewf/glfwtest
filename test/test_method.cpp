#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <limits.h>
#include <set>
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

/* 气泡排序 n2 稳定*/ 
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

/* 快速排序 nlogn 不稳定*/ 
void quickSort( IntVec &arr, int lf, int rg)
{
    if(arr.empty()) return;
    if(lf >= rg)return;
    int _lf = lf;
    int _rg = rg;
    auto temp = arr[lf];
    while(lf != rg)
    {
        while(lf < rg && temp <= arr[rg])
            rg--;
        arr[lf] = arr[rg];
        while(lf < rg && temp >= arr[lf])
            lf++;
        arr[rg] = arr[lf];
    }
    arr[rg] = temp;
    quickSort(arr, _lf, lf - 1);
    quickSort(arr, rg + 1, _rg);
}
/* 插入排序 n2 稳定*/ 
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
/* 堆排序 nlogn 不稳定 */
void heapSort( IntVec &arr)
{

}
#pragma endregion

#pragma region 字符串转int
int AtoInt(const std::string &s)
{
    if(!s.empty())
    {
        int sign = 1, tmp = 0, i = 0;

        while(s[i] == ' ')  ++i;              //1.忽略前导空格

        if(s[i] == '+' || s[i] == '-')        //2.确定正负号
            sign = (s[i++] == '-') ? -1 : 1;  //s[i]为+的话sign依旧为1，为-的话sign为-1

        while(s[i] >= '0' && s[i] <= '9')     //3.检查输入是否合法
        {
            if(tmp > INT_MAX / 10 || (tmp == INT_MAX / 10 && s[i] - '0' > 7))    //4.是否溢出
                return sign == 1 ? INT_MAX : INT_MIN;
            tmp = tmp * 10 + (s[i++] - '0');  //5.不加括号有溢出风险
        }
        return tmp * sign;
    }
};
#pragma endregion


string getText( std::string str)
{
   int ed = str.size() - 1;
   std::string temp = str.substr(0,1);
    for(size_t i = 0; i < str.size(); ++i)
    {
        for(size_t j = ed; j > i ; --j)
        {
            if(str[i] == str[j])
            {
                auto s = str.substr(i, j - i +1);
                auto t = s;
                if(s.size() > temp.size())
                {
                    std::reverse(s.begin(),s.end());
                    if(s == t)
                        temp = std::move(s);
                }
                    
                break;
            }

        }
    }
    return temp;
}



 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

ListNode* reverseList(ListNode* head) 
{
    ListNode *cur   = head;
    ListNode *pre   = NULL;
    while(cur)
    {
        auto  temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    return pre;
}

 ListNode* deleteNode(ListNode* head, int val)
 {
    ListNode *cur = head;
    ListNode *pre = head;
    if(cur->val == val) {return head->next;}
    while(cur && (cur->val != val)){pre = cur;cur = cur->next;}
    if(cur)
        pre->next = cur->next;
    return head;

}


void printList( ListNode *pnode)
{
    while(pnode)
    {
        std::cout << pnode->val << " ";
        pnode = pnode->next;
    }
}

int reverse(int x)
{
   string str =  std::to_string(abs(x));
   
   int sign = (x < 0) ? -1 : 1;
   int value = 0;
   while(!str.empty())
   {
       if(value > INT_MAX / 10) return 0;
       value = value * 10 + (static_cast<int>(str.back()) - '0');
       str.pop_back();
   }
    return sign * value;
}

#include <queue>

void test()
{
    std::deque<int> ques;
    ques.push_back(10);
    ques.push_back(11);
    ques.push_back(11);
    ques.push_back(10);
    // ques.push_back(10);

    size_t half = (ques.size() >> 1);
    while((ques.size() > 1) && (ques.front() == ques.back()))
    {
        ques.pop_back();
        ques.pop_front();  
    }
    if(ques.size() <= 1)
        std::cout << "hui" << std::endl;
    else
        std::cout << "not" << std::endl;
}

    //不重复串  滑动窗口
    int lengthOfLongestSubstring(string s) {
        std::vector<int> m(128, 0);//128  ascii码范围
        int ans = 0;
        int i = 0;
        for (int j = 0; j < s.size(); j++) {
            if(m[s[j]] != 0)
                i = std::max(i, m[s[j]]);
            m[s[j]] = j + 1;
            ans = std::max(ans, j - i + 1);
        }
        return ans;
    }


#include <unordered_set>
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

#if 0  //排序
    //bubbleSort(vecs);
    //insertSort(vecs);
    quickSort(vecs,0, vecs.size() - 1);
    for(auto i : vecs)
    {
        std::cout << i << " ";
    }
#endif 

    // std::cout << AtoInt("   -43");
    // std::cout << getText(string("aacabdkacaa"));

    
    // std::cout << lengthOfLongestSubstring("testcc") << std::endl;
    // std::unordered_set<char>  values;
    // values.insert('a');
    // values.insert('b');
    // values.insert('c');
    // values.insert('d');

    std::unordered_set<int>    tests;
    tests.insert(10);
    tests.insert(12);
    tests.insert(15);
    tests.insert(13);

    for(auto i : tests)
    {
        std::cout << i << " ";
    }

    
    return 0;
}