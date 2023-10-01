import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run3_cff import Run3
process = cms.Process("ggNtuplizer",Run3)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.load('Configuration.Geometry.GeometryIdeal_cff')
process.load('Configuration.Geometry.GeometryRecoDB_cff')
#process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")

from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '122X_mcRun3_2021_realistic_v9', '')     # 2022 Winter22MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '124X_mcRun3_2022_realistic_v5', '')     # 2022 Winter22MC Relval
#process.GlobalTag = GlobalTag(process.GlobalTag, '124X_mcRun3_2022_realistic_postEE_v1', '')     # 2022 Summer22MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '126X_mcRun3_2023_forPU65_v1', '')     # 2023 Winter23MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '124X_mcRun3_2022_realistic_postEE_v1', '')     # 124X PostEE DoubleElectron
process.GlobalTag = GlobalTag(process.GlobalTag, '126X_mcRun3_2022_realistic_postEE_v1', '')     # 2022 Summer22MC
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2022_realistic', '')


#process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mcRun3_2024_realistic_v4', '')     # 2024 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mcRun3_2023_realistic_v3', '')     # 2023 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mcRun3_2021_realistic_v3', '')     # 2021 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v15', '')     # 2018 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Sep2018Rereco_v1', '')     # 2018 data
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v6', '')     # 2017 data 


# TrackAssociator
## add TrackDetectorAssociator lookup maps to the EventSetup
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
from TrackingTools.TrackAssociator.default_cfi import *

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
#            'file:/afs/cern.ch/cms/Tutorials/TWIKI_DATA/TTJets_8TeV_53X.root'
#                                    '/store/relval/CMSSW_12_4_0/RelValQCD_FlatPt_15_3000HS_14/MINIAODSIM/124X_mcRun3_2022_realistic_v5-v1/2580000/04e8ae77-4dae-4d10-a159-3e687adbb835.root',
#                                    '/store/relval/CMSSW_12_4_0/RelValQCD_FlatPt_15_3000HS_14/MINIAODSIM/124X_mcRun3_2022_realistic_v5-v1/2580000/5e10a082-d7af-4262-85e8-e746cbfb4447.root',
#                                    '/store/relval/CMSSW_12_4_0/RelValQCD_FlatPt_15_3000HS_14/MINIAODSIM/124X_mcRun3_2022_realistic_v5-v1/2580000/8acbf6d6-b6b3-409d-a83d-7ed2d36e02dc.root',
#                                    '/store/relval/CMSSW_12_4_0/RelValQCD_FlatPt_15_3000HS_14/MINIAODSIM/124X_mcRun3_2022_realistic_v5-v1/2580000/a497817b-ac20-47eb-b84c-f4fd373734a2.root',
#                                    '/store/relval/CMSSW_12_4_0/RelValQCD_FlatPt_15_3000HS_14/MINIAODSIM/124X_mcRun3_2022_realistic_v5-v1/2580000/c70b1090-fa34-423f-9375-1bc059c246dc.root',
#                                    '/store/relval/CMSSW_12_4_0/RelValQCD_FlatPt_15_3000HS_14/MINIAODSIM/124X_mcRun3_2022_realistic_v5-v1/2580000/d99a4778-c5dc-4274-9fce-7ef2e22e985b.root',
#                                    '/store/relval/CMSSW_12_4_0/RelValQCD_FlatPt_15_3000HS_14/MINIAODSIM/124X_mcRun3_2022_realistic_v5-v1/2580000/eb6ca885-ffd8-40a5-b737-6d0ce2a9a58c.root'
                                    #'/store/mc/Run3Summer22EEMiniAODv3/DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/MINIAODSIM/forPOG_124X_mcRun3_2022_realistic_postEE_v1-v3/2810000/014eb5f9-88c8-4620-a422-28a3fe114f1c.root'
                                   
                                    #'/store/mc/Run3Winter23MiniAOD/DYTo2L_MLL-50_TuneCP5_13p6TeV_pythia8/MINIAODSIM/RnD_126X_mcRun3_2023_forPU65_v1-v2/2540000/173d48ef-56c6-45eb-876a-76ccb2e10ca2.root',
                                    #'/store/mc/Run3Winter23MiniAOD/DYTo2L_MLL-50_TuneCP5_13p6TeV_pythia8/MINIAODSIM/RnD_126X_mcRun3_2023_forPU65_v1-v2/2540000/2e50a58f-8980-41e8-900a-58ab4db4ec8c.root'
                                    #'/store/mc/Run3Summer22EEMiniAODv3/DoubleElectron_FlatPT-1to500_13p6TeV/MINIAODSIM/FlatPU0to70_124X_mcRun3_2022_realistic_postEE_v1-v2/2810000/0356e051-963b-4057-b861-2b35e9fc4c30.root'
                                    #'/store/mc/Run3Winter22DR/GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/AODSIM/FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/2430000/00acca83-e889-4d35-8339-0a0ba956e74e.root'
                                    #'/store/mc/Run3Winter22DR/GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/AODSIM/FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/2430000/023a9365-aa97-4a10-8a5a-178eaedd94d4.root'
                                    '/store/mc/Run3Summer22EEDRPremix/GJet_PT-20_DoubleEMEnriched_MGG-40to80_TuneCP5_13p6TeV_pythia8/AODSIM/124X_mcRun3_2022_realistic_postEE_v1-v2/2550000/01e16df8-432d-4f97-b7c7-9da80e38e137.root'
                                    #'/store/mc/Run3Winter22MiniAOD/GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/MINIAODSIM/FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/2430000/019c9ef2-86db-4258-a076-bdb5169dc3d0.root',
                                    #'/store/mc/Run3Winter22MiniAOD/GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/MINIAODSIM/FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/2430000/0a80915b-ce51-4d0e-ae0d-a170a6736a19.root',
                                    #'/store/mc/Run3Winter22MiniAOD/GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/MINIAODSIM/FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/2430000/1020066d-ab70-4718-8535-efbdfd3356cd.root',
                                    #'/store/mc/Run3Winter22MiniAOD/GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/MINIAODSIM/FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/2430000/11fa80b0-204f-49ad-8682-5bf232b9f927.root',
                                    #'/store/mc/Run3Winter22MiniAOD/GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/MINIAODSIM/FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/2430000/1711acf7-208f-4d92-8e0b-2c38ed779bf7.root'
                                    #'/store/mc/Run3Summer19MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v2/130000/00DF0005-F507-2C4B-BF8B-C46342D7194E.root' #Run3 MINIAOD 
#                                    '/store/mc/Run3Summer19DRPremix/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/AODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v2/130000/9CAB93A4-1C7A-9F48-A707-6ED2FF2AAC6C.root' #Run3 AOD
#                                    '/store/mc/RunIISummer19UL17RECO/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/AODSIM/106X_mc2017_realistic_v6-v2/70000/FFF299F2-182B-B742-978A-A1E27778EFB0.root'  #Run2 UL17 AOD
#                                    '/store/mc/RunIISummer19UL18RECO/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1-v1/70001/2A3DF112-2092-AC4D-82E6-1CFBEC62B830.root'  #Run2 UL18 AOD DYJetsToLL
#                                    '/store/mc/RunIISummer19UL16RECOAPV/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/106X_mcRun2_asymptotic_preVFP_v8-v1/270002/FEBBB375-C5E8-7446-AAFB-7BC9225DECB5.root' ##Run2 UL16 AOD DYJetsToLL
                                )
                            )

process.TFileService = cms.Service("TFileService", fileName = cms.string('ggntuplizer_ECAl_rechits_trackpropagationtoECAl_params.root'))

process.ggNtuplizer = cms.EDAnalyzer('ggNtuplizer',
                                      TrackAssociatorParameterBlock,
                                      doGenParticles       = cms.bool(True),
                                      runOnParticleGun     = cms.bool(False),
                                      runOnSherpa          = cms.bool(False),
                                      dumpPDFSystWeight    = cms.bool(False),
                                      dumpGenScaleSystWeights = cms.bool(False),
                                      dumpCrystalinfo      = cms.bool(True), 
                                      dumptrackparamsinfo  = cms.bool(True), 

                                      VtxLabel             = cms.InputTag("offlinePrimaryVertices"), # from AoD
#                                      VtxBSLabel           = cms.InputTag("offlinePrimaryVerticesWithBS"),
                                      rhoLabel             = cms.InputTag("fixedGridRhoFastjetAll"),
                                      rhoCentralLabel      = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
                                      triggerEvent         = cms.InputTag("slimmedPatTrigger", "", ""),
                                      triggerResults       = cms.InputTag("TriggerResults", "", "HLT"),
                                      #patTriggerResults    = cms.InputTag("TriggerResults", "", "PAT"),
                                      patTriggerResults    = cms.InputTag("TriggerResults", "", "RECO"),

                                      genParticleSrc       = cms.InputTag("genParticles"), # from AOD 
                                      generatorLabel       = cms.InputTag("generator"),
                                      LHEEventLabel        = cms.InputTag("externalLHEProducer"),
                                      pileupCollection     = cms.InputTag("addPileupInfo"), # from AOD
                                      newParticles         = cms.vint32(1000006, 1000021, 1000022, 1000024, 1000025, 1000039, 3000001, 3000002, 35),

                                      recoElectronSrc = cms.InputTag('gedGsfElectrons'), ## for AOD                                         
                                      recoPhotonSrc             = cms.InputTag("gedPhotons"), ## for AoD                                      
                                      TrackLabel                = cms.InputTag("generalTracks"),                                              
                                      ebReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"), ## for AoD                           
                                      eeReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"), ## for AoD                            
                                      esReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsES"), ## for AoD 
                                      barrelClusterCollection = cms.InputTag("reducedEgamma","reducedEBEEClusters"),
                                      endcapClusterCollection = cms.InputTag("reducedEgamma","reducedEBEEClusters"),
                                      hbheReducedRecHitCollection = cms.InputTag("reducedHcalRecHits", "hbhereco"), # from AOD
                                  )

process.p = cms.Path(process.ggNtuplizer)
