#include "Districts.h" //<iostream> included there

int main() {
    std::cout << "Great District Wars 2021\nby Justin Sham"
    << std::endl << std::endl <<
    "Please choose mode:" << std::endl
    << "1. " << DISTCOUNCIL << " Districts in " << LEGCO_GC_201X << " Colours" << std::endl
    << "2. " << DISTCOUNCIL << " Districts in " << DISTCOUNCIL << " Colours" << std::endl
    << "3. " << ELECTORAL << " Districts in " << LEGCO_GC_201X << " Colours" << std::endl
    << "4. " << ELECTORAL << " Districts in " << LEGCO_GC_202X << " Colours" << std::endl
    << "5. " << ELECTORAL << " Districts in " << DISTCOUNCIL << " Colours" << std::endl;
    //Colour::start_world(LEGCO_GC_201X);
    return 0;
}