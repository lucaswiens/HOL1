#pragma once

#include <vector>

class HoProduct {
public:
	HoProduct(){};
	~HoProduct(){};
	// DTTP Variables
	int dttpSize;
	std::vector<int> dttpBx,
		dttpWheel,
		dttpSection,
		dttpStation,
		dttpQualityCode,
		dttpTs2Tag,
		dttpIPhi;
	std::vector<float> dttpPt,
		dttpPhi,
		dttpPhiB;
	std::vector<double> dttpCmsPhi;
	std::vector<bool> dttpIsHq;
	// Track Finder Muons
	unsigned short bmtfSize;
	std::vector<int> bmtfTrackType;
	std::vector<short> bmtfBx,
		bmtfGlobalPhi,
		bmtfPt,
		bmtfEta;
	std::vector<double> bmtfCmsPt,
		bmtfCmsEta,
		bmtfCmsPhi;
	std::vector<std::vector<int>> bmtfTrackerAddresses;
	// HO Variables
	double sumQ;
	unsigned int nHcalDetIds, nHcalQIESamples;
	std::vector<int> hcalIEta,
		hcalIPhi,
		hcalQIESample,
		hcalQIESampleAdc,
		hcalQIESampleDv,
		hcalQIESampleEr,
		hcalWheel,
		hcalSection;
	std::vector<float> SampleEnergy,
		QIESampleFc,
		QIESamplePedestal,
		QIESampleFc_MPedestals,
		hcalCmsPhi,
		hcalCmsEta;
	// Matching tfMuon (BMTF output) with DTTP (BMTF input)
	std::vector<bool> isBmtfMatchedDttp;
	std::vector<std::vector<int>> bmtfMatchedDttpIndices;
	std::vector<int> bmtfMatchedDttpWheel,
		bmtfMatchedDttpSection,
		bmtfMatchedDttpStation;
	std::vector<double> bmtfMatchedDttpDeltaPhi,
		bmtfMatchedDttpPt,
		bmtfMatchedDttpPhi,
		bmtfMatchedDttpCmsPhi;
	// Reco Muons
	unsigned short nMuon;
	std::vector<bool> isLooseMuon,
		isMediumMuon,
		isTightMuon,
		muonHltIsoMu,
		muonHltMu,
		muonPassesSingleMuon,
		muonHasMb1;
	std::vector<int> muonCharge,
		muonIEta;
	std::vector<float> muonE,
		muonEt,
		muonPt,
		muonEta,
		muonPhi,
		muonIso,
		muonHltIsoDeltaR,
		muonDeltaR,
		muonEtaSt1,
		muonPhiSt1,
		muonEtaSt2,
		muonPhiSt2;
	std::vector<double> muonMet,
		muonMt;
	// Unused Muons
	unsigned short nUnusedMuon;
	std::vector<bool> isMediumUnusedMuon,
		unusedMuonHltIsoMu,
		unusedMuonHltMu,
		unusedMuonPassesSingleMuon,
		unusedMuonHasMb1;
	std::vector<int> unusedMuonCharge,
		unusedMuonIEta;
	std::vector<float> unusedMuonE,
		unusedMuonEt,
		unusedMuonPt,
		unusedMuonEta,
		unusedMuonPhi,
		unusedMuonIso,
		unusedMuonHltIsoDeltaR,
		unusedMuonDeltaR,
		unusedMuonEtaSt1,
		unusedMuonPhiSt1,
		unusedMuonEtaSt2,
		unusedMuonPhiSt2;
	std::vector<double> unusedMuonMet,
		unusedMuonMt;
	// Matching tfMuon (BMTF output) with Reco Muon
	std::vector<double> bmtfMatchedMuonDeltaR,
		bmtfMatchedMuonPt,
		bmtfMatchedMuonEta,
		bmtfMatchedMuonPhi,
		bmtfMatchedMuonTrackType,
		bmtfMatchedMuonDeltaPhi;
	std::vector<int> bmtfMatchedMuonCharge,
		bmtfMatchedMuonIndex;
	std::vector<bool> isBmtfMatchedMuon;
	// Matching MB34 with HO
	std::vector<double> bmtfMb34MatchedHoDeltaR,
		bmtfMb34MatchedHoPt,
		bmtfMb34MatchedHoCmsEta,
		bmtfMb34MatchedHoCmsPhi,
		bmtfMb34MatchedHoDeltaPhi,
		bmtfMb34MatchedMuonPt,
		bmtfMb34MatchedMuonEta,
		bmtfMb34MatchedMuonPhi,
		bmtfMb34MatchedMuonDeltaPhi;
	std::vector<int> bmtfMb34MatchedHoIEta,
		bmtfMb34MatchedHoIPhi,
		bmtfMb34MatchedHoDeltaIPhi;
	std::vector<bool> isMb3HoIEtaMatched,
		isMb4HoIEtaMatched;
	// DTTP matching HO
	std::vector<bool> isDttpMatchedHo;
	std::vector<int> dttpMatchedHoDeltaIPhi,
		dttpMatchedHoIPhi,
		dttpMatchedHoIEta;
	std::vector<double> dttpMatchedHoCmsPhi,
		dttpMatchedHoCmsEta;
	// DTTP matching Muon
	std::vector<bool> isDttpMatchedMuon;
	// Reco Muon matching Ho
	std::vector<int> nHo3x3Hit;

};
