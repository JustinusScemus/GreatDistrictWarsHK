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
    const int districtmodes[5] = {DISTCOUNCIL, DISTCOUNCIL, ELECTORAL, ELECTORAL, ELECTORAL};
    const int colourmodes[5] = {LEGCO_GC_201X, DISTCOUNCIL, LEGCO_GC_201X, LEGCO_GC_202X, DISTCOUNCIL};
    int modechoice; std::cin >> modechoice;
    Colour::start_world(colourmodes[modechoice-1]);
    District::init_district(districtmodes[modechoice-1]);
    while (!District::united(ds)) {}
    std::cout << "Game over. Hong Kong has been united."; std::cin.get();
    return 0;
}