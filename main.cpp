#include "Districts.h" //<iostream> included there

//Version of the game.
#define GAME_VERSION "0.0.2022.1a1"

int main() {
    Colour* world_cols;
    District** ds;
    std::cout << "Great District Wars 2021\nby Justin Sham"
    << std::endl << "Version " << GAME_VERSION << std::endl <<
    "Please choose mode:" << std::endl
    << "1. " << DISTCOUNCIL << " Districts in " << LEGCO_GC_201X << " Colours" << std::endl
    << "2. " << DISTCOUNCIL << " Districts in " << DISTCOUNCIL << " Colours" << std::endl
    << "3. " << ELECTORAL << " Districts in " << LEGCO_GC_201X << " Colours" << std::endl
    << "4. " << ELECTORAL << " Districts in " << LEGCO_GC_202X << " Colours" << std::endl
    << "5. " << ELECTORAL << " Districts in " << DISTCOUNCIL << " Colours" << std::endl;
    const int districtmodes[5] = {DISTCOUNCIL, DISTCOUNCIL, ELECTORAL, ELECTORAL, ELECTORAL};
    const int colourmodes[5] = {LEGCO_GC_201X, DISTCOUNCIL, LEGCO_GC_201X, LEGCO_GC_202X, DISTCOUNCIL};
    int modechoice; std::cin >> modechoice;
    int worlds = Colour::start_world(world_cols, colourmodes[modechoice-1]);
    if (worlds<0) {
        std::cerr << "Colours cannot be initialized." << std::endl;
        std::cout << "Game aborted." << std::endl; std::cin.get();
        return 0;
    }
    int districts = District::init_district(ds, world_cols, districtmodes[modechoice-1], colourmodes[modechoice-1]);
    if (districts == -1) {
        std::cerr << "Number of districts is wrong." << std::endl;
        std::cout << "Game aborted." << std::endl; std::cin.get();
        return 0;
    }
    if (districts == -2) {
        std::cout << "Make sure the \"d_list.txt\" file is ready and restart the game." << std::endl; std::cin.get();
        return 0;
    }
  
    std::string c_choice;
    std::cout << "Choose colour number (starting from 0)";
    std::cin >> c_choice;
    Colour* c_this = Colour::choice(world_cols, c_choice, worlds); 
    while (c_this->alive() && !District::united(ds, districts)) {
            District::display(ds, districts); //static void District::display(int);
            std::string d_choice;
            std::cout << "Choose district code or number (starting from 0)";
            std::cin >> d_choice;
            District* d_this = District::Dist_choice(ds, d_choice, districts); /**need more implementation, probably replaced by similar
            method in the Colour class
            */
            char movement; std::cin >> movement;
            switch (movement) {
                case 'm': case 'M':
                  int war_power;
                  d_this->mobilise(*ds[0], war_power);
                break;
            }
    }
    std::cout << "Game over. Hong Kong has been united." << std::endl; std::cin.get();
    return 0;
}