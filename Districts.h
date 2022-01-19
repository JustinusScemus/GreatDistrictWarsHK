//Two types of objects: Districts and Colours
#ifndef _DISTRICTS_H
#define _DISTRICTS_H

#include <iostream>
#include <string>
#include <unordered_set>

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
    unsigned int currpower;
    std::string name;
    Colour* currcolor;
    struct co_ord{
      int x,y;
    } * polygon;
    std::unordered_set<District*> neighbours; //Array of pointers to neighbouring districts
    //int neighbourcount;
  public:
    District();
    District(int l, int f, Colour* cc, std::string name);
    static int init_district(District**, Colour*, int d_count, int col_count); //Initialize the "districts" of the game, -1 if unsuccessful
    static District* Dist_choice(District**, std::string input, int districts);
    void addneigh(District*); //attaching another district as a neighbour, and stays during the game
    bool mobilise(District&, int); //return value is whether successful
    static bool united(District**, int);
    static void display(District**, int);
  friend class Colour;
};

#endif //_DISTRICTS_H
