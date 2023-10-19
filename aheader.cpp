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

Tga::Header Tga::getHeader() {
    return this->h;
}

vector<vector<unsigned char>> Tga::getPixelShallow() {
    return this->pickcells;
}

vector<vector<unsigned char>>* Tga::getPixelDeep() {
    return &this->pickcells;
}

int Tga::getPixelCount() {
    return this->pickcellCount;
}

void Tga::setHeader(Tga::Header setter) {
    this->h = setter;
}

void Tga::setPixelCount(int count) {
    this->pickcellCount=count;
}

void Tga::writeTga(string name) {
    fstream outfile(name, ios_base::out | ios_base::binary);
    if (outfile.is_open()){
        outfile.write(&this->h.idLength, 1);
        outfile.write(&this->h.colorMapType, 1);
        outfile.write(&this->h.dataCodetype, 1);
        outfile.write(reinterpret_cast<char*>(&this->h.colorMapOrigin), 2);
        outfile.write(reinterpret_cast<char*>(&this->h.colorMapLength), 2);
        outfile.write(&this->h.colorMapDepth, 1);
        outfile.write(reinterpret_cast<char*>(&this->h.xOrigin), 2);
        outfile.write(reinterpret_cast<char*>(&this->h.yOrigin), 2);
        outfile.write(reinterpret_cast<char*>(&this->h.width), 2);
        outfile.write(reinterpret_cast<char*>(&this->h.height), 2);
        outfile.write(&this->h.bitsPerPixel, 1);
        outfile.write(&this->h.imageDescriptor, 1);
        for (int i=0; i< this-> pickcellCount;i++){
            for (int j=0;j<3;j++){
                outfile.write(reinterpret_cast<char*>(&this->pickcells[i][j]),1);
            }
        }
    }
    else{
        cout<<"File isn't open"<<endl;
    }
}

void Tga::writeChannel(string name, string channel) {
    fstream outfile(name, ios_base::out | ios_base::binary);
    if(outfile.is_open()){
        outfile.write(&this->h.idLength, 1);
        outfile.write(&this->h.colorMapType, 1);
        outfile.write(&this->h.dataCodetype, 1);
        outfile.write(reinterpret_cast<char*>(&this->h.colorMapOrigin), 2);
        outfile.write(reinterpret_cast<char*>(&this->h.colorMapLength), 2);
        outfile.write(&this->h.colorMapDepth, 1);
        outfile.write(reinterpret_cast<char*>(&this->h.xOrigin), 2);
        outfile.write(reinterpret_cast<char*>(&this->h.yOrigin), 2);
        outfile.write(reinterpret_cast<char*>(&this->h.width), 2);
        outfile.write(reinterpret_cast<char*>(&this->h.height), 2);
        outfile.write(&this->h.bitsPerPixel, 1);
        outfile.write(&this->h.imageDescriptor, 1);

        if (channel=="blue"){
            for (int i=0;i<this->pickcellCount;i++){
                for (int j=0;j<3;j++){
                    outfile.write(reinterpret_cast<char*>(&this->pickcells[i][0]), 1);
                }
            }
        }
        if (channel=="green"){
            for (int i=0;i<this->pickcellCount;i++){
                for (int j=0;j<3;j++){
                    outfile.write(reinterpret_cast<char*>(&this->pickcells[i][1]), 1);
                }
            }
        }
        if (channel == "red"){
            for (int i=0;i<this->pickcellCount;i++){
                for (int j=0;j<3;j++){
                    outfile.write(reinterpret_cast<char*>(&this->pickcells[i][2]), 1);
                }
            }
        }
    }
    else{
        cout<<"File isn't open"<<endl;
    }
}

//separate between functions for the two classes

Manipulator::Manipulator() {
    ;
}

Manipulator::~Manipulator(){
    ;
}

Tga Manipulator::multiply(Tga Uno, Tga Dos) {
    Tga Rizz;
    vector<vector<unsigned char>> temu1 = Uno.getPixelShallow();
    vector<vector<unsigned char>> temu2 = Dos.getPixelShallow();
    Rizz.setHeader(Uno.getHeader());
    Rizz.setPixelCount(Uno.getPixelCount());
    for (int i=0;i<Rizz.getPixelCount();i++){
        vector<unsigned char> dolores(3, 0);
        for (int j=0;j<3;j++){
            float color=(static_cast<float>(temu1[i][j]) / 255.0f) * (static_cast<float>(temu2[i][j]) / 255.0f);
            color=(color*255.0f)+0.5f;
            dolores[j] = static_cast<unsigned char>(color);
        }
        Rizz.getPixelDeep()->push_back(dolores);
    }
    return (Rizz);
}

Tga Manipulator::screen(Tga Uno, Tga Dos) {

}

Tga Manipulator::subtract(Tga Uno, Tga Dos) {

}

Tga Manipulator::add(Tga Uno, Tga Dos) {

}

Tga Manipulator::overlay(Tga Uno, Tga Dos) {

}

Tga Manipulator::combineIndividual(Tga Uno, Tga Dos, std::string channel) {

}

Tga Manipulator::multiplyChannel(Tga Uno, std::string channel, float scale) {

}

Tga Manipulator::addChannel(Tga Uno, std::string channel, int amount) {

}

Tga Manipulator::flip(Tga Uno) {

}

Tga Manipulator::singleChannel(Tga Uno, std::string channel) {

}