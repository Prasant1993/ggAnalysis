#include "../interface/ggNtuplizer.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/ESGetToken.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/CaloRecHit/interface/CaloRecHit.h"
#include "DataFormats/RecoCandidate/interface/CaloRecHitCandidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "CommonTools/BaseParticlePropagator/interface/BaseParticlePropagator.h"
#include "CommonTools/BaseParticlePropagator/interface/RawParticle.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/GsfTools/interface/MultiGaussianStateTransform.h"
#include "TrackingTools/GsfTools/interface/MultiGaussianState1D.h"
#include "TrackingTools/GsfTools/interface/GaussianSumUtilities1D.h"
#include "RecoParticleFlow/PFTracking/interface/PFGsfHelper.h"
#include "DataFormats/PatCandidates/interface/IsolatedTrack.h"
#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"
#include "TrackingTools/TrackAssociator/interface/TrackDetMatchInfo.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"


using namespace std;
using namespace edm;

Int_t n_tracks_;
std::vector<float> track_eta_;
std::vector<float> track_phi_;
std::vector<float> track_pt_;
std::vector<float> track_energy_;
std::vector<int> track_charge_;

std::vector<float> track_EBpos_x_;
std::vector<float> track_EBpos_y_;
std::vector<float> track_EBpos_z_;
std::vector<float> track_EB_iEta_;
std::vector<float> track_EB_iPhi_;

std::vector<float> track_EEpos_x_;
std::vector<float> track_EEpos_y_;
std::vector<float> track_EEpos_z_;
std::vector<float> track_EE_iEta_;
std::vector<float> track_EE_iPhi_;

std::vector<float> track_ESpos_x_;
std::vector<float> track_ESpos_y_;
std::vector<float> track_ESpos_z_;
std::vector<float> track_ES_iEta_;
std::vector<float> track_ES_iPhi_;
std::vector<Int_t> track_ES_DetID_;
std::vector<Int_t> track_EE_DetID_;
std::vector<Int_t> track_EB_DetID_;


void ggNtuplizer::branchestrackparams_ECALEntrance(TTree* tree) {
                                                                                                                                                                        

  if(dumptrackparamsinfo_){
    tree->Branch("ntracks",         &n_tracks_);
    tree->Branch("track_eta",         &track_eta_);
    tree->Branch("track_phi",         &track_phi_);
    tree->Branch("track_pt",         &track_pt_);
    tree->Branch("track_energy",     &track_energy_);
    tree->Branch("track_charge",     &track_charge_);
    tree->Branch("track_EBpos_x",     &track_EBpos_x_);
    tree->Branch("track_EBpos_y",     &track_EBpos_y_);
    tree->Branch("track_EBpos_z",     &track_EBpos_z_);
    tree->Branch("track_EB_iEta",     &track_EB_iEta_);
    tree->Branch("track_EB_iPhi",     &track_EB_iPhi_);
    tree->Branch("track_EEpos_x",     &track_EEpos_x_);
    tree->Branch("track_EEpos_y",     &track_EEpos_y_);
    tree->Branch("track_EEpos_z",     &track_EEpos_z_);
    tree->Branch("track_EE_iEta",     &track_EE_iEta_);
    tree->Branch("track_EE_iPhi",     &track_EE_iPhi_);
    tree->Branch("track_ESpos_x",     &track_ESpos_x_);
    tree->Branch("track_ESpos_y",     &track_ESpos_y_);
    tree->Branch("track_ESpos_z",     &track_ESpos_z_);
    tree->Branch("track_ES_iEta",     &track_ES_iEta_);
    tree->Branch("track_ES_iPhi",     &track_ES_iPhi_);
    tree->Branch("track_EB_DetID",     &track_EB_DetID_);
    tree->Branch("track_EE_DetID",     &track_EE_DetID_);
    tree->Branch("track_ES_DetID",     &track_ES_DetID_);
  }
}


///////////////////////////////////
// member functions
//////////////////////////////////
// ------------ method called for each event  ------------
void ggNtuplizer::filltrackparams_ECALEntrance(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
 
  n_tracks_ = 0;
  track_eta_.clear();
  track_phi_.clear();
  track_pt_.clear();
  track_energy_.clear();
  track_charge_.clear();
  track_EBpos_x_.clear();
  track_EBpos_y_.clear();
  track_EBpos_z_.clear();
  track_EB_iEta_.clear();
  track_EB_iPhi_.clear();
  track_EEpos_x_.clear();
  track_EEpos_y_.clear();
  track_EEpos_z_.clear();
  track_EE_iEta_.clear();
  track_EE_iPhi_.clear();
  track_ESpos_x_.clear();
  track_ESpos_y_.clear();
  track_ESpos_z_.clear();
  track_ES_iEta_.clear();
  track_ES_iPhi_.clear();
  track_EB_DetID_.clear();
  track_EE_DetID_.clear();
  track_ES_DetID_.clear();

  //TrackDetectorAssociator::Direction direction = TrackDetectorAssociator::InsideOut;

  Handle<reco::TrackCollection> trackHandle;
  iEvent.getByToken(tracklabel_, trackHandle);
  const reco::TrackCollection *recoTracks = trackHandle.product();

  trkQuality_ = reco::TrackBase::qualityByName("highPurity");

  //Handle<reco::TrackCollection> recoTracks;
  // iEvent.getByLabel(tracklabel_, recoTracks);
 
   //if (!recoTracks.isValid())
   //throw cms::Exception("FatalError") << "No reco tracks were found\n";

 
  for (reco::TrackCollection::const_iterator it_track = recoTracks->begin(); it_track != recoTracks->end(); it_track++)
    {      


      // Accept only good quality tracks. (This is suitable for most physics analyses)
      if (!(it_track->quality(trkQuality_))) continue;


      // skip low Pt tracks
      //if (it_track->pt() < 2) {
      //LogTrace("TrackAssociator") << "Skipped low Pt track (Pt: " << it_track->pt() << ")";
      //continue;
      //}


      TrackDetMatchInfo trk_info;
      //trk_info = trackAssociator_.associate(iEvent, iSetup, *it_track, parameters_, direction);
      trk_info = trackAssociator_.associate(iEvent, iSetup, *it_track, parameters_);
      //trk_info = trackAssociator_.associate(iEvent, iSetup, trackAssociator_.getFreeTrajectoryState(&iSetup.getData(parameters_.bFieldToken), *it_track), parameters_);

      double trackEn = it_track->pt() * cosh(it_track->eta());
      track_pt_.push_back(it_track->pt());
      track_eta_.push_back(it_track->eta());
      track_phi_.push_back(it_track->phi());
      track_energy_.push_back(trackEn);
      track_charge_.push_back(it_track->charge());

      edm::LogVerbatim("TrackAssociator") << "\n-------------------------------------------------------\n Track (pt,eta,phi): " << 
	it_track->pt() << " , " << it_track->eta() << " , " << it_track->phi() ;

      for (std::vector<DetId>::const_iterator trk_ECALid = trk_info.crossedEcalIds.begin(); trk_ECALid != trk_info.crossedEcalIds.end(); ++trk_ECALid){

        if(trk_ECALid->subdetId() == EcalBarrel){
	   EBDetId detId(*trk_ECALid);
           EBDetId trk_ebid = (trk_ECALid->rawId());
	   int EB_ieta = detId.ieta();
	   int EB_iphi = detId.iphi();

	   GlobalPoint EBpoint = trk_info.getPosition(*trk_ECALid);
	   track_EB_iEta_.push_back(EB_ieta);
	   track_EB_iPhi_.push_back(EB_iphi);
	   track_EB_DetID_.push_back(trk_ebid);
	   track_EBpos_x_.push_back(EBpoint.x());
	   track_EBpos_y_.push_back(EBpoint.y());
	   track_EBpos_z_.push_back(EBpoint.z());
	}
        else{
	EEDetId detId(*trk_ECALid);  
        EEDetId trk_eeid = (trk_ECALid->rawId());
	int EE_ieta = detId.ix();
        int EE_iphi = detId.iy();

	GlobalPoint EEpoint = trk_info.getPosition(*trk_ECALid);
        track_EE_iEta_.push_back(EE_ieta);
        track_EE_iPhi_.push_back(EE_iphi);
        track_EE_DetID_.push_back(trk_eeid);
	track_EBpos_x_.push_back(EEpoint.x());
	track_EBpos_y_.push_back(EEpoint.y());
	track_EBpos_z_.push_back(EEpoint.z());
	}

      }
      for (std::vector<DetId>::const_iterator trk_ESid = trk_info.crossedPreshowerIds.begin(); trk_ESid != trk_info.crossedPreshowerIds.end(); ++trk_ESid) {
        GlobalPoint ESpoint = trk_info.getPosition(*trk_ESid);
	ESDetId detId(*trk_ESid);
        ESDetId trk_esid = (trk_ESid->rawId());                                                                                                                                                 

        int ES_ieta = detId.six();
        int ES_iphi = detId.siy();
        track_ES_iEta_.push_back(ES_ieta);
        track_ES_iPhi_.push_back(ES_iphi);
        track_ES_DetID_.push_back(trk_esid); 
	track_ESpos_x_.push_back(ESpoint.x());
        track_ESpos_y_.push_back(ESpoint.y());
        track_ESpos_z_.push_back(ESpoint.z());
        
      }
              
      n_tracks_++; 
    }

}















 





   


  













    
































    


 
  
  
  

  

  
  
  
  
    
    
    
    
    
  
  
  
  
  

  
  
  
  

  
    
     
     
     
     
     
    
                                                                                                                                             
    
   
      


