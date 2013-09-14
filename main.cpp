#include <iostream>
#include <graph.h>
using namespace std;

int main()
{
    Graph <string> A;
    A.add_vertex("A");
    A.add_vertex("jfk");
    std::string s("f");
    A.print();
    A.add_vertex(std::move(s));
    A.rem_vertex(std::move(s));
    A.rem_vertex(std::move(s));
    A.print();
    A.add_edge("A", "f", 67);
    A.print();
    return 0;
}

