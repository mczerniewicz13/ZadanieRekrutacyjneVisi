#include "Reader.h"


//Metoda zwracaj�ca liczb� zapisan� w bajtach w kolejno�ci Big Endian
int Reader::bigEndianOrder(int byteToRead)
    {
        FILE* file = fopen("test.shp","r");
        int tmpOrResult=0;
        //P�tla przeskakuj�ca po kolejnych 4 bajtach od wskazanego
        for(int i=0;i<=4;i++)
        {
            //Ustawienie wska�nika wewn�trznego pliku
            fseek(file,byteToRead+i,SEEK_SET);
            //Do��czanie kolejnych bajt�w w jedn� liczb� w kolejno�ci od lewej do prawej
            tmpOrResult= tmpOrResult|((fgetc(file)& 0xff)<<(24-(i*8)));
        }
        fclose(file);
        return tmpOrResult;

    }
//Metoda zwracaj�ca liczb� zapisan� w bajtach w kolejno�ci Little Endian
int Reader::littleEndianOrder(int byteToRead)
    {
        FILE* file = fopen("test.shp","r");
        int tmpOrResult=0;

        //P�tla przeskakuj�ca po kolejnych 4 bajtach od wskazanego
        for(int i=0;i<4;i++)
        {
            //Ustawienie wska�nika wewn�trznego pliku
            fseek(file,byteToRead+(3-i),SEEK_SET);
            //Do��czanie kolejnych bajt�w w jedn� liczb� w kolejno�ci od prawej do lewej
            tmpOrResult= tmpOrResult|((fgetc(file)& 0xff)<<(24-(i*8)));
        }
        fclose(file);
        return tmpOrResult;
    }

//Metoda zwracaj�ca liczb� zapisan� w bajtach w kolejno�ci Little Endian 
double Reader::littleEndianDoubleOrder(int byteToRead)
    {
        FILE* file = fopen("test.shp","r");
        char* fileBuf = new char[8888];
        //Sczytanie ca�ego pliku do zmiennej fileBuf
        fread(fileBuf, 8888, 1, file);
        double result;
        char mark[8];
        int j = -1;
        //P�tla przeskakuj�ca po kolejnych 8 bajtach od wskazanego
        for(int i=byteToRead;i<byteToRead+8;i++)
        {
            j++;
            mark[j]=fileBuf[i];

        }
        //Rzutowanie char`a na double
        result = *reinterpret_cast<double* const>(mark);
        fclose(file);
        return(result);

    }
