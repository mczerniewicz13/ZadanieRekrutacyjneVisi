#include "Part.h"
#include <iostream>
#include <vector>
using namespace std;
Part::Part(int byteIndex)
{
    //Sczytywanie kolejnych bajtów przechowuj¹cych informacje o wspó³rzêdnych punktów odcinka
    x1=reader.littleEndianDoubleOrder(byteIndex);
    y1=reader.littleEndianDoubleOrder(byteIndex+8);
    x2=reader.littleEndianDoubleOrder(byteIndex+16);
    y2=reader.littleEndianDoubleOrder(byteIndex+24);
    z1=reader.littleEndianDoubleOrder(byteIndex+32);
    z2=reader.littleEndianDoubleOrder(byteIndex+40);
    points.push_back(x1);
    points.push_back(y1);
    points.push_back(z1);
    points.push_back(x2);
    points.push_back(y2);
    points.push_back(z2);


}
Part::Part()
{
    x1=reader.littleEndianDoubleOrder(156);
    y1=reader.littleEndianDoubleOrder(156+8);
    x2=reader.littleEndianDoubleOrder(156+16);
    y2=reader.littleEndianDoubleOrder(156+24);
    z1=reader.littleEndianDoubleOrder(156+32);
    z2=reader.littleEndianDoubleOrder(156+40);
    points.push_back(x1);
    points.push_back(y1);
    points.push_back(z1);
    points.push_back(x2);
    points.push_back(y2);
    points.push_back(z2);

}

