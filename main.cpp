#include <SDL.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "Reader.h"
#include "FileInfo.h"
#include "Part.h"

using namespace std;

//Funkcja znajduj�ca aktualnie najwi�ksze warto�ci x oraz y w zbiorze odcink�w
vector<double> findMinMax(vector<Part> lines)
{
    //xMin, xMax, yMin, yMax
    vector<double> result = { lines[0].x1 ,lines[0].x1, lines[0].y1, lines[0].y1};

    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].x1 < result[0])
        {
            result[0] = lines[i].x1;
        }
        if (lines[i].x1 > result[1])
        {
            result[1] = lines[i].x1;
        }


        if (lines[i].x2 < result[0])
        {
            result[0] = lines[i].x2;
        }
        if (lines[i].x2 > result[1])
        {
            result[1] = lines[i].x2;
        }


        if (lines[i].y1 < result[2])
        {
            result[2] = lines[i].y1;
        }
        if (lines[i].y1 > result[3])
        {
            result[3] = lines[i].y1;
        }


        if (lines[i].y2 < result[2])
        {
            result[2] = lines[i].y2;
        }
        if (lines[i].y2 > result[3])
        {
            result[3] = lines[i].y2;
        }
    }

    return result;
    
}

//Funkcja sczytuj�ca kolejne odcinki wraz ze wszystkimi ich informacjami z pliku .shp
vector<Part> returnShape(FILE* file, Reader reader)
{
    vector<Part> parts;

    Part pTmp(156);
    int startPoint = 156;
    int i = 0;
    while (reader.littleEndianOrder(startPoint + (i * 152)) != -1)
    {

        pTmp.byteIndex = startPoint + (i * 152);
        Part pTmp(startPoint + (i * 152));
        parts.push_back(pTmp);
        i++;
    }
 
    return parts;


}


/*Funkcja wybieraj�ca ostatnie n cyfr z wsp�rz�dnych punkt�w kszta�tu.
  Warto�ci s� te� od razu skalowane tak aby kszta� by� widoczny na ekranie.
  Zakres warto�ci jest pomniejszany o jego minimum tak aby warto�ci zaczyna�y si� od 0*/
vector<Part> cutNDigits(vector<Part> lines, int n, float xscale, float yscale)
{
    
    vector<Part> result = lines;
    int cutNumber = pow(10, n);

    //Wybieranie n ostatnich cyfr i skalowanie
    for (int i = 0; i < result.size(); i++)
    {
        result[i].x1 = ((int)result[i].x1 % cutNumber) * 15 - xscale;
        result[i].y1 = ((int)result[i].y1 % cutNumber) * 15 - yscale;
        result[i].x2 = ((int)result[i].x2 % cutNumber) * 15 - xscale;
        result[i].y2 = ((int)result[i].y2 % cutNumber) * 15 - yscale;
    }

    //Skalowanie zakresu warto�ci
    vector<double> minMax = findMinMax(result);
    for (int i = 0; i < result.size(); i++)
    {
        result[i].x1 -= minMax[0];
        result[i].y1 -= minMax[2];
        result[i].x2 -= minMax[0];
        result[i].y2 -= minMax[2];
    }
    return result;

}


//Funkcja skaluj�ca kszta�t
vector<Part> resize(vector<Part> lines, float size)
{
    vector<Part> result = lines;
    for (int i = 0; i < result.size(); i++)
    {
        result[i].x1 *= size;
        result[i].y1 *= size;
        result[i].x2 *= size;
        result[i].y2 *= size;
    }

    return result;
}


int main(int argc, char** argv)
{

    // ZMIENNE

    FILE* data; 
    data = fopen("test.shp", "r");
    SDL_Event event;
    Reader reader;

    //Wymiary okna rysowania kszta�tu
    int height = 720;
    int width = 1280;

    //Zmienne ruchu kszta�tem
    int x1Mouse = 0;
    int x2Mouse = 0; 
    int y1Mouse = 0; 
    int y2Mouse = 0;
    int xMouseOffset = 0;
    int yMouseOffset = 0;
    bool panning = false;
    bool motion = false;

    bool quit = false;

    //Zmienne skali do skalowania kszta�tu
    float xscale = 8500;
    float yscale = 12800;
    float sizeUp = 1;
    float sizeDown = 1; 

    //Anchor point dla kszta�tu
    vector<int> anchor = { 0,0 };
   
    //Inicjalizacja ca�ego kszta�tu oraz skalowanie do wymiar�w mieszcz�cych si� w oknie
    vector<Part> lines = returnShape(data, reader);;
    lines = cutNDigits(lines,3,xscale,yscale);


    //Ustawianie anchor point`a i wy�rodkowywanie rysowania kszta�tu
    vector<double> minMax = findMinMax(lines);
    int shapeWidth = minMax[1] - minMax[0];
    int shapeHeight = minMax[3] - minMax[2];
    anchor[0] = width / 2 - shapeWidth/2 ;
    anchor[1] = -height / 2 + shapeHeight / 2;



    // Inicjalizacja SDL`a
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Zadanie Rekrutacyjne Mateusz Czerniewicz",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetWindowResizable(window, SDL_TRUE);
    // P�tla g��wna
    while (!quit)
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);
        
        //Switch z rozpoznaniem event�w
        switch (event.type)
        {
        
        case SDL_QUIT:
            quit = true;
            break;

        //Obs�uga wci�ni�cia LPM i ustawienie punktu pocz�tkowego ruchu myszy 
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x1Mouse = event.motion.x;
                y1Mouse = event.motion.y;
                panning = true;
                motion = false;
            }
            break;

        /*Obs�uga ruchu mysz�.Jedynie po wci�ni�ciu LPM wyliczana jest obecna pozycja kursora,
          a nast�pnie warto�� przesuni�cia od miejsca klikni�cia.*/
        
        case SDL_MOUSEMOTION:
            if (panning)
            {
                SDL_GetMouseState(&x2Mouse, &y2Mouse);
                xMouseOffset = x2Mouse - x1Mouse;
                yMouseOffset = y2Mouse - y1Mouse;
            }
            break; 
            
        //Obs�uga zwolnienia LPM.
        case SDL_MOUSEBUTTONUP:
            panning = false;
            motion = true;
            break;

        //Obs�uga k�ka myszy. Ruch w prz�d powi�ksza a w ty� zmniejsza kszta�t
        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0)
            {   
                sizeDown = 1;
                sizeUp += 0.05;
                lines = resize(lines, sizeUp);
            }
            if (event.wheel.y < 0)
            {   
                sizeUp = 1;
                sizeDown -= 0.05;
                lines = resize(lines, sizeDown);
            }
            break;
        }
        
           
        
        //Ustalenie koloru t�a okna rysowania
        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        //Ustalenie koloru rysowania
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


        for (int i = 0; i < lines.size(); i++)
        {
            //Rysowanie kolejnych odcink�w kszta�tu z uwzgl�dnieniem pozycji wzgl�dem anchor point`a i przesuni�ciem myszy
            SDL_RenderDrawLine(renderer, anchor[0]+lines[i].x1 + xMouseOffset, anchor[1] + height - lines[i].y1 + yMouseOffset,
                anchor[0] + lines[i].x2 + xMouseOffset, anchor[1] + height - lines[i].y2 + yMouseOffset);

            //Warunek sprawdzaj�cy puszczenie LPM
            if (motion)
            {
                //Nadpisanie pozycji anchor point`a o aktualne przesuni�cie myszy
                anchor[0] += xMouseOffset;
                anchor[1] += yMouseOffset;
                xMouseOffset = 0;
                yMouseOffset = 0;
            }
        }
        motion = false;
        SDL_RenderPresent(renderer);

    }
    //Zwolnienie zainicjalizowanych zmiennych
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    fclose(data);
    return 0;
}