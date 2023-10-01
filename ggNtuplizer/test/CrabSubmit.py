# https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial
import sys
import CRABClient
from CRABClient.UserUtilities import config

config = config()

submitVersion = "EgammaID_ntuples_RunIII_v5_added_trkiso_FileBased"

mainOutputDir = '/store/group/phys_egamma/prrout/Egamma_Photon_Identification/RunIII/ggNtuples/%s' % submitVersion

config.General.transferLogs = False

config.JobType.pluginName  = 'Analysis'

# Name of the CMSSW configuration file
config.JobType.psetName  = '/afs/cern.ch/work/p/prrout/public/Egamma_RunIII_Ntuplizer_CMKuo/CMSSW_12_2_1/src/ggAnalysis/ggNtuplizer/test/EgammaID_RunIII_ConfFile_cfg.py'

config.JobType.sendExternalFolder = True
config.JobType.allowUndistributedCMSSW = True

config.Data.allowNonValidInputDataset = True

config.Data.inputDBS = 'global'
config.Data.publication = False

#config.Data.publishDataName = 
config.Site.storageSite = 'T2_CH_CERN'
config.General.workArea = 'crab_%s' % submitVersion



##### now submit DATA
config.Data.outLFNDirBase = '%s/%s/' % (mainOutputDir,'data5_added_trkiso')
config.Data.splitting     = 'FileBased' # on MC
#config.Data.splitting     = 'LumiBased' # on data 
#config.Data.splitting     = 'EventBased' # on PrivateMC
config.Data.totalUnits      = -1
#config.Data.lumiMask      = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt' #UL2018  
config.Data.unitsPerJob   = 40
#config.Data.unitsPerJob   = 200

### For different DataSets

config.General.requestName = 'job_GJet_Pt-40toInf_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8_Run3Winter22MiniAoD_2022'
config.Data.inputDataset   = '/GJet_Pt-40toInf_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/Run3Winter22MiniAOD-FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/MINIAODSIM'
    
    

    
    
    

    
    






