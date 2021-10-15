//Two types of objects: Districts and Colours

#include <iostream>
#include <string>

//Number of LegCo Districts in Geographical Constituencies prior to 2020
#define LEGCO_GC_201X 5
#define LEGCO_GC_202X 10
#define DISTCOUNCIL 18
#define ELECTORAL 452
#ifndef _DISTRICTS_H
#define _DISTRICTS_H
class Colour {
  private:
    std::string name;
    int argb; //argb means the colour shown on screen
  public:
    //Initialize the "colours" of the game, -1 if unsuccessful
    static int start_world(int worlds);

    //Announce that a "colour" has "unified" the game world
    static int unif();

    //Set attributes of a Colour.
    void setattrib(std::string name, int argb=0xFF000000) {this->name=name; setcolor(argb); std::cout<<"Colour name: "<<name<<" init.";}
    void setcolor(int argb) {this->argb=argb;}
    uint8_t get_red() const {return this->argb >> 16;}
    uint8_t get_green() const {return this->argb >> 8;}
    uint8_t get_blue() const {return (uint8_t)(this->argb);}
} *world_cols;

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
    District** neighbours; //Array of pointers to districts
    int neighbourcount;
  public:
    District() = default;
    District(int l, int f, Colour& cc, std::string name);
    void addneigh(District*);
};
#endif //_DISTRICTS_H