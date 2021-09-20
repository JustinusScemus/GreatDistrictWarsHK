#include "Districts.h"
int Colour::start_world (int worlds) {
    switch (worlds) {
        case 5:
        worldc = new Colour[5];
        worldc[0].setattrib("Hong Kong Island");
        return worlds;
        case 18:
        worldc = new Colour[18];
        return worlds;
        default: return -1;
    }
}