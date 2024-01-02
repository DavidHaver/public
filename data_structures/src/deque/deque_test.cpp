#include "my_assert.hpp"//TEST SUMMARY 
#include "deque.hpp"//header 

using namespace david_haver; 

void AddAndAccessTest(void);
void AssignmentTest(void);

int main() 
{ 
    AddAndAccessTest();
    AssignmentTest();
    SUMMARY; 
    return 0; 
}

void AddAndAccessTest(void) 
{
    Deque<int> orign(4);
    TEST(orign.Empty());
    orign.PushBack(2);
    orign.PushFront(1);
    orign.PushBack(3);
    orign.PushBack(4);
    orign.PushBack(5);
    const Deque<int> duplicate(orign);
    TEST(!orign.Empty());
    TEST(!duplicate.Empty());
    TEST(1 == orign[0]);
    TEST(1 == duplicate[0]);
    TEST(3 == orign[2]);
    TEST(3 == duplicate[2]);
    TEST(5 == orign[4]);
    TEST(5 == duplicate[4]);
    TEST(3 == orign.At(2));
    TEST(3 == duplicate.At(2));
    TEST(5 == orign.At(4));
    TEST(5 == duplicate.At(4));
    TEST(1 == orign.Front());
    TEST(1 == duplicate.Front());
    TEST(5 == orign.Back());
    TEST(5 == duplicate.Back());
    
    try
    {
        orign.At(5) = 6; //out of range in chunk
    }
    catch(const std::exception& e)
    {
        TEST(std::string("position out of range") == e.what());
    }
    try
    {
        orign.At(8) = 9;//out of range outside chunk
    }
    catch(const std::exception& e)
    {
        TEST(std::string("position out of range") == e.what());
    }
      
    orign.PushFront(0);
    TEST(0 == orign.At(0));
    TEST(1 == duplicate.At(0));
    TEST(1 == orign.At(1));
    TEST(2 == duplicate.At(1));
    TEST(!orign.Empty());
    TEST(!duplicate.Empty());

}

void AssignmentTest(void)
{
    Deque<std::shared_ptr<int>> orign(4);
    TEST(orign.Empty());
    orign.PushBack(std::shared_ptr<int>(new int(2)));
    orign.PushFront(std::shared_ptr<int>(new int(1)));
    orign.PushBack(std::shared_ptr<int>(new int(3)));
    orign.PushBack(std::shared_ptr<int>(new int(4)));
    orign.PushBack(std::shared_ptr<int>(new int(5)));
    Deque<std::shared_ptr<int>> copy(7);
    TEST(copy.Empty());
    copy = orign;
    TEST(!copy.Empty());
    TEST(orign.At(0) == copy.At(0));
    TEST(orign.At(1) == copy.At(1));
    TEST(orign.At(2) == copy.At(2));
    TEST(orign.At(3) == copy.At(3));
    TEST(orign.At(4) == copy.At(4));
    copy.At(3) = std::shared_ptr<int>(new int(6));
    TEST(6 == *(copy.At(3)));
    TEST(4 == *(orign.At(3)));
    TEST(orign.At(0) == copy.At(0));
    TEST(orign.At(3) != copy.At(3));
    copy = orign;
    TEST(orign.At(0) == copy.At(0));
    TEST(orign.At(1) == copy.At(1));
    TEST(orign.At(2) == copy.At(2));
    TEST(orign.At(3) == copy.At(3));
    TEST(orign.At(4) == copy.At(4));
}
