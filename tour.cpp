//
// Created by Alec on 2019-12-01.
//

#include "tour.hpp"

/*
 * Tour constructor
 * Makes a new tour
 */
tour:: tour(){
    fitness = 0.0;
    city c = {'a', 0, 0};
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        cities.push_back(c);
    }
}