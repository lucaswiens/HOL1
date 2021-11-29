#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>

MuonProducer::MuonProducer(const double &ptCut, const double &etaCut, const char &workingPointCut):
	ptCut(ptCut),
	etaCut(etaCut),
	workingPointCut(workingPointCut)
	{
		Name = "Reco Muon Producer";
		std::map<char, std::string> workingPointMap = {
			{'l', "loose"},
			{'m', "medium"},
			{'t', "tight"},
			{'a', "all"}
		};
		std::cout << "Using " << workingPointMap[workingPointCut] << " Muons." << std::endl;
	}

void MuonProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {

	product->nMuon = *dataReader->nMuon->Get();
	for (unsigned short iMuon = 1; iMuon < product->nMuon; iMuon++) {
		//const bool &leadingMuonIsTight = dataReader->muonIsTightMuon->At(0);
		//if (i != 1 && !leadingMuonIsTight) { continue;}

		const float &muonPt = dataReader->muonPt->At(iMuon);
		const float &muonEta = dataReader->muonEta->At(iMuon);
		const float &muonPhi = dataReader->muonPhi->At(iMuon);
		const bool &isLooseMuon = dataReader->muonIsLooseMuon->At(iMuon);
		const bool &isMediumMuon = dataReader->muonIsMediumMuon->At(iMuon);
		const bool &isTightMuon = dataReader->muonIsTightMuon->At(iMuon);

		bool passesWorkingPoint = false;

		if (workingPointCut == 'm') {
			passesWorkingPoint = isMediumMuon;
		} else if (workingPointCut == 't') {
			passesWorkingPoint = isTightMuon;
		} else if (workingPointCut == 'l') {
			passesWorkingPoint = isLooseMuon;
		} else if (workingPointCut == 'a') {
			passesWorkingPoint = true;
		} else {
			std::cerr << "Chosen invalid working point!" << std::endl;
		}

		//if (muonPt < ptCut || fabs(muonEta) > etaCut || !passesWorkingPoint) { continue;}
		if (!passesWorkingPoint) { continue;}
		if (muonPt < ptCut || fabs(muonEta) > etaCut) { continue; }

		product->isLooseMuon.push_back(isLooseMuon);
		product->isMediumMuon.push_back(isMediumMuon);
		product->isTightMuon.push_back(isTightMuon);
		product->muonHltIsoMu.push_back(dataReader->muonHlt_isomu->At(iMuon));
		product->muonHltMu.push_back(dataReader->muonHlt_mu->At(iMuon));
		product->muonPassesSingleMuon.push_back(dataReader->muonPassesSingleMuon->At(iMuon));
		product->muonCharge.push_back(dataReader->muonCharge->At(iMuon));
		product->muonE.push_back(dataReader->muonE->At(iMuon));
		product->muonEt.push_back(dataReader->muonEt->At(iMuon));
		product->muonPt.push_back(muonPt);
		product->muonEta.push_back(muonEta);
		product->muonPhi.push_back(muonPhi);
		product->muonIso.push_back(dataReader->muonIso->At(iMuon));
		product->muonHltIsoDeltaR.push_back(dataReader->muonHlt_isoDeltaR->At(iMuon));
		product->muonDeltaR.push_back(dataReader->muonHlt_deltaR->At(iMuon));
		product->muonEtaSt1.push_back(dataReader->muonEtaSt1->At(iMuon));
		product->muonPhiSt1.push_back(dataReader->muonPhiSt1->At(iMuon));
		product->muonEtaSt2.push_back(dataReader->muonEtaSt2->At(iMuon));
		product->muonPhiSt2.push_back(dataReader->muonPhiSt2->At(iMuon));
		product->muonMet.push_back(dataReader->muonMet->At(iMuon));
		product->muonMt.push_back(dataReader->muonMt->At(iMuon));

		product->muonIEta.push_back(Utility::CmsEtaToHoIEta(product->muonEta.back()));
		product->muonHasMb1.push_back((fabs(product->muonEtaSt1.back()) < 5) && (fabs(product->muonPhiSt1.back()) < M_PI));
		product->muonHasMb2.push_back((fabs(product->muonEtaSt2.back()) < 5) && (fabs(product->muonPhiSt2.back()) < M_PI));

		histCollection->histMuonMet->Fill(product->muonMet.back());
		histCollection->histMuonMt->Fill(product->muonMt.back());

		histCollection->histIsLooseMuon->Fill(product->isLooseMuon.back());
		histCollection->histIsMediumMuon->Fill(product->isMediumMuon.back());
		histCollection->histIsTightMuon->Fill(product->isTightMuon.back());
		histCollection->histMuonHltIsoMu->Fill(product->muonHltIsoMu.back());
		histCollection->histMuonHltMu->Fill(product->muonHltMu.back());
		histCollection->histMuonPassesSingleMuon->Fill(product->muonPassesSingleMuon.back());
		histCollection->histMuonCharge->Fill(product->muonCharge.back());

		histCollection->histMuonE->Fill(product->muonE.back());
		histCollection->histMuonEt->Fill(product->muonEt.back());
		histCollection->histMuonPt->Fill(product->muonPt.back());
		histCollection->histMuonPt20->Fill(product->muonPt.back());
		histCollection->histMuonEta->Fill(product->muonEta.back());
		histCollection->histMuonPhi->Fill(product->muonPhi.back());
		histCollection->histMuonIso->Fill(product->muonIso.back());
		histCollection->histMuonHltIsoDeltaR->Fill(product->muonHltIsoDeltaR.back());
		histCollection->histMuonDeltaR->Fill(product->muonDeltaR.back());
		histCollection->histMuonEtaSt1->Fill(product->muonEtaSt1.back());
		histCollection->histMuonPhiSt1->Fill(product->muonPhiSt1.back());
		histCollection->histMuonEtaSt2->Fill(product->muonEtaSt2.back());
		histCollection->histMuonPhiSt2->Fill(product->muonPhiSt2.back());

		histCollection->histMuonIEta->Fill(product->muonIEta.back());
	}
	product->nMuon = product->muonPt.size();
}

void MuonProducer::EndJob(HoHistogramCollection* histCollection) {}
MuonProducer::~MuonProducer() {}
