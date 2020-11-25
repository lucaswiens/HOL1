#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>

MuonProducer::MuonProducer() {
	histMuonMet = new TH1D("muonMet", "muonMet", 30, 0, 1000);
	histMuonMt = new TH1D("muonMt", "muonMt", 30, 0, 1000);

	histIsLooseMuon = new TH1I("isLooseMuon", "isLooseMuon", 2, 0, 2);
	histIsMediumMuon = new TH1I("isMediumMuon", "isMediumMuon", 2, 0, 2);
	histIsTightMuon = new TH1I("isTightMuon", "isTightMuon", 2, 0, 2);
	histMuonHltIsoMu = new TH1I("muonHlt_isomu", "muonHlt_isomu", 2, 0, 2);
	histMuonHltMu = new TH1I("muonHlt_mu", "muonHlt_mu", 2, 0, 2);
	histMuonPassesSingleMuon = new TH1I("muonPassesSingleMuon", "muonPassesSingleMuon", 2, 0, 2);
	histMuonCharge = new TH1I("muonCharge", "muonCharge", 3, -1, 1);
	histMuonIEta = new TH1I("muonIEta", "muonIEta", 20, 0, 20);

	histMuonE = new TH1F("muonE", "muonE", 30, 0, 1000);
	histMuonEt = new TH1F("muonEt", "muonEt", 30, 0, 1000);
	histMuonPt = new TH1F("muonPt", "muonPt", 30, 0, 1000);
	histMuonEta = new TH1F("muonEta", "muonEta", 30, -3, 3);
	histMuonPhi = new TH1F("muonPhi", "muonPhi", 30, -M_PI, M_PI);
	histMuonIso = new TH1F("muonIso", "muonIso", 30, 0, 1);
	histMuonHltIsoDeltaR = new TH1F("muonHlt_isoDeltaR", "muonHlt_isoDeltaR", 30, 0, 5);
	histMuonDeltaR = new TH1F("muonHlt_deltaR", "muonHlt_deltaR", 30, 0, 5);
	histMuonEtaSt1 = new TH1F("muonEtaSt1", "muonEtaSt1", 30, -3, 3);
	histMuonPhiSt1 = new TH1F("muonPhiSt1", "muonPhiSt1", 30, -M_PI, M_PI);
	histMuonEtaSt2 = new TH1F("muonEtaSt2", "muonEtaSt2", 30, -3, 3);
	histMuonPhiSt2 = new TH1F("muonPhiSt2", "muonPhiSt2", 30, -M_PI, M_PI);

}

void MuonProducer::Produce(DataReader* dataReader, HoProduct* product) {
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

		histMuonMet->Fill(product->muonMet.back());
		histMuonMt->Fill(product->muonMt.back());

		histIsLooseMuon->Fill(product->isLooseMuon.back());
		histIsMediumMuon->Fill(product->isMediumMuon.back());
		histIsTightMuon->Fill(product->isTightMuon.back());
		histMuonHltIsoMu->Fill(product->muonHltIsoMu.back());
		histMuonHltMu->Fill(product->muonHltMu.back());
		histMuonPassesSingleMuon->Fill(product->muonPassesSingleMuon.back());
		histMuonCharge->Fill(product->muonCharge.back());

		histMuonE->Fill(product->muonE.back());
		histMuonEt->Fill(product->muonEt.back());
		histMuonPt->Fill(product->muonPt.back());
		histMuonEta->Fill(product->muonEta.back());
		histMuonPhi->Fill(product->muonPhi.back());
		histMuonIso->Fill(product->muonIso.back());
		histMuonHltIsoDeltaR->Fill(product->muonHltIsoDeltaR.back());
		histMuonDeltaR->Fill(product->muonDeltaR.back());
		histMuonEtaSt1->Fill(product->muonEtaSt1.back());
		histMuonPhiSt1->Fill(product->muonPhiSt1.back());
		histMuonEtaSt2->Fill(product->muonEtaSt2.back());
		histMuonPhiSt2->Fill(product->muonPhiSt2.back());

		histMuonIEta->Fill(product->muonIEta.back());
	}
}

MuonProducer::~MuonProducer() {}
