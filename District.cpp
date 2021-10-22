#include "Districts.h"
#include "Colour.h"

#include <fstream>
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
        world_cols[0].setattrib("Central & Western"); world_cols[9].setattrib("Tsuen Wan");
        world_cols[1].setattrib("Wan Chai"); world_cols[10].setattrib("Tuen Mun");
        world_cols[2].setattrib("Eastern"); world_cols[11].setattrib("Yuen Long");
        world_cols[3].setattrib("Southern"); world_cols[12].setattrib("North");
        world_cols[4].setattrib("Yau Tsim Mong"); world_cols[13].setattrib("Tai Po");
        world_cols[5].setattrib("Sham Shui Po"); world_cols[14].setattrib("Sai Kung");
        world_cols[6].setattrib("Kowloon City"); world_cols[15].setattrib("Sha Tin");
        world_cols[7].setattrib("Wong Tai Sin"); world_cols[16].setattrib("Kwai Tsing");
        world_cols[8].setattrib("Kwun Tong"); world_cols[17].setattrib("Islands");
        return worlds;
        case LEGCO_GC_202X:
        world_cols = new Colour[LEGCO_GC_202X];
        world_cols[0].setattrib("Island East");
        world_cols[1].setattrib("Island West");
        world_cols[2].setattrib("Kowloon East");
        world_cols[3].setattrib("Kowloon West");
        world_cols[4].setattrib("Kowloon Central");
        world_cols[5].setattrib("NT South East");
        world_cols[6].setattrib("NT North");
        world_cols[7].setattrib("NT North West");
        world_cols[8].setattrib("NT South West");
        world_cols[9].setattrib("NT North East");
        return worlds;
        default: return -1;
    }
}
int Colour::unif() {
    return argb;
}
void Colour::add_d(District* d) {
    area.push_back(d);
}
void Colour::lose_d(District* d) {
    area.remove(d);
}
bool Colour::operator==(const Colour& other) {
    return (this->name == other.name);
}

//End of Colour functions
//Start of District functions

District** ds; //Array of pointers to districts
District::District() : landpower(0), fiscalpower(0), currcolor(world_cols[0]) {}
int District::init_district(int d_count){
    switch (d_count)
    {
    case DISTCOUNCIL:
    case ELECTORAL:
        ds = new District*[d_count];
        break;
    default: return -1;
    }
    
    std::string filename="d_list.txt";
    std::ifstream d_list(filename, std::ios_base::in);// bool pass=false;
    if (!d_list.good()){
        std::cerr << "Required file: \"d_list.txt\" not found." << std::endl;
        delete[] ds;
        return -2;
    } /**File format: "Name of district" landpower fiscalpower col_index_201x col_index_202x col_index_distcouncil Nn n n Px,y,x,y,x,y
    * N denotes neighbours and P denotes the polygon vertices. P ends with a -1 notation.
    */
    char mode[6];
    d_list.getline(mode, 6);
    int d_iter = 0;
    do {
        std::string temp_name, temp_polygon; int temp_land, temp_fiscal, col_index;
        //d_list >> temp_name >> temp_land >> temp_fiscal >> col_index >> temp_polygon;
        ds[d_iter++] = new District(temp_land, temp_fiscal, world_cols[col_index], temp_name);
    } while (d_iter<d_count);
    return d_count;
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

bool District::united(int districts) {
    Colour onecolor = ds[0]->currcolor;
    for (int i=1; i<districts; i++) {
        if (ds[i]->currcolor!=onecolor) return false;
    };
    onecolor.unif();
    return true;/***/
}