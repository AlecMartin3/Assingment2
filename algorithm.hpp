//
// Created by Alec on 2019-12-01.
//

#ifndef ASSINGMENT2_ALGORITHM_HPP
#define ASSINGMENT2_ALGORITHM_HPP

#include <random>
#include <iostream>
#include <vector>
#include "city.hpp"
#include "tour.hpp"
#include <algorithm>
#include <iterator>
using namespace std;

class algorithm {
public:
    int CITIES_IN_TOUR = 32;
    unsigned long POPULATION_SIZE = 32;
    int MAP_BOUNDARY = 1000;

    algorithm();
    void shuffle_cities(tour& t);
};


#endif //ASSINGMENT2_ALGORITHM_HPP
