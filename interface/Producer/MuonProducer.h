#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class MuonProducer : public BaseProducer {
	private:
		TH1D *histMuonMet, *histMuonMt;
		TH1I *histIsLooseMuon, *histIsMediumMuon, *histIsTightMuon, *histMuonHltIsoMu, *histMuonHltMu, *histMuonPassesSingleMuon, *histMuonCharge, *histMuonIEta;
		TH1F *histMuonE, *histMuonEt, *histMuonPt, *histMuonEta, *histMuonPhi, *histMuonIso, *histMuonHltIsoDeltaR, *histMuonDeltaR, *histMuonEtaSt1, *histMuonPhiSt1, *histMuonEtaSt2, *histMuonPhiSt2;

	public:
		MuonProducer();
		~MuonProducer();
		void Produce(DataReader* dataReader, HoProduct* product);
};
