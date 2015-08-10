import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("SKIM")

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
process.o = cms.OutputModule("PoolOutputModule",
	fileName = cms.untracked.string("verySpecialEvent.root")
)
 
process.e = cms.EndPath(process.o)
