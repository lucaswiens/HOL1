#pragma once

#include <TGraphAsymmErrors.h>
#include <TH1F.h>
#include <TH2F.h>

class HoHistogramCollection {
public:
	HoHistogramCollection(){};
	~HoHistogramCollection(){};
	// BMTF and DTTP Histograms
	TH1I *histDttpSize, *histBmtfThSize, *histDttpBx, *histDttpWheel, *histDttpSection, *histDttpStation, *histDttpQualityCode, *histDttpTs2Tag, *histBmtfThBx, *histBmtfThWh, *histBmtfThSe, *histBmtfThSt, *histBmtfThTheta, *histBmtfThCode, *histDttpIPhi;
	TH1S *histNBmtf, *histBmtfHwPt, *histBmtfHwEta, *histBmtfHwPhi, *histBmtfGlobalPhi, *histBmtfHwSign, *histBmtfHwSignValid, *histBmtfHwQual, *histBmtfLink, *histBmtfProcessor, *histBmtfTrackFinderType, *histBmtfTrackType, *histBmtfHwHF, *histBmtfBx, *histBmtfWh, *histBmtfTrAdd, *histBmtfTrAddSt1, *histBmtfTrAddSt2, *histBmtfTrAddSt3, *histBmtfTrAddSt4;
	TH1F *histDttpPhi, *histDttpPhiB;
	TH1D *histBmtfCmsPt, *histBmtfCmsEta, *histBmtfCmsPhi, *histDttpCmsPhi, *histDttpPt, *histDttpCmsPhiSection1, *histDttpCmsPhiSection2, *histDttpCmsPhiSection3, *histDttpCmsPhiSection4, *histDttpCmsPhiSection5, *histDttpCmsPhiSection6, *histDttpCmsPhiSection7, *histDttpCmsPhiSection8, *histDttpCmsPhiSection9, *histDttpCmsPhiSection10, *histDttpCmsPhiSection11, *histDttpCmsPhiSection12;
	// HO Histograms
	TH1D *histSumQ, *histHcalCmsPhi, *histHcalCmsEta;
	TH1I *histNHcalDetIds, *histNHcalQIESamples, *histHcalDetIdIEta, *histHcalDetIdIPhi, *histHcalQIESample, *histHcalQIESampleAdc, *histHcalQIESampleDv, *histHcalQIESampleEr, *histHcalWheel, *histHcalSection;
	TH1F *histSampleEnergy, *histQIESampleFc,  *histQIESamplePedestal, *histQIESampleFc_MPedestals;
	// Reco Muon Histogram
	TH1D *histMuonMet, *histMuonMt;
	TH1I *histIsLooseMuon, *histIsMediumMuon, *histIsTightMuon, *histMuonHltIsoMu, *histMuonHltMu, *histMuonPassesSingleMuon, *histMuonCharge, *histMuonIEta;
	TH1F *histMuonE, *histMuonEt, *histMuonPt, *histMuonEta, *histMuonPhi, *histMuonIso, *histMuonHltIsoDeltaR, *histMuonDeltaR, *histMuonEtaSt1, *histMuonPhiSt1, *histMuonEtaSt2, *histMuonPhiSt2;
	// HO Coincidence Histogram
	TGraphAsymmErrors *efficiencyBmtf34MatchedHoPt, *efficiencyBmtfPt;
	TH1S *histNUnusedMuon, *histIsMediumUnusedMuon, *histUnusedMuonHltIsoMu, *histUnusedMuonHltMu, *histUnusedMuonPassesSingleMuon, *histUnusedMuonHasMb1,
		*histNUsedMuon, *histIsMediumUsedMuon, *histUsedMuonHltIsoMu, *histUsedMuonHltMu, *histUsedMuonPassesSingleMuon, *histUsedMuonHasMb1,
		*histIsBmtfMatchedMuon,
		*histIsMb3HoIEtaMatched, *histIsMb4HoIEtaMatched,
		*histIsDttpMatchedHo,
		*histIsDttpMatchedMuon,
		*histIsBmtfMatchedDttp;

	TH1I *histUnusedMuonCharge, *histUnusedMuonIEta,
		*histUsedMuonCharge, *histUsedMuonIEta,
		*histBmtfMatchedMuonCharge, *histBmtfMatchedMuonIndex,
		*histBmtfMb34MatchedHoIEta, *histBmtfMb34MatchedHoIPhi, *histBmtfMb34MatchedHoDeltaIPhi,
		*histDttpMatchedHoDeltaIPhi, *histDttpMatchedHoIPhi, *histDttpMatchedHoIEta,
		*histNHo3x3Hit,
		*histBmtfMatchedDttpPhi;

	TH1D *histDttpMatchedHoDeltaPhi;
	// Used and Unused Histograms
	TH1D *histUnusedMuonE, *histUnusedMuonEt, *histUnusedMuonPt, *histUnusedMuonEta, *histUnusedMuonPhi, *histUnusedMuonIso, *histUnusedMuonHltIsoDeltaR, *histUnusedMuonDeltaR, *histUnusedMuonEtaSt1, *histUnusedMuonPhiSt1, *histUnusedMuonEtaSt2, *histUnusedMuonPhiSt2,
		*histUsedMuonE, *histUsedMuonEt, *histUsedMuonPt, *histUsedMuonEta, *histUsedMuonPhi, *histUsedMuonIso, *histUsedMuonHltIsoDeltaR, *histUsedMuonDeltaR, *histUsedMuonEtaSt1, *histUsedMuonPhiSt1, *histUsedMuonEtaSt2, *histUsedMuonPhiSt2;

	TH1D *histUnusedMuonMet, *histUnusedMuonMt,
		*histUsedMuonMet, *histUsedMuonMt,
		*histBmtfMatchedMuonDeltaR, *histBmtfMatchedMuonPt, *histBmtfMatchedMuonEta, *histBmtfMatchedMuonPhi, *histBmtfMatchedMuonTrackType, *histBmtfMatchedMuonDeltaPhi,
		*histBmtfMb34MatchedHoDeltaR, *histBmtfMb34MatchedHoPt, *histBmtfMb34MatchedHoCmsEta, *histBmtfMb34MatchedHoCmsPhi, *histBmtfMb34MatchedHoDeltaPhi, *histBmtfMb34MatchedMuonPt, *histBmtfMb34MatchedMuonEta, *histBmtfMb34MatchedMuonPhi, *histBmtfMb34MatchedMuonDeltaPhi,
		*histDttpMatchedHoCmsPhi, *histDttpMatchedHoCmsEta,
		*histBmtfMatchedDttpPt, *histBmtfMatchedDttpDeltaPhi, *histBmtfMatchedDttpCmsPhi, *histBmtfMatchedDttpDeltaPhiSt1, *histBmtfMatchedDttpDeltaPhiSt2, *histBmtfMatchedDttpDeltaPhiSt3, *histBmtfMatchedDttpDeltaPhiSt4,
		*histDttpMatchedMuonDeltaR;
};
