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
	std::vector<bool> dttpIsHq,
		dttpIsLq;
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
	std::vector<bool> isDttpMatchedBmtf,
		isBmtfMatchedDttp;
	std::vector<std::vector<int>> bmtfMatchedDttpIndices;
	std::vector<int> bmtfMatchedDttpWheel,
		bmtfMatchedDttpSection,
		bmtfMatchedDttpStation,
		bmtfMatchedDttpIndex;
	std::vector<double> bmtfMatchedDttpDeltaPhi,
		bmtfMatchedDttpPt,
		bmtfMatchedDttpPhi,
		bmtfMatchedDttpCmsPhi;
	std::vector<std::vector<double>> bmtfMatchedDttpDeltaPhiPerStation;
	std::vector<std::vector<int>> bmtfMatchedDttpIndexPerStation;
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
	// Used Muons
	unsigned short nUsedMuon;
	std::vector<bool> isMediumUsedMuon,
		usedMuonHltIsoMu,
		usedMuonHltMu,
		usedMuonPassesSingleMuon,
		usedMuonHasMb1;
	std::vector<int> usedMuonCharge,
		usedMuonIEta;
	std::vector<float> usedMuonE,
		usedMuonEt,
		usedMuonPt,
		usedMuonEta,
		usedMuonPhi,
		usedMuonIso,
		usedMuonHltIsoDeltaR,
		usedMuonDeltaR,
		usedMuonEtaSt1,
		usedMuonPhiSt1,
		usedMuonEtaSt2,
		usedMuonPhiSt2;
	std::vector<double> usedMuonMet,
		usedMuonMt;
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
	std::vector<int> bmtfMatchedMuonCharge;
	std::vector<unsigned short> bmtfMatchedMuonIndex,
		muonMatchedBmtfIndex;
	std::vector<bool> isMuonMatchedBmtf,
		isBmtfMatchedMuon;
	// Matching MB34 with HO
	std::vector<double> bmtfMb34MatchedHoDeltaR,
		bmtfMb34MatchedHoPt,
		bmtfMb34MatchedHoCmsEta,
		bmtfMb34MatchedHoCmsPhi,
		bmtfMb34MatchedHoDeltaPhi,
		bmtfMb3MatchedHoDeltaPhi,
		bmtfMb4MatchedHoDeltaPhi,
		bmtfMb34MatchedMuonPt,
		bmtfMb34MatchedMuonEta,
		bmtfMb34MatchedMuonPhi,
		bmtfMb34MatchedMuonDeltaPhi;
	std::vector<int> bmtfMb34MatchedHoIEta,
		bmtfMb34MatchedHoIPhi,
		bmtfMb34MatchedHoDeltaIPhi,
		bmtfMb3MatchedHoIPhi,
		bmtfMb3MatchedHoDeltaIPhi,
		bmtfMb4MatchedHoIPhi,
		bmtfMb4MatchedHoDeltaIPhi;
	std::vector<unsigned int> bmtfMb34MatchedHoIndex,
		bmtfMb3MatchedHoIndex,
		bmtfMb4MatchedHoIndex;
	std::vector<bool> isBmtfMb34HoMatched,
		isMb3HoIEtaMatched,
		isMb4HoIEtaMatched;
	// DTTP matching HO
	std::vector<bool> isDttpMatchedHo;
	std::vector<int> dttpMatchedHoDeltaIPhi,
		dttpMatchedHoIPhi,
		dttpMatchedHoIEta;
	std::vector<unsigned int> dttpMatchedHoIndex;
	std::vector<double> dttpMatchedHoCmsPhi,
		dttpMatchedHoCmsEta,
		dttpMatchedHoDeltaPhi;
	// DTTP matching Muon
	std::vector<bool> isMuonMatchedDttp,
		isDttpMatchedMuon;
	std::vector<unsigned short> dttpMatchedMuonIndex,
		dttpMatchedBmtfIndex;
	std::vector<double> dttpMatchedMuonDeltaR;
	// Reco Muon matching Ho
	std::vector<int> muonMatchedDttpNHo3x3Hit,
		muonMatchedDttpIndex;

};

