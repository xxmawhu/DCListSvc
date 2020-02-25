/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : GetParList.cpp
#   Create Time   : 2020-02-24 18:14
#   Last Modified : 2020-02-24 18:39
#   Describe      :
#
# ====================================================*/
#include "EvtRecEvent/EvtRecEtaToGG.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecPi0.h"

#include "HadronInfo/ParticleInf.h"
#include "BesStdSelector/Selector.h"
//#include "BesStdSelector/Proton.h"

#include "DCListSvc/DCListSvc.h"
#include "DCListSvc/util.h"

using namespace BesStdSelector;
CDDecayList DCListSvc::PrimaryTrk(int pid) {
    // select the primary good charged tracks, 
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc_, "/Event/EvtRec/EvtRecEvent");
    SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc_, "/Event/EvtRec/EvtRecTrackCol");

    EvtRecTrackIterator track_begin = evtRecTrackCol->begin();
    EvtRecTrackIterator track_end = evtRecTrackCol->begin() + evtRecEvent->totalCharged();

    if (m_InfoLvl > 5) {
        cout << "total tracks " << track_end - track_begin << endl;
    }
    CDDecayList trkList;

    if (abs(pid) == 11) {
        if (m_initList["m_ElectronList"]) {
            m_ElectronList = CDElectronList(track_begin, track_end, primaryElectronSelector);
            m_initList["m_ElectronList"] = false;
        }
        if (m_InfoLvl > 6) {
            printInfo("Primary electron", m_ElectronList.size());
        }
        if (pid > 0){
            trkList = m_ElectronList.plus();
        } else {
            trkList = m_ElectronList.minus();
        }
        return trkList;
    }

    if (abs(pid) == 211) {
        if (m_initList["m_PionPrimaryList"]) {
            m_PionPrimaryList =
                CDChargedPionList(track_begin, track_end, primaryPionSelector);
            m_initList["m_PionPrimaryList"] = false;
        }
        if (m_InfoLvl > 6) {
            printInfo("Primary pi+", m_PionPrimaryList.size(),
                      m_PionAllList.size());
            // Print(m_PionAllList);
        }
        if (pid > 0) {
            trkList = m_PionPrimaryList.plus();
        } else{
            trkList = m_PionPrimaryList.minus();
        }
        return trkList;
    }

    if (abs(pid) == 321) {
        if (m_initList["m_KaonPrimaryList"]) {
            m_KaonPrimaryList =
                CDChargedKaonList(track_begin, track_end, primaryKaonSelector);
            m_initList["m_KaonPrimaryList"] = false;
        }
        if (m_InfoLvl > 6) {
            printInfo("Primary K+", m_KaonPrimaryList.size(),
                      m_KaonAllList.size());
            // Print(m_KaonAllList);
        }
        if (pid > 0) {
            trkList = m_KaonPrimaryList.plus();
        } else{
            trkList = m_KaonPrimaryList.minus();
        }
        return trkList;
    }

    if (abs(pid) == 2212) {
        if (m_initList["m_ProtonPrimaryList"]) {
            m_ProtonPrimaryList =
                CDProtonList(track_begin, track_end, primaryProtonSelector);
            m_initList["m_ProtonPrimaryList"] = false;
        }
        if (m_InfoLvl > 6) {
            printInfo("Primary proton", m_ProtonPrimaryList.size(),
                      m_ProtonAllList.size());
        }
        if (pid > 0) {
            trkList = m_ProtonPrimaryList.plus();
        } else{
            trkList = m_ProtonPrimaryList.minus();
        }
        return trkList;
    }
}

CDDecayList DCListSvc::SecondaryTrk(int pid) {
    CDDecayList trkList;
    // select the all good charged tracks, 
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc_, "/Event/EvtRec/EvtRecEvent");
    SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc_, "/Event/EvtRec/EvtRecTrackCol");

    EvtRecTrackIterator track_begin = evtRecTrackCol->begin();
    EvtRecTrackIterator track_end = evtRecTrackCol->begin() + evtRecEvent->totalCharged();

    if (m_InfoLvl > 5) {
        cout << "total tracks " << track_end - track_begin << endl;
    }

    if (abs(pid) == 11) {
        if (m_initList["m_ElectronAllList"]) {
            m_ElectronAllList = CDElectronList(track_begin, track_end, primaryElectronSelector);
            m_initList["m_ElectronAllList"] = false;
        }
        if (m_InfoLvl > 6) {
            printInfo("Secondary electron", m_ElectronAllList.size());
        }
        if (pid > 0){
            trkList = m_ElectronAllList.plus();
        } else {
            trkList = m_ElectronAllList.minus();
        }
        return trkList;
    }

    if (abs(pid) == 211) {
        if (m_initList["m_PionAllList"]) {
            m_PionAllList =
                CDChargedPionList(track_begin, track_end, primaryPionSelector);
            m_initList["m_PionAllList"] = false;
        }
        if (m_InfoLvl > 6) {
            printInfo("Pion", m_PionAllList.size(),
                      m_PionAllList.size());
            // Print(m_PionAllList);
        }
        if (pid > 0) {
            trkList = m_PionAllList.plus();
        } else{
            trkList = m_PionAllList.minus();
        }
        return trkList;
    }

    if (abs(pid) == 321) {
        if (m_initList["m_KaonAllList"]) {
            m_KaonAllList =
                CDChargedKaonList(track_begin, track_end, primaryKaonSelector);
            m_initList["m_KaonAllList"] = false;
        }
        if (m_InfoLvl > 6) {
            printInfo("Kaon", m_KaonAllList.size(),
                      m_KaonAllList.size());
            // Print(m_KaonAllList);
        }
        if (pid > 0) {
            trkList = m_KaonAllList.plus();
        } else{
            trkList = m_KaonAllList.minus();
        }
        return trkList;
    }

    if (abs(pid) == 2212) {
        if (m_initList["m_ProtonAllList"]) {
            m_ProtonAllList =
                CDProtonList(track_begin, track_end, primaryProtonSelector);
            m_initList["m_ProtonAllList"] = false;
        }
        if (m_InfoLvl > 6) {
            printInfo("Secondary Proton", m_ProtonAllList.size(),
                      m_ProtonAllList.size());
        }
        if (pid > 0) {
            trkList = m_ProtonAllList.plus();
        } else {
            trkList = m_ProtonAllList.minus();
        }
        return trkList;
    }
}

CDDecayList& DCListSvc::Shower(bool seleSoloPhoton) {
    // good photon
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc_, "/Event/EvtRec/EvtRecEvent");
    SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc_, "/Event/EvtRec/EvtRecTrackCol");
    EvtRecTrackIterator neu_begin = evtRecTrackCol->begin() + evtRecEvent->totalCharged();
    EvtRecTrackIterator neu_end = evtRecTrackCol->end();

    if (seleSoloPhoton) {
        if (m_initList["m_PhotonSoloList"]) {
            if (soloPhotonSelector.vetoPi0()){
                soloPhotonSelector.setPi0List(DecayList(111));
            }
            m_PhotonSoloList = CDPhotonList(neu_begin, neu_end, soloPhotonSelector);
            m_initList["m_PhotonSoloList"] = false;
        }
        return m_PhotonSoloList;
    } else {
        if (m_initList["m_PhotonList"]) {
            cout << "fill photon list " << endl;
            m_PhotonList = CDPhotonList(neu_begin, neu_end, photonSelector);
            cout << "photon size" << m_PhotonList.size() << endl;
            m_initList["m_PhotonList"] = false;
        }
        return m_PhotonList;
    }
}

CDDecayList& DCListSvc::SoloPhoton() {
    return Shower(true);
}

CDDecayList& DCListSvc::Photon() {
    return Shower(false);
}
