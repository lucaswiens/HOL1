#pragma once

#include <TGraphAsymmErrors.h>
#include <TH1F.h>
#include <TH2F.h>

class HoHistogramCollection {
private:
	bool hasRecoMuon;
public:
	HoHistogramCollection(const bool &hasRecoMuon);
	~HoHistogramCollection();
	bool GetHasRecoMuon() {return hasRecoMuon;}
	//void SetHasRecoMuon(bool HasRecoMuon) {hasRecoMuon = HasRecoMuon;}
	TH1I *numberOfEvents;

	// BMTF and DTTP Histograms
	TH1I *histDttpSize, *histBmtfThSize, *histDttpBx, *histDttpWheel, *histDttpSection, *histDttpStation, *histDttpQualityCode, *histDttpTs2Tag, *histBmtfThBx, *histBmtfThWh, *histBmtfThSe, *histBmtfThSt, *histBmtfThTheta, *histBmtfThCode, *histDttpIPhi,
	//new one
	*hist_corrected_DttpBx, *hist_HoMatched_DttpBx;
	TH1S *histNBmtf, *histBmtfHwPt, *histBmtfHwEta, *histBmtfHwPhi, *histBmtfGlobalPhi, *histBmtfHwSign, *histBmtfHwSignValid, *histBmtfHwQual, *histBmtfLink, *histBmtfProcessor, *histBmtfTrackFinderType, *histBmtfTrackType, *histBmtfHwHF, *histBmtfBx, *histBmtfWh, *histBmtfTrAdd, *histBmtfTrAddSt1, *histBmtfTrAddSt2, *histBmtfTrAddSt3, *histBmtfTrAddSt4;
	TH1F *histDttpPhi, *histDttpPhiB;
	TH1D *histBmtfCmsPt, *histBmtfCmsPt20, *histBmtfCmsEta, *histBmtfCmsPhi, *histDttpCmsPhi, *histDttpCmsPt, *histDttpCmsPhiSection1, *histDttpCmsPhiSection2, *histDttpCmsPhiSection3, *histDttpCmsPhiSection4, *histDttpCmsPhiSection5, *histDttpCmsPhiSection6, *histDttpCmsPhiSection7, *histDttpCmsPhiSection8, *histDttpCmsPhiSection9, *histDttpCmsPhiSection10, *histDttpCmsPhiSection11, *histDttpCmsPhiSection12, *histBmtfNumber;
	// HO Histograms
	TH1D *histSumQ, *histHcalCmsPhi, *histHcalCmsEta;
	TH1I *histNHcalDetIds, *histNHcalQIESamples, *histHcalDetIdIEta, *histHcalDetIdIPhi, *histHcalQIESample, *histHcalQIESampleAdc, *histHcalQIESampleDv, *histHcalQIESampleEr, *histHcalWheel, *histHcalSection;
	TH1F *histSampleEnergy, *histQIESampleFc,  *histQIESamplePedestal, *histQIESampleFc_MPedestals,
		  //new one
		 *hist_Weighted_HcalQIESampleAdc;
	// Reco Muon Histogram
	TH1D *histMuonMet, *histMuonMt, *histDiMuonMass, *histSelectedDiMuonMass;
	TH1I *histIsLooseMuon, *histIsMediumMuon, *histIsTightMuon, *histMuonHltIsoMu, *histMuonHltMu, *histMuonPassesSingleMuon, *histMuonCharge, *histMuonIEta, *histMuonHoN3x3Hit, *histDttpHoN3x3Hit;
	TH1F *histMuonE, *histMuonEt, *histMuonPt, *histMuonPt20, *histMuonEta, *histMuonPhi, *histMuonIso, *histMuonHltIsoDeltaR, *histMuonDeltaR, *histMuonEtaSt1, *histMuonPhiSt1, *histMuonEtaSt2, *histMuonPhiSt2;
	TH2D *histMuonPt_vs_MuonEta, *histMuonEta_vs_MuonPt, *histNTagMuon_vs_nProbeMuon;
	// HO Coincidence Histogram
	TH1S *histIsBmtfMatchedMuon,
		*histIsMb3HoIEtaMatched, *histIsMb4HoIEtaMatched,
		*histIsDttpMatchedHo,
		*histIsDttpMatchedHoN3x3,
		*histIsDttpMatchedMuon,
		*histIsBmtfMatchedDttp;

	TH1I *histBmtfMatchedMuonCharge, *histBmtfMatchedMuonIndex,
		*histBmtfMb34MatchedHoIEta, *histBmtfMb34MatchedHoIPhi, *histBmtfMb34MatchedHoDeltaIPhi,
		*histDttpMatchedHoDeltaIPhi, *histDttpMatchedHoIPhi, *histDttpMatchedHoIEta,
		*histDttpMatchedHoN3x3, *histDttpMatchedHoN3x3DeltaIPhi, *histDttpMatchedHoN3x3IPhi, *histDttpMatchedHoN3x3IEta,
		*histHoN3x3Hit,
		*histBmtfMatchedDttpPhi;

	TH1D *histDttpMatchedHoDeltaPhi, *histMuonMatchedBmtfCmsPt, *histMuonMatchedBmtfCmsEta, *histDttpMatchedHoNumber,
		*histDttpMatchedHoN3x3DeltaPhi, *histDttpMatchedHoN3x3Number,
		*histIsoMb1MatchedMuonPt, *histIsoMb1MatchedMuonPt20,*histIsoMb1MatchedMuonEta,
		*histIsoMb12MatchedMuonPt, *histIsoMb12MatchedMuonPt20,*histIsoMb12MatchedMuonEta,
		*histIsoMb2MatchedMuonPt, *histIsoMb2MatchedMuonPt20,*histIsoMb2MatchedMuonEta,
		*histIsoMb1MatchedMuonN3x3Pt, *histIsoMb1MatchedMuonN3x3Pt20,*histIsoMb1MatchedMuonN3x3Eta,
		*histIsoMb12MatchedMuonN3x3Pt, *histIsoMb12MatchedMuonN3x3Pt20,*histIsoMb12MatchedMuonN3x3Eta,
		*histIsoMb2MatchedMuonN3x3Pt, *histIsoMb2MatchedMuonN3x3Pt20,*histIsoMb2MatchedMuonN3x3Eta,
		*histBmtfMatchedMuonDeltaR, *histBmtfMatchedMuonPt, *histBmtfMatchedMuonPt20, *histBmtfMatchedMuonEta, *histBmtfMatchedMuonPhi, *histBmtfMatchedMuonTrackType, *histBmtfMatchedMuonDeltaPhi,
		*histBmtfMb34MatchedHoDeltaR, *histBmtfMb34MatchedHoPt, *histBmtfMb34MatchedHoPt20, *histBmtfMb34MatchedHoCmsEta, *histBmtfMb34MatchedHoCmsPhi, *histBmtfMb34MatchedHoDeltaPhi, *histBmtfMb34MatchedMuonPt, *histBmtfMb34MatchedMuonPt20, *histBmtfMb34MatchedMuonEta, *histBmtfMb34MatchedMuonPhi, *histBmtfMb34MatchedMuonDeltaPhi, *histBmtfMb34MatchedHoNumber,
		*histDttpMatchedHoCmsPhi, *histDttpMatchedHoCmsEta,
		*histDttpMatchedHoN3x3CmsPhi, *histDttpMatchedHoN3x3CmsEta,
		*histBmtfMatchedDttpCmsPt, *histBmtfMatchedDttpDeltaPhi, *histBmtfMatchedDttpCmsPhi, *histBmtfMatchedDttpDeltaPhiSt1, *histBmtfMatchedDttpDeltaPhiSt2, *histBmtfMatchedDttpDeltaPhiSt3, *histBmtfMatchedDttpDeltaPhiSt4,
		*histDttpMatchedMuonDeltaR;


	//XvsY
	TH2D *histBmtfMatchedMuonPt_vs_MuonEta, *histBmtfMatchedMuonEta_vs_MuonPt,
		*histIsoMb1MatchedMuonEta_vs_MuonPt, *histIsoMb2MatchedMuonEta_vs_MuonPt, *histIsoMb12MatchedMuonEta_vs_MuonPt,
		*histIsoMb1MatchedMuonN3x3Eta_vs_MuonPt, *histIsoMb2MatchedMuonN3x3Eta_vs_MuonPt, *histIsoMb12MatchedMuonN3x3Eta_vs_MuonPt,
		*histHcalQIESamples_vs_HcalQIESampleAdc;

	// Used and Unused Histograms
	TH1S *histNUnusedMuon, *histIsMediumUnusedMuon, *histUnusedMuonHltIsoMu, *histUnusedMuonHltMu, *histUnusedMuonPassesSingleMuon, *histUnusedMuonHasMb1,
		*histNUsedMuon, *histIsMediumUsedMuon, *histUsedMuonHltIsoMu, *histUsedMuonHltMu, *histUsedMuonPassesSingleMuon, *histUsedMuonHasMb1;

	TH1I *histUnusedMuonCharge, *histUnusedMuonIEta, *histUnusedMuonHoN3x3Hit,
		*histUsedMuonCharge, *histUsedMuonIEta, *histUsedMuonHoN3x3Hit;

	TH1D *histUnusedMuonE, *histUnusedMuonEt, *histUnusedMuonPt, *histUnusedMuonPt20, *histUnusedMuonEta, *histUnusedMuonPhi, *histUnusedMuonIso, *histUnusedMuonHltIsoDeltaR, *histUnusedMuonDeltaR, *histUnusedMuonEtaSt1, *histUnusedMuonPhiSt1, *histUnusedMuonEtaSt2, *histUnusedMuonPhiSt2,
		*histUsedMuonE, *histUsedMuonEt, *histUsedMuonPt, *histUsedMuonPt20, *histUsedMuonEta, *histUsedMuonPhi, *histUsedMuonIso, *histUsedMuonHltIsoDeltaR, *histUsedMuonDeltaR, *histUsedMuonEtaSt1, *histUsedMuonPhiSt1, *histUsedMuonEtaSt2, *histUsedMuonPhiSt2;

	TH1D *histUnusedMuonMet, *histUnusedMuonMt,
		*histUsedMuonMet, *histUsedMuonMt;
};

