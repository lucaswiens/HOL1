#include <HOAnalysis/HOL1/interface/HoHistogramCollection.h>

HoHistogramCollection::HoHistogramCollection(const bool &hasRecoMuon) : hasRecoMuon(hasRecoMuon) {
	double minE   =   0, minPt   =   0, minMass =   0  , minPtVs   =   0, minPhi   = -M_PI, minEta   = -2.0*M_PI/72.0 * 15, minWheel   = -3, minStation   = 1, minSection   =  0, minQualityCode   =  0, minDeltaR   =  0, minTrackType   =  0, minIPhi   =  1, minIEta   = -20;
	double maxE   = 250, maxPt   = 250, maxMass = 500  , maxPtVs   = 150, maxPhi   =  M_PI, maxEta   =  2.0*M_PI/72.0 * 15, maxWheel   =  4, maxStation   = 5, maxSection   = 12, maxQualityCode   = 10, maxDeltaR   =  3, maxTrackType   = 25, maxIPhi   = 73, maxIEta   =  20;
	int    nBinsE = 500, nBinsPt = 500, nMass   = 500*5, nBinsPtVs =  30, nBinsPhi =    72, nBinsEta =                  30, nBinsWheel =  7, nBinsStation = 4, nBinsSection = 12, nBinsQualityCode = 10, nBinsDeltaR = 30, nBinsTrackType = 25, nBinsIPhi = 72, nBinsIEta =  40;
	double ptBinning[24] = {0., 2., 3., 4., 5., 6., 7., 8., 10., 12., 14., 16., 18., 20., 22., 25., 30., 35., 45., 60., 75., 100., 140., 150};

	minEta   = -2.0*M_PI/72.0 * 28;
	maxEta   =  2.0*M_PI/72.0 * 28;
	nBinsEta =                  56;

	nBinsPhi = 31; // binning used in the offical tracker paper

	// Number of Events
	numberOfEvents = new TH1D("numberOfEvents", "", 1, 0, 1);
	histBmtfNumber = new TH1D("bmtfNumber", "", 1, 0, 1);
	histDttpMatchedHoNumber = new TH1D("dttpMatchedHoNumber", "", 1, 0, 1);
	histDttpMatchedHoN3x3Number = new TH1D("dttpMatchedHoN3x3Number", "", 1, 0, 1);
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
		/*
		histMuonPtAtIEtaP3 = new TH1D("muonPtAtIEtaP3", "", 23, ptBinning);
		histMuonPtAtIEtaM3 = new TH1D("muonPtAtIEtaM3", "", 23, ptBinning);
		*/
		histMuonPtFineBinning = new TH1D("muonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histMuonEta = new TH1D("muonEta", "", nBinsEta, minEta, maxEta);
		/*
		histMuonEtaHighPt = new TH1D("muonEtaHighPt", "", nBinsEta, minEta, maxEta);
		histMuonEtaLowPt = new TH1D("muonEtaLowPt", "", nBinsEta, minEta, maxEta);
		*/
		histMuonPhi = new TH1D("muonPhi", "", nBinsPhi, minPhi, maxPhi);
		histMuonIso = new TH1D("muonIso", "", 100, 0, 1);
		histMuonHltIsoDeltaR = new TH1D("muonHlt_isoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histMuonDeltaR = new TH1D("muonHlt_deltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histMuonEtaSt1 = new TH1D("muonEtaSt1", "", nBinsEta, minEta, maxEta);
		histMuonPhiSt1 = new TH1D("muonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histMuonEtaSt2 = new TH1D("muonEtaSt2", "", nBinsEta, minEta, maxEta);
		histMuonPhiSt2 = new TH1D("muonPhiSt2", "", nBinsPhi, minPhi, maxPhi);

		histDiMuonMass = new TH1D("diMuonMass", "", nMass, minMass, maxMass);
		histTagAndProbeDiMuonMass = new TH1D("tagAndProbeDiMuonMass", "", nMass, minMass, maxMass); // Not used atm

		histMuonPt_vs_MuonEta = new TH2D("muonPt_vs_MuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
		histMuonEta_vs_MuonPt = new TH2D("muonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histMuonEta_vs_MuonPhi = new TH2D("muonEta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		histNTagMuon_vs_nProbeMuon = new TH2D("nTagMuon_vs_nProbeMuon", "", 10, 0, 10, 10, 0, 10);

		histMuonMet = new TH1D("muonMet", "", 23, ptBinning);
		histMuonMt = new TH1D("muonMt", "", 23, ptBinning);

		histMuonHltIsoMu = new TH1D("muonHlt_isomu", "", 2, 0, 2);
		histMuonHltMu = new TH1D("muonHlt_mu", "", 2, 0, 2);
		histMuonPassesSingleMuon = new TH1D("muonPassesSingleMuon", "", 2, 0, 2);
		histMuonCharge = new TH1D("muonCharge", "", 3, -1, 1);
		histMuonIEta = new TH1D("muonIEta", "", nBinsIEta, minIEta, maxIEta);
		histMuonHoN3x3Hit = new TH1D("muonHoN3x3Hit", "", 10, 0, 10);

		// Reco Tag Muons
		histNTagMuon = new TH1D("nTagMuon", "", 10, 0, 10);
		histIsLooseTagMuon = new TH1D("isLooseTagMuon", "", 2, 0, 2);
		histIsMediumTagMuon = new TH1D("isMediumTagMuon", "", 2, 0, 2);
		histIsTightTagMuon = new TH1D("isTightTagMuon", "", 2, 0, 2);

		histTagMuonE = new TH1D("tagMuonE", "", nBinsE, minE, maxE);
		histTagMuonEt = new TH1D("tagMuonEt", "", nBinsE, minE, maxE);
		histTagMuonPt = new TH1D("tagMuonPt", "", 23, ptBinning);
		/*
		histTagMuonPtAtIEtaP3 = new TH1D("tagMuonPtAtIEtaP3", "", 23, ptBinning);
		histTagMuonPtAtIEtaM3 = new TH1D("tagMuonPtAtIEtaM3", "", 23, ptBinning);
		*/
		histTagMuonPtFineBinning = new TH1D("tagMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histTagMuonEta = new TH1D("tagMuonEta", "", nBinsEta, minEta, maxEta);
		/*
		histTagMuonEtaHighPt = new TH1D("tagMuonEtaHighPt", "", nBinsEta, minEta, maxEta);
		histTagMuonEtaLowPt = new TH1D("tagMuonEtaLowPt", "", nBinsEta, minEta, maxEta);
		*/
		histTagMuonPhi = new TH1D("tagMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histTagMuonIso = new TH1D("tagMuonIso", "", 100, 0, 1);
		histTagMuonHltIsoDeltaR = new TH1D("tagMuonHlt_isoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histTagMuonDeltaR = new TH1D("tagMuonHlt_deltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histTagMuonEtaSt1 = new TH1D("tagMuonEtaSt1", "", nBinsEta, minEta, maxEta);
		histTagMuonPhiSt1 = new TH1D("tagMuonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histTagMuonEtaSt2 = new TH1D("tagMuonEtaSt2", "", nBinsEta, minEta, maxEta);
		histTagMuonPhiSt2 = new TH1D("tagMuonPhiSt2", "", nBinsPhi, minPhi, maxPhi);

		histTagMuonPt_vs_TagMuonEta = new TH2D("tagMuonPt_vs_TagMuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
		histTagMuonEta_vs_TagMuonPt = new TH2D("tagMuonEta_vs_TagMuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histTagMuonEta_vs_TagMuonPhi = new TH2D("tagMuonEta_vs_TagMuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		histTagMuonMet = new TH1D("tagMuonMet", "", 23, ptBinning);
		histTagMuonMt = new TH1D("tagMuonMt", "", 23, ptBinning);

		histTagMuonHltIsoMu = new TH1D("tagMuonHlt_isomu", "", 2, 0, 2);
		histTagMuonHltMu = new TH1D("tagMuonHlt_mu", "", 2, 0, 2);
		histTagMuonPassesSingleMuon = new TH1D("tagMuonPassesSingleMuon", "", 2, 0, 2);
		histTagMuonCharge = new TH1D("tagMuonCharge", "", 3, -1, 1);
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
		/*
		histProbeMuonPtAtIEtaP3 = new TH1D("probeMuonPtAtIEtaP3", "", 23, ptBinning);
		histProbeMuonPtAtIEtaM3 = new TH1D("probeMuonPtAtIEtaM3", "", 23, ptBinning);
		*/
		histProbeMuonPtFineBinning = new TH1D("probeMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histProbeMuonEta = new TH1D("probeMuonEta", "", nBinsEta, minEta, maxEta);
		/*
		histProbeMuonEtaHighPt = new TH1D("probeMuonEtaHighPt", "", nBinsEta, minEta, maxEta);
		histProbeMuonEtaLowPt = new TH1D("probeMuonEtaLowPt", "", nBinsEta, minEta, maxEta);
		*/
		histProbeMuonPhi = new TH1D("probeMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histProbeMuonIso = new TH1D("probeMuonIso", "", 100, 0, 1);
		histProbeMuonHltIsoDeltaR = new TH1D("probeMuonHlt_isoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histProbeMuonDeltaR = new TH1D("probeMuonHlt_deltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histProbeMuonEtaSt1 = new TH1D("probeMuonEtaSt1", "", nBinsEta, minEta, maxEta);
		histProbeMuonPhiSt1 = new TH1D("probeMuonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histProbeMuonEtaSt2 = new TH1D("probeMuonEtaSt2", "", nBinsEta, minEta, maxEta);
		histProbeMuonPhiSt2 = new TH1D("probeMuonPhiSt2", "", nBinsPhi, minPhi, maxPhi);

		histProbeMuonPt_vs_ProbeMuonEta = new TH2D("probeMuonPt_vs_ProbeMuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
		histProbeMuonEta_vs_ProbeMuonPt = new TH2D("probeMuonEta_vs_ProbeMuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histProbeMuonEta_vs_ProbeMuonPhi = new TH2D("probeMuonEta_vs_ProbeMuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		histProbeMuonMet = new TH1D("probeMuonMet", "", 23, ptBinning);
		histProbeMuonMt = new TH1D("probeMuonMt", "", 23, ptBinning);

		histProbeMuonHltIsoMu = new TH1D("probeMuonHlt_isomu", "", 2, 0, 2);
		histProbeMuonHltMu = new TH1D("probeMuonHlt_mu", "", 2, 0, 2);
		histProbeMuonPassesSingleMuon = new TH1D("probeMuonPassesSingleMuon", "", 2, 0, 2);
		histProbeMuonCharge = new TH1D("probeMuonCharge", "", 3, -1, 1);
		histProbeMuonIEta = new TH1D("probeMuonIEta", "", nBinsIEta, minIEta, maxIEta);
		histProbeMuonHoN3x3Hit = new TH1D("probeMuonHoN3x3Hit", "", 10, 0, 10);
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

	// BMTF Producer
	histNBmtf = new TH1D("nBmtf", "", 25, 0, 25);
	//histBmtfHwPt = new TH1D("bmtfHwPt", "", nBinsPt, minPt, maxPt);
	histBmtfHwPt = new TH1D("bmtfHwPt", "", 23, ptBinning);
	//histBmtfCmsPt = new TH1D("bmtfCmsPt", "", nBinsPt, minPt, maxPt);
	histBmtfCmsPt = new TH1D("bmtfCmsPt", "", 23, ptBinning);
	histBmtfCmsPtFineBinning = new TH1D("bmtfCmsPtFineBinning", "", nBinsPt, minPt, maxPt);
	histBmtfHwEta = new TH1D("bmtfHwEta", "", 25, 0, 25);
	histBmtfCmsEta = new TH1D("bmtfCmsEta", "", nBinsEta, minEta, maxEta);
	histBmtfHwPhi = new TH1D("bmtfHwPhi", "", 56, 0, 56);
	histBmtfGlobalPhi = new TH1D("bmtfGlobalPhi", "", 576, 0, 576);
	//histBmtfCmsPhi = new TH1D("bmtfCmsPhi", "", 144, minPhi, maxPhi);
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

	histtfMuonRateVsPhi = new TH1D("uGMTPhiRate", "", nBinsPhi, minPhi, maxPhi);
	histBmtfMuonRateVsPhi = new TH1D("BmtfPhiRate", "", nBinsPhi, minPhi, maxPhi);
	histOmtfMuonRateVsPhi = new TH1D("OmtfPhiRate", "", nBinsPhi, minPhi, maxPhi);
	histEmtfMuonRateVsPhi = new TH1D("EmtfPhiRate", "", nBinsPhi, minPhi, maxPhi);

	//if (hasRecoMuon) {
	//	histtfMatchedMuonRateVsPhi = new TH1D("uGMTMatchedMuonPhiRate", "", nBinsPhi, minPhi, maxPhi);
	//	histBmtfMatchedMuonRateVsPhi = new TH1D("BmtfMatchedMuonPhiRate", "", nBinsPhi, minPhi, maxPhi);
	//	histOmtfMatchedMuonRateVsPhi = new TH1D("OmtfMatchedMuonPhiRate", "", nBinsPhi, minPhi, maxPhi);
	//	histMatchedEmtfMuonRateVsPhi = new TH1D("EmtfMatchedMuonPhiRate", "", nBinsPhi, minPhi, maxPhi);
	//}

	//histDttpStation_vs_DttpWheel = new TH2D("MB_station_vs_wheel", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histDttpStation_vs_DttpWheel_Hq = new TH2D("MB_station_vs_wheel_Hq", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histDttpStation_vs_DttpWheel_Lq = new TH2D("MB_station_vs_wheel_Lq", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);

	// HOTP Histogram
	histNHcalDetIds = new TH1D("hcalDetIds", "", 50, 500, 1000);
	histSampleEnergy = new TH1D("SampleEnergy", "", 25, 0, 1);
	histHcalDetIdIEta = new TH1D("hcalDetIdIEta", "", nBinsIEta, minIEta, maxIEta);
	histHcalDetIdIPhi = new TH1D("hcalDetIdIPhi", "", 72, 1, 73);
	//histHcalCmsEta = new TH1D("hcalCmsEta", "", 68, -3, 3);
	histHcalCmsEta = new TH1D("hcalCmsEta", "", nBinsEta, -minEta, maxEta);
	histHcalCmsPhi = new TH1D("hcalCmsPhi", "", nBinsPhi, -M_PI, M_PI);
	histHcalWheel = new TH1D("hcalWheel", "", 5, -2, 3);
	histHcalSection = new TH1D("hcalSection", "", 12, 0, 12);
	histSumQ = new TH1D("sumQ", "", 50, 0, 50);
	histNHcalQIESamples = new TH1D("nHcalQIESamples", "", 3000, 6000, 9000);
	histHcalQIESample = new TH1D("hcalQIESample", "", 10, 1, 11);
	histHcalQIESampleAdc = new TH1D("hcalQIESampleAdc", "", 50, 0, 50);
	histHcalQIESampleDv = new TH1D("hcalQIESampleDv", "", 2, 0, 2);
	histHcalQIESampleEr = new TH1D("hcalQIESampleEr", "", 25, 0, 1);
	histQIESampleFc = new TH1D("QIESampleFc", "", 50, 0, 100);
	histQIESamplePedestal = new TH1D("QIESamplePedestal", "", 30, -10, 10);
	histQIESampleFc_MPedestals = new TH1D("QIESampleFc_MPedestals", "", 50, 0, 100);

	//histBmtfMatchedMuonPt_vs_MuonEta  = new TH2D("bmtfMatchedMuonPt_vs_MuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
	histHcalQIESamples_vs_HcalQIESampleAdc = new TH2D("HcalQIESamples_vs_HcalQIESampleAdc", "", 10, 0, 10, 50, 0, 50);

	// Ho Matched Variables
	histIsMb3HoIEtaMatched = new TH1D("isMb3HoIEtaMatched", "", 2, 0, 2);
	histIsMb4HoIEtaMatched = new TH1D("isMb4HoIEtaMatched", "", 2, 0, 2);
	histBmtfMb34MatchedHoIEta = new TH1D("bmtfMb34MatchedHoIEta", "", nBinsIEta, minIEta, maxIEta);
	histBmtfMb34MatchedHoIPhi = new TH1D("bmtfMb34MatchedHoIPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histBmtfMb34MatchedHoDeltaIPhi = new TH1D("bmtfMb34MatchedHoDeltaIPhi", "", 2*nBinsIPhi+1, -maxIPhi+1, maxIPhi);
	histBmtfMb34MatchedHoDeltaR = new TH1D("bmtfMb34MatchedHoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
	//histBmtfMb34MatchedHoPt = new TH1D("bmtfMb34MatchedHoPt", "", nBinsPt, minPt, maxPt);
	histBmtfMb34MatchedHoPt = new TH1D("bmtfMb34MatchedHoPt", "", 23, ptBinning);
	histBmtfMb34MatchedHoPtFineBinning = new TH1D("bmtfMb34MatchedHoPtFineBinning", "", nBinsPt, minPt, maxPt);
	histBmtfMb34MatchedHoCmsEta = new TH1D("bmtfMb34MatchedHoCmsEta", "", nBinsEta, minEta, maxEta);
	histBmtfMb34MatchedHoCmsPhi = new TH1D("bmtfMb34MatchedHoCmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histBmtfMb34MatchedHoDeltaPhi = new TH1D("bmtfMb34MatchedHoDeltaPhi", "", nBinsPhi, -maxPhi, maxPhi);

	if (hasRecoMuon) {
		//histBmtfMb34MatchedMuonPt = new TH1D("bmtfMb34MatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histBmtfMb34MatchedMuonPt = new TH1D("bmtfMb34MatchedMuonPt", "", 23, ptBinning);
		histBmtfMb34MatchedMuonPtFineBinning = new TH1D("bmtfMb34MatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histBmtfMb34MatchedMuonEta = new TH1D("bmtfMb34MatchedMuonEta", "", nBinsEta, minEta, maxEta);
		histBmtfMb34MatchedMuonPhi = new TH1D("bmtfMb34MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histBmtfMb34MatchedMuonDeltaPhi = new TH1D("bmtfMb34MatchedMuonDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

		histBmtfMatchedMuonCharge = new TH1D("bmtfMatchedMuonCharge", "", 3, -1, 2);
		histIsBmtfMatchedMuon = new TH1D("isBmtfMatchedMuon", "", 2, 0, 2);
		histBmtfMatchedMuonDeltaR = new TH1D("bmtfMatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		//histBmtfMatchedMuonPt = new TH1D("bmtfMatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histBmtfMatchedMuonPt = new TH1D("bmtfMatchedMuonPt", "", 23, ptBinning);
		/*
		histBmtfMatchedMuonPtAtIEtaP3 = new TH1D("bmtfMatchedMuonPtAtIEtaP3", "", 23, ptBinning);
		histBmtfMatchedMuonPtAtIEtaM3 = new TH1D("bmtfMatchedMuonPtAtIEtaM3", "", 23, ptBinning);
		*/

		histBmtfMatchedMuonPtFineBinning = new TH1D("bmtfMatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histBmtfMatchedMuonEta = new TH1D("bmtfMatchedMuonEta", "", nBinsEta, minEta, maxEta);
		/*
		histBmtfMatchedMuonEtaLowPt = new TH1D("bmtfMatchedMuonEtaLowPt", "", nBinsEta, minEta, maxEta);
		histBmtfMatchedMuonEtaHighPt = new TH1D("bmtfMatchedMuonEtaHighPt", "", nBinsEta, minEta, maxEta);
		*/
		histBmtfMatchedMuonPhi = new TH1D("bmtfMatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histBmtfMatchedMuonTrackType = new TH1D("bmtfMatchedMuonTrackType", "", nBinsTrackType, minTrackType, maxTrackType);
		histBmtfMatchedMuonDeltaPhi = new TH1D("bmtfMatchedMuonDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

		histBmtfMatchedMuonPt_vs_MuonEta  = new TH2D("bmtfMatchedMuonPt_vs_MuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
		histBmtfMatchedMuonEta_vs_MuonPt  = new TH2D("bmtfMatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histBmtfMatchedMuonEta_vs_MuonPhi  = new TH2D("bmtfMatchedMuonEta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		//histMuonMatchedBmtfCmsPt = new TH1D("muonMatchedBmtfCmsPt", "", nBinsPt, minPt, maxPt);
		//histMuonMatchedBmtfCmsPt = new TH1D("muonMatchedBmtfCmsPt", "", 23, ptBinning);
		//histMuonMatchedBmtfCmsEta = new TH1D("muonMatchedBmtfCmsEta", "", nBinsEta, minEta, maxEta);

		histTfMatchedMuonCharge = new TH1D("tfMatchedMuonCharge", "", 3, -1, 2);
		histIsTfMatchedMuon = new TH1D("isTFMatchedMuon", "", 2, 0, 2);
		histTfMatchedMuonDeltaR = new TH1D("tfMatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		//histTfMatchedMuonPt = new TH1D("tfMatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histTfMatchedMuonPt = new TH1D("tfMatchedMuonPt", "", 23, ptBinning);
		/*
		histTfMatchedMuonPtAtIEtaP3 = new TH1D("tfMatchedMuonPtAtIEtaP3", "", 23, ptBinning);
		histTfMatchedMuonPtAtIEtaM3 = new TH1D("tfMatchedMuonPtAtIEtaM3", "", 23, ptBinning);
		*/

		histTfMatchedMuonPtFineBinning = new TH1D("tfMatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histTfMatchedMuonEta = new TH1D("tfMatchedMuonEta", "", nBinsEta, minEta, maxEta);
		/*
		histTfMatchedMuonEtaLowPt = new TH1D("tfMatchedMuonEtaLowPt", "", nBinsEta, minEta, maxEta);
		histTfMatchedMuonEtaHighPt = new TH1D("tfMatchedMuonEtaHighPt", "", nBinsEta, minEta, maxEta);
		*/
		histTfMatchedMuonPhi = new TH1D("tfMatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histTfMatchedMuonTrackType = new TH1D("tfMatchedMuonTrackType", "", nBinsTrackType, minTrackType, maxTrackType);
		histTfMatchedMuonDeltaPhi = new TH1D("tfMatchedMuonDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

		histTfMatchedMuonPt_vs_MuonEta  = new TH2D("tfMatchedMuonPt_vs_MuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
		histTfMatchedMuonEta_vs_MuonPt  = new TH2D("tfMatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histTfMatchedMuonEta_vs_MuonPhi  = new TH2D("tfMatchedMuonEta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		for (int tfType : {Utility::Bmtf, Utility::Omtf, Utility::Emtf, Utility::UGMT}) {
			histTfMapMatchedMuonPt.insert({tfType, new TH1D(("tfMatchedMuonPt_" + Utility::TfNames.at(tfType)).c_str(), "", 23, ptBinning)});
			histTfMapMatchedMuonPtFineBinning.insert({tfType, new TH1D(("tfMatchedMuonPtFineBinning_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPt, minPt, maxPt)});
			histTfMapMatchedMuonEta.insert({tfType, new TH1D(("tfMatchedMuonEta_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsEta, minEta, maxEta)});
			histTfMapMatchedMuonPhi.insert({tfType, new TH1D(("tfMatchedMuonPhi_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPhi, minPhi, maxPhi)});

			histTfMapMatchedMuonTfType.insert({tfType, new TH1D(("tfMatchedMuonTfType_" + Utility::TfNames.at(tfType)).c_str(), "", 4, 0, 4)});

			histProbeMuonMapPt.insert({tfType, new TH1D(("probeMuonPt_" + Utility::TfNames.at(tfType)).c_str(), "", 23, ptBinning)});
			histProbeMuonMapPtFineBinning.insert({tfType, new TH1D(("probeMuonPtFineBinning_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPt, minPt, maxPt)});
			histProbeMuonMapEta.insert({tfType, new TH1D(("probeMuonEta_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsEta, minEta, maxEta)});
			histProbeMuonMapPhi.insert({tfType, new TH1D(("probeMuonPhi_" + Utility::TfNames.at(tfType)).c_str(), "", nBinsPhi, minPhi, maxPhi)});
		}
	}

	histIsBmtfMatchedDttp = new TH1D("isBmtfMatchedDttp", "", 2, 0, 2);
	//histBmtfMatchedDttpPhi = new TH1D("bmtfMatchedDttpPhi", "", 64, -2048, 2048);
	histBmtfMatchedDttpPhi = new TH1D("bmtfMatchedDttpPhi", "", nBinsPhi, -2048, 2048);
	//histBmtfMatchedDttpCmsPt = new TH1D("bmtfMatchedDttpCmsPt", "", nBinsPt, minPt, maxPt);
	histBmtfMatchedDttpCmsPt = new TH1D("bmtfMatchedDttpCmsPt", "", 23, ptBinning);
	histBmtfMatchedDttpDeltaPhi = new TH1D("bmtfMatchedDttpDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpCmsPhi = new TH1D("bmtfMatchedDttpCmsPhi", "", nBinsPhi, minPhi, maxPhi);

	histBmtfMatchedDttpDeltaPhiSt1 = new TH1D("bmtfMatchedDttpDeltaPhiSt1", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt2 = new TH1D("bmtfMatchedDttpDeltaPhiSt2", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt3 = new TH1D("bmtfMatchedDttpDeltaPhiSt3", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt4 = new TH1D("bmtfMatchedDttpDeltaPhiSt4", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

	histIsDttpMatchedHo = new TH1D("isDttpMatchedHo", "", 2, 0, 2);
	histDttpMatchedHoDeltaIPhi = new TH1D("dttpMatchedHoDeltaIPhi", "", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histDttpMatchedHoDeltaPhi = new TH1D("dttpMatchedHoDeltaPhi", "", 2*nBinsPhi, -maxPhi, maxPhi);
	histDttpMatchedHoIPhi = new TH1D("dttpMatchedHoIPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histDttpMatchedHoIEta = new TH1D("dttpMatchedHoIEta", "", nBinsIEta, minIEta, maxIEta);
	histDttpMatchedHoCmsPhi = new TH1D("dttpMatchedHoCmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histDttpMatchedHoCmsEta = new TH1D("dttpMatchedHoCmsEta", "", nBinsEta, minEta, maxEta);

	histIsDttpMatchedHoN3x3 = new TH1D("isDttpMatchedHoN3x3", "", 2, 0, 2);
	histDttpMatchedHoN3x3 = new TH1D("dttpMatchedHoN3x3", "", 10, 0, 10);
	histDttpMatchedHoN3x3DeltaIPhi = new TH1D("dttpMatchedHoN3x3DeltaIPhi", "", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histDttpMatchedHoN3x3DeltaPhi = new TH1D("dttpMatchedHoN3x3DeltaPhi", "", 2*nBinsPhi, -maxPhi, maxPhi);
	histDttpMatchedHoN3x3IPhi = new TH1D("dttpMatchedHoN3x3IPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histDttpMatchedHoN3x3IEta = new TH1D("dttpMatchedHoN3x3IEta", "", nBinsIEta, minIEta, maxIEta);
	histDttpMatchedHoN3x3CmsPhi = new TH1D("dttpMatchedHoN3x3CmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histDttpMatchedHoN3x3CmsEta = new TH1D("dttpMatchedHoN3x3CmsEta", "", nBinsEta, minEta, maxEta);



	if (hasRecoMuon) {
		//histIsoMb1MatchedMuonPt = new TH1D("isoMb1MatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonPt = new TH1D("isoMb1MatchedMuonPt", "", 23, ptBinning);
		/*
		histIsoMb1MatchedMuonPtAtIEtaP3 = new TH1D("isoMb1MatchedMuonPtAtIEtaP3", "", 23, ptBinning);
		histIsoMb1MatchedMuonPtAtIEtaM3 = new TH1D("isoMb1MatchedMuonPtAtIEtaM3", "", 23, ptBinning);
		*/
		histIsoMb1MatchedMuonPtFineBinning = new TH1D("isoMb1MatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonEta = new TH1D("isoMb1MatchedMuonEta", "", nBinsEta, minEta, maxEta);
		histIsoMb1MatchedMuonEtaLowPt = new TH1D("isoMb1MatchedMuonEtaLowPt", "", nBinsEta, minEta, maxEta);
		histIsoMb1MatchedMuonEtaHighPt = new TH1D("isoMb1MatchedMuonEtaHighPt", "", nBinsEta, minEta, maxEta);
		histIsoMb1MatchedMuonPhi = new TH1D("isoMb1MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb1MatchedMuonEta_vs_MuonPt = new TH2D("isoMb1MatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb1MatchedMuonEta_vs_MuonPhi = new TH2D("isoMb1MatchedMuonEta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		//histIsoMb2MatchedMuonPt = new TH1D("isoMb2MatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonPt = new TH1D("isoMb2MatchedMuonPt", "", 23, ptBinning);
		/*
		histIsoMb2MatchedMuonPtAtIEtaP3 = new TH1D("isoMb2MatchedMuonPtAtIEtaP3", "", 23, ptBinning);
		histIsoMb2MatchedMuonPtAtIEtaM3 = new TH1D("isoMb2MatchedMuonPtAtIEtaM3", "", 23, ptBinning);
		*/
		histIsoMb2MatchedMuonPtFineBinning = new TH1D("isoMb2MatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonEta = new TH1D("isoMb2MatchedMuonEta", "", nBinsEta, minEta, maxEta);
		histIsoMb2MatchedMuonEtaLowPt = new TH1D("isoMb2MatchedMuonEtaLowPt", "", nBinsEta, minEta, maxEta);
		histIsoMb2MatchedMuonEtaHighPt = new TH1D("isoMb2MatchedMuonEtaHighPt", "", nBinsEta, minEta, maxEta);
		histIsoMb2MatchedMuonPhi = new TH1D("isoMb2MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb2MatchedMuonEta_vs_MuonPt = new TH2D("isoMb2MatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb2MatchedMuonEta_vs_MuonPhi = new TH2D("isoMb2MatchedMuonEta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		//histIsoMb12MatchedMuonPt = new TH1D("isoMb12MatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonPt = new TH1D("isoMb12MatchedMuonPt", "", 23, ptBinning);
		/*
		histIsoMb12MatchedMuonPtAtIEtaP3 = new TH1D("isoMb12MatchedMuonPtAtIEtaP3", "", 23, ptBinning);
		histIsoMb12MatchedMuonPtAtIEtaM3 = new TH1D("isoMb12MatchedMuonPtAtIEtaM3", "", 23, ptBinning);
		*/
		histIsoMb12MatchedMuonPtFineBinning = new TH1D("isoMb12MatchedMuonPtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonEta = new TH1D("isoMb12MatchedMuonEta", "", nBinsEta, minEta, maxEta);
		/*
		histIsoMb12MatchedMuonEtaLowPt = new TH1D("isoMb12MatchedMuonEtaLowPt", "", nBinsEta, minEta, maxEta);
		histIsoMb12MatchedMuonEtaHighPt = new TH1D("isoMb12MatchedMuonEtaHighPt", "", nBinsEta, minEta, maxEta);
		*/
		histIsoMb12MatchedMuonPhi = new TH1D("isoMb12MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb12MatchedMuonEta_vs_MuonPt = new TH2D("isoMb12MatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb12MatchedMuonEta_vs_MuonPhi = new TH2D("isoMb12MatchedMuonEta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		//histIsoMb1MatchedMuonN3x3Pt = new TH1D("isoMb1MatchedMuonN3x3Pt", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonN3x3Pt = new TH1D("isoMb1MatchedMuonN3x3Pt", "", 23, ptBinning);
		/*
		histIsoMb1MatchedMuonN3x3PtAtIEtaP3 = new TH1D("isoMb1MatchedMuonN3x3PtAtIEtaP3", "", 23, ptBinning);
		histIsoMb1MatchedMuonN3x3PtAtIEtaM3 = new TH1D("isoMb1MatchedMuonN3x3PtAtIEtaM3", "", 23, ptBinning);
		*/
		histIsoMb1MatchedMuonN3x3PtFineBinning = new TH1D("isoMb1MatchedMuonN3x3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonN3x3Eta = new TH1D("isoMb1MatchedMuonN3x3Eta", "", nBinsEta, minEta, maxEta);
		/*
		histIsoMb1MatchedMuonN3x3EtaLowPt = new TH1D("isoMb1MatchedMuonN3x3EtaLowPt", "", nBinsEta, minEta, maxEta);
		histIsoMb1MatchedMuonN3x3EtaHighPt = new TH1D("isoMb1MatchedMuonN3x3EtaHighPt", "", nBinsEta, minEta, maxEta);
		*/
		histIsoMb1MatchedMuonN3x3Phi = new TH1D("isoMb1MatchedMuonN3x3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb1MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb1MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb1MatchedMuonN3x3Eta_vs_MuonPhi = new TH2D("isoMb1MatchedMuonN3x3Eta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		//histIsoMb2MatchedMuonN3x3Pt = new TH1D("isoMb2MatchedMuonN3x3Pt", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonN3x3Pt = new TH1D("isoMb2MatchedMuonN3x3Pt", "", 23, ptBinning);
		/*
		histIsoMb2MatchedMuonN3x3PtAtIEtaP3 = new TH1D("isoMb2MatchedMuonN3x3PtAtIEtaP3", "", 23, ptBinning);
		histIsoMb2MatchedMuonN3x3PtAtIEtaM3 = new TH1D("isoMb2MatchedMuonN3x3PtAtIEtaM3", "", 23, ptBinning);
		*/
		histIsoMb2MatchedMuonN3x3PtFineBinning = new TH1D("isoMb2MatchedMuonN3x3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonN3x3Eta = new TH1D("isoMb2MatchedMuonN3x3Eta", "", nBinsEta, minEta, maxEta);
		histIsoMb2MatchedMuonN3x3EtaLowPt = new TH1D("isoMb2MatchedMuonN3x3EtaLowPt", "", nBinsEta, minEta, maxEta);
		histIsoMb2MatchedMuonN3x3EtaHighPt = new TH1D("isoMb2MatchedMuonN3x3EtaHighPt", "", nBinsEta, minEta, maxEta);
		histIsoMb2MatchedMuonN3x3Phi = new TH1D("isoMb2MatchedMuonN3x3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb2MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb2MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb2MatchedMuonN3x3Eta_vs_MuonPhi = new TH2D("isoMb2MatchedMuonN3x3Eta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		//histIsoMb12MatchedMuonN3x3Pt = new TH1D("isoMb12MatchedMuonN3x3Pt", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonN3x3Pt = new TH1D("isoMb12MatchedMuonN3x3Pt", "", 23, ptBinning);
		/*
		histIsoMb12MatchedMuonN3x3PtAtIEtaP3 = new TH1D("isoMb12MatchedMuonN3x3PtAtIEtaP3", "", 23, ptBinning);
		histIsoMb12MatchedMuonN3x3PtAtIEtaM3 = new TH1D("isoMb12MatchedMuonN3x3PtAtIEtaM3", "", 23, ptBinning);
		*/
		histIsoMb12MatchedMuonN3x3PtFineBinning = new TH1D("isoMb12MatchedMuonN3x3PtFineBinning", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonN3x3Eta = new TH1D("isoMb12MatchedMuonN3x3Eta", "", nBinsEta, minEta, maxEta);
		/*
		histIsoMb12MatchedMuonN3x3EtaLowPt = new TH1D("isoMb12MatchedMuonN3x3EtaLowPt", "", nBinsEta, minEta, maxEta);
		histIsoMb12MatchedMuonN3x3EtaHighPt = new TH1D("isoMb12MatchedMuonN3x3EtaHighPt", "", nBinsEta, minEta, maxEta);
		*/
		histIsoMb12MatchedMuonN3x3Phi = new TH1D("isoMb12MatchedMuonN3x3Phi", "", nBinsPhi, minPhi, maxPhi);
		histIsoMb12MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb12MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);
		histIsoMb12MatchedMuonN3x3Eta_vs_MuonPhi = new TH2D("isoMb12MatchedMuonN3x3Eta_vs_MuonPhi", "", nBinsEta, minEta, maxEta, nBinsPhi, minPhi, maxPhi);

		histIsDttpMatchedMuon = new TH1D("isDttpMatchedMuon", "", 2, 0, 2);
		histDttpMatchedMuonDeltaR = new TH1D("dttpMatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
	}
	histHoN3x3Hit = new TH1D("nMuonMatchedDttpHoN3x3Hit", "", 10, 0, 10);
}

HoHistogramCollection::~HoHistogramCollection(){}
