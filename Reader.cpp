#include "Reader.h"


//Metoda zwracaj¹ca liczbê zapisan¹ w bajtach w kolejnoœci Big Endian
int Reader::bigEndianOrder(int byteToRead)
    {
        FILE* file = fopen("test.shp","r");
        int tmpOrResult=0;
        //Pêtla przeskakuj¹ca po kolejnych 4 bajtach od wskazanego
        for(int i=0;i<=4;i++)
        {
            //Ustawienie wskaŸnika wewnêtrznego pliku
            fseek(file,byteToRead+i,SEEK_SET);
            //Do³¹czanie kolejnych bajtów w jedn¹ liczbê w kolejnoœci od lewej do prawej
            tmpOrResult= tmpOrResult|((fgetc(file)& 0xff)<<(24-(i*8)));
        }
        fclose(file);
        return tmpOrResult;

    }
//Metoda zwracaj¹ca liczbê zapisan¹ w bajtach w kolejnoœci Little Endian
int Reader::littleEndianOrder(int byteToRead)
    {
        FILE* file = fopen("test.shp","r");
        int tmpOrResult=0;

        //Pêtla przeskakuj¹ca po kolejnych 4 bajtach od wskazanego
        for(int i=0;i<4;i++)
        {
            //Ustawienie wskaŸnika wewnêtrznego pliku
            fseek(file,byteToRead+(3-i),SEEK_SET);
            //Do³¹czanie kolejnych bajtów w jedn¹ liczbê w kolejnoœci od prawej do lewej
            tmpOrResult= tmpOrResult|((fgetc(file)& 0xff)<<(24-(i*8)));
        }
        fclose(file);
        return tmpOrResult;
    }

//Metoda zwracaj¹ca liczbê zapisan¹ w bajtach w kolejnoœci Little Endian 
double Reader::littleEndianDoubleOrder(int byteToRead)
    {
        FILE* file = fopen("test.shp","r");
        char* fileBuf = new char[8888];
        //Sczytanie ca³ego pliku do zmiennej fileBuf
        fread(fileBuf, 8888, 1, file);
        double result;
        char mark[8];
        int j = -1;
        //Pêtla przeskakuj¹ca po kolejnych 8 bajtach od wskazanego
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
