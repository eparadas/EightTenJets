// -*- C++ -*-
//
// Package:    Test/EightTenJets
// Class:      EightTenJets
// 
/**\class EightTenJets EightTenJets.cc Test/EightTenJets/plugins/EightTenJets.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Evangelos Paradas evangelos.paradas@cern.ch
//         Created:  Mon, 06 Jul 2015 09:33:03 GMT
//
//


// system include files
#include <iostream>
#include <vector>
#include <memory>
#include "TTree.h"
#include "TString.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
//
// class declaration
//

class EightTenJets : public edm::EDAnalyzer {
   public:
      explicit EightTenJets(const edm::ParameterSet&);
      ~EightTenJets();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      void Init();
      void SphericityAplanarity(float& sphericity, float& aplanarity, std::vector<float> px, std::vector<float> py, std::vector<float> pz, int nJets);
      
      
    //  edm::InputTag  _trigResultsLabel;
      edm::EDGetTokenT<reco::VertexCollection> _vtxToken;
      edm::EDGetTokenT<pat::JetCollection> _jetToken;
      edm::EDGetTokenT<pat::JetCollection> _fatjetToken;
      edm::EDGetTokenT<edm::View<reco::GenParticle> > _prunedGenToken;
      edm::EDGetTokenT <reco::GenJetCollection> _genJetsToken;
      edm::EDGetTokenT<edm::TriggerResults> _triggerBits;
      bool _isMC, _wtMC;
      float _bTagValue, _ptMin, _etaMin;
      int _nJetsToBeKept;
      
      TTree* _tree;
      
      //Tree variables
		TString _trig_pass;
		int _evtNo, _runNo, _lumiNo;
		float _weight;
		//Jets
			std::vector<float> _et, _pt, _eta, _phi, _px, _py, _pz, _mass, _energy, _beta, _nhf, _phf, _chf, _muf, _elf, _jec, _jecUnc, _bTag, _puMva;
			float _sphericity, _aplanarity, _ht;
			int  _nJet, _nJetBdisc, _nJetAll;
		//GenJets
			std::vector<float> _genPt, _genEta, _genPhi, _genPx, _genPy, _genPz, _genMass, _genEnergy;
			float _genSphericity, _genAplanarity, _genHt;
			int _genNJet;
		//GenParticles
			std::vector<float> _partonPt, _partonEta, _partonPhi, _partonPx, _partonPy, _partonPz, _partonMass, _partonEnergy;
			float _partonSphericity, _partonAplanarity, _partonHt;
			int _partonNJet;
			
		//FatJets
			std::vector<float> _fatPt, _fatEta, _fatPhi, _fatPx, _fatPy, _fatPz, _fatMass, _fatSoftDroppedMass, _fatPrunedMass, _fatTrimmedMass, _fatEnergy, _fatBeta, _fatNhf, _fatPhf, _fatChf, _fatMuf, _fatElf, _fatJec, _fatJecUnc, _fatBTag, _fatPuMva;
			float _fatSphericity, _fatAplanarity, _fatHt;
			int  _fatNJet;
      
      
      
};
