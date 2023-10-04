#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>

HoHistogramProducer::HoHistogramProducer() {
	Name = "Histogram Producer";
}
//int histCounter = 0;

void HoHistogramProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	const float maxPt = 149.5;
	for (unsigned int iBmtf = 0; iBmtf < product->tfMuonSize.at(Utility::Bmtf); iBmtf++) {
		histCollection->histIsBmtfMatchedDttp->Fill(product->isBmtfMatchedDttp.at(iBmtf));
		if (!product->isBmtfMatchedDttp.at(iBmtf)) { continue;}
		histCollection->histBmtfMatchedDttpDeltaPhi->Fill(product->bmtfMatchedDttpDeltaPhi.at(iBmtf));
		histCollection->histBmtfMatchedDttpCmsPt->Fill(std::min(maxPt, (float)product->bmtfMatchedDttpCmsPt.at(iBmtf)));
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

					histCollection->histTfMatchedMuonEta_vs_MuonPt.at(tfType)->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf), product->tfMatchedMuonPt.at(tfType).at(iTf), product->isTfMatchedMuon.at(tfType).at(iTf));
					histCollection->histTfMatchedMuonEta_vs_MuonPhi.at(tfType)->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf), product->tfMatchedMuonPhi.at(tfType).at(iTf), product->isTfMatchedMuon.at(tfType).at(iTf));

					histCollection->histTfMapMatchedMuonPt.at(Utility::UGMT)->Fill(product->tfMatchedMuonPt.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonPtFineBinning.at(Utility::UGMT)->Fill(product->tfMatchedMuonPt.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonEta.at(Utility::UGMT)->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonPhi.at(Utility::UGMT)->Fill(product->tfMatchedMuonPhi.at(tfType).at(iTf));
					histCollection->histTfMapMatchedMuonTfType.at(Utility::UGMT)->Fill(product->tfMatchedMuonTfType.at(tfType).at(iTf));

					histCollection->histTfMatchedMuonPt_vs_MuonEta.at(Utility::UGMT)->Fill(product->tfMatchedMuonPt.at(tfType).at(iTf), product->tfMatchedMuonEta.at(tfType).at(iTf), product->isTfMatchedMuon.at(tfType).at(iTf));
					histCollection->histTfMatchedMuonEta_vs_MuonPt.at(Utility::UGMT)->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf), product->tfMatchedMuonPt.at(tfType).at(iTf), product->isTfMatchedMuon.at(tfType).at(iTf));
					histCollection->histTfMatchedMuonEta_vs_MuonPhi.at(Utility::UGMT)->Fill(product->tfMatchedMuonEta.at(tfType).at(iTf), product->tfMatchedMuonPhi.at(tfType).at(iTf), product->isTfMatchedMuon.at(tfType).at(iTf));
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


					//histCollection->histMuonPt_vs_MuonEta->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPt.at(iProbe));
					histCollection->histMuonEta_vs_MuonPt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)), product->probeMuonEta.at(iProbe));
					histCollection->histMuonEta_vs_MuonPhi->Fill(product->probeMuonPhi.at(iProbe), product->probeMuonEta.at(iProbe));
				}
			}
		}

		for (int iProbe = 0; iProbe < product->nProbeMuon; iProbe++) {
			histCollection->histMuonHoN3x3Hit->Fill(product->muonHoN3x3Hit.at(iProbe));

			// Only use the IsoMb1/2 if the BMTF does not reconstruct a muon
			if (!product->isMuonMatchedTf.at(iProbe) && product->isMuonMatchedDttp.at(iProbe)) {
				int iDttp = product->muonMatchedDttpIndex.at(iProbe);
				if (product->dttpStation.at(iDttp) == 1) {
					histCollection->histIsoMb1MatchedMuonPt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
					histCollection->histIsoMb1MatchedMuonPtFineBinning->Fill(product->probeMuonPt.at(iProbe));
					histCollection->histIsoMb1MatchedMuonEta->Fill(product->probeMuonEta.at(iProbe));
					histCollection->histIsoMb1MatchedMuonPhi->Fill(product->probeMuonPhi.at(iProbe));

					histCollection->histIsoMb1MatchedMuonDeltaR->Fill(product->dttpMatchedMuonDeltaR.at(iDttp));
					histCollection->histIsoMb1MatchedMuonDeltaEta->Fill(product->dttpMatchedMuonDeltaEta.at(iDttp));
					//histCollection->histIsoMb1MatchedMuonDeltaPhi->Fill(product->dttpMatchedMuonDeltaPhi.at(iDttp));

					histCollection->histIsoMb1MatchedMuonEta_vs_MuonPt->Fill(std::min(maxPt, product->probeMuonEta.at(iProbe)), product->probeMuonPt.at(iProbe));
					histCollection->histIsoMb1MatchedMuonEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
				} else if (product->dttpStation.at(iDttp) == 2) {
					histCollection->histIsoMb2MatchedMuonPt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
					histCollection->histIsoMb2MatchedMuonPtFineBinning->Fill(product->probeMuonPt.at(iProbe));
					histCollection->histIsoMb2MatchedMuonEta->Fill(product->probeMuonEta.at(iProbe));
					histCollection->histIsoMb2MatchedMuonPhi->Fill(product->probeMuonPhi.at(iProbe));

					histCollection->histIsoMb2MatchedMuonDeltaR->Fill(product->dttpMatchedMuonDeltaR.at(iDttp));
					histCollection->histIsoMb2MatchedMuonDeltaEta->Fill(product->dttpMatchedMuonDeltaEta.at(iDttp));
					//histCollection->histIsoMb2MatchedMuonDeltaPhi->Fill(product->dttpMatchedMuonDeltaPhi.at(iDttp));

					histCollection->histIsoMb2MatchedMuonEta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
					histCollection->histIsoMb2MatchedMuonEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
				}

				if (product->dttpStation.at(iDttp) <= 2) {
					histCollection->histIsoMb12MatchedMuonPt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
					histCollection->histIsoMb12MatchedMuonPtFineBinning->Fill(product->probeMuonPt.at(iProbe));
					histCollection->histIsoMb12MatchedMuonEta->Fill(product->probeMuonEta.at(iProbe));
					histCollection->histIsoMb12MatchedMuonPhi->Fill(product->probeMuonPhi.at(iProbe));

					histCollection->histIsoMb12MatchedMuonDeltaR->Fill(product->dttpMatchedMuonDeltaR.at(iDttp));
					histCollection->histIsoMb12MatchedMuonDeltaEta->Fill(product->dttpMatchedMuonDeltaEta.at(iDttp));
					//histCollection->histIsoMb12MatchedMuonDeltaPhi->Fill(product->dttpMatchedMuonDeltaPhi.at(iDttp));

					histCollection->histIsoMb12MatchedMuonEta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
					histCollection->histIsoMb12MatchedMuonEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
				}

				const bool &n3x3Cut = product->dttpMatchedMuonHoN3x3Hit.at(iDttp) <= 1;
				if (n3x3Cut) {
					if (product->dttpStation.at(iDttp) == 1) {
						histCollection->histIsoMb1MatchedMuonN3x3Pt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb1MatchedMuonN3x3PtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb1MatchedMuonN3x3Eta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb1MatchedMuonN3x3Phi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb1MatchedMuonN3x3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb1MatchedMuonN3x3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					} else if (product->dttpStation.at(iDttp) == 2) {
						histCollection->histIsoMb2MatchedMuonN3x3Pt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb2MatchedMuonN3x3PtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb2MatchedMuonN3x3Eta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb2MatchedMuonN3x3Phi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb2MatchedMuonN3x3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb2MatchedMuonN3x3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					}

					if (product->dttpStation.at(iDttp) <= 2) {
						histCollection->histIsoMb12MatchedMuonN3x3Pt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb12MatchedMuonN3x3PtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb12MatchedMuonN3x3Eta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb12MatchedMuonN3x3Phi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb12MatchedMuonN3x3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb12MatchedMuonN3x3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					}
				}

				if (std::abs(product->hcalIEta.at(product->muonMatchedHoIndex.at(iProbe))) == 3) {
					if (product->dttpStation.at(iDttp) == 1) {
						histCollection->histIsoMb1MatchedMuonAbsIEta3Pt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb1MatchedMuonAbsIEta3PtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb1MatchedMuonAbsIEta3Eta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb1MatchedMuonAbsIEta3Phi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb1MatchedMuonAbsIEta3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb1MatchedMuonAbsIEta3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					} else if (product->dttpStation.at(iDttp) == 2) {
						histCollection->histIsoMb2MatchedMuonAbsIEta3Pt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb2MatchedMuonAbsIEta3PtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb2MatchedMuonAbsIEta3Eta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb2MatchedMuonAbsIEta3Phi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb2MatchedMuonAbsIEta3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb2MatchedMuonAbsIEta3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					}

					if (product->dttpStation.at(iDttp) <= 2) {
						histCollection->histIsoMb12MatchedMuonAbsIEta3Pt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb12MatchedMuonAbsIEta3PtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb12MatchedMuonAbsIEta3Eta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb12MatchedMuonAbsIEta3Phi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb12MatchedMuonAbsIEta3Eta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb12MatchedMuonAbsIEta3Eta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					}
				}

				if (std::abs(product->hcalQIESampleAdc.at(product->muonMatchedHoIndex.at(iProbe))) >= 20) {
					if (product->dttpStation.at(iDttp) == 1) {
						histCollection->histIsoMb1MatchedMuonHighADCPt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb1MatchedMuonHighADCPtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb1MatchedMuonHighADCEta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb1MatchedMuonHighADCPhi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb1MatchedMuonHighADCEta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb1MatchedMuonHighADCEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					} else if (product->dttpStation.at(iDttp) == 2) {
						histCollection->histIsoMb2MatchedMuonHighADCPt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb2MatchedMuonHighADCPtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb2MatchedMuonHighADCEta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb2MatchedMuonHighADCPhi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb2MatchedMuonHighADCEta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb2MatchedMuonHighADCEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					}

					if (product->dttpStation.at(iDttp) <= 2) {
						histCollection->histIsoMb12MatchedMuonHighADCPt->Fill(std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb12MatchedMuonHighADCPtFineBinning->Fill(product->probeMuonPt.at(iProbe));
						histCollection->histIsoMb12MatchedMuonHighADCEta->Fill(product->probeMuonEta.at(iProbe));
						histCollection->histIsoMb12MatchedMuonHighADCPhi->Fill(product->probeMuonPhi.at(iProbe));
						histCollection->histIsoMb12MatchedMuonHighADCEta_vs_MuonPt->Fill(product->probeMuonEta.at(iProbe), std::min(maxPt, product->probeMuonPt.at(iProbe)));
						histCollection->histIsoMb12MatchedMuonHighADCEta_vs_MuonPhi->Fill(product->probeMuonEta.at(iProbe), product->probeMuonPhi.at(iProbe));
					}
				}
			}
		}
	}


	//for (unsigned iHo = 0; iHo < dataReader->hcalDetIdIEta->GetSize(); iHo++) {
	//for (int iDttp = 0; iDttp < product->dttpSize; iDttp++) {
	for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
		//unsigned int iHo = product->dttpMatchedHoIndex.at(iDttp);
		int iDttp = product->hoMatchedDttpIndex.at(iHo);
		bool isIsoMbMatch = product->isHoMatchedDttp.at(iHo);
		// For rate it is sufficient to check if isDttpMatchedHo
		// But for efficiency we only want to consider those matched that are matched to recomuons
		if (isIsoMbMatch && dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
			isIsoMbMatch = product->isDttpMatchedMuon.at(iDttp);
		}

		if (isIsoMbMatch) {
			if (product->dttpStation.at(iDttp) == 1) {
				histCollection->histSampleEnergy_isoMb1->Fill(product->SampleEnergy.at(iHo));
				histCollection->histHcalDetIdIEta_isoMb1->Fill(product->hcalIEta.at(iHo));
				histCollection->histHcalDetIdIPhi_isoMb1->Fill(product->hcalIPhi.at(iHo));
				histCollection->histHcalCmsEta_isoMb1->Fill(product->hcalCmsEta.at(iHo));
				histCollection->histHcalCmsPhi_isoMb1->Fill(product->hcalCmsPhi.at(iHo));
				histCollection->histHcalWheel_isoMb1->Fill(product->hcalWheel.at(iHo));
				histCollection->histHcalSection_isoMb1->Fill(product->hcalSection.at(iHo));
				//histCollection->histSumQ_isoMb1->Fill(product->sumQ.at(iHo));
				//histCollection->histNHcalQIESamples_isoMb1->Fill(product->nHcalQIESamples.at(iHo));
				histCollection->histHcalQIESample_isoMb1->Fill(product->hcalQIESample.at(iHo));
				histCollection->histHcalQIESampleAdc_isoMb1->Fill(product->hcalQIESampleAdc.at(iHo));
				histCollection->histHcalQIESampleDv_isoMb1->Fill(product->hcalQIESampleDv.at(iHo));
				histCollection->histHcalQIESampleEr_isoMb1->Fill(product->hcalQIESampleEr.at(iHo));
				histCollection->histQIESampleFc_isoMb1->Fill(product->QIESampleFc.at(iHo));
				histCollection->histQIESamplePedestal_isoMb1->Fill(product->QIESamplePedestal.at(iHo));
				//histCollection->histQIESampleFc_MPedestals_isoMb1->Fill(product->QIESampleFc_MPedestals_isoMb1.at(iHo));
			}
			if (product->dttpStation.at(iDttp) == 2) {
				histCollection->histSampleEnergy_isoMb2->Fill(product->SampleEnergy.at(iHo));
				histCollection->histHcalDetIdIEta_isoMb2->Fill(product->hcalIEta.at(iHo));
				histCollection->histHcalDetIdIPhi_isoMb2->Fill(product->hcalIPhi.at(iHo));
				histCollection->histHcalCmsEta_isoMb2->Fill(product->hcalCmsEta.at(iHo));
				histCollection->histHcalCmsPhi_isoMb2->Fill(product->hcalCmsPhi.at(iHo));
				histCollection->histHcalWheel_isoMb2->Fill(product->hcalWheel.at(iHo));
				histCollection->histHcalSection_isoMb2->Fill(product->hcalSection.at(iHo));
				//histCollection->histSumQ_isoMb2->Fill(product->sumQ.at(iHo));
				//histCollection->histNHcalQIESamples_isoMb2->Fill(product->nHcalQIESamples.at(iHo));
				histCollection->histHcalQIESample_isoMb2->Fill(product->hcalQIESample.at(iHo));
				histCollection->histHcalQIESampleAdc_isoMb2->Fill(product->hcalQIESampleAdc.at(iHo));
				histCollection->histHcalQIESampleDv_isoMb2->Fill(product->hcalQIESampleDv.at(iHo));
				histCollection->histHcalQIESampleEr_isoMb2->Fill(product->hcalQIESampleEr.at(iHo));
				histCollection->histQIESampleFc_isoMb2->Fill(product->QIESampleFc.at(iHo));
				histCollection->histQIESamplePedestal_isoMb2->Fill(product->QIESamplePedestal.at(iHo));
				//histCollection->histQIESampleFc_MPedestals_isoMb2->Fill(product->QIESampleFc_MPedestals_isoMb2.at(iHo));
			}
			if (product->dttpStation.at(iDttp) <= 2) {
				histCollection->histSampleEnergy_isoMb12->Fill(product->SampleEnergy.at(iHo));
				histCollection->histHcalDetIdIEta_isoMb12->Fill(product->hcalIEta.at(iHo));
				histCollection->histHcalDetIdIPhi_isoMb12->Fill(product->hcalIPhi.at(iHo));
				histCollection->histHcalCmsEta_isoMb12->Fill(product->hcalCmsEta.at(iHo));
				histCollection->histHcalCmsPhi_isoMb12->Fill(product->hcalCmsPhi.at(iHo));
				histCollection->histHcalWheel_isoMb12->Fill(product->hcalWheel.at(iHo));
				histCollection->histHcalSection_isoMb12->Fill(product->hcalSection.at(iHo));
				//histCollection->histSumQ_isoMb12->Fill(product->sumQ.at(iHo));
				//histCollection->histNHcalQIESamples_isoMb12->Fill(product->nHcalQIESamples.at(iHo));
				histCollection->histHcalQIESample_isoMb12->Fill(product->hcalQIESample.at(iHo));
				histCollection->histHcalQIESampleAdc_isoMb12->Fill(product->hcalQIESampleAdc.at(iHo));
				histCollection->histHcalQIESampleDv_isoMb12->Fill(product->hcalQIESampleDv.at(iHo));
				histCollection->histHcalQIESampleEr_isoMb12->Fill(product->hcalQIESampleEr.at(iHo));
				histCollection->histQIESampleFc_isoMb12->Fill(product->QIESampleFc.at(iHo));
				histCollection->histQIESamplePedestal_isoMb12->Fill(product->QIESamplePedestal.at(iHo));
				//histCollection->histQIESampleFc_MPedestals_isoMb12->Fill(product->QIESampleFc_MPedestals_isoMb12.at(iHo));
			}
		} else {
			histCollection->histSampleEnergy_notIsoMbMatched->Fill(product->SampleEnergy.at(iHo));
			histCollection->histHcalDetIdIEta_notIsoMbMatched->Fill(product->hcalIEta.at(iHo));
			histCollection->histHcalDetIdIPhi_notIsoMbMatched->Fill(product->hcalIPhi.at(iHo));
			histCollection->histHcalCmsEta_notIsoMbMatched->Fill(product->hcalCmsEta.at(iHo));
			histCollection->histHcalCmsPhi_notIsoMbMatched->Fill(product->hcalCmsPhi.at(iHo));
			histCollection->histHcalWheel_notIsoMbMatched->Fill(product->hcalWheel.at(iHo));
			histCollection->histHcalSection_notIsoMbMatched->Fill(product->hcalSection.at(iHo));
			//histCollection->histSumQ_notIsoMbMatched->Fill(product->sumQ.at(iHo));
			//histCollection->histNHcalQIESamples_notIsoMbMatched->Fill(product->nHcalQIESamples.at(iHo));
			histCollection->histHcalQIESample_notIsoMbMatched->Fill(product->hcalQIESample.at(iHo));
			histCollection->histHcalQIESampleAdc_notIsoMbMatched->Fill(product->hcalQIESampleAdc.at(iHo));
			histCollection->histHcalQIESampleDv_notIsoMbMatched->Fill(product->hcalQIESampleDv.at(iHo));
			histCollection->histHcalQIESampleEr_notIsoMbMatched->Fill(product->hcalQIESampleEr.at(iHo));
			histCollection->histQIESampleFc_notIsoMbMatched->Fill(product->QIESampleFc.at(iHo));
			histCollection->histQIESamplePedestal_notIsoMbMatched->Fill(product->QIESamplePedestal.at(iHo));
			//histCollection->histQIESampleFc_MPedestals_notIsoMbMatched->Fill(product->QIESampleFc_MPedestals_notIsoMbMatched.at(iHo));
		}


		if (product->isHoMatchedMuon.at(iHo)) {
			histCollection->histMuonMatchedSampleEnergy->Fill(product->SampleEnergy.at(iHo));
			histCollection->histMuonMatchedHcalDetIdIEta->Fill(product->hcalIEta.at(iHo));
			histCollection->histMuonMatchedHcalDetIdIPhi->Fill(product->hcalIPhi.at(iHo));
			histCollection->histMuonMatchedHcalCmsEta->Fill(product->hcalCmsEta.at(iHo));
			histCollection->histMuonMatchedHcalCmsPhi->Fill(product->hcalCmsPhi.at(iHo));
			histCollection->histMuonMatchedHcalWheel->Fill(product->hcalWheel.at(iHo));
			histCollection->histMuonMatchedHcalSection->Fill(product->hcalSection.at(iHo));
			histCollection->histMuonMatchedHcalQIESample->Fill(product->hcalQIESample.at(iHo));
			histCollection->histMuonMatchedHcalQIESampleAdc->Fill(product->hcalQIESampleAdc.at(iHo));
			histCollection->histMuonMatchedHcalQIESampleDv->Fill(product->hcalQIESampleDv.at(iHo));
			histCollection->histMuonMatchedHcalQIESampleEr->Fill(product->hcalQIESampleEr.at(iHo));
			histCollection->histMuonMatchedQIESampleFc->Fill(product->QIESampleFc.at(iHo));
			histCollection->histMuonMatchedQIESamplePedestal->Fill(product->QIESamplePedestal.at(iHo));
			histCollection->histMuonMatchedQIESampleFc_MPedestals->Fill(product->QIESampleFc_MPedestals.at(iHo));
			histCollection->histMuonMatchedHoDeltaR->Fill(product->hoMatchedMuonDeltaR.at(iHo));
		}
	}

	for (unsigned int iBmtf = 0; iBmtf < product->tfMuonSize.at(Utility::Bmtf); iBmtf++) {
		histCollection->histIsMb3HoIEtaMatched->Fill(product->isMb3HoIEtaMatched.at(iBmtf));
		histCollection->histIsMb4HoIEtaMatched->Fill(product->isMb4HoIEtaMatched.at(iBmtf));
		const bool &isMb34Matched = product->isMb3HoIEtaMatched.at(iBmtf) || product->isMb4HoIEtaMatched.at(iBmtf);
		if (isMb34Matched) {
			histCollection->histBmtfMb34MatchedHoNumber->Fill("bmtfMb34MatchedHoNumber", 1);
			histCollection->histBmtfMb34MatchedHoDeltaR->Fill(product->bmtfMb34MatchedHoDeltaR.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoPt->Fill(std::min(maxPt, (float)product->bmtfMb34MatchedHoPt.at(iBmtf)), isMb34Matched);
			//histCollection->histBmtfMb34MatchedHoCmsEta->Fill(product->bmtfMb34MatchedHoCmsEta.at(iBmtf), isMb34Matched);
			//histCollection->histBmtfMb34MatchedHoCmsPhi->Fill(product->bmtfMb34MatchedHoCmsPhi.at(iBmtf), isMb34Matched);
			//histCollection->histBmtfMb34MatchedHoDeltaPhi->Fill(product->bmtfMb34MatchedHoDeltaPhi.at(iBmtf), isMb34Matched);
			if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
				histCollection->histBmtfMb34MatchedMuonPt->Fill(std::min(maxPt, (float)product->bmtfMb34MatchedMuonPt.at(iBmtf)), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonPtFineBinning->Fill(product->bmtfMb34MatchedMuonPt.at(iBmtf), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonEta->Fill(product->bmtfMb34MatchedMuonEta.at(iBmtf), isMb34Matched);
				histCollection->histBmtfMb34MatchedMuonPhi->Fill(product->bmtfMb34MatchedMuonPhi.at(iBmtf), isMb34Matched);
				//histCollection->histBmtfMb34MatchedMuonDeltaPhi->Fill(product->bmtfMb34MatchedMuonDeltaPhi.at(iBmtf), isMb34Matched);
			}
			histCollection->histBmtfMb34MatchedHoIEta->Fill(product->bmtfMb34MatchedHoIEta.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoIPhi->Fill(product->bmtfMb34MatchedHoIPhi.at(iBmtf), isMb34Matched);
			histCollection->histBmtfMb34MatchedHoDeltaIPhi->Fill(product->bmtfMb34MatchedHoDeltaIPhi.at(iBmtf), isMb34Matched);
		} else {
			if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
				histCollection->histBmtfMb34MatchedMuonPt->Fill(std::min(maxPt, (float)product->tfMatchedMuonPt.at(Utility::Bmtf).at(iBmtf)));
				histCollection->histBmtfMb34MatchedMuonPtFineBinning->Fill(product->tfMatchedMuonPt.at(Utility::Bmtf).at(iBmtf));
				histCollection->histBmtfMb34MatchedMuonEta->Fill(product->tfMatchedMuonEta.at(Utility::Bmtf).at(iBmtf));
				histCollection->histBmtfMb34MatchedMuonPhi->Fill(product->tfMatchedMuonPhi.at(Utility::Bmtf).at(iBmtf));
				//histCollection->histBmtfMb34MatchedMuonDeltaPhi->Fill(product->bmtfMatchedMuonDeltaPhi.at(iBmtf));
			}
		}
		//unsigned int iProbe = product->dttpMatchedMuonIndex.at(i);
	}


	for (int iDttp = 0; iDttp < product->dttpSize; iDttp++) {
		//const bool &n3x3Cut = product->muonMatchedDttpHoN3x3Hit.at(iDttp) <= 1;
		bool n3x3Cut = false;
		histCollection->histDttpMatchedHoN3x3Hit->Fill(product->dttpHoN3x3Hit.at(iDttp));
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
		if (std::abs(product->dttpMatchedHoIEta.at(iDttp)) == 3) {
			histCollection->histIsDttpMatchedHoAbsIEta3->Fill(product->isDttpMatchedHo.at(iDttp));
		}

		if (product->isDttpMatchedHo.at(iDttp)) {
			histCollection->histDttpMatchedHoNumber->Fill("dttpMatchedHoNumber", 1);
			//histCollection->histDttpMatchedHoDeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
			histCollection->histDttpMatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
			histCollection->histDttpMatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
			histCollection->histDttpMatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
			//histCollection->histDttpMatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
			//histCollection->histDttpMatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
			if (n3x3Cut) {
				histCollection->histDttpMatchedHoN3x3Number->Fill("dttpMatchedHoN3x3Number", 1);
				//histCollection->histDttpMatchedHoN3x3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
				histCollection->histDttpMatchedHoN3x3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
				histCollection->histDttpMatchedHoN3x3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
				histCollection->histDttpMatchedHoN3x3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
				//histCollection->histDttpMatchedHoN3x3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
				//histCollection->histDttpMatchedHoN3x3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
			}

			if (std::abs(product->dttpMatchedHoIEta.at(iDttp)) == 3) {
				histCollection->histDttpMatchedHoAbsIEta3Number->Fill("dttpMatchedHoAbsIEta3Number", 1);
				//histCollection->histDttpMatchedHoAbsIEta3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
				histCollection->histDttpMatchedHoAbsIEta3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
				histCollection->histDttpMatchedHoAbsIEta3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
				histCollection->histDttpMatchedHoAbsIEta3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
				//histCollection->histDttpMatchedHoAbsIEta3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
				//histCollection->histDttpMatchedHoAbsIEta3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
			}
			// isoMb1 Candidates
			if (product->dttpStation.at(iDttp) == 1) {
				histCollection->histDttpMb1MatchedHoNumber->Fill("dttpMb1MatchedHoNumber", 1);
				//histCollection->histDttpMb1MatchedHoDeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
				//histCollection->histDttpMb1MatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
				//histCollection->histDttpMb1MatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
				//histCollection->histDttpMb1MatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
				//histCollection->histDttpMb1MatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
				//histCollection->histDttpMb1MatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));

				if (n3x3Cut) {
					histCollection->histDttpMb1MatchedHoN3x3Number->Fill("dttpMb1MatchedHoN3x3Number", 1);
					//histCollection->histDttpMb1MatchedHoN3x3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
					//histCollection->histDttpMb1MatchedHoN3x3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
					//histCollection->histDttpMb1MatchedHoN3x3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
					//histCollection->histDttpMb1MatchedHoN3x3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
					//histCollection->histDttpMb1MatchedHoN3x3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
					//histCollection->histDttpMb1MatchedHoN3x3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
				}

				if (std::abs(product->dttpMatchedHoIEta.at(iDttp)) == 3) {
					histCollection->histDttpMb1MatchedHoAbsIEta3Number->Fill("dttpMb1MatchedHoAbsIEta3Number", 1);
					//histCollection->histDttpMb1MatchedHoAbsIEta3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
					//histCollection->histDttpMb1MatchedHoAbsIEta3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
					//histCollection->histDttpMb1MatchedHoAbsIEta3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
					//histCollection->histDttpMb1MatchedHoAbsIEta3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
					//histCollection->histDttpMb1MatchedHoAbsIEta3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
					//histCollection->histDttpMb1MatchedHoAbsIEta3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
				}
			}
			// isoMb2 Candidates
			if (product->dttpStation.at(iDttp) == 2) {
				histCollection->histDttpMb2MatchedHoNumber->Fill("dttpMb2MatchedHoNumber", 1);
				//histCollection->histDttpMb2MatchedHoDeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
				//histCollection->histDttpMb2MatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
				//histCollection->histDttpMb2MatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
				//histCollection->histDttpMb2MatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
				//histCollection->histDttpMb2MatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
				//histCollection->histDttpMb2MatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));

				if (n3x3Cut) {
					histCollection->histDttpMb2MatchedHoN3x3Number->Fill("dttpMb2MatchedHoN3x3Number", 1);
					//histCollection->histDttpMb2MatchedHoN3x3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
					//histCollection->histDttpMb2MatchedHoN3x3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
					//histCollection->histDttpMb2MatchedHoN3x3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
					//histCollection->histDttpMb2MatchedHoN3x3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
					//histCollection->histDttpMb2MatchedHoN3x3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
					//histCollection->histDttpMb2MatchedHoN3x3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
				}

				if (std::abs(product->dttpMatchedHoIEta.at(iDttp)) == 3) {
					histCollection->histDttpMb2MatchedHoAbsIEta3Number->Fill("dttpMb2MatchedHoAbsIEta3Number", 1);
					//histCollection->histDttpMb2MatchedHoAbsIEta3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
					//histCollection->histDttpMb2MatchedHoAbsIEta3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
					//histCollection->histDttpMb2MatchedHoAbsIEta3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
					//histCollection->histDttpMb2MatchedHoAbsIEta3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
					//histCollection->histDttpMb2MatchedHoAbsIEta3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
					//histCollection->histDttpMb2MatchedHoAbsIEta3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
				}
			}
			// isoMb12 Candidates
			if (product->dttpStation.at(iDttp) <= 2) {
				histCollection->histDttpMb12MatchedHoNumber->Fill("dttpMb12MatchedHoNumber", 1);
				//histCollection->histDttpMb12MatchedHoDeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
				//histCollection->histDttpMb12MatchedHoDeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
				//histCollection->histDttpMb12MatchedHoIPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
				//histCollection->histDttpMb12MatchedHoIEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
				//histCollection->histDttpMb12MatchedHoCmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
				//histCollection->histDttpMb12MatchedHoCmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));

				if (n3x3Cut) {
					histCollection->histDttpMb12MatchedHoN3x3Number->Fill("dttpMb12MatchedHoN3x3Number", 1);
					//histCollection->histDttpMb12MatchedHoN3x3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
					//histCollection->histDttpMb12MatchedHoN3x3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
					//histCollection->histDttpMb12MatchedHoN3x3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
					//histCollection->histDttpMb12MatchedHoN3x3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
					//histCollection->histDttpMb12MatchedHoN3x3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
					//histCollection->histDttpMb12MatchedHoN3x3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
				}

				if (std::abs(product->dttpMatchedHoIEta.at(iDttp)) == 3) {
					histCollection->histDttpMb12MatchedHoAbsIEta3Number->Fill("dttpMb12MatchedHoAbsIEta3Number", 1);
					//histCollection->histDttpMb12MatchedHoAbsIEta3DeltaPhi->Fill(product->dttpMatchedHoDeltaPhi.at(iDttp));
					//histCollection->histDttpMb12MatchedHoAbsIEta3DeltaIPhi->Fill(product->dttpMatchedHoDeltaIPhi.at(iDttp));
					//histCollection->histDttpMb12MatchedHoAbsIEta3IPhi->Fill(product->dttpMatchedHoIPhi.at(iDttp));
					//histCollection->histDttpMb12MatchedHoAbsIEta3IEta->Fill(product->dttpMatchedHoIEta.at(iDttp));
					//histCollection->histDttpMb12MatchedHoAbsIEta3CmsPhi->Fill(product->dttpMatchedHoCmsPhi.at(iDttp));
					//histCollection->histDttpMb12MatchedHoAbsIEta3CmsEta->Fill(product->dttpMatchedHoCmsEta.at(iDttp));
				}
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
		for (TH1D *hist : {histCollection->histIsoMb1MatchedMuonPt, histCollection->histIsoMb2MatchedMuonPt, histCollection->histIsoMb12MatchedMuonPt, histCollection->histIsoMb1MatchedMuonN3x3Pt, histCollection->histIsoMb2MatchedMuonN3x3Pt, histCollection->histIsoMb12MatchedMuonN3x3Pt, histCollection->histIsoMb1MatchedMuonAbsIEta3Pt, histCollection->histIsoMb2MatchedMuonAbsIEta3Pt, histCollection->histIsoMb12MatchedMuonAbsIEta3Pt, histCollection->histIsoMb1MatchedMuonHighADCPt, histCollection->histIsoMb2MatchedMuonHighADCPt, histCollection->histIsoMb12MatchedMuonHighADCPt}) {
			hist->Add(histCollection->histTfMapMatchedMuonPt.at(Utility::Bmtf));
		}

		for (TH1D *hist : {histCollection->histIsoMb1MatchedMuonEta, histCollection->histIsoMb2MatchedMuonEta, histCollection->histIsoMb12MatchedMuonEta, histCollection->histIsoMb1MatchedMuonN3x3Eta, histCollection->histIsoMb2MatchedMuonN3x3Eta, histCollection->histIsoMb12MatchedMuonN3x3Eta, histCollection->histIsoMb1MatchedMuonAbsIEta3Eta, histCollection->histIsoMb2MatchedMuonAbsIEta3Eta, histCollection->histIsoMb12MatchedMuonAbsIEta3Eta, histCollection->histIsoMb1MatchedMuonHighADCEta, histCollection->histIsoMb2MatchedMuonHighADCEta, histCollection->histIsoMb12MatchedMuonHighADCEta}) {
			hist->Add(histCollection->histTfMapMatchedMuonEta.at(Utility::Bmtf));
		}

		for (TH1D *hist : {histCollection->histIsoMb1MatchedMuonPhi, histCollection->histIsoMb2MatchedMuonPhi, histCollection->histIsoMb12MatchedMuonPhi, histCollection->histIsoMb1MatchedMuonN3x3Phi, histCollection->histIsoMb2MatchedMuonN3x3Phi, histCollection->histIsoMb12MatchedMuonN3x3Phi, histCollection->histIsoMb1MatchedMuonAbsIEta3Phi, histCollection->histIsoMb2MatchedMuonAbsIEta3Phi, histCollection->histIsoMb12MatchedMuonAbsIEta3Phi, histCollection->histIsoMb1MatchedMuonHighADCPhi, histCollection->histIsoMb2MatchedMuonHighADCPhi, histCollection->histIsoMb12MatchedMuonHighADCPhi}) {
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

		for (TH2D *hist : {histCollection->histIsoMb1MatchedMuonEta_vs_MuonPt, histCollection->histIsoMb2MatchedMuonEta_vs_MuonPt, histCollection->histIsoMb12MatchedMuonEta_vs_MuonPt}) {
			hist->Add(histCollection->histTfMatchedMuonEta_vs_MuonPt.at(Utility::Bmtf));
		}
		for (TH2D *hist : {histCollection->histIsoMb1MatchedMuonEta_vs_MuonPhi, histCollection->histIsoMb2MatchedMuonEta_vs_MuonPhi, histCollection->histIsoMb12MatchedMuonEta_vs_MuonPhi}) {
			hist->Add(histCollection->histTfMatchedMuonEta_vs_MuonPhi.at(Utility::Bmtf));
		}
		TH2D *efficiencyBmtfMuonEta_vs_MuonPt = (TH2D*)histCollection->histTfMatchedMuonEta_vs_MuonPt.at(Utility::Bmtf)->Clone("efficiencyBmtfMatchedMuonEta_vs_Pt");
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

		TH2D *efficiencyTfMuonEta_vs_MuonPt = (TH2D*)histCollection->histTfMatchedMuonEta_vs_MuonPt.at(Utility::UGMT)->Clone("efficiencyTfMatchedMuonEta_vs_Pt");
		efficiencyTfMuonEta_vs_MuonPt->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPt);
		efficiencyTfMuonEta_vs_MuonPt->Write("efficiencyTfMuonEta_vs_MuonPt");

		TH2D *efficiencyBmtfMuonEta_vs_MuonPhi = (TH2D*)histCollection->histTfMatchedMuonEta_vs_MuonPhi.at(Utility::Bmtf)->Clone("efficiencyBmtfMatchedMuonEta_vs_Phi");
		efficiencyBmtfMuonEta_vs_MuonPhi->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPhi);
		efficiencyBmtfMuonEta_vs_MuonPhi->Write("efficiencyBmtfMuonEta_vs_MuonPhi");

		TH2D *efficiencyIsoMb1MuonEta_vs_MuonPhi = (TH2D*)histCollection->histIsoMb1MatchedMuonEta_vs_MuonPhi->Clone("efficiencyIsoMb1MatchedMuonEta_vs_Phi");
		efficiencyIsoMb1MuonEta_vs_MuonPhi->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPhi);
		efficiencyIsoMb1MuonEta_vs_MuonPhi->Write("efficiencyIsoMb1MuonEta_vs_MuonPhi");

		TH2D *efficiencyIsoMb2MuonEta_vs_MuonPhi = (TH2D*)histCollection->histIsoMb2MatchedMuonEta_vs_MuonPhi->Clone("efficiencyIsoMb2MatchedMuonEta_vs_Phi");
		efficiencyIsoMb2MuonEta_vs_MuonPhi->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPhi);
		efficiencyIsoMb2MuonEta_vs_MuonPhi->Write("efficiencyIsoMb2MuonEta_vs_MuonPhi");

		TH2D *efficiencyIsoMb12MuonEta_vs_MuonPhi = (TH2D*)histCollection->histIsoMb12MatchedMuonEta_vs_MuonPhi->Clone("efficiencyIsoMb12MatchedMuonEta_vs_Phi");
		efficiencyIsoMb12MuonEta_vs_MuonPhi->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPhi);
		efficiencyIsoMb12MuonEta_vs_MuonPhi->Write("efficiencyIsoMb12MuonEta_vs_MuonPhi");

		TH2D *efficiencyRatioIsoMB1MuonEta_vs_MuonPhi = (TH2D*)efficiencyIsoMb1MuonEta_vs_MuonPhi->Clone("efficiencyRatioIsoMB1MuonEta_vs_MuonPhi");
		efficiencyRatioIsoMB1MuonEta_vs_MuonPhi->Divide(efficiencyBmtfMuonEta_vs_MuonPhi);
		efficiencyRatioIsoMB1MuonEta_vs_MuonPhi->Write("efficiencyRatioIsoMB1MuonEta_vs_MuonPhi");

		TH2D *efficiencyRatioIsoMB2MuonEta_vs_MuonPhi = (TH2D*)efficiencyIsoMb2MuonEta_vs_MuonPhi->Clone("efficiencyRatioIsoMB2MuonEta_vs_MuonPhi");
		efficiencyRatioIsoMB2MuonEta_vs_MuonPhi->Divide(efficiencyBmtfMuonEta_vs_MuonPhi);
		efficiencyRatioIsoMB2MuonEta_vs_MuonPhi->Write("efficiencyRatioIsoMB2MuonEta_vs_MuonPhi");

		TH2D *efficiencyRatioIsoMB12MuonEta_vs_MuonPhi = (TH2D*)efficiencyIsoMb12MuonEta_vs_MuonPhi->Clone("efficiencyRatioIsoMB12MuonEta_vs_MuonPhi");
		efficiencyRatioIsoMB12MuonEta_vs_MuonPhi->Divide(efficiencyBmtfMuonEta_vs_MuonPhi);
		efficiencyRatioIsoMB12MuonEta_vs_MuonPhi->Write("efficiencyRatioIsoMB12MuonEta_vs_MuonPhi");

		TH2D *efficiencyTfMuonEta_vs_MuonPhi = (TH2D*)histCollection->histTfMatchedMuonEta_vs_MuonPhi.at(Utility::UGMT)->Clone("efficiencyTfMatchedMuonEta_vs_Phi");
		efficiencyTfMuonEta_vs_MuonPhi->Divide(histCollection->histProbeMuonEta_vs_ProbeMuonPhi);
		efficiencyTfMuonEta_vs_MuonPhi->Write("efficiencyTfMuonEta_vs_MuonPhi");
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
