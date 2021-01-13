#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

#include <TMath.h>

class HoHistogramProducer : public BaseProducer {
	private:
		TH1S *histNUnusedMuon, *histIsMediumUnusedMuon, *histUnusedMuonHltIsoMu, *histUnusedMuonHltMu, *histUnusedMuonPassesSingleMuon, *histUnusedMuonHasMb1,
			*histIsBmtfMatchedMuon,
			*histIsMb3HoIEtaMatched, *histIsMb4HoIEtaMatched,
			*histIsDttpMatchedHo,
			*histIsDttpMatchedMuon,
			*histIsBmtfMatchedDttp;

		TH1I *histUnusedMuonCharge, *histUnusedMuonIEta,
			*histBmtfMatchedMuonCharge, *histBmtfMatchedMuonIndex,
			*histBmtfMb34MatchedHoIEta, *histBmtfMb34MatchedHoIPhi, *histBmtfMb34MatchedHoDeltaIPhi,
			*histDttpMatchedHoDeltaIPhi, *histDttpMatchedHoIPhi, *histDttpMatchedHoIEta,
			*histNHo3x3Hit,
			*histBmtfMatchedDttpPhi;

		//TH1F *histUnusedMuonE, *histUnusedMuonEt, *histUnusedMuonPt, *histUnusedMuonEta, *histUnusedMuonPhi, *histUnusedMuonIso, *histUnusedMuonHltIsoDeltaR, *histUnusedMuonDeltaR, *histUnusedMuonEtaSt1, *histUnusedMuonPhiSt1, *histUnusedMuonEtaSt2, *histUnusedMuonPhiSt2;
		TH1D *histUnusedMuonE, *histUnusedMuonEt, *histUnusedMuonPt, *histUnusedMuonEta, *histUnusedMuonPhi, *histUnusedMuonIso, *histUnusedMuonHltIsoDeltaR, *histUnusedMuonDeltaR, *histUnusedMuonEtaSt1, *histUnusedMuonPhiSt1, *histUnusedMuonEtaSt2, *histUnusedMuonPhiSt2;

		TH1D *histUnusedMuonMet, *histUnusedMuonMt,
			*histBmtfMatchedMuonDeltaR, *histBmtfMatchedMuonPt, *histBmtfMatchedMuonEta, *histBmtfMatchedMuonPhi, *histBmtfMatchedMuonTrackType, *histBmtfMatchedMuonDeltaPhi,
			*histBmtfMb34MatchedHoDeltaR, *histBmtfMb34MatchedHoPt, *histBmtfMb34MatchedHoCmsEta, *histBmtfMb34MatchedHoCmsPhi, *histBmtfMb34MatchedHoDeltaPhi, *histBmtfMb34MatchedMuonPt, *histBmtfMb34MatchedMuonEta, *histBmtfMb34MatchedMuonPhi, *histBmtfMb34MatchedMuonDeltaPhi,
			*histDttpMatchedHoCmsPhi, *histDttpMatchedHoCmsEta,
			*histBmtfMatchedDttpPt, *histBmtfMatchedDttpDeltaPhi, *histBmtfMatchedDttpCmsPhi, *histBmtfMatchedDttpDeltaPhiSt1, *histBmtfMatchedDttpDeltaPhiSt2, *histBmtfMatchedDttpDeltaPhiSt3, *histBmtfMatchedDttpDeltaPhiSt4,
			*histDttpMatchedMuonDeltaR;


	public:
		HoHistogramProducer();
		~HoHistogramProducer();
		void Produce(DataReader *dataReader, HoProduct *product);
};
