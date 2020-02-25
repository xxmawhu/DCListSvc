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
#ifndef DCListSvc_util_H
#define DCListSvc_util_H

#include "EvtRecEvent/EvtRecEtaToGG.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecPi0.h"

#include "HadronInfo/ParticleInf.h"
#include "BesStdSelector/Selector.h"
//#include "BesStdSelector/Proton.h"
#include "BesDChain/CDDecayList.h"

void printInfo(const std::string& name, const int& primary, const int& all);
void printInfo(const std::string& name, const int& size);
void print(const CDDecayList& signal);
#endif
