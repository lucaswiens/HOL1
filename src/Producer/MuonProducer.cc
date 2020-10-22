#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>

MuonProducer::MuonProducer() {
	histMuonMet = new TH1D("muonMet", "muonMet", 30, 0, 1000);
	histMuonMt = new TH1D("muonMt", "muonMt", 30, 0, 1000);

	histMuonIsLooseMuon = new TH1I("muonIsLooseMuon", "muonIsLooseMuon", 2, 0, 2);
	histMuonIsMediumMuon = new TH1I("muonIsMediumMuon", "muonIsMediumMuon", 2, 0, 2);
	histMuonIsTightMuon = new TH1I("muonIsTightMuon", "muonIsTightMuon", 2, 0, 2);
	histMuonHlt_isomu = new TH1I("muonHlt_isomu", "muonHlt_isomu", 2, 0, 2);
	histMuonHlt_mu = new TH1I("muonHlt_mu", "muonHlt_mu", 2, 0, 2);
	histMuonPassesSingleMuon = new TH1I("muonPassesSingleMuon", "muonPassesSingleMuon", 2, 0, 2);
	histMuonCharge = new TH1I("muonCharge", "muonCharge", 3, -1, 1);

	histMuonE = new TH1F("muonE", "muonE", 30, 0, 1000);
	histMuonEt = new TH1F("muonEt", "muonEt", 30, 0, 1000);
	histMuonPt = new TH1F("muonPt", "muonPt", 30, 0, 1000);
	histMuonEta = new TH1F("muonEta", "muonEta", 30, -3, 3);
	histMuonPhi = new TH1F("muonPhi", "muonPhi", 30, -TMath::Pi(), TMath::Pi());
	histMuonIso = new TH1F("muonIso", "muonIso", 30, 0, 1);
	histMuonHlt_isoDeltaR = new TH1F("muonHlt_isoDeltaR", "muonHlt_isoDeltaR", 30, 0, 5);
	histMuonHlt_deltaR = new TH1F("muonHlt_deltaR", "muonHlt_deltaR", 30, 0, 5);
	histMuonEtaSt1 = new TH1F("muonEtaSt1", "muonEtaSt1", 30, -3, 3);
	histMuonPhiSt1 = new TH1F("muonPhiSt1", "muonPhiSt1", 30, -TMath::Pi(), TMath::Pi());
	histMuonEtaSt2 = new TH1F("muonEtaSt2", "muonEtaSt2", 30, -3, 3);
	histMuonPhiSt2 = new TH1F("muonPhiSt2", "muonPhiSt2", 30, -TMath::Pi(), TMath::Pi());
}

void MuonProducer::Produce(DataReader* dataReader) {
	unsigned short NMuon = *dataReader->nMuon->Get();
	for (unsigned short i = 0; i < NMuon; i++){
		histMuonMet->Fill(dataReader->muonMet->At(i));
		histMuonMt->Fill(dataReader->muonMt->At(i));

		histMuonIsLooseMuon->Fill(dataReader->muonIsLooseMuon->At(i));
		histMuonIsMediumMuon->Fill(dataReader->muonIsMediumMuon->At(i));
		histMuonIsTightMuon->Fill(dataReader->muonIsTightMuon->At(i));
		histMuonHlt_isomu->Fill(dataReader->muonHlt_isomu->At(i));
		histMuonHlt_mu->Fill(dataReader->muonHlt_mu->At(i));
		histMuonPassesSingleMuon->Fill(dataReader->muonPassesSingleMuon->At(i));
		histMuonCharge->Fill(dataReader->muonCharge->At(i));

		histMuonE->Fill(dataReader->muonE->At(i));
		histMuonEt->Fill(dataReader->muonEt->At(i));
		histMuonPt->Fill(dataReader->muonPt->At(i));
		histMuonEta->Fill(dataReader->muonEta->At(i));
		histMuonPhi->Fill(dataReader->muonPhi->At(i));
		histMuonIso->Fill(dataReader->muonIso->At(i));
		histMuonHlt_isoDeltaR->Fill(dataReader->muonHlt_isoDeltaR->At(i));
		histMuonHlt_deltaR->Fill(dataReader->muonHlt_deltaR->At(i));
		histMuonEtaSt1->Fill(dataReader->muonEtaSt1->At(i));
		histMuonPhiSt1->Fill(dataReader->muonPhiSt1->At(i));
		histMuonEtaSt2->Fill(dataReader->muonEtaSt2->At(i));
		histMuonPhiSt2->Fill(dataReader->muonPhiSt2->At(i));
	}
}

MuonProducer::~MuonProducer() {}
