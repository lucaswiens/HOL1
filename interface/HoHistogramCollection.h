#pragma once

#include <TGraphAsymmErrors.h>
#include <TH1D.h>
#include <TH2F.h>

#include <HOAnalysis/HOL1/interface/Utility/Utility.h>

class HoHistogramCollection {
private:
	bool hasRecoMuon;
public:
	HoHistogramCollection(const bool &hasRecoMuon);
	~HoHistogramCollection();
	bool GetHasRecoMuon() {return hasRecoMuon;}
	//void SetHasRecoMuon(bool HasRecoMuon) {hasRecoMuon = HasRecoMuon;}
	TH1D *numberOfEvents;

	// BMTF and DTTP Histograms
	TH1D *histDttpSize, *histBmtfThSize, *histDttpBx, *histDttpWheel, *histDttpSection, *histDttpStation, *histDttpQualityCode, *histDttpTs2Tag, *histBmtfThBx, *histBmtfThWh, *histBmtfThSe, *histBmtfThSt, *histBmtfThTheta, *histBmtfThCode, *histDttpIPhi;
	TH1D *histNBmtf, *histBmtfHwPt, *histBmtfHwEta, *histBmtfHwPhi, *histBmtfGlobalPhi, *histBmtfHwSign, *histBmtfHwSignValid, *histBmtfHwQual, *histBmtfLink, *histBmtfProcessor, *histBmtfTrackFinderType, *histBmtfTrackType, *histBmtfHwHF, *histBmtfBx, *histBmtfWh, *histBmtfTrAdd, *histBmtfTrAddSt1, *histBmtfTrAddSt2, *histBmtfTrAddSt3, *histBmtfTrAddSt4;
	TH1D *histDttpPhi, *histDttpPhiB;
	TH1D *histBmtfCmsPt, *histBmtfCmsPtFineBinning, *histBmtfCmsEta, *histBmtfCmsPhi, *histDttpCmsPhi, *histDttpCmsPt, *histDttpCmsPhiSection1, *histDttpCmsPhiSection2, *histDttpCmsPhiSection3, *histDttpCmsPhiSection4, *histDttpCmsPhiSection5, *histDttpCmsPhiSection6, *histDttpCmsPhiSection7, *histDttpCmsPhiSection8, *histDttpCmsPhiSection9, *histDttpCmsPhiSection10, *histDttpCmsPhiSection11, *histDttpCmsPhiSection12, *histBmtfNumber,
		*histtfMuonRateVsPhi, *histBmtfMuonRateVsPhi, *histOmtfMuonRateVsPhi, *histEmtfMuonRateVsPhi,
		*histtfMatchedMuonRateVsPhi, *histBmtfMatchedMuonRateVsPhi, *histOmtfMatchedMuonRateVsPhi, *histMatchedEmtfMuonRateVsPhi;
	// HO Histograms
	TH1D *histSumQ, *histHcalCmsPhi, *histHcalCmsEta;
	TH1D *histNHcalDetIds, *histNHcalQIESamples, *histHcalDetIdIEta, *histHcalDetIdIPhi, *histHcalQIESample, *histHcalQIESampleAdc, *histHcalQIESampleDv, *histHcalQIESampleEr, *histHcalWheel, *histHcalSection;
	TH1D *histSampleEnergy, *histQIESampleFc,  *histQIESamplePedestal, *histQIESampleFc_MPedestals;
	// Reco Muon Histogram
	TH1D *histMuonMet, *histMuonMt, *histDiMuonMass, *histTagAndProbeDiMuonMass;
	TH1D *histNMuon, *histIsLooseMuon, *histIsMediumMuon, *histIsTightMuon, *histMuonHltIsoMu, *histMuonHltMu, *histMuonPassesSingleMuon, *histMuonCharge, *histMuonIEta, *histMuonHoN3x3Hit, *histDttpHoN3x3Hit;
	TH1D *histMuonE, *histMuonEt, *histMuonPt, *histMuonPtAtIEtaP3, *histMuonPtAtIEtaM3, *histMuonPtFineBinning, *histMuonEta, *histMuonEtaHighPt, *histMuonEtaLowPt, *histMuonPhi, *histMuonIso, *histMuonHltIsoDeltaR, *histMuonDeltaR, *histMuonEtaSt1, *histMuonPhiSt1, *histMuonEtaSt2, *histMuonPhiSt2;
	TH2D *histMuonPt_vs_MuonEta, *histMuonEta_vs_MuonPt, *histMuonEta_vs_MuonPhi, *histNTagMuon_vs_nProbeMuon;
	// Reco Tag Muon
	TH1D *histTagMuonMet, *histTagMuonMt;
	TH1D *histNTagMuon, *histIsLooseTagMuon, *histIsMediumTagMuon, *histIsTightTagMuon, *histTagMuonHltIsoMu, *histTagMuonHltMu, *histTagMuonPassesSingleMuon, *histTagMuonCharge, *histTagMuonIEta, *histTagMuonHoN3x3Hit;
	TH1D *histTagMuonE, *histTagMuonEt, *histTagMuonPt, *histTagMuonPtAtIEtaP3, *histTagMuonPtAtIEtaM3, *histTagMuonPtFineBinning, *histTagMuonEta, *histTagMuonEtaHighPt, *histTagMuonEtaLowPt, *histTagMuonPhi, *histTagMuonIso, *histTagMuonHltIsoDeltaR, *histTagMuonDeltaR, *histTagMuonEtaSt1, *histTagMuonPhiSt1, *histTagMuonEtaSt2, *histTagMuonPhiSt2;
	TH2D *histTagMuonPt_vs_TagMuonEta, *histTagMuonEta_vs_TagMuonPhi, *histTagMuonEta_vs_TagMuonPt;
	// Reco Probe Muon
	TH1D *histProbeMuonMet, *histProbeMuonMt, *histDiProbeMuonMass, *histTagAndProbeDiProbeMuonMass;
	TH1D *histNProbeMuon, *histIsLooseProbeMuon, *histIsMediumProbeMuon, *histIsTightProbeMuon, *histProbeMuonHltIsoMu, *histProbeMuonHltMu, *histProbeMuonPassesSingleMuon, *histProbeMuonCharge, *histProbeMuonIEta, *histProbeMuonHoN3x3Hit;
	TH1D *histProbeMuonE, *histProbeMuonEt, *histProbeMuonPt, *histProbeMuonPtAtIEtaP3, *histProbeMuonPtAtIEtaM3, *histProbeMuonPtFineBinning, *histProbeMuonEta, *histProbeMuonEtaHighPt, *histProbeMuonEtaLowPt, *histProbeMuonPhi, *histProbeMuonIso, *histProbeMuonHltIsoDeltaR, *histProbeMuonDeltaR, *histProbeMuonEtaSt1, *histProbeMuonPhiSt1, *histProbeMuonEtaSt2, *histProbeMuonPhiSt2;
	std::map<int, TH1D*> histProbeMuonMapPt, histProbeMuonMapPtFineBinning, histProbeMuonMapEta, histProbeMuonMapPhi;
	TH2D *histProbeMuonPt_vs_ProbeMuonEta, *histProbeMuonEta_vs_ProbeMuonPhi, *histProbeMuonEta_vs_ProbeMuonPt;
	// HO Coincidence Histogram
	TH1D *histIsBmtfMatchedMuon,
		*histIsTfMatchedMuon,
		*histIsMb3HoIEtaMatched, *histIsMb4HoIEtaMatched,
		*histIsDttpMatchedHo,
		*histIsDttpMatchedHoN3x3,
		*histIsDttpMatchedMuon,
		*histIsBmtfMatchedDttp;

	TH1D *histBmtfMatchedMuonCharge, *histBmtfMatchedMuonIndex,
		*histTfMatchedMuonCharge, *histTfMatchedMuonIndex,
		*histBmtfMb34MatchedHoIEta, *histBmtfMb34MatchedHoIPhi, *histBmtfMb34MatchedHoDeltaIPhi,
		*histDttpMatchedHoDeltaIPhi, *histDttpMatchedHoIPhi, *histDttpMatchedHoIEta,
		*histDttpMatchedHoN3x3, *histDttpMatchedHoN3x3DeltaIPhi, *histDttpMatchedHoN3x3IPhi, *histDttpMatchedHoN3x3IEta,
		*histHoN3x3Hit,
		*histBmtfMatchedDttpPhi;

	TH1D *histDttpMatchedHoDeltaPhi, *histMuonMatchedBmtfCmsPt, *histMuonMatchedBmtfCmsEta, *histDttpMatchedHoNumber,
		*histDttpMatchedHoN3x3DeltaPhi, *histDttpMatchedHoN3x3Number,
		*histIsoMb1MatchedMuonPt,  *histIsoMb1MatchedMuonPtAtIEtaP3,  *histIsoMb1MatchedMuonPtAtIEtaM3,  *histIsoMb1MatchedMuonPtFineBinning,  *histIsoMb1MatchedMuonEta,  *histIsoMb1MatchedMuonEtaLowPt,  *histIsoMb1MatchedMuonEtaHighPt,  *histIsoMb1MatchedMuonPhi,
		*histIsoMb2MatchedMuonPt,  *histIsoMb2MatchedMuonPtAtIEtaP3,  *histIsoMb2MatchedMuonPtAtIEtaM3,  *histIsoMb2MatchedMuonPtFineBinning,  *histIsoMb2MatchedMuonEta,  *histIsoMb2MatchedMuonEtaLowPt,  *histIsoMb2MatchedMuonEtaHighPt,  *histIsoMb2MatchedMuonPhi,
		*histIsoMb12MatchedMuonPt, *histIsoMb12MatchedMuonPtAtIEtaP3, *histIsoMb12MatchedMuonPtAtIEtaM3, *histIsoMb12MatchedMuonPtFineBinning, *histIsoMb12MatchedMuonEta, *histIsoMb12MatchedMuonEtaLowPt, *histIsoMb12MatchedMuonEtaHighPt, *histIsoMb12MatchedMuonPhi,

		*histIsoMb1MatchedMuonN3x3Pt,  *histIsoMb1MatchedMuonN3x3PtAtIEtaP3,  *histIsoMb1MatchedMuonN3x3PtAtIEtaM3,  *histIsoMb1MatchedMuonN3x3PtFineBinning,  *histIsoMb1MatchedMuonN3x3Eta,  *histIsoMb1MatchedMuonN3x3EtaLowPt,  *histIsoMb1MatchedMuonN3x3EtaHighPt,  *histIsoMb1MatchedMuonN3x3Phi,
		*histIsoMb2MatchedMuonN3x3Pt,  *histIsoMb2MatchedMuonN3x3PtAtIEtaP3,  *histIsoMb2MatchedMuonN3x3PtAtIEtaM3,  *histIsoMb2MatchedMuonN3x3PtFineBinning,  *histIsoMb2MatchedMuonN3x3Eta,  *histIsoMb2MatchedMuonN3x3EtaLowPt,  *histIsoMb2MatchedMuonN3x3EtaHighPt,  *histIsoMb2MatchedMuonN3x3Phi,
		*histIsoMb12MatchedMuonN3x3Pt, *histIsoMb12MatchedMuonN3x3PtAtIEtaP3, *histIsoMb12MatchedMuonN3x3PtAtIEtaM3, *histIsoMb12MatchedMuonN3x3PtFineBinning, *histIsoMb12MatchedMuonN3x3Eta, *histIsoMb12MatchedMuonN3x3EtaLowPt, *histIsoMb12MatchedMuonN3x3EtaHighPt, *histIsoMb12MatchedMuonN3x3Phi,
		*histBmtfMatchedMuonDeltaR, *histBmtfMatchedMuonPt, *histBmtfMatchedMuonPtAtIEtaP3, *histBmtfMatchedMuonPtAtIEtaM3, *histBmtfMatchedMuonPtFineBinning, *histBmtfMatchedMuonEta, *histBmtfMatchedMuonEtaLowPt, *histBmtfMatchedMuonEtaHighPt,*histBmtfMatchedMuonPhi, *histBmtfMatchedMuonTrackType, *histBmtfMatchedMuonDeltaPhi,
		*histTfMatchedMuonDeltaR, *histTfMatchedMuonPt, *histTfMatchedMuonPtAtIEtaP3, *histTfMatchedMuonPtAtIEtaM3, *histTfMatchedMuonPtFineBinning, *histTfMatchedMuonEta, *histTfMatchedMuonEtaLowPt, *histTfMatchedMuonEtaHighPt,*histTfMatchedMuonPhi, *histTfMatchedMuonTrackType, *histTfMatchedMuonDeltaPhi,
		*histBmtfMb34MatchedHoDeltaR, *histBmtfMb34MatchedHoPt, *histBmtfMb34MatchedHoPtFineBinning, *histBmtfMb34MatchedHoCmsEta, *histBmtfMb34MatchedHoCmsPhi, *histBmtfMb34MatchedHoDeltaPhi, *histBmtfMb34MatchedMuonPt, *histBmtfMb34MatchedMuonPtFineBinning, *histBmtfMb34MatchedMuonEta, *histBmtfMb34MatchedMuonPhi, *histBmtfMb34MatchedMuonDeltaPhi, *histBmtfMb34MatchedHoNumber,
		*histDttpMatchedHoCmsPhi, *histDttpMatchedHoCmsEta,
		*histDttpMatchedHoN3x3CmsPhi, *histDttpMatchedHoN3x3CmsEta,
		*histBmtfMatchedDttpCmsPt, *histBmtfMatchedDttpDeltaPhi, *histBmtfMatchedDttpCmsPhi, *histBmtfMatchedDttpDeltaPhiSt1, *histBmtfMatchedDttpDeltaPhiSt2, *histBmtfMatchedDttpDeltaPhiSt3, *histBmtfMatchedDttpDeltaPhiSt4,
		*histDttpMatchedMuonDeltaR;

	std::map<int, TH1D*> histTfMapMatchedMuonPt, histTfMapMatchedMuonPtFineBinning, histTfMapMatchedMuonEta, histTfMapMatchedMuonPhi, histTfMapMatchedMuonTfType;


	//XvsY
	TH2D *histBmtfMatchedMuonPt_vs_MuonEta, *histBmtfMatchedMuonEta_vs_MuonPt, *histBmtfMatchedMuonEta_vs_MuonPhi,
		*histTfMatchedMuonPt_vs_MuonEta, *histTfMatchedMuonEta_vs_MuonPt, *histTfMatchedMuonEta_vs_MuonPhi,
		*histIsoMb1MatchedMuonEta_vs_MuonPt, *histIsoMb2MatchedMuonEta_vs_MuonPt, *histIsoMb12MatchedMuonEta_vs_MuonPt,
		*histIsoMb1MatchedMuonEta_vs_MuonPhi, *histIsoMb2MatchedMuonEta_vs_MuonPhi, *histIsoMb12MatchedMuonEta_vs_MuonPhi,
		*histIsoMb1MatchedMuonN3x3Eta_vs_MuonPt, *histIsoMb2MatchedMuonN3x3Eta_vs_MuonPt, *histIsoMb12MatchedMuonN3x3Eta_vs_MuonPt,
		*histIsoMb1MatchedMuonN3x3Eta_vs_MuonPhi, *histIsoMb2MatchedMuonN3x3Eta_vs_MuonPhi, *histIsoMb12MatchedMuonN3x3Eta_vs_MuonPhi,
		*histHcalQIESamples_vs_HcalQIESampleAdc;
};

