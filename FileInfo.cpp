#include "FileInfo.h"
#include <iostream>
using namespace std;

    //Ustawienie wskaŸnika wewnêtrznego pliku 
    void FileInfo::setIndc(int index)
    {
        fseek(file, index, SEEK_SET);
    }

    //Metody zwracaj¹ce wartoœci z odpowiednich bajtów
    int FileInfo::getShape()
    {
        return reader.littleEndianOrder(32);
    }
    double FileInfo::getMinX()
    {
        return reader.littleEndianDoubleOrder(36);
    }
    double FileInfo::getMaxX()
    {
        return reader.littleEndianDoubleOrder(52);
    }
    double FileInfo::getMinY()
    {
        return reader.littleEndianDoubleOrder(44);
    }
    double FileInfo::getMaxY()
    {
        return reader.littleEndianDoubleOrder(60);
    }
    double FileInfo::getMinZ()
    {
        return reader.littleEndianDoubleOrder(68);
    }
    double FileInfo::getMaxZ()
    {
        return reader.littleEndianDoubleOrder(76);
    }

    void FileInfo::getInfo()
    {
        cout << "Info File: " << filePath << endl;
        cout << "Shape type: " << shapeType << endl;
        cout << "Min X:" << minX << endl;
        cout << "Max X:" << maxX << endl;
        cout << "Min Y:" << minY << endl;
        cout << "Max Y:" << maxY << endl;
        cout << "Min Z:" << minZ << endl;
        cout << "Max Z:" << maxZ << endl;
    }
FileInfo::FileInfo()
{
    file = fopen(filePath, "r");

    shapeType = getShape();

    minX = getMinX();
    maxX = getMaxX();
    minY = getMinY();
    maxY = getMaxY();
    minZ = getMinZ();
    maxZ = getMaxZ();
}

