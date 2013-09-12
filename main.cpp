#include <iostream>
#include <graph.h>
using namespace std;

int main()
{
    Graph <string> A;
    A.add_vertex("A");
    A.add_vertex("jfk");
    std::string s("f");
    A.add_vertex(std::move(s));
    A.rem_vertex(std::move(s));
    A.rem_vertex(std::move(s));
     cout << "Hello" << endl;
    A.add_edge("A", "f", 67);
    cout << "Hello World!" << endl;
    return 0;
}

