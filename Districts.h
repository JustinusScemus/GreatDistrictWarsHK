//Two types of objects: Districts and Colours
#ifndef _DISTRICTS_H
#define _DISTRICTS_H
#include <iostream>
#include <string>
class Colour {
  private:
    std::string name;
    int argb; //argb means the colour shown on screen
  public:
    static int start_world(int worlds); //initialize the "colours" of the game, -1 if unsuccessful
    void setattrib(std::string name, int argb=0) {this->name=name; this->argb=argb; std::cout<<"Colour name: "<<name<<" init.";}
} *worldc;

class District {
  //Districts are physical districts that are assigned a colour but changes during the game
  private:
    int landpower; //Islands is assigned to be largest while Y.T.M. is assigned to be smallest
    int fiscalpower; //C&W assigned to be largest while Islands assigned to be smallest
    Colour& currcolor;
};
#endif //_DISTRICTS_H