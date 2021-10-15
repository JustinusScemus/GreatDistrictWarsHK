#include "Districts.h"
Colour* world_cols;
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
        world_cols[0].setattrib("Central & Western");
        world_cols[1].setattrib("Wan Chai");
        world_cols[2].setattrib("Eastern");
        world_cols[3].setattrib("Southern");
        world_cols[4].setattrib("Yau Tsim Mong");
        world_cols[5].setattrib("Sham Shui Po");
        world_cols[6].setattrib("Kowloon City");
        world_cols[7].setattrib("Wong Tai Sin");
        world_cols[8].setattrib("Kwun Tong");
        return worlds;
        case LEGCO_GC_202X:
        default: return -1;
    }
}
District::District(int l, int f, Colour& cc, std::string name):
landpower(l), fiscalpower(f),
currcolor(cc), name(name),
polygon(nullptr), neighbours(nullptr), neighbourcount(0) {}

void District::addneigh(District* d) {
    District** temp = new District*[neighbourcount+1];
    for (int i=0; i < neighbourcount; i++) {
        temp[i] = neighbours[i];
    }
    temp[neighbourcount] = d;
    delete [] neighbours;
    neighbours = temp;
    neighbourcount++;
}