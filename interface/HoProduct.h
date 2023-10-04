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
	std::vector<float> dttpCmsPt,
		dttpPhi,
		dttpPhiB;
	std::vector<double> dttpCmsPhi;
	std::vector<bool> dttpIsHq,
		dttpIsLq;
	// Track Finder Muons BMTF=0; OMTF=1; EMTF=2
	std::map<int, unsigned short> tfMuonSize = {{0, 0}, {1, 0}, {2, 0}};
	std::map<int, std::vector<int>> tfMuonTrackType = {{0, {}}, {1, {}}, {2, {}}},
		tfMuonQuality = {{0, {}}, {1, {}}, {2, {}}};
	std::map<int, std::vector<short>> tfMuonBx = {{0, {}}, {1, {}}, {2, {}}},
		tfMuonGlobalPhi = {{0, {}}, {1, {}}, {2, {}}},
		tfMuonPt = {{0, {}}, {1, {}}, {2, {}}},
		tfMuonEta = {{0, {}}, {1, {}}, {2, {}}};
	std::map<int, std::vector<double>> tfMuonCmsPt = {{0, {}}, {1, {}}, {2, {}}},
		tfMuonCmsEta = {{0, {}}, {1, {}}, {2, {}}},
		tfMuonCmsPhi = {{0, {}}, {1, {}}, {2, {}}};
	std::map<int, std::vector<std::vector<int>>> tfMuonTrackerAddresses = {{0, {}}, {1, {}}, {2, {}}};

	// Track Finder Muons (uGMT)
	unsigned short nUGMTMuons;
	std::vector<int> uGMTMuonTrackType,
		uGMTMuonQuality;
	std::vector<short> uGMTMuonBx,
		uGMTMuonGlobalPhi,
		uGMTMuonPt,
		uGMTMuonEta;
	std::vector<double> uGMTMuonCmsPt,
		uGMTMuonCmsEta,
		uGMTMuonCmsPhi;
	//std::map<int, std::vector<std::vector<int>>> tfMuonTrackerAddresses;

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
		bmtfMatchedDttpCmsPt,
		bmtfMatchedDttpPhi,
		bmtfMatchedDttpCmsPhi;
	std::vector<std::vector<double>> bmtfMatchedDttpDeltaPhiPerStation;
	std::vector<std::vector<int>> bmtfMatchedDttpIndexPerStation;
	int tagMuonMatchedBmtfIndex;

	// Reco Muons
	unsigned short nMuon;
	std::vector<bool> isLooseMuon,
		isMediumMuon,
		isTightMuon,
		muonHltIsoMu,
		muonHltMu,
		muonPassesSingleMuon,
		muonHasMb1,
		muonHasMb2;
	std::vector<int> muonCharge,
		muonIEta,
		muonIPhi,
		muonHoN3x3Hit;
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
	// Tag Muons
	unsigned short nTagMuon;
	std::vector<bool> isLooseTagMuon,
		isMediumTagMuon,
		isTightTagMuon,
		tagMuonHltIsoMu,
		tagMuonHltMu,
		tagMuonPassesSingleMuon,
		tagMuonHasMb1,
		tagMuonHasMb2;
	std::vector<int> tagMuonCharge,
		tagMuonIEta,
		tagMuonHoN3x3Hit;
	std::vector<float> tagMuonE,
		tagMuonEt,
		tagMuonPt,
		tagMuonEta,
		tagMuonPhi,
		tagMuonIso,
		tagMuonHltIsoDeltaR,
		tagMuonDeltaR,
		tagMuonEtaSt1,
		tagMuonPhiSt1,
		tagMuonEtaSt2,
		tagMuonPhiSt2;
	std::vector<double> tagMuonMet,
		tagMuonMt;
	// Probe Muons
	unsigned short nProbeMuon;
	std::vector<bool> isLooseProbeMuon,
		isMediumProbeMuon,
		isTightProbeMuon,
		probeMuonHltIsoMu,
		probeMuonHltMu,
		probeMuonPassesSingleMuon,
		probeMuonHasMb1,
		probeMuonHasMb2;
	std::vector<int> probeMuonCharge,
		probeMuonIEta,
		probeMuonIPhi,
		probeMuonHoN3x3Hit;
	std::vector<float> probeMuonE,
		probeMuonEt,
		probeMuonPt,
		probeMuonEta,
		probeMuonPhi,
		probeMuonIso,
		probeMuonHltIsoDeltaR,
		probeMuonDeltaR,
		probeMuonEtaSt1,
		probeMuonPhiSt1,
		probeMuonEtaSt2,
		probeMuonPhiSt2;
	std::vector<double> probeMuonMet,
		probeMuonMt;

	// Matching tfMuon (BMTF output) with Reco Muon
	//std::vector<double> bmtfMatchedMuonDeltaR,
	//	bmtfMatchedMuonPt,
	//	bmtfMatchedMuonEta,
	//	bmtfMatchedMuonPhi,
	//	bmtfMatchedMuonTrackType,
	//	bmtfMatchedMuonDeltaPhi;
	//std::vector<int> bmtfMatchedMuonCharge;
	//std::vector<unsigned short> bmtfMatchedMuonIndex,
	//	muonMatchedBmtfIndex;
	//std::vector<double> muonMatchedBmtfCmsPt,
	//	muonMatchedBmtfCmsEta;
	//std::vector<bool> isMuonMatchedBmtf,
	//	isBmtfMatchedMuon;
	// Matching tfMuon (TF output) with Reco Muon
	std::map<int, std::vector<double>> tfMatchedMuonDeltaR,
		tfMatchedMuonPt,
		tfMatchedMuonEta,
		tfMatchedMuonPhi,
		tfMatchedMuonTrackType,
		tfMatchedMuonDeltaPhi;
	std::map<int, std::vector<int>> tfMatchedMuonCharge,
		tfMatchedMuonTfType;
	std::map<int, std::vector<unsigned short>> tfMatchedMuonIndex,
		muonMatchedTfIndex;
	std::map<int, std::vector<bool>> isTfMatchedMuon;
	std::vector<bool> isMuonMatchedTf;

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
	std::vector<int> bmtfMb34MatchedHoNumber,
		bmtfMb34MatchedHoIEta,
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
	std::vector<bool> isDttpMatchedHo,
		isHoMatchedDttp;
	std::vector<int> hoMatchedDttpIndex,
		dttpMatchedHoDeltaIPhi,
		hoMatchedDttpDeltaIPhi,
		dttpMatchedHoIPhi,
		dttpMatchedHoIEta,
		dttpHoN3x3Hit;
	std::vector<unsigned int> dttpMatchedHoIndex;
	std::vector<double> dttpMatchedHoCmsPt,
		hoMatchedDttpDeltaPhi,
		dttpMatchedHoCmsPhi,
		dttpMatchedHoCmsEta,
		dttpMatchedHoDeltaPhi;
	// DTTP and HO matching Muon
	std::vector<bool> isMuonMatchedDttp,
		isDttpMatchedMuon;
	std::vector<unsigned short> dttpMatchedMuonIndex,
		dttpMatchedBmtfIndex;
	std::vector<double> dttpMatchedMuonDeltaR,
		dttpMatchedMuonDeltaPhi,
		dttpMatchedMuonDeltaEta;
	std::vector<int> dttpMatchedMuonHoN3x3Hit;
	// Reco Muon matching Ho
	std::vector<int> muonMatchedDttpHoN3x3Hit,
		muonMatchedDttpIndex;
	// HO matched Muon
	std::vector<bool> isMuonMatchedHo,
		isHoMatchedMuon;
	std::vector<double> hoMatchedMuonDeltaR,
		muonMatchedHoDeltaR,
		hoMatchedMuonDeltaPhi,
		hoMatchedMuonDeltaEta;
	std::vector<unsigned int> muonMatchedHoIndex;
	std::vector<unsigned short> hoMatchedMuonIndex;
	std::vector<int> muonMatchedHoN3x3Hit,
		hoMatchedMuonHoN3x3Hit;

};

