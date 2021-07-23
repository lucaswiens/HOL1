#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>

HoHistogramProducer::HoHistogramProducer(HoHistogramCollection* histCollection) {
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
		histCollection->histIsDttpMatchedHo->Fill(product->isDttpMatchedHo.at(i));

		histCollection->histDttpMatchedHoDeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(i), product->isDttpMatchedHo.at(i));
		histCollection->histDttpMatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(i), product->isDttpMatchedHo.at(i));

		if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
			histCollection->histIsDttpMatchedMuon->Fill(product->isDttpMatchedMuon.at(i));
			histCollection->histDttpMatchedMuonDeltaR->Fill(product->dttpMatchedMuonDeltaR.at(i));
			unsigned short iMuon = product->dttpMatchedMuonIndex.at(i);
			if (iMuon < 999) {
				histCollection->histNHo3x3Hit->Fill(product->muonMatchedDttpNHo3x3Hit.at(iMuon));
			}
		}
	}

}

void HoHistogramProducer::EndJob(HoHistogramCollection* histCollection) {
	if (histCollection->GetHasRecoMuon()) {
		histCollection->efficiencyBmtf34MatchedHoPt = new TGraphAsymmErrors(histCollection->histBmtfMb34MatchedMuonPt20);
		histCollection->efficiencyBmtfPt = new TGraphAsymmErrors(histCollection->histMuonPt20);

		//TH1D *histTmp = (TH1D*) histCollection->histMuonPt20->Clone();
		//histTmp->Add(histCollection->histMuonPt20, histCollection->histUnusedMuonPt20);

		//histCollection->efficiencyBmtfPt->Divide(histCollection->histBmtfMatchedMuonPt20, histCollection->histUsedMuonPt20, "cl=0.683 b(1,1) mode");
		histCollection->efficiencyBmtfPt->Divide(histCollection->histMuonMatchedBmtfCmsPt, histCollection->histBmtfCmsPt, "cl=0.683 b(1,1) mode");
		//histCollection->efficiencyBmtf34MatchedHoPt->Divide(histCollection->histBmtfMb34MatchedMuonPt20, histCollection->histUsedMuonPt20, "cl=0.683 b(1,1) mode");
		histCollection->efficiencyBmtf34MatchedHoPt->Divide(histCollection->histBmtfMb34MatchedMuonPt20, histCollection->histBmtfCmsPt20, "cl=0.683 b(1,1) mode");

		histCollection->efficiencyBmtfPt->Write("efficiencyBmtfPt");
		histCollection->efficiencyBmtf34MatchedHoPt->Write("efficiencyBmtf34MatchedHoPt");
	} else {
		std::cout << "This is a ZeroBias sample. Rates calculation not implemented yet!" << std::endl;
	}
}
HoHistogramProducer::~HoHistogramProducer() {}
