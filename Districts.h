//Two types of objects: Districts and Colours
#ifndef _DISTRICTS_H
#define _DISTRICTS_H

#include <iostream>
#include <string>

//Number of LegCo Districts in Geographical Constituencies prior to 2020
#define LEGCO_GC_201X 5
#define LEGCO_GC_202X 10
#define DISTCOUNCIL 18
#define ELECTORAL 452

#include "Colour.h"
class District {
  //Districts are physical districts that are assigned a colour but changes during the game
  private:
    int landpower; //Islands is assigned to be largest while Y.T.M. is assigned to be smallest
    int fiscalpower; //C&W assigned to be largest while Islands assigned to be smallest
    std::string name;
    Colour& currcolor;
    struct co_ord{
      int x,y;
    } * polygon;
    District** neighbours; //Array of pointers to neighbouring districts
    int neighbourcount;
  public:
    District();
    District(int l, int f, Colour& cc, std::string name);
    static int init_district(int d_count); //Initialize the "districts" of the game, -1 if unsuccessful
    void addneigh(District*);
    bool mobilise(District&, int); //return value is whether successful
    static bool united(int);
};
//
#endif //_DISTRICTS_H