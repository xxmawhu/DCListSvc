/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : DCListSvc.h
#   Create Time   : 2020-02-24 18:20
#   Last Modified : 2020-02-24 18:20
#   Describe      :
#
# ====================================================*/
#ifndef DCListSvc_DCListSvc_H
#define DCListSvc_DCListSvc_H

#include "GaudiKernel/Service.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "BesDChain/CDChargedKaonList.h"
#include "BesDChain/CDChargedPionList.h"
#include "BesDChain/CDDecayList.h"
#include "BesDChain/CDElectronList.h"
#include "BesDChain/CDEtaList.h"
#include "BesDChain/CDKsList.h"
#include "BesDChain/CDLambdaList.h"
#include "BesDChain/CDPhotonList.h"
#include "BesDChain/CDPi0List.h"
#include "BesDChain/CDProtonList.h"

#include "GaudiKernel/Algorithm.h"
#include "MCTruthMatchSvc/MCTruthMatchSvc.h"
#include "McDecayModeSvc/McDecayModeSvc.h"
#include "ParticleID/ParticleID.h"
#include "VertexFit/WTrackParameter.h"
#include "TupleSvc/DecayTree.h"
#include "TupleSvc/TupleSvc.h"
#include "TupleSvc/DecayChainSvc.h"
#include "MCTruthInfo/MCTruthInfo.h"
#include "BeamInfoSvc/BeamInfoSvc.h"
#include "PhotonConverSvc/PhotonConverSvc.h"
#include "DCListSvc/IDCListSvc.h"

// already include in "GaudiKernel/Algorithm.h"
// #include <string>
// #include <vector>

class DCListSvc : public Service,
                virtual public IDCListSvc{
   public:
    DCListSvc(const std::string &name, ISvcLocator *pSvcLocator);
    virtual ~ DCListSvc();
    virtual StatusCode initialize();
    virtual StatusCode finalize();
    virtual StatusCode queryInterface(const InterfaceID& riid, void** ppvIF);
    void init();
    CDDecayList DecayList(int);
    CDDecayList DecayList(std::vector<int> fid);
    CDDecayList DecayList(const DecayTree& decayTree);
    CDDecayList& Photon();
    CDDecayList& SoloPhoton();
    CDDecayList PrimaryTrk(int);
    CDDecayList SecondaryTrk(int);

   private:
    IDataProviderSvc* eventSvc_;
    IDatabaseSvc* m_dbsvc;
    BeamInfoSvc *gBeamInfoSvc;
    // mutable EventNavigator* m_navigator;
    double m_Ecm;
    bool m_readBeamE;
    int m_runID, m_eventID;
    int m_InfoLvl;
    bool m_newEvent;
    
    std::map<std::string, bool> m_initList;
    CDDecayList& Shower(bool);

    CDElectronList m_ElectronList, m_ElectronAllList;
    CDChargedPionList m_PionNoPID, m_PionPrimaryList, m_PionAllList;
    CDChargedKaonList m_KaonPrimaryList, m_KaonAllList;
    CDProtonList m_ProtonPrimaryList, m_ProtonAllList;
    CDDecayList m_LambdaList, m_LambdaBarList;
    CDDecayList m_Pi0List;
    CDDecayList m_KsList;
    CDDecayList m_EtaList, m_EtatoPiPiPi0List;
    CDDecayList m_EtapList, m_omegaList;
    CDDecayList m_PhotonList;
    CDDecayList m_PhotonSoloList;
    CDDecayList m_OmegaList, m_OmegaBarList;
    CDDecayList m_XimList, m_XimBarList;
    CDDecayList m_Xi0List, m_Xi0BarList;
    CDDecayList m_Sigma0List, m_Sigma0BarList;
    CDDecayList m_SigmapList, m_SigmapBarList;

};

#endif
