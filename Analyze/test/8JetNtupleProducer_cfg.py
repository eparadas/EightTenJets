import FWCore.ParameterSet.Config as cms

process = cms.Process("EightTenJets")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://xrootd.unl.edu//store/mc/RunIISpring15DR74/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/Asympt25nsRaw_MCRUN2_74_V9-v3/00000/08547C6F-CD08-E511-81F2-0025905A60AA.root'
    )
)
process.TFileService = cms.Service("TFileService",
      fileName = cms.string("EightTenJets.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.EightTenJets = cms.EDAnalyzer("EightTenJets",
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
#   muons = cms.InputTag("slimmedMuons"),
#   electrons = cms.InputTag("slimmedElectrons"),
#   taus = cms.InputTag("slimmedTaus"),
#   photons = cms.InputTag("slimmedPhotons"),
    jets = cms.InputTag("slimmedJets"),
#   fatjets = cms.InputTag("slimmedJetsAK8"),
#   mets = cms.InputTag("slimmedMETs"),
    pruned = cms.InputTag("prunedGenParticles"),
    genjets = cms.InputTag("slimmedGenJets"),
    bTagValue = cms.double(0),
    isMC = cms.bool(True),
    wtMC = cms.bool(True),
    ptMin = cms.double(50),
    etaMin = cms.double(2.5),
    nJetsToBeKept = cms.int32(0)
    
)


process.p = cms.Path(process.EightTenJets)
