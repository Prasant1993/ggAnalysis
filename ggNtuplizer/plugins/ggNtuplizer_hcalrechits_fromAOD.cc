#include "../interface/ggNtuplizer.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/ESGetToken.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/CaloRecHit/interface/CaloRecHit.h"
#include "DataFormats/RecoCandidate/interface/CaloRecHitCandidate.h"

//edm::SortedCollection<HBHERecHit,edm::StrictWeakOrdering<HBHERecHit> >    "reducedHcalRecHits"        "hbhereco"        "RECO"              
//edm::SortedCollection<HFRecHit,edm::StrictWeakOrdering<HFRecHit> >    "reducedHcalRecHits"        "hfreco"          "RECO"
//edm::SortedCollection<HORecHit,edm::StrictWeakOrdering<HORecHit> >    "reducedHcalRecHits"        "horeco"          "RECO"

using namespace std;
using namespace edm;

/////EB                                                                                                                                   
Int_t nhbheRechit_;
vector<Float_t> hbheRechitE_;
vector<Int_t> hbheRechitiEta_;
vector<Int_t> hbheRechitiPhi_;
//vector<Int_t> ebRechitZside_;
vector<Float_t> hbheRechitEta_;
vector<Float_t> hbheRechitPhi_;
vector<Float_t> hbheRechitX_;
vector<Float_t> hbheRechitY_;
vector<Float_t> hbheRechitZ_;
vector<Int_t> hbheRechitDetID_;


void ggNtuplizer::brancheshcalRechits(TTree* tree) {
  
  if(dumpCrystalinfo_){
  tree->Branch("nhbheRechit",         &nhbheRechit_);
  tree->Branch("hbheRechitE",         &hbheRechitE_);
  tree->Branch("hbheRechitiEta",         &hbheRechitiEta_);
  tree->Branch("hbheRechitiPhi",         &hbheRechitiPhi_);
  //tree->Branch("hbheRechitZside",         &ebRechitZside_);
  tree->Branch("hbheRechitEta",         &hbheRechitEta_);
  tree->Branch("hbheRechitPhi",         &hbheRechitPhi_);
  tree->Branch("hbheRechitX",         &hbheRechitX_);
  tree->Branch("hbheRechitY",         &hbheRechitY_);
  tree->Branch("hbheRechitZ",         &hbheRechitZ_);
  tree->Branch("hbheRechitDetID",         &hbheRechitDetID_);  
  
  }
}

///////////////////////////////////
// member functions
//////////////////////////////////
// ------------ method called for each event  ------------
void ggNtuplizer::fillhcalRechits(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  //bool debugRH = true;
  bool debugRH = false;

  //////////////////////////////HBHE rechits/////////////////////////////////////////
 
  nhbheRechit_ = 0;  
  hbheRechitE_.clear();                 
  hbheRechitiEta_.clear();
  hbheRechitiPhi_.clear();
  //ebRechitZside_.clear();
  hbheRechitEta_.clear();
  hbheRechitPhi_.clear();
  hbheRechitX_.clear();
  hbheRechitY_.clear();
  hbheRechitZ_.clear();
  hbheRechitDetID_.clear();
  

  iSetup.getData(CalogeomoToken_);
  edm::ESHandle<CaloGeometry> pG_ = iSetup.getHandle(CalogeomoToken_);
  const CaloGeometry* geo = pG_.product();

  edm::Handle<HBHERecHitCollection> hbheRecHitsHandle;

  iEvent.getByToken(hbheReducedRecHitCollection_,hbheRecHitsHandle);
  
  const HBHERecHitCollection* HBHERecHits = nullptr;
  
    if ( !hbheRecHitsHandle.isValid() ) {
      LogDebug("") << "ggNtuplizer_hcalrechits: Error! HBHE rechits can't get product!" << std::endl;
    } else {
      HBHERecHits = hbheRecHitsHandle.product();  // get a ptr to the product
    }
  
  // https://github.com/cms-sw/cmssw/blob/c2e865adc2671fa7d91832fbdab21b90db967572/DPGAnalysis/Skims/src/BeamSplash.cc#L70
  HBHERecHitCollection::const_iterator hbherechit;
  
  for (hbherechit = HBHERecHits->begin(); hbherechit != HBHERecHits->end(); ++hbherechit) {

    double Energy = hbherechit->energy();
    HcalDetId det = hbherechit->id();
    int ieta = det.ieta();
    int iphi = det.iphi();

    uint32_t detid = det.rawId();                                                                                                              
    if(dumpCrystalinfo_){                                                                                                                     
      hbheRechitE_.push_back(Energy);                                                                                                         
      hbheRechitiEta_.push_back(ieta);                                                                                                        
      hbheRechitiPhi_.push_back(iphi);                                                                                                        
      //hbRechitZside_.push_back(zside);                                                                                                     
      hbheRechitDetID_.push_back(detid);}                                                                                                      
    
                                                                                                                                             
    const GlobalPoint & rechitPoint = geo->getPosition(det);                                                                                 
                                                                                                                                           
    if(dumpCrystalinfo_){                                                                                                                     
      hbheRechitEta_.push_back(rechitPoint.eta());
      hbheRechitPhi_.push_back(rechitPoint.phi());}
                                                                                                                                             
    if(debugRH){                                                                                                                              
      std::cout<<"eta "<<rechitPoint.eta()<<std::endl;                                                                                        
    }                                                                                                                                                                                                                                                                                     
    if(dumpCrystalinfo_){                                                                                                                                                                                                            
      hbheRechitX_.push_back(rechitPoint.x());                                                                                                
      hbheRechitY_.push_back(rechitPoint.y());                                                                                                
      hbheRechitZ_.push_back(rechitPoint.z());}                                                                                     
               
                                                                                                                                              
    nhbheRechit_++;


  }
      
}

