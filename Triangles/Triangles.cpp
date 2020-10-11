#include <iostream>
#include <cassert>
#include <unordered_map>
#include "Tree.h"
#include "Triangles.h"



int main()
{
    int n;
    std::cout << "Input count of triangles" << std::endl;
    std::cin >> n;
    assert(std::cin.good());

    Tree::Ternary_Tree tree;
   
    double x1, y1, z1, x2, y2, z2, x3, y3, z3; 
    
    std::cout << "Input triangles" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
        tree.tr_push(Triangles::Triangle{ i, Triangles::Triangle::Point{x1, y1, z1}, Triangles::Triangle::Point{ x2, y2, z2 }, Triangles::Triangle::Point{ x3, y3, z3 } });
    }

    bool* arr = new bool[n]{ false };
    tree.undergo(arr);

    std::cout << "Triangles that intersects: ";
    for (int i = 0; i < n; i++)
        if (arr[i])
            std::cout << i + 1 << " ";
    std::cout << std::endl;

    tree.free();
    delete[] arr;
}
