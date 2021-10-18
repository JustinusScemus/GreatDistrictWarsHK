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
    int worlds = Colour::start_world(colourmodes[modechoice-1]);
    if (worlds<0) {
        std::cerr << "Colours cannot be initialized." << std::endl;
        std::cout << "Game aborted." << std::endl; std::cin.get();
        return 0;
    }
    int districts = District::init_district(districtmodes[modechoice-1]);
    switch (districts) {
        case -1:
        std::cerr << "Number of districts is wrong." << std::endl;
        std::cout << "Game aborted." << std::endl; std::cin.get();
        return 0;
        case -2:
        std::cout << "Make sure the \"d_list.txt\" file is ready and restart the game." << std::endl; std::cin.get();
        return 0;
        default:
        while (!District::united()) {}
        std::cout << "Game over. Hong Kong has been united." << std::endl; std::cin.get();
    }
    return 0;
}