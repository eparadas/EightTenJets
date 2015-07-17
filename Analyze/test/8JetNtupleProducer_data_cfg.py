import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("EightTenJets")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/161/00000/CACA9422-9C26-E511-AD2E-02163E0117FF.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/162/00000/0A926801-4627-E511-99E6-02163E0144D6.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/163/00000/F05CF208-A026-E511-85F4-02163E011B15.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/164/00000/503874CF-A826-E511-A22B-02163E011A34.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/167/00000/10A72E3C-A826-E511-994E-02163E013926.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/168/00000/20CE9858-DB26-E511-8C25-02163E01386E.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/02E5A1CA-1A28-E511-ADD6-02163E012AA4.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/06D72E6F-0728-E511-91F4-02163E011E24.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/185E18B2-1928-E511-804E-02163E013728.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/34A1A096-1B28-E511-B863-02163E01416E.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/5A49A64A-1B28-E511-9141-02163E014181.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/741C7214-1B28-E511-A528-02163E013406.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/8685520B-0528-E511-A9AE-02163E0142FD.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/AC111760-1B28-E511-8DD9-02163E012031.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/B8DDF6CB-1A28-E511-9A92-02163E0125E8.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/D4175FF4-1A28-E511-B7BB-02163E013576.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/E236B1D5-1928-E511-9D95-02163E0142FD.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/244/00000/EA306540-E928-E511-B726-02163E0143C0.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/251/00000/308B45C4-9527-E511-9262-02163E011C7F.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/251/00000/44A026C4-9527-E511-BF03-02163E0145B2.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/251/00000/BA8A42CF-9527-E511-8418-02163E01472B.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/251/00000/D0D474C9-9527-E511-89E0-02163E0141E9.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/263D331F-AF27-E511-969B-02163E012627.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/52F74C29-AF27-E511-BAA1-02163E01358B.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/583CFB34-AF27-E511-8639-02163E0135AC.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/8A22C61F-AF27-E511-B6BF-02163E012620.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/8C85BC1E-AF27-E511-9E2D-02163E012AA4.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/9604D91E-AF27-E511-8C5A-02163E014166.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/AA9FA822-AF27-E511-BCD7-02163E0133A4.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/B28F4A1F-AF27-E511-8471-02163E0135C9.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/B2B3821D-AF27-E511-A054-02163E01267F.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/CCF39221-AF27-E511-82FB-02163E0142FD.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/D231F61F-AF27-E511-97A9-02163E013432.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/252/00000/F8295A1B-AF27-E511-89C2-02163E014289.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/493/00000/C2A10B1C-D328-E511-8AA7-02163E01463E.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/497/00000/B83D5763-F928-E511-B430-02163E0134FD.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/498/00000/2024B575-EA28-E511-901E-02163E0139A2.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/499/00000/0289B99F-0629-E511-8C9C-02163E0133AD.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/500/00000/36EA9649-3529-E511-A8DE-02163E0135B4.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/521/00000/0C2A2945-6E29-E511-A6F9-02163E013576.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/522/00000/D2CE33AC-6429-E511-88E5-02163E011CD6.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/548/00000/E2E9954F-D929-E511-9E4C-02163E012A2C.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/560/00000/6005646B-E229-E511-8C01-02163E013440.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/561/00000/7E66429B-2C2A-E511-9D07-02163E0128F2.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/561/00000/C86C890B-0C2A-E511-8C6E-02163E013425.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/26A914E6-9C2A-E511-AC57-02163E011CD6.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/48102A76-7D2A-E511-A753-02163E011E24.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/508117F0-9C2A-E511-A71B-02163E014241.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/6C284BEF-9C2A-E511-A00C-02163E013536.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/704086DE-9C2A-E511-83FF-02163E014576.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/720AC5E7-9C2A-E511-9FB2-02163E0129A3.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/8400ADFB-842A-E511-AF09-02163E01420D.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/8A33C3E4-9C2A-E511-95EC-02163E0123C0.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/924A8CCD-802A-E511-AFEE-02163E0125E8.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/B6E35572-822A-E511-B0E4-02163E0136E6.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/C67C9591-8E2A-E511-9D3D-02163E014275.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/CE70BD25-862A-E511-924E-02163E011824.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/562/00000/CEF44D82-882A-E511-AED0-02163E013597.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/604/00000/B8EEEAC4-A62A-E511-A2BE-02163E0138A8.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/612/00000/9015BCFA-AA2A-E511-91E6-02163E011CD6.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/638/00000/1C1DE091-012B-E511-9C18-02163E01457B.root',
'root://xrootd.unl.edu//store/data/Run2015B/JetHT/MINIAOD/PromptReco-v1/000/251/642/00000/14E4B16E-E92A-E511-A223-02163E01366D.root'
    )
)
process.TFileService = cms.Service("TFileService",
      fileName = cms.string("EightTenJets_JetHT_Run2015B.root"),
      closeFileFast = cms.untracked.bool(True)
  )

import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
JSONfile = './json_DCSONLY_Run2015B.txt'
myLumis = LumiList.LumiList(filename = JSONfile).getCMSSWString().split(',')
process.source.lumisToProcess.extend(myLumis)



process.EightTenJets = cms.EDAnalyzer("EightTenJets",
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    jets = cms.InputTag("slimmedJets"),
    fatjets = cms.InputTag("slimmedJetsAK8"),
    pruned = cms.InputTag("prunedGenParticles"),
    genjets = cms.InputTag("slimmedGenJets"),
    bTagValue = cms.double(0),
    isMC = cms.bool(False),
    wtMC = cms.bool(False),
    ptMin = cms.double(50),
    etaMin = cms.double(2.5),
    nJetsToBeKept = cms.int32(4)
    
)


process.p = cms.Path(process.EightTenJets)
