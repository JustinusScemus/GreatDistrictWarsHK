//Two types of objects: Districts and Colours
#include <string>
class Colours {
  private:
    std::string name;
    int argb; //argb means the colour shown on screen
};

class District {
  private:
    int landpower; //Islands is assigned to be largest while Y.T.M. is assigned to be smallest
    int fiscalpower; //C&W assigned to be largest while Islands assigned to be smallest
};
