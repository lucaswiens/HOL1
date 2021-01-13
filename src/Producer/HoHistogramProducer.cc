#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>

HoHistogramProducer::HoHistogramProducer() {
	int nBinsE = 100, nBinsPt = 100, nBinsPhi = 72, nBinsEta = 68, nBinsDeltaR = 50, nBinsTrackType = 25, nBinsIPhi = 72, nBinsIEta = 40;
	double maxE = 300, maxPt = 300, maxPhi = M_PI, maxEta = 3, maxDeltaR = 3, maxTrackType = 25, minIPhi = 1, minIEta = -20;
	double minE = 0, minPt = 0, minPhi = -M_PI, minEta = -3, minDeltaR = 0, minTrackType = 0, maxIPhi = 73, maxIEta = 20;

	histIsMb3HoIEtaMatched = new TH1S("isMb3HoIEtaMatched", "isMb3HoIEtaMatched", 2, 0, 2);
	histIsMb4HoIEtaMatched = new TH1S("isMb4HoIEtaMatched", "isMb4HoIEtaMatched", 2, 0, 2);
	histBmtfMb34MatchedHoIEta = new TH1I("bmtfMb34MatchedHoIEta", "bmtfMb34MatchedHoIEta", nBinsIEta, minIEta, maxIEta);
	histBmtfMb34MatchedHoIPhi = new TH1I("bmtfMb34MatchedHoIPhi", "bmtfMb34MatchedHoIPhi", nBinsIPhi, minIPhi, maxIPhi);
	histBmtfMb34MatchedHoDeltaIPhi = new TH1I("bmtfMb34MatchedHoDeltaIPhi", "bmtfMb34MatchedHoDeltaIPhi", 2*nBinsIPhi+1, -maxIPhi+1, maxIPhi);
	histBmtfMb34MatchedHoDeltaR = new TH1D("bmtfMb34MatchedHoDeltaR", "bmtfMb34MatchedHoDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histBmtfMb34MatchedHoPt = new TH1D("bmtfMb34MatchedHoPt", "bmtfMb34MatchedHoPt", nBinsPt, minPt, maxPt);
	histBmtfMb34MatchedHoCmsEta = new TH1D("bmtfMb34MatchedHoCmsEta", "bmtfMb34MatchedHoCmsEta", nBinsEta, minEta, maxEta);
	histBmtfMb34MatchedHoCmsPhi = new TH1D("bmtfMb34MatchedHoCmsPhi", "bmtfMb34MatchedHoCmsPhi", nBinsPhi, minPhi, maxPhi);
	histBmtfMb34MatchedHoDeltaPhi = new TH1D("bmtfMb34MatchedHoDeltaPhi", "bmtfMb34MatchedHoDeltaPhi", 2*nBinsPhi, -maxPhi, maxPhi);
	histBmtfMb34MatchedMuonPt = new TH1D("bmtfMb34MatchedMuonPt", "bmtfMb34MatchedMuonPt", nBinsPt, minPt, maxPt);
	histBmtfMb34MatchedMuonEta = new TH1D("bmtfMb34MatchedMuonEta", "bmtfMb34MatchedMuonEta", nBinsEta, minEta, maxEta);
	histBmtfMb34MatchedMuonPhi = new TH1D("bmtfMb34MatchedMuonPhi", "bmtfMb34MatchedMuonPhi", nBinsPhi, minPhi, maxPhi);
	histBmtfMb34MatchedMuonDeltaPhi = new TH1D("bmtfMb34MatchedMuonDeltaPhi", "bmtfMb34MatchedMuonDeltaPhi", 2*nBinsPhi, -maxPhi, maxPhi);

	histBmtfMatchedMuonCharge = new TH1I("bmtfMatchedMuonCharge", "bmtfMatchedMuonCharge", 3, -1, 2);
	histIsBmtfMatchedMuon = new TH1S("isBmtfMatchedMuon", "isBmtfMatchedMuon", 2, 0, 2);
	histBmtfMatchedMuonDeltaR = new TH1D("bmtfMatchedMuonDeltaR", "bmtfMatchedMuonDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histBmtfMatchedMuonPt = new TH1D("bmtfMatchedMuonPt", "bmtfMatchedMuonPt", nBinsPt, minPt, maxPt);
	histBmtfMatchedMuonEta = new TH1D("bmtfMatchedMuonEta", "bmtfMatchedMuonEta", nBinsEta, minEta, maxEta);
	histBmtfMatchedMuonPhi = new TH1D("bmtfMatchedMuonPhi", "bmtfMatchedMuonPhi", nBinsPhi, minPhi, maxPhi);
	histBmtfMatchedMuonTrackType = new TH1D("bmtfMatchedMuonTrackType", "bmtfMatchedMuonTrackType", nBinsTrackType, minTrackType, maxTrackType);
	histBmtfMatchedMuonDeltaPhi = new TH1D("bmtfMatchedMuonDeltaPhi", "bmtfMatchedMuonDeltaPhi", 2*nBinsPhi, -maxPhi, maxPhi);
	histIsBmtfMatchedDttp = new TH1S("isBmtfMatchedDttp", "isBmtfMatchedDttp", 2, 0, 2);
	histBmtfMatchedDttpPhi = new TH1I("bmtfMatchedDttpPhi", "bmtfMatchedDttpPhi", 64, -2048, 2048);
	histBmtfMatchedDttpPt = new TH1D("bmtfMatchedDttpPt", "bmtfMatchedDttpPt", nBinsPt, minPt, maxPt);
	histBmtfMatchedDttpDeltaPhi = new TH1D("bmtfMatchedDttpDeltaPhi", "bmtfMatchedDttpDeltaPhi", 2*nBinsPhi, -maxPhi, maxPhi);
	histBmtfMatchedDttpCmsPhi = new TH1D("bmtfMatchedDttpCmsPhi", "bmtfMatchedDttpCmsPhi", nBinsPhi, minPhi, maxPhi);

	histBmtfMatchedDttpDeltaPhiSt1 = new TH1D("bmtfMatchedDttpDeltaPhiSt1", "bmtfMatchedDttpDeltaPhiSt1", 2*nBinsPhi, -maxPhi, maxPhi);
	histBmtfMatchedDttpDeltaPhiSt2 = new TH1D("bmtfMatchedDttpDeltaPhiSt2", "bmtfMatchedDttpDeltaPhiSt2", 2*nBinsPhi, -maxPhi, maxPhi);
	histBmtfMatchedDttpDeltaPhiSt3 = new TH1D("bmtfMatchedDttpDeltaPhiSt3", "bmtfMatchedDttpDeltaPhiSt3", 2*nBinsPhi, -maxPhi, maxPhi);
	histBmtfMatchedDttpDeltaPhiSt4 = new TH1D("bmtfMatchedDttpDeltaPhiSt4", "bmtfMatchedDttpDeltaPhiSt4", 2*nBinsPhi, -maxPhi, maxPhi);

	histIsDttpMatchedHo = new TH1S("isDttpMatchedHo", "isDttpMatchedHo", 2, 0, 2);
	histDttpMatchedHoDeltaIPhi = new TH1I("dttpMatchedHoDeltaIPhi", "dttpMatchedHoDeltaIPhi", 2*nBinsIPhi, -maxIPhi, maxIPhi);
	histDttpMatchedHoIPhi = new TH1I("dttpMatchedHoIPhi", "dttpMatchedHoIPhi", nBinsIPhi, minIPhi, maxIPhi);
	histDttpMatchedHoIEta = new TH1I("dttpMatchedHoIEta", "dttpMatchedHoIEta", nBinsIEta, minIEta, maxIEta);
	histDttpMatchedHoCmsPhi = new TH1D("dttpMatchedHoCmsPhi", "dttpMatchedHoCmsPhi", nBinsPhi, minPhi, maxPhi);
	histDttpMatchedHoCmsEta = new TH1D("dttpMatchedHoCmsEta", "dttpMatchedHoCmsEta", nBinsEta, minEta, maxEta);

	histIsDttpMatchedMuon = new TH1S("isDttpMatchedMuon", "isDttpMatchedMuon", 2, 0, 2);
	histDttpMatchedMuonDeltaR = new TH1D("dttpMatchedMuonDeltaR", "dttpMatchedMuonDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histNHo3x3Hit = new TH1I("nMuonMatchedDttpNHo3x3Hit", "nMuonMatchedDttpNHo3x3Hit", 10, 0, 10);

	histNUnusedMuon = new TH1S("nUnusedMuon", "nUnusedMuon", 2, 0, 2);
	histIsMediumUnusedMuon = new TH1S("isMediumUnusedMuon", "isMediumUnusedMuon", 2, 0, 2);
	histUnusedMuonHltIsoMu = new TH1S("unusedMuonHltIsoMu", "unusedMuonHltIsoMu", 2, 0, 2);
	histUnusedMuonHltMu = new TH1S("unusedMuonHltMu", "unusedMuonHltMu", 2, 0, 2);
	histUnusedMuonPassesSingleMuon = new TH1S("unusedMuonPassesSingleMuon", "unusedMuonPassesSingleMuon", 2, 0, 2);
	histUnusedMuonHasMb1 = new TH1S("unusedMuonHasMb1", "unusedMuonHasMb1", 2, 0, 2);

	histUnusedMuonCharge = new TH1I("unusedMuonCharge", "unusedMuonCharge", 3, -1, 2);
	histUnusedMuonIEta = new TH1I("unusedMuonIEta", "unusedMuonIEta", nBinsIEta, minIEta, maxIEta);

	histUnusedMuonE = new TH1D("unusedMuonE", "unusedMuonE", nBinsE, minE, maxE);
	histUnusedMuonEt = new TH1D("unusedMuonEt", "unusedMuonEt", nBinsE, minE, maxE);
	histUnusedMuonPt = new TH1D("unusedMuonPt", "unusedMuonPt", nBinsPt, minPt, maxPt);
	histUnusedMuonEta = new TH1D("unusedMuonEta", "unusedMuonEta", nBinsEta, minEta, maxEta);
	histUnusedMuonPhi = new TH1D("unusedMuonPhi", "unusedMuonPhi", nBinsPhi, minPhi, maxPhi);
	histUnusedMuonIso = new TH1D("unusedMuonIso", "unusedMuonIso", 2, 0, 2);
	histUnusedMuonHltIsoDeltaR = new TH1D("unusedMuonHltIsoDeltaR", "unusedMuonHltIsoDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histUnusedMuonDeltaR = new TH1D("unusedMuonDeltaR", "unusedMuonDeltaR", nBinsDeltaR, minDeltaR, maxDeltaR);
	histUnusedMuonEtaSt1 = new TH1D("unusedMuonEtaSt1", "unusedMuonEtaSt1", nBinsEta, minEta, maxEta);
	histUnusedMuonPhiSt1 = new TH1D("unusedMuonPhiSt1", "unusedMuonPhiSt1", nBinsPhi, minPhi, maxPhi);
	histUnusedMuonEtaSt2 = new TH1D("unusedMuonEtaSt2", "unusedMuonEtaSt2", nBinsEta, minEta, maxEta);
	histUnusedMuonPhiSt2 = new TH1D("unusedMuonPhiSt2", "unusedMuonPhiSt2", nBinsPhi, minPhi, maxPhi);


	histUnusedMuonMet = new TH1D("unusedMuonMet", "unusedMuonMet", nBinsPt, minPt, maxPt);
	histUnusedMuonMt = new TH1D("unusedMuonMt", "unusedMuonMt", nBinsE, minE, maxE);


}

void HoHistogramProducer::Produce(DataReader* dataReader, HoProduct* product) {
	for (unsigned int i = 0; i < product->bmtfSize; i++) {
		histIsBmtfMatchedDttp->Fill(product->isBmtfMatchedDttp.at(i));
		histBmtfMatchedDttpDeltaPhi->Fill(product->bmtfMatchedDttpDeltaPhi.at(i));
		histBmtfMatchedDttpPt->Fill(product->bmtfMatchedDttpPt.at(i));
		histBmtfMatchedDttpPhi->Fill(product->bmtfMatchedDttpPhi.at(i));
		histBmtfMatchedDttpCmsPhi->Fill(product->bmtfMatchedDttpCmsPhi.at(i));

		histBmtfMatchedDttpDeltaPhiSt1->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(i).at(0));
		histBmtfMatchedDttpDeltaPhiSt2->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(i).at(1));
		histBmtfMatchedDttpDeltaPhiSt3->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(i).at(2));
		histBmtfMatchedDttpDeltaPhiSt4->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(i).at(3));
	}
	histNUnusedMuon->Fill(product->nUnusedMuon);
	for (int i = 0; i < product->nUnusedMuon; i++) {
		histIsMediumUnusedMuon->Fill(product->isMediumUnusedMuon.at(i));
		histUnusedMuonHltIsoMu->Fill(product->unusedMuonHltIsoMu.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonHltMu->Fill(product->unusedMuonHltMu.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonPassesSingleMuon->Fill(product->unusedMuonPassesSingleMuon.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonHasMb1->Fill(product->unusedMuonHasMb1.at(i), product->isMediumUnusedMuon.at(i));

		histUnusedMuonCharge->Fill(product->unusedMuonCharge.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonIEta->Fill(product->unusedMuonIEta.at(i), product->isMediumUnusedMuon.at(i));

		histUnusedMuonE->Fill(product->unusedMuonE.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonEt->Fill(product->unusedMuonEt.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonPt->Fill(product->unusedMuonPt.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonEta->Fill(product->unusedMuonEta.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonPhi->Fill(product->unusedMuonPhi.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonIso->Fill(product->unusedMuonIso.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonHltIsoDeltaR->Fill(product->unusedMuonHltIsoDeltaR.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonDeltaR->Fill(product->unusedMuonDeltaR.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonEtaSt1->Fill(product->unusedMuonEtaSt1.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonPhiSt1->Fill(product->unusedMuonPhiSt1.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonEtaSt2->Fill(product->unusedMuonEtaSt2.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonPhiSt2->Fill(product->unusedMuonPhiSt2.at(i), product->isMediumUnusedMuon.at(i));


		histUnusedMuonMet->Fill(product->unusedMuonMet.at(i), product->isMediumUnusedMuon.at(i));
		histUnusedMuonMt->Fill(product->unusedMuonMt.at(i), product->isMediumUnusedMuon.at(i));
	}

	for (unsigned short i = 0; i < product->bmtfMatchedMuonCharge.size(); i++) {
		if (!product->isBmtfMatchedMuon.at(i)) { continue;}
		histIsBmtfMatchedMuon->Fill(product->isBmtfMatchedMuon.at(i));
		histBmtfMatchedMuonCharge->Fill(product->bmtfMatchedMuonCharge.at(i), product->isBmtfMatchedMuon.at(i));
		histBmtfMatchedMuonDeltaR->Fill(product->bmtfMatchedMuonDeltaR.at(i), product->isBmtfMatchedMuon.at(i));
		histBmtfMatchedMuonPt->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
		histBmtfMatchedMuonEta->Fill(product->bmtfMatchedMuonEta.at(i), product->isBmtfMatchedMuon.at(i));
		histBmtfMatchedMuonPhi->Fill(product->bmtfMatchedMuonPhi.at(i), product->isBmtfMatchedMuon.at(i));
		//histBmtfMatchedMuonTrackType->Fill(product->bmtfMatchedMuonTrackType.at(i), product->isBmtfMatchedMuon.at(i));
		histBmtfMatchedMuonDeltaPhi->Fill(product->bmtfMatchedMuonDeltaPhi.at(i), product->isBmtfMatchedMuon.at(i));
	}

	for (unsigned int i = 0; i < product->bmtfSize; i++) {
		histIsMb3HoIEtaMatched->Fill(product->isMb3HoIEtaMatched.at(i));
		histIsMb4HoIEtaMatched->Fill(product->isMb4HoIEtaMatched.at(i));
		const bool &isMb34Matched = product->isMb3HoIEtaMatched.at(i) || product->isMb4HoIEtaMatched.at(i);
		histBmtfMb34MatchedHoDeltaR->Fill(product->bmtfMb34MatchedHoDeltaR.at(i), isMb34Matched);
		histBmtfMb34MatchedHoPt->Fill(product->bmtfMb34MatchedHoPt.at(i), isMb34Matched);
		histBmtfMb34MatchedHoCmsEta->Fill(product->bmtfMb34MatchedHoCmsEta.at(i), isMb34Matched);
		histBmtfMb34MatchedHoCmsPhi->Fill(product->bmtfMb34MatchedHoCmsPhi.at(i), isMb34Matched);
		histBmtfMb34MatchedHoDeltaPhi->Fill(product->bmtfMb34MatchedHoDeltaPhi.at(i), isMb34Matched);
		histBmtfMb34MatchedMuonPt->Fill(product->bmtfMb34MatchedMuonPt.at(i), isMb34Matched);
		histBmtfMb34MatchedMuonEta->Fill(product->bmtfMb34MatchedMuonEta.at(i), isMb34Matched);
		histBmtfMb34MatchedMuonPhi->Fill(product->bmtfMb34MatchedMuonPhi.at(i), isMb34Matched);
		histBmtfMb34MatchedMuonDeltaPhi->Fill(product->bmtfMb34MatchedMuonDeltaPhi.at(i), isMb34Matched);
		histBmtfMb34MatchedHoIEta->Fill(product->bmtfMb34MatchedHoIEta.at(i), isMb34Matched);
		histBmtfMb34MatchedHoIPhi->Fill(product->bmtfMb34MatchedHoIPhi.at(i), isMb34Matched);
		histBmtfMb34MatchedHoDeltaIPhi->Fill(product->bmtfMb34MatchedHoDeltaIPhi.at(i), isMb34Matched);
		//unsigned int iMuon = product->dttpMatchedMuonIndex.at(i);
	}

	for (int i = 0; i < product->dttpSize; i++) {
		histIsDttpMatchedHo->Fill(product->isDttpMatchedHo.at(i));

		histDttpMatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(i), product->isDttpMatchedHo.at(i));
		histDttpMatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(i), product->isDttpMatchedHo.at(i));
		histDttpMatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(i), product->isDttpMatchedHo.at(i));
		histDttpMatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(i), product->isDttpMatchedHo.at(i));
		histDttpMatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(i), product->isDttpMatchedHo.at(i));

		histIsDttpMatchedMuon->Fill(product->isDttpMatchedMuon.at(i));
		histDttpMatchedMuonDeltaR->Fill(product->dttpMatchedMuonDeltaR.at(i));
		unsigned short iMuon = product->dttpMatchedMuonIndex.at(i);
		if (iMuon < 999) {
			histNHo3x3Hit->Fill(product->muonMatchedDttpNHo3x3Hit.at(iMuon));
		}
	}
}

HoHistogramProducer::~HoHistogramProducer() {}
