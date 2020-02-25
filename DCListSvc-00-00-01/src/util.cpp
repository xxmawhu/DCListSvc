/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : util.cpp
#   Create Time   : 2020-03-14 20:56
#   Last Modified : 2020-03-14 20:56
#   Describe      :
#
# ====================================================*/

#include "EvtRecEvent/EvtRecEtaToGG.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecPi0.h"

#include "HadronInfo/ParticleInf.h"
#include "BesStdSelector/Selector.h"
//#include "BesStdSelector/Proton.h"
#include "BesDChain/CDDecayList.h"


void printInfo(const std::string& name, const int& primary,
                      const int& all) {
    std::cout << "Need to reconstruct the " << name << std::endl << "And find "
              << all << " candidates in total, "
              << "in which, the number of primary ones is " << primary
              << std::endl;
}

void printInfo(const std::string& name, const int& size) {
    std::cout << "Need to reconstruct the " << name << std::endl << "And find "
              << size << " candidates." << std::endl;
}

void print(const CDDecayList& signal) {
    std::cout << "size = " << signal.size() << std::endl;
}
