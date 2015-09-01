import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("EightTenJets")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
	'file:///mnt/storage/EightJets_13TeV/MINIAOD_94468100_PromptReco.root'
    )
)
process.TFileService = cms.Service("TFileService",
      fileName = cms.string("EightTenJets_JetHT_TrObj_TEST.root"),
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
    nJetsToBeKept = cms.int32(0)
    
)


process.p = cms.Path(process.EightTenJets)
