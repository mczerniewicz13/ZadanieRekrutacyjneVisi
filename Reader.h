#ifndef READER_H
#define READER_H
#include <fstream>


/*Klasa Reader odczytuje zapisane w pliku bajty
  i zwraca je jako wartoœci liczbowe w systemie dziesiêtnym w zale¿noœci od wybranej kolejnoœci bajtów */
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
