namespace std {}
using namespace std;
#include "fiTQun_projectProjectHeaders.h"

#include "fiTQun_projectLinkDef.h"

#include "fiTQun_projectProjectDict.cxx"

struct DeleteObjectFunctor {
   template <typename T>
   void operator()(const T *ptr) const {
      delete ptr;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T,Q> &) const {
      // Do nothing
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T,Q*> &ptr) const {
      delete ptr.second;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T*,Q> &ptr) const {
      delete ptr.first;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T*,Q*> &ptr) const {
      delete ptr.first;
      delete ptr.second;
   }
};

#ifndef WCSimRootEvent_cxx
#define WCSimRootEvent_cxx
WCSimRootEvent::WCSimRootEvent() {
   fEventList = 0;
}
WCSimRootEvent &WCSimRootEvent::operator=(const WCSimRootEvent & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootEvent &>( rhs ));
   fEventList = (const_cast<WCSimRootEvent &>( rhs ).fEventList);
   WCSimRootEvent &modrhs = const_cast<WCSimRootEvent &>( rhs );
   modrhs.fEventList = 0;
   return *this;
}
WCSimRootEvent::WCSimRootEvent(const WCSimRootEvent & rhs)
   : TObject(const_cast<WCSimRootEvent &>( rhs ))
   , fEventList(const_cast<WCSimRootEvent &>( rhs ).fEventList)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   WCSimRootEvent &modrhs = const_cast<WCSimRootEvent &>( rhs );
   modrhs.fEventList = 0;
}
WCSimRootEvent::~WCSimRootEvent() {
   delete fEventList;   fEventList = 0;
}
#endif // WCSimRootEvent_cxx

#ifndef WCSimRootTrigger_cxx
#define WCSimRootTrigger_cxx
WCSimRootTrigger::WCSimRootTrigger() {
   fCaptures = 0;
   fTracks = 0;
   fCherenkovHits = 0;
   fCherenkovHitTimes = 0;
   fCherenkovHitHistories = 0;
   fCherenkovDigiHits = 0;
}
WCSimRootTrigger &WCSimRootTrigger::operator=(const WCSimRootTrigger & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootTrigger &>( rhs ));
   fEvtHdr = (const_cast<WCSimRootTrigger &>( rhs ).fEvtHdr);
   fNvtxs = (const_cast<WCSimRootTrigger &>( rhs ).fNvtxs);
   fVecRecNumber = (const_cast<WCSimRootTrigger &>( rhs ).fVecRecNumber);
   fJmu = (const_cast<WCSimRootTrigger &>( rhs ).fJmu);
   fJp = (const_cast<WCSimRootTrigger &>( rhs ).fJp);
   fPi0 = (const_cast<WCSimRootTrigger &>( rhs ).fPi0);
   fCaptures = (const_cast<WCSimRootTrigger &>( rhs ).fCaptures);
   fNcaptures = (const_cast<WCSimRootTrigger &>( rhs ).fNcaptures);
   fNpar = (const_cast<WCSimRootTrigger &>( rhs ).fNpar);
   fNtrack = (const_cast<WCSimRootTrigger &>( rhs ).fNtrack);
   fNtrack_slots = (const_cast<WCSimRootTrigger &>( rhs ).fNtrack_slots);
   fTracks = (const_cast<WCSimRootTrigger &>( rhs ).fTracks);
   fNumTubesHit = (const_cast<WCSimRootTrigger &>( rhs ).fNumTubesHit);
   fNcherenkovhits = (const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovhits);
   fCherenkovHits = (const_cast<WCSimRootTrigger &>( rhs ).fCherenkovHits);
   fCherenkovHitCounter = (const_cast<WCSimRootTrigger &>( rhs ).fCherenkovHitCounter);
   fNcherenkovhittimes = (const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovhittimes);
   fCherenkovHitTimes = (const_cast<WCSimRootTrigger &>( rhs ).fCherenkovHitTimes);
   fNcherenkovhithistories = (const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovhithistories);
   fCherenkovHitHistories = (const_cast<WCSimRootTrigger &>( rhs ).fCherenkovHitHistories);
   fNumDigitizedTubes = (const_cast<WCSimRootTrigger &>( rhs ).fNumDigitizedTubes);
   fNcherenkovdigihits = (const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovdigihits);
   fNcherenkovdigihits_slots = (const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovdigihits_slots);
   fSumQ = (const_cast<WCSimRootTrigger &>( rhs ).fSumQ);
   fCherenkovDigiHits = (const_cast<WCSimRootTrigger &>( rhs ).fCherenkovDigiHits);
   fTriggerType = (const_cast<WCSimRootTrigger &>( rhs ).fTriggerType);
   fTriggerInfo = (const_cast<WCSimRootTrigger &>( rhs ).fTriggerInfo);
   IsZombie = (const_cast<WCSimRootTrigger &>( rhs ).IsZombie);
   for (Int_t i=0;i<900;i++) fMode[i] = rhs.fMode[i];
   for (Int_t i=0;i<900;i++) fVtxsvol[i] = rhs.fVtxsvol[i];
   for (Int_t i=0;i<3600;i++) reinterpret_cast<float *>(fVtxs)[i] = reinterpret_cast<float const *>(rhs.fVtxs)[i];
   WCSimRootTrigger &modrhs = const_cast<WCSimRootTrigger &>( rhs );
   modrhs.fCaptures = 0;
   modrhs.fTracks = 0;
   modrhs.fCherenkovHits = 0;
   modrhs.fCherenkovHitTimes = 0;
   modrhs.fCherenkovHitHistories = 0;
   modrhs.fCherenkovDigiHits = 0;
   modrhs.fTriggerInfo.clear();
   return *this;
}
WCSimRootTrigger::WCSimRootTrigger(const WCSimRootTrigger & rhs)
   : TObject(const_cast<WCSimRootTrigger &>( rhs ))
   , fEvtHdr(const_cast<WCSimRootTrigger &>( rhs ).fEvtHdr)
   , fNvtxs(const_cast<WCSimRootTrigger &>( rhs ).fNvtxs)
   , fVecRecNumber(const_cast<WCSimRootTrigger &>( rhs ).fVecRecNumber)
   , fJmu(const_cast<WCSimRootTrigger &>( rhs ).fJmu)
   , fJp(const_cast<WCSimRootTrigger &>( rhs ).fJp)
   , fPi0(const_cast<WCSimRootTrigger &>( rhs ).fPi0)
   , fCaptures(const_cast<WCSimRootTrigger &>( rhs ).fCaptures)
   , fNcaptures(const_cast<WCSimRootTrigger &>( rhs ).fNcaptures)
   , fNpar(const_cast<WCSimRootTrigger &>( rhs ).fNpar)
   , fNtrack(const_cast<WCSimRootTrigger &>( rhs ).fNtrack)
   , fNtrack_slots(const_cast<WCSimRootTrigger &>( rhs ).fNtrack_slots)
   , fTracks(const_cast<WCSimRootTrigger &>( rhs ).fTracks)
   , fNumTubesHit(const_cast<WCSimRootTrigger &>( rhs ).fNumTubesHit)
   , fNcherenkovhits(const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovhits)
   , fCherenkovHits(const_cast<WCSimRootTrigger &>( rhs ).fCherenkovHits)
   , fCherenkovHitCounter(const_cast<WCSimRootTrigger &>( rhs ).fCherenkovHitCounter)
   , fNcherenkovhittimes(const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovhittimes)
   , fCherenkovHitTimes(const_cast<WCSimRootTrigger &>( rhs ).fCherenkovHitTimes)
   , fNcherenkovhithistories(const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovhithistories)
   , fCherenkovHitHistories(const_cast<WCSimRootTrigger &>( rhs ).fCherenkovHitHistories)
   , fNumDigitizedTubes(const_cast<WCSimRootTrigger &>( rhs ).fNumDigitizedTubes)
   , fNcherenkovdigihits(const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovdigihits)
   , fNcherenkovdigihits_slots(const_cast<WCSimRootTrigger &>( rhs ).fNcherenkovdigihits_slots)
   , fSumQ(const_cast<WCSimRootTrigger &>( rhs ).fSumQ)
   , fCherenkovDigiHits(const_cast<WCSimRootTrigger &>( rhs ).fCherenkovDigiHits)
   , fTriggerType(const_cast<WCSimRootTrigger &>( rhs ).fTriggerType)
   , fTriggerInfo(const_cast<WCSimRootTrigger &>( rhs ).fTriggerInfo)
   , IsZombie(const_cast<WCSimRootTrigger &>( rhs ).IsZombie)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<900;i++) fMode[i] = rhs.fMode[i];
   for (Int_t i=0;i<900;i++) fVtxsvol[i] = rhs.fVtxsvol[i];
   for (Int_t i=0;i<3600;i++) reinterpret_cast<float *>(fVtxs)[i] = reinterpret_cast<float const *>(rhs.fVtxs)[i];
   WCSimRootTrigger &modrhs = const_cast<WCSimRootTrigger &>( rhs );
   modrhs.fCaptures = 0;
   modrhs.fTracks = 0;
   modrhs.fCherenkovHits = 0;
   modrhs.fCherenkovHitTimes = 0;
   modrhs.fCherenkovHitHistories = 0;
   modrhs.fCherenkovDigiHits = 0;
   modrhs.fTriggerInfo.clear();
}
WCSimRootTrigger::~WCSimRootTrigger() {
   delete fCaptures;   fCaptures = 0;
   delete fTracks;   fTracks = 0;
   delete fCherenkovHits;   fCherenkovHits = 0;
   delete fCherenkovHitTimes;   fCherenkovHitTimes = 0;
   delete fCherenkovHitHistories;   fCherenkovHitHistories = 0;
   delete fCherenkovDigiHits;   fCherenkovDigiHits = 0;
}
#endif // WCSimRootTrigger_cxx

#ifndef WCSimRootEventHeader_cxx
#define WCSimRootEventHeader_cxx
WCSimRootEventHeader::WCSimRootEventHeader() {
}
WCSimRootEventHeader &WCSimRootEventHeader::operator=(const WCSimRootEventHeader & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   fEvtNum = (const_cast<WCSimRootEventHeader &>( rhs ).fEvtNum);
   fRun = (const_cast<WCSimRootEventHeader &>( rhs ).fRun);
   fDate = (const_cast<WCSimRootEventHeader &>( rhs ).fDate);
   fSubEvtNumber = (const_cast<WCSimRootEventHeader &>( rhs ).fSubEvtNumber);
   return *this;
}
WCSimRootEventHeader::WCSimRootEventHeader(const WCSimRootEventHeader & rhs)
   : fEvtNum(const_cast<WCSimRootEventHeader &>( rhs ).fEvtNum)
   , fRun(const_cast<WCSimRootEventHeader &>( rhs ).fRun)
   , fDate(const_cast<WCSimRootEventHeader &>( rhs ).fDate)
   , fSubEvtNumber(const_cast<WCSimRootEventHeader &>( rhs ).fSubEvtNumber)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
WCSimRootEventHeader::~WCSimRootEventHeader() {
}
#endif // WCSimRootEventHeader_cxx

#ifndef WCSimRootPi0_cxx
#define WCSimRootPi0_cxx
WCSimRootPi0::WCSimRootPi0() {
}
WCSimRootPi0 &WCSimRootPi0::operator=(const WCSimRootPi0 & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootPi0 &>( rhs ));
   for (Int_t i=0;i<3;i++) fPi0Vtx[i] = rhs.fPi0Vtx[i];
   for (Int_t i=0;i<2;i++) fGammaID[i] = rhs.fGammaID[i];
   for (Int_t i=0;i<2;i++) fGammaE[i] = rhs.fGammaE[i];
   for (Int_t i=0;i<6;i++) reinterpret_cast<float *>(fGammaVtx)[i] = reinterpret_cast<float const *>(rhs.fGammaVtx)[i];
   return *this;
}
WCSimRootPi0::WCSimRootPi0(const WCSimRootPi0 & rhs)
   : TObject(const_cast<WCSimRootPi0 &>( rhs ))
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<3;i++) fPi0Vtx[i] = rhs.fPi0Vtx[i];
   for (Int_t i=0;i<2;i++) fGammaID[i] = rhs.fGammaID[i];
   for (Int_t i=0;i<2;i++) fGammaE[i] = rhs.fGammaE[i];
   for (Int_t i=0;i<6;i++) reinterpret_cast<float *>(fGammaVtx)[i] = reinterpret_cast<float const *>(rhs.fGammaVtx)[i];
}
WCSimRootPi0::~WCSimRootPi0() {
}
#endif // WCSimRootPi0_cxx

#ifndef WCSimRootGeom_cxx
#define WCSimRootGeom_cxx
WCSimRootGeom::WCSimRootGeom() {
   fPMTArray = 0;
   fPMTArray2 = 0;
   fODPMTArray = 0;
}
WCSimRootGeom &WCSimRootGeom::operator=(const WCSimRootGeom & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootGeom &>( rhs ));
   fBoundaryWallDimensions = (const_cast<WCSimRootGeom &>( rhs ).fBoundaryWallDimensions);
   fWCCylRadius = (const_cast<WCSimRootGeom &>( rhs ).fWCCylRadius);
   fWCCylLength = (const_cast<WCSimRootGeom &>( rhs ).fWCCylLength);
   fgeo_type = (const_cast<WCSimRootGeom &>( rhs ).fgeo_type);
   fWCPMTRadius = (const_cast<WCSimRootGeom &>( rhs ).fWCPMTRadius);
   fWCPMTRadius2 = (const_cast<WCSimRootGeom &>( rhs ).fWCPMTRadius2);
   fWCNumPMT = (const_cast<WCSimRootGeom &>( rhs ).fWCNumPMT);
   fWCNumPMT2 = (const_cast<WCSimRootGeom &>( rhs ).fWCNumPMT2);
   fODWCPMTRadius = (const_cast<WCSimRootGeom &>( rhs ).fODWCPMTRadius);
   fODWCNumPMT = (const_cast<WCSimRootGeom &>( rhs ).fODWCNumPMT);
   fOrientation = (const_cast<WCSimRootGeom &>( rhs ).fOrientation);
   fPMTArray = (const_cast<WCSimRootGeom &>( rhs ).fPMTArray);
   fPMTArray2 = (const_cast<WCSimRootGeom &>( rhs ).fPMTArray2);
   fODPMTArray = (const_cast<WCSimRootGeom &>( rhs ).fODPMTArray);
   WCSimRootGeom &modrhs = const_cast<WCSimRootGeom &>( rhs );
   modrhs.fBoundaryWallDimensions.clear();
   for (Int_t i=0;i<3;i++) fWCOffset[i] = rhs.fWCOffset[i];
   modrhs.fPMTArray = 0;
   modrhs.fPMTArray2 = 0;
   modrhs.fODPMTArray = 0;
   return *this;
}
WCSimRootGeom::WCSimRootGeom(const WCSimRootGeom & rhs)
   : TObject(const_cast<WCSimRootGeom &>( rhs ))
   , fBoundaryWallDimensions(const_cast<WCSimRootGeom &>( rhs ).fBoundaryWallDimensions)
   , fWCCylRadius(const_cast<WCSimRootGeom &>( rhs ).fWCCylRadius)
   , fWCCylLength(const_cast<WCSimRootGeom &>( rhs ).fWCCylLength)
   , fgeo_type(const_cast<WCSimRootGeom &>( rhs ).fgeo_type)
   , fWCPMTRadius(const_cast<WCSimRootGeom &>( rhs ).fWCPMTRadius)
   , fWCPMTRadius2(const_cast<WCSimRootGeom &>( rhs ).fWCPMTRadius2)
   , fWCNumPMT(const_cast<WCSimRootGeom &>( rhs ).fWCNumPMT)
   , fWCNumPMT2(const_cast<WCSimRootGeom &>( rhs ).fWCNumPMT2)
   , fODWCPMTRadius(const_cast<WCSimRootGeom &>( rhs ).fODWCPMTRadius)
   , fODWCNumPMT(const_cast<WCSimRootGeom &>( rhs ).fODWCNumPMT)
   , fOrientation(const_cast<WCSimRootGeom &>( rhs ).fOrientation)
   , fPMTArray(const_cast<WCSimRootGeom &>( rhs ).fPMTArray)
   , fPMTArray2(const_cast<WCSimRootGeom &>( rhs ).fPMTArray2)
   , fODPMTArray(const_cast<WCSimRootGeom &>( rhs ).fODPMTArray)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   WCSimRootGeom &modrhs = const_cast<WCSimRootGeom &>( rhs );
   modrhs.fBoundaryWallDimensions.clear();
   for (Int_t i=0;i<3;i++) fWCOffset[i] = rhs.fWCOffset[i];
   modrhs.fPMTArray = 0;
   modrhs.fPMTArray2 = 0;
   modrhs.fODPMTArray = 0;
}
WCSimRootGeom::~WCSimRootGeom() {
   delete fPMTArray;   fPMTArray = 0;
   delete fPMTArray2;   fPMTArray2 = 0;
   delete fODPMTArray;   fODPMTArray = 0;
}
#endif // WCSimRootGeom_cxx

#ifndef WCSimRootPMT_cxx
#define WCSimRootPMT_cxx
WCSimRootPMT::WCSimRootPMT() {
}
WCSimRootPMT &WCSimRootPMT::operator=(const WCSimRootPMT & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootPMT &>( rhs ));
   fTubeNo = (const_cast<WCSimRootPMT &>( rhs ).fTubeNo);
   fmPMTNo = (const_cast<WCSimRootPMT &>( rhs ).fmPMTNo);
   fmPMT_PMTNo = (const_cast<WCSimRootPMT &>( rhs ).fmPMT_PMTNo);
   fCylLoc = (const_cast<WCSimRootPMT &>( rhs ).fCylLoc);
   for (Int_t i=0;i<3;i++) fOrientation[i] = rhs.fOrientation[i];
   for (Int_t i=0;i<3;i++) fPosition[i] = rhs.fPosition[i];
   return *this;
}
WCSimRootPMT::WCSimRootPMT(const WCSimRootPMT & rhs)
   : TObject(const_cast<WCSimRootPMT &>( rhs ))
   , fTubeNo(const_cast<WCSimRootPMT &>( rhs ).fTubeNo)
   , fmPMTNo(const_cast<WCSimRootPMT &>( rhs ).fmPMTNo)
   , fmPMT_PMTNo(const_cast<WCSimRootPMT &>( rhs ).fmPMT_PMTNo)
   , fCylLoc(const_cast<WCSimRootPMT &>( rhs ).fCylLoc)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<3;i++) fOrientation[i] = rhs.fOrientation[i];
   for (Int_t i=0;i<3;i++) fPosition[i] = rhs.fPosition[i];
}
WCSimRootPMT::~WCSimRootPMT() {
}
#endif // WCSimRootPMT_cxx

#ifndef WCSimRootOptions_cxx
#define WCSimRootOptions_cxx
WCSimRootOptions::WCSimRootOptions() {
}
WCSimRootOptions &WCSimRootOptions::operator=(const WCSimRootOptions & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootOptions &>( rhs ));
   WCSimVersion = (const_cast<WCSimRootOptions &>( rhs ).WCSimVersion);
   DetectorName = (const_cast<WCSimRootOptions &>( rhs ).DetectorName);
   GeomHasOD = (const_cast<WCSimRootOptions &>( rhs ).GeomHasOD);
   SavePi0 = (const_cast<WCSimRootOptions &>( rhs ).SavePi0);
   PMTQEMethod = (const_cast<WCSimRootOptions &>( rhs ).PMTQEMethod);
   PMTCollEff = (const_cast<WCSimRootOptions &>( rhs ).PMTCollEff);
   DarkOptMap = (const_cast<WCSimRootOptions &>( rhs ).DarkOptMap);
   DigitizerClassName = (const_cast<WCSimRootOptions &>( rhs ).DigitizerClassName);
   DigitizerDeadTime = (const_cast<WCSimRootOptions &>( rhs ).DigitizerDeadTime);
   DigitizerIntegrationWindow = (const_cast<WCSimRootOptions &>( rhs ).DigitizerIntegrationWindow);
   DigitizerTimingPrecision = (const_cast<WCSimRootOptions &>( rhs ).DigitizerTimingPrecision);
   DigitizerPEPrecision = (const_cast<WCSimRootOptions &>( rhs ).DigitizerPEPrecision);
   TriggerClassName = (const_cast<WCSimRootOptions &>( rhs ).TriggerClassName);
   MultiDigitsPerTrigger = (const_cast<WCSimRootOptions &>( rhs ).MultiDigitsPerTrigger);
   TriggerOffset = (const_cast<WCSimRootOptions &>( rhs ).TriggerOffset);
   NDigitsThreshold = (const_cast<WCSimRootOptions &>( rhs ).NDigitsThreshold);
   NDigitsWindow = (const_cast<WCSimRootOptions &>( rhs ).NDigitsWindow);
   NDigitsAdjustForNoise = (const_cast<WCSimRootOptions &>( rhs ).NDigitsAdjustForNoise);
   NDigitsPreTriggerWindow = (const_cast<WCSimRootOptions &>( rhs ).NDigitsPreTriggerWindow);
   NDigitsPostTriggerWindow = (const_cast<WCSimRootOptions &>( rhs ).NDigitsPostTriggerWindow);
   SaveFailuresMode = (const_cast<WCSimRootOptions &>( rhs ).SaveFailuresMode);
   SaveFailuresTime = (const_cast<WCSimRootOptions &>( rhs ).SaveFailuresTime);
   SaveFailuresPreTriggerWindow = (const_cast<WCSimRootOptions &>( rhs ).SaveFailuresPreTriggerWindow);
   SaveFailuresPostTriggerWindow = (const_cast<WCSimRootOptions &>( rhs ).SaveFailuresPostTriggerWindow);
   Rayff = (const_cast<WCSimRootOptions &>( rhs ).Rayff);
   Bsrff = (const_cast<WCSimRootOptions &>( rhs ).Bsrff);
   Abwff = (const_cast<WCSimRootOptions &>( rhs ).Abwff);
   Rgcff = (const_cast<WCSimRootOptions &>( rhs ).Rgcff);
   Qeff = (const_cast<WCSimRootOptions &>( rhs ).Qeff);
   Mieff = (const_cast<WCSimRootOptions &>( rhs ).Mieff);
   Ttsff = (const_cast<WCSimRootOptions &>( rhs ).Ttsff);
   PmtSatur = (const_cast<WCSimRootOptions &>( rhs ).PmtSatur);
   Tvspacing = (const_cast<WCSimRootOptions &>( rhs ).Tvspacing);
   Topveto = (const_cast<WCSimRootOptions &>( rhs ).Topveto);
   PhysicsListName = (const_cast<WCSimRootOptions &>( rhs ).PhysicsListName);
   VectorFileName = (const_cast<WCSimRootOptions &>( rhs ).VectorFileName);
   GeneratorType = (const_cast<WCSimRootOptions &>( rhs ).GeneratorType);
   RandomSeed = (const_cast<WCSimRootOptions &>( rhs ).RandomSeed);
   RandomGenerator = (const_cast<WCSimRootOptions &>( rhs ).RandomGenerator);
   WCSimRootOptions &modrhs = const_cast<WCSimRootOptions &>( rhs );
   modrhs.WCSimVersion.clear();
   modrhs.DetectorName.clear();
   modrhs.DarkOptMap.clear();
   modrhs.DigitizerClassName.clear();
   modrhs.TriggerClassName.clear();
   modrhs.PhysicsListName.clear();
   modrhs.VectorFileName.clear();
   modrhs.GeneratorType.clear();
   return *this;
}
WCSimRootOptions::WCSimRootOptions(const WCSimRootOptions & rhs)
   : TObject(const_cast<WCSimRootOptions &>( rhs ))
   , WCSimVersion(const_cast<WCSimRootOptions &>( rhs ).WCSimVersion)
   , DetectorName(const_cast<WCSimRootOptions &>( rhs ).DetectorName)
   , GeomHasOD(const_cast<WCSimRootOptions &>( rhs ).GeomHasOD)
   , SavePi0(const_cast<WCSimRootOptions &>( rhs ).SavePi0)
   , PMTQEMethod(const_cast<WCSimRootOptions &>( rhs ).PMTQEMethod)
   , PMTCollEff(const_cast<WCSimRootOptions &>( rhs ).PMTCollEff)
   , DarkOptMap(const_cast<WCSimRootOptions &>( rhs ).DarkOptMap)
   , DigitizerClassName(const_cast<WCSimRootOptions &>( rhs ).DigitizerClassName)
   , DigitizerDeadTime(const_cast<WCSimRootOptions &>( rhs ).DigitizerDeadTime)
   , DigitizerIntegrationWindow(const_cast<WCSimRootOptions &>( rhs ).DigitizerIntegrationWindow)
   , DigitizerTimingPrecision(const_cast<WCSimRootOptions &>( rhs ).DigitizerTimingPrecision)
   , DigitizerPEPrecision(const_cast<WCSimRootOptions &>( rhs ).DigitizerPEPrecision)
   , TriggerClassName(const_cast<WCSimRootOptions &>( rhs ).TriggerClassName)
   , MultiDigitsPerTrigger(const_cast<WCSimRootOptions &>( rhs ).MultiDigitsPerTrigger)
   , TriggerOffset(const_cast<WCSimRootOptions &>( rhs ).TriggerOffset)
   , NDigitsThreshold(const_cast<WCSimRootOptions &>( rhs ).NDigitsThreshold)
   , NDigitsWindow(const_cast<WCSimRootOptions &>( rhs ).NDigitsWindow)
   , NDigitsAdjustForNoise(const_cast<WCSimRootOptions &>( rhs ).NDigitsAdjustForNoise)
   , NDigitsPreTriggerWindow(const_cast<WCSimRootOptions &>( rhs ).NDigitsPreTriggerWindow)
   , NDigitsPostTriggerWindow(const_cast<WCSimRootOptions &>( rhs ).NDigitsPostTriggerWindow)
   , SaveFailuresMode(const_cast<WCSimRootOptions &>( rhs ).SaveFailuresMode)
   , SaveFailuresTime(const_cast<WCSimRootOptions &>( rhs ).SaveFailuresTime)
   , SaveFailuresPreTriggerWindow(const_cast<WCSimRootOptions &>( rhs ).SaveFailuresPreTriggerWindow)
   , SaveFailuresPostTriggerWindow(const_cast<WCSimRootOptions &>( rhs ).SaveFailuresPostTriggerWindow)
   , Rayff(const_cast<WCSimRootOptions &>( rhs ).Rayff)
   , Bsrff(const_cast<WCSimRootOptions &>( rhs ).Bsrff)
   , Abwff(const_cast<WCSimRootOptions &>( rhs ).Abwff)
   , Rgcff(const_cast<WCSimRootOptions &>( rhs ).Rgcff)
   , Qeff(const_cast<WCSimRootOptions &>( rhs ).Qeff)
   , Mieff(const_cast<WCSimRootOptions &>( rhs ).Mieff)
   , Ttsff(const_cast<WCSimRootOptions &>( rhs ).Ttsff)
   , PmtSatur(const_cast<WCSimRootOptions &>( rhs ).PmtSatur)
   , Tvspacing(const_cast<WCSimRootOptions &>( rhs ).Tvspacing)
   , Topveto(const_cast<WCSimRootOptions &>( rhs ).Topveto)
   , PhysicsListName(const_cast<WCSimRootOptions &>( rhs ).PhysicsListName)
   , VectorFileName(const_cast<WCSimRootOptions &>( rhs ).VectorFileName)
   , GeneratorType(const_cast<WCSimRootOptions &>( rhs ).GeneratorType)
   , RandomSeed(const_cast<WCSimRootOptions &>( rhs ).RandomSeed)
   , RandomGenerator(const_cast<WCSimRootOptions &>( rhs ).RandomGenerator)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   WCSimRootOptions &modrhs = const_cast<WCSimRootOptions &>( rhs );
   modrhs.WCSimVersion.clear();
   modrhs.DetectorName.clear();
   modrhs.DarkOptMap.clear();
   modrhs.DigitizerClassName.clear();
   modrhs.TriggerClassName.clear();
   modrhs.PhysicsListName.clear();
   modrhs.VectorFileName.clear();
   modrhs.GeneratorType.clear();
}
WCSimRootOptions::~WCSimRootOptions() {
}
#endif // WCSimRootOptions_cxx

#ifndef WCSimDarkNoiseOptions_cxx
#define WCSimDarkNoiseOptions_cxx
WCSimDarkNoiseOptions::WCSimDarkNoiseOptions() {
}
WCSimDarkNoiseOptions &WCSimDarkNoiseOptions::operator=(const WCSimDarkNoiseOptions & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   PMTDarkRate = (const_cast<WCSimDarkNoiseOptions &>( rhs ).PMTDarkRate);
   ConvRate = (const_cast<WCSimDarkNoiseOptions &>( rhs ).ConvRate);
   DarkHigh = (const_cast<WCSimDarkNoiseOptions &>( rhs ).DarkHigh);
   DarkLow = (const_cast<WCSimDarkNoiseOptions &>( rhs ).DarkLow);
   DarkWindow = (const_cast<WCSimDarkNoiseOptions &>( rhs ).DarkWindow);
   DarkMode = (const_cast<WCSimDarkNoiseOptions &>( rhs ).DarkMode);
   return *this;
}
WCSimDarkNoiseOptions::WCSimDarkNoiseOptions(const WCSimDarkNoiseOptions & rhs)
   : PMTDarkRate(const_cast<WCSimDarkNoiseOptions &>( rhs ).PMTDarkRate)
   , ConvRate(const_cast<WCSimDarkNoiseOptions &>( rhs ).ConvRate)
   , DarkHigh(const_cast<WCSimDarkNoiseOptions &>( rhs ).DarkHigh)
   , DarkLow(const_cast<WCSimDarkNoiseOptions &>( rhs ).DarkLow)
   , DarkWindow(const_cast<WCSimDarkNoiseOptions &>( rhs ).DarkWindow)
   , DarkMode(const_cast<WCSimDarkNoiseOptions &>( rhs ).DarkMode)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
WCSimDarkNoiseOptions::~WCSimDarkNoiseOptions() {
}
#endif // WCSimDarkNoiseOptions_cxx

#ifndef ND__NRooTrackerVtx_cxx
#define ND__NRooTrackerVtx_cxx
ND::NRooTrackerVtx::NRooTrackerVtx() {
   EvtCode = 0;
   StdHepPdg = 0;
   StdHepStatus = 0;
   StdHepFd = 0;
   StdHepLd = 0;
   StdHepFm = 0;
   StdHepLm = 0;
   NEipvc = 0;
   NEiorgvc = 0;
   NEiflgvc = 0;
   NEicrnvc = 0;
   NEiflgvert = 0;
   NEabspvert = 0;
   NEabstpvert = 0;
   NEipvert = 0;
   NEiverti = 0;
   NEivertf = 0;
   NFiflag = 0;
   NFx = 0;
   NFy = 0;
   NFz = 0;
   NFpx = 0;
   NFpy = 0;
   NFpz = 0;
   NFe = 0;
   NFfirststep = 0;
   NFecms2 = 0;
   Prob = 0;
   VertFlagStep = 0;
   VertFsiRhon = 0;
   StepPel = 0;
   StepPsp = 0;
   StepPdp = 0;
   StepScaleFactor = 0;
   StepEkin = 0;
   GeomPath = 0;
   GeneratorName = 0;
   OrigFileName = 0;
   OrigTreeName = 0;
}
ND::NRooTrackerVtx &ND::NRooTrackerVtx::operator=(const NRooTrackerVtx & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   ND::JNuBeamFlux::operator=(const_cast<NRooTrackerVtx &>( rhs ));
   EvtCode = (const_cast<NRooTrackerVtx &>( rhs ).EvtCode);
   EvtNum = (const_cast<NRooTrackerVtx &>( rhs ).EvtNum);
   EvtXSec = (const_cast<NRooTrackerVtx &>( rhs ).EvtXSec);
   EvtDXSec = (const_cast<NRooTrackerVtx &>( rhs ).EvtDXSec);
   EvtWght = (const_cast<NRooTrackerVtx &>( rhs ).EvtWght);
   EvtProb = (const_cast<NRooTrackerVtx &>( rhs ).EvtProb);
   StdHepN = (const_cast<NRooTrackerVtx &>( rhs ).StdHepN);
   StdHepPdg = (const_cast<NRooTrackerVtx &>( rhs ).StdHepPdg);
   StdHepStatus = (const_cast<NRooTrackerVtx &>( rhs ).StdHepStatus);
   StdHepFd = (const_cast<NRooTrackerVtx &>( rhs ).StdHepFd);
   StdHepLd = (const_cast<NRooTrackerVtx &>( rhs ).StdHepLd);
   StdHepFm = (const_cast<NRooTrackerVtx &>( rhs ).StdHepFm);
   StdHepLm = (const_cast<NRooTrackerVtx &>( rhs ).StdHepLm);
   NEnvc = (const_cast<NRooTrackerVtx &>( rhs ).NEnvc);
   NEipvc = (const_cast<NRooTrackerVtx &>( rhs ).NEipvc);
   NEiorgvc = (const_cast<NRooTrackerVtx &>( rhs ).NEiorgvc);
   NEiflgvc = (const_cast<NRooTrackerVtx &>( rhs ).NEiflgvc);
   NEicrnvc = (const_cast<NRooTrackerVtx &>( rhs ).NEicrnvc);
   NEcrsx = (const_cast<NRooTrackerVtx &>( rhs ).NEcrsx);
   NEcrsy = (const_cast<NRooTrackerVtx &>( rhs ).NEcrsy);
   NEcrsz = (const_cast<NRooTrackerVtx &>( rhs ).NEcrsz);
   NEcrsphi = (const_cast<NRooTrackerVtx &>( rhs ).NEcrsphi);
   NEnvert = (const_cast<NRooTrackerVtx &>( rhs ).NEnvert);
   NEiflgvert = (const_cast<NRooTrackerVtx &>( rhs ).NEiflgvert);
   NEnvcvert = (const_cast<NRooTrackerVtx &>( rhs ).NEnvcvert);
   NEabspvert = (const_cast<NRooTrackerVtx &>( rhs ).NEabspvert);
   NEabstpvert = (const_cast<NRooTrackerVtx &>( rhs ).NEabstpvert);
   NEipvert = (const_cast<NRooTrackerVtx &>( rhs ).NEipvert);
   NEiverti = (const_cast<NRooTrackerVtx &>( rhs ).NEiverti);
   NEivertf = (const_cast<NRooTrackerVtx &>( rhs ).NEivertf);
   NFnvert = (const_cast<NRooTrackerVtx &>( rhs ).NFnvert);
   NFiflag = (const_cast<NRooTrackerVtx &>( rhs ).NFiflag);
   NFx = (const_cast<NRooTrackerVtx &>( rhs ).NFx);
   NFy = (const_cast<NRooTrackerVtx &>( rhs ).NFy);
   NFz = (const_cast<NRooTrackerVtx &>( rhs ).NFz);
   NFpx = (const_cast<NRooTrackerVtx &>( rhs ).NFpx);
   NFpy = (const_cast<NRooTrackerVtx &>( rhs ).NFpy);
   NFpz = (const_cast<NRooTrackerVtx &>( rhs ).NFpz);
   NFe = (const_cast<NRooTrackerVtx &>( rhs ).NFe);
   NFfirststep = (const_cast<NRooTrackerVtx &>( rhs ).NFfirststep);
   NFnstep = (const_cast<NRooTrackerVtx &>( rhs ).NFnstep);
   NFecms2 = (const_cast<NRooTrackerVtx &>( rhs ).NFecms2);
   PCascProb = (const_cast<NRooTrackerVtx &>( rhs ).PCascProb);
   Prob = (const_cast<NRooTrackerVtx &>( rhs ).Prob);
   VertFlagStep = (const_cast<NRooTrackerVtx &>( rhs ).VertFlagStep);
   VertFsiRhon = (const_cast<NRooTrackerVtx &>( rhs ).VertFsiRhon);
   StepPel = (const_cast<NRooTrackerVtx &>( rhs ).StepPel);
   StepPsp = (const_cast<NRooTrackerVtx &>( rhs ).StepPsp);
   StepPdp = (const_cast<NRooTrackerVtx &>( rhs ).StepPdp);
   StepScaleFactor = (const_cast<NRooTrackerVtx &>( rhs ).StepScaleFactor);
   StepEkin = (const_cast<NRooTrackerVtx &>( rhs ).StepEkin);
   SPIDelta = (const_cast<NRooTrackerVtx &>( rhs ).SPIDelta);
   IRadCorrPht = (const_cast<NRooTrackerVtx &>( rhs ).IRadCorrPht);
   GeomPath = (const_cast<NRooTrackerVtx &>( rhs ).GeomPath);
   GeneratorName = (const_cast<NRooTrackerVtx &>( rhs ).GeneratorName);
   OrigFileName = (const_cast<NRooTrackerVtx &>( rhs ).OrigFileName);
   OrigTreeName = (const_cast<NRooTrackerVtx &>( rhs ).OrigTreeName);
   OrigEvtNum = (const_cast<NRooTrackerVtx &>( rhs ).OrigEvtNum);
   OrigTreeEntries = (const_cast<NRooTrackerVtx &>( rhs ).OrigTreeEntries);
   OrigTreePOT = (const_cast<NRooTrackerVtx &>( rhs ).OrigTreePOT);
   TimeInSpill = (const_cast<NRooTrackerVtx &>( rhs ).TimeInSpill);
   TruthVertexID = (const_cast<NRooTrackerVtx &>( rhs ).TruthVertexID);
   NRooTrackerVtx &modrhs = const_cast<NRooTrackerVtx &>( rhs );
   modrhs.EvtCode = 0;
   for (Int_t i=0;i<4;i++) EvtVtx[i] = rhs.EvtVtx[i];
   modrhs.StdHepPdg = 0;
   modrhs.StdHepStatus = 0;
   for (Int_t i=0;i<400;i++) reinterpret_cast<double *>(StdHepX4)[i] = reinterpret_cast<double const *>(rhs.StdHepX4)[i];
   for (Int_t i=0;i<400;i++) reinterpret_cast<double *>(StdHepP4)[i] = reinterpret_cast<double const *>(rhs.StdHepP4)[i];
   for (Int_t i=0;i<300;i++) reinterpret_cast<double *>(StdHepPolz)[i] = reinterpret_cast<double const *>(rhs.StdHepPolz)[i];
   modrhs.StdHepFd = 0;
   modrhs.StdHepLd = 0;
   modrhs.StdHepFm = 0;
   modrhs.StdHepLm = 0;
   modrhs.NEipvc = 0;
   for (Int_t i=0;i<300;i++) reinterpret_cast<float *>(NEpvc)[i] = reinterpret_cast<float const *>(rhs.NEpvc)[i];
   modrhs.NEiorgvc = 0;
   modrhs.NEiflgvc = 0;
   modrhs.NEicrnvc = 0;
   for (Int_t i=0;i<300;i++) reinterpret_cast<float *>(NEposvert)[i] = reinterpret_cast<float const *>(rhs.NEposvert)[i];
   modrhs.NEiflgvert = 0;
   for (Int_t i=0;i<900;i++) reinterpret_cast<float *>(NEdirvert)[i] = reinterpret_cast<float const *>(rhs.NEdirvert)[i];
   modrhs.NEabspvert = 0;
   modrhs.NEabstpvert = 0;
   modrhs.NEipvert = 0;
   modrhs.NEiverti = 0;
   modrhs.NEivertf = 0;
   modrhs.NFiflag = 0;
   modrhs.NFx = 0;
   modrhs.NFy = 0;
   modrhs.NFz = 0;
   modrhs.NFpx = 0;
   modrhs.NFpy = 0;
   modrhs.NFpz = 0;
   modrhs.NFe = 0;
   modrhs.NFfirststep = 0;
   modrhs.NFecms2 = 0;
   modrhs.Prob = 0;
   modrhs.VertFlagStep = 0;
   modrhs.VertFsiRhon = 0;
   modrhs.StepPel = 0;
   modrhs.StepPsp = 0;
   modrhs.StepPdp = 0;
   modrhs.StepScaleFactor = 0;
   modrhs.StepEkin = 0;
   modrhs.GeomPath = 0;
   modrhs.GeneratorName = 0;
   modrhs.OrigFileName = 0;
   modrhs.OrigTreeName = 0;
   return *this;
}
ND::NRooTrackerVtx::NRooTrackerVtx(const NRooTrackerVtx & rhs)
   : ND::JNuBeamFlux(const_cast<NRooTrackerVtx &>( rhs ))
   , EvtCode(const_cast<NRooTrackerVtx &>( rhs ).EvtCode)
   , EvtNum(const_cast<NRooTrackerVtx &>( rhs ).EvtNum)
   , EvtXSec(const_cast<NRooTrackerVtx &>( rhs ).EvtXSec)
   , EvtDXSec(const_cast<NRooTrackerVtx &>( rhs ).EvtDXSec)
   , EvtWght(const_cast<NRooTrackerVtx &>( rhs ).EvtWght)
   , EvtProb(const_cast<NRooTrackerVtx &>( rhs ).EvtProb)
   , StdHepN(const_cast<NRooTrackerVtx &>( rhs ).StdHepN)
   , StdHepPdg(const_cast<NRooTrackerVtx &>( rhs ).StdHepPdg)
   , StdHepStatus(const_cast<NRooTrackerVtx &>( rhs ).StdHepStatus)
   , StdHepFd(const_cast<NRooTrackerVtx &>( rhs ).StdHepFd)
   , StdHepLd(const_cast<NRooTrackerVtx &>( rhs ).StdHepLd)
   , StdHepFm(const_cast<NRooTrackerVtx &>( rhs ).StdHepFm)
   , StdHepLm(const_cast<NRooTrackerVtx &>( rhs ).StdHepLm)
   , NEnvc(const_cast<NRooTrackerVtx &>( rhs ).NEnvc)
   , NEipvc(const_cast<NRooTrackerVtx &>( rhs ).NEipvc)
   , NEiorgvc(const_cast<NRooTrackerVtx &>( rhs ).NEiorgvc)
   , NEiflgvc(const_cast<NRooTrackerVtx &>( rhs ).NEiflgvc)
   , NEicrnvc(const_cast<NRooTrackerVtx &>( rhs ).NEicrnvc)
   , NEcrsx(const_cast<NRooTrackerVtx &>( rhs ).NEcrsx)
   , NEcrsy(const_cast<NRooTrackerVtx &>( rhs ).NEcrsy)
   , NEcrsz(const_cast<NRooTrackerVtx &>( rhs ).NEcrsz)
   , NEcrsphi(const_cast<NRooTrackerVtx &>( rhs ).NEcrsphi)
   , NEnvert(const_cast<NRooTrackerVtx &>( rhs ).NEnvert)
   , NEiflgvert(const_cast<NRooTrackerVtx &>( rhs ).NEiflgvert)
   , NEnvcvert(const_cast<NRooTrackerVtx &>( rhs ).NEnvcvert)
   , NEabspvert(const_cast<NRooTrackerVtx &>( rhs ).NEabspvert)
   , NEabstpvert(const_cast<NRooTrackerVtx &>( rhs ).NEabstpvert)
   , NEipvert(const_cast<NRooTrackerVtx &>( rhs ).NEipvert)
   , NEiverti(const_cast<NRooTrackerVtx &>( rhs ).NEiverti)
   , NEivertf(const_cast<NRooTrackerVtx &>( rhs ).NEivertf)
   , NFnvert(const_cast<NRooTrackerVtx &>( rhs ).NFnvert)
   , NFiflag(const_cast<NRooTrackerVtx &>( rhs ).NFiflag)
   , NFx(const_cast<NRooTrackerVtx &>( rhs ).NFx)
   , NFy(const_cast<NRooTrackerVtx &>( rhs ).NFy)
   , NFz(const_cast<NRooTrackerVtx &>( rhs ).NFz)
   , NFpx(const_cast<NRooTrackerVtx &>( rhs ).NFpx)
   , NFpy(const_cast<NRooTrackerVtx &>( rhs ).NFpy)
   , NFpz(const_cast<NRooTrackerVtx &>( rhs ).NFpz)
   , NFe(const_cast<NRooTrackerVtx &>( rhs ).NFe)
   , NFfirststep(const_cast<NRooTrackerVtx &>( rhs ).NFfirststep)
   , NFnstep(const_cast<NRooTrackerVtx &>( rhs ).NFnstep)
   , NFecms2(const_cast<NRooTrackerVtx &>( rhs ).NFecms2)
   , PCascProb(const_cast<NRooTrackerVtx &>( rhs ).PCascProb)
   , Prob(const_cast<NRooTrackerVtx &>( rhs ).Prob)
   , VertFlagStep(const_cast<NRooTrackerVtx &>( rhs ).VertFlagStep)
   , VertFsiRhon(const_cast<NRooTrackerVtx &>( rhs ).VertFsiRhon)
   , StepPel(const_cast<NRooTrackerVtx &>( rhs ).StepPel)
   , StepPsp(const_cast<NRooTrackerVtx &>( rhs ).StepPsp)
   , StepPdp(const_cast<NRooTrackerVtx &>( rhs ).StepPdp)
   , StepScaleFactor(const_cast<NRooTrackerVtx &>( rhs ).StepScaleFactor)
   , StepEkin(const_cast<NRooTrackerVtx &>( rhs ).StepEkin)
   , SPIDelta(const_cast<NRooTrackerVtx &>( rhs ).SPIDelta)
   , IRadCorrPht(const_cast<NRooTrackerVtx &>( rhs ).IRadCorrPht)
   , GeomPath(const_cast<NRooTrackerVtx &>( rhs ).GeomPath)
   , GeneratorName(const_cast<NRooTrackerVtx &>( rhs ).GeneratorName)
   , OrigFileName(const_cast<NRooTrackerVtx &>( rhs ).OrigFileName)
   , OrigTreeName(const_cast<NRooTrackerVtx &>( rhs ).OrigTreeName)
   , OrigEvtNum(const_cast<NRooTrackerVtx &>( rhs ).OrigEvtNum)
   , OrigTreeEntries(const_cast<NRooTrackerVtx &>( rhs ).OrigTreeEntries)
   , OrigTreePOT(const_cast<NRooTrackerVtx &>( rhs ).OrigTreePOT)
   , TimeInSpill(const_cast<NRooTrackerVtx &>( rhs ).TimeInSpill)
   , TruthVertexID(const_cast<NRooTrackerVtx &>( rhs ).TruthVertexID)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   NRooTrackerVtx &modrhs = const_cast<NRooTrackerVtx &>( rhs );
   modrhs.EvtCode = 0;
   for (Int_t i=0;i<4;i++) EvtVtx[i] = rhs.EvtVtx[i];
   modrhs.StdHepPdg = 0;
   modrhs.StdHepStatus = 0;
   for (Int_t i=0;i<400;i++) reinterpret_cast<double *>(StdHepX4)[i] = reinterpret_cast<double const *>(rhs.StdHepX4)[i];
   for (Int_t i=0;i<400;i++) reinterpret_cast<double *>(StdHepP4)[i] = reinterpret_cast<double const *>(rhs.StdHepP4)[i];
   for (Int_t i=0;i<300;i++) reinterpret_cast<double *>(StdHepPolz)[i] = reinterpret_cast<double const *>(rhs.StdHepPolz)[i];
   modrhs.StdHepFd = 0;
   modrhs.StdHepLd = 0;
   modrhs.StdHepFm = 0;
   modrhs.StdHepLm = 0;
   modrhs.NEipvc = 0;
   for (Int_t i=0;i<300;i++) reinterpret_cast<float *>(NEpvc)[i] = reinterpret_cast<float const *>(rhs.NEpvc)[i];
   modrhs.NEiorgvc = 0;
   modrhs.NEiflgvc = 0;
   modrhs.NEicrnvc = 0;
   for (Int_t i=0;i<300;i++) reinterpret_cast<float *>(NEposvert)[i] = reinterpret_cast<float const *>(rhs.NEposvert)[i];
   modrhs.NEiflgvert = 0;
   for (Int_t i=0;i<900;i++) reinterpret_cast<float *>(NEdirvert)[i] = reinterpret_cast<float const *>(rhs.NEdirvert)[i];
   modrhs.NEabspvert = 0;
   modrhs.NEabstpvert = 0;
   modrhs.NEipvert = 0;
   modrhs.NEiverti = 0;
   modrhs.NEivertf = 0;
   modrhs.NFiflag = 0;
   modrhs.NFx = 0;
   modrhs.NFy = 0;
   modrhs.NFz = 0;
   modrhs.NFpx = 0;
   modrhs.NFpy = 0;
   modrhs.NFpz = 0;
   modrhs.NFe = 0;
   modrhs.NFfirststep = 0;
   modrhs.NFecms2 = 0;
   modrhs.Prob = 0;
   modrhs.VertFlagStep = 0;
   modrhs.VertFsiRhon = 0;
   modrhs.StepPel = 0;
   modrhs.StepPsp = 0;
   modrhs.StepPdp = 0;
   modrhs.StepScaleFactor = 0;
   modrhs.StepEkin = 0;
   modrhs.GeomPath = 0;
   modrhs.GeneratorName = 0;
   modrhs.OrigFileName = 0;
   modrhs.OrigTreeName = 0;
}
ND::NRooTrackerVtx::~NRooTrackerVtx() {
   delete EvtCode;   EvtCode = 0;
   delete [] StdHepPdg;   StdHepPdg = 0;
   delete [] StdHepStatus;   StdHepStatus = 0;
   delete [] StdHepFd;   StdHepFd = 0;
   delete [] StdHepLd;   StdHepLd = 0;
   delete [] StdHepFm;   StdHepFm = 0;
   delete [] StdHepLm;   StdHepLm = 0;
   delete [] NEipvc;   NEipvc = 0;
   delete [] NEiorgvc;   NEiorgvc = 0;
   delete [] NEiflgvc;   NEiflgvc = 0;
   delete [] NEicrnvc;   NEicrnvc = 0;
   delete [] NEiflgvert;   NEiflgvert = 0;
   delete [] NEabspvert;   NEabspvert = 0;
   delete [] NEabstpvert;   NEabstpvert = 0;
   delete [] NEipvert;   NEipvert = 0;
   delete [] NEiverti;   NEiverti = 0;
   delete [] NEivertf;   NEivertf = 0;
   delete [] NFiflag;   NFiflag = 0;
   delete [] NFx;   NFx = 0;
   delete [] NFy;   NFy = 0;
   delete [] NFz;   NFz = 0;
   delete [] NFpx;   NFpx = 0;
   delete [] NFpy;   NFpy = 0;
   delete [] NFpz;   NFpz = 0;
   delete [] NFe;   NFe = 0;
   delete [] NFfirststep;   NFfirststep = 0;
   delete [] NFecms2;   NFecms2 = 0;
   delete [] Prob;   Prob = 0;
   delete [] VertFlagStep;   VertFlagStep = 0;
   delete [] VertFsiRhon;   VertFsiRhon = 0;
   delete [] StepPel;   StepPel = 0;
   delete [] StepPsp;   StepPsp = 0;
   delete [] StepPdp;   StepPdp = 0;
   delete [] StepScaleFactor;   StepScaleFactor = 0;
   delete [] StepEkin;   StepEkin = 0;
   delete GeomPath;   GeomPath = 0;
   delete GeneratorName;   GeneratorName = 0;
   delete OrigFileName;   OrigFileName = 0;
   delete OrigTreeName;   OrigTreeName = 0;
}
#endif // ND__NRooTrackerVtx_cxx

#ifndef ND__JNuBeamFlux_cxx
#define ND__JNuBeamFlux_cxx
ND::JNuBeamFlux::JNuBeamFlux() {
   NuFileName = 0;
}
ND::JNuBeamFlux &ND::JNuBeamFlux::operator=(const JNuBeamFlux & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   ND::RooTrackerVtxBase::operator=(const_cast<JNuBeamFlux &>( rhs ));
   NuFluxEntry = (const_cast<JNuBeamFlux &>( rhs ).NuFluxEntry);
   NuFileName = (const_cast<JNuBeamFlux &>( rhs ).NuFileName);
   NuParentPdg = (const_cast<JNuBeamFlux &>( rhs ).NuParentPdg);
   NuParentDecMode = (const_cast<JNuBeamFlux &>( rhs ).NuParentDecMode);
   NuCospibm = (const_cast<JNuBeamFlux &>( rhs ).NuCospibm);
   NuNorm = (const_cast<JNuBeamFlux &>( rhs ).NuNorm);
   NuCospi0bm = (const_cast<JNuBeamFlux &>( rhs ).NuCospi0bm);
   NuRnu = (const_cast<JNuBeamFlux &>( rhs ).NuRnu);
   NuIdfd = (const_cast<JNuBeamFlux &>( rhs ).NuIdfd);
   NuGipart = (const_cast<JNuBeamFlux &>( rhs ).NuGipart);
   NuGamom0 = (const_cast<JNuBeamFlux &>( rhs ).NuGamom0);
   NuNg = (const_cast<JNuBeamFlux &>( rhs ).NuNg);
   NuEnusk = (const_cast<JNuBeamFlux &>( rhs ).NuEnusk);
   NuNormsk = (const_cast<JNuBeamFlux &>( rhs ).NuNormsk);
   NuAnorm = (const_cast<JNuBeamFlux &>( rhs ).NuAnorm);
   NuVersion = (const_cast<JNuBeamFlux &>( rhs ).NuVersion);
   NuTuneid = (const_cast<JNuBeamFlux &>( rhs ).NuTuneid);
   NuNtrig = (const_cast<JNuBeamFlux &>( rhs ).NuNtrig);
   NuPint = (const_cast<JNuBeamFlux &>( rhs ).NuPint);
   NuRand = (const_cast<JNuBeamFlux &>( rhs ).NuRand);
   JNuBeamFlux &modrhs = const_cast<JNuBeamFlux &>( rhs );
   modrhs.NuFileName = 0;
   for (Int_t i=0;i<4;i++) NuParentDecP4[i] = rhs.NuParentDecP4[i];
   for (Int_t i=0;i<4;i++) NuParentDecX4[i] = rhs.NuParentDecX4[i];
   for (Int_t i=0;i<4;i++) NuParentProP4[i] = rhs.NuParentProP4[i];
   for (Int_t i=0;i<4;i++) NuParentProX4[i] = rhs.NuParentProX4[i];
   for (Int_t i=0;i<2;i++) NuXnu[i] = rhs.NuXnu[i];
   for (Int_t i=0;i<3;i++) NuGpos0[i] = rhs.NuGpos0[i];
   for (Int_t i=0;i<3;i++) NuGvec0[i] = rhs.NuGvec0[i];
   for (Int_t i=0;i<36;i++) reinterpret_cast<float *>(NuGp)[i] = reinterpret_cast<float const *>(rhs.NuGp)[i];
   for (Int_t i=0;i<12;i++) NuGcosbm[i] = rhs.NuGcosbm[i];
   for (Int_t i=0;i<36;i++) reinterpret_cast<float *>(NuGv)[i] = reinterpret_cast<float const *>(rhs.NuGv)[i];
   for (Int_t i=0;i<12;i++) NuGpid[i] = rhs.NuGpid[i];
   for (Int_t i=0;i<12;i++) NuGmec[i] = rhs.NuGmec[i];
   for (Int_t i=0;i<12;i++) NuGmat[i] = rhs.NuGmat[i];
   for (Int_t i=0;i<12;i++) NuGdistc[i] = rhs.NuGdistc[i];
   for (Int_t i=0;i<12;i++) NuGdistal[i] = rhs.NuGdistal[i];
   for (Int_t i=0;i<12;i++) NuGdistti[i] = rhs.NuGdistti[i];
   for (Int_t i=0;i<12;i++) NuGdistfe[i] = rhs.NuGdistfe[i];
   for (Int_t i=0;i<2;i++) NuBpos[i] = rhs.NuBpos[i];
   for (Int_t i=0;i<2;i++) NuBtilt[i] = rhs.NuBtilt[i];
   for (Int_t i=0;i<2;i++) NuBrms[i] = rhs.NuBrms[i];
   for (Int_t i=0;i<2;i++) NuEmit[i] = rhs.NuEmit[i];
   for (Int_t i=0;i<2;i++) NuAlpha[i] = rhs.NuAlpha[i];
   for (Int_t i=0;i<3;i++) NuHcur[i] = rhs.NuHcur[i];
   return *this;
}
ND::JNuBeamFlux::JNuBeamFlux(const JNuBeamFlux & rhs)
   : ND::RooTrackerVtxBase(const_cast<JNuBeamFlux &>( rhs ))
   , NuFluxEntry(const_cast<JNuBeamFlux &>( rhs ).NuFluxEntry)
   , NuFileName(const_cast<JNuBeamFlux &>( rhs ).NuFileName)
   , NuParentPdg(const_cast<JNuBeamFlux &>( rhs ).NuParentPdg)
   , NuParentDecMode(const_cast<JNuBeamFlux &>( rhs ).NuParentDecMode)
   , NuCospibm(const_cast<JNuBeamFlux &>( rhs ).NuCospibm)
   , NuNorm(const_cast<JNuBeamFlux &>( rhs ).NuNorm)
   , NuCospi0bm(const_cast<JNuBeamFlux &>( rhs ).NuCospi0bm)
   , NuRnu(const_cast<JNuBeamFlux &>( rhs ).NuRnu)
   , NuIdfd(const_cast<JNuBeamFlux &>( rhs ).NuIdfd)
   , NuGipart(const_cast<JNuBeamFlux &>( rhs ).NuGipart)
   , NuGamom0(const_cast<JNuBeamFlux &>( rhs ).NuGamom0)
   , NuNg(const_cast<JNuBeamFlux &>( rhs ).NuNg)
   , NuEnusk(const_cast<JNuBeamFlux &>( rhs ).NuEnusk)
   , NuNormsk(const_cast<JNuBeamFlux &>( rhs ).NuNormsk)
   , NuAnorm(const_cast<JNuBeamFlux &>( rhs ).NuAnorm)
   , NuVersion(const_cast<JNuBeamFlux &>( rhs ).NuVersion)
   , NuTuneid(const_cast<JNuBeamFlux &>( rhs ).NuTuneid)
   , NuNtrig(const_cast<JNuBeamFlux &>( rhs ).NuNtrig)
   , NuPint(const_cast<JNuBeamFlux &>( rhs ).NuPint)
   , NuRand(const_cast<JNuBeamFlux &>( rhs ).NuRand)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   JNuBeamFlux &modrhs = const_cast<JNuBeamFlux &>( rhs );
   modrhs.NuFileName = 0;
   for (Int_t i=0;i<4;i++) NuParentDecP4[i] = rhs.NuParentDecP4[i];
   for (Int_t i=0;i<4;i++) NuParentDecX4[i] = rhs.NuParentDecX4[i];
   for (Int_t i=0;i<4;i++) NuParentProP4[i] = rhs.NuParentProP4[i];
   for (Int_t i=0;i<4;i++) NuParentProX4[i] = rhs.NuParentProX4[i];
   for (Int_t i=0;i<2;i++) NuXnu[i] = rhs.NuXnu[i];
   for (Int_t i=0;i<3;i++) NuGpos0[i] = rhs.NuGpos0[i];
   for (Int_t i=0;i<3;i++) NuGvec0[i] = rhs.NuGvec0[i];
   for (Int_t i=0;i<36;i++) reinterpret_cast<float *>(NuGp)[i] = reinterpret_cast<float const *>(rhs.NuGp)[i];
   for (Int_t i=0;i<12;i++) NuGcosbm[i] = rhs.NuGcosbm[i];
   for (Int_t i=0;i<36;i++) reinterpret_cast<float *>(NuGv)[i] = reinterpret_cast<float const *>(rhs.NuGv)[i];
   for (Int_t i=0;i<12;i++) NuGpid[i] = rhs.NuGpid[i];
   for (Int_t i=0;i<12;i++) NuGmec[i] = rhs.NuGmec[i];
   for (Int_t i=0;i<12;i++) NuGmat[i] = rhs.NuGmat[i];
   for (Int_t i=0;i<12;i++) NuGdistc[i] = rhs.NuGdistc[i];
   for (Int_t i=0;i<12;i++) NuGdistal[i] = rhs.NuGdistal[i];
   for (Int_t i=0;i<12;i++) NuGdistti[i] = rhs.NuGdistti[i];
   for (Int_t i=0;i<12;i++) NuGdistfe[i] = rhs.NuGdistfe[i];
   for (Int_t i=0;i<2;i++) NuBpos[i] = rhs.NuBpos[i];
   for (Int_t i=0;i<2;i++) NuBtilt[i] = rhs.NuBtilt[i];
   for (Int_t i=0;i<2;i++) NuBrms[i] = rhs.NuBrms[i];
   for (Int_t i=0;i<2;i++) NuEmit[i] = rhs.NuEmit[i];
   for (Int_t i=0;i<2;i++) NuAlpha[i] = rhs.NuAlpha[i];
   for (Int_t i=0;i<3;i++) NuHcur[i] = rhs.NuHcur[i];
}
ND::JNuBeamFlux::~JNuBeamFlux() {
   delete NuFileName;   NuFileName = 0;
}
#endif // ND__JNuBeamFlux_cxx

#ifndef ND__RooTrackerVtxBase_cxx
#define ND__RooTrackerVtxBase_cxx
ND::RooTrackerVtxBase::RooTrackerVtxBase() {
}
ND::RooTrackerVtxBase &ND::RooTrackerVtxBase::operator=(const RooTrackerVtxBase & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<RooTrackerVtxBase &>( rhs ));
   return *this;
}
ND::RooTrackerVtxBase::RooTrackerVtxBase(const RooTrackerVtxBase & rhs)
   : TObject(const_cast<RooTrackerVtxBase &>( rhs ))
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
ND::RooTrackerVtxBase::~RooTrackerVtxBase() {
}
#endif // ND__RooTrackerVtxBase_cxx

#ifndef WCSimRootCapture_cxx
#define WCSimRootCapture_cxx
WCSimRootCapture::WCSimRootCapture() {
   fGammas = 0;
}
WCSimRootCapture &WCSimRootCapture::operator=(const WCSimRootCapture & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootCapture &>( rhs ));
   fCaptureParent = (const_cast<WCSimRootCapture &>( rhs ).fCaptureParent);
   fNGamma = (const_cast<WCSimRootCapture &>( rhs ).fNGamma);
   fTotalGammaE = (const_cast<WCSimRootCapture &>( rhs ).fTotalGammaE);
   fCaptureT = (const_cast<WCSimRootCapture &>( rhs ).fCaptureT);
   fCaptureNucleus = (const_cast<WCSimRootCapture &>( rhs ).fCaptureNucleus);
   fGammas = (const_cast<WCSimRootCapture &>( rhs ).fGammas);
   IsZombie = (const_cast<WCSimRootCapture &>( rhs ).IsZombie);
   for (Int_t i=0;i<3;i++) fCaptureVtx[i] = rhs.fCaptureVtx[i];
   WCSimRootCapture &modrhs = const_cast<WCSimRootCapture &>( rhs );
   modrhs.fGammas = 0;
   return *this;
}
WCSimRootCapture::WCSimRootCapture(const WCSimRootCapture & rhs)
   : TObject(const_cast<WCSimRootCapture &>( rhs ))
   , fCaptureParent(const_cast<WCSimRootCapture &>( rhs ).fCaptureParent)
   , fNGamma(const_cast<WCSimRootCapture &>( rhs ).fNGamma)
   , fTotalGammaE(const_cast<WCSimRootCapture &>( rhs ).fTotalGammaE)
   , fCaptureT(const_cast<WCSimRootCapture &>( rhs ).fCaptureT)
   , fCaptureNucleus(const_cast<WCSimRootCapture &>( rhs ).fCaptureNucleus)
   , fGammas(const_cast<WCSimRootCapture &>( rhs ).fGammas)
   , IsZombie(const_cast<WCSimRootCapture &>( rhs ).IsZombie)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<3;i++) fCaptureVtx[i] = rhs.fCaptureVtx[i];
   WCSimRootCapture &modrhs = const_cast<WCSimRootCapture &>( rhs );
   modrhs.fGammas = 0;
}
WCSimRootCapture::~WCSimRootCapture() {
   delete fGammas;   fGammas = 0;
}
#endif // WCSimRootCapture_cxx

#ifndef WCSimRootTrack_cxx
#define WCSimRootTrack_cxx
WCSimRootTrack::WCSimRootTrack() {
}
WCSimRootTrack &WCSimRootTrack::operator=(const WCSimRootTrack & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootTrack &>( rhs ));
   fIpnu = (const_cast<WCSimRootTrack &>( rhs ).fIpnu);
   fFlag = (const_cast<WCSimRootTrack &>( rhs ).fFlag);
   fM = (const_cast<WCSimRootTrack &>( rhs ).fM);
   fP = (const_cast<WCSimRootTrack &>( rhs ).fP);
   fE = (const_cast<WCSimRootTrack &>( rhs ).fE);
   fStartvol = (const_cast<WCSimRootTrack &>( rhs ).fStartvol);
   fStopvol = (const_cast<WCSimRootTrack &>( rhs ).fStopvol);
   fParenttype = (const_cast<WCSimRootTrack &>( rhs ).fParenttype);
   fCreatorProcess = (const_cast<WCSimRootTrack &>( rhs ).fCreatorProcess);
   fTime = (const_cast<WCSimRootTrack &>( rhs ).fTime);
   fId = (const_cast<WCSimRootTrack &>( rhs ).fId);
   fParentId = (const_cast<WCSimRootTrack &>( rhs ).fParentId);
   boundaryPoints = (const_cast<WCSimRootTrack &>( rhs ).boundaryPoints);
   boundaryKEs = (const_cast<WCSimRootTrack &>( rhs ).boundaryKEs);
   boundaryTimes = (const_cast<WCSimRootTrack &>( rhs ).boundaryTimes);
   boundaryTypes = (const_cast<WCSimRootTrack &>( rhs ).boundaryTypes);
   for (Int_t i=0;i<3;i++) fDir[i] = rhs.fDir[i];
   for (Int_t i=0;i<3;i++) fPdir[i] = rhs.fPdir[i];
   for (Int_t i=0;i<3;i++) fStop[i] = rhs.fStop[i];
   for (Int_t i=0;i<3;i++) fStart[i] = rhs.fStart[i];
   WCSimRootTrack &modrhs = const_cast<WCSimRootTrack &>( rhs );
   modrhs.boundaryPoints.clear();
   modrhs.boundaryKEs.clear();
   modrhs.boundaryTimes.clear();
   modrhs.boundaryTypes.clear();
   return *this;
}
WCSimRootTrack::WCSimRootTrack(const WCSimRootTrack & rhs)
   : TObject(const_cast<WCSimRootTrack &>( rhs ))
   , fIpnu(const_cast<WCSimRootTrack &>( rhs ).fIpnu)
   , fFlag(const_cast<WCSimRootTrack &>( rhs ).fFlag)
   , fM(const_cast<WCSimRootTrack &>( rhs ).fM)
   , fP(const_cast<WCSimRootTrack &>( rhs ).fP)
   , fE(const_cast<WCSimRootTrack &>( rhs ).fE)
   , fStartvol(const_cast<WCSimRootTrack &>( rhs ).fStartvol)
   , fStopvol(const_cast<WCSimRootTrack &>( rhs ).fStopvol)
   , fParenttype(const_cast<WCSimRootTrack &>( rhs ).fParenttype)
   , fCreatorProcess(const_cast<WCSimRootTrack &>( rhs ).fCreatorProcess)
   , fTime(const_cast<WCSimRootTrack &>( rhs ).fTime)
   , fId(const_cast<WCSimRootTrack &>( rhs ).fId)
   , fParentId(const_cast<WCSimRootTrack &>( rhs ).fParentId)
   , boundaryPoints(const_cast<WCSimRootTrack &>( rhs ).boundaryPoints)
   , boundaryKEs(const_cast<WCSimRootTrack &>( rhs ).boundaryKEs)
   , boundaryTimes(const_cast<WCSimRootTrack &>( rhs ).boundaryTimes)
   , boundaryTypes(const_cast<WCSimRootTrack &>( rhs ).boundaryTypes)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<3;i++) fDir[i] = rhs.fDir[i];
   for (Int_t i=0;i<3;i++) fPdir[i] = rhs.fPdir[i];
   for (Int_t i=0;i<3;i++) fStop[i] = rhs.fStop[i];
   for (Int_t i=0;i<3;i++) fStart[i] = rhs.fStart[i];
   WCSimRootTrack &modrhs = const_cast<WCSimRootTrack &>( rhs );
   modrhs.boundaryPoints.clear();
   modrhs.boundaryKEs.clear();
   modrhs.boundaryTimes.clear();
   modrhs.boundaryTypes.clear();
}
WCSimRootTrack::~WCSimRootTrack() {
}
#endif // WCSimRootTrack_cxx

#ifndef WCSimRootCherenkovHit_cxx
#define WCSimRootCherenkovHit_cxx
WCSimRootCherenkovHit::WCSimRootCherenkovHit() {
}
WCSimRootCherenkovHit &WCSimRootCherenkovHit::operator=(const WCSimRootCherenkovHit & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootCherenkovHit &>( rhs ));
   fTubeID = (const_cast<WCSimRootCherenkovHit &>( rhs ).fTubeID);
   fmPMTID = (const_cast<WCSimRootCherenkovHit &>( rhs ).fmPMTID);
   fmPMT_PMTID = (const_cast<WCSimRootCherenkovHit &>( rhs ).fmPMT_PMTID);
   for (Int_t i=0;i<2;i++) fTotalPe[i] = rhs.fTotalPe[i];
   return *this;
}
WCSimRootCherenkovHit::WCSimRootCherenkovHit(const WCSimRootCherenkovHit & rhs)
   : TObject(const_cast<WCSimRootCherenkovHit &>( rhs ))
   , fTubeID(const_cast<WCSimRootCherenkovHit &>( rhs ).fTubeID)
   , fmPMTID(const_cast<WCSimRootCherenkovHit &>( rhs ).fmPMTID)
   , fmPMT_PMTID(const_cast<WCSimRootCherenkovHit &>( rhs ).fmPMT_PMTID)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<2;i++) fTotalPe[i] = rhs.fTotalPe[i];
}
WCSimRootCherenkovHit::~WCSimRootCherenkovHit() {
}
#endif // WCSimRootCherenkovHit_cxx

#ifndef WCSimRootCherenkovHitTime_cxx
#define WCSimRootCherenkovHitTime_cxx
WCSimRootCherenkovHitTime::WCSimRootCherenkovHitTime() {
}
WCSimRootCherenkovHitTime &WCSimRootCherenkovHitTime::operator=(const WCSimRootCherenkovHitTime & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootCherenkovHitTime &>( rhs ));
   fTruetime = (const_cast<WCSimRootCherenkovHitTime &>( rhs ).fTruetime);
   fParentSavedTrackID = (const_cast<WCSimRootCherenkovHitTime &>( rhs ).fParentSavedTrackID);
   fPhotonStartTime = (const_cast<WCSimRootCherenkovHitTime &>( rhs ).fPhotonStartTime);
   fPhotonStartEnergy = (const_cast<WCSimRootCherenkovHitTime &>( rhs ).fPhotonStartEnergy);
   fPhotonEndEnergy = (const_cast<WCSimRootCherenkovHitTime &>( rhs ).fPhotonEndEnergy);
   fPhotonCreatorProcess = (const_cast<WCSimRootCherenkovHitTime &>( rhs ).fPhotonCreatorProcess);
   for (Int_t i=0;i<3;i++) fPhotonStartPos[i] = rhs.fPhotonStartPos[i];
   for (Int_t i=0;i<3;i++) fPhotonEndPos[i] = rhs.fPhotonEndPos[i];
   for (Int_t i=0;i<3;i++) fPhotonStartDir[i] = rhs.fPhotonStartDir[i];
   for (Int_t i=0;i<3;i++) fPhotonEndDir[i] = rhs.fPhotonEndDir[i];
   return *this;
}
WCSimRootCherenkovHitTime::WCSimRootCherenkovHitTime(const WCSimRootCherenkovHitTime & rhs)
   : TObject(const_cast<WCSimRootCherenkovHitTime &>( rhs ))
   , fTruetime(const_cast<WCSimRootCherenkovHitTime &>( rhs ).fTruetime)
   , fParentSavedTrackID(const_cast<WCSimRootCherenkovHitTime &>( rhs ).fParentSavedTrackID)
   , fPhotonStartTime(const_cast<WCSimRootCherenkovHitTime &>( rhs ).fPhotonStartTime)
   , fPhotonStartEnergy(const_cast<WCSimRootCherenkovHitTime &>( rhs ).fPhotonStartEnergy)
   , fPhotonEndEnergy(const_cast<WCSimRootCherenkovHitTime &>( rhs ).fPhotonEndEnergy)
   , fPhotonCreatorProcess(const_cast<WCSimRootCherenkovHitTime &>( rhs ).fPhotonCreatorProcess)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<3;i++) fPhotonStartPos[i] = rhs.fPhotonStartPos[i];
   for (Int_t i=0;i<3;i++) fPhotonEndPos[i] = rhs.fPhotonEndPos[i];
   for (Int_t i=0;i<3;i++) fPhotonStartDir[i] = rhs.fPhotonStartDir[i];
   for (Int_t i=0;i<3;i++) fPhotonEndDir[i] = rhs.fPhotonEndDir[i];
}
WCSimRootCherenkovHitTime::~WCSimRootCherenkovHitTime() {
}
#endif // WCSimRootCherenkovHitTime_cxx

#ifndef WCSimRootCherenkovHitHistory_cxx
#define WCSimRootCherenkovHitHistory_cxx
WCSimRootCherenkovHitHistory::WCSimRootCherenkovHitHistory() {
}
WCSimRootCherenkovHitHistory &WCSimRootCherenkovHitHistory::operator=(const WCSimRootCherenkovHitHistory & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootCherenkovHitHistory &>( rhs ));
   fNRayScat = (const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fNRayScat);
   fNRamScat = (const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fNRamScat);
   fNMieScat = (const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fNMieScat);
   fReflec = (const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fReflec);
   fStepsX = (const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fStepsX);
   fStepsY = (const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fStepsY);
   fStepsZ = (const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fStepsZ);
   fStepsType = (const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fStepsType);
   WCSimRootCherenkovHitHistory &modrhs = const_cast<WCSimRootCherenkovHitHistory &>( rhs );
   modrhs.fReflec.clear();
   modrhs.fStepsX.clear();
   modrhs.fStepsY.clear();
   modrhs.fStepsZ.clear();
   modrhs.fStepsType.clear();
   return *this;
}
WCSimRootCherenkovHitHistory::WCSimRootCherenkovHitHistory(const WCSimRootCherenkovHitHistory & rhs)
   : TObject(const_cast<WCSimRootCherenkovHitHistory &>( rhs ))
   , fNRayScat(const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fNRayScat)
   , fNRamScat(const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fNRamScat)
   , fNMieScat(const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fNMieScat)
   , fReflec(const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fReflec)
   , fStepsX(const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fStepsX)
   , fStepsY(const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fStepsY)
   , fStepsZ(const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fStepsZ)
   , fStepsType(const_cast<WCSimRootCherenkovHitHistory &>( rhs ).fStepsType)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   WCSimRootCherenkovHitHistory &modrhs = const_cast<WCSimRootCherenkovHitHistory &>( rhs );
   modrhs.fReflec.clear();
   modrhs.fStepsX.clear();
   modrhs.fStepsY.clear();
   modrhs.fStepsZ.clear();
   modrhs.fStepsType.clear();
}
WCSimRootCherenkovHitHistory::~WCSimRootCherenkovHitHistory() {
}
#endif // WCSimRootCherenkovHitHistory_cxx

#ifndef WCSimRootCherenkovDigiHit_cxx
#define WCSimRootCherenkovDigiHit_cxx
WCSimRootCherenkovDigiHit::WCSimRootCherenkovDigiHit() {
}
WCSimRootCherenkovDigiHit &WCSimRootCherenkovDigiHit::operator=(const WCSimRootCherenkovDigiHit & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<WCSimRootCherenkovDigiHit &>( rhs ));
   fQ = (const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fQ);
   fT = (const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fT);
   fTubeId = (const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fTubeId);
   fmPMTId = (const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fmPMTId);
   fmPMT_PMTId = (const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fmPMT_PMTId);
   fPhotonIds = (const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fPhotonIds);
   WCSimRootCherenkovDigiHit &modrhs = const_cast<WCSimRootCherenkovDigiHit &>( rhs );
   modrhs.fPhotonIds.clear();
   return *this;
}
WCSimRootCherenkovDigiHit::WCSimRootCherenkovDigiHit(const WCSimRootCherenkovDigiHit & rhs)
   : TObject(const_cast<WCSimRootCherenkovDigiHit &>( rhs ))
   , fQ(const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fQ)
   , fT(const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fT)
   , fTubeId(const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fTubeId)
   , fmPMTId(const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fmPMTId)
   , fmPMT_PMTId(const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fmPMT_PMTId)
   , fPhotonIds(const_cast<WCSimRootCherenkovDigiHit &>( rhs ).fPhotonIds)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   WCSimRootCherenkovDigiHit &modrhs = const_cast<WCSimRootCherenkovDigiHit &>( rhs );
   modrhs.fPhotonIds.clear();
}
WCSimRootCherenkovDigiHit::~WCSimRootCherenkovDigiHit() {
}
#endif // WCSimRootCherenkovDigiHit_cxx

