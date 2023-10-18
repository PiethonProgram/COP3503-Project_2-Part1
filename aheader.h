#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Tga {
    public:
        struct Header {
            char idLength;
            char colorMapType;
            char dataCodetype;
            short colorMapOrigin;
            short colorMapLength;
            char colorMapDepth;
            short xOrigin;
            short yOrigin;
            short width;
            short height;
            char bitsPerPixel;
            char imageDescriptor;
        };
        Tga();
        Tga(string file);
        ~Tga();

        Header getHeader();
        vector<vector<unsigned char>> getPixelShallow();
        vector<vector<unsigned char>>* getPixelDeep();
        int getPixelCount();

        void setHeader(Header);
        void setPixelCount(int);

        void writeTga(string name);
        void writeChannel(string name, string channel);



    private:
        Header h;
        string file ="";
        vector<vector<unsigned char>> pickcells;
        int pickcellCount;



};