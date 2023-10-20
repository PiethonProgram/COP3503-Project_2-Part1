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
    Tga Florida;
    vector<vector<unsigned char>> Flo = Uno.getPixelShallow();
    vector<vector<unsigned char>> Rida = Dos.getPixelShallow();
    Florida.setHeader(Uno.getHeader());
    Florida.setPixelCount(Uno.getPixelCount());
    for (int i=0; i<Florida.getPixelCount();i++){
        vector<unsigned char> surf(3, 0);
        for (int j=0;j<3;j++){
            float board = (1-(Flo[i][j]/255.0f)) * (1-(Rida[i][j]/255.0f));
            board=(1-board)*255.0f+0.5f;
            surf[j] = static_cast<unsigned char>(board);
        }
        Florida.getPixelDeep()->push_back(surf);
    }
    return (Florida);
}

Tga Manipulator::subtract(Tga Uno, Tga Dos) {
    Tga Cheese;
    vector<vector<unsigned char>> Mozzarella = Uno.getPixelShallow();
    vector<vector<unsigned char>> Provolone = Dos.getPixelShallow();
    Cheese.setHeader(Uno.getHeader());
    Cheese.setPixelCount(Uno.getPixelCount());
    for (int i=0;i<Cheese.getPixelCount();i++){
        vector<unsigned char> cheddar(3,0);
        for (int j=0;j<3;j++){
            int feta = int(Mozzarella[i][j]) - int(Provolone[i][j]);
            if (feta<0){
                feta=0;
            }
            feta=static_cast<unsigned char>(feta);
            cheddar.push_back(feta);
        }
        Cheese.getPixelDeep()->push_back(cheddar);
    }
    return (Cheese);
}

Tga Manipulator::add(Tga Uno, Tga Dos) {
    Tga Cheese;
    vector<vector<unsigned char>> Mozzarella = Uno.getPixelShallow();
    vector<vector<unsigned char>> Provolone = Dos.getPixelShallow();
    Cheese.setHeader(Uno.getHeader());
    Cheese.setPixelCount(Uno.getPixelCount());
    for (int i=0;i<Cheese.getPixelCount();i++){
        vector<unsigned char> cheddar(3,0);
        for (int j=0;j<3;j++){
            int feta = int(Mozzarella[i][j]) + int(Provolone[i][j]);
            if (feta>255){
                feta=255;
            }
            feta=static_cast<unsigned char>(feta);
            cheddar.push_back(feta);
        }
        Cheese.getPixelDeep()->push_back(cheddar);
    }
    return (Cheese);
}

Tga Manipulator::overlay(Tga Uno, Tga Dos) {
    Tga FF;
    vector<vector<unsigned char>> hamburger = Uno.getPixelShallow();
    vector<vector<unsigned char>> hotdog = Dos.getPixelShallow();
    FF.setHeader(Uno.getHeader());
    FF.setPixelCount(Uno.getPixelCount());
    for(int i=0; i<FF.getPixelCount(); i++){
        vector<unsigned char>condiment(3,0);
        for(int j=0; j<3; j++){
            float color;
            if(hotdog[i][j]/255.0f <= 0.5){
                color = 2.0f*(hamburger[i][j]/255.0f) * (hotdog[i][j]/255.0f);
                color = (color*255.0f)+0.5f;
            }
            else{
                color = 2.0f*(1-(hamburger[i][j]/255.0f)) * (1-(hotdog[i][j]/255.0f));
                color = (1 - color)*255.0f+0.5f;
            }
            color = static_cast<unsigned char>(color);
            condiment.push_back(color);
        }
        FF.getPixelDeep()->push_back(condiment);
    }
    return (FF);
}

Tga Manipulator::combineIndividual(Tga Uno, Tga Dos, string channel) {
    Tga Kitchen;
    vector<vector<unsigned char>> Fridge = Uno.getPixelShallow();
    vector<vector<unsigned char>> Microwave = Dos.getPixelShallow();
    Kitchen.setHeader(Uno.getHeader());
    Kitchen.setPixelCount(Uno.getPixelCount());
    if (channel=="blue"){
        for (int i=0;i<Kitchen.getPixelCount();i++){
            Fridge[i][0]=Microwave[i][0];
            Kitchen.getPixelDeep()->push_back(Fridge[i]);
        }
    }
    if (channel=="green"){
        for (int i=0;i<Kitchen.getPixelCount();i++){
            Fridge[i][1]=Microwave[i][1];
            Kitchen.getPixelDeep()->push_back(Fridge[i]);
        }
    }
    if (channel=="red"){
        for (int i=0;i<Kitchen.getPixelCount();i++){
            Fridge[i][2]=Microwave[i][2];
            Kitchen.getPixelDeep()->push_back(Fridge[i]);
        }
    }
    return (Kitchen);
}

Tga Manipulator::multiplyChannel(Tga Uno, string channel, float scale) {
    Tga Gru;
    vector<vector<unsigned char>> Minion = Uno.getPixelShallow();
    Gru.setHeader(Uno.getHeader());
    Gru.setPixelCount(Uno.getPixelCount());
    for (int i=0;i<Gru.getPixelCount();i++){
        float Nefario;
        int Bob=NULL;
        if (channel=="blue"){
            Bob=0;
            Nefario=Minion[i][0]*scale;
        }
        if (channel=="green"){
            Bob=1;
            Nefario=Minion[i][1]*scale;
        }
        if (channel=="red"){
            Bob=2;
            Nefario=Minion[i][2]*scale;
        }
        if (Nefario>255){
            Nefario=255;
        }
        Nefario+=0.5f;
        Minion[i][Bob]=static_cast<unsigned char>(Nefario);
        Gru.getPixelDeep()->push_back(Minion[i]);
    }
    return (Gru);
}

Tga Manipulator::addChannel(Tga Uno, string channel, int amount) {

}

Tga Manipulator::flip(Tga Uno) {
    Tga Sumo;
    vector<vector<unsigned char>> Reverse = Uno.getPixelShallow();
    Sumo.setHeader(Uno.getHeader());
    Sumo.setPixelCount(Uno.getPixelCount());
    for(int i=Sumo.getPixelCount();i>=0;i--){
        Sumo.getPixelDeep()->push_back(Reverse[i]);
    }
    return (Sumo);
}

Tga Manipulator::singleChannel(Tga Uno, string channel) {

}