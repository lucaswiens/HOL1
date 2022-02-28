#include <HOAnalysis/HOL1/interface/HoHistogramCollection.h>

HoHistogramCollection::HoHistogramCollection(const bool &hasRecoMuon) : hasRecoMuon(hasRecoMuon) {
	double minE   = 0,    minPt   = 0,    minMass = 0, minPtVs   = 0,      minPhi   = -M_PI, minEta   = -2.0*M_PI/72.0 * 15, minWheel   = -3, minStation   = 1, minSection   =  0, minQualityCode   =  0, minDeltaR   =  0, minTrackType   =  0, minIPhi   =  1, minIEta   = -20;
	double maxE   = 500,  maxPt   = 500,  maxMass = 500, maxPtVs   = 100,  maxPhi   =  M_PI, maxEta   =  2.0*M_PI/72.0 * 15, maxWheel   =  4, maxStation   = 5, maxSection   = 12, maxQualityCode   = 10, maxDeltaR   =  3, maxTrackType   = 25, maxIPhi   = 73, maxIEta   =  20;
	int    nBinsE = 1000, nBinsPt = 1000, nMass   = 500*5, nBinsPtVs = 20, nBinsPhi =  72,   nBinsEta =  30,                 nBinsWheel = 7,  nBinsStation = 4, nBinsSection = 12, nBinsQualityCode = 10, nBinsDeltaR = 30, nBinsTrackType = 25, nBinsIPhi = 72, nBinsIEta =  40;
	nBinsPt = 500;
	int nBinsPt20 = 20;

	// Number of Events
	numberOfEvents = new TH1I("numberOfEvents", "", 1, 0, 1);
	histBmtfNumber = new TH1D("bmtfNumber", "", 1, 0, 1);
	histDttpMatchedHoNumber = new TH1D("dttpMatchedHoNumber", "", 1, 0, 1);
	histDttpMatchedHoN3x3Number = new TH1D("dttpMatchedHoN3x3Number", "", 1, 0, 1);
	histBmtfMb34MatchedHoNumber = new TH1D("bmtfMb34MatchedHoNumber", "", 1, 0, 1);
	//histNumber = new TH1D("Number", "", 1, 0, 1);

	// Muon Histograms
	if (hasRecoMuon) {
		histIsLooseMuon = new TH1I("isLooseMuon", "", 2, 0, 2);
		histIsMediumMuon = new TH1I("isMediumMuon", "", 2, 0, 2);
		histIsTightMuon = new TH1I("isTightMuon", "", 2, 0, 2);

		histMuonE = new TH1F("muonE", "", nBinsE, minE, maxE);
		histMuonEt = new TH1F("muonEt", "", nBinsE, minE, maxE);
		histMuonPt = new TH1F("muonPt", "", nBinsPt, minPt, maxPt);
		histMuonPt20 = new TH1F("muonPt20", "", nBinsPt20, minPt, 20);
		histMuonEta = new TH1F("muonEta", "", nBinsEta, minEta, maxEta);
		histMuonPhi = new TH1F("muonPhi", "", nBinsPhi, minPhi, maxPhi);
		histMuonIso = new TH1F("muonIso", "", 100, 0, 1);
		histMuonHltIsoDeltaR = new TH1F("muonHlt_isoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histMuonDeltaR = new TH1F("muonHlt_deltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histMuonEtaSt1 = new TH1F("muonEtaSt1", "", nBinsEta, minEta, maxEta);
		histMuonPhiSt1 = new TH1F("muonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histMuonEtaSt2 = new TH1F("muonEtaSt2", "", nBinsEta, minEta, maxEta);
		histMuonPhiSt2 = new TH1F("muonPhiSt2", "", nBinsPhi, minPhi, maxPhi);

		histDiMuonMass = new TH1D("diMuonMass", "", nMass, minMass, maxMass);
		histSelectedDiMuonMass = new TH1D("selectedDiMuonMass", "", nMass, minMass, maxMass);

		histMuonPt_vs_MuonEta  = new TH2D("muonPt_vs_MuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
		histMuonEta_vs_MuonPt  = new TH2D("muonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);

		histMuonMet = new TH1D("muonMet", "", nBinsPt, minPt, maxPt);
		histMuonMt = new TH1D("muonMt", "", nBinsPt, minPt, maxPt);

		histMuonHltIsoMu = new TH1I("muonHlt_isomu", "", 2, 0, 2);
		histMuonHltMu = new TH1I("muonHlt_mu", "", 2, 0, 2);
		histMuonPassesSingleMuon = new TH1I("muonPassesSingleMuon", "", 2, 0, 2);
		histMuonCharge = new TH1I("muonCharge", "", 3, -1, 1);
		histMuonIEta = new TH1I("muonIEta", "", nBinsIEta, minIEta, maxIEta);
		histMuonNHo3x3Hit = new TH1I("muonNHo3x3Hit", "", 10, 0, 10);
	}

	// DTTP Histograms
	histDttpSize = new TH1I("dttpSize", "", 15, 0, 15);
	histDttpBx = new TH1I("dttpBx", "", 5, -2, 2);
	histDttpWheel = new TH1I("dttpWheel", "", nBinsWheel, minWheel, maxWheel);
	histDttpSection = new TH1I("dttpSection", "", nBinsSection, minSection, maxSection);
	histDttpStation = new TH1I("dttpStation", "", nBinsStation, minStation, maxStation);
	histDttpQualityCode = new TH1I("dttpQualitytCode", "", nBinsQualityCode, minQualityCode, maxQualityCode);
	histDttpTs2Tag = new TH1I("dttpTs2Tag", "", 2, 0, 2);
	histDttpIPhi = new TH1I("dttpIPhi", "", 72, 1, 73);
	histDttpPhi = new TH1F("dttpPhi", "", 512, -2048, 2048);
	histDttpPhiB = new TH1F("dttpPhiB", "", 500, -250, 250);
	histDttpCmsPt = new TH1D("dttpCmsPt", "", 300, 0, 300);
	histDttpCmsPhi = new TH1D("dttpCmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histDttpNHo3x3Hit = new TH1I("dttpNHo3x3Hit", "", 10, 0, 10);

	/*
	histDttpCmsPhiSection1 = new TH1D("dttpCmsPhiSection1", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection2 = new TH1D("dttpCmsPhiSection2", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection3 = new TH1D("dttpCmsPhiSection3", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection4 = new TH1D("dttpCmsPhiSection4", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection5 = new TH1D("dttpCmsPhiSection5", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection6 = new TH1D("dttpCmsPhiSection6", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection7 = new TH1D("dttpCmsPhiSection7", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection8 = new TH1D("dttpCmsPhiSection8", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection9 = new TH1D("dttpCmsPhiSection9", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection10 = new TH1D("dttpCmsPhiSection10", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection11 = new TH1D("dttpCmsPhiSection11", "", nBinsPhi, minPhi, maxPhi);
	histDttpCmsPhiSection12 = new TH1D("dttpCmsPhiSection12", "", nBinsPhi, minPhi, maxPhi);
	*/

	// BMTF Producer
	histNBmtf = new TH1S("nBmtf", "", 25, 0, 25);
	histBmtfHwPt = new TH1S("bmtfHwPt", "", nBinsPt, minPt, maxPt);
	histBmtfCmsPt = new TH1D("bmtfCmsPt", "", nBinsPt, minPt, maxPt);
	histBmtfCmsPt20 = new TH1D("bmtfCmsPt20", "", nBinsPt20, minPt, 20);
	histBmtfHwEta = new TH1S("bmtfHwEta", "", 25, 0, 25);
	histBmtfCmsEta = new TH1D("bmtfCmsEta", "", nBinsEta, minEta, maxEta);
	histBmtfHwPhi = new TH1S("bmtfHwPhi", "", 56, 0, 56);
	histBmtfGlobalPhi = new TH1S("bmtfGlobalPhi", "", 576, 0, 576);
	//histBmtfCmsPhi = new TH1D("bmtfCmsPhi", "", 144, minPhi, maxPhi);
	histBmtfCmsPhi = new TH1D("bmtfCmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histBmtfHwSign = new TH1S("bmtfHwSign", "", 5, -2, 3);
	histBmtfHwSignValid = new TH1S("bmtfHwSignValid", "", 2, 0, 2);
	histBmtfHwQual = new TH1S("bmtfHwQual", "", 25, 0, 25);
	histBmtfLink = new TH1S("bmtfLink", "", 25, 0, 25);
	histBmtfProcessor = new TH1S("bmtfProcessor", "", 25, 0, 25);
	histBmtfTrackFinderType = new TH1S("bmtfTrackFinderType", "", 25, 0, 25);
	histBmtfTrackType = new TH1S("bmtfTrackType", "", 25, 0, 25);
	histBmtfHwHF = new TH1S("bmtfHwHF", "", 25, 0, 25);
	histBmtfBx = new TH1S("bmtfBx", "", 25, 0, 25);
	histBmtfWh = new TH1S("bmtfWh", "", 25, 0, 25);
	histBmtfTrAdd = new TH1S("bmtfTrAdd", "", 25, 0, 25);
	histBmtfTrAddSt1 = new TH1S("bmtfTrAddSt1", "", 25, 0, 25);
	histBmtfTrAddSt2 = new TH1S("bmtfTrAddSt2", "", 25, 0, 25);
	histBmtfTrAddSt3 = new TH1S("bmtfTrAddSt3", "", 25, 0, 25);
	histBmtfTrAddSt4 = new TH1S("bmtfTrAddSt4", "", 25, 0, 25);

	//histDttpStation_vs_DttpWheel = new TH2D("MB_station_vs_wheel", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histDttpStation_vs_DttpWheel_Hq = new TH2D("MB_station_vs_wheel_Hq", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histDttpStation_vs_DttpWheel_Lq = new TH2D("MB_station_vs_wheel_Lq", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUsedDttpStation_vs_DttpWheel = new TH2D("usedMB_station_vs_wheel", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUsedDttpStation_vs_DttpWheel_Hq = new TH2D("usedMB_station_vs_wheel_Hq", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUsedDttpStation_vs_DttpWheel_Lq = new TH2D("usedMB_station_vs_wheel_Lq", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUnusedDttpStation_vs_DttpWheel = new TH2D("unusedMB_station_vs_wheel", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUnusedDttpStation_vs_DttpWheel_Hq = new TH2D("unusedMB_station_vs_wheel_Hq", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUnusedDttpStation_vs_DttpWheel_Lq = new TH2D("unusedMB_station_vs_wheel_Lq", "", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);

	// BMTFTheta Histograms, just for completenes
	histBmtfThSize = new TH1I("bmtfThSize", "", 25, 0, 25);
	histBmtfThBx = new TH1I("bmtfThBx", "", 6, -3, 3);
	histBmtfThWh = new TH1I("bmtfThWh", "", 6, -3, 3);
	histBmtfThSe = new TH1I("bmtfThSe", "", 15, 0, 15);
	histBmtfThSt = new TH1I("bmtfThSt", "", 5, 0, 5);
	histBmtfThTheta = new TH1I("bmtfThTheta", "", 100, 8e7, 1e8);
	histBmtfThCode = new TH1I("bmtfThCode", "", 10, 8e7, 2e8);

	// HOTP Histogram
	histNHcalDetIds = new TH1I("hcalDetIds", "", 50, 500, 1000);
	histSampleEnergy = new TH1F("SampleEnergy", "", 25, 0, 1);
	histHcalDetIdIEta = new TH1I("hcalDetIdIEta", "", nBinsIEta, minIEta, maxIEta);
	histHcalDetIdIPhi = new TH1I("hcalDetIdIPhi", "", 72, 1, 73);
	//histHcalCmsEta = new TH1D("hcalCmsEta", "", 68, -3, 3);
	histHcalCmsEta = new TH1D("hcalCmsEta", "", nBinsEta, -minEta, maxEta);
	histHcalCmsPhi = new TH1D("hcalCmsPhi", "", nBinsPhi, -M_PI, M_PI);
	histHcalWheel = new TH1I("hcalWheel", "", 5, -2, 3);
	histHcalSection = new TH1I("hcalSection", "", 12, 0, 12);
	histSumQ = new TH1D("sumQ", "", 50, 0, 50);
	histNHcalQIESamples = new TH1I("nHcalQIESamples", "", 3000, 6000, 9000);
	histHcalQIESample = new TH1I("hcalQIESample", "", 10, 1, 11);
	histHcalQIESampleAdc = new TH1I("hcalQIESampleAdc", "", 50, 0, 50);
	histHcalQIESampleDv = new TH1I("hcalQIESampleDv", "", 2, 0, 2);
	histHcalQIESampleEr = new TH1I("hcalQIESampleEr", "", 25, 0, 1);
	histQIESampleFc = new TH1F("QIESampleFc", "", 50, 0, 100);
	histQIESamplePedestal = new TH1F("QIESamplePedestal", "", 30, -10, 10);
	histQIESampleFc_MPedestals = new TH1F("QIESampleFc_MPedestals", "", 50, 0, 100);

	//histBmtfMatchedMuonPt_vs_MuonEta  = new TH2D("bmtfMatchedMuonPt_vs_MuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
	histHcalQIESamples_vs_HcalQIESampleAdc = new TH2D("HcalQIESamples_vs_HcalQIESampleAdc", "", 10, 0, 10, 50, 0, 50);

	// Ho Matched Variables
	histIsMb3HoIEtaMatched = new TH1S("isMb3HoIEtaMatched", "", 2, 0, 2);
	histIsMb4HoIEtaMatched = new TH1S("isMb4HoIEtaMatched", "", 2, 0, 2);
	histBmtfMb34MatchedHoIEta = new TH1I("bmtfMb34MatchedHoIEta", "", nBinsIEta, minIEta, maxIEta);
	histBmtfMb34MatchedHoIPhi = new TH1I("bmtfMb34MatchedHoIPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histBmtfMb34MatchedHoDeltaIPhi = new TH1I("bmtfMb34MatchedHoDeltaIPhi", "", 2*nBinsIPhi+1, -maxIPhi+1, maxIPhi);
	histBmtfMb34MatchedHoDeltaR = new TH1D("bmtfMb34MatchedHoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
	histBmtfMb34MatchedHoPt = new TH1D("bmtfMb34MatchedHoPt", "", nBinsPt, minPt, maxPt);
	histBmtfMb34MatchedHoPt20 = new TH1D("bmtfMb34MatchedHoPt20", "", nBinsPt20, minPt, 20);
	histBmtfMb34MatchedHoCmsEta = new TH1D("bmtfMb34MatchedHoCmsEta", "", nBinsEta, minEta, maxEta);
	histBmtfMb34MatchedHoCmsPhi = new TH1D("bmtfMb34MatchedHoCmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histBmtfMb34MatchedHoDeltaPhi = new TH1D("bmtfMb34MatchedHoDeltaPhi", "", nBinsPhi, -maxPhi, maxPhi);

	if (hasRecoMuon) {
		histBmtfMb34MatchedMuonPt = new TH1D("bmtfMb34MatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histBmtfMb34MatchedMuonPt20 = new TH1D("bmtfMb34MatchedMuonPt20", "", nBinsPt20, minPt, 20);
		histBmtfMb34MatchedMuonEta = new TH1D("bmtfMb34MatchedMuonEta", "", nBinsEta, minEta, maxEta);
		histBmtfMb34MatchedMuonPhi = new TH1D("bmtfMb34MatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histBmtfMb34MatchedMuonDeltaPhi = new TH1D("bmtfMb34MatchedMuonDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

		histBmtfMatchedMuonCharge = new TH1I("bmtfMatchedMuonCharge", "", 3, -1, 2);
		histIsBmtfMatchedMuon = new TH1S("isBmtfMatchedMuon", "", 2, 0, 2);
		histBmtfMatchedMuonDeltaR = new TH1D("bmtfMatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histBmtfMatchedMuonPt = new TH1D("bmtfMatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histBmtfMatchedMuonPt20 = new TH1D("bmtfMatchedMuonPt20", "", nBinsPt20, minPt, 20);
		histBmtfMatchedMuonEta = new TH1D("bmtfMatchedMuonEta", "", nBinsEta, minEta, maxEta);
		histBmtfMatchedMuonPhi = new TH1D("bmtfMatchedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histBmtfMatchedMuonTrackType = new TH1D("bmtfMatchedMuonTrackType", "", nBinsTrackType, minTrackType, maxTrackType);
		histBmtfMatchedMuonDeltaPhi = new TH1D("bmtfMatchedMuonDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

		histBmtfMatchedMuonPt_vs_MuonEta  = new TH2D("bmtfMatchedMuonPt_vs_MuonEta", "", nBinsPtVs, minPtVs, maxPtVs, nBinsEta, minEta, maxEta);
		histBmtfMatchedMuonEta_vs_MuonPt  = new TH2D("bmtfMatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);

		histMuonMatchedBmtfCmsPt = new TH1D("muonMatchedBmtfCmsPt", "", nBinsPt, minPt, maxPt);
		histMuonMatchedBmtfCmsEta = new TH1D("muonMatchedBmtfCmsEta", "", nBinsEta, minEta, maxEta);
	}

	histIsBmtfMatchedDttp = new TH1S("isBmtfMatchedDttp", "", 2, 0, 2);
	//histBmtfMatchedDttpPhi = new TH1I("bmtfMatchedDttpPhi", "", 64, -2048, 2048);
	histBmtfMatchedDttpPhi = new TH1I("bmtfMatchedDttpPhi", "", nBinsPhi, -2048, 2048);
	histBmtfMatchedDttpCmsPt = new TH1D("bmtfMatchedDttpCmsPt", "", nBinsPt, minPt, maxPt);
	histBmtfMatchedDttpDeltaPhi = new TH1D("bmtfMatchedDttpDeltaPhi", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpCmsPhi = new TH1D("bmtfMatchedDttpCmsPhi", "", nBinsPhi, minPhi, maxPhi);

	histBmtfMatchedDttpDeltaPhiSt1 = new TH1D("bmtfMatchedDttpDeltaPhiSt1", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt2 = new TH1D("bmtfMatchedDttpDeltaPhiSt2", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt3 = new TH1D("bmtfMatchedDttpDeltaPhiSt3", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histBmtfMatchedDttpDeltaPhiSt4 = new TH1D("bmtfMatchedDttpDeltaPhiSt4", "", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

	histIsDttpMatchedHo = new TH1S("isDttpMatchedHo", "", 2, 0, 2);
	histDttpMatchedHoDeltaIPhi = new TH1I("dttpMatchedHoDeltaIPhi", "", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histDttpMatchedHoDeltaPhi = new TH1D("dttpMatchedHoDeltaPhi", "", 2*nBinsPhi, -maxPhi, maxPhi);
	histDttpMatchedHoIPhi = new TH1I("dttpMatchedHoIPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histDttpMatchedHoIEta = new TH1I("dttpMatchedHoIEta", "", nBinsIEta, minIEta, maxIEta);
	histDttpMatchedHoCmsPhi = new TH1D("dttpMatchedHoCmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histDttpMatchedHoCmsEta = new TH1D("dttpMatchedHoCmsEta", "", nBinsEta, minEta, maxEta);

	histIsDttpMatchedHoN3x3 = new TH1S("isDttpMatchedHoN3x3", "", 2, 0, 2);
	histDttpMatchedHoN3x3DeltaIPhi = new TH1I("dttpMatchedHoN3x3DeltaIPhi", "", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histDttpMatchedHoN3x3DeltaPhi = new TH1D("dttpMatchedHoN3x3DeltaPhi", "", 2*nBinsPhi, -maxPhi, maxPhi);
	histDttpMatchedHoN3x3IPhi = new TH1I("dttpMatchedHoN3x3IPhi", "", nBinsIPhi, minIPhi, maxIPhi);
	histDttpMatchedHoN3x3IEta = new TH1I("dttpMatchedHoN3x3IEta", "", nBinsIEta, minIEta, maxIEta);
	histDttpMatchedHoN3x3CmsPhi = new TH1D("dttpMatchedHoN3x3CmsPhi", "", nBinsPhi, minPhi, maxPhi);
	histDttpMatchedHoN3x3CmsEta = new TH1D("dttpMatchedHoN3x3CmsEta", "", nBinsEta, minEta, maxEta);



	if (hasRecoMuon) {
		histIsoMb1MatchedMuonPt = new TH1D("isoMb1MatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonPt20 = new TH1D("isoMb1MatchedMuonPt20", "", nBinsPt20, 0, 20);
		histIsoMb1MatchedMuonEta = new TH1D("isoMb1MatchedMuonEta", "", nBinsEta, minEta, maxEta);
		histIsoMb1MatchedMuonEta_vs_MuonPt = new TH2D("isoMb1MatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);

		histIsoMb2MatchedMuonPt = new TH1D("isoMb2MatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonPt20 = new TH1D("isoMb2MatchedMuonPt20", "", nBinsPt20, 0, 20);
		histIsoMb2MatchedMuonEta = new TH1D("isoMb2MatchedMuonEta", "", nBinsEta, minEta, maxEta);
		histIsoMb2MatchedMuonEta_vs_MuonPt = new TH2D("isoMb2MatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);

		histIsoMb12MatchedMuonPt = new TH1D("isoMb12MatchedMuonPt", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonPt20 = new TH1D("isoMb12MatchedMuonPt20", "", nBinsPt20, 0, 20);
		histIsoMb12MatchedMuonEta = new TH1D("isoMb12MatchedMuonEta", "", nBinsEta, minEta, maxEta);
		histIsoMb12MatchedMuonEta_vs_MuonPt = new TH2D("isoMb12MatchedMuonEta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);

		histIsoMb1MatchedMuonN3x3Pt = new TH1D("isoMb1MatchedMuonN3x3Pt", "", nBinsPt, minPt, maxPt);
		histIsoMb1MatchedMuonN3x3Pt20 = new TH1D("isoMb1MatchedMuonN3x3Pt20", "", nBinsPt20, 0, 20);
		histIsoMb1MatchedMuonN3x3Eta = new TH1D("isoMb1MatchedMuonN3x3Eta", "", nBinsEta, minEta, maxEta);
		histIsoMb1MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb1MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);

		histIsoMb2MatchedMuonN3x3Pt = new TH1D("isoMb2MatchedMuonN3x3Pt", "", nBinsPt, minPt, maxPt);
		histIsoMb2MatchedMuonN3x3Pt20 = new TH1D("isoMb2MatchedMuonN3x3Pt20", "", nBinsPt20, 0, 20);
		histIsoMb2MatchedMuonN3x3Eta = new TH1D("isoMb2MatchedMuonN3x3Eta", "", nBinsEta, minEta, maxEta);
		histIsoMb2MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb2MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);

		histIsoMb12MatchedMuonN3x3Pt = new TH1D("isoMb12MatchedMuonN3x3Pt", "", nBinsPt, minPt, maxPt);
		histIsoMb12MatchedMuonN3x3Pt20 = new TH1D("isoMb12MatchedMuonN3x3Pt20", "", nBinsPt20, 0, 20);
		histIsoMb12MatchedMuonN3x3Eta = new TH1D("isoMb12MatchedMuonN3x3Eta", "", nBinsEta, minEta, maxEta);
		histIsoMb12MatchedMuonN3x3Eta_vs_MuonPt = new TH2D("isoMb12MatchedMuonN3x3Eta_vs_MuonPt", "", nBinsEta, minEta, maxEta, nBinsPtVs, minPtVs, maxPtVs);

		histIsDttpMatchedMuon = new TH1S("isDttpMatchedMuon", "", 2, 0, 2);
		histDttpMatchedMuonDeltaR = new TH1D("dttpMatchedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
	}
	histNHo3x3Hit = new TH1I("nMuonMatchedDttpNHo3x3Hit", "", 10, 0, 10);

	if (hasRecoMuon) {
		histNUnusedMuon = new TH1S("nUnusedMuon", "", 10, 0, 10);
		histIsMediumUnusedMuon = new TH1S("isMediumUnusedMuon", "", 2, 0, 2);
		histUnusedMuonHltIsoMu = new TH1S("unusedMuonHltIsoMu", "", 2, 0, 2);
		histUnusedMuonHltMu = new TH1S("unusedMuonHltMu", "", 2, 0, 2);
		histUnusedMuonPassesSingleMuon = new TH1S("unusedMuonPassesSingleMuon", "", 2, 0, 2);
		histUnusedMuonHasMb1 = new TH1S("unusedMuonHasMb1", "", 2, 0, 2);

		histUnusedMuonCharge = new TH1I("unusedMuonCharge", "", 3, -1, 2);
		histUnusedMuonIEta = new TH1I("unusedMuonIEta", "", nBinsIEta, minIEta, maxIEta);
		histUnusedMuonNHo3x3Hit = new TH1I("unusedNHo3x3Hit", "", 10, 0, 10);

		histUnusedMuonE = new TH1D("unusedMuonE", "", nBinsE, minE, maxE);
		histUnusedMuonEt = new TH1D("unusedMuonEt", "", nBinsE, minE, maxE);
		histUnusedMuonMet = new TH1D("unusedMuonMet", "", nBinsPt, minPt, maxPt);
		histUnusedMuonMt = new TH1D("unusedMuonMt", "", nBinsE, minE, maxE);
		histUnusedMuonPt = new TH1D("unusedMuonPt", "", nBinsPt, minPt, maxPt);
		histUnusedMuonPt20 = new TH1D("unusedMuonPt20", "", nBinsPt20, minPt, 20);
		histUnusedMuonEta = new TH1D("unusedMuonEta", "", nBinsEta, minEta, maxEta);
		histUnusedMuonPhi = new TH1D("unusedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histUnusedMuonIso = new TH1D("unusedMuonIso", "", 2, 0, 2);
		histUnusedMuonHltIsoDeltaR = new TH1D("unusedMuonHltIsoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histUnusedMuonDeltaR = new TH1D("unusedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histUnusedMuonEtaSt1 = new TH1D("unusedMuonEtaSt1", "", nBinsEta, minEta, maxEta);
		histUnusedMuonPhiSt1 = new TH1D("unusedMuonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histUnusedMuonEtaSt2 = new TH1D("unusedMuonEtaSt2", "", nBinsEta, minEta, maxEta);
		histUnusedMuonPhiSt2 = new TH1D("unusedMuonPhiSt2", "", nBinsPhi, minPhi, maxPhi);

		histNUsedMuon = new TH1S("nUsedMuon", "", 10, 0, 10);
		histIsMediumUsedMuon = new TH1S("isMediumUsedMuon", "", 2, 0, 2);
		histUsedMuonHltIsoMu = new TH1S("usedMuonHltIsoMu", "", 2, 0, 2);
		histUsedMuonHltMu = new TH1S("usedMuonHltMu", "", 2, 0, 2);
		histUsedMuonPassesSingleMuon = new TH1S("usedMuonPassesSingleMuon", "", 2, 0, 2);
		histUsedMuonHasMb1 = new TH1S("usedMuonHasMb1", "", 2, 0, 2);

		histUsedMuonCharge = new TH1I("usedMuonCharge", "", 3, -1, 2);
		histUsedMuonIEta = new TH1I("usedMuonIEta", "", nBinsIEta, minIEta, maxIEta);
		histUsedMuonNHo3x3Hit = new TH1I("usedMuonNHo3x3Hit", "", 10, 0, 10);

		histUsedMuonE = new TH1D("usedMuonE", "", nBinsE, minE, maxE);
		histUsedMuonEt = new TH1D("usedMuonEt", "", nBinsE, minE, maxE);
		histUsedMuonMet = new TH1D("usedMuonMet", "", nBinsPt, minPt, maxPt);
		histUsedMuonMt = new TH1D("usedMuonMt", "", nBinsE, minE, maxE);
		histUsedMuonPt = new TH1D("usedMuonPt", "", nBinsPt, minPt, maxPt);
		histUsedMuonPt20 = new TH1D("usedMuonPt20", "", nBinsPt20, minPt, 20);
		histUsedMuonEta = new TH1D("usedMuonEta", "", nBinsEta, minEta, maxEta);
		histUsedMuonPhi = new TH1D("usedMuonPhi", "", nBinsPhi, minPhi, maxPhi);
		histUsedMuonIso = new TH1D("usedMuonIso", "", 2, 0, 2);
		histUsedMuonHltIsoDeltaR = new TH1D("usedMuonHltIsoDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histUsedMuonDeltaR = new TH1D("usedMuonDeltaR", "", nBinsDeltaR, minDeltaR, maxDeltaR);
		histUsedMuonEtaSt1 = new TH1D("usedMuonEtaSt1", "", nBinsEta, minEta, maxEta);
		histUsedMuonPhiSt1 = new TH1D("usedMuonPhiSt1", "", nBinsPhi, minPhi, maxPhi);
		histUsedMuonEtaSt2 = new TH1D("usedMuonEtaSt2", "", nBinsEta, minEta, maxEta);
		histUsedMuonPhiSt2 = new TH1D("usedMuonPhiSt2", "", nBinsPhi, minPhi, maxPhi);
	}
}

HoHistogramCollection::~HoHistogramCollection(){}
