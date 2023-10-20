#include <iostream>
#include <vector>
#include <string>
#include "aheader.h"
using namespace std;


int main(int arg, char* argv[]) {

    Manipulator Manning;

    //declaration of independent files
    Tga car = Tga("./input/car.tga");
    Tga circles = Tga("./input/circles.tga");
    Tga layer_blue = Tga("./input/layer_blue.tga");
    Tga layer_green = Tga("./input/layer_green.tga");
    Tga layer_red = Tga("./input/layer_red.tga");
    Tga layer1 = Tga("./input/layer1.tga");
    Tga layer2 = Tga("./input/layer2.tga");
    Tga pattern1 = Tga("./input/pattern1.tga");
    Tga pattern2 = Tga("./input/pattern2.tga");
    Tga text = Tga("./input/text.tga");
    Tga text2 = Tga("./input/text2.tga");

    //uno
    Tga eins = Manning.multiply(layer1, pattern1);
    eins.writeTga("./output/part1.tga");

    //dos
    Tga zwei = Manning.subtract(car,layer2);
    zwei.writeTga("./output/part2.tga");

    //tres
    Tga drei1 = Manning.multiply(layer1, pattern2);
    Tga drei2 = Manning.screen(drei1, text);
    drei2.writeTga("./output/part3.tga");

    //quatro
    Tga vier1 = Manning.multiply(layer2,circles);
    Tga vier2 = Manning.subtract(vier1,pattern2);
    vier2.writeTga("./output/part4.tga");

    //cinco
    Tga funf = Manning.overlay(layer1,pattern1);
    funf.writeTga("./output/part5.tga");

    //seis
    Tga sechs = Manning.addChannel(car, "green", 200);
    sechs.writeTga("./output/part6.tga");

    //siete
    Tga sieben = Manning.multiplyChannel(car, "red", 4.0);
    sieben = Manning.multiplyChannel(sieben, "blue", 0.0);
    sieben.writeTga("./output/part7.tga");

    //ocho
    Tga acht = car ;
    acht.writeChannel("./output/part8_r.tga","red");
    acht.writeChannel("./output/part8_g.tga","green");
    acht.writeChannel("./output/part8_b.tga","blue");

    //nueve
    Tga neun = Manning.combineIndividual(layer_red,layer_green,"red");
    neun = Manning.combineIndividual(neun, layer_blue,"blue");
    neun.writeTga("./output/neun.tga");

    //diez
    Tga zehn = Manning.flip(text2);
    zehn.writeTga("./output/zehn.tga");

}
