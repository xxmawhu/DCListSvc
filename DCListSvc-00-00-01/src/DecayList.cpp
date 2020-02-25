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

#include "DCListSvc/DCListSvc.h"
#include "DTagAlg/LocalKaonSelector.h"

using BesStdSelector::primaryProtonSelector;
using BesStdSelector::secondaryProtonSelector;
CDDecayList DCListSvc::DecayList(int pid) {
    // Ks 310 ; K 321 ; Pion 211 ; Pi0 111 ; Eta 221 ; eta' 331
    // Lambda: 3122, Omega: 3334, etaV3pi 2212211, electron 11
    CDDecayList decayList;
    switch (pid) {
        case 310:
            return m_KsList;

        case 321:
            decayList = m_KaonPrimaryList.plus();
            return decayList;

        case -321:
            decayList = m_KaonPrimaryList.minus();
            return decayList;

        case 211:
            decayList = m_PionPrimaryList.plus();
            return decayList;

        case -211:
            decayList = m_PionPrimaryList.minus();
            return decayList;

        case 11:
            decayList = m_ElectronList.plus();
            return decayList;

        case -11:
            decayList = m_ElectronList.minus();
            return decayList;

        case 111:
            decayList = m_Pi0List;
            return decayList;

        case 221:
            return m_EtaList;

        case 22:
            decayList = m_PhotonList;
            return decayList;

        case 331: {  // Eta'  42.6(7)
            CDDecayList EtaP(BesStdSelector::EtaPtoPiPiEtaSelector);
            EtaP = m_PionPrimaryList.plus() * m_PionPrimaryList.minus() *
                   m_EtaList;
            return EtaP;
        }
        case 223: {  // omega  89.2(7)
            CDDecayList omegaList(BesStdSelector::omegaSelector);
            omegaList = m_PionPrimaryList.plus() * m_PionPrimaryList.minus() *
                        m_Pi0List;
            return omegaList;
        }

        case 333: {  // phi 492(5)
            CDDecayList phiList(BesStdSelector::phiSelector);
            phiList = m_KaonPrimaryList.plus() * m_KaonPrimaryList.minus();
            return phiList;
        }

        case 2212:
            decayList = m_ProtonPrimaryList.plus();
            return decayList;

        case -2212:
            decayList = m_ProtonPrimaryList.minus();
            return decayList;

        case 3122: {
            CDDecayList Lambda(BesStdSelector::lambdaSelector);
            Lambda = m_ProtonAllList.plus() * m_PionAllList.minus();
            return Lambda;
        }

        case -3122: {
            CDDecayList Lambdabar(BesStdSelector::lambdaSelector);
            Lambdabar = m_ProtonAllList.minus() * m_PionAllList.plus();
            return Lambdabar;
        }
        case 2212211: {
            CDDecayList Eta(BesStdSelector::etatoPiPiPi0Selector);
            Eta = m_PionPrimaryList.plus() * m_PionPrimaryList.minus() *
                  m_Pi0List;
            return Eta;
        }

        case 3212: {
            CDDecayList Sigma0(BesStdSelector::Sigma0Selector);
            // Sigma0 = Lambda * m_PhotonList;
            Sigma0 = DecayList(3122) * m_PhotonList;
            return Sigma0;
        }

        case -3212: {
            CDDecayList Sigma0bar(BesStdSelector::Sigma0Selector);
            // Sigma0bar = Lambdabar * m_PhotonList;
            Sigma0bar = DecayList(-3122) * m_PhotonList;
            return Sigma0bar;
        }

        case 3334: {
            CDDecayList Omega(BesStdSelector::OmegaSelector);
            Omega = DecayList(3122) * m_KaonAllList.minus();
            return Omega;
        }

        case -3334: {
            CDDecayList Omegabar(BesStdSelector::OmegaSelector);
            Omegabar = DecayList(-3122) * m_KaonAllList.plus();
            return Omegabar;
        }
        // Simga+ -> p pi0
        case 3222: {
            CDDecayList Sigmap(BesStdSelector::SigmapSelector);
            Sigmap = m_ProtonAllList.plus() * m_Pi0List;
            return Sigmap;
        }
        case -3222: {
            CDDecayList Sigmap(BesStdSelector::SigmapSelector);
            Sigmap = m_ProtonAllList.minus() * m_Pi0List;
            return Sigmap;
        }
        // 3312  Xi- -> Lambda pi-
        case 3312: {
            CDDecayList Xim(BesStdSelector::XimSelector);
            Xim = DecayList(3122) * m_PionAllList.minus();
            return Xim;
        }
        case -3312: {
            CDDecayList Xim(BesStdSelector::XimSelector);
            Xim = DecayList(-3122) * m_PionAllList.plus();
            return Xim;
        }
        // 3322  Xi0 -> Lambda pi0
        case 3322: {
            CDDecayList Xi0(BesStdSelector::Xi0Selector);
            Xi0 = DecayList(3122) * m_Pi0List;
            return Xi0;
        }
        case -3322: {
            CDDecayList Xi0(BesStdSelector::Xi0Selector);
            Xi0 = DecayList(-3122) * m_Pi0List;
            return Xi0;
        }

        default:
            return decayList;
    }
    return decayList;
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
