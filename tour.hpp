//
// Created by Alec on 2019-12-01.
//

#ifndef ASSINGMENT2_TOUR_HPP
#define ASSINGMENT2_TOUR_HPP

#include <vector>
#include "city.hpp"
using namespace std;
/**
 * Tour class
 * Used by the algorithm as a list of cities
 */
class tour {
public:
    const int CITIES_IN_TOUR = 32;
    double fitness;
    vector<city> cities;
    tour();
    tour & operator=(tour t);

};


#endif //ASSINGMENT2_TOUR_HPP
