#ifndef PART_H
#define PART_H
#include <fstream>
#include <vector>
#include "Reader.h"
using namespace std;

//Klasa Part zdobywa przechowuje informacje o danym odcinku kszta�tu 
class Part
{
    public:
        Part();
        Part(int byteIndex);
        //Wsp�rz�dne punkt�w odcinka
        double x1;
        double y1;
        double z1;
        double x2;
        double y2;
        double z2;
        vector<double> points;
        FILE* file = fopen("test.shp","r");
        int byteIndex;
        Reader reader;

    protected:

    private:
};

#endif // PART_H
