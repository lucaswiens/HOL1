#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>

//BmtfInputProducer::BmtfInputProducer() {}
BmtfInputProducer::BmtfInputProducer(double l1EtaCut, double l1PtCut):
	l1EtaCut(l1EtaCut),
	l1PtCut(l1PtCut) {
	Name = "BMTF Producer";
}

void BmtfInputProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	int dttpSize = *dataReader->bmtfPhSize->Get();

	// The bmtfPh variables are input variables for the bmtf algorithm and are assigned the DTTP prefix, because they are trigger primitves constructed with the drift tube information
	for (int iDttp = 0; iDttp < dttpSize; iDttp++) {
		const int &dttpStation = dataReader->bmtfPhSt->At(iDttp);
		const float &dttpPhiB = dataReader->bmtfPhBandAng->At(iDttp);

		double dttpCmsPt = -999;
		if (dttpStation == 1) {
			dttpCmsPt = Utility::PhiBMb1ToPt.at(dttpPhiB) * 0.5;
		} else if (dttpStation == 2) {
			dttpCmsPt = Utility::PhiBMb2ToPt.at(dttpPhiB) * 0.5;
		}

		if (fabs(dttpCmsPt) < l1PtCut) { continue;}
		product->dttpCmsPt.push_back(dttpCmsPt);

		product->dttpBx.push_back(dataReader->bmtfPhBx->At(iDttp));
		product->dttpWheel.push_back(dataReader->bmtfPhWh->At(iDttp));
		product->dttpSection.push_back(dataReader->bmtfPhSe->At(iDttp));
		product->dttpStation.push_back(dttpStation);
		product->dttpQualityCode.push_back(dataReader->bmtfPhCode->At(iDttp));
		product->dttpTs2Tag.push_back(dataReader->bmtfPhTs2Tag->At(iDttp));
		product->dttpPhi.push_back(dataReader->bmtfPhAng->At(iDttp));
		product->dttpPhiB.push_back(dttpPhiB);

		product->dttpCmsPhi.push_back(Utility::DttpPhiToCmsPhi(product->dttpPhi.back(), product->dttpSection.back()));
		product->dttpIPhi.push_back(Utility::CmsPhiToHoIPhi(product->dttpCmsPhi.back()));

		histCollection->histDttpBx->Fill(product->dttpBx.back());
		histCollection->histDttpWheel->Fill(product->dttpWheel.back());
		histCollection->histDttpSection->Fill(product->dttpSection.back());
		histCollection->histDttpStation->Fill(product->dttpStation.back());
		histCollection->histDttpQualityCode->Fill(product->dttpQualityCode.back());
		histCollection->histDttpTs2Tag->Fill(product->dttpTs2Tag.back());
		histCollection->histDttpPhi->Fill(product->dttpPhi.back());
		histCollection->histDttpPhiB->Fill(product->dttpPhiB.back());
		histCollection->histDttpCmsPt->Fill(product->dttpCmsPt.back());
		histCollection->histDttpCmsPhi->Fill(product->dttpCmsPhi.back());
		histCollection->histDttpIPhi->Fill(product->dttpIPhi.back());

		product->dttpIsLq.push_back((0 < product->dttpQualityCode.back()) && (product->dttpQualityCode.back() < 4));
		product->dttpIsHq.push_back((3 < product->dttpQualityCode.back()) && (product->dttpQualityCode.back() < 7));
	}
	product->dttpSize = product->dttpCmsPt.size();
	histCollection->histDttpSize->Fill(product->dttpSize);

	product->nUGMTMuons = *dataReader->nUGMTMuons->Get();
	for (unsigned short iUGMT = 0; iUGMT < product->nUGMTMuons; iUGMT++) {
		const short &uGMTTfMuonIndex = dataReader->uGMTTfMuonIdx->At(iUGMT);
		const int &tfType = Utility::TfMuonIndexToTfType(uGMTTfMuonIndex);

		const double &uGMTCmsPt  = dataReader->uGMTEt->At(iUGMT);
		const short &uGMTEta     = dataReader->uGMTIEta->At(iUGMT);
		const double &uGMTCmsEta = dataReader->uGMTEta->At(iUGMT);
		const double &uGMTCmsPhi = dataReader->uGMTPhi->At(iUGMT);

		if (uGMTCmsPt < l1PtCut) { continue;}
		//histCollection->histBmtfNumber->Fill(tfType); //this should probably be put in its own hist or something

		//histCollection->histtfMuonRateVsPhi->Fill(uGMTCmsPhi);

		if (tfType == Utility::Bmtf) {
			histCollection->histBmtfMuonRateVsPhi->Fill(uGMTCmsPhi);
		} else if (tfType == Utility::Omtf) {
			histCollection->histOmtfMuonRateVsPhi->Fill(uGMTCmsPhi);
		} else if (tfType == Utility::Emtf) {
			histCollection->histEmtfMuonRateVsPhi->Fill(uGMTCmsPhi);;
		}

		product->uGMTMuonBx.push_back(dataReader->uGMTBx->At(iUGMT));
		product->uGMTMuonPt.push_back(dataReader->uGMTIEt->At(iUGMT));
		product->uGMTMuonEta.push_back(uGMTEta);
		product->uGMTMuonGlobalPhi.push_back(dataReader->uGMTIPhi->At(iUGMT));
		product->uGMTMuonCmsPt.push_back(uGMTCmsPt);
		product->uGMTMuonCmsEta.push_back(uGMTCmsEta);
		product->uGMTMuonCmsPhi.push_back(uGMTCmsPhi);
		product->uGMTMuonQuality.push_back(dataReader->uGMTQual->At(iUGMT));
	}
	product->nUGMTMuons = product->uGMTMuonCmsPt.size();

	//The track finder Muon is what we call a bmtf muon which is given the bmtf prefix
	product->tfMuonSize.at(Utility::Bmtf) = *dataReader->nTfMuons.at(Utility::Bmtf)->Get();
	product->tfMuonSize.at(Utility::Omtf) = *dataReader->nTfMuons.at(Utility::Omtf)->Get();
	product->tfMuonSize.at(Utility::Emtf) = *dataReader->nTfMuons.at(Utility::Emtf)->Get();
	for (int tfType : {Utility::Bmtf, Utility::Omtf, Utility::Emtf}) {
		for (unsigned short iTf = 0; iTf < product->tfMuonSize.at(tfType); iTf++) {
			const short tfMuonPt      = dataReader->tfMuonHwPt.at(tfType)->At(iTf);
			const double tfMuonCmsPt  = Utility::BmtfPtToCmsPt(tfMuonPt);
			const short tfMuonEta     = dataReader->tfMuonHwEta.at(tfType)->At(iTf);
			const double tfMuonCmsEta = Utility::BmtfEtaToCmsEta(tfMuonEta);
			const int tfMuonHwQual    = dataReader->tfMuonHwQual.at(tfType)->At(iTf);

			if (tfMuonCmsPt < l1PtCut) { continue;}
			const int &tfMuonBx = dataReader->tfMuonBx.at(tfType)->At(iTf);
			if (tfMuonBx != 0) { continue;}

			bool uGMTMatch = false;
			for (unsigned short iUGMT = 0; iUGMT < product->nUGMTMuons; iUGMT++) {
				if (tfMuonBx == product->uGMTMuonBx.at(iUGMT) &&
					tfMuonEta == product->uGMTMuonEta.at(iUGMT) &&
					tfMuonPt == product->uGMTMuonPt.at(iUGMT)
				) { uGMTMatch = true;}
			}
			if (!uGMTMatch) {
				continue;
			}

			product->tfMuonBx.at(tfType).push_back(tfMuonBx);
			product->tfMuonPt.at(tfType).push_back(tfMuonPt);
			product->tfMuonEta.at(tfType).push_back(tfMuonEta);
			product->tfMuonGlobalPhi.at(tfType).push_back(dataReader->tfMuonGlobalPhi.at(tfType)->At(iTf));
			product->tfMuonCmsPt.at(tfType).push_back(tfMuonCmsPt);
			product->tfMuonCmsEta.at(tfType).push_back(tfMuonCmsEta);
			product->tfMuonCmsPhi.at(tfType).push_back(Utility::BmtfGlobalPhiToCmsPhi(product->tfMuonGlobalPhi.at(tfType).back()));
			product->tfMuonQuality.at(tfType).push_back(tfMuonHwQual);

			if (tfType == Utility::Bmtf) {
				histCollection->histBmtfNumber->Fill(0);
				//Somehow this is only filled properly for the bmtf.. But it is also only needed for it, so that should be ok
				product->tfMuonTrackerAddresses.at(tfType).push_back({
					dataReader->tfMuonTrAdd.at(tfType)->At(4 * iTf + 0),
					dataReader->tfMuonTrAdd.at(tfType)->At(4 * iTf + 1),
					dataReader->tfMuonTrAdd.at(tfType)->At(4 * iTf + 2),
					dataReader->tfMuonTrAdd.at(tfType)->At(4 * iTf + 3)
				});
				product->tfMuonTrackType.at(tfType).push_back(Utility::GetBmtfStationMask(product->tfMuonTrackerAddresses.at(tfType).back()));

				histCollection->histBmtfHwPt->Fill(product->tfMuonPt.at(tfType).back());
				histCollection->histBmtfHwEta->Fill(product->tfMuonEta.at(tfType).back());
				histCollection->histBmtfHwPhi->Fill(dataReader->tfMuonHwPhi.at(tfType)->At(iTf));
				histCollection->histBmtfGlobalPhi->Fill(product->tfMuonGlobalPhi.at(tfType).back());
				histCollection->histBmtfHwSign->Fill(dataReader->tfMuonHwSign.at(tfType)->At(iTf));
				histCollection->histBmtfHwSignValid->Fill(dataReader->tfMuonHwSignValid.at(tfType)->At(iTf));
				histCollection->histBmtfHwQual->Fill(tfMuonHwQual);
				histCollection->histBmtfLink->Fill(dataReader->tfMuonLink.at(tfType)->At(iTf));
				histCollection->histBmtfProcessor->Fill(dataReader->tfMuonProcessor.at(tfType)->At(iTf));
				histCollection->histBmtfTrackFinderType->Fill(dataReader->tfMuonTrackFinderType.at(tfType)->At(iTf));
				histCollection->histBmtfHwHF->Fill(dataReader->tfMuonHwHF.at(tfType)->At(iTf));
				histCollection->histBmtfBx->Fill(product->tfMuonBx.at(tfType).back());
				histCollection->histBmtfWh->Fill(dataReader->tfMuonWh.at(tfType)->At(iTf));
				histCollection->histBmtfTrAdd->Fill(product->tfMuonTrackerAddresses.at(tfType).back().at(0));
				histCollection->histBmtfTrAdd->Fill(product->tfMuonTrackerAddresses.at(tfType).back().at(1));
				histCollection->histBmtfTrAdd->Fill(product->tfMuonTrackerAddresses.at(tfType).back().at(2));
				histCollection->histBmtfTrAdd->Fill(product->tfMuonTrackerAddresses.at(tfType).back().at(3));
				histCollection->histBmtfTrAddSt1->Fill(product->tfMuonTrackerAddresses.at(tfType).back().at(0));
				histCollection->histBmtfTrAddSt2->Fill(product->tfMuonTrackerAddresses.at(tfType).back().at(1));
				histCollection->histBmtfTrAddSt3->Fill(product->tfMuonTrackerAddresses.at(tfType).back().at(2));
				histCollection->histBmtfTrAddSt4->Fill(product->tfMuonTrackerAddresses.at(tfType).back().at(3));
				histCollection->histBmtfTrackType->Fill(product->tfMuonTrackType.at(tfType).back());
				histCollection->histBmtfCmsPt->Fill(product->tfMuonCmsPt.at(tfType).back());
				histCollection->histBmtfCmsPtFineBinning->Fill(product->tfMuonCmsPt.at(tfType).back());
				histCollection->histBmtfCmsEta->Fill(product->tfMuonCmsEta.at(tfType).back());
				histCollection->histBmtfCmsPhi->Fill(product->tfMuonCmsPhi.at(tfType).back());
			}
		}
	}

	product->tfMuonSize.at(Utility::Bmtf) = product->tfMuonPt.at(Utility::Bmtf).size();
	product->tfMuonSize.at(Utility::Omtf) = product->tfMuonPt.at(Utility::Omtf).size();
	product->tfMuonSize.at(Utility::Emtf) = product->tfMuonPt.at(Utility::Emtf).size();
	histCollection->histNBmtf->Fill(product->tfMuonSize.at(Utility::Bmtf));
}

void BmtfInputProducer::EndJob(HoHistogramCollection* histCollection) { }

BmtfInputProducer::~BmtfInputProducer() {}
