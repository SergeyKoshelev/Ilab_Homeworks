#include <cassert>
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <cmath>
#include "Triangles.h"
#include <fstream>

int main() {

        int n;
        std::cout << "Input count of triangles" << std::endl;
        std::cin >> n;
        assert(std::cin.good());

        Triangle* Triangles = new Triangle[n];
        bool* inters = new bool[n] {false};
        std::cout << "Input points of your triangles (Ax, Ay, Bx, By, Cx, Cy)" << std::endl;
        for (int i = 0; i < n; i++)
        {
            std::cin >> Triangles[i].A.x >> Triangles[i].A.y >> Triangles[i].B.x >> Triangles[i].B.y >> Triangles[i].C.x >> Triangles[i].C.y;
            Triangles[i].init_segs();
            assert(std::cin.good());
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; (j < n) && ((inters[i] == false) || (inters[j] == false)); j++)
                if (intersect_tr(Triangles[i], Triangles[j]))
                {
                    inters[i] = true;
                    inters[j] = true;
                }
        }

        std::cout << "Triangles that have intersection" << std::endl;

        for (int i = 0; i < n; i++)
            if (inters[i])
                std::cout << i + 1 << " ";

        std::cout << std::endl;
        delete[] Triangles;
        delete[] inters;
 /* tests went to special progect Triangles_Test with GTest interface
    else //test from file
    {
        std::ifstream file("tests.txt");
        for (int n = 0; file >> n; )
        {
            Triangle* Triangles = new Triangle[n];
            bool inter = false; //detect if we have intersections

            for (int i = 0; i < n; i++)
            {
                file >> Triangles[i].A.x >> Triangles[i].A.y >> Triangles[i].B.x >> Triangles[i].B.y >> Triangles[i].C.x >> Triangles[i].C.y;
                Triangles[i].init_segs();
            }

            inter = intersect_tr(Triangles[0], Triangles[n-1]);

            std::cout << "TEST" << std::endl;
            std::cout << "1st Triangle " << Triangles[0].A.x << " " << Triangles[0].A.y << " " <<
                Triangles[0].B.x << " " << Triangles[0].B.y << " " <<
                Triangles[0].C.x << " " << Triangles[0].C.y << std::endl;
            std::cout << "2nd Triangle " << Triangles[1].A.x << " " << Triangles[1].A.y << " " <<
                Triangles[1].B.x << " " << Triangles[1].B.y << " " <<
                Triangles[1].C.x << " " << Triangles[1].C.y << std::endl;
            int correct = 0;
            file >> correct;

            std::cout << "Correct: ";
            if (correct == 1)
                std::cout << "true ";
            else
                std::cout << "false ";

            std::cout << "Program: ";
            if (inter)
                    std::cout << "true " << std::endl;
            else
                    std::cout << "false" << std::endl;

            if ((inter && (correct == 1))||(!inter && (correct != 1)))
                std::cout << "Test passed" << std::endl;
            else
                std::cout << "Test failed" << std::endl;
            std::cout << std::endl;


            delete[] Triangles;
        }
    }
    */
}
