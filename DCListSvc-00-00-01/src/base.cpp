#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "EventModel/EventHeader.h"
#include "DCListSvc/DCListSvc.h"
#include <algorithm>

using CLHEP::HepLorentzVector;
using namespace Event;
using std::cout;
using std::endl;
DCListSvc::DCListSvc(const std::string& name, ISvcLocator* pSvcLocator)
: Service(name, pSvcLocator){
    declareProperty("Ecm", m_Ecm = 3.097);
    declareProperty("ReadBeamE", m_readBeamE = false);
}
DCListSvc::~DCListSvc() { }
StatusCode DCListSvc::initialize() {
    MsgStream log(messageService(), name());
    log << MSG::INFO << "@initialize()" << endreq;

    StatusCode sc = Service::initialize();
    sc = serviceLocator()->service("EventDataSvc", eventSvc_, true);
    
    IBeamInfoSvc * i_BeamInfoSvc;
    StatusCode sc_BeamInfoSvc = service("BeamInfoSvc", i_BeamInfoSvc);
    if (sc_BeamInfoSvc.isFailure()) {
        log << MSG::FATAL << "could not load BeamInfoSvc" << endreq;
        return sc_BeamInfoSvc;
    }
    gBeamInfoSvc = dynamic_cast<BeamInfoSvc*>(i_BeamInfoSvc);
    return sc;
}

StatusCode DCListSvc::finalize() {
    MsgStream log(messageService(), name());
    log << MSG::INFO << "@initialize()" << endreq;
    StatusCode sc = Service::finalize();
    return sc;
}

StatusCode DCListSvc::queryInterface(const InterfaceID& riid, void** ppvIF) {
    if (IDCListSvc::interfaceID().versionMatch(riid)) {
        *ppvIF = dynamic_cast<IDCListSvc*>(this);
    } else {
        return Service::queryInterface(riid, ppvIF);
    }
    addRef();
    // cout<<"DCListSvc::Inf:queryInterface"<<endl;
    return StatusCode::SUCCESS;
}
