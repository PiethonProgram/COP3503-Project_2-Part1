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

class Manipulator{
public:
    Manipulator();
    ~Manipulator();

    Tga multiply(Tga Uno, Tga Dos);
    Tga screen(Tga Uno, Tga Dos);
    Tga subtract(Tga Uno, Tga Dos);
    Tga add(Tga Uno, Tga Dos);
    Tga overlay(Tga Uno, Tga Dos);
    Tga combineIndividual(Tga Uno, Tga Dos, string channel);
    Tga multiplyChannel(Tga Uno, string channel, float scale);
    Tga addChannel(Tga Uno, string channel, int amount);
    Tga flip(Tga Uno);
    Tga singleChannel(Tga Uno, string channel);
};