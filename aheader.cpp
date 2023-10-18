#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "aheader.h"
using namespace std;

Tga::Tga(){
    this->pickcellCount=0;
}

Tga::Tga(string file){
    this->file = file;
    fstream infile(file,ios_base::in | ios_base::binary);

    if (infile.is_open()){
        infile.read(&this->h.idLength,1);
        infile.read(&this->h.colorMapType,1);
        infile.read(&this->h.dataCodetype,1);
        infile.read(reinterpret_cast<char*>(&this->h.colorMapOrigin),2);
        infile.read(reinterpret_cast<char*>(&this->h.colorMapDepth),2);
        infile.read(&this->h.colorMapDepth,1);
        infile.read(reinterpret_cast<char*>(&this->h.xOrigin),2);
        infile.read(reinterpret_cast<char*>(&this->h.yOrigin),2);
        infile.read(reinterpret_cast<char*>(&this->h.idLength),2);
        infile.read(reinterpret_cast<char*>(&this->h.idLength),2);
        infile.read(&this->h.bitsPerPixel,1);
        infile.read(&this->h.imageDescriptor,1);
        this->pickcellCount = this->h.width*this->h.height;

        vector<unsigned char> colors;
        for (int i=0;i<pickcellCount;i++){
            for (int j=0;j<3;j++){
                unsigned char dolores;
                infile.read(reinterpret_cast<char*>(&dolores),1);
                colors.push_back(dolores);
            }
            pickcells.push_back((colors));
        }
        infile.close();
    }
    else{
        cout<<"File does not exist"<<endl;
    }
}

Tga::~Tga(){
    ;
}

