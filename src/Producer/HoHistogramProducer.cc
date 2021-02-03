#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>

HoHistogramProducer::HoHistogramProducer(HoHistogramCollection* histCollection) {
	double maxE = 300, maxPt = 20, maxPhi = M_PI, maxEta = 3, maxDeltaR = 3, maxTrackType = 25, minIPhi = 1, minIEta = -20;
	double minE = 0, minPt = 0, minPhi = -M_PI, minEta = -3, minDeltaR = 0, minTrackType = 0, maxIPhi = 73, maxIEta = 20;
	int nBinsE = 100, nBinsPt = (maxPt - minPt), nBinsPhi = 72, nBinsEta = 68, nBinsDeltaR = 50, nBinsTrackType = 25, nBinsIPhi = 72, nBinsIEta = 40;

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
	histCollection->efficiencyBmtfPt->Divide(histCollection->histBmtfMatchedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");
	histCollection->efficiencyBmtf34MatchedHoPt->Divide(histCollection->histBmtfMb34MatchedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");

	histCollection->efficiencyBmtfPt->Write("efficiencyBmtfPt");
	histCollection->efficiencyBmtf34MatchedHoPt->Write("efficiencyBmtf34MatchedHoPt");
}
HoHistogramProducer::~HoHistogramProducer() {}
