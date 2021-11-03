#include "Districts.h" //<iostream> included there

int main() {
    std::cout << "Great District Wars 2021\nby Justin Sham"
    << std::endl << "Version 0.0" << std::endl <<
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
    int districts = District::init_district(districtmodes[modechoice-1], colourmodes[modechoice-1]);
    if (districts == -1) {
        std::cerr << "Number of districts is wrong." << std::endl;
        std::cout << "Game aborted." << std::endl; std::cin.get();
        return 0;
    }
    if (districts == -2) {
        std::cout << "Make sure the \"d_list.txt\" file is ready and restart the game." << std::endl; std::cin.get();
        return 0;
    }
    
    std::string d_choice;
    std::cout << "Choose district code or number (starting from 0)";
    std::cin >> d_choice;
    District* d_this = District::Dist_choice(d_choice, districts); //need more implementation
    while (d_this && !District::united(districts)) {
            District::display(districts); //static void District::display(int);
            char movement; std::cin >> movement;
            switch (movement) {
                case 'm': case 'M':
                  int war_power;
                  //d_this->mobilise(ds[0], war_power);
                break;
            }
    }
    std::cout << "Game over. Hong Kong has been united." << std::endl; std::cin.get();
    return 0;
}