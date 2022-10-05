#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>

HoHistogramProducer::HoHistogramProducer() {
	Name = "Histogram Producer";
}
//int histCounter = 0;

void HoHistogramProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	for (unsigned int iBmtf = 0; iBmtf < product->tfMuonSize.at(Utility::Bmtf); iBmtf++) {
		histCollection->histIsBmtfMatchedDttp->Fill(product->isBmtfMatchedDttp.at(iBmtf));
		if (!product->isBmtfMatchedDttp.at(iBmtf)) { continue;}
		histCollection->histBmtfMatchedDttpDeltaPhi->Fill(product->bmtfMatchedDttpDeltaPhi.at(iBmtf));
		histCollection->histBmtfMatchedDttpCmsPt->Fill(product->bmtfMatchedDttpCmsPt.at(iBmtf));
		histCollection->histBmtfMatchedDttpPhi->Fill(product->bmtfMatchedDttpPhi.at(iBmtf));
		histCollection->histBmtfMatchedDttpCmsPhi->Fill(product->bmtfMatchedDttpCmsPhi.at(iBmtf));

		histCollection->histBmtfMatchedDttpDeltaPhiSt1->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(0));
		histCollection->histBmtfMatchedDttpDeltaPhiSt2->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(1));
		histCollection->histBmtfMatchedDttpDeltaPhiSt3->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(2));
		histCollection->histBmtfMatchedDttpDeltaPhiSt4->Fill(product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(3));
	}

	if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
		for (int tfType : Utility::TfAlgorithms) {
			for (unsigned short iTf = 0; iTf < product->tfMuonSize.at(tfType); iTf++) {
				if (Utility::EtaCuts.at(tfType).first <= std::abs(product->tfMatchedMuonEta.at(tfType).at(iTf)) && std::abs(product->tfMatchedMuonEta.at(tfType).at(iTf)) < Utility::EtaCuts.at(tfType).second) {
					histCollection->histTfMapMatchedMuonPt.at(tfType)->Fill(product->tfMatchedMuonPt.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonPtFineBinning.at(tfType)->Fill(product->tfMatchedMuonPt.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonEta.at(tfType)->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonPhi.at(tfType)->Fill(product->tfMatchedMuonPhi.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonTfType.at(tfType)->Fill(product->tfMatchedMuonTfType.at(tfType).at(iTf));

					histCollection->histTfMapMatchedMuonPt.at(Utility::UGMT)->Fill(product->tfMatchedMuonPt.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonPtFineBinning.at(Utility::UGMT)->Fill(product->tfMatchedMuonPt.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonEta.at(Utility::UGMT)->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonPhi.at(Utility::UGMT)->Fill(product->tfMatchedMuonPhi.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonTfType.at(Utility::UGMT)->Fill(product->tfMatchedMuonTfType.at(tfType).at(iTf));

					histCollection->histTfMatchedMuonPt_vs_MuonEta->Fill(product->tfMatchedMuonPt.at(tfType).at(iTf), product->tfMatchedMuonEta.at(tfType).at(iTf), product->isTfMatchedMuon.at(tfType).at(iTf));
					histCollection->histTfMatchedMuonEta_vs_MuonPt->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf), product->tfMatchedMuonPt.at(tfType).at(iTf), product->isTfMatchedMuon.at(tfType).at(iTf));
					histCollection->histTfMatchedMuonEta_vs_MuonPhi->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf), product->tfMatchedMuonPhi.at(tfType).at(iTf), product->isTfMatchedMuon.at(tfType).at(iTf));
				}
			}

			for (unsigned short iProbe = 0; iProbe < product->nProbeMuon; iProbe++) {
				if (Utility::EtaCuts.at(tfType).first <= std::abs(product->probeMuonEta.at(iProbe)) && std::abs(product->probeMuonEta.at(iProbe)) < Utility::EtaCuts.at(tfType).second) {
					histCollection->histProbeMuonMapPt.at(tfType)->Fill(product->probeMuonPt.at(iProbe));
					histCollection->histProbeMuonMapPtFineBinning.at(tfType)->Fill(product->probeMuonPt.at(iProbe));
					histCollection->histProbeMuonMapEta.at(tfType)->Fill(product->probeMuonEta.at(iProbe));
					histCollection->histProbeMuonMapPhi.at(tfType)->Fill(product->probeMuonPhi.at(iProbe));

					histCollection->histProbeMuonMapPt.at(Utility::UGMT)->Fill(product->probeMuonPt.at(iProbe));
					histCollection->histProbeMuonMapPtFineBinning.at(Utility::UGMT)->Fill(product->probeMuonPt.at(iProbe));
					histCollection->histProbeMuonMapEta.at(Utility::UGMT)->Fill(product->probeMuonEta.at(iProbe));
					histCollection->histProbeMuonMapPhi.at(Utility::UGMT)->Fill(product->probeMuonPhi.at(iProbe));
				}
			}
		}

		for (int iMuon = 0; iMuon < product->nProbeMuon; iMuon++) {
			histCollection->histMuonHoN3x3Hit->Fill(product->muonHoN3x3Hit.at(iMuon));

			// Only use the IsoMb1/2 if the BMTF does not reconstruct a muon
			if (!product->isMuonMatchedTf.at(iMuon) && product->isMuonMatchedDttp.at(iMuon)) {
				histCollection->histIsoMb1MatchedMuonPt->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
				histCollection->histIsoMb1MatchedMuonPtFineBinning->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
				histCollection->histIsoMb1MatchedMuonEta->Fill(product->probeMuonEta.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
				histCollection->histIsoMb1MatchedMuonPhi->Fill(product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
				histCollection->histIsoMb1MatchedMuonEta_vs_MuonPt->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
				histCollection->histIsoMb1MatchedMuonEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));

				histCollection->histIsoMb2MatchedMuonPt->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
				histCollection->histIsoMb2MatchedMuonPtFineBinning->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
				histCollection->histIsoMb2MatchedMuonEta->Fill(product->probeMuonEta.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
				histCollection->histIsoMb2MatchedMuonPhi->Fill(product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
				histCollection->histIsoMb2MatchedMuonEta_vs_MuonPt->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
				histCollection->histIsoMb2MatchedMuonEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));

				histCollection->histIsoMb12MatchedMuonPt->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
				histCollection->histIsoMb12MatchedMuonPtFineBinning->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
				histCollection->histIsoMb12MatchedMuonEta->Fill(product->probeMuonEta.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
				histCollection->histIsoMb12MatchedMuonPhi->Fill(product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
				histCollection->histIsoMb12MatchedMuonEta_vs_MuonPt->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
				histCollection->histIsoMb12MatchedMuonEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));

				const bool &n3x3Cut = product->dttpMatchedMuonHoN3x3Hit.at(product->muonMatchedDttpIndex.at(iMuon)) <= 1;
				if (n3x3Cut) {
					histCollection->histIsoMb1MatchedMuonN3x3Pt->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
					histCollection->histIsoMb1MatchedMuonN3x3PtFineBinning->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
					histCollection->histIsoMb1MatchedMuonN3x3Eta->Fill(product->probeMuonEta.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
					histCollection->histIsoMb1MatchedMuonN3x3Phi->Fill(product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
					histCollection->histIsoMb1MatchedMuonN3x3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));
					histCollection->histIsoMb1MatchedMuonN3x3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 1));

					histCollection->histIsoMb2MatchedMuonN3x3Pt->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
					histCollection->histIsoMb2MatchedMuonN3x3PtFineBinning->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
					histCollection->histIsoMb2MatchedMuonN3x3Eta->Fill(product->probeMuonEta.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
					histCollection->histIsoMb2MatchedMuonN3x3Phi->Fill(product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
					histCollection->histIsoMb2MatchedMuonN3x3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));
					histCollection->histIsoMb2MatchedMuonN3x3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) == 2));

					histCollection->histIsoMb12MatchedMuonN3x3Pt->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
					histCollection->histIsoMb12MatchedMuonN3x3PtFineBinning->Fill(product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
					histCollection->histIsoMb12MatchedMuonN3x3Eta->Fill(product->probeMuonEta.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
					histCollection->histIsoMb12MatchedMuonN3x3Phi->Fill(product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
					histCollection->histIsoMb12MatchedMuonN3x3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPt.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
					histCollection->histIsoMb12MatchedMuonN3x3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iMuon), product->probeMuonPhi.at(iMuon), (product->dttpStation.at(product->muonMatchedDttpIndex.at(iMuon)) <= 2));
				}
			}
		}
	}

	for (unsigned int iBmtf = 0; iBmtf < product->tfMuonSize.at(Utility::Bmtf); iBmtf++) {
		histCollection->histIsMb3HoIEtaMatched->Fill(product->isMb3HoIEtaMatched.at(iBmtf));
		histCollection->histIsMb4HoIEtaMatched->Fill(product->isMb4HoIEtaMatched.at(iBmtf));
		const bool &isMb34Matched = product->isMb3HoIEtaMatched.at(iBmtf) || product->isMb4HoIEtaMatched.at(iBmtf);
		if (isMb34Matched) {
			histCollection->histBmtfMb34MatchedHoNumber->Fill(0.);
			histCollection->histBmtfMb34MatchedHoDeltaR->Fill(product->bmtfMb34MatchedHoDeltaR.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoPt->Fill(product->bmtfMb34MatchedHoPt.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoCmsEta->Fill(product->bmtfMb34MatchedHoCmsEta.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoCmsPhi->Fill(product->bmtfMb34MatchedHoCmsPhi.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoDeltaPhi->Fill(product->bmtfMb34MatchedHoDeltaPhi.at(iBmtf), isMb34Matched);
			if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
				histCollection->histBmtfMb34MatchedMuonPt->Fill(product->bmtfMb34MatchedMuonPt.at(iBmtf), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonPtFineBinning->Fill(product->bmtfMb34MatchedMuonPt.at(iBmtf), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonEta->Fill(product->bmtfMb34MatchedMuonEta.at(iBmtf), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonPhi->Fill(product->bmtfMb34MatchedMuonPhi.at(iBmtf), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonDeltaPhi->Fill(product->bmtfMb34MatchedMuonDeltaPhi.at(iBmtf), isMb34Matched);
			}
			histCollection->histBmtfMb34MatchedHoIEta->Fill(product->bmtfMb34MatchedHoIEta.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoIPhi->Fill(product->bmtfMb34MatchedHoIPhi.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoDeltaIPhi->Fill(product->bmtfMb34MatchedHoDeltaIPhi.at(iBmtf), isMb34Matched);
		} else {
			if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
				histCollection->histBmtfMb34MatchedMuonPt->Fill(product->tfMatchedMuonPt.at(Utility::Bmtf).at(iBmtf));
				histCollection->histBmtfMb34MatchedMuonPtFineBinning->Fill(product->tfMatchedMuonPt.at(Utility::Bmtf).at(iBmtf));
				histCollection->histBmtfMb34MatchedMuonEta->Fill(product->tfMatchedMuonEta.at(Utility::Bmtf).at(iBmtf));
				histCollection->histBmtfMb34MatchedMuonPhi->Fill(product->tfMatchedMuonPhi.at(Utility::Bmtf).at(iBmtf));
				//histCollection->histBmtfMb34MatchedMuonDeltaPhi->Fill(product->bmtfMatchedMuonDeltaPhi.at(iBmtf));
			}
		}
		//unsigned int iMuon = product->dttpMatchedMuonIndex.at(i);
	}


	for (int iDttp = 0; iDttp < product->dttpSize; iDttp++) {
		//const bool &n3x3Cut = product->muonMatchedDttpHoN3x3Hit.at(iDttp) <= 1;
		bool n3x3Cut = false;
		histCollection->histDttpMatchedHoN3x3->Fill(product->dttpHoN3x3Hit.at(iDttp));
		if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
			n3x3Cut = product->dttpMatchedMuonHoN3x3Hit.at(iDttp) <= 1;
			//histCollection->histDttpMatchedHoN3x3->Fill(product->dttpMatchedMuonHoN3x3Hit.at(iDttp));
		} else {
			n3x3Cut = product->dttpHoN3x3Hit.at(iDttp) <= 1;
		}

		histCollection->histDttpHoN3x3Hit->Fill(product->dttpHoN3x3Hit.at(iDttp), product->dttpStation.at(iDttp) == 1);
		histCollection->histIsDttpMatchedHo->Fill(product->isDttpMatchedHo.at(iDttp));
		if (n3x3Cut) {
			histCollection->histIsDttpMatchedHoN3x3->Fill(product->isDttpMatchedHo.at(iDttp));
		}

		if (product->isDttpMatchedHo.at(iDttp)) {
			histCollection->histDttpMatchedHoNumber->Fill(0., product->dttpStation.at(iDttp) == 1);
			histCollection->histDttpMatchedHoDeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp), product->dttpStation.at(iDttp) == 1);
			histCollection->histDttpMatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp), product->dttpStation.at(iDttp) == 1);
			histCollection->histDttpMatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp), product->dttpStation.at(iDttp) == 1);
			histCollection->histDttpMatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(iDttp), product->dttpStation.at(iDttp) == 1);
			histCollection->histDttpMatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp), product->dttpStation.at(iDttp) == 1);
			histCollection->histDttpMatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp), product->dttpStation.at(iDttp) == 1);

			if (n3x3Cut) {
				histCollection->histDttpMatchedHoN3x3Number->Fill(0., product->dttpStation.at(iDttp) == 1);
				histCollection->histDttpMatchedHoN3x3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp), product->dttpStation.at(iDttp) == 1);
				histCollection->histDttpMatchedHoN3x3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp), product->dttpStation.at(iDttp) == 1);
				histCollection->histDttpMatchedHoN3x3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp), product->dttpStation.at(iDttp) == 1);
				histCollection->histDttpMatchedHoN3x3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp), product->dttpStation.at(iDttp) == 1);
				histCollection->histDttpMatchedHoN3x3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp), product->dttpStation.at(iDttp) == 1);
				histCollection->histDttpMatchedHoN3x3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp), product->dttpStation.at(iDttp) == 1);
			}
		}

		if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
			histCollection->histIsDttpMatchedMuon->Fill(product->isDttpMatchedMuon.at(iDttp) * n3x3Cut);
			histCollection->histDttpMatchedMuonDeltaR->Fill(product->dttpMatchedMuonDeltaR.at(iDttp) * n3x3Cut);
			if (product->dttpMatchedMuonIndex.at(iDttp) < 999) {
				histCollection->histMuonHoN3x3Hit->Fill(product->muonMatchedDttpHoN3x3Hit.at(product->dttpMatchedMuonIndex.at(iDttp)));
			}
		}
	}

}

void HoHistogramProducer::EndJob(HoHistogramCollection* histCollection) {
	if (histCollection->GetHasRecoMuon()) {
		for (int tfType : {Utility::Bmtf, Utility::Omtf, Utility::Emtf}) {
			TGraphAsymmErrors *efficiencyTfPt = new TGraphAsymmErrors(histCollection->histTfMapMatchedMuonPt.at(tfType));
			TGraphAsymmErrors *efficiencyTfPtFineBinning = new TGraphAsymmErrors(histCollection->histTfMapMatchedMuonPtFineBinning.at(tfType));
			TGraphAsymmErrors *efficiencyTfEta = new TGraphAsymmErrors(histCollection->histTfMapMatchedMuonEta.at(tfType));
			TGraphAsymmErrors *efficiencyTfPhi = new TGraphAsymmErrors(histCollection->histTfMapMatchedMuonPhi.at(tfType));
			efficiencyTfPt->Divide(histCollection->histTfMapMatchedMuonPt.at(tfType), histCollection->histProbeMuonMapPt.at(tfType), "cl=0.683 b(1,1) mode");
			efficiencyTfPtFineBinning->Divide(histCollection->histTfMapMatchedMuonPtFineBinning.at(tfType),   histCollection->histProbeMuonMapPtFineBinning.at(tfType), "cl=0.683 b(1,1) mode");
			efficiencyTfEta->Divide(histCollection->histTfMapMatchedMuonEta.at(tfType), histCollection->histProbeMuonMapEta.at(tfType), "cl=0.683 b(1,1) mode");
			efficiencyTfPhi->Divide(histCollection->histTfMapMatchedMuonPhi.at(tfType), histCollection->histProbeMuonMapPhi.at(tfType), "cl=0.683 b(1,1) mode");
			efficiencyTfPt->Write(("efficiency" + Utility::TfNames.at(tfType) + "Pt").c_str());
			efficiencyTfPtFineBinning->Write(("efficiency" + Utility::TfNames.at(tfType) + "FineBinningPt").c_str());
			efficiencyTfEta->Write(("efficiency" + Utility::TfNames.at(tfType) + "Eta").c_str());
			efficiencyTfPhi->Write(("efficiency" + Utility::TfNames.at(tfType) + "Phi").c_str());
			delete efficiencyTfPt; delete efficiencyTfPtFineBinning; delete efficiencyTfEta; delete efficiencyTfPhi;
		}

		// Add the BMTF matched muons on top of the isoMB matched muons to get combined efficiency
		for (TH1D *hist : {histCollection->histIsoMb1MatchedMuonPt, histCollection->histIsoMb2MatchedMuonPt, histCollection->histIsoMb12MatchedMuonPt, histCollection->histIsoMb1MatchedMuonN3x3Pt, histCollection->histIsoMb2MatchedMuonN3x3Pt, histCollection->histIsoMb12MatchedMuonN3x3Pt}) {
			hist->Add(histCollection->histTfMapMatchedMuonPt.at(Utility::Bmtf));
		}

		for (TH1D *hist : {histCollection->histIsoMb1MatchedMuonEta, histCollection->histIsoMb2MatchedMuonEta, histCollection->histIsoMb12MatchedMuonEta, histCollection->histIsoMb1MatchedMuonN3x3Eta, histCollection->histIsoMb2MatchedMuonN3x3Eta, histCollection->histIsoMb12MatchedMuonN3x3Eta}) {
			hist->Add(histCollection->histTfMapMatchedMuonEta.at(Utility::Bmtf));
		}

		for (TH1D *hist : {histCollection->histIsoMb1MatchedMuonPhi, histCollection->histIsoMb2MatchedMuonPhi, histCollection->histIsoMb12MatchedMuonPhi, histCollection->histIsoMb1MatchedMuonN3x3Phi, histCollection->histIsoMb2MatchedMuonN3x3Phi, histCollection->histIsoMb12MatchedMuonN3x3Phi}) {
			hist->Add(histCollection->histTfMapMatchedMuonPhi.at(Utility::Bmtf));
		}

		TGraphAsymmErrors *efficiencyIsoMb1Pt = new TGraphAsymmErrors(histCollection->histIsoMb1MatchedMuonPt);
		TGraphAsymmErrors *efficiencyIsoMb1Eta = new TGraphAsymmErrors(histCollection->histIsoMb1MatchedMuonEta);
		TGraphAsymmErrors *efficiencyIsoMb1Phi = new TGraphAsymmErrors(histCollection->histIsoMb1MatchedMuonPhi);
		efficiencyIsoMb1Pt->Divide(histCollection->histIsoMb1MatchedMuonPt, histCollection->histProbeMuonMapPt.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb1Eta->Divide(histCollection->histIsoMb1MatchedMuonEta, histCollection->histProbeMuonMapEta.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb1Phi->Divide(histCollection->histIsoMb1MatchedMuonPhi, histCollection->histProbeMuonMapPhi.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb1Pt->Write("efficiencyIsoMb1Pt");
		efficiencyIsoMb1Eta->Write("efficiencyIsoMb1Eta");
		efficiencyIsoMb1Phi->Write("efficiencyIsoMb1Phi");
		delete efficiencyIsoMb1Pt; delete efficiencyIsoMb1Eta; delete efficiencyIsoMb1Phi;

		TGraphAsymmErrors *efficiencyIsoMb2Pt = new TGraphAsymmErrors(histCollection->histIsoMb2MatchedMuonPt);
		TGraphAsymmErrors *efficiencyIsoMb2Eta = new TGraphAsymmErrors(histCollection->histIsoMb2MatchedMuonEta);
		TGraphAsymmErrors *efficiencyIsoMb2Phi = new TGraphAsymmErrors(histCollection->histIsoMb2MatchedMuonPhi);
		efficiencyIsoMb2Pt->Divide(histCollection->histIsoMb2MatchedMuonPt, histCollection->histProbeMuonMapPt.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb2Eta->Divide(histCollection->histIsoMb2MatchedMuonEta, histCollection->histProbeMuonMapEta.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb2Phi->Divide(histCollection->histIsoMb2MatchedMuonPhi, histCollection->histProbeMuonMapPhi.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb2Pt->Write("efficiencyIsoMb2Pt");
		efficiencyIsoMb2Eta->Write("efficiencyIsoMb2Eta");
		efficiencyIsoMb2Eta->Write("efficiencyIsoMb2Eta");
		delete efficiencyIsoMb2Pt; delete efficiencyIsoMb2Eta; delete efficiencyIsoMb2Phi;

		TGraphAsymmErrors *efficiencyIsoMb12Pt = new TGraphAsymmErrors(histCollection->histIsoMb12MatchedMuonPt);
		TGraphAsymmErrors *efficiencyIsoMb12Eta = new TGraphAsymmErrors(histCollection->histIsoMb12MatchedMuonEta);
		TGraphAsymmErrors *efficiencyIsoMb12Phi = new TGraphAsymmErrors(histCollection->histIsoMb12MatchedMuonPhi);
		efficiencyIsoMb12Pt->Divide(histCollection->histIsoMb12MatchedMuonPt, histCollection->histProbeMuonMapPt.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb12Eta->Divide(histCollection->histIsoMb12MatchedMuonEta, histCollection->histProbeMuonMapEta.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb12Phi->Divide(histCollection->histIsoMb12MatchedMuonPhi, histCollection->histProbeMuonMapPhi.at(Utility::Bmtf), "cl=0.683 b(1,1) mode");
		efficiencyIsoMb12Pt->Write("efficiencyIsoMb12Pt");
		efficiencyIsoMb12Eta->Write("efficiencyIsoMb12Eta");
		efficiencyIsoMb12Phi->Write("efficiencyIsoMb12Phi");
		delete efficiencyIsoMb12Pt; delete efficiencyIsoMb12Eta; delete efficiencyIsoMb12Phi;

		TGraphAsymmErrors *efficiencyTfPt = new TGraphAsymmErrors(histCollection->histTfMapMatchedMuonPt.at(Utility::UGMT));
		TGraphAsymmErrors *efficiencyTfEta = new TGraphAsymmErrors(histCollection->histTfMapMatchedMuonEta.at(Utility::UGMT));
		TGraphAsymmErrors *efficiencyTfPhi = new TGraphAsymmErrors(histCollection->histTfMapMatchedMuonPhi.at(Utility::UGMT));
		efficiencyTfPt->Divide(histCollection->histTfMapMatchedMuonPt.at(Utility::UGMT), histCollection->histProbeMuonPt, "cl=0.683 b(1,1) mode");
		efficiencyTfEta->Divide(histCollection->histTfMapMatchedMuonEta.at(Utility::UGMT), histCollection->histProbeMuonEta, "cl=0.683 b(1,1) mode");
		efficiencyTfPhi->Divide(histCollection->histTfMapMatchedMuonPhi.at(Utility::UGMT), histCollection->histProbeMuonPhi, "cl=0.683 b(1,1) mode");
		efficiencyTfPt->Write("efficiencyTfPt");
		efficiencyTfEta->Write("efficiencyTfEta");
		efficiencyTfPhi->Write("efficiencyTfPhi");
		delete efficiencyTfPt; delete efficiencyTfEta; delete efficiencyTfPhi;

		//histCollection->histIsoMb1MatchedMuonPt_vs_MuonEta->Fill(product->probeMuonPt.at(i), product->probeMuonEta.at(i), (product->dttpStation.at(product->muonMatchedDttpIndex.at(i)) == 1));
		TH2D *efficiencyBmtfMuonEta_vs_MuonPt = (TH2D*)histCollection->histBmtfMatchedMuonEta_vs_MuonPt->Clone("efficiencyBmtfMatchedMuonEta_vs_Pt");
		efficiencyBmtfMuonEta_vs_MuonPt->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPt);
		efficiencyBmtfMuonEta_vs_MuonPt->Write("efficiencyBmtfMuonEta_vs_MuonPt");

		TH2D *efficiencyIsoMb1MuonEta_vs_MuonPt = (TH2D*)histCollection->histIsoMb1MatchedMuonEta_vs_MuonPt->Clone("efficiencyIsoMb1MatchedMuonEta_vs_Pt");
		efficiencyIsoMb1MuonEta_vs_MuonPt->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPt);
		efficiencyIsoMb1MuonEta_vs_MuonPt->Write("efficiencyIsoMb1MuonEta_vs_MuonPt");

		TH2D *efficiencyIsoMb2MuonEta_vs_MuonPt = (TH2D*)histCollection->histIsoMb2MatchedMuonEta_vs_MuonPt->Clone("efficiencyIsoMb2MatchedMuonEta_vs_Pt");
		efficiencyIsoMb2MuonEta_vs_MuonPt->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPt);
		efficiencyIsoMb2MuonEta_vs_MuonPt->Write("efficiencyIsoMb2MuonEta_vs_MuonPt");

		TH2D *efficiencyIsoMb12MuonEta_vs_MuonPt = (TH2D*)histCollection->histIsoMb12MatchedMuonEta_vs_MuonPt->Clone("efficiencyIsoMb12MatchedMuonEta_vs_Pt");
		efficiencyIsoMb12MuonEta_vs_MuonPt->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPt);
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

		TH2D *efficiencyTfMuonEta_vs_MuonPt = (TH2D*)histCollection->histTfMatchedMuonEta_vs_MuonPt->Clone("efficiencyTfMatchedMuonEta_vs_Pt");
		efficiencyTfMuonEta_vs_MuonPt->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPt);
		efficiencyTfMuonEta_vs_MuonPt->Write("efficiencyTfMuonEta_vs_MuonPt");
	} else {
		TH1D* histBmtfRate = (TH1D*)histCollection->histBmtfNumber->Clone("bmtfRate");
		histBmtfRate->Scale(1 / histCollection->numberOfEvents->GetBinContent(1));

		TH1D *histDttpMatchedHoRate = (TH1D*)histCollection->histDttpMatchedHoNumber->Clone("dttpMatchedHoRate");
		histDttpMatchedHoRate->Scale(1 / histCollection->numberOfEvents->GetBinContent(1));

		TH1D *histDttpMatchedHoRelativeRate = (TH1D*)histCollection->histDttpMatchedHoNumber->Clone("dttpMatchedHoRelativeRate");
		histDttpMatchedHoRelativeRate->Divide(histCollection->histBmtfNumber);

		TH1D *histBmtfMb34MatchedHoRate = (TH1D*)histCollection->histBmtfMb34MatchedHoNumber->Clone("bmtfMb34MatchedHoRate");
		histBmtfMb34MatchedHoRate->Scale(1 / histCollection->numberOfEvents->GetBinContent(1));

		TH1D *histDttpMatchedHoN3x3Rate = (TH1D*)histCollection->histDttpMatchedHoN3x3Number->Clone("dttpMatchedHoN3x3Rate");
		histDttpMatchedHoN3x3Rate->Scale(1 / histCollection->numberOfEvents->GetBinContent(1));

		TH1D *histDttpMatchedHoN3x3RelativeRate = (TH1D*)histCollection->histDttpMatchedHoN3x3Number->Clone("dttpMatchedHoN3x3RelativeRate");
		histDttpMatchedHoN3x3RelativeRate->Divide(histCollection->histBmtfNumber);
	}
}

HoHistogramProducer::~HoHistogramProducer() {}
