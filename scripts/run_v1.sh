
InputFilePath="/eos/cms/store/group/phys_egamma/prrout/Egamma_Photon_Identification/RunIII/ggNtuples/EgammaID_ntuples_RunIII/data/"

InputFileName=Out_GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8_RunIII_EgammaID.root


OutputFile=Out_sig_bkg_GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8_RunIII_EgammaID.root

MaxEvent=6000000
ReportEvery=10000
EvtWeightXS=1.0

echo "Running... ./photonTreeProducer.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $EvtWeightXS"
./photonTreeProducer.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $EvtWeightXS
