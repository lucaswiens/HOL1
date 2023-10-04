#include <HOAnalysis/HOL1/interface/HoHistogramCollection.h>
#include<iostream>
#include <iomanip>
#include <limits>

HoHistogramCollection::HoHistogramCollection(const bool &hasRecoMuon) : hasRecoMuon(hasRecoMuon) {
	double minE   =   0, minPt   =   0, minMass =   0, minPtVs   =   0, minPhi   = -M_PI, minEta   = -2.0*M_PI/72.0 * 28, minWheel   = -3, minStation   = 1, minSection   =  0, minQualityCode   =  0, minDeltaR   =  0, minTrackType   =  0, minIPhi   =  1, minIEta   = -20;
	double maxE   = 250, maxPt   = 250, maxMass = 250, maxPtVs   = 150, maxPhi   =  M_PI, maxEta   =  2.0*M_PI/72.0 * 28, maxWheel   =  4, maxStation   = 5, maxSection   = 12, maxQualityCode   = 20, maxDeltaR   =  1, maxTrackType   = 25, maxIPhi   = 73, maxIEta   =  20;
	int    nBinsE = 500, nBinsPt = 500, nMass   = 500, nBinsPtVs =  30, nBinsPhi =    31, nBinsEta =                  56, nBinsWheel =  7, nBinsStation = 4, nBinsSection = 12, nBinsQualityCode = 20, nBinsDeltaR = 30, nBinsTrackType = 25, nBinsIPhi = 72, nBinsIEta =  40;
	double ptBinning[24] = {0., 2., 3., 4., 5., 6., 7., 8., 10., 12., 14., 16., 18., 20., 22., 25., 30., 35., 45., 60., 75., 100., 140., 150};

	// For some reason root will not choose the correct equidistant binning, probably some easy mistake.. But like this it works.
	double etaBinning[57] = {-2.44346, -2.35619, -2.26893, -2.18166, -2.0944, -2.00713, -1.91986, -1.8326, -1.74533, -1.65806, -1.5708, -1.48353, -1.39626, -1.309, -1.22173, -1.13446, -1.0472, -0.959931, -0.872665, -0.785398, -0.698132, -0.610865, -0.523599, -0.436332, -0.349066, -0.261799, -0.174533, -0.0872665, 0, 0.0872665, 0.174533, 0.261799, 0.349066, 0.436332, 0.523599, 0.610865, 0.698132, 0.785398, 0.872665, 0.959931, 1.0472, 1.13446, 1.22173, 1.309, 1.39626, 1.48353, 1.5708, 1.65806, 1.74533, 1.8326, 1.91986, 2.00713, 2.0944, 2.18166, 2.26893, 2.35619, 2.44346};
	/* This code was used to get the bin edges
	nBinsEta = 56;
	double binwidth = (maxEta - minEta) / nBinsEta;
	for (int i = -nBinsEta/2; i < nBinsEta/2+1; i++) { std::cout << i * binwidth << ", ";}
	std::exit(1);
	*/

	// Number of Events
	numberOfEvents = new TH1D("numberOfEvents", "", 1, 0, 1);
	histBmtfNumber = new TH1D("bmtfNumber", "", 1, 0, 1);
	histDttpMatchedHoNumber = new TH1D("dttpMatchedHoNumber", "", 1, 0, 1);
	histDttpMatchedHoN3x3Number = new TH1D("dttpMatchedHoN3x3Number", "", 1, 0, 1);
	histDttpMatchedHoAbsIEta3Number = new TH1D("dttpMatchedHoAbsIEta3Number", "", 1, 0, 1);
	histDttpMatchedHoHighADCNumber = new TH1D("dttpMatchedHoHighADCNumber", "", 1, 0, 1);

	histDttpMb1MatchedHoNumber = new TH1D("dttpMb1MatchedHoNumber", "", 1, 0, 1);
	histDttpMb2MatchedHoNumber = new TH1D("dttpMb2MatchedHoNumber", "", 1, 0, 1);
	histDttpMb12MatchedHoNumber = new TH1D("dttpMb12MatchedHoNumber", "", 1, 0, 1);

	histDttpMb1MatchedHoN3x3Number = new TH1D("dttpMb1MatchedHoN3x3Number", "", 1, 0, 1);
	histDttpMb2MatchedHoN3x3Number = new TH1D("dttpMb2MatchedHoN3x3Number", "", 1, 0, 1);
	histDttpMb12MatchedHoN3x3Number = new TH1D("dttpMb12MatchedHoN3x3Number", "", 1, 0, 1);

	histDttpMb1MatchedHoAbsIEta3Number = new TH1D("dttpMb1MatchedHoAbsIEta3Number", "", 1, 0, 1);
	histDttpMb2MatchedHoAbsIEta3Number = new TH1D("dttpMb2MatchedHoAbsIEta3Number", "", 1, 0, 1);
	histDttpMb12MatchedHoAbsIEta3Number = new TH1D("dttpMb12MatchedHoAbsIEta3Number", "", 1, 0, 1);

	histDttpMb1MatchedHoHighADCNumber = new TH1D("dttpMb1MatchedHoHighADCNumber", "", 1, 0, 1);
	histDttpMb2MatchedHoHighADCNumber = new TH1D("dttpMb2MatchedHoHighADCNumber", "", 1, 0, 1);
	histDttpMb12MatchedHoHighADCNumber = new TH1D("dttpMb12MatchedHoHighADCNumber", "", 1, 0, 1);

	histBmtfMb34MatchedHoNumber = new TH1D("bmtfMb34MatchedHoNumber", "", 1, 0, 1);
	//histNumber = new TH1D("Number", "", 1, 0, 1);

	// Muon Histograms
	if (hasRecoMuon) {
		// Reco Muons
		histNMuon = new TH1D("nMuon", "", 10, 0, 10);
		histIsLooseMuon = new TH1D("isLooseMuon", "", 2, 0, 2);
		histIsMediumMuon = new TH1D("isMediumMuon", "", 2, 0, 2);
		histIsTightMuon = new TH1D("isTightMuon", "", 2, 0, 2);

		histMuonE = new TH1D("muonE", "", nBinsE, minE, maxE);
		histMuonEt = new TH1D("muonEt", "", nBinsE, minE, maxE);
		histMuonPt = new TH1D("muonPt", "", 23, ptBinning);
		histMuonPtFineBinning = new TH1D("muonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histMuonEta = new TH1D("muonEta", "", nBinsEta, etaBinning);
		histMuonPhi = new TH1D("muonPhi", "", nBinsPhi, minPhi, maxPhi);
		histMuonIso = new TH1D("muonIso", "", 100, 0, 1);
		histMuonHltIsoDeltaR = new TH1D("muonHlt_isoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histMuonDeltaR = new TH1D("muonHlt_deltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histMuonEtaSt1 = new TH1D("muonEtaSt1", "", nBinsEta, etaBinning);
		histMuonPhiSt1 = new TH1D("muonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histMuonEtaSt2 = new TH1D("muonEtaSt2", "", nBinsEta, etaBinning);
		histMuonPhiSt2 = new TH1D("muonPhiSt2", "", nBinsPhi, minPhi, maxPhi);

		histDiMuonMass = new TH1D("diMuonMass", "", nMass, minMass, maxMass);
		histTagAndProbeDiMuonMass = new TH1D("tagAndProbeDiMuonMass", "", nMass, minMass, maxMass); // Not used atm

		histMuonPt_vs_MuonEta = new TH2D("muonPt_vs_MuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, etaBinning);
		histMuonEta_vs_MuonPt = new TH2D("muonEta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histMuonEta_vs_MuonPhi = new TH2D("muonEta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histNTagMuon_vs_nProbeMuon = new TH2D("nTagMuon_vs_nProbeMuon", "", 10, 0, 10, 10, 0, 10);

		histMuonMet = new TH1D("muonMet", "", 23, ptBinning);
		histMuonMt = new TH1D("muonMt", "", 23, ptBinning);

		histMuonHltIsoMu = new TH1D("muonHlt_isomu", "", 2, 0, 2);
		histMuonHltMu = new TH1D("muonHlt_mu", "", 2, 0, 2);
		histMuonPassesSingleMuon = new TH1D("muonPassesSingleMuon", "", 2, 0, 2);
		histMuonCharge = new TH1D("muonCharge", "", 3, -1, 2);
		histMuonIEta = new TH1D("muonIEta", "", nBinsIEta, minIEta, maxIEta);
		histMuonHoN3x3Hit = new TH1D("muonHoN3x3Hit", "", 10, 0, 10);
		histMuonHoAbsIEta3Hit = new TH1D("muonHoAbsIEta3Hit", "", 10, 0, 10);

		// Reco Tag Muons
		histNTagMuon = new TH1D("nTagMuon", "", 10, 0, 10);
		histIsLooseTagMuon = new TH1D("isLooseTagMuon", "", 2, 0, 2);
		histIsMediumTagMuon = new TH1D("isMediumTagMuon", "", 2, 0, 2);
		histIsTightTagMuon = new TH1D("isTightTagMuon", "", 2, 0, 2);

		histTagMuonE = new TH1D("tagMuonE", "", nBinsE, minE, maxE);
		histTagMuonEt = new TH1D("tagMuonEt", "", nBinsE, minE, maxE);
		histTagMuonPt = new TH1D("tagMuonPt", "", 23, ptBinning);
		histTagMuonPtFineBinning = new TH1D("tagMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histTagMuonEta = new TH1D("tagMuonEta", "", nBinsEta, etaBinning);
		histTagMuonPhi = new TH1D("tagMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histTagMuonIso = new TH1D("tagMuonIso", "", 100, 0, 1);
		histTagMuonHltIsoDeltaR = new TH1D("tagMuonHlt_isoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histTagMuonDeltaR = new TH1D("tagMuonHlt_deltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histTagMuonEtaSt1 = new TH1D("tagMuonEtaSt1", "", nBinsEta, etaBinning);
		histTagMuonPhiSt1 = new TH1D("tagMuonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histTagMuonEtaSt2 = new TH1D("tagMuonEtaSt2", "", nBinsEta, etaBinning);
		histTagMuonPhiSt2 = new TH1D("tagMuonPhiSt2", "", nBinsPhi, minPhi, maxPhi);

		histTagMuonPt_vs_TagMuonEta = new TH2D("tagMuonPt_vs_TagMuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, etaBinning);
		histTagMuonEta_vs_TagMuonPt = new TH2D("tagMuonEta_vs_TagMuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histTagMuonEta_vs_TagMuonPhi = new TH2D("tagMuonEta_vs_TagMuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histTagMuonMet = new TH1D("tagMuonMet", "", 23, ptBinning);
		histTagMuonMt = new TH1D("tagMuonMt", "", 23, ptBinning);

		histTagMuonHltIsoMu = new TH1D("tagMuonHlt_isomu", "", 2, 0, 2);
		histTagMuonHltMu = new TH1D("tagMuonHlt_mu", "", 2, 0, 2);
		histTagMuonPassesSingleMuon = new TH1D("tagMuonPassesSingleMuon", "", 2, 0, 2);
		histTagMuonCharge = new TH1D("tagMuonCharge", "", 3, -1, 2);
		//histTagMuonIEta = new TH1D("tagMuonIEta", "", nBinsIEta, minIEta, maxIEta);
		//histTagMuonHoN3x3Hit = new TH1D("tagMuonHoN3x3Hit", "", 10, 0, 10);

		// Reco Probe ProbeMuons
		histNProbeMuon = new TH1D("nProbeMuon", "", 10, 0, 10);
		histIsLooseProbeMuon = new TH1D("isLooseProbeMuon", "", 2, 0, 2);
		histIsMediumProbeMuon = new TH1D("isMediumProbeMuon", "", 2, 0, 2);
		histIsTightProbeMuon = new TH1D("isTightProbeMuon", "", 2, 0, 2);

		histProbeMuonE = new TH1D("probeMuonE", "", nBinsE, minE, maxE);
		histProbeMuonEt = new TH1D("probeMuonEt", "", nBinsE, minE, maxE);
		histProbeMuonPt = new TH1D("probeMuonPt", "", 23, ptBinning);
		histProbeMuonPtFineBinning = new TH1D("probeMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histProbeMuonEta = new TH1D("probeMuonEta", "", nBinsEta, etaBinning);
		histProbeMuonPhi = new TH1D("probeMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histProbeMuonIso = new TH1D("probeMuonIso", "", 100, 0, 1);
		histProbeMuonHltIsoDeltaR = new TH1D("probeMuonHlt_isoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histProbeMuonDeltaR = new TH1D("probeMuonHlt_deltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histProbeMuonEtaSt1 = new TH1D("probeMuonEtaSt1", "", nBinsEta, etaBinning);
		histProbeMuonPhiSt1 = new TH1D("probeMuonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histProbeMuonEtaSt2 = new TH1D("probeMuonEtaSt2", "", nBinsEta, etaBinning);
		histProbeMuonPhiSt2 = new TH1D("probeMuonPhiSt2", "", nBinsPhi, minPhi, maxPhi);

		histProbeMuonPt_vs_ProbeMuonEta = new TH2D("probeMuonPt_vs_ProbeMuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, etaBinning);
		histProbeMuonEta_vs_ProbeMuonPt = new TH2D("probeMuonEta_vs_ProbeMuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histProbeMuonEta_vs_ProbeMuonPhi = new TH2D("probeMuonEta_vs_ProbeMuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histProbeMuonMet = new TH1D("probeMuonMet", "", 23, ptBinning);
		histProbeMuonMt = new TH1D("probeMuonMt", "", 23, ptBinning);

		histProbeMuonHltIsoMu = new TH1D("probeMuonHlt_isomu", "", 2, 0, 2);
		histProbeMuonHltMu = new TH1D("probeMuonHlt_mu", "", 2, 0, 2);
		histProbeMuonPassesSingleMuon = new TH1D("probeMuonPassesSingleMuon", "", 2, 0, 2);
		histProbeMuonCharge = new TH1D("probeMuonCharge", "", 3, -1, 2);
		histProbeMuonIEta = new TH1D("probeMuonIEta", "", nBinsIEta, minIEta, maxIEta);
		histProbeMuonHoN3x3Hit = new TH1D("probeMuonHoN3x3Hit", "", 10, 0, 10);
		histProbeMuonHoAbsIEta3Hit = new TH1D("probeMuonHoAbsIEta3Hit", "", 10, 0, 10);
	}

	// DTTP Histograms
	histDttpSize = new TH1D("dttpSize", "", 15, 0, 15);
	histDttpBx = new TH1D("dttpBx", "", 20, -10, 10);
	histDttpWheel = new TH1D("dttpWheel", "", nBinsWheel, minWheel, maxWheel);
	histDttpSection = new TH1D("dttpSection", "", nBinsSection, minSection, maxSection);
	histDttpStation = new TH1D("dttpStation", "", nBinsStation, minStation, maxStation);
	histDttpQualityCode = new TH1D("dttpQualitytCode", "", nBinsQualityCode, minQualityCode, maxQualityCode);
	histDttpTs2Tag = new TH1D("dttpTs2Tag", "", 2, 0, 2);
	histDttpIPhi = new TH1D("dttpIPhi", "", 72, 1, 73);
	histDttpPhi = new TH1D("dttpPhi", "", 512, -2048, 2048);
	histDttpPhiB = new TH1D("dttpPhiB", "", 500, -250, 250);
	histDttpCmsPt = new TH1D("dttpCmsPt", "", 300, 0, 300);
	histDttpCmsPhi = new TH1D("dttpCmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histDttpHoN3x3Hit = new TH1D("dttpHoN3x3Hit", "", 10, 0, 10);
	histDttpHoAbsIEta3Hit = new TH1D("dttpHoAbsIEta3Hit", "", 10, 0, 10);

	// BMTF Producer
	histNBmtf = new TH1D("nBmtf", "", 25, 0, 25);
	histBmtfHwPt = new TH1D("bmtfHwPt", "", 23, ptBinning);
	histBmtfCmsPt = new TH1D("bmtfCmsPt", "", 23, ptBinning);
	histBmtfCmsPtFineBinning = new TH1D("bmtfCmsPtFineBinning", "", nBinsPt, minPt, maxPt);
	histBmtfHwEta = new TH1D("bmtfHwEta", "", 25, 0, 25);
	histBmtfCmsEta = new TH1D("bmtfCmsEta", "", nBinsEta, etaBinning);
	histBmtfHwPhi = new TH1D("bmtfHwPhi", "", 56, 0, 56);
	histBmtfGlobalPhi = new TH1D("bmtfGlobalPhi", "", 576, 0, 576);
	histBmtfCmsPhi = new TH1D("bmtfCmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histBmtfHwSign = new TH1D("bmtfHwSign", "", 5, -2, 3);
	histBmtfHwSignValid = new TH1D("bmtfHwSignValid", "", 2, 0, 2);
	histBmtfHwQual = new TH1D("bmtfHwQual", "", 25, 0, 25);
	histBmtfLink = new TH1D("bmtfLink", "", 25, 0, 25);
	histBmtfProcessor = new TH1D("bmtfProcessor", "", 25, 0, 25);
	histBmtfTrackFinderType = new TH1D("bmtfTrackFinderType", "", 25, 0, 25);
	histBmtfTrackType = new TH1D("bmtfTrackType", "", 25, 0, 25);
	histBmtfHwHF = new TH1D("bmtfHwHF", "", 25, 0, 25);
	histBmtfBx = new TH1D("bmtfBx", "", 20, -10, 10);
	histBmtfWh = new TH1D("bmtfWh", "", 25, 0, 25);
	histBmtfTrAdd = new TH1D("bmtfTrAdd", "", 25, 0, 25);
	histBmtfTrAddSt1 = new TH1D("bmtfTrAddSt1", "", 25, 0, 25);
	histBmtfTrAddSt2 = new TH1D("bmtfTrAddSt2", "", 25, 0, 25);
	histBmtfTrAddSt3 = new TH1D("bmtfTrAddSt3", "", 25, 0, 25);
	histBmtfTrAddSt4 = new TH1D("bmtfTrAddSt4", "", 25, 0, 25);

	// HOTP Histogram
	histNHcalDetIds = new TH1D("hcalDetIds", "", 50, 500, 1000);
	histSampleEnergy = new TH1D("SampleEnergy", "", 25, 0, 1);
	histHcalDetIdIEta = new TH1D("hcalIEta", "", nBinsIEta, minIEta, maxIEta);
	histHcalDetIdIPhi = new TH1D("hcalIPhi", "", 72, 1, 73);
	//histHcalCmsEta = new TH1D("hcalCmsEta", "", 68, -3, 3);
	//histHcalCmsEta = new TH1D("hcalCmsEta", "", nBinsEta, etaBinning);
	histHcalCmsEta = new TH1D("hcalCmsEta", "", nBinsEta, etaBinning);
	histHcalCmsPhi = new TH1D("hcalCmsPhi", "", nBinsPhi, -M_PI, M_PI);
	histHcalWheel = new TH1D("hcalWheel", "", 5, -2, 3);
	histHcalSection = new TH1D("hcalSection", "", 12, 0, 12);
	histSumQ = new TH1D("sumQ", "", 50, 0, 50);
	histNHcalQIESamples = new TH1D("nHcalQIESamples", "", 3000, 6000, 9000);
	histHcalQIESample = new TH1D("hcalQIESample", "", 10, 1, 11);
	histHcalQIESampleAdc = new TH1D("hcalQIESampleAdc", "", 50, 0, 50);
	histHcalQIESampleDv = new TH1D("hcalQIESampleDv", "", 2, 0, 2);
	histHcalQIESampleEr = new TH1D("hcalQIESampleEr", "", 25, 0, 1);
	histQIESampleFc = new TH1D("QIESampleFc", "", 100, 0, 100);
	histQIESamplePedestal = new TH1D("QIESamplePedestal", "", 20, 5, 15);
	histQIESampleFc_MPedestals = new TH1D("QIESampleFc_MPedestals", "", 100, 0, 100);
	histHcalQIESamples_vs_HcalQIESampleAdc = new TH2D("HcalQIESamples_vs_HcalQIESampleAdc", "", 10, 0, 10, 50, 0, 50);

	// HOTP that are isoMb1
	histNHcalDetIds_isoMb1 = new TH1D("hcalDetIds_isoMb1", "", 50, 500, 1000);
	histSampleEnergy_isoMb1 = new TH1D("SampleEnergy_isoMb1", "", 25, 0, 1);
	histHcalDetIdIEta_isoMb1 = new TH1D("hcalIEta_isoMb1", "", nBinsIEta, minIEta, maxIEta);
	histHcalDetIdIPhi_isoMb1 = new TH1D("hcalIPhi_isoMb1", "", 72, 1, 73);
	histHcalCmsEta_isoMb1 = new TH1D("hcalCmsEta_isoMb1", "", nBinsEta, etaBinning);
	histHcalCmsPhi_isoMb1 = new TH1D("hcalCmsPhi_isoMb1", "", nBinsPhi, -M_PI, M_PI);
	histHcalWheel_isoMb1 = new TH1D("hcalWheel_isoMb1", "", 5, -2, 3);
	histHcalSection_isoMb1 = new TH1D("hcalSection_isoMb1", "", 12, 0, 12);
	histSumQ_isoMb1 = new TH1D("sumQ_isoMb1", "", 50, 0, 50);
	histNHcalQIESamples_isoMb1 = new TH1D("nHcalQIESamples_isoMb1", "", 3000, 6000, 9000);
	histHcalQIESample_isoMb1 = new TH1D("hcalQIESample_isoMb1", "", 10, 1, 11);
	histHcalQIESampleAdc_isoMb1 = new TH1D("hcalQIESampleAdc_isoMb1", "", 50, 0, 50);
	histHcalQIESampleDv_isoMb1 = new TH1D("hcalQIESampleDv_isoMb1", "", 2, 0, 2);
	histHcalQIESampleEr_isoMb1 = new TH1D("hcalQIESampleEr_isoMb1", "", 25, 0, 1);
	histQIESampleFc_isoMb1 = new TH1D("QIESampleFc_isoMb1", "", 100, 0, 100);
	histQIESamplePedestal_isoMb1 = new TH1D("QIESamplePedestal_isoMb1", "", 20, 5, 15);
	histQIESampleFc_MPedestals_isoMb1 = new TH1D("QIESampleFc_MPedestals_isoMb1", "", 100, 0, 100);
	histHcalQIESamples_vs_HcalQIESampleAdc_isoMb1 = new TH2D("HcalQIESamples_vs_HcalQIESampleAdc_isoMb1", "", 10, 0, 10, 50, 0, 50);

	// HOTP that are isoMb2
	histNHcalDetIds_isoMb2 = new TH1D("hcalDetIds_isoMb2", "", 50, 500, 1000);
	histSampleEnergy_isoMb2 = new TH1D("SampleEnergy_isoMb2", "", 25, 0, 1);
	histHcalDetIdIEta_isoMb2 = new TH1D("hcalIEta_isoMb2", "", nBinsIEta, minIEta, maxIEta);
	histHcalDetIdIPhi_isoMb2 = new TH1D("hcalIPhi_isoMb2", "", 72, 1, 73);
	histHcalCmsEta_isoMb2 = new TH1D("hcalCmsEta_isoMb2", "", nBinsEta, etaBinning);
	histHcalCmsPhi_isoMb2 = new TH1D("hcalCmsPhi_isoMb2", "", nBinsPhi, -M_PI, M_PI);
	histHcalWheel_isoMb2 = new TH1D("hcalWheel_isoMb2", "", 5, -2, 3);
	histHcalSection_isoMb2 = new TH1D("hcalSection_isoMb2", "", 12, 0, 12);
	histSumQ_isoMb2 = new TH1D("sumQ_isoMb2", "", 50, 0, 50);
	histNHcalQIESamples_isoMb2 = new TH1D("nHcalQIESamples_isoMb2", "", 3000, 6000, 9000);
	histHcalQIESample_isoMb2 = new TH1D("hcalQIESample_isoMb2", "", 10, 1, 11);
	histHcalQIESampleAdc_isoMb2 = new TH1D("hcalQIESampleAdc_isoMb2", "", 50, 0, 50);
	histHcalQIESampleDv_isoMb2 = new TH1D("hcalQIESampleDv_isoMb2", "", 2, 0, 2);
	histHcalQIESampleEr_isoMb2 = new TH1D("hcalQIESampleEr_isoMb2", "", 25, 0, 1);
	histQIESampleFc_isoMb2 = new TH1D("QIESampleFc_isoMb2", "", 100, 0, 100);
	histQIESamplePedestal_isoMb2 = new TH1D("QIESamplePedestal_isoMb2", "", 20, 5, 15);
	histQIESampleFc_MPedestals_isoMb2 = new TH1D("QIESampleFc_MPedestals_isoMb2", "", 100, 0, 100);
	histHcalQIESamples_vs_HcalQIESampleAdc_isoMb2 = new TH2D("HcalQIESamples_vs_HcalQIESampleAdc_isoMb2", "", 10, 0, 10, 50, 0, 50);

	// HOTP that are isoMb12
	histSampleEnergy_isoMb12 = new TH1D("SampleEnergy_isoMb12", "", 25, 0, 1);
	histHcalDetIdIEta_isoMb12 = new TH1D("hcalIEta_isoMb12", "", nBinsIEta, minIEta, maxIEta);
	histHcalDetIdIPhi_isoMb12 = new TH1D("hcalIPhi_isoMb12", "", 72, 1, 73);
	histHcalCmsEta_isoMb12 = new TH1D("hcalCmsEta_isoMb12", "", nBinsEta, etaBinning);
	histHcalCmsPhi_isoMb12 = new TH1D("hcalCmsPhi_isoMb12", "", nBinsPhi, -M_PI, M_PI);
	histHcalWheel_isoMb12 = new TH1D("hcalWheel_isoMb12", "", 5, -2, 3);
	histHcalSection_isoMb12 = new TH1D("hcalSection_isoMb12", "", 12, 0, 12);
	histSumQ_isoMb12 = new TH1D("sumQ_isoMb12", "", 50, 0, 50);
	histNHcalQIESamples_isoMb12 = new TH1D("nHcalQIESamples_isoMb12", "", 3000, 6000, 9000);
	histHcalQIESample_isoMb12 = new TH1D("hcalQIESample_isoMb12", "", 10, 1, 11);
	histHcalQIESampleAdc_isoMb12 = new TH1D("hcalQIESampleAdc_isoMb12", "", 50, 0, 50);
	histHcalQIESampleDv_isoMb12 = new TH1D("hcalQIESampleDv_isoMb12", "", 2, 0, 2);
	histHcalQIESampleEr_isoMb12 = new TH1D("hcalQIESampleEr_isoMb12", "", 25, 0, 1);
	histQIESampleFc_isoMb12 = new TH1D("QIESampleFc_isoMb12", "", 100, 0, 100);
	histQIESamplePedestal_isoMb12 = new TH1D("QIESamplePedestal_isoMb12", "", 20, 5, 15);
	histQIESampleFc_MPedestals_isoMb12 = new TH1D("QIESampleFc_MPedestals_isoMb12", "", 100, 0, 100);
	histHcalQIESamples_vs_HcalQIESampleAdc_isoMb12 = new TH2D("HcalQIESamples_vs_HcalQIESampleAdc_isoMb12", "", 10, 0, 10, 50, 0, 50);

	// HOTP that are notIsoMbMatched
	histNHcalDetIds_notIsoMbMatched = new TH1D("hcalDetIds_notIsoMbMatched", "", 50, 500, 1000);
	histSampleEnergy_notIsoMbMatched = new TH1D("SampleEnergy_notIsoMbMatched", "", 25, 0, 1);
	histHcalDetIdIEta_notIsoMbMatched = new TH1D("hcalIEta_notIsoMbMatched", "", nBinsIEta, minIEta, maxIEta);
	histHcalDetIdIPhi_notIsoMbMatched = new TH1D("hcalIPhi_notIsoMbMatched", "", 72, 1, 73);
	histHcalCmsEta_notIsoMbMatched = new TH1D("hcalCmsEta_notIsoMbMatched", "", nBinsEta, etaBinning);
	histHcalCmsPhi_notIsoMbMatched = new TH1D("hcalCmsPhi_notIsoMbMatched", "", nBinsPhi, -M_PI, M_PI);
	histHcalWheel_notIsoMbMatched = new TH1D("hcalWheel_notIsoMbMatched", "", 5, -2, 3);
	histHcalSection_notIsoMbMatched = new TH1D("hcalSection_notIsoMbMatched", "", 12, 0, 12);
	histSumQ_notIsoMbMatched = new TH1D("sumQ_notIsoMbMatched", "", 50, 0, 50);
	histNHcalQIESamples_notIsoMbMatched = new TH1D("nHcalQIESamples_notIsoMbMatched", "", 3000, 6000, 9000);
	histHcalQIESample_notIsoMbMatched = new TH1D("hcalQIESample_notIsoMbMatched", "", 10, 1, 11);
	histHcalQIESampleAdc_notIsoMbMatched = new TH1D("hcalQIESampleAdc_notIsoMbMatched", "", 50, 0, 50);
	histHcalQIESampleDv_notIsoMbMatched = new TH1D("hcalQIESampleDv_notIsoMbMatched", "", 2, 0, 2);
	histHcalQIESampleEr_notIsoMbMatched = new TH1D("hcalQIESampleEr_notIsoMbMatched", "", 25, 0, 1);
	histQIESampleFc_notIsoMbMatched = new TH1D("QIESampleFc_notIsoMbMatched", "", 100, 0, 100);
	histQIESamplePedestal_notIsoMbMatched = new TH1D("QIESamplePedestal_notIsoMbMatched", "", 20, 5, 15);
	histQIESampleFc_MPedestals_notIsoMbMatched = new TH1D("QIESampleFc_MPedestals_notIsoMbMatched", "", 100, 0, 100);
	histHcalQIESamples_vs_HcalQIESampleAdc_notIsoMbMatched = new TH2D("HcalQIESamples_vs_HcalQIESampleAdc_notIsoMbMatched", "", 10, 0, 10, 50, 0, 50);

	// Any muon matched HOTP
	histNMuonMatchedHcalDetIds = new TH1D("muonMatchedHcalDetIds", "", 50, 500, 1000);
	histMuonMatchedSampleEnergy = new TH1D("muonMatchedSampleEnergy", "", 25, 0, 1);
	histMuonMatchedHcalDetIdIEta = new TH1D("muonMatchedHcalIEta", "", nBinsIEta, minIEta, maxIEta);
	histMuonMatchedHcalDetIdIPhi = new TH1D("muonMatchedHcalIPhi", "", 72, 1, 73);
	histMuonMatchedHcalCmsEta = new TH1D("muonMatchedHcalCmsEta", "", nBinsEta, etaBinning);
	histMuonMatchedHcalCmsPhi = new TH1D("muonMatchedHcalCmsPhi", "", nBinsPhi, -M_PI, M_PI);
	histMuonMatchedHcalWheel = new TH1D("muonMatchedHcalWheel", "", 5, -2, 3);
	histMuonMatchedHcalSection = new TH1D("muonMatchedHcalSection", "", 12, 0, 12);
	histMuonMatchedHcalQIESample = new TH1D("muonMatchedHcalQIESample", "", 10, 1, 11);
	histMuonMatchedHcalQIESampleAdc = new TH1D("muonMatchedHcalQIESampleAdc", "", 50, 0, 50);
	histMuonMatchedHcalQIESampleDv = new TH1D("muonMatchedHcalQIESampleDv", "", 2, 0, 2);
	histMuonMatchedHcalQIESampleEr = new TH1D("muonMatchedHcalQIESampleEr", "", 25, 0, 1);
	histMuonMatchedQIESampleFc = new TH1D("muonMatchedQIESampleFc", "", 100, 0, 100);
	histMuonMatchedQIESamplePedestal = new TH1D("muonMatchedQIESamplePedestal", "", 20, 5, 15);
	histMuonMatchedQIESampleFc_MPedestals = new TH1D("muonMatchedQIESampleFc_MPedestals", "", 100, 0, 100);
	histMuonMatchedHoDeltaR = new TH1D("MuonMatchedHoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);

	// Ho Matched Variables
	histIsMb3HoIEtaMatched = new TH1D("isMb3HoIEtaMatched", "", 2, 0, 2);
	histIsMb4HoIEtaMatched = new TH1D("isMb4HoIEtaMatched", "", 2, 0, 2);
	histBmtfMb34MatchedHoIEta = new TH1D("bmtfMb34MatchedHoIEta", "", nBinsIEta, minIEta, maxIEta);
	histBmtfMb34MatchedHoIPhi = new TH1D("bmtfMb34MatchedHoIPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histBmtfMb34MatchedHoDeltaIPhi = new TH1D("bmtfMb34MatchedHoDeltaIPhi", "", 2*nBinsIPhi+1, -maxIPhi+1, maxIPhi);
	histBmtfMb34MatchedHoDeltaR = new TH1D("bmtfMb34MatchedHoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
	histBmtfMb34MatchedHoPt = new TH1D("bmtfMb34MatchedHoPt", "", 23, ptBinning);
	histBmtfMb34MatchedHoPtFineBinning = new TH1D("bmtfMb34MatchedHoPtFineBinning", "", nBinsPt, minPt, maxPt);
	histBmtfMb34MatchedHoDeltaPhi = new TH1D("bmtfMb34MatchedHoDeltaPhi", "", nBinsPhi, -maxPhi, maxPhi);

	if (hasRecoMuon) {
		histBmtfMb34MatchedMuonPt = new TH1D("bmtfMb34MatchedMuonPt", "", 23, ptBinning);
		histBmtfMb34MatchedMuonPtFineBinning = new TH1D("bmtfMb34MatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histBmtfMb34MatchedMuonEta = new TH1D("bmtfMb34MatchedMuonEta", "", nBinsEta, etaBinning);
		histBmtfMb34MatchedMuonPhi = new TH1D("bmtfMb34MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histBmtfMb34MatchedMuonDeltaPhi = new TH1D("bmtfMb34MatchedMuonDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

		for (int tfType : {Utility::Bmtf, Utility::Omtf, Utility::Emtf, Utility::UGMT}) {
			histTfMapMatchedMuonPt.insert({tfType, new TH1D(("tfMatchedMuonPt_" + Utility::TfNames.at(tfType)).c_str(), "", 23, ptBinning)});
			histTfMapMatchedMuonPtFineBinning.insert({tfType, new TH1D(("tfMatchedMuonPtFineBinning_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPt, minPt, maxPt)});
			histTfMapMatchedMuonEta.insert({tfType, new TH1D(("tfMatchedMuonEta_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsEta, etaBinning)});
			histTfMapMatchedMuonPhi.insert({tfType, new TH1D(("tfMatchedMuonPhi_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPhi, minPhi, maxPhi)});
			histTfMapMatchedMuonTfType.insert({tfType, new TH1D(("tfMatchedMuonTfType_" + Utility::TfNames.at(tfType)).c_str(), "", 4, 0, 4)});

			histTfMatchedMuonEta_vs_MuonPt.insert({tfType, new TH2D(("tfMatchedMuonEta_vs_MuonPt_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs)});
			histTfMatchedMuonPt_vs_MuonEta.insert({tfType, new TH2D(("tfMatchedMuonPt_vs_MuonEta_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, etaBinning)});
			histTfMatchedMuonEta_vs_MuonPhi.insert({tfType, new TH2D(("tfMatchedMuonEta_vs_MuonPhi_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi)});

			histProbeMuonMapPt.insert({tfType, new TH1D(("probeMuonPt_" + Utility::TfNames.at(tfType)).c_str(), "", 23, ptBinning)});
			histProbeMuonMapPtFineBinning.insert({tfType, new TH1D(("probeMuonPtFineBinning_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPt, minPt, maxPt)});
			histProbeMuonMapEta.insert({tfType, new TH1D(("probeMuonEta_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsEta, etaBinning)});
			histProbeMuonMapPhi.insert({tfType, new TH1D(("probeMuonPhi_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPhi, minPhi, maxPhi)});
		}
	}

	histIsBmtfMatchedDttp = new TH1D("isBmtfMatchedDttp", "", 2, 0, 2);
	histBmtfMatchedDttpPhi = new TH1D("bmtfMatchedDttpPhi", "", nBinsPhi, -2048, 2048);
	histBmtfMatchedDttpCmsPt = new TH1D("bmtfMatchedDttpCmsPt", "", 23, ptBinning);
	histBmtfMatchedDttpDeltaPhi = new TH1D("bmtfMatchedDttpDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpCmsPhi = new TH1D("bmtfMatchedDttpCmsPhi", "", nBinsPhi, minPhi, maxPhi);

	histBmtfMatchedDttpDeltaPhiSt1 = new TH1D("bmtfMatchedDttpDeltaPhiSt1", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt2 = new TH1D("bmtfMatchedDttpDeltaPhiSt2", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt3 = new TH1D("bmtfMatchedDttpDeltaPhiSt3", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt4 = new TH1D("bmtfMatchedDttpDeltaPhiSt4", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

	histIsDttpMatchedHo = new TH1D("isDttpMatchedHo", "", 2, 0, 2);
	histDttpMatchedHoDeltaIPhi = new TH1D("dttpMatchedHoDeltaIPhi", "", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histDttpMatchedHoIPhi = new TH1D("dttpMatchedHoIPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histDttpMatchedHoIEta = new TH1D("dttpMatchedHoIEta", "", nBinsIEta, minIEta, maxIEta);

	histIsDttpMatchedHoN3x3 = new TH1D("isDttpMatchedHoN3x3", "", 2, 0, 2);
	histDttpMatchedHoN3x3Hit = new TH1D("dttpMatchedHoN3x3Hit", "", 10, 0, 10);
	histDttpMatchedHoN3x3DeltaIPhi = new TH1D("dttpMatchedHoN3x3DeltaIPhi", "", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histDttpMatchedHoN3x3IPhi = new TH1D("dttpMatchedHoN3x3IPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histDttpMatchedHoN3x3IEta = new TH1D("dttpMatchedHoN3x3IEta", "", nBinsIEta, minIEta, maxIEta);

	histIsDttpMatchedHoAbsIEta3 = new TH1D("isDttpMatchedHoAbsIEta3", "", 2, 0, 2);
	histDttpMatchedHoAbsIEta3DeltaIPhi = new TH1D("dttpMatchedHoAbsIEta3DeltaIPhi", "", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histDttpMatchedHoAbsIEta3IPhi = new TH1D("dttpMatchedHoAbsIEta3IPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histDttpMatchedHoAbsIEta3IEta = new TH1D("dttpMatchedHoAbsIEta3IEta", "", nBinsIEta, minIEta, maxIEta);



	if (hasRecoMuon) {
		histIsoMb1MatchedMuonPt = new TH1D("isoMb1MatchedMuonPt", "", 23, ptBinning);
		histIsoMb1MatchedMuonPtFineBinning = new TH1D("isoMb1MatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonEta = new TH1D("isoMb1MatchedMuonEta", "", nBinsEta, etaBinning);
		histIsoMb1MatchedMuonPhi = new TH1D("isoMb1MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);

		histIsoMb1MatchedMuonDeltaR   = new TH1D("histIsoMb1MatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histIsoMb1MatchedMuonDeltaEta = new TH1D("histIsoMb1MatchedMuonDeltaEta", "", nBinsEta, etaBinning);
		histIsoMb1MatchedMuonDeltaPhi = new TH1D("histIsoMb1MatchedMuonDeltaPhi", "", nBinsPhi, minPhi, maxPhi);

		histIsoMb1MatchedMuonEta_vs_MuonPt = new TH2D("isoMb1MatchedMuonEta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb1MatchedMuonEta_vs_MuonPhi = new TH2D("isoMb1MatchedMuonEta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);



		histIsoMb2MatchedMuonPt = new TH1D("isoMb2MatchedMuonPt", "", 23, ptBinning);
		histIsoMb2MatchedMuonPtFineBinning = new TH1D("isoMb2MatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonEta = new TH1D("isoMb2MatchedMuonEta", "", nBinsEta, etaBinning);
		histIsoMb2MatchedMuonPhi = new TH1D("isoMb2MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);

		histIsoMb2MatchedMuonDeltaR   = new TH1D("histIsoMb2MatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histIsoMb2MatchedMuonDeltaEta = new TH1D("histIsoMb2MatchedMuonDeltaEta", "", nBinsEta, etaBinning);
		histIsoMb2MatchedMuonDeltaPhi = new TH1D("histIsoMb2MatchedMuonDeltaPhi", "", nBinsPhi, minPhi, maxPhi);

		histIsoMb2MatchedMuonEta_vs_MuonPt = new TH2D("isoMb2MatchedMuonEta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb2MatchedMuonEta_vs_MuonPhi = new TH2D("isoMb2MatchedMuonEta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb12MatchedMuonPt = new TH1D("isoMb12MatchedMuonPt", "", 23, ptBinning);
		histIsoMb12MatchedMuonPtFineBinning = new TH1D("isoMb12MatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonEta = new TH1D("isoMb12MatchedMuonEta", "", nBinsEta, etaBinning);
		histIsoMb12MatchedMuonPhi = new TH1D("isoMb12MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);

		histIsoMb12MatchedMuonDeltaR   = new TH1D("histIsoMb12MatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histIsoMb12MatchedMuonDeltaEta = new TH1D("histIsoMb12MatchedMuonDeltaEta", "", nBinsEta, etaBinning);
		histIsoMb12MatchedMuonDeltaPhi = new TH1D("histIsoMb12MatchedMuonDeltaPhi", "", nBinsPhi, minPhi, maxPhi);

		histIsoMb12MatchedMuonEta_vs_MuonPt = new TH2D("isoMb12MatchedMuonEta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb12MatchedMuonEta_vs_MuonPhi = new TH2D("isoMb12MatchedMuonEta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb1MatchedMuonN3x3Pt = new TH1D("isoMb1MatchedMuonN3x3Pt", "", 23, ptBinning);
		histIsoMb1MatchedMuonN3x3PtFineBinning = new TH1D("isoMb1MatchedMuonN3x3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonN3x3Eta = new TH1D("isoMb1MatchedMuonN3x3Eta", "", nBinsEta, etaBinning);
		histIsoMb1MatchedMuonN3x3Phi = new TH1D("isoMb1MatchedMuonN3x3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb1MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb1MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb1MatchedMuonN3x3Eta_vs_MuonPhi = new TH2D("isoMb1MatchedMuonN3x3Eta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb2MatchedMuonN3x3Pt = new TH1D("isoMb2MatchedMuonN3x3Pt", "", 23, ptBinning);
		histIsoMb2MatchedMuonN3x3PtFineBinning = new TH1D("isoMb2MatchedMuonN3x3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonN3x3Eta = new TH1D("isoMb2MatchedMuonN3x3Eta", "", nBinsEta, etaBinning);
		histIsoMb2MatchedMuonN3x3Phi = new TH1D("isoMb2MatchedMuonN3x3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb2MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb2MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb2MatchedMuonN3x3Eta_vs_MuonPhi = new TH2D("isoMb2MatchedMuonN3x3Eta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb12MatchedMuonN3x3Pt = new TH1D("isoMb12MatchedMuonN3x3Pt", "", 23, ptBinning);
		histIsoMb12MatchedMuonN3x3PtFineBinning = new TH1D("isoMb12MatchedMuonN3x3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonN3x3Eta = new TH1D("isoMb12MatchedMuonN3x3Eta", "", nBinsEta, etaBinning);
		histIsoMb12MatchedMuonN3x3Phi = new TH1D("isoMb12MatchedMuonN3x3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb12MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb12MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb12MatchedMuonN3x3Eta_vs_MuonPhi = new TH2D("isoMb12MatchedMuonN3x3Eta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb1MatchedMuonAbsIEta3Pt = new TH1D("isoMb1MatchedMuonAbsIEta3Pt", "", 23, ptBinning);
		histIsoMb1MatchedMuonAbsIEta3PtFineBinning = new TH1D("isoMb1MatchedMuonAbsIEta3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonAbsIEta3Eta = new TH1D("isoMb1MatchedMuonAbsIEta3Eta", "", nBinsEta, etaBinning);
		histIsoMb1MatchedMuonAbsIEta3Phi = new TH1D("isoMb1MatchedMuonAbsIEta3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb1MatchedMuonAbsIEta3Eta_vs_MuonPt = new TH2D("isoMb1MatchedMuonAbsIEta3Eta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb1MatchedMuonAbsIEta3Eta_vs_MuonPhi = new TH2D("isoMb1MatchedMuonAbsIEta3Eta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb2MatchedMuonAbsIEta3Pt = new TH1D("isoMb2MatchedMuonAbsIEta3Pt", "", 23, ptBinning);
		histIsoMb2MatchedMuonAbsIEta3PtFineBinning = new TH1D("isoMb2MatchedMuonAbsIEta3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonAbsIEta3Eta = new TH1D("isoMb2MatchedMuonAbsIEta3Eta", "", nBinsEta, etaBinning);
		histIsoMb2MatchedMuonAbsIEta3Phi = new TH1D("isoMb2MatchedMuonAbsIEta3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb2MatchedMuonAbsIEta3Eta_vs_MuonPt = new TH2D("isoMb2MatchedMuonAbsIEta3Eta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb2MatchedMuonAbsIEta3Eta_vs_MuonPhi = new TH2D("isoMb2MatchedMuonAbsIEta3Eta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb12MatchedMuonAbsIEta3Pt = new TH1D("isoMb12MatchedMuonAbsIEta3Pt", "", 23, ptBinning);
		histIsoMb12MatchedMuonAbsIEta3PtFineBinning = new TH1D("isoMb12MatchedMuonAbsIEta3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonAbsIEta3Eta = new TH1D("isoMb12MatchedMuonAbsIEta3Eta", "", nBinsEta, etaBinning);
		histIsoMb12MatchedMuonAbsIEta3Phi = new TH1D("isoMb12MatchedMuonAbsIEta3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb12MatchedMuonAbsIEta3Eta_vs_MuonPt = new TH2D("isoMb12MatchedMuonAbsIEta3Eta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb12MatchedMuonAbsIEta3Eta_vs_MuonPhi = new TH2D("isoMb12MatchedMuonAbsIEta3Eta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb1MatchedMuonHighADCPt = new TH1D("isoMb1MatchedMuonHighADCPt", "", 23, ptBinning);
		histIsoMb1MatchedMuonHighADCPtFineBinning = new TH1D("isoMb1MatchedMuonHighADCPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonHighADCEta = new TH1D("isoMb1MatchedMuonHighADCEta", "", nBinsEta, etaBinning);
		histIsoMb1MatchedMuonHighADCPhi = new TH1D("isoMb1MatchedMuonHighADCPhi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb1MatchedMuonHighADCEta_vs_MuonPt = new TH2D("isoMb1MatchedMuonHighADCEta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb1MatchedMuonHighADCEta_vs_MuonPhi = new TH2D("isoMb1MatchedMuonHighADCEta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb2MatchedMuonHighADCPt = new TH1D("isoMb2MatchedMuonHighADCPt", "", 23, ptBinning);
		histIsoMb2MatchedMuonHighADCPtFineBinning = new TH1D("isoMb2MatchedMuonHighADCPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonHighADCEta = new TH1D("isoMb2MatchedMuonHighADCEta", "", nBinsEta, etaBinning);
		histIsoMb2MatchedMuonHighADCPhi = new TH1D("isoMb2MatchedMuonHighADCPhi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb2MatchedMuonHighADCEta_vs_MuonPt = new TH2D("isoMb2MatchedMuonHighADCEta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb2MatchedMuonHighADCEta_vs_MuonPhi = new TH2D("isoMb2MatchedMuonHighADCEta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsoMb12MatchedMuonHighADCPt = new TH1D("isoMb12MatchedMuonHighADCPt", "", 23, ptBinning);
		histIsoMb12MatchedMuonHighADCPtFineBinning = new TH1D("isoMb12MatchedMuonHighADCPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonHighADCEta = new TH1D("isoMb12MatchedMuonHighADCEta", "", nBinsEta, etaBinning);
		histIsoMb12MatchedMuonHighADCPhi = new TH1D("isoMb12MatchedMuonHighADCPhi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb12MatchedMuonHighADCEta_vs_MuonPt = new TH2D("isoMb12MatchedMuonHighADCEta_vs_MuonPt", "", nBinsEta, etaBinning, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb12MatchedMuonHighADCEta_vs_MuonPhi = new TH2D("isoMb12MatchedMuonHighADCEta_vs_MuonPhi", "", nBinsEta, etaBinning, nBinsPhi, minPhi, maxPhi);

		histIsDttpMatchedMuon = new TH1D("isDttpMatchedMuon", "", 2, 0, 2);
		histDttpMatchedMuonDeltaR = new TH1D("dttpMatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
	}
	histHoN3x3Hit = new TH1D("nMuonMatchedDttpHoN3x3Hit", "", 10, 0, 10);
}

HoHistogramCollection::~HoHistogramCollection(){}
