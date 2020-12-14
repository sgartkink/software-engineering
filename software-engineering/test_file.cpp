#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "test_file2.cpp"

namespace test_namespace {

//test comment
/*
 * test multiline comment
 * test function()
 */

int sum(int a, int b)
{
    return a+b;
}

void test() {

}

void test_function()
{
    std::string s("test");
    int a = 0;
    int b = 5;
    sum(a,b);
    test();
}

}//~test_namespace
