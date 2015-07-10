#include "EightTenJets.h"

#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TVectorD.h"


EightTenJets::EightTenJets(const edm::ParameterSet& iConfig) :

	_trigResultsLabel("TriggerResults", "", "HLT"),
	_vtxToken(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
	_jetToken(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets"))),
	_fatjetToken(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("fatjets"))),
	_prunedGenToken(consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
	_genJetsToken(consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("genjets"))),
	_isMC( iConfig.getParameter<bool>("isMC") ),
	_wtMC( iConfig.getParameter<bool>("wtMC") ),
	_bTagValue( iConfig.getParameter<double>("bTagValue") ),
	_ptMin( iConfig.getParameter<double>("ptMin") ),
	_etaMin( iConfig.getParameter<double>("etaMin") ),
	_nJetsToBeKept( iConfig.getParameter<int>("nJetsToBeKept") )
{
	edm::Service<TFileService> fs ;
	_tree = fs->make <TTree>("EightTenJets","13TeV");
	_tree->Branch("evtNo",&_evtNo,"evtNo/I");
	_tree->Branch("runNo",&_runNo,"runNo/I");
	_tree->Branch("lumiNo",&_lumiNo,"lumiNo/I");
	if ( _isMC && _wtMC )
		_tree->Branch("weight", &_weight, "weight/F");
		
	//Jets
	_tree->Branch("pt","vector<float>", &_pt);
	_tree->Branch("eta","vector<float>", &_eta);
	_tree->Branch("phi","vector<float>", &_phi);
	_tree->Branch("px","vector<float>", &_px);
	_tree->Branch("py","vector<float>", &_py);
	_tree->Branch("pz","vector<float>", &_pz);
	_tree->Branch("mass","vector<float>", &_mass);
	_tree->Branch("energy","vector<float>", &_energy);
	_tree->Branch("chf","vector<float>", &_chf);
	_tree->Branch("nhf","vector<float>", &_nhf);
	_tree->Branch("phf","vector<float>", &_phf);
	_tree->Branch("muf","vector<float>", &_muf);
	_tree->Branch("elf","vector<float>", &_elf);
	_tree->Branch("jec","vector<float>", &_jec);
	_tree->Branch("jecUnc","vector<float>",&_jecUnc);
	_tree->Branch("bTag","vector<float>", &_bTag);
	_tree->Branch("puMva","vector<float>", &_puMva);
	_tree->Branch("sphericity", &_sphericity, "sphericity/F");
	_tree->Branch("aplanarity", &_aplanarity, "aplanarity/F");
	_tree->Branch("ht", &_ht, "ht/F");
	_tree->Branch("nJet",&_nJet,"nJet/I");
	_tree->Branch("nJetBdisc", &_nJetBdisc, "nJetBdisc/I");
	_tree->Branch("nJetAll",&_nJetAll,"nJetAll/F");
	
	//fatJets
	_tree->Branch("fatPt","vector<float>", &_fatPt);
	_tree->Branch("fatEta","vector<float>", &_fatEta);
	_tree->Branch("fatPhi","vector<float>", &_fatPhi);
	_tree->Branch("fatPx","vector<float>", &_fatPx);
	_tree->Branch("fatPy","vector<float>", &_fatPy);
	_tree->Branch("fatPz","vector<float>", &_fatPz);
	_tree->Branch("fatMass","vector<float>", &_fatMass);
	_tree->Branch("fatPrunedMass", "vector<float>", &_fatPrunedMass);
	_tree->Branch("fatSoftDroppedMass", "vector<float>", &_fatSoftDroppedMass);
	_tree->Branch("fatTrimmedMass", "vector<float>", &_fatTrimmedMass);
	_tree->Branch("fatEnergy","vector<float>", &_fatEnergy);
	_tree->Branch("fatChf","vector<float>", &_fatChf);
	_tree->Branch("fatNhf","vector<float>", &_fatNhf);
	_tree->Branch("fatPhf","vector<float>", &_fatPhf);
	_tree->Branch("fatMuf","vector<float>", &_fatMuf);
	_tree->Branch("fatElf","vector<float>", &_fatElf);
	_tree->Branch("fatJec","vector<float>", &_fatJec);
	_tree->Branch("fatJecUnc","vector<float>",&_fatJecUnc);
	_tree->Branch("fatBTag","vector<float>", &_fatBTag);
	_tree->Branch("fatPuMva","vector<float>", &_fatPuMva);
	_tree->Branch("fatSphericity", &_fatSphericity, "fatSphericity/F");
	_tree->Branch("fatAplanarity", &_fatAplanarity, "fatAplanarity/F");
	_tree->Branch("fatHt", &_fatHt, "fatHt/F");
	_tree->Branch("fatNJet",&_fatNJet,"fatNJet/I");
	
	
	//GenJets & genParticles
	if ( _isMC )
	{
		_tree->Branch("genPt","vector<float>", &_genPt);
		_tree->Branch("genEta","vector<float>", &_genEta);
		_tree->Branch("genPhi","vector<float>", &_genPhi);
		_tree->Branch("genPx","vector<float>", &_genPx);
		_tree->Branch("genPy","vector<float>", &_genPy);
		_tree->Branch("genPz","vector<float>", &_genPz);
		_tree->Branch("genMass","vector<float>", &_genMass);
		_tree->Branch("genEnergy","vector<float>", &_genEnergy);
		_tree->Branch("genSphericity", &_genSphericity, "genSphericity/F");
		_tree->Branch("genAplanarity", &_genAplanarity, "genAplanarity/F");
		_tree->Branch("genHt", &_genHt, "genHt/F");
		_tree->Branch("genNJet",&_genNJet,"genNJet/I");
				
		_tree->Branch("partonPt","vector<float>", &_partonPt);
		_tree->Branch("partonEta","vector<float>", &_partonEta);
		_tree->Branch("partonPhi","vector<float>", &_partonPhi);
		_tree->Branch("partonPx","vector<float>", &_partonPx);
		_tree->Branch("partonPy","vector<float>", &_partonPy);
		_tree->Branch("partonPz","vector<float>", &_partonPz);
		_tree->Branch("partonMass","vector<float>", &_partonMass);
		_tree->Branch("partonEnergy","vector<float>", &_partonEnergy);
		_tree->Branch("partonSphericity", &_partonSphericity, "partonSphericity/F");
		_tree->Branch("partonAplanarity", &_partonAplanarity, "partonAplanarity/F");
		_tree->Branch("partonHt", &_partonHt, "partonHt/F");
		_tree->Branch("partonNJet",&_partonNJet,"partonNJet/I");
	}// _isMC
	
}
void EightTenJets::Init()
{
	_evtNo = -999;
	_runNo = -999;
	_lumiNo = -999;
	if ( _isMC && _wtMC )
		_weight = -999;
		
	_pt.clear();
	_eta.clear();
	_phi.clear();
	_px.clear();
	_py.clear();
	_pz.clear();
	_mass.clear();
	_energy.clear();
	_chf.clear();
	_nhf.clear();
	_phf.clear();
	_muf.clear();
	_elf.clear();
	_jecUnc.clear();
	_bTag.clear();
	_puMva.clear();
	_sphericity = -999;
	_aplanarity = -999;
	_ht = -999;
	_nJet = -999;
	_nJetBdisc = -999;
	_nJetAll = -999;
	
	_fatPt.clear();
	_fatEta.clear();
	_fatPhi.clear();
	_fatPx.clear();
	_fatPy.clear();
	_fatPz.clear();
	_fatMass.clear();
	_fatSoftDroppedMass.clear();
	_fatPrunedMass.clear();
	_fatTrimmedMass.clear();
	_fatEnergy.clear();
	_fatChf.clear();
	_fatNhf.clear();
	_fatPhf.clear();
	_fatMuf.clear();
	_fatElf.clear();
	_fatJecUnc.clear();
	_fatBTag.clear();
	_fatPuMva.clear();
	_fatSphericity = -999;
	_fatAplanarity = -999;
	_fatHt = -999;
	_fatNJet = -999;

	_genPt.clear();
	_genEta.clear();
	_genPhi.clear();
	_genPx.clear();
	_genPy.clear();
	_genPz.clear();
	_genMass.clear();
	_genEnergy.clear();
	_genSphericity = -999;
	_genAplanarity = -999;
	_genHt = -999;
	_genNJet = -999;
	
	_partonPt.clear();
	_partonEta.clear();
	_partonPhi.clear();
	_partonPx.clear();
	_partonPy.clear();
	_partonPz.clear();
	_partonMass.clear();
	_partonEnergy.clear();
	_partonSphericity = -999;
	_partonAplanarity = -999;
	_partonHt = -999;
	_partonNJet = -999;
}

EightTenJets::~EightTenJets()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
EightTenJets::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	Init();
  // using namespace edm;

	_runNo   = iEvent.id().run();
	_lumiNo  = iEvent.luminosityBlock();
	_evtNo = iEvent.id().event();

	edm::Handle<reco::VertexCollection> vertices;
    iEvent.getByToken(_vtxToken, vertices);
    if (vertices->empty()) return; // skip the event if no PV found
    const reco::Vertex &PV = vertices->front();

	edm::Handle<edm::TriggerResults> H_trig;
	iEvent.getByLabel(_trigResultsLabel, H_trig);
	
	_trig_pass = "";
	const edm::TriggerNames & triggerNames = iEvent.triggerNames(*H_trig);
	for (int iHLT = 0 ; iHLT<static_cast<int>(H_trig->size()); ++iHLT) 
	{
		if (H_trig->accept (iHLT)) 
		{
			TString path = TString(triggerNames.triggerName(iHLT));
			_trig_pass += "_%_"+path ;
		}
	}

	edm::Handle<pat::JetCollection> jets;
    iEvent.getByToken(_jetToken, jets);
    _ht = 0;
    _nJet = 0;
    _nJetBdisc = 0;
    _nJetAll = 0;
    
    for (const pat::Jet &j : *jets) 
    {
        
   //   printf("jet  with pt %5.1f (raw pt %5.1f), eta %+4.2f, btag CSV %.3f, CISV %.3f, pileup mva disc %+.2f\n",
         //   j.pt(), j.pt()*j.jecFactor("Uncorrected"), j.eta(), std::max(0.f,j.bDiscriminator("combinedSecondaryVertexBJetTags")), std::max(0.f,j.bDiscriminator("combinedInclusiveSecondaryVertexBJetTags")), j.userFloat("pileupJetId:fullDiscriminant"));
		float t_chf = j.chargedHadronEnergyFraction();
		float t_nhf = j.neutralHadronEnergyFraction() + j.HFHadronEnergyFraction();
		float t_phf = j.photonEnergy()/(j.jecFactor(0) * j.energy());
		float t_elf = j.electronEnergy()/(j.jecFactor(0) * j.energy());
		float t_muf = j.muonEnergy()/(j.jecFactor(0) * j.energy());
		int t_chm = j.chargedHadronMultiplicity();
        int t_npr = j.chargedMultiplicity() + j.neutralMultiplicity();
		bool id = (t_npr>1 && t_phf<0.99 && t_nhf<0.99 && ((fabs(j.eta())<=2.4 && t_nhf<0.9 && t_phf<0.9 && t_elf<0.99 && t_muf<0.99 && t_chf>0 && t_chm>0) || fabs(j.eta())>2.4));
		if ( id )
			_nJetAll++;
		
		if ( (id) && (j.pt() > _ptMin) && (j.eta() < _etaMin) )
		{
			_pt.push_back(j.pt());
			_ht += j.pt();
			_eta.push_back(j.eta());
			_phi.push_back(j.phi());
			_px.push_back(j.px());
			_py.push_back(j.py());
			_pz.push_back(j.pz());
			_mass.push_back(j.mass());
			_energy.push_back(j.energy());
			_beta.push_back(j.userFloat("beta"));
			_chf.push_back(t_chf);
			_nhf.push_back(t_nhf);
			_phf.push_back(t_phf);
			_muf.push_back(t_muf);
			_elf.push_back(t_elf);
			_jec.push_back( 1./j.jecFactor(0) );
			_jecUnc.push_back(j.userFloat("jecUnc"));
			_bTag.push_back( std::max(0.f,j.bDiscriminator("combinedSecondaryVertexBJetTags")) );
			_puMva.push_back( j.userFloat("pileupJetId:fullDiscriminant") );
			_nJet++;
			if ( std::max(0.f,j.bDiscriminator("combinedSecondaryVertexBJetTags")) > _bTagValue )
				_nJetBdisc++;
			
			
		}//if ( (id) && (j.pt() < _ptMin) && (j.eta() > _etaMin) )
        
    }//jets
	SphericityAplanarity(_sphericity, _aplanarity, _px, _py, _pz, _nJet);
	
	//FatJets
	edm::Handle<pat::JetCollection> fatjets;
    iEvent.getByToken(_fatjetToken, fatjets);
    _fatHt = 0;
    _fatNJet = 0;
    if ( (*fatjets).size() > 0 )
    {
		for (const pat::Jet &j : *fatjets) 
		{
			float t_chf = j.chargedHadronEnergyFraction();
			float t_nhf = j.neutralHadronEnergyFraction() + j.HFHadronEnergyFraction();
			float t_phf = j.photonEnergy()/(j.jecFactor(0) * j.energy());
			float t_elf = j.electronEnergy()/(j.jecFactor(0) * j.energy());
			float t_muf = j.muonEnergy()/(j.jecFactor(0) * j.energy());
			int t_chm = j.chargedHadronMultiplicity();
			int t_npr = j.chargedMultiplicity() + j.neutralMultiplicity();
			
			bool id = (t_npr>1 && t_phf<0.99 && t_nhf<0.99 && ((fabs(j.eta())<=2.4 && t_nhf<0.9 && t_phf<0.9 && t_elf<0.99 && t_muf<0.99 && t_chf>0 && t_chm>0) || fabs(j.eta())>2.4));
			
			if ( id )
			{
				_fatPt.push_back(j.pt());
				_fatHt += j.pt();
				_fatEta.push_back(j.eta());
				_fatPhi.push_back(j.phi());
				_fatPx.push_back(j.px());
				_fatPy.push_back(j.py());
				_fatPz.push_back(j.pz());
				_fatMass.push_back(j.mass());
				_fatSoftDroppedMass.push_back(j.userFloat("ak8PFJetsCHSSoftDropMass"));
				_fatPrunedMass.push_back(j.userFloat("ak8PFJetsCHSPrunedMass"));
				_fatTrimmedMass.push_back(j.userFloat("ak8PFJetsCHSTrimmedMass"));
				_fatEnergy.push_back(j.energy());
				_fatBeta.push_back(j.userFloat("beta"));
				_fatChf.push_back(t_chf);
				_fatNhf.push_back(t_nhf);
				_fatPhf.push_back(t_phf);
				_fatMuf.push_back(t_muf);
				_fatElf.push_back(t_elf);
				_fatJec.push_back( 1./j.jecFactor(0) );
				_fatJecUnc.push_back(j.userFloat("jecUnc"));
				_fatBTag.push_back( std::max(0.f,j.bDiscriminator("combinedSecondaryVertexBJetTags")) );
				_fatPuMva.push_back( j.userFloat("pileupJetId:fullDiscriminant") );     
				_fatNJet++;
			}//id
		}//fatjets
		SphericityAplanarity(_fatSphericity, _fatAplanarity, _fatPx, _fatPy, _fatPz, _fatNJet);
	}//if fatjets.size()
    
    
    if ( _isMC )
    {
		if ( _wtMC )
		{
			edm::Handle<GenEventInfoProduct> genEventInfo;
			iEvent.getByLabel("generator", genEventInfo);
			_weight = genEventInfo->weight();
		}//_wtMC
		
		edm::Handle<edm::View<reco::GenParticle> > pruned;
        iEvent.getByToken(_prunedGenToken,pruned);
        _partonHt = 0;
        _partonNJet = 0;
        for(size_t i=0; i<pruned->size();i++)
        {
			_partonPt.push_back((*pruned)[i].pt());
			_partonHt += (*pruned)[i].pt();
			_partonEta.push_back((*pruned)[i].eta());
			_partonPhi.push_back((*pruned)[i].phi());
			_partonPx.push_back((*pruned)[i].px());
			_partonPy.push_back((*pruned)[i].py());
			_partonPz.push_back((*pruned)[i].pz());
			_partonMass.push_back((*pruned)[i].mass());
			_partonEnergy.push_back((*pruned)[i].energy());
			_partonNJet++;
		}//genParticles
		SphericityAplanarity(_partonSphericity, _partonAplanarity, _partonPx, _partonPy, _partonPz, _partonNJet);
		
		edm::Handle<reco::GenJetCollection> genJets;
		iEvent.getByToken(_genJetsToken, genJets);
		_genHt = 0;
		_genNJet = 0;
		for(reco::GenJetCollection::const_iterator genJet = genJets->begin(); genJet!=genJets->end(); ++genJet )
		{
			_genPt.push_back(genJet->pt());
			_genHt += genJet->pt();
			_genEta.push_back(genJet->eta());
			_genPhi.push_back(genJet->phi());
			_genPx.push_back(genJet->px());
			_genPy.push_back(genJet->py());
			_genPz.push_back(genJet->pz());
			_genMass.push_back(genJet->mass());
			_genEnergy.push_back(genJet->energy());
			_genNJet++;
		}//genJets			
		SphericityAplanarity(_genSphericity, _genAplanarity, _genPx, _genPy, _genPz, _genNJet);
		
			
	}//_isMC
	
	if ( _nJet >= _nJetsToBeKept )
		_tree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
EightTenJets::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EightTenJets::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
EightTenJets::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
EightTenJets::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
EightTenJets::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
EightTenJets::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
EightTenJets::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void EightTenJets::SphericityAplanarity(float& sphericity, float& aplanarity,
										std::vector<float> px, std::vector<float> py, std::vector<float> pz, int nJets)
{
	float sumPxx(0);
	float sumPyy(0);
	float sumPzz(0);
	float sumPxy(0);
	float sumPxz(0);
	float sumPyz(0);
	float sumPP(0);

	for(int jk=0; jk<nJets; jk++)
	{
		sumPxx += pow(px[jk],2);
		sumPyy += pow(py[jk],2);
		sumPzz += pow(pz[jk],2);
		sumPxy += px[jk] * py[jk];
		sumPyz += py[jk] * pz[jk];
		sumPxz += px[jk] * pz[jk];
		sumPP += ( pow(px[jk], 2) + pow(py[jk], 2) + pow(pz[jk], 2) );
	}
	TMatrixDSym s_matrix(3);
	s_matrix(0,0) = sumPxx/sumPP;
	s_matrix(0,1) = sumPxy/sumPP;
	s_matrix(0,2) = sumPxz/sumPP;
	s_matrix(1,0) = sumPxy/sumPP;
	s_matrix(1,1) = sumPyy/sumPP;
	s_matrix(1,2) = sumPyz/sumPP;
	s_matrix(2,0) = sumPxz/sumPP;
	s_matrix(2,1) = sumPyz/sumPP;
	s_matrix(2,2) = sumPzz/sumPP;
	TMatrixDSymEigen TEigen(s_matrix);
	TVectorD eigenValues(TEigen.GetEigenValues());
	sphericity = 1.5*(eigenValues(1)+eigenValues(2));
	aplanarity = 1.5*eigenValues(2);
	
}


//define this as a plug-in
DEFINE_FWK_MODULE(EightTenJets);
