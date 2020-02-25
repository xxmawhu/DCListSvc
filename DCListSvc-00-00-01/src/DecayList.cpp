/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : DecayList.cpp
#   Create Time   : 2020-02-24 18:15
#   Last Modified : 2020-02-24 18:15
#   Describe      :
#
# ====================================================*/

#include "EvtRecEvent/EvtRecEtaToGG.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecPi0.h"

#include "HadronInfo/ParticleInf.h"
#include "BesStdSelector/Selector.h"
#include "TupleSvc/DecayTree.h"

#include "DCListSvc/DCListSvc.h"
#include "DTagAlg/LocalKaonSelector.h"

using BesStdSelector::primaryProtonSelector;
using BesStdSelector::secondaryProtonSelector;
CDDecayList DCListSvc::DecayList(int pid) {
    // Ks 310 ; K 321 ; Pion 211 ; Pi0 111 ; Eta 221 ; eta' 331
    // Lambda: 3122, Omega: 3334, etaV3pi 2212211, electron 11
    if (abs(pid) == 11 || abs(pid) == 211 || abs(pid) == 2212
           || abs(pid) == 321 ) {
        return PrimaryTrk(pid);
    } 
    if (pid == 22) {
        // 22 means solo photon
        return SoloPhoton();
    } 
    switch (pid) {
        case 310: 
        {
            if (m_initList["m_KsList"]) {
                CDDecayList ks(BesStdSelector::ksSelector);
                ks = SecondaryTrk(211) * SecondaryTrk(-211);
                m_KsList = ks;
                m_initList["m_KsList"] = false;
            }
            return m_KsList;
        }
        case 111:
        {
            if (m_initList["m_Pi0List"]) {
                CDDecayList pi0(BesStdSelector::pi0Selector);
                pi0 = Photon() * Photon();
                m_Pi0List = pi0;
                m_initList["m_Pi0List"] = false;
            }
            return m_Pi0List;
        }
        case 221:
        {
            if (m_initList["m_EtaList"]) {
                CDDecayList pi0(BesStdSelector::etatoGGSelector);
                pi0 = Photon() * Photon();
                m_EtaList = pi0;
                m_initList["m_EtaList"] = false;
            }
            return m_EtaList;
        }
        case 331:   
        {
            // Eta'  42.6(7)
            if (m_initList["m_EtapList"]) {
                CDDecayList EtaP(BesStdSelector::EtaPtoPiPiEtaSelector);
                EtaP = PrimaryTrk(211) * PrimaryTrk(-211) * DecayList(111);
                m_EtapList = EtaP;
                m_initList["m_EtapList"] = false;
            }
            return m_EtapList;
        }
        case 223: 
        {
            // omega  89.2(7)
            if (m_initList["m_omegaList"]) {
                CDDecayList omega(BesStdSelector::omegaSelector);
                omega = PrimaryTrk(211) * PrimaryTrk(-211) * DecayList(111);
                m_omegaList = omega;
                m_initList["m_omegaList"] = false;
            }
            return m_omegaList;
        }
        case 333:   
        {    // phi 492(5)
            CDDecayList phiList(BesStdSelector::phiSelector);
            phiList = m_KaonPrimaryList.plus() * m_KaonPrimaryList.minus();
            return phiList;
        }
        case 3122: 
        { 
            if (m_initList["m_LambdaList"]) {
                CDDecayList Lambda(BesStdSelector::lambdaSelector);
                Lambda = SecondaryTrk(2212) * SecondaryTrk(-211);
                m_LambdaList = Lambda;
                m_initList["m_LambdaList"] = false;
            }
            return m_LambdaList;
        }
        case -3122: 
        {    if (m_initList["m_LambdaBarList"]) {
               CDDecayList Lambda(BesStdSelector::lambdaSelector);
               Lambda = SecondaryTrk(-2212) * SecondaryTrk(211);
               m_LambdaBarList = Lambda;
               m_initList["m_LambdaBarList"] = false;
           }
           return m_LambdaBarList;
        }
        case 2212211: 
        {
            if (m_initList["m_EtatoPiPiPi0List"]) {
                CDDecayList Eta(BesStdSelector::etatoPiPiPi0Selector);
                Eta = SecondaryTrk(211) * SecondaryTrk(-211) * DecayList(111);
                m_EtatoPiPiPi0List = Eta;
                m_initList["m_EtatoPiPiPi0List"] = false;
            }
            return m_EtatoPiPiPi0List;
        }
        case 3212: 
        {
            if (m_initList["m_Sigma0List"]) {
                CDDecayList Sigma0(BesStdSelector::Sigma0Selector);
                Sigma0 = DecayList(3122) * Photon();
                m_SigmapList = Sigma0;
                m_initList["m_Sigma0List"] = false;
            }
            return m_Sigma0List;
        }
        case -3212: 
        {
            if (m_initList["m_Sigma0BarList"]) {
                CDDecayList Sigma0(BesStdSelector::Sigma0Selector);
                Sigma0 = DecayList(3122) * Photon();
                m_SigmapList = Sigma0;
                m_initList["m_Sigma0BarList"] = false;
            }
            return m_Sigma0BarList;
        }
        case 3334: 
        {
            if (m_initList["m_OmegaList"]) {
                CDDecayList Omega(BesStdSelector::OmegaSelector);
                Omega = DecayList(3122) * SecondaryTrk(-321);
                m_OmegaList = Omega;
                m_initList["m_OmegaList"] = false;
            }
            return m_OmegaList;
        }
        case -3334: 
        {
            if (m_initList["m_OmegaBarList"]) {
                CDDecayList Omega(BesStdSelector::OmegaSelector);
                Omega = DecayList(-3122) * SecondaryTrk(321);
                m_OmegaBarList = Omega;
                m_initList["m_OmegaBarList"] = false;
            }
            return m_OmegaBarList;
        }
        case 3222: 
        {
            if (m_initList["m_SigmapList"]) {
                CDDecayList mSigmap(BesStdSelector::SigmapSelector);
                mSigmap = SecondaryTrk(2212) * DecayList(111);
                m_SigmapList = mSigmap;
                m_initList["m_SigmapList"] = false;
            }
            return m_SigmapList;
        }
        case -3222: 
        {
            if (m_initList["m_SigmapBarList"]) {
                CDDecayList mSigmap(BesStdSelector::SigmapSelector);
                mSigmap = m_ProtonAllList.plus() * m_Pi0List;
                mSigmap = SecondaryTrk(2212) * DecayList(111);
                m_SigmapBarList = mSigmap;
                m_initList["m_SigmapBarList"] = false;
            }
            return m_SigmapBarList;
        }
        // 3312  Xi- -> Lambda pi-
        case 3312: 
        {
            if (m_initList["m_XimList"]) {
                CDDecayList Xim(BesStdSelector::XimSelector);
                Xim = DecayList(3122) * SecondaryTrk(-211);
                m_XimList = Xim;
                m_initList["m_XimList"] = false;
            }
            return m_XimList;
        }
        case -3312: 
        {
            if (m_initList["m_XimBarList"]) {
                CDDecayList Xim(BesStdSelector::XimSelector);
                Xim = DecayList(3122) * SecondaryTrk(-211);
                m_XimBarList = Xim;
                m_initList["m_XimBarList"] = false;
            }
            return m_XimBarList;
        }
        case 3322: 
        {
            // 3322  Xi0 -> Lambda pi0
            if (m_initList["m_Xi0List"]) {
                CDDecayList Xi0(BesStdSelector::Xi0Selector);
                Xi0 = DecayList(3122) * DecayList(111);
                m_Xi0List = Xi0;
                m_initList["m_Xi0List"] = false;
            }
            return m_Xi0List;
        }
        case -3322: 
        {
            // 3322  Xi0 -> Lambda pi0
            if (m_initList["m_Xi0BarList"]) {
                CDDecayList Xi0(BesStdSelector::Xi0Selector);
                Xi0 = DecayList(3122) * DecayList(111);
                m_Xi0BarList = Xi0;
                m_initList["m_Xi0BarList"] = false;
            }
            return m_Xi0BarList;
        }
    }
}

CDDecayList DCListSvc::DecayList(vector<int> fid) {
    switch (fid.size()) {
        case 1:
            return DecayList(fid[0]);

        case 2:
            return DecayList(fid[0]) * DecayList(fid[1]);

        case 3:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]);

        case 4:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]);

        case 5:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]);

        case 6:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]);

        case 7:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]);

        case 8:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]);

        case 9:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]);

        case 10:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                   DecayList(fid[9]);

        case 11:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                   DecayList(fid[9]) * DecayList(fid[10]);

        case 12:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                   DecayList(fid[9]) * DecayList(fid[10]) * DecayList(fid[11]);

        case 13:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                   DecayList(fid[9]) * DecayList(fid[10]) * DecayList(fid[11]) *
                   DecayList(fid[12]);

        case 14:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                   DecayList(fid[9]) * DecayList(fid[10]) * DecayList(fid[11]) *
                   DecayList(fid[12]) * DecayList(fid[13]);

        case 15:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                   DecayList(fid[9]) * DecayList(fid[10]) * DecayList(fid[11]) *
                   DecayList(fid[12]) * DecayList(fid[13]) * DecayList(fid[14]);

        case 16:
            return DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                   DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                   DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                   DecayList(fid[9]) * DecayList(fid[10]) * DecayList(fid[11]) *
                   DecayList(fid[12]) * DecayList(fid[13]) *
                   DecayList(fid[14]) * DecayList(fid[15]);

        default: {
            CDDecayList decayList;
            // decayList.erase();
            return decayList;
        }
    }
}

CDDecayList DCListSvc::DecayList(const DecayTree& decayTree) {
    return DecayList(decayTree.GetFID());
}
