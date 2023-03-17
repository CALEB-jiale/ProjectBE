//
// Created by Franck XU on 16/03/2023.
//

#include "MultiPersona.h"
#include <cmath>
#include <iostream>
#include <vector>

SuicideBoomer::SuicideBoomer(const Milieu *milieu, Behavior** behaviors) : Behavior(milieu), behaviors{
    LOG_DEBUG("Create SuicideBoomer behavior operand");
}

SuicideBoomer::~SuicideBoomer() { LOG_DEBUG("Destroy SuicideBoomer behavior operand"); }

