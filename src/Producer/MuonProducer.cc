#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>

MuonProducer::MuonProducer(const double &ptCut, const double &etaCut, const char &workingPointCut):
	ptCut(ptCut),
	etaCut(etaCut),
	workingPointCut(workingPointCut)
	{
		Name = "Reco Muon Producer";
		//std::map<char, std::string> workingPointMap = {
		//	{'l', "loose"},
		//	{'m', "medium"},
		//	{'t', "tight"},
		//	{'a', "all"}
		//};
		//std::cout << "Using " << workingPointMap[workingPointCut] << " Muons." << std::endl;
	}

//I used a T&P method to calculate efficiencies for several L1T pT and quality working points.
//RECO muons were selected with medium quality working point.
//For tag muons I used HLT match (hlt_isomu == true), HLT Iso DeltaR (hlt_isoDeltaR < 0.1), and Iso (iso < 0.1) cuts.
//Both tag and probe muons were matched to L1 muons by using eta and phi at station 2 if it exists and station 1 otherwise.
//I discarded muons with no etaSt2 or etaSt1 value.
//I also required the T&P muons to have pT > L1 pT + 3 GeV.

void MuonProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	product->nMuon = *dataReader->nMuon->Get();
	for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++) {
		const float &muonEtaSt1 = dataReader->muonEtaSt1->At(iMuon);
		const float &muonPhiSt1 = dataReader->muonPhiSt1->At(iMuon);
		const bool &hasMB1 = (fabs(muonEtaSt1) < 5) && (fabs(muonPhiSt1) < M_PI);

		const float &muonEtaSt2 = dataReader->muonEtaSt2->At(iMuon);
		const float &muonPhiSt2 = dataReader->muonPhiSt2->At(iMuon);
		const bool &hasMB2 = (fabs(muonEtaSt2) < 5) && (fabs(muonPhiSt2) < M_PI);

		product->isLooseMuon.push_back(dataReader->muonIsLooseMuon->At(iMuon));
		product->isMediumMuon.push_back(dataReader->muonIsMediumMuon->At(iMuon));
		product->isTightMuon.push_back(dataReader->muonIsTightMuon->At(iMuon));
		product->muonHltIsoMu.push_back(dataReader->muonHlt_isomu->At(iMuon));
		product->muonHltMu.push_back(dataReader->muonHlt_mu->At(iMuon));
		product->muonPassesSingleMuon.push_back(dataReader->muonPassesSingleMuon->At(iMuon));
		product->muonCharge.push_back(dataReader->muonCharge->At(iMuon));
		product->muonE.push_back(dataReader->muonE->At(iMuon));
		product->muonEt.push_back(dataReader->muonEt->At(iMuon));
		product->muonPt.push_back(std::min(dataReader->muonPt->At(iMuon), (float)149.99)); // Keep this for now to be the same as eff_L1T.py
		product->muonEta.push_back(dataReader->muonEta->At(iMuon));
		product->muonPhi.push_back(dataReader->muonPhi->At(iMuon));
		product->muonIso.push_back(dataReader->muonIso->At(iMuon));
		product->muonHltIsoDeltaR.push_back(dataReader->muonHlt_isoDeltaR->At(iMuon));
		product->muonDeltaR.push_back(dataReader->muonHlt_deltaR->At(iMuon));
		product->muonEtaSt1.push_back(muonEtaSt1);
		product->muonPhiSt1.push_back(muonPhiSt1);
		product->muonEtaSt2.push_back(muonEtaSt2);
		product->muonPhiSt2.push_back(muonPhiSt2);
		product->muonMet.push_back(dataReader->muonMet->At(iMuon));
		product->muonMt.push_back(dataReader->muonMt->At(iMuon));

		product->muonIEta.push_back(Utility::CmsEtaToHoIEta(product->muonEta.back()));
		product->muonHasMb1.push_back(hasMB1);
		product->muonHasMb2.push_back(hasMB2);

		//histCollection->histMuonMet->Fill(product->muonMet.back());
		//histCollection->histMuonMt->Fill(product->muonMt.back());

		//histCollection->histIsLooseMuon->Fill(product->isLooseMuon.back());
		//histCollection->histIsMediumMuon->Fill(product->isMediumMuon.back());
		//histCollection->histIsTightMuon->Fill(product->isTightMuon.back());
		//histCollection->histMuonHltIsoMu->Fill(product->muonHltIsoMu.back());
		//histCollection->histMuonHltMu->Fill(product->muonHltMu.back());
		//histCollection->histMuonPassesSingleMuon->Fill(product->muonPassesSingleMuon.back());
		//histCollection->histMuonCharge->Fill(product->muonCharge.back());

		//histCollection->histMuonE->Fill(product->muonE.back());
		//histCollection->histMuonEt->Fill(product->muonEt.back());
		//histCollection->histMuonPt->Fill(product->muonPt.back());
		//histCollection->histMuonPt20->Fill(product->muonPt.back());
		//histCollection->histMuonEta->Fill(product->muonEta.back());
		//histCollection->histMuonPhi->Fill(product->muonPhi.back());
		//histCollection->histMuonIso->Fill(product->muonIso.back());
		//histCollection->histMuonHltIsoDeltaR->Fill(product->muonHltIsoDeltaR.back());
		//histCollection->histMuonDeltaR->Fill(product->muonDeltaR.back());
		//histCollection->histMuonEtaSt1->Fill(product->muonEtaSt1.back());
		//histCollection->histMuonPhiSt1->Fill(product->muonPhiSt1.back());
		//histCollection->histMuonEtaSt2->Fill(product->muonEtaSt2.back());
		//histCollection->histMuonPhiSt2->Fill(product->muonPhiSt2.back());

		//histCollection->histMuonIEta->Fill(product->muonIEta.back());
	}
}

void MuonProducer::EndJob(HoHistogramCollection* histCollection) {}
MuonProducer::~MuonProducer() {}
