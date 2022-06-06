
InputFilePath="/eos/cms/store/group/phys_egamma/prrout/Egamma_Photon_Identification/RunIII/ggNtuples/EgammaID_ntuples_RunIII/data/"

InputFileName=Out_GJet_Pt-40toInf_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8_RunIII_EgammaID.root


OutputFile=Out_sig_bkg_Out_GJet_Pt-40toInf_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8_RunIII_EgammaID.root

MaxEvent=6000000
ReportEvery=10000
EvtWeightXS=0.2906042589335407

echo "Running... ./photonTreeProducer.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $EvtWeightXS"
./photonTreeProducer.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $EvtWeightXS
