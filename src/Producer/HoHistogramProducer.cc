#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>

HoHistogramProducer::HoHistogramProducer() {
	Name = "Histogram Producer";
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

	if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
		histCollection->histNUnusedMuon->Fill(product->nUnusedMuon);
		for (int i = 0; i < product->nUnusedMuon; i++) {
			histCollection->histIsMediumUnusedMuon->Fill(product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonHltIsoMu->Fill(product->unusedMuonHltIsoMu.at(i), product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonHltMu->Fill(product->unusedMuonHltMu.at(i), product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonPassesSingleMuon->Fill(product->unusedMuonPassesSingleMuon.at(i), product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonHasMb1->Fill(product->unusedMuonHasMb1.at(i), product->isMediumUnusedMuon.at(i));

			histCollection->histUnusedMuonCharge->Fill(product->unusedMuonCharge.at(i), product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonIEta->Fill(product->unusedMuonIEta.at(i), product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonNHo3x3Hit->Fill(product->unusedMuonNHo3x3Hit.at(i), product->isMediumUnusedMuon.at(i));

			histCollection->histUnusedMuonE->Fill(product->unusedMuonE.at(i), product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonEt->Fill(product->unusedMuonEt.at(i), product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonPt->Fill(product->unusedMuonPt.at(i), product->isMediumUnusedMuon.at(i));
			histCollection->histUnusedMuonPt20->Fill(product->unusedMuonPt.at(i), product->isMediumUnusedMuon.at(i));
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
			histCollection->histUsedMuonNHo3x3Hit->Fill(product->usedMuonNHo3x3Hit.at(i), product->isMediumUsedMuon.at(i));

			histCollection->histUsedMuonE->Fill(product->usedMuonE.at(i), product->isMediumUsedMuon.at(i));
			histCollection->histUsedMuonEt->Fill(product->usedMuonEt.at(i), product->isMediumUsedMuon.at(i));
			histCollection->histUsedMuonPt->Fill(product->usedMuonPt.at(i), product->isMediumUsedMuon.at(i));
			histCollection->histUsedMuonPt20->Fill(product->usedMuonPt.at(i), product->isMediumUsedMuon.at(i));
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
			histCollection->histIsBmtfMatchedMuon->Fill(product->isBmtfMatchedMuon.at(i));
			histCollection->histBmtfMatchedMuonCharge->Fill(product->bmtfMatchedMuonCharge.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histBmtfMatchedMuonDeltaR->Fill(product->bmtfMatchedMuonDeltaR.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histBmtfMatchedMuonPt->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histBmtfMatchedMuonPt20->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histBmtfMatchedMuonEta->Fill(product->bmtfMatchedMuonEta.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histBmtfMatchedMuonPhi->Fill(product->bmtfMatchedMuonPhi.at(i), product->isBmtfMatchedMuon.at(i));
			//histCollection->histBmtfMatchedMuonTrackType->Fill(product->bmtfMatchedMuonTrackType.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histBmtfMatchedMuonDeltaPhi->Fill(product->bmtfMatchedMuonDeltaPhi.at(i), product->isBmtfMatchedMuon.at(i));

			histCollection->histIsoMb1MatchedMuonPt->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histIsoMb1MatchedMuonPt20->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histIsoMb1MatchedMuonEta->Fill(product->bmtfMatchedMuonEta.at(i), product->isBmtfMatchedMuon.at(i));

			histCollection->histIsoMb2MatchedMuonPt->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histIsoMb2MatchedMuonPt20->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histIsoMb2MatchedMuonEta->Fill(product->bmtfMatchedMuonEta.at(i), product->isBmtfMatchedMuon.at(i));

			histCollection->histIsoMb12MatchedMuonPt->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histIsoMb12MatchedMuonPt20->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histIsoMb12MatchedMuonEta->Fill(product->bmtfMatchedMuonEta.at(i), product->isBmtfMatchedMuon.at(i));

			histCollection->histIsoMb1MatchedMuonEta_vs_MuonPt->Fill(product->bmtfMatchedMuonEta.at(i), product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histIsoMb2MatchedMuonEta_vs_MuonPt->Fill(product->bmtfMatchedMuonEta.at(i), product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
			histCollection->histIsoMb12MatchedMuonEta_vs_MuonPt->Fill(product->bmtfMatchedMuonEta.at(i), product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));

		}

		for (int i = 0; i < product->nMuon; i++) {
			histCollection->histMuonNHo3x3Hit->Fill(product->muonNHo3x3Hit.at(i));
			// Only use the IsoMb1/2 if the BMTF does not reconstruct a muon
			if (!product->isMuonMatchedBmtf.at(i) && product->isMuonMatchedDttp.at(i)) {
				histCollection->histIsoMb1MatchedMuonPt->Fill(product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 1));
				histCollection->histIsoMb1MatchedMuonPt20->Fill(product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 1));
				histCollection->histIsoMb1MatchedMuonEta->Fill(product->muonEta.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 1));
				histCollection->histIsoMb1MatchedMuonEta_vs_MuonPt->Fill(product->muonEta.at(i), product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 1));

				histCollection->histIsoMb2MatchedMuonPt->Fill(product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 2));
				histCollection->histIsoMb2MatchedMuonPt20->Fill(product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 2));
				histCollection->histIsoMb2MatchedMuonEta->Fill(product->muonEta.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 2));
				histCollection->histIsoMb2MatchedMuonEta_vs_MuonPt->Fill(product->muonEta.at(i), product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 2));

				histCollection->histIsoMb12MatchedMuonPt->Fill(product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) <= 2));
				histCollection->histIsoMb12MatchedMuonPt20->Fill(product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) <= 2));
				histCollection->histIsoMb12MatchedMuonEta->Fill(product->muonEta.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) <= 2));
				histCollection->histIsoMb12MatchedMuonEta_vs_MuonPt->Fill(product->muonEta.at(i), product->muonPt.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) <= 2));
			}

			histCollection->histMuonMatchedBmtfCmsPt->Fill(product->muonMatchedBmtfCmsPt.at(i), product->isMuonMatchedBmtf.at(i));
			histCollection->histMuonMatchedBmtfCmsEta->Fill(product->muonMatchedBmtfCmsEta.at(i), product->isMuonMatchedBmtf.at(i));

			histCollection->histMuonPt_vs_MuonEta->Fill(product->muonPt.at(i), product->muonEta.at(i));
			histCollection->histMuonEta_vs_MuonPt->Fill(product->muonEta.at(i), product->muonPt.at(i));

			histCollection->histBmtfMatchedMuonPt_vs_MuonEta->Fill(product->muonPt.at(i), product->muonEta.at(i), product->isMuonMatchedBmtf.at(i));
			histCollection->histBmtfMatchedMuonEta_vs_MuonPt->Fill(product->muonEta.at(i), product->muonPt.at(i), product->isMuonMatchedBmtf.at(i));
		}
	}

	for (unsigned int i = 0; i < product->bmtfSize; i++) {
		histCollection->histIsMb3HoIEtaMatched->Fill(product->isMb3HoIEtaMatched.at(i));
		histCollection->histIsMb4HoIEtaMatched->Fill(product->isMb4HoIEtaMatched.at(i));
		const bool &isMb34Matched = product->isMb3HoIEtaMatched.at(i) || product->isMb4HoIEtaMatched.at(i);
		if (isMb34Matched) {
			histCollection->histBmtfMb34MatchedHoDeltaR->Fill(product->bmtfMb34MatchedHoDeltaR.at(i), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoPt->Fill(product->bmtfMb34MatchedHoPt.at(i), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoCmsEta->Fill(product->bmtfMb34MatchedHoCmsEta.at(i), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoCmsPhi->Fill(product->bmtfMb34MatchedHoCmsPhi.at(i), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoDeltaPhi->Fill(product->bmtfMb34MatchedHoDeltaPhi.at(i), isMb34Matched);
			if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
				histCollection->histBmtfMb34MatchedMuonPt->Fill(product->bmtfMb34MatchedMuonPt.at(i), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonPt20->Fill(product->bmtfMb34MatchedMuonPt.at(i), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonEta->Fill(product->bmtfMb34MatchedMuonEta.at(i), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonPhi->Fill(product->bmtfMb34MatchedMuonPhi.at(i), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonDeltaPhi->Fill(product->bmtfMb34MatchedMuonDeltaPhi.at(i), isMb34Matched);
			}
			histCollection->histBmtfMb34MatchedHoIEta->Fill(product->bmtfMb34MatchedHoIEta.at(i), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoIPhi->Fill(product->bmtfMb34MatchedHoIPhi.at(i), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoDeltaIPhi->Fill(product->bmtfMb34MatchedHoDeltaIPhi.at(i), isMb34Matched);
		} else {
			if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
				histCollection->histBmtfMb34MatchedMuonPt->Fill(product->bmtfMatchedMuonPt.at(i));
				histCollection->histBmtfMb34MatchedMuonPt20->Fill(product->bmtfMatchedMuonPt.at(i), product->isBmtfMatchedMuon.at(i));
				histCollection->histBmtfMb34MatchedMuonEta->Fill(product->bmtfMatchedMuonEta.at(i));
				histCollection->histBmtfMb34MatchedMuonPhi->Fill(product->bmtfMatchedMuonPhi.at(i));
				histCollection->histBmtfMb34MatchedMuonDeltaPhi->Fill(product->bmtfMatchedMuonDeltaPhi.at(i));
			}
		}
		//unsigned int iMuon = product->dttpMatchedMuonIndex.at(i);
	}


	for (int i = 0; i < product->dttpSize; i++) {
		//const bool &n3x3Cut = product->muonMatchedDttpNHo3x3Hit.at(i) <= 1;
		const bool &n3x3Cut = product->dttpMatchedMuonNHo3x3Hit.at(i) <= 1;

		histCollection->histIsDttpMatchedHo->Fill(product->isDttpMatchedHo.at(i), n3x3Cut);

		histCollection->histDttpMatchedHoDeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(i), product->isDttpMatchedHo.at(i) * n3x3Cut);
		histCollection->histDttpMatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(i), product->isDttpMatchedHo.at(i) * n3x3Cut);
		histCollection->histDttpMatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(i), product->isDttpMatchedHo.at(i) * n3x3Cut);
		histCollection->histDttpMatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(i), product->isDttpMatchedHo.at(i) * n3x3Cut);
		histCollection->histDttpMatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(i), product->isDttpMatchedHo.at(i) * n3x3Cut);
		histCollection->histDttpMatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(i), product->isDttpMatchedHo.at(i) * n3x3Cut);

		if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
			histCollection->histIsDttpMatchedMuon->Fill(product->isDttpMatchedMuon.at(i) * n3x3Cut);
			histCollection->histDttpMatchedMuonDeltaR->Fill(product->dttpMatchedMuonDeltaR.at(i) * n3x3Cut);
			unsigned short iMuon = product->dttpMatchedMuonIndex.at(i);
			if (iMuon < 999) {
				histCollection->histNHo3x3Hit->Fill(product->muonMatchedDttpNHo3x3Hit.at(iMuon));
			}
		}
	}

}

void HoHistogramProducer::EndJob(HoHistogramCollection* histCollection) {
	if (histCollection->GetHasRecoMuon()) {
		TGraphAsymmErrors *efficiencyBmtfPt = new TGraphAsymmErrors(histCollection->histBmtfMatchedMuonPt);
		TGraphAsymmErrors *efficiencyBmtfEta = new TGraphAsymmErrors(histCollection->histBmtfMatchedMuonEta);
		efficiencyBmtfPt->Divide(histCollection->histBmtfMatchedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");
		efficiencyBmtfEta->Divide(histCollection->histBmtfMatchedMuonEta, histCollection->histMuonEta, "cl=0.683 b(1,1) mode");
		efficiencyBmtfPt->Write("efficiencyBmtfPt");
		efficiencyBmtfEta->Write("efficiencyBmtfEta");
		delete efficiencyBmtfPt; delete efficiencyBmtfEta;

		TGraphAsymmErrors *efficiencyIsoMb1Pt = new TGraphAsymmErrors(histCollection->histBmtfMatchedMuonPt);
		TGraphAsymmErrors *efficiencyIsoMb1Eta = new TGraphAsymmErrors(histCollection->histBmtfMatchedMuonEta);
		efficiencyIsoMb1Pt->Divide(histCollection->histIsoMb1MatchedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");
		efficiencyIsoMb1Eta->Divide(histCollection->histIsoMb1MatchedMuonEta, histCollection->histMuonEta, "cl=0.683 b(1,1) mode");
		efficiencyIsoMb1Pt->Write("efficiencyIsoMb1Pt");
		efficiencyIsoMb1Eta->Write("efficiencyIsoMb1Eta");
		delete efficiencyIsoMb1Pt; delete efficiencyIsoMb1Eta;

		TGraphAsymmErrors *efficiencyIsoMb2Pt = new TGraphAsymmErrors(histCollection->histBmtfMatchedMuonPt);
		TGraphAsymmErrors *efficiencyIsoMb2Eta = new TGraphAsymmErrors(histCollection->histBmtfMatchedMuonEta);
		efficiencyIsoMb2Pt->Divide(histCollection->histIsoMb2MatchedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");
		efficiencyIsoMb2Eta->Divide(histCollection->histIsoMb2MatchedMuonEta, histCollection->histMuonEta, "cl=0.683 b(1,1) mode");
		efficiencyIsoMb2Pt->Write("efficiencyIsoMb2Pt");
		efficiencyIsoMb2Eta->Write("efficiencyIsoMb2Eta");
		delete efficiencyIsoMb2Pt; delete efficiencyIsoMb2Eta;

		TGraphAsymmErrors *efficiencyIsoMb12Pt = new TGraphAsymmErrors(histCollection->histBmtfMatchedMuonPt);
		TGraphAsymmErrors *efficiencyIsoMb12Eta = new TGraphAsymmErrors(histCollection->histBmtfMatchedMuonEta);
		efficiencyIsoMb12Pt->Divide(histCollection->histIsoMb12MatchedMuonPt, histCollection->histMuonPt, "cl=0.683 b(1,1) mode");
		efficiencyIsoMb12Eta->Divide(histCollection->histIsoMb12MatchedMuonEta, histCollection->histMuonEta, "cl=0.683 b(1,1) mode");
		efficiencyIsoMb12Pt->Write("efficiencyIsoMb12Pt");
		efficiencyIsoMb12Eta->Write("efficiencyIsoMb12Eta");
		delete efficiencyIsoMb12Pt; delete efficiencyIsoMb12Eta;

		//histCollection->histIsoMb1MatchedMuonPt_vs_MuonEta->Fill(product->muonPt.at(i), product->muonEta.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 1));
		TH2D *efficiencyBmtfMuonEta_vs_MuonPt = (TH2D*)histCollection->histBmtfMatchedMuonEta_vs_MuonPt->Clone("efficiencyBmtfMatchedMuonEta_vs_Pt");
		efficiencyBmtfMuonEta_vs_MuonPt->Divide(histCollection->histMuonEta_vs_MuonPt);
		efficiencyBmtfMuonEta_vs_MuonPt->Write("efficiencyBmtfMuonEta_vs_MuonPt");

		TH2D *efficiencyIsoMb1MuonEta_vs_MuonPt = (TH2D*)histCollection->histIsoMb1MatchedMuonEta_vs_MuonPt->Clone("efficiencyIsoMb1MatchedMuonEta_vs_Pt");
		efficiencyIsoMb1MuonEta_vs_MuonPt->Divide(histCollection->histMuonEta_vs_MuonPt);
		efficiencyIsoMb1MuonEta_vs_MuonPt->Write("efficiencyIsoMb1MuonEta_vs_MuonPt");

		TH2D *efficiencyIsoMb2MuonEta_vs_MuonPt = (TH2D*)histCollection->histIsoMb2MatchedMuonEta_vs_MuonPt->Clone("efficiencyIsoMb2MatchedMuonEta_vs_Pt");
		efficiencyIsoMb2MuonEta_vs_MuonPt->Divide(histCollection->histMuonEta_vs_MuonPt);
		efficiencyIsoMb2MuonEta_vs_MuonPt->Write("efficiencyIsoMb2MuonEta_vs_MuonPt");

		TH2D *efficiencyIsoMb12MuonEta_vs_MuonPt = (TH2D*)histCollection->histIsoMb12MatchedMuonEta_vs_MuonPt->Clone("efficiencyIsoMb12MatchedMuonEta_vs_Pt");
		efficiencyIsoMb12MuonEta_vs_MuonPt->Divide(histCollection->histMuonEta_vs_MuonPt);
		efficiencyIsoMb12MuonEta_vs_MuonPt->Write("efficiencyIsoMb12MuonEta_vs_MuonPt");

		TH2D *efficiencyRatioIsoMB1MuonEta_vs_MuonPt = (TH2D*)efficiencyIsoMb1MuonEta_vs_MuonPt->Clone("efficiencyRatioIsoMB1MuonEta_vs_MuonPt");
		efficiencyRatioIsoMB1MuonEta_vs_MuonPt->Divide(efficiencyBmtfMuonEta_vs_MuonPt);
		efficiencyRatioIsoMB1MuonEta_vs_MuonPt->Write("efficiencyRatioIsoMB1MuonEta_vs_MuonPt");

		TH2D *efficiencyRatioIsoMB2MuonEta_vs_MuonPt = (TH2D*)efficiencyIsoMb2MuonEta_vs_MuonPt->Clone("efficiencyRatioIsoMB2MuonEta_vs_MuonPt");
		efficiencyRatioIsoMB2MuonEta_vs_MuonPt->Divide(efficiencyBmtfMuonEta_vs_MuonPt);
		efficiencyRatioIsoMB2MuonEta_vs_MuonPt->Write("efficiencyRatioIsoMB2MuonEta_vs_MuonPt");

		TH2D *efficiencyRatioIsoMB12MuonEta_vs_MuonPt = (TH2D*)efficiencyIsoMb12MuonEta_vs_MuonPt->Clone("efficiencyRatioIsoMB12MuonEta_vs_MuonPt");
		efficiencyRatioIsoMB12MuonEta_vs_MuonPt->Divide(efficiencyBmtfMuonEta_vs_MuonPt);
		efficiencyRatioIsoMB12MuonEta_vs_MuonPt->Write("efficiencyRatioIsoMB12MuonEta_vs_MuonPt");

		//histCollection->efficiencyBmtf34MatchedHoPt->Write("efficiencyBmtf34MatchedHoPt");
	} else {
		std::cout << "This is a ZeroBias sample. Rates calculation not implemented yet!" << std::endl;
	}
}
HoHistogramProducer::~HoHistogramProducer() {}
