#pragma once

#include <TGraphAsymmErrors.h>
#include <TH1D.h>
#include <TH2F.h>

#include <HOAnalysis/HOL1/interface/Utility/Utility.h>

class HoHistogramCollection {
private:
	bool hasRecoMuon;
	const float maxPt = 149.5;
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
	TH1D *histBmtfCmsPt, *histBmtfCmsPtFineBinning, *histBmtfCmsEta, *histBmtfCmsPhi, *histDttpCmsPhi, *histDttpCmsPt, *histDttpCmsPhiSection1, *histDttpCmsPhiSection2, *histDttpCmsPhiSection3, *histDttpCmsPhiSection4, *histDttpCmsPhiSection5, *histDttpCmsPhiSection6, *histDttpCmsPhiSection7, *histDttpCmsPhiSection8, *histDttpCmsPhiSection9, *histDttpCmsPhiSection10, *histDttpCmsPhiSection11, *histDttpCmsPhiSection12, *histBmtfNumber;
	// HO Histograms
	TH1D *histSumQ, *histHcalCmsPhi, *histHcalCmsEta;
	TH1D *histNHcalDetIds, *histNHcalQIESamples, *histHcalDetIdIEta, *histHcalDetIdIPhi, *histHcalQIESample, *histHcalQIESampleAdc, *histHcalQIESampleDv, *histHcalQIESampleEr, *histHcalWheel, *histHcalSection;
	TH1D *histSampleEnergy, *histQIESampleFc,  *histQIESamplePedestal, *histQIESampleFc_MPedestals;

	// HO histograms that are either matched to a reco muon and DTTP at station 1 or 2.. or not
	TH1D *histNHcalDetIds_isoMb1, *histSampleEnergy_isoMb1, *histHcalDetIdIEta_isoMb1, *histHcalDetIdIPhi_isoMb1, *histHcalCmsEta_isoMb1, *histHcalCmsPhi_isoMb1, *histHcalWheel_isoMb1, *histHcalSection_isoMb1, *histSumQ_isoMb1, *histNHcalQIESamples_isoMb1, *histHcalQIESample_isoMb1, *histHcalQIESampleAdc_isoMb1, *histHcalQIESampleDv_isoMb1, *histHcalQIESampleEr_isoMb1, *histQIESampleFc_isoMb1, *histQIESamplePedestal_isoMb1, *histQIESampleFc_MPedestals_isoMb1,
		*histNHcalDetIds_isoMb2, *histSampleEnergy_isoMb2, *histHcalDetIdIEta_isoMb2, *histHcalDetIdIPhi_isoMb2, *histHcalCmsEta_isoMb2, *histHcalCmsPhi_isoMb2, *histHcalWheel_isoMb2, *histHcalSection_isoMb2, *histSumQ_isoMb2, *histNHcalQIESamples_isoMb2, *histHcalQIESample_isoMb2, *histHcalQIESampleAdc_isoMb2, *histHcalQIESampleDv_isoMb2, *histHcalQIESampleEr_isoMb2, *histQIESampleFc_isoMb2, *histQIESamplePedestal_isoMb2, *histQIESampleFc_MPedestals_isoMb2,
		*histNHcalDetIds_isoMb12, *histSampleEnergy_isoMb12, *histHcalDetIdIEta_isoMb12, *histHcalDetIdIPhi_isoMb12, *histHcalCmsEta_isoMb12, *histHcalCmsPhi_isoMb12, *histHcalWheel_isoMb12, *histHcalSection_isoMb12, *histSumQ_isoMb12, *histNHcalQIESamples_isoMb12, *histHcalQIESample_isoMb12, *histHcalQIESampleAdc_isoMb12, *histHcalQIESampleDv_isoMb12, *histHcalQIESampleEr_isoMb12, *histQIESampleFc_isoMb12, *histQIESamplePedestal_isoMb12, *histQIESampleFc_MPedestals_isoMb12,
		*histNHcalDetIds_notIsoMbMatched, *histSampleEnergy_notIsoMbMatched, *histHcalDetIdIEta_notIsoMbMatched, *histHcalDetIdIPhi_notIsoMbMatched, *histHcalCmsEta_notIsoMbMatched, *histHcalCmsPhi_notIsoMbMatched, *histHcalWheel_notIsoMbMatched, *histHcalSection_notIsoMbMatched, *histSumQ_notIsoMbMatched, *histNHcalQIESamples_notIsoMbMatched, *histHcalQIESample_notIsoMbMatched, *histHcalQIESampleAdc_notIsoMbMatched, *histHcalQIESampleDv_notIsoMbMatched, *histHcalQIESampleEr_notIsoMbMatched, *histQIESampleFc_notIsoMbMatched, *histQIESamplePedestal_notIsoMbMatched, *histQIESampleFc_MPedestals_notIsoMbMatched,
		*histNMuonMatchedHcalDetIds, *histMuonMatchedSampleEnergy, *histMuonMatchedHcalDetIdIEta, *histMuonMatchedHcalDetIdIPhi, *histMuonMatchedHcalCmsEta, *histMuonMatchedHcalCmsPhi, *histMuonMatchedHcalWheel, *histMuonMatchedHcalSection, *histMuonMatchedSumQ, *histNmuonMatchedHcalQIESamples, *histMuonMatchedHcalQIESample, *histMuonMatchedHcalQIESampleAdc, *histMuonMatchedHcalQIESampleDv, *histMuonMatchedHcalQIESampleEr, *histMuonMatchedQIESampleFc, *histMuonMatchedQIESamplePedestal, *histMuonMatchedQIESampleFc_MPedestals, *histMuonMatchedHoDeltaR;

	TH2D *histHcalQIESamples_vs_HcalQIESampleAdc_isoMb1,
		*histHcalQIESamples_vs_HcalQIESampleAdc_isoMb2,
		*histHcalQIESamples_vs_HcalQIESampleAdc_isoMb12,
		*histHcalQIESamples_vs_HcalQIESampleAdc_notIsoMbMatched;

	// Reco Muon Histogram
	TH1D *histMuonMet, *histMuonMt, *histDiMuonMass, *histTagAndProbeDiMuonMass;
	TH1D *histNMuon, *histIsLooseMuon, *histIsMediumMuon, *histIsTightMuon, *histMuonHltIsoMu, *histMuonHltMu, *histMuonPassesSingleMuon, *histMuonCharge, *histMuonIEta, *histMuonHoAbsIEta3Hit, *histDttpHoAbsIEta3Hit, *histMuonHoN3x3Hit, *histDttpHoN3x3Hit;
	TH1D *histMuonE, *histMuonEt, *histMuonPt, *histMuonPtAtIEtaP3, *histMuonPtAtIEtaM3, *histMuonPtFineBinning, *histMuonEta, *histMuonEtaHighPt, *histMuonEtaLowPt, *histMuonPhi, *histMuonIso, *histMuonHltIsoDeltaR, *histMuonDeltaR, *histMuonEtaSt1, *histMuonPhiSt1, *histMuonEtaSt2, *histMuonPhiSt2;
	TH2D *histMuonPt_vs_MuonEta, *histMuonEta_vs_MuonPt, *histMuonEta_vs_MuonPhi, *histNTagMuon_vs_nProbeMuon;
	// Reco Tag Muon
	TH1D *histTagMuonMet, *histTagMuonMt;
	TH1D *histNTagMuon, *histIsLooseTagMuon, *histIsMediumTagMuon, *histIsTightTagMuon, *histTagMuonHltIsoMu, *histTagMuonHltMu, *histTagMuonPassesSingleMuon, *histTagMuonCharge, *histTagMuonIEta, *histTagMuonHoN3x3Hit;
	TH1D *histTagMuonE, *histTagMuonEt, *histTagMuonPt, *histTagMuonPtAtIEtaP3, *histTagMuonPtAtIEtaM3, *histTagMuonPtFineBinning, *histTagMuonEta, *histTagMuonEtaHighPt, *histTagMuonEtaLowPt, *histTagMuonPhi, *histTagMuonIso, *histTagMuonHltIsoDeltaR, *histTagMuonDeltaR, *histTagMuonEtaSt1, *histTagMuonPhiSt1, *histTagMuonEtaSt2, *histTagMuonPhiSt2;
	TH2D *histTagMuonPt_vs_TagMuonEta, *histTagMuonEta_vs_TagMuonPhi, *histTagMuonEta_vs_TagMuonPt;
	// Reco Probe Muon
	TH1D *histProbeMuonMet, *histProbeMuonMt, *histDiProbeMuonMass, *histTagAndProbeDiProbeMuonMass;
	TH1D *histNProbeMuon, *histIsLooseProbeMuon, *histIsMediumProbeMuon, *histIsTightProbeMuon, *histProbeMuonHltIsoMu, *histProbeMuonHltMu, *histProbeMuonPassesSingleMuon, *histProbeMuonCharge, *histProbeMuonIEta, *histProbeMuonHoAbsIEta3Hit, *histProbeMuonHoN3x3Hit;
	TH1D *histProbeMuonE, *histProbeMuonEt, *histProbeMuonPt, *histProbeMuonPtAtIEtaP3, *histProbeMuonPtAtIEtaM3, *histProbeMuonPtFineBinning, *histProbeMuonEta, *histProbeMuonEtaHighPt, *histProbeMuonEtaLowPt, *histProbeMuonPhi, *histProbeMuonIso, *histProbeMuonHltIsoDeltaR, *histProbeMuonDeltaR, *histProbeMuonEtaSt1, *histProbeMuonPhiSt1, *histProbeMuonEtaSt2, *histProbeMuonPhiSt2;
	std::map<int, TH1D*> histProbeMuonMapPt, histProbeMuonMapPtFineBinning, histProbeMuonMapEta, histProbeMuonMapPhi;
	TH2D *histProbeMuonPt_vs_ProbeMuonEta, *histProbeMuonEta_vs_ProbeMuonPhi, *histProbeMuonEta_vs_ProbeMuonPt;

	// HO Coincidence Histogram
	TH1D
		// Dttp Matched Bmtf
		*histBmtfMatchedDttpPhi,
		// Dttp Matched to Hotp
		*histIsDttpMatchedHo, *histIsDttpMatchedHoN3x3, *histIsDttpMatchedHoAbsIEta3,
		*histDttpMatchedHoNumber, *histDttpMatchedHoDeltaIPhi, *histDttpMatchedHoIPhi, *histDttpMatchedHoIEta, *histHoN3x3Hit,
		*histDttpMatchedHoN3x3Hit, *histDttpMatchedHoN3x3Number, *histDttpMatchedHoN3x3DeltaIPhi, *histDttpMatchedHoN3x3IPhi, *histDttpMatchedHoN3x3IEta,
		*histDttpMatchedHoAbsIEta3Number, *histDttpMatchedHoAbsIEta3DeltaIPhi, *histDttpMatchedHoAbsIEta3IPhi, *histDttpMatchedHoAbsIEta3IEta,
		*histDttpMatchedHoHighADCNumber, *histDttpMatchedHoHighADCDeltaIPhi, *histDttpMatchedHoHighADCIPhi, *histDttpMatchedHoHighADCIEta,
		// Only DTTP at MB1/2
		*histDttpMb1MatchedHoNumber, *histDttpMb1MatchedHoDeltaIPhi, *histDttpMb1MatchedHoIPhi, *histDttpMb1MatchedHoIEta,
		*histDttpMb2MatchedHoNumber, *histDttpMb2MatchedHoDeltaIPhi, *histDttpMb2MatchedHoIPhi, *histDttpMb2MatchedHoIEta,
		*histDttpMb12MatchedHoNumber, *histDttpMb12MatchedHoDeltaIPhi, *histDttpMb12MatchedHoIPhi, *histDttpMb12MatchedHoIEta,
		// Only DTTP at MB1/2 and HoN3x3 cut
		*histDttpMb1MatchedHoN3x3Number, *histDttpMb1MatchedHoN3x3DeltaIPhi, *histDttpMb1MatchedHoN3x3IPhi, *histDttpMb1MatchedHoN3x3IEta,
		*histDttpMb2MatchedHoN3x3Number, *histDttpMb2MatchedHoN3x3DeltaIPhi, *histDttpMb2MatchedHoN3x3IPhi, *histDttpMb2MatchedHoN3x3IEta,
		*histDttpMb12MatchedHoN3x3Number, *histDttpMb12MatchedHoN3x3DeltaIPhi, *histDttpMb12MatchedHoN3x3IPhi, *histDttpMb12MatchedHoN3x3IEta,
		// Only DTTP at MB1/2 and iEta==+-3
		*histDttpMb1MatchedHoAbsIEta3Number, *histDttpMb1MatchedHoAbsIEta3DeltaIPhi, *histDttpMb1MatchedHoAbsIEta3IPhi, *histDttpMb1MatchedHoAbsIEta3IEta,
		*histDttpMb2MatchedHoAbsIEta3Number, *histDttpMb2MatchedHoAbsIEta3DeltaIPhi, *histDttpMb2MatchedHoAbsIEta3IPhi, *histDttpMb2MatchedHoAbsIEta3IEta,
		*histDttpMb12MatchedHoAbsIEta3Number, *histDttpMb12MatchedHoAbsIEta3DeltaIPhi, *histDttpMb12MatchedHoAbsIEta3IPhi, *histDttpMb12MatchedHoAbsIEta3IEta,
		// Only DTTP at MB1/2 and HOTP has high ADC count
		*histDttpMb1MatchedHoHighADCNumber, *histDttpMb1MatchedHoHighADCDeltaIPhi, *histDttpMb1MatchedHoHighADCIPhi, *histDttpMb1MatchedHoHighADCIEta,
		*histDttpMb2MatchedHoHighADCNumber, *histDttpMb2MatchedHoHighADCDeltaIPhi, *histDttpMb2MatchedHoHighADCIPhi, *histDttpMb2MatchedHoHighADCIEta,
		*histDttpMb12MatchedHoHighADCNumber, *histDttpMb12MatchedHoHighADCDeltaIPhi, *histDttpMb12MatchedHoHighADCIPhi, *histDttpMb12MatchedHoHighADCIEta,

		// Matching of isoMB1 (Hotp matched with DTTP) to reco muons.. The histogram should only be filled if muons are not Tf matched
		*histIsBmtfMatchedDttp, *histIsDttpMatchedMuon,
		*histIsoMb1MatchedMuonPt,  *histIsoMb1MatchedMuonPtFineBinning,  *histIsoMb1MatchedMuonEta,  *histIsoMb1MatchedMuonPhi,  *histIsoMb1MatchedMuonDeltaR,  *histIsoMb1MatchedMuonDeltaEta,  *histIsoMb1MatchedMuonDeltaPhi,
		*histIsoMb2MatchedMuonPt,  *histIsoMb2MatchedMuonPtFineBinning,  *histIsoMb2MatchedMuonEta,  *histIsoMb2MatchedMuonPhi,  *histIsoMb2MatchedMuonDeltaR,  *histIsoMb2MatchedMuonDeltaEta,  *histIsoMb2MatchedMuonDeltaPhi,
		*histIsoMb12MatchedMuonPt, *histIsoMb12MatchedMuonPtFineBinning, *histIsoMb12MatchedMuonEta, *histIsoMb12MatchedMuonPhi, *histIsoMb12MatchedMuonDeltaR, *histIsoMb12MatchedMuonDeltaEta, *histIsoMb12MatchedMuonDeltaPhi,

		*histIsoMb1MatchedMuonN3x3Pt,  *histIsoMb1MatchedMuonN3x3PtFineBinning,  *histIsoMb1MatchedMuonN3x3Eta,  *histIsoMb1MatchedMuonN3x3Phi,
		*histIsoMb2MatchedMuonN3x3Pt,  *histIsoMb2MatchedMuonN3x3PtFineBinning,  *histIsoMb2MatchedMuonN3x3Eta,  *histIsoMb2MatchedMuonN3x3Phi,
		*histIsoMb12MatchedMuonN3x3Pt, *histIsoMb12MatchedMuonN3x3PtFineBinning, *histIsoMb12MatchedMuonN3x3Eta, *histIsoMb12MatchedMuonN3x3Phi,

		*histIsoMb1MatchedMuonAbsIEta3Pt,  *histIsoMb1MatchedMuonAbsIEta3PtFineBinning,  *histIsoMb1MatchedMuonAbsIEta3Eta,  *histIsoMb1MatchedMuonAbsIEta3Phi,
		*histIsoMb2MatchedMuonAbsIEta3Pt,  *histIsoMb2MatchedMuonAbsIEta3PtFineBinning,  *histIsoMb2MatchedMuonAbsIEta3Eta,  *histIsoMb2MatchedMuonAbsIEta3Phi,
		*histIsoMb12MatchedMuonAbsIEta3Pt, *histIsoMb12MatchedMuonAbsIEta3PtFineBinning, *histIsoMb12MatchedMuonAbsIEta3Eta, *histIsoMb12MatchedMuonAbsIEta3Phi,

		*histIsoMb1MatchedMuonHighADCPt,  *histIsoMb1MatchedMuonHighADCPtFineBinning,  *histIsoMb1MatchedMuonHighADCEta,  *histIsoMb1MatchedMuonHighADCPhi,
		*histIsoMb2MatchedMuonHighADCPt,  *histIsoMb2MatchedMuonHighADCPtFineBinning,  *histIsoMb2MatchedMuonHighADCEta,  *histIsoMb2MatchedMuonHighADCPhi,
		*histIsoMb12MatchedMuonHighADCPt, *histIsoMb12MatchedMuonHighADCPtFineBinning, *histIsoMb12MatchedMuonHighADCEta, *histIsoMb12MatchedMuonHighADCPhi,

		*histDttpMb1MatchedHoAbsIEta3CmsPhi, *histDttpMb1MatchedHoAbsIEta3CmsEta,
		*histDttpMb2MatchedHoAbsIEta3CmsPhi, *histDttpMb2MatchedHoAbsIEta3CmsEta,
		*histDttpMb12MatchedHoAbsIEta3CmsPhi, *histDttpMb12MatchedHoAbsIEta3CmsEta,
		*histBmtfMatchedDttpCmsPt, *histBmtfMatchedDttpDeltaPhi, *histBmtfMatchedDttpCmsPhi, *histBmtfMatchedDttpDeltaPhiSt1, *histBmtfMatchedDttpDeltaPhiSt2, *histBmtfMatchedDttpDeltaPhiSt3, *histBmtfMatchedDttpDeltaPhiSt4,
		*histDttpMatchedMuonDeltaR,

		// DTTP in MB34 matched to HOTP (not really used at the moment)
		*histIsMb3HoIEtaMatched, *histIsMb4HoIEtaMatched,
		*histBmtfMb34MatchedHoIEta, *histBmtfMb34MatchedHoIPhi, *histBmtfMb34MatchedHoDeltaIPhi,
		*histBmtfMb34MatchedHoDeltaR, *histBmtfMb34MatchedHoPt, *histBmtfMb34MatchedHoPtFineBinning, *histBmtfMb34MatchedHoCmsEta, *histBmtfMb34MatchedHoCmsPhi, *histBmtfMb34MatchedHoDeltaPhi, *histBmtfMb34MatchedMuonPt, *histBmtfMb34MatchedMuonPtFineBinning, *histBmtfMb34MatchedMuonEta, *histBmtfMb34MatchedMuonPhi, *histBmtfMb34MatchedMuonDeltaPhi, *histBmtfMb34MatchedHoNumber;
	std::map<int, TH1D*> histTfMapMatchedMuonPt, histTfMapMatchedMuonPtFineBinning, histTfMapMatchedMuonEta, histTfMapMatchedMuonPhi, histTfMapMatchedMuonTfType;

	//XvsY
	TH2D *histBmtfMatchedMuonPt_vs_MuonEta, *histBmtfMatchedMuonEta_vs_MuonPt, *histBmtfMatchedMuonEta_vs_MuonPhi,
		*histIsoMb1MatchedMuonEta_vs_MuonPt, *histIsoMb2MatchedMuonEta_vs_MuonPt, *histIsoMb12MatchedMuonEta_vs_MuonPt,
		*histIsoMb1MatchedMuonEta_vs_MuonPhi, *histIsoMb2MatchedMuonEta_vs_MuonPhi, *histIsoMb12MatchedMuonEta_vs_MuonPhi,
		*histIsoMb1MatchedMuonN3x3Eta_vs_MuonPt, *histIsoMb2MatchedMuonN3x3Eta_vs_MuonPt, *histIsoMb12MatchedMuonN3x3Eta_vs_MuonPt,
		*histIsoMb1MatchedMuonN3x3Eta_vs_MuonPhi, *histIsoMb2MatchedMuonN3x3Eta_vs_MuonPhi, *histIsoMb12MatchedMuonN3x3Eta_vs_MuonPhi,
		*histIsoMb1MatchedMuonAbsIEta3Eta_vs_MuonPt, *histIsoMb2MatchedMuonAbsIEta3Eta_vs_MuonPt, *histIsoMb12MatchedMuonAbsIEta3Eta_vs_MuonPt,
		*histIsoMb1MatchedMuonAbsIEta3Eta_vs_MuonPhi, *histIsoMb2MatchedMuonAbsIEta3Eta_vs_MuonPhi, *histIsoMb12MatchedMuonAbsIEta3Eta_vs_MuonPhi,
		*histIsoMb1MatchedMuonHighADCEta_vs_MuonPt, *histIsoMb2MatchedMuonHighADCEta_vs_MuonPt, *histIsoMb12MatchedMuonHighADCEta_vs_MuonPt,
		*histIsoMb1MatchedMuonHighADCEta_vs_MuonPhi, *histIsoMb2MatchedMuonHighADCEta_vs_MuonPhi, *histIsoMb12MatchedMuonHighADCEta_vs_MuonPhi,
		*histHcalQIESamples_vs_HcalQIESampleAdc;

	std::map<int, TH2D*> histTfMatchedMuonPt_vs_MuonEta, histTfMatchedMuonEta_vs_MuonPt, histTfMatchedMuonEta_vs_MuonPhi;
};

