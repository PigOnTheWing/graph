#include <iostream>
#include "Graph/graph.h"

int main() {
    auto* g = new graph<char>();
    g->add_node('a');
    g->add_node('b');
    g->add_node('c');
    g->add_node('d');
    g->add_node('e');
    g->add_node('f');
    g->add_node('g');
    g->add_node('h');
    g->add_node('i');

    g->connect(0, 1, 4);
    g->connect(0, 7, 8);
    g->connect(1, 2, 8);
    g->connect(1, 7, 11);
    g->connect(2, 3, 7);
    g->connect(2, 5, 4);
    g->connect(2, 8, 2);
    g->connect(3, 4, 9);
    g->connect(3, 5, 14);
    g->connect(4, 5, 10);
    g->connect(5, 6, 2);
    g->connect(5, 3, 14);
    g->connect(6, 7, 1);
    g->connect(6, 8, 2);
    g->connect(7, 8, 7);
    g->connect(7, 1, 11);
    g->connect(8, 7, 7);
    g->connect(8, 2, 2);

    g->print();

    std::cout<<"Breadth"<<std::endl;

    for (graph<char>::iterator it = g->breadth_begin(0); it != g->breadth_end(0); ++it)
    {
        std::cout << (*it)->get_data() << std::endl;
    }

    std::cout<<"Depth"<<std::endl;

    for (graph<char>::iterator it = g->depth_begin(0); it != g->depth_end(0); ++it)
    {
        std::cout << (*it)->get_data() << std::endl;
    }

    delete g;
    return 0;
}