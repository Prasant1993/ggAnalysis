#include "../interface/ggNtuplizer.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/ESGetToken.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/CaloRecHit/interface/CaloRecHit.h"
#include "DataFormats/RecoCandidate/interface/CaloRecHitCandidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
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


using namespace std;
using namespace edm;

Int_t n_tracks_v1_;
std::vector<float> track_eta_v1_;
std::vector<float> track_phi_v1_;
std::vector<float> track_pt_v1_;
std::vector<float> track_energy_v1_;
std::vector<int> track_charge_v1_;
std::vector<int> track_success_v1_;
std::vector<float> track_pos_x_v1_;
std::vector<float> track_pos_y_v1_;
std::vector<float> track_pos_z_v1_;
std::vector<float> magnetfield_x_v1_;
std::vector<float> magnetfield_y_v1_;
std::vector<float> magnetfield_z_v1_;

void ggNtuplizer::branchestrackparams_basicparticle_ECALEntrance(TTree* tree) {
  
  if(dumptrackparamsinfo_){
    tree->Branch("ntracks_propagated",         &n_tracks_v1_);
    tree->Branch("track_eta_propagated",         &track_eta_v1_);
    tree->Branch("track_phi_propagated",         &track_phi_v1_);
    tree->Branch("track_pt_propagated",         &track_pt_v1_);
    tree->Branch("track_energy_propagated",     &track_energy_v1_);
    tree->Branch("track_charge_propagated",     &track_charge_v1_);
    tree->Branch("track_pos_x_propagated",     &track_pos_x_v1_);
    tree->Branch("track_pos_y_propagated",     &track_pos_y_v1_);
    tree->Branch("track_pos_z_propagated",     &track_pos_z_v1_);
    tree->Branch("track_getsuccess_propagated",     &track_success_v1_);
    tree->Branch("magnetfield_x",     &magnetfield_x_v1_);
    tree->Branch("magnetfield_y",     &magnetfield_y_v1_);
    tree->Branch("magnetfield_z",     &magnetfield_z_v1_);
  }
}

///////////////////////////////////
// member functions
//////////////////////////////////
// ------------ method called for each event  ------------
void ggNtuplizer::filltrackparams_basicparticle_ECALEntrance(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  //bool debugRH = true;
  // bool debugRH = false;

  n_tracks_v1_ = 0;
  track_eta_v1_.clear();
  track_phi_v1_.clear();
  track_pt_v1_.clear();
  track_energy_v1_.clear();
  track_charge_v1_.clear();
  track_pos_x_v1_.clear();
  track_pos_y_v1_.clear();
  track_pos_z_v1_.clear();
  track_success_v1_.clear();
  magnetfield_x_v1_.clear();
  magnetfield_y_v1_.clear();
  magnetfield_z_v1_.clear();
  
  // https://github.com/cms-sw/cmssw/blob/master/RecoParticleFlow/PFTracking/src/PFTrackTransformer.cc
  //BaseParticlePropagator theParticle = BaseParticlePropagator(
  //                    RawParticle(XYZTLorentzVector(track.px(), track.py(), track.pz(), pfenergy),
  //				    XYZTLorentzVector(track.vertex().x(), track.vertex().y(), track.vertex().z(), 0.),
  //				    track.charge()),
  //			0.,
  //			0.,
  //			B_.z());

  // https://github.com/cms-sw/cmssw/blob/master/RecoTauTag/RecoTau/plugins/PFRecoTauChargedHadronFromGenericTrackPlugin.cc
  // https://github.com/sameasy/HGCALprod/blob/main/RecoNtuples/HGCalAnalysis/plugins/HGCalAnalysis.cc

 
  Handle<reco::TrackCollection> trackHandle;
  iEvent.getByToken(tracklabel_, trackHandle);
  const reco::TrackCollection *reco_Tracks = trackHandle.product();
 
 
  for (reco::TrackCollection::const_iterator itr_track = reco_Tracks->begin(); itr_track != reco_Tracks->end();++itr_track)
    {      

      double trackEn = itr_track->pt() * cosh(itr_track->eta());

      // Propagate electron track to ECAL surface
      //double mass2 = 0.000511 * 0.000511;
      //float p2 = pow(gsf->p(), 2);
      //float energy = sqrt(mass2 + p2);

      math::XYZPointF ecal_pos;
      math::XYZTLorentzVector ecal_Proptrack_momentum;
      //GlobalPoint const& ecal_pos,

      math::XYZVector magneticFieldStrength_;
      magneticFieldStrength_ = iSetup.getData(tok_magField_).inTesla(GlobalPoint(0., 0., 0.));

      math::XYZTLorentzVector trackP4(itr_track->px(), itr_track->py(), itr_track->pz(), trackEn);
      //math::XYZTLorentzVector trackpos(getTrackPos(it_track));
      math::XYZTLorentzVector trackpos(itr_track->vx(), itr_track->vy(), itr_track->vz(), 0.); 
      //RawParticle RP(trackP4, trackpos);
      //RP.setCharge(it_track->charge());
      BaseParticlePropagator trackPropagator(RawParticle(trackP4, trackpos, itr_track->charge()), 0., 0., magneticFieldStrength_.z());

      /*BaseParticlePropagator trackPropagator(
					     RawParticle(XYZTLorentzVector(it_track->px(), it_track->py(), it_track->pz(), trackEn),
					     XYZTLorentzVector(it_track->vx(), it_track->vy(), it_track->vz(), 0.),
							 it_track->charge()),
					     0., 
					     0., 
					     magneticFieldStrength_.z());*/

      
      trackPropagator.propagateToEcalEntrance(false);
      //bool reach_ECAL = trackpropagator.getSuccess();  // 0 does not reach ECAL, 1 yes barrel, 2 yes endcaps
      // ECAL entry point for track

      if (trackPropagator.getSuccess() != 0) {
	////////////////////////////////////////////

	ecal_pos = math::XYZPointF(trackPropagator.particle().vertex());
	ecal_Proptrack_momentum = math::XYZTLorentzVector(trackPropagator.particle().px(),trackPropagator.particle().py(),trackPropagator.particle().pz(),trackPropagator.particle().E());
        //ecal_pos = trackPropagator.particle().vertex().Vect());
	//GlobalPoint ecal_pos(trackPropagator.particle().x(), trackPropagator.particle().y(), trackPropagator.particle().z());
	track_pt_v1_.push_back(ecal_Proptrack_momentum.pt());
	track_eta_v1_.push_back(ecal_pos.eta());
	track_phi_v1_.push_back(ecal_pos.phi());
	track_energy_v1_.push_back(ecal_Proptrack_momentum.E());
	track_charge_v1_.push_back(trackPropagator.particle().charge());
        track_pos_x_v1_.push_back(ecal_pos.x());
        track_pos_y_v1_.push_back(ecal_pos.y());
        track_pos_z_v1_.push_back(ecal_pos.z());
        track_success_v1_.push_back(trackPropagator.getSuccess());
        magnetfield_x_v1_.push_back(magneticFieldStrength_.x());
        magnetfield_y_v1_.push_back(magneticFieldStrength_.y());
        magnetfield_z_v1_.push_back(magneticFieldStrength_.z());}
        n_tracks_v1_++;
    }

}  















 





   


  













    
































    


 
  
  
  

  

  
  
  
  
    
    
    
    
    
  
  
  
  
  

  
  
  
  

  
    
     
     
     
     
     
    
                                                                                                                                             
    
   
      


