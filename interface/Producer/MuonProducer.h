#pragma once

#include <TMath.h>

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>
#include <HOAnalysis/HOL1/interface/DataReader.h>

class MuonProducer : public BaseProducer {
	private:
		TH1D *histMuonMet, *histMuonMt;
		TH1I *histMuonIsLooseMuon, *histMuonIsMediumMuon, *histMuonIsTightMuon, *histMuonHlt_isomu, *histMuonHlt_mu, *histMuonPassesSingleMuon, *histMuonCharge;
		TH1F *histMuonE, *histMuonEt, *histMuonPt, *histMuonEta, *histMuonPhi, *histMuonIso, *histMuonHlt_isoDeltaR, *histMuonHlt_deltaR, *histMuonEtaSt1, *histMuonPhiSt1, *histMuonEtaSt2, *histMuonPhiSt2;

	public:
		MuonProducer();
		~MuonProducer();
		void Produce(DataReader*);
};
