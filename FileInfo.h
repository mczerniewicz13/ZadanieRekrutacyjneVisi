#ifndef FILEINFO_H
#define FILEINFO_H
#include <fstream>
#include "Reader.h"


//Klasa FileInfo zdobywa i przechowuje wszystkie przydatne informacje o pliku .shp
class FileInfo
{
    public:
        FileInfo();

        const char* filePath = "test.shp";
        FILE* file;
        Reader reader;
        //typ kszta�tu - w tym wypadku warto�� 13 - PolyLineZ
        int shapeType; 

        //Wsp�rz�dne okna ograniczaj�cego kszta�t
        double minX;
        double maxX;
        double minY;
        double maxY;
        double minZ;
        double maxZ;

        
        void setIndc(int index);
        int getShape();
        double getMinX();
        double getMaxX();
        double getMinY();
        double getMaxY();
        double getMinZ();
        double getMaxZ();



        void getInfo();


    protected:

    private:
};

#endif // FILEINFO_H
