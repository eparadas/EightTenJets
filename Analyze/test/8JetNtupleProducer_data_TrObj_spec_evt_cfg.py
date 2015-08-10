import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("EightTenJets")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/AC111760-1B28-E511-8DD9-02163E012031.root'
    ),
eventsToProcess = cms.untracked.VEventRange('251244:210262254-251244:210262254')
#eventsToProcess = cms.untracked.VEventRange('251252:230757268-251252:230757268')
#eventsToProcess = cms.untracked.VEventRange('251562:94468100-251562:94468100')
)
process.TFileService = cms.Service("TFileService",
      fileName = cms.string("EightTenJets_JetHT_TrObj_Run2015B_spec_evt.root"),
      closeFileFast = cms.untracked.bool(True)
  )



process.EightTenJets = cms.EDAnalyzer("EightTenJetsTrObj",
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    jets = cms.InputTag("slimmedJets"),
    fatjets = cms.InputTag("slimmedJetsAK8"),
    pruned = cms.InputTag("prunedGenParticles"),
    genjets = cms.InputTag("slimmedGenJets"),
    bits = cms.InputTag("TriggerResults","","HLT"),
    prescales = cms.InputTag("patTrigger"),
    objects = cms.InputTag("selectedPatTrigger"),
    bTagValue = cms.double(0),
    isMC = cms.bool(False),
    wtMC = cms.bool(False),
    ptMin = cms.double(50),
    etaMin = cms.double(2.5),
    nJetsToBeKept = cms.int32(4)
    
)


process.p = cms.Path(process.EightTenJets)
