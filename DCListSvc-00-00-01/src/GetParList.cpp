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

using namespace BesStdSelector;
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

bool DCListSvc::IsNewEvent() {
    SmartDataPtr<Event::EventHeader> eventHeader(eventSvc_,
                                                 "/Event/EventHeader");
    if (m_eventID == eventHeader->eventNumber() &&
        m_runID == eventHeader->runNumber()) {
        /// cout << "Info in DCListSvc::init: ";
        /// cout << "#run = " << m_runID << ", #id = " << m_eventID << endl;
        m_newEvent = false;
        return false;
    } else {
        m_runID = eventHeader->runNumber();
        m_eventID = eventHeader->eventNumber();
        m_newEvent = true;
        /// cout << "Info in DCListSvc::init : ";
        /// cout << "#run = " << m_runID << ", #id = " << m_eventID << endl;
        return true;
    }
}

bool DCListSvc::GetParList() {
    if (m_InfoLvl > 5) std::cout << "Get Particle List BEGIN!" << std::endl;
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc_,
                                          "/Event/EvtRec/EvtRecEvent");
    //  if (!evtRecEvent) return false;

    SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc_,
                                                "/Event/EvtRec/EvtRecTrackCol");
    // if (!evtRecTrackCol) return false;

    EvtRecTrackIterator track_begin = evtRecTrackCol->begin();
    EvtRecTrackIterator track_end =
        evtRecTrackCol->begin() + evtRecEvent->totalCharged();

    if (m_InfoLvl > 5)
        cout << "total tracks " << track_end - track_begin << endl;
    ParticleInf particleInfo;
    particleInfo.SetChildren(m_fid);
    if (m_InfoLvl > 5)
            cout << "Need " << particleInfo.Need(11) << " electron" << endl;

    if (particleInfo.NeedElectron()) {
        if (m_InfoLvl > 5)
            cout << "Need " << particleInfo.Need(11) << " electron" << endl;
        m_ElectronList =
            CDElectronList(track_begin, track_end, primaryElectronSelector);
        m_ElectronAllList =
            CDElectronList(track_begin, track_end, secondaryElectronSelector);
        if (m_ElectronList.empty() && m_ElectronAllList.empty()) return false;

        if (m_InfoLvl > 6) {
            printInfo(particleInfo.Name(11), m_ElectronList.size());
        }
    }

    if (particleInfo.NeedPion()) {
        m_PionPrimaryList =
            CDChargedPionList(track_begin, track_end, primaryPionSelector);
        m_PionAllList =
            CDChargedPionList(track_begin, track_end, secondaryPionSelector);

        if (m_PionPrimaryList.empty() && m_PionAllList.empty()) return false;

        if (m_InfoLvl > 6) {
            printInfo(particleInfo.Name(211), m_PionPrimaryList.size(),
                      m_PionAllList.size());
            // Print(m_PionAllList);
        }
    }

    if (particleInfo.NeedKaon()) {
        m_KaonPrimaryList =
            CDChargedKaonList(track_begin, track_end, primaryKaonSelector);
        m_KaonAllList =
            CDChargedKaonList(track_begin, track_end, secondaryKaonSelector);

        if (m_KaonPrimaryList.empty() && m_KaonAllList.empty()) return false;

        if (m_InfoLvl > 6) {
            printInfo(particleInfo.Name(321), m_KaonPrimaryList.size(),
                      m_KaonAllList.size());
            // Print(m_KaonAllList);
        }
    }

    if (particleInfo.NeedProton()) {
        m_ProtonPrimaryList =
            CDProtonList(track_begin, track_end, primaryProtonSelector);
        m_ProtonAllList =
            CDProtonList(track_begin, track_end, secondaryProtonSelector);

        if (m_ProtonPrimaryList.empty() && m_ProtonAllList.empty()) {
            return false;
        }

        if (m_InfoLvl > 6) {
            printInfo(particleInfo.Name(2212), m_ProtonPrimaryList.size(),
                      m_ProtonAllList.size());
        }
    }

    if (particleInfo.NeedKs()) {
        SmartDataPtr<EvtRecVeeVertexCol> recVeeCol(
            eventSvc_, "/Event/EvtRec/EvtRecVeeVertexCol");
        if (!recVeeCol) return false;

        CDKsList KsList(ksSelector);
        dc_fill(KsList, recVeeCol->begin(), recVeeCol->end());
        m_KsList = KsList;

        if (m_KsList.empty()) return false;

        if (m_InfoLvl > 6) {
            printInfo(particleInfo.Name(310), m_KsList.size());
            // Print(m_KsList);
        }
    }

    if (particleInfo.NeedPhoton()) {
        if (soloPhotonSelector.vetoPi0()) {
            SmartDataPtr<EvtRecPi0Col> recPi0Col(Algorithm::eventSvc_,
                                                 "/Event/EvtRec/EvtRecPi0Col");
            CDPi0List Pi0List(pi0Selector);
            dc_fill(Pi0List, recPi0Col->begin(), recPi0Col->end());

            // fill into  the vector
            vector<const EvtRecPi0*> _pi0s;
            for (CDPi0List::iterator itr = Pi0List.particle_begin();
                 itr != Pi0List.particle_end(); ++itr) {
                const EvtRecPi0* navPi0 =
                    (*itr).particle().decay().child(0).navPi0();
                _pi0s.push_back(navPi0);
            }
            BesStdSelector::soloPhotonSelector.setPi0s(_pi0s);
        }
        EvtRecTrackIterator neu_begin =
            evtRecTrackCol->begin() + evtRecEvent->totalCharged();
        EvtRecTrackIterator neu_end = evtRecTrackCol->end();

        m_PhotonList = CDPhotonList(neu_begin, neu_end, soloPhotonSelector);

        if (particleInfo.NeedPhoton() && m_PhotonList.empty()) return false;

        if (m_InfoLvl > 6) {
            printInfo(particleInfo.Name(22), m_PhotonList.size());
            // Print(m_PhotonList);
        }
    }

    if (particleInfo.NeedPi0()) {
        SmartDataPtr<EvtRecPi0Col> recPi0Col(Algorithm::eventSvc_,
                                             "/Event/EvtRec/EvtRecPi0Col");
        if (!recPi0Col) return false;

        if (m_InfoLvl > 5) {
            std::cout << "EvtRecPi0Col Size: " << recPi0Col->size()
                      << std::endl;
        }
        CDPi0List Pi0List(BesStdSelector::pi0Selector);
        dc_fill(Pi0List, recPi0Col->begin(), recPi0Col->end());
        m_Pi0List = Pi0List;

        if (m_Pi0List.empty()) return false;

        if (m_InfoLvl > 6) {
            printInfo(particleInfo.Name(111), m_Pi0List.size());
        }
    }

    if (particleInfo.NeedEta()) {
        SmartDataPtr<EvtRecEtaToGGCol> evtRecEtaToGGCol(
            eventSvc_, "/Event/EvtRec/EvtRecEtaToGGCol");
        if (!evtRecEtaToGGCol) return false;

        CDEtaList EtaGGList(BesStdSelector::etatoGGSelector);
        dc_fill(EtaGGList, evtRecEtaToGGCol->begin(), evtRecEtaToGGCol->end());
        m_EtaList = EtaGGList;

        if (particleInfo.NeedEta() && m_EtaList.empty()) return false;

        if (m_InfoLvl > 6) {
            printInfo(particleInfo.Name(221), m_EtaList.size());
        }
    }

    return true;
}

void DCListSvc::GetChargedList(int pid) {

}

