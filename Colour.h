#ifndef _COLOUR_H
#define _COLOUR_H
class District;
#include <iostream>
#include <string>
#include <list>
class Colour {
  private:
    std::string name;
    int argb; //argb means the colour shown on screen
    std::list<District*> area;
  public:
    //Initialize the "colours" of the game, -1 if unsuccessful
    static int start_world(int worlds);

    //Announce that this "colour" has "unified" the game world
    int unif();
    void add_d(District *);
    void lose_d(District *);
    //Set attributes of a Colour.
    void setattrib(std::string name, int argb=0xFF000000) {
      this->name=name; setcolor(argb);
      std::cout<<"Colour name: "<<name<<" init."<<std::endl; //for debug
    }
    void setcolor(int argb) {this->argb=argb;}
    bool operator==(const Colour&);
    bool operator!=(const Colour& other) {return !(*this==other);}
    uint8_t get_red() const {return this->argb >> 16;}
    uint8_t get_green() const {return this->argb >> 8;}
    uint8_t get_blue() const {return (uint8_t)(this->argb);}
    char name0() const {return name[0];}
    char name1() const {
      char temp = name[name.length()/2]; int i=0;
      while (temp==' ') temp = name[name.length()/2 + ++i];
      return temp;
    }
    char name2() const {return name[name.length()-1];}
};
#endif