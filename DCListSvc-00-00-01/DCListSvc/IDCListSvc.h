/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : IDCListSvc.h
#   Create Time   : 2020-02-08 15:07
#   Last Modified : 2020-02-08 15:07
#   Describe      :
#
# ====================================================*/
#ifndef DCListSvc__IDCListSvc_H
#define DCListSvc__IDCListSvc_H
#include "GaudiKernel/IService.h"
// #include "McTruth/McParticle.h"
// #include "EvtRecEvent/EvtRecTrack.h"
// #include "CLHEP/Vector/LorentzVector.h"

/* Decaration of the interface ID */
static const InterfaceID IID_IDCListSvc("IDCListSvc", 1, 0);

class IDCListSvc : virtual public IService {
   public:
    virtual ~IDCListSvc() {}
    static const InterfaceID& interfaceID() { return IID_IDCListSvc; }
};
#endif
