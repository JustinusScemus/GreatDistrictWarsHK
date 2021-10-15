#include "Districts.h"
int Colour::start_world (int worlds) {
    switch (worlds) {
        case LEGCO_GC_201X:
        world_cols = new Colour[LEGCO_GC_201X];
        world_cols[0].setattrib("Hong Kong Island");
        world_cols[1].setattrib("Kowloon West");
        world_cols[2].setattrib("Kowloon East");
        world_cols[3].setattrib("New T West");
        world_cols[4].setattrib("New T East");
        return worlds;
        case DISTCOUNCIL:
        world_cols = new Colour[DISTCOUNCIL];
        return worlds;
        default: return -1;
    }
}
District::District(int l, int f, Colour& cc, std::string name):
landpower(l), fiscalpower(f),
currcolor(cc), name(name),
polygon(nullptr), neighbours(nullptr), neighbourcount(0) {}

void District::addneigh(District* d) {}