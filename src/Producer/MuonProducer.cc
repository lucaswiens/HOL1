#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>

MuonProducer::MuonProducer(HoHistogramCollection* histCollection) {}

void MuonProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	product->nMuon = *dataReader->nMuon->Get();

	for (unsigned short i = 0; i < product->nMuon; i++){
		product->isLooseMuon.push_back(dataReader->muonIsLooseMuon->At(i));
		product->isMediumMuon.push_back(dataReader->muonIsMediumMuon->At(i));
		product->isTightMuon.push_back(dataReader->muonIsTightMuon->At(i));
		product->muonHltIsoMu.push_back(dataReader->muonHlt_isomu->At(i));
		product->muonHltMu.push_back(dataReader->muonHlt_mu->At(i));
		product->muonPassesSingleMuon.push_back(dataReader->muonPassesSingleMuon->At(i));
		product->muonCharge.push_back(dataReader->muonCharge->At(i));
		product->muonE.push_back(dataReader->muonE->At(i));
		product->muonEt.push_back(dataReader->muonEt->At(i));
		product->muonPt.push_back(dataReader->muonPt->At(i));
		product->muonEta.push_back(dataReader->muonEta->At(i));
		product->muonPhi.push_back(dataReader->muonPhi->At(i));
		product->muonIso.push_back(dataReader->muonIso->At(i));
		product->muonHltIsoDeltaR.push_back(dataReader->muonHlt_isoDeltaR->At(i));
		product->muonDeltaR.push_back(dataReader->muonHlt_deltaR->At(i));
		product->muonEtaSt1.push_back(dataReader->muonEtaSt1->At(i));
		product->muonPhiSt1.push_back(dataReader->muonPhiSt1->At(i));
		product->muonEtaSt2.push_back(dataReader->muonEtaSt2->At(i));
		product->muonPhiSt2.push_back(dataReader->muonPhiSt2->At(i));
		product->muonMet.push_back(dataReader->muonMet->At(i));
		product->muonMt.push_back(dataReader->muonMt->At(i));

		product->muonIEta.push_back(Utility::CmsEtaToHoIEta(product->muonEta.back()));

		product->muonHasMb1.push_back((fabs(product->muonEtaSt1.back()) < 5) && (fabs(product->muonPhiSt1.back()) < M_PI));

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
}

void MuonProducer::EndJob(HoHistogramCollection* histCollection) {}
MuonProducer::~MuonProducer() {}
