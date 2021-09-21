#include "Districts.h"
int Colour::start_world (int worlds) {
    switch (worlds) {
        case LEGCO_GC_201X:
        worldc = new Colour[LEGCO_GC_201X];
        worldc[0].setattrib("Hong Kong Island");
        worldc[1].setattrib("Kowloon West");
        worldc[2].setattrib("Kowloon East");
        worldc[3].setattrib("New T West");
        worldc[4].setattrib("New T East");
        return worlds;
        case DISTCOUNCIL:
        worldc = new Colour[DISTCOUNCIL];
        return worlds;
        default: return -1;
    }
}