#include "Districts.h"
#include "Colour.h"

#include <fstream>
#include <sstream>
//Colour* world_cols; Changed to local variable
int Colour::start_world (Colour*& world_cols, int worlds) {
    switch (worlds) {
        case LEGCO_GC_201X:
        world_cols = new Colour[LEGCO_GC_201X];
        world_cols[0].setattrib("Hong Kong Island");
        world_cols[1].setattrib("Kowloon West");
        world_cols[2].setattrib("Kowloon East");
        world_cols[3].setattrib("New T West");
        world_cols[4].setattrib("New T East");
        return worlds;
        case DISTCOUNCIL:
        world_cols = new Colour[DISTCOUNCIL];
        world_cols[0].setattrib("Central & Western"); world_cols[9].setattrib("Tsuen Wan");
        world_cols[1].setattrib("Wan Chai"); world_cols[10].setattrib("Tuen Mun");
        world_cols[2].setattrib("Eastern"); world_cols[11].setattrib("Yuen Long");
        world_cols[3].setattrib("Southern"); world_cols[12].setattrib("North");
        world_cols[4].setattrib("Yau Tsim Mong"); world_cols[13].setattrib("Tai Po");
        world_cols[5].setattrib("Sham Shui Po"); world_cols[14].setattrib("Sai Kung");
        world_cols[6].setattrib("Kowloon City"); world_cols[15].setattrib("Sha Tin");
        world_cols[7].setattrib("Wong Tai Sin"); world_cols[16].setattrib("Kwai Tsing");
        world_cols[8].setattrib("Kwun Tong"); world_cols[17].setattrib("Islands");
        return worlds;
        case LEGCO_GC_202X:
        world_cols = new Colour[LEGCO_GC_202X];
        world_cols[0].setattrib("Island East");
        world_cols[1].setattrib("Island West");
        world_cols[2].setattrib("Kowloon East");
        world_cols[3].setattrib("Kowloon West");
        world_cols[4].setattrib("Kowloon Central");
        world_cols[5].setattrib("NT South East");
        world_cols[6].setattrib("NT North");
        world_cols[7].setattrib("NT North West");
        world_cols[8].setattrib("NT South West");
        world_cols[9].setattrib("NT North East");
        return worlds;
        default: return -1;
    }
}
Colour* Colour::choice(Colour*& world_cols, std::string input, int c_count) {
    if (input[0] >= '0' && input[0] <= '9') {
        int a = std::stoi (input);
        if (a >= 0 && a < c_count) {
            return &world_cols[a];
        }
    }
    return nullptr;
}

int Colour::unif() {
    return argb;
}
void Colour::add_d(District* d) {
    area.insert(d);
}
void Colour::lose_d(District* d) {
    area.erase(d);
}
bool Colour::operator==(const Colour& other) {
    return (this->name == other.name);
}
bool Colour::alive() {
    return !(area.empty());
}

//End of Colour functions
//Start of District functions

//District** ds; Array of pointers to districts

District::District() : landpower(0), fiscalpower(0), currcolor(nullptr) {}
int District::init_district(District**& ds, Colour*& cs, int d_count, int col_count){
    switch (d_count)
    {
    case DISTCOUNCIL: case ELECTORAL:
        ds = new District*[d_count];
        break;
    default: return -1;
    }
    
    std::string filename="d_list.txt";
    std::ifstream d_list(filename, std::ios_base::in);// bool pass=false;
    if (!d_list.good()){
        std::cerr << "Required file: \"d_list.txt\" not found." << std::endl;
        delete[] ds;
        return -2;
    }
    std::string mode, desiredmode;
    switch (d_count)
    {
    case DISTCOUNCIL:
        desiredmode = "DISTC";
        break;
    case ELECTORAL:
        desiredmode = "ELCTR";
    default:
        break;
    }
    while (desiredmode!=mode) {
        //std::cout << mode << " " << desiredmode << std::endl; for debug
        std::getline(d_list, mode);
    }
    int d_iter = 0;
    do {
        std::string temp_name, temp_dist, temp_polygon; int temp_land, temp_fiscal, col_index_10, col_index_20, col_index_dist;
        d_list >> temp_name >> temp_land >> temp_fiscal >> col_index_10 >> col_index_20 >> col_index_dist;
        getline(d_list, temp_polygon);
        if (temp_name[0] == '#') {
            std::cout << "Comment\n"; continue;
        }
        std::cout << "Dist: " << temp_name << " has landpower " << temp_land << " and fiscalpower " << temp_fiscal << ", ";
        int col_index;
        switch (col_count)
        {
        case LEGCO_GC_201X:
            col_index = col_index_10;
            break;
        case LEGCO_GC_202X:
            col_index = col_index_20;
            break;
        case DISTCOUNCIL:
            col_index = col_index_dist;
            break;
        default:
            break;
        }
        ds[d_iter] = new District(temp_land, temp_fiscal, &cs[col_index], temp_name);
        std::cout << "Belongs to " << cs[col_index].name0() << '.' << cs[col_index].name1() << '.' << cs[col_index].name2() << ' ' << col_index << std::endl;
        cs[col_index].add_d(ds[d_iter]);
        std::string temp_neigh = temp_polygon.substr(0, temp_polygon.find('P') - 1);
        if (!temp_neigh.empty()) {
            std::istringstream neigh_stream(temp_neigh);
            //It is decided that only the District pointer with the higher index would initiate the adding of the lower neighbour
            //If all the neighbours have higher index than itself, then "this" district would temporarily be isolated.
            std::string parsed_neigh; //parsed_neigh may be negative, such that relative referencing can be made.
            neigh_stream>>parsed_neigh; //It should contain the first neighbour with the prefix N.
            std::cout << "Parsed first neighbour: " << parsed_neigh << '\t'; //for debug
            int neigh_index = std::stoi(parsed_neigh.substr(1));
            if (neigh_index < 0) neigh_index = d_iter + neigh_index;
            ds[d_iter]->addneigh(ds[neigh_index]);
            while (!neigh_stream.eof()) {
                neigh_stream >> parsed_neigh;
                std::cout << "Parsed neighbour: " << parsed_neigh << '\t'; //for debug
                neigh_index = std::stoi(parsed_neigh);
                if (neigh_index < 0) neigh_index = d_iter + neigh_index;
                ds[d_iter]->addneigh(ds[neigh_index]);
            }
        }//if temp_neigh contains things
        //TODO: Storing of polygon
        d_iter++;
        std::cout << std::endl; //for debug
    } while (d_iter<d_count && !d_list.eof());
    d_list.close();
    if (d_iter<d_count) {
        delete[] ds;
        return -1;
    }
    return d_count;
}
District::District(int l, int f, Colour* cc, std::string name):
landpower(l), fiscalpower(f),
currcolor(cc), name(name),
polygon(nullptr)/**, neighbourcount(0)*/ {}

District* District::Dist_choice(District** ds, std::string input, int districts) {
    if (input[0] >= '0' && input[0] <= '9') {
        int a = std::stoi (input);
        if (a >= 0 && a < districts) {
            return ds[a];
        }
    }
    return nullptr;
}

void District::addneigh(District* d) {
    //It should be bidirectional
    neighbours.insert(d);
    d->neighbours.insert(this);
    std::cout << ' ' << this->name << " neighs " << d->name << "bidirec"; //for debug
}

bool District::mobilise(District& d, int warpower) {
    if (warpower > currpower) {return false;}
    currpower -= warpower;
    return true;
}

bool District::united(District** ds, int districts) {
    Colour onecolor = *(ds[0]->currcolor);
    for (int i=1; i<districts; i++) {
        if (*(ds[i]->currcolor)!=onecolor) return false;
    };
    onecolor.unif();
    return true;/***/
}

/** For DC districts, Displays in maps width 20, height 15
 *  For Electral districts, prompts for input, display maps with width 40, height 15, and exits only with "exit".
 */
void District::display(District** ds, int districts) {
    std::string input;
    switch (districts)
    {
    case DISTCOUNCIL:
        /**
         * XXXXXXX---12-XXXXXXX
         * XXXXXX/XXXXXX\XXXXXX
         * XXX-11--------13XXXX
         * XX/XX|XXXXXXX/XXXXXX
         * X10--09----15----XXX 5
         * XX|X/X|XXX/X|XX\X\XX
         * X017X16--05-06-07X|X
         * XXXXXXXXX|X/|X\|XX|X
         * XXXXXXXXX04X|X08-14X
         * XXXXXXXXX|XX|XX|XXXX 10
         * XXXXXXXX(Victoria H)
         * XXXXXXXXX|XX|XX|XXXX
         * XXXXXXXXX00-01-02XXX
         * XXXXXXXXXX\X|X/XXXXX
         * XXXXXXXXXXX03XXXXXXX
         */
        std::cout <<
        "       ---" << ds[12]->currcolor->name0() << ds[12]->currcolor->name1()
        << "-       \n";
        std::cout << "      /      \\      \n";
        std::cout << "   -" << ds[11]->currcolor->name0() << ds[11]->currcolor->name1() << "--------"
        << ds[13]->currcolor->name0() << ds[13]->currcolor->name1() << "    \n";
        std::cout << "  /  |       /      \n";
        std::cout << " " << ds[10]->currcolor->name0() << ds[10]->currcolor->name1() << "--" << ds[9]->currcolor->name0()
        << ds[9]->currcolor->name1() << "----" << ds[15]->currcolor->name0() << ds[15]->currcolor->name1() << "----   \n";
        std::cout << "  | / |   / |  \\ \\  \n";
        std::cout << ' ' << ds[17]->currcolor->name0() << ds[17]->currcolor->name1() << ds[17]->currcolor->name2()
        << ' ' << ds[16]->currcolor->name0() << ds[16]->currcolor->name1() << "--" << ds[5]->currcolor->name0()
        << ds[5]->currcolor->name1() << '-' << ds[6]->currcolor->name0() << ds[6]->currcolor->name1() << '-'
        << ds[7]->currcolor->name0() << ds[7]->currcolor->name1() << " | \n";
        std::cout << "         | /| \\|  | \n";
        std::cout << "         " << ds[4]->currcolor->name0() << ds[4]->currcolor->name1() << " | " << ds[8]->currcolor->name0()
        << ds[8]->currcolor->name1() << '-' << ds[14]->currcolor->name0() << ds[14]->currcolor->name1() << " \n";
        std::cout << "         |  |  |    \n        (Victoria H)\n         |  |  |    \n";
        std::cout << "         " << ds[0]->currcolor->name0() << ds[0]->currcolor->name1() << '-' << ds[1]->currcolor->name0()
        << ds[1]->currcolor->name1() << '-' << ds[2]->currcolor->name0() << ds[2]->currcolor->name1() << "   \n";
        std::cout << "          \\ | /     \n";
        std::cout << "           " << ds[3]->currcolor->name0() << ds[3]->currcolor->name1() << "       \n";
        return;
    case ELECTORAL:
        do {
            getline(std::cin, input);
        } while (input!="exit");
        return;
    default:
        std::cerr << "District numbers invalid." << std::endl;
        return;
    }
}
