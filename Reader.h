#ifndef READER_H
#define READER_H
#include <fstream>


/*Klasa Reader odczytuje zapisane w pliku bajty
  i zwraca je jako warto�ci liczbowe w systemie dziesi�tnym w zale�no�ci od wybranej kolejno�ci bajt�w */
class Reader
{
    public:
        int bigEndianOrder(int byteToRead);

        int littleEndianOrder(int byteToRead);

        double littleEndianDoubleOrder(int byteToRead);


    protected:

    private:
};

#endif // READER_H
