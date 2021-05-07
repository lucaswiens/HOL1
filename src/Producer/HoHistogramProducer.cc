#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>

HoHistogramProducer::HoHistogramProducer(HoHistogramCollection* histCollection) {
	//BMTF
	double minE   = 0,    minPt   = 0,    minPhi   = -M_PI, minEta   = -3, minWheel  = -3, minStation   = 1, minSection   =  0, minQualityCode   =  0, minDeltaR   = 0, minTrackType   =  0, minIPhi   =  1, minIEta   = -20;
	double maxE   = 1000, maxPt   = 1000, maxPhi   =  M_PI, maxEta   =  3, maxWheel  =  4, maxStation   = 5, maxSection   = 12, maxQualityCode   = 10, maxDeltaR   = 3, maxTrackType   = 25, maxIPhi   = 73, maxIEta   =  20;
	int    nBinsE = 1000, nBinsPt = 1000, nBinsPhi = 256,   nBinsEta = 68, nBinsWheel = 7, nBinsStation = 4, nBinsSection = 12, nBinsQualityCode = 10, nBinsDeltaR = 3, nBinsTrackType = 25, nBinsIPhi = 72, nBinsIEta =  40;

	// Muon Histograms
	histCollection->histIsLooseMuon = new TH1I("isLooseMuon", "isLooseMuon", 2, 0, 2);
	histCollection->histIsMediumMuon = new TH1I("isMediumMuon", "isMediumMuon", 2, 0, 2);
	histCollection->histIsTightMuon = new TH1I("isTightMuon", "isTightMuon", 2, 0, 2);

	histCollection->histMuonE = new TH1F("muonE", "muonE", nBinsE, minE, maxE);
	histCollection->histMuonEt = new TH1F("muonEt", "muonEt", nBinsE, minE, maxE);
	histCollection->histMuonPt = new TH1F("muonPt", "muonPt", nBinsPt, minPt, maxPt);
	histCollection->histMuonEta = new TH1F("muonEta", "muonEta", nBinsEta, minEta, maxEta);
	histCollection->histMuonPhi = new TH1F("muonPhi", "muonPhi", nBinsPhi, minPhi, maxPhi);
	histCollection->histMuonIso = new TH1F("muonIso", "muonIso", 100, 0, 1);
	histCollection->histMuonHltIsoDeltaR = new TH1F("muonHlt_isoDeltaR", "muonHlt_isoDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histMuonDeltaR = new TH1F("muonHlt_deltaR", "muonHlt_deltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histMuonEtaSt1 = new TH1F("muonEtaSt1", "muonEtaSt1", nBinsEta, minEta, maxEta);
	histCollection->histMuonPhiSt1 = new TH1F("muonPhiSt1", "muonPhiSt1", nBinsPhi, minPhi, maxPhi);
	histCollection->histMuonEtaSt2 = new TH1F("muonEtaSt2", "muonEtaSt2", nBinsEta, minEta, maxEta);
	histCollection->histMuonPhiSt2 = new TH1F("muonPhiSt2", "muonPhiSt2", nBinsPhi, minPhi, maxPhi);

	histCollection->histMuonMet = new TH1D("muonMet", "muonMet", nBinsPt, minPt, maxPt);
	histCollection->histMuonMt = new TH1D("muonMt", "muonMt", nBinsPt, minPt, maxPt);

	histCollection->histMuonHltIsoMu = new TH1I("muonHlt_isomu", "muonHlt_isomu", 2, 0, 2);
	histCollection->histMuonHltMu = new TH1I("muonHlt_mu", "muonHlt_mu", 2, 0, 2);
	histCollection->histMuonPassesSingleMuon = new TH1I("muonPassesSingleMuon", "muonPassesSingleMuon", 2, 0, 2);
	histCollection->histMuonCharge = new TH1I("muonCharge", "muonCharge", 3, -1, 1);
	histCollection->histMuonIEta = new TH1I("muonIEta", "muonIEta", nBinsIEta, minIEta, maxIEta);

	// DTTP Histograms
	histCollection->histDttpSize = new TH1I("dttpSize", "dttpSize", 15, 0, 15);
	histCollection->histDttpBx = new TH1I("dttpBx", "dttpBx", 5, -2, 2);
	histCollection->histDttpWheel = new TH1I("dttpWheel", "dttpWheel", nBinsWheel, minWheel, maxWheel);
	histCollection->histDttpSection = new TH1I("dttpSection", "dttpSection", nBinsSection, minSection, maxSection);
	histCollection->histDttpStation = new TH1I("dttpStation", "dttpStation", nBinsStation, minStation, maxStation);
	histCollection->histDttpQualityCode = new TH1I("dttpQualitytCode", "dttpQualitytCode", nBinsQualityCode, minQualityCode, maxQualityCode);
	histCollection->histDttpTs2Tag = new TH1I("dttpTs2Tag", "dttpTs2Tag", 2, 0, 2);
	histCollection->histDttpIPhi = new TH1I("dttpIPhi", "dttpIPhi", 72, 1, 73);
	histCollection->histDttpPhi = new TH1F("dttpPhi", "dttpPhi", 512, -2048, 2048);
	histCollection->histDttpPhiB = new TH1F("dttpPhiB", "dttpPhiB", 500, -250, 250);
	histCollection->histDttpPt = new TH1D("dttpPt", "dttpPt", 300, 0, 300);
	histCollection->histDttpCmsPhi = new TH1D("dttpCmsPhi", "dttpCmsPhi", nBinsPhi, minPhi, maxPhi);

	/*
	histCollection->histDttpCmsPhiSection1 = new TH1D("dttpCmsPhiSection1", "dttpCmsPhiSection1", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection2 = new TH1D("dttpCmsPhiSection2", "dttpCmsPhiSection2", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection3 = new TH1D("dttpCmsPhiSection3", "dttpCmsPhiSection3", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection4 = new TH1D("dttpCmsPhiSection4", "dttpCmsPhiSection4", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection5 = new TH1D("dttpCmsPhiSection5", "dttpCmsPhiSection5", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection6 = new TH1D("dttpCmsPhiSection6", "dttpCmsPhiSection6", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection7 = new TH1D("dttpCmsPhiSection7", "dttpCmsPhiSection7", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection8 = new TH1D("dttpCmsPhiSection8", "dttpCmsPhiSection8", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection9 = new TH1D("dttpCmsPhiSection9", "dttpCmsPhiSection9", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection10 = new TH1D("dttpCmsPhiSection10", "dttpCmsPhiSection10", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection11 = new TH1D("dttpCmsPhiSection11", "dttpCmsPhiSection11", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpCmsPhiSection12 = new TH1D("dttpCmsPhiSection12", "dttpCmsPhiSection12", nBinsPhi, minPhi, maxPhi);
	*/

	// BMTF Producer
	histCollection->histNBmtf = new TH1S("nBmtf", "nBmtf", 25, 0, 25);
	histCollection->histBmtfHwPt = new TH1S("bmtfHwPt", "bmtfHwPt", nBinsPt, minPt, maxPt);
	histCollection->histBmtfCmsPt = new TH1D("bmtfCmsPt", "bmtfCmsPt", nBinsPt, minPt, maxPt);
	histCollection->histBmtfHwEta = new TH1S("bmtfHwEta", "bmtfHwEta", 25, 0, 25);
	histCollection->histBmtfCmsEta = new TH1D("bmtfCmsEta", "bmtfCmsEta", nBinsEta, minEta, maxEta);
	histCollection->histBmtfHwPhi = new TH1S("bmtfHwPhi", "bmtfHwPhi", 56, 0, 56);
	histCollection->histBmtfGlobalPhi = new TH1S("bmtfGlobalPhi", "bmtfGlobalPhi", 576, 0, 576);
	histCollection->histBmtfCmsPhi = new TH1D("bmtfCmsPhi", "bmtfCmsPhi", 144, minPhi, maxPhi);
	histCollection->histBmtfHwSign = new TH1S("bmtfHwSign", "bmtfHwSign", 5, -2, 3);
	histCollection->histBmtfHwSignValid = new TH1S("bmtfHwSignValid", "bmtfHwSignValid", 2, 0, 2);
	histCollection->histBmtfHwQual = new TH1S("bmtfHwQual", "bmtfHwQual", 25, 0, 25);
	histCollection->histBmtfLink = new TH1S("bmtfLink", "bmtfLink", 25, 0, 25);
	histCollection->histBmtfProcessor = new TH1S("bmtfProcessor", "bmtfProcessor", 25, 0, 25);
	histCollection->histBmtfTrackFinderType = new TH1S("bmtfTrackFinderType", "bmtfTrackFinderType", 25, 0, 25);
	histCollection->histBmtfTrackType = new TH1S("bmtfTrackType", "bmtfTrackType", 25, 0, 25);
	histCollection->histBmtfHwHF = new TH1S("bmtfHwHF", "bmtfHwHF", 25, 0, 25);
	histCollection->histBmtfBx = new TH1S("bmtfBx", "bmtfBx", 25, 0, 25);
	histCollection->histBmtfWh = new TH1S("bmtfWh", "bmtfWh", 25, 0, 25);
	histCollection->histBmtfTrAdd = new TH1S("bmtfTrAdd", "bmtfTrAdd", 25, 0, 25);
	histCollection->histBmtfTrAddSt1 = new TH1S("bmtfTrAddSt1", "bmtfTrAddSt1", 25, 0, 25);
	histCollection->histBmtfTrAddSt2 = new TH1S("bmtfTrAddSt2", "bmtfTrAddSt2", 25, 0, 25);
	histCollection->histBmtfTrAddSt3 = new TH1S("bmtfTrAddSt3", "bmtfTrAddSt3", 25, 0, 25);
	histCollection->histBmtfTrAddSt4 = new TH1S("bmtfTrAddSt4", "bmtfTrAddSt4", 25, 0, 25);

	//histCollection->histDttpStation_vs_DttpWheel = new TH2D("MB_station_vs_wheel", "MB_station_vs_wheel", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histCollection->histDttpStation_vs_DttpWheel_Hq = new TH2D("MB_station_vs_wheel_Hq", "MB_station_vs_wheel_Hq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histCollection->histDttpStation_vs_DttpWheel_Lq = new TH2D("MB_station_vs_wheel_Lq", "MB_station_vs_wheel_Lq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histCollection->histUsedDttpStation_vs_DttpWheel = new TH2D("usedMB_station_vs_wheel", "usedMB_station_vs_wheel", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histCollection->histUsedDttpStation_vs_DttpWheel_Hq = new TH2D("usedMB_station_vs_wheel_Hq", "usedMB_station_vs_wheel_Hq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histCollection->histUsedDttpStation_vs_DttpWheel_Lq = new TH2D("usedMB_station_vs_wheel_Lq", "usedMB_station_vs_wheel_Lq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histCollection->histUnusedDttpStation_vs_DttpWheel = new TH2D("unusedMB_station_vs_wheel", "unusedMB_station_vs_wheel", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histCollection->histUnusedDttpStation_vs_DttpWheel_Hq = new TH2D("unusedMB_station_vs_wheel_Hq", "unusedMB_station_vs_wheel_Hq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histCollection->histUnusedDttpStation_vs_DttpWheel_Lq = new TH2D("unusedMB_station_vs_wheel_Lq", "unusedMB_station_vs_wheel_Lq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);

	// BMTFTheta Histograms, just for completenes
	histCollection->histBmtfThSize = new TH1I("bmtfThSize", "bmtfThSize", 25, 0, 25);
	histCollection->histBmtfThBx = new TH1I("bmtfThBx", "bmtfThBx", 6, -3, 3);
	histCollection->histBmtfThWh = new TH1I("bmtfThWh", "bmtfThWh", 6, -3, 3);
	histCollection->histBmtfThSe = new TH1I("bmtfThSe", "bmtfThSe", 15, 0, 15);
	histCollection->histBmtfThSt = new TH1I("bmtfThSt", "bmtfThSt", 5, 0, 5);
	histCollection->histBmtfThTheta = new TH1I("bmtfThTheta", "bmtfThTheta", 100, 8e7, 1e8);
	histCollection->histBmtfThCode = new TH1I("bmtfThCode", "bmtfThCode", 10, 8e7, 2e8);

	// HOTP Histogram
	histCollection->histNHcalDetIds = new TH1I("hcalDetIds", "hcalDetIds", 50, 500, 1000);
	histCollection->histSampleEnergy = new TH1F("SampleEnergy", "SampleEnergy", 25, 0, 1);
	histCollection->histHcalDetIdIEta = new TH1I("hcalDetIdIEta", "hcalDetIdIEta", 40, -20, 20);
	histCollection->histHcalDetIdIPhi = new TH1I("hcalDetIdIPhi", "hcalDetIdIPhi", 72, 1, 73);
	histCollection->histHcalCmsEta = new TH1D("hcalCmsEta", "hcalCmsEta", 68, -3, 3);
	histCollection->histHcalCmsPhi = new TH1D("hcalCmsPhi", "hcalCmsPhi", 72, -M_PI, M_PI);
	histCollection->histHcalWheel = new TH1I("hcalWheel", "hcalWheel", 5, -2, 3);
	histCollection->histHcalSection = new TH1I("hcalSection", "hcalSection", 12, 0, 12);
	histCollection->histSumQ = new TH1D("sumQ", "sumQ", 50, 0, 50);
	histCollection->histNHcalQIESamples = new TH1I("hcalQIESamples", "hcalQIESamples", 50, 5000, 12500);
	histCollection->histHcalQIESample = new TH1I("hcalQIESample", "hcalQIESample", 10, 1, 11);
	histCollection->histHcalQIESampleAdc = new TH1I("hcalQIESampleAdc", "hcalQIESampleAdc", 50, 0, 50);
	histCollection->histHcalQIESampleDv = new TH1I("hcalQIESampleDv", "hcalQIESampleDv", 2, 0, 2);
	histCollection->histHcalQIESampleEr = new TH1I("hcalQIESampleEr", "hcalQIESampleEr", 25, 0, 1);
	histCollection->histQIESampleFc = new TH1F("QIESampleFc", "QIESampleFc", 50, 0, 100);
	histCollection->histQIESamplePedestal = new TH1F("QIESamplePedestal", "QIESamplePedestal", 30, -10, 10);
	histCollection->histQIESampleFc_MPedestals = new TH1F("QIESampleFc_MPedestals", "QIESampleFc_MPedestals", 50, 0, 100);

	// Ho Matched Variables
	histCollection->histIsMb3HoIEtaMatched = new TH1S("isMb3HoIEtaMatched", "isMb3HoIEtaMatched", 2, 0, 2);
	histCollection->histIsMb4HoIEtaMatched = new TH1S("isMb4HoIEtaMatched", "isMb4HoIEtaMatched", 2, 0, 2);
	histCollection->histBmtfMb34MatchedHoIEta = new TH1I("bmtfMb34MatchedHoIEta", "bmtfMb34MatchedHoIEta", nBinsIEta, minIEta, maxIEta);
	histCollection->histBmtfMb34MatchedHoIPhi = new TH1I("bmtfMb34MatchedHoIPhi", "bmtfMb34MatchedHoIPhi", nBinsIPhi, minIPhi, maxIPhi);
	histCollection->histBmtfMb34MatchedHoDeltaIPhi = new TH1I("bmtfMb34MatchedHoDeltaIPhi", "bmtfMb34MatchedHoDeltaIPhi", 2*nBinsIPhi+1, -maxIPhi+1, maxIPhi);
	histCollection->histBmtfMb34MatchedHoDeltaR = new TH1D("bmtfMb34MatchedHoDeltaR", "bmtfMb34MatchedHoDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histBmtfMb34MatchedHoPt = new TH1D("bmtfMb34MatchedHoPt", "bmtfMb34MatchedHoPt", nBinsPt, minPt, maxPt);
	histCollection->histBmtfMb34MatchedHoCmsEta = new TH1D("bmtfMb34MatchedHoCmsEta", "bmtfMb34MatchedHoCmsEta", nBinsEta, minEta, maxEta);
	histCollection->histBmtfMb34MatchedHoCmsPhi = new TH1D("bmtfMb34MatchedHoCmsPhi", "bmtfMb34MatchedHoCmsPhi", nBinsPhi, minPhi, maxPhi);
	histCollection->histBmtfMb34MatchedHoDeltaPhi = new TH1D("bmtfMb34MatchedHoDeltaPhi", "bmtfMb34MatchedHoDeltaPhi", nBinsPhi, -maxPhi, maxPhi);
	histCollection->histBmtfMb34MatchedMuonPt = new TH1D("bmtfMb34MatchedMuonPt", "bmtfMb34MatchedMuonPt", nBinsPt, minPt, maxPt);
	histCollection->histBmtfMb34MatchedMuonEta = new TH1D("bmtfMb34MatchedMuonEta", "bmtfMb34MatchedMuonEta", nBinsEta, minEta, maxEta);
	histCollection->histBmtfMb34MatchedMuonPhi = new TH1D("bmtfMb34MatchedMuonPhi", "bmtfMb34MatchedMuonPhi", nBinsPhi, minPhi, maxPhi);
	histCollection->histBmtfMb34MatchedMuonDeltaPhi = new TH1D("bmtfMb34MatchedMuonDeltaPhi", "bmtfMb34MatchedMuonDeltaPhi", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

	histCollection->histBmtfMatchedMuonCharge = new TH1I("bmtfMatchedMuonCharge", "bmtfMatchedMuonCharge", 3, -1, 2);
	histCollection->histIsBmtfMatchedMuon = new TH1S("isBmtfMatchedMuon", "isBmtfMatchedMuon", 2, 0, 2);
	histCollection->histBmtfMatchedMuonDeltaR = new TH1D("bmtfMatchedMuonDeltaR", "bmtfMatchedMuonDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histBmtfMatchedMuonPt = new TH1D("bmtfMatchedMuonPt", "bmtfMatchedMuonPt", nBinsPt, minPt, maxPt);
	histCollection->histBmtfMatchedMuonEta = new TH1D("bmtfMatchedMuonEta", "bmtfMatchedMuonEta", nBinsEta, minEta, maxEta);
	histCollection->histBmtfMatchedMuonPhi = new TH1D("bmtfMatchedMuonPhi", "bmtfMatchedMuonPhi", nBinsPhi, minPhi, maxPhi);
	histCollection->histBmtfMatchedMuonTrackType = new TH1D("bmtfMatchedMuonTrackType", "bmtfMatchedMuonTrackType", nBinsTrackType, minTrackType, maxTrackType);
	histCollection->histBmtfMatchedMuonDeltaPhi = new TH1D("bmtfMatchedMuonDeltaPhi", "bmtfMatchedMuonDeltaPhi", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histCollection->histIsBmtfMatchedDttp = new TH1S("isBmtfMatchedDttp", "isBmtfMatchedDttp", 2, 0, 2);
	histCollection->histBmtfMatchedDttpPhi = new TH1I("bmtfMatchedDttpPhi", "bmtfMatchedDttpPhi", 64, -2048, 2048);
	histCollection->histBmtfMatchedDttpPt = new TH1D("bmtfMatchedDttpPt", "bmtfMatchedDttpPt", nBinsPt, minPt, maxPt);
	histCollection->histBmtfMatchedDttpDeltaPhi = new TH1D("bmtfMatchedDttpDeltaPhi", "bmtfMatchedDttpDeltaPhi", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histCollection->histBmtfMatchedDttpCmsPhi = new TH1D("bmtfMatchedDttpCmsPhi", "bmtfMatchedDttpCmsPhi", nBinsPhi, minPhi, maxPhi);

	histCollection->histBmtfMatchedDttpDeltaPhiSt1 = new TH1D("bmtfMatchedDttpDeltaPhiSt1", "bmtfMatchedDttpDeltaPhiSt1", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histCollection->histBmtfMatchedDttpDeltaPhiSt2 = new TH1D("bmtfMatchedDttpDeltaPhiSt2", "bmtfMatchedDttpDeltaPhiSt2", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histCollection->histBmtfMatchedDttpDeltaPhiSt3 = new TH1D("bmtfMatchedDttpDeltaPhiSt3", "bmtfMatchedDttpDeltaPhiSt3", nBinsPhi / 2, -maxPhi/4, maxPhi/4);
	histCollection->histBmtfMatchedDttpDeltaPhiSt4 = new TH1D("bmtfMatchedDttpDeltaPhiSt4", "bmtfMatchedDttpDeltaPhiSt4", nBinsPhi / 2, -maxPhi/4, maxPhi/4);

	histCollection->histIsDttpMatchedHo = new TH1S("isDttpMatchedHo", "isDttpMatchedHo", 2, 0, 2);
	histCollection->histDttpMatchedHoDeltaIPhi = new TH1I("dttpMatchedHoDeltaIPhi", "dttpMatchedHoDeltaIPhi", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histCollection->histDttpMatchedHoDeltaPhi = new TH1D("dttpMatchedHoDeltaPhi", "dttpMatchedHoDeltaPhi", 2*nBinsPhi, -maxPhi, maxPhi);
	histCollection->histDttpMatchedHoIPhi = new TH1I("dttpMatchedHoIPhi", "dttpMatchedHoIPhi", nBinsIPhi, minIPhi, maxIPhi);
	histCollection->histDttpMatchedHoIEta = new TH1I("dttpMatchedHoIEta", "dttpMatchedHoIEta", nBinsIEta, minIEta, maxIEta);
	histCollection->histDttpMatchedHoCmsPhi = new TH1D("dttpMatchedHoCmsPhi", "dttpMatchedHoCmsPhi", nBinsPhi, minPhi, maxPhi);
	histCollection->histDttpMatchedHoCmsEta = new TH1D("dttpMatchedHoCmsEta", "dttpMatchedHoCmsEta", nBinsEta, minEta, maxEta);

	histCollection->histIsDttpMatchedMuon = new TH1S("isDttpMatchedMuon", "isDttpMatchedMuon", 2, 0, 2);
	histCollection->histDttpMatchedMuonDeltaR = new TH1D("dttpMatchedMuonDeltaR", "dttpMatchedMuonDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histNHo3x3Hit = new TH1I("nMuonMatchedDttpNHo3x3Hit", "nMuonMatchedDttpNHo3x3Hit", 10, 0, 10);

	histCollection->histNUnusedMuon = new TH1S("nUnusedMuon", "nUnusedMuon", 10, 0, 10);
	histCollection->histIsMediumUnusedMuon = new TH1S("isMediumUnusedMuon", "isMediumUnusedMuon", 2, 0, 2);
	histCollection->histUnusedMuonHltIsoMu = new TH1S("unusedMuonHltIsoMu", "unusedMuonHltIsoMu", 2, 0, 2);
	histCollection->histUnusedMuonHltMu = new TH1S("unusedMuonHltMu", "unusedMuonHltMu", 2, 0, 2);
	histCollection->histUnusedMuonPassesSingleMuon = new TH1S("unusedMuonPassesSingleMuon", "unusedMuonPassesSingleMuon", 2, 0, 2);
	histCollection->histUnusedMuonHasMb1 = new TH1S("unusedMuonHasMb1", "unusedMuonHasMb1", 2, 0, 2);

	histCollection->histUnusedMuonCharge = new TH1I("unusedMuonCharge", "unusedMuonCharge", 3, -1, 2);
	histCollection->histUnusedMuonIEta = new TH1I("unusedMuonIEta", "unusedMuonIEta", nBinsIEta, minIEta, maxIEta);

	histCollection->histUnusedMuonE = new TH1D("unusedMuonE", "unusedMuonE", nBinsE, minE, maxE);
	histCollection->histUnusedMuonEt = new TH1D("unusedMuonEt", "unusedMuonEt", nBinsE, minE, maxE);
	histCollection->histUnusedMuonMet = new TH1D("unusedMuonMet", "unusedMuonMet", nBinsPt, minPt, maxPt);
	histCollection->histUnusedMuonMt = new TH1D("unusedMuonMt", "unusedMuonMt", nBinsE, minE, maxE);
	histCollection->histUnusedMuonPt = new TH1D("unusedMuonPt", "unusedMuonPt", nBinsPt, minPt, maxPt);
	histCollection->histUnusedMuonEta = new TH1D("unusedMuonEta", "unusedMuonEta", nBinsEta, minEta, maxEta);
	histCollection->histUnusedMuonPhi = new TH1D("unusedMuonPhi", "unusedMuonPhi", nBinsPhi, minPhi, maxPhi);
	histCollection->histUnusedMuonIso = new TH1D("unusedMuonIso", "unusedMuonIso", 2, 0, 2);
	histCollection->histUnusedMuonHltIsoDeltaR = new TH1D("unusedMuonHltIsoDeltaR", "unusedMuonHltIsoDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histUnusedMuonDeltaR = new TH1D("unusedMuonDeltaR", "unusedMuonDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histUnusedMuonEtaSt1 = new TH1D("unusedMuonEtaSt1", "unusedMuonEtaSt1", nBinsEta, minEta, maxEta);
	histCollection->histUnusedMuonPhiSt1 = new TH1D("unusedMuonPhiSt1", "unusedMuonPhiSt1", nBinsPhi, minPhi, maxPhi);
	histCollection->histUnusedMuonEtaSt2 = new TH1D("unusedMuonEtaSt2", "unusedMuonEtaSt2", nBinsEta, minEta, maxEta);
	histCollection->histUnusedMuonPhiSt2 = new TH1D("unusedMuonPhiSt2", "unusedMuonPhiSt2", nBinsPhi, minPhi, maxPhi);

	histCollection->histNUsedMuon = new TH1S("nUsedMuon", "nUsedMuon", 10, 0, 10);
	histCollection->histIsMediumUsedMuon = new TH1S("isMediumUsedMuon", "isMediumUsedMuon", 2, 0, 2);
	histCollection->histUsedMuonHltIsoMu = new TH1S("usedMuonHltIsoMu", "usedMuonHltIsoMu", 2, 0, 2);
	histCollection->histUsedMuonHltMu = new TH1S("usedMuonHltMu", "usedMuonHltMu", 2, 0, 2); histCollection->histUsedMuonPassesSingleMuon = new TH1S("usedMuonPassesSingleMuon", "usedMuonPassesSingleMuon", 2, 0, 2);
	histCollection->histUsedMuonHasMb1 = new TH1S("usedMuonHasMb1", "usedMuonHasMb1", 2, 0, 2);

	histCollection->histUsedMuonCharge = new TH1I("usedMuonCharge", "usedMuonCharge", 3, -1, 2);
	histCollection->histUsedMuonIEta = new TH1I("usedMuonIEta", "usedMuonIEta", nBinsIEta, minIEta, maxIEta);

	histCollection->histUsedMuonE = new TH1D("usedMuonE", "usedMuonE", nBinsE, minE, maxE);
	histCollection->histUsedMuonEt = new TH1D("usedMuonEt", "usedMuonEt", nBinsE, minE, maxE);
	histCollection->histUsedMuonMet = new TH1D("usedMuonMet", "usedMuonMet", nBinsPt, minPt, maxPt);
	histCollection->histUsedMuonMt = new TH1D("usedMuonMt", "usedMuonMt", nBinsE, minE, maxE);
	histCollection->histUsedMuonPt = new TH1D("usedMuonPt", "usedMuonPt", nBinsPt, minPt, maxPt);
	histCollection->histUsedMuonEta = new TH1D("usedMuonEta", "usedMuonEta", nBinsEta, minEta, maxEta);
	histCollection->histUsedMuonPhi = new TH1D("usedMuonPhi", "usedMuonPhi", nBinsPhi, minPhi, maxPhi);
	histCollection->histUsedMuonIso = new TH1D("usedMuonIso", "usedMuonIso", 2, 0, 2);
	histCollection->histUsedMuonHltIsoDeltaR = new TH1D("usedMuonHltIsoDeltaR", "usedMuonHltIsoDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histUsedMuonDeltaR = new TH1D("usedMuonDeltaR", "usedMuonDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histCollection->histUsedMuonEtaSt1 = new TH1D("usedMuonEtaSt1", "usedMuonEtaSt1", nBinsEta, minEta, maxEta);
	histCollection->histUsedMuonPhiSt1 = new TH1D("usedMuonPhiSt1", "usedMuonPhiSt1", nBinsPhi, minPhi, maxPhi);
	histCollection->histUsedMuonEtaSt2 = new TH1D("usedMuonEtaSt2", "usedMuonEtaSt2", nBinsEta, minEta, maxEta);
	histCollection->histUsedMuonPhiSt2 = new TH1D("usedMuonPhiSt2", "usedMuonPhiSt2", nBinsPhi, minPhi, maxPhi);
}

void HoHistogramProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	for (unsigned int i = 0; i < product->bmtfSize; i++) {
		histCollection->histIsBmtfMatchedDttp->Fill(product->isBmtfMatchedDttp.at(i));
		histCollection->histBmtfMatchedDttpDeltaPhi->Fill(product->bmtfMatchedDttpDeltaPhi.at(i));
		histCollection->histBmtfMatchedDttpPt->Fill(product->bmtfMatchedDttpPt.at(i));
		histCollection->histBmtfMatchedDttpPhi->Fill(product->bmtfMatchedDttpPhi.at(i));
		histCollection->histBmtfMatchedDttpCmsPhi->Fill(product->bmtfMatchedDttpCmsPhi.at(i));

		histCollection->histBmtfMatchedDttpDeltaPhiSt1->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(i).at(0));
		histCollection->histBmtfMatchedDttpDeltaPhiSt2->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(i).at(1));
		histCollection->histBmtfMatchedDttpDeltaPhiSt3->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(i).at(2));
		histCollection->histBmtfMatchedDttpDeltaPhiSt4->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(i).at(3));
	}

	histCollection->histNUnusedMuon->Fill(product->nUnusedMuon);
	for (int i = 0; i < product->nUnusedMuon; i++) {
		histCollection->histIsMediumUnusedMuon->Fill(product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonHltIsoMu->Fill(product->unusedMuonHltIsoMu.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonHltMu->Fill(product->unusedMuonHltMu.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonPassesSingleMuon->Fill(product->unusedMuonPassesSingleMuon.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonHasMb1->Fill(product->unusedMuonHasMb1.at(i), product->isMediumUnusedMuon.at(i));

		histCollection->histUnusedMuonCharge->Fill(product->unusedMuonCharge.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonIEta->Fill(product->unusedMuonIEta.at(i), product->isMediumUnusedMuon.at(i));

		histCollection->histUnusedMuonE->Fill(product->unusedMuonE.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonEt->Fill(product->unusedMuonEt.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonPt->Fill(product->unusedMuonPt.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonEta->Fill(product->unusedMuonEta.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonPhi->Fill(product->unusedMuonPhi.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonIso->Fill(product->unusedMuonIso.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonHltIsoDeltaR->Fill(product->unusedMuonHltIsoDeltaR.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonDeltaR->Fill(product->unusedMuonDeltaR.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonEtaSt1->Fill(product->unusedMuonEtaSt1.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonPhiSt1->Fill(product->unusedMuonPhiSt1.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonEtaSt2->Fill(product->unusedMuonEtaSt2.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonPhiSt2->Fill(product->unusedMuonPhiSt2.at(i), product->isMediumUnusedMuon.at(i));


		histCollection->histUnusedMuonMet->Fill(product->unusedMuonMet.at(i), product->isMediumUnusedMuon.at(i));
		histCollection->histUnusedMuonMt->Fill(product->unusedMuonMt.at(i), product->isMediumUnusedMuon.at(i));
	}

	histCollection->histNUsedMuon->Fill(product->nUsedMuon);
	for (int i = 0; i < product->nUsedMuon; i++) {
		histCollection->histIsMediumUsedMuon->Fill(product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonHltIsoMu->Fill(product->usedMuonHltIsoMu.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonHltMu->Fill(product->usedMuonHltMu.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonPassesSingleMuon->Fill(product->usedMuonPassesSingleMuon.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonHasMb1->Fill(product->usedMuonHasMb1.at(i), product->isMediumUsedMuon.at(i));

		histCollection->histUsedMuonCharge->Fill(product->usedMuonCharge.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonIEta->Fill(product->usedMuonIEta.at(i), product->isMediumUsedMuon.at(i));

		histCollection->histUsedMuonE->Fill(product->usedMuonE.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonEt->Fill(product->usedMuonEt.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonPt->Fill(product->usedMuonPt.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonEta->Fill(product->usedMuonEta.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonPhi->Fill(product->usedMuonPhi.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonIso->Fill(product->usedMuonIso.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonHltIsoDeltaR->Fill(product->usedMuonHltIsoDeltaR.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonDeltaR->Fill(product->usedMuonDeltaR.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonEtaSt1->Fill(product->usedMuonEtaSt1.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonPhiSt1->Fill(product->usedMuonPhiSt1.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonEtaSt2->Fill(product->usedMuonEtaSt2.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonPhiSt2->Fill(product->usedMuonPhiSt2.at(i), product->isMediumUsedMuon.at(i));


		histCollection->histUsedMuonMet->Fill(product->usedMuonMet.at(i), product->isMediumUsedMuon.at(i));
		histCollection->histUsedMuonMt->Fill(product->usedMuonMt.at(i), product->isMediumUsedMuon.at(i));
	}

	for (unsigned short i = 0; i < product->bmtfMatchedMuonCharge.size(); i++) {
		if (!product->isBmtfMatchedMuon.at(i)) { continue;}
		histCollection->histIsBmtfMatchedMuon->Fill(product->isBmtfMatchedMuon.at(i));
		histCollection->histBmtfMatchedMuonCharge->Fill(product->bmtfMatchedMuonCharge.at(i), product->isBmtfMatchedMuon.at(i));
		histCollection->histBmtfMatchedMuonDeltaR->Fill(product->bmtfMatchedMuonDeltaR.at(i), product->isBmtfMatchedMuon.at(i));
		histCollection->histBmtfMatchedMuonPt->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
		histCollection->histBmtfMatchedMuonEta->Fill(product->bmtfMatchedMuonEta.at(i), product->isBmtfMatchedMuon.at(i));
		histCollection->histBmtfMatchedMuonPhi->Fill(product->bmtfMatchedMuonPhi.at(i), product->isBmtfMatchedMuon.at(i));
		//histCollection->histBmtfMatchedMuonTrackType->Fill(product->bmtfMatchedMuonTrackType.at(i), product->isBmtfMatchedMuon.at(i));
		histCollection->histBmtfMatchedMuonDeltaPhi->Fill(product->bmtfMatchedMuonDeltaPhi.at(i), product->isBmtfMatchedMuon.at(i));
	}

	for (unsigned int i = 0; i < product->bmtfSize; i++) {
		histCollection->histIsMb3HoIEtaMatched->Fill(product->isMb3HoIEtaMatched.at(i));
		histCollection->histIsMb4HoIEtaMatched->Fill(product->isMb4HoIEtaMatched.at(i));
		const bool &isMb34Matched = product->isMb3HoIEtaMatched.at(i) || product->isMb4HoIEtaMatched.at(i);
		histCollection->histBmtfMb34MatchedHoDeltaR->Fill(product->bmtfMb34MatchedHoDeltaR.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedHoPt->Fill(product->bmtfMb34MatchedHoPt.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedHoCmsEta->Fill(product->bmtfMb34MatchedHoCmsEta.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedHoCmsPhi->Fill(product->bmtfMb34MatchedHoCmsPhi.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedHoDeltaPhi->Fill(product->bmtfMb34MatchedHoDeltaPhi.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedMuonPt->Fill(product->bmtfMb34MatchedMuonPt.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedMuonEta->Fill(product->bmtfMb34MatchedMuonEta.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedMuonPhi->Fill(product->bmtfMb34MatchedMuonPhi.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedMuonDeltaPhi->Fill(product->bmtfMb34MatchedMuonDeltaPhi.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedHoIEta->Fill(product->bmtfMb34MatchedHoIEta.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedHoIPhi->Fill(product->bmtfMb34MatchedHoIPhi.at(i), isMb34Matched);
		histCollection->histBmtfMb34MatchedHoDeltaIPhi->Fill(product->bmtfMb34MatchedHoDeltaIPhi.at(i), isMb34Matched);
		//unsigned int iMuon = product->dttpMatchedMuonIndex.at(i);
	}


	for (int i = 0; i < product->dttpSize; i++) {
		histCollection->histIsDttpMatchedHo->Fill(product->isDttpMatchedHo.at(i));

		histCollection->histDttpMatchedHoDeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(i), product->isDttpMatchedHo.at(i));

		histCollection->histIsDttpMatchedMuon->Fill(product->isDttpMatchedMuon.at(i));
		histCollection->histDttpMatchedMuonDeltaR->Fill(product->dttpMatchedMuonDeltaR.at(i));
		unsigned short iMuon = product->dttpMatchedMuonIndex.at(i);
		if (iMuon < 999) {
			histCollection->histNHo3x3Hit->Fill(product->muonMatchedDttpNHo3x3Hit.at(iMuon));
		}
	}

}

void HoHistogramProducer::EndJob(HoHistogramCollection* histCollection) {
	histCollection->efficiencyBmtf34MatchedHoPt = new TGraphAsymmErrors(histCollection->histBmtfMb34MatchedMuonPt);
	histCollection->efficiencyBmtfPt = new TGraphAsymmErrors(histCollection->histUsedMuonPt);

	//TH1D *histTmp = (TH1D*) histCollection->histUsedMuonPt->Clone();
	//histTmp->Add(histCollection->histUsedMuonPt, histCollection->histUnusedMuonPt);

	//histCollection->efficiencyBmtfPt->Divide(histCollection->histUsedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");
	//histCollection->efficiencyBmtfPt->Divide(histCollection->histBmtfMatchedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");
	//histCollection->efficiencyBmtf34MatchedHoPt->Divide(histCollection->histBmtfMb34MatchedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");

	//histCollection->efficiencyBmtfPt->Write("efficiencyBmtfPt");
	//histCollection->efficiencyBmtf34MatchedHoPt->Write("efficiencyBmtf34MatchedHoPt");
}
HoHistogramProducer::~HoHistogramProducer() {}
