#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>

BmtfInputProducer::BmtfInputProducer() {
	Name = "BMTF Producer";
}

void BmtfInputProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	const int &dttpSize = *dataReader->bmtfPhSize->Get();
	histCollection->histDttpSize->Fill(dttpSize);
	product->dttpSize = dttpSize;

	// The bmtfPh variables are input variables for the bmtf algorithm and are assigned the DTTP prefix, because they are trigger primitves constructed with the drift tube information
	for (int i = 0; i < dttpSize; i++) {
		product->dttpBx.push_back(dataReader->bmtfPhBx->At(i));
		product->dttpWheel.push_back(dataReader->bmtfPhWh->At(i));
		product->dttpSection.push_back(dataReader->bmtfPhSe->At(i));
		product->dttpStation.push_back(dataReader->bmtfPhSt->At(i));
		product->dttpQualityCode.push_back(dataReader->bmtfPhCode->At(i));
		product->dttpTs2Tag.push_back(dataReader->bmtfPhTs2Tag->At(i));
		product->dttpPhi.push_back(dataReader->bmtfPhAng->At(i));
		product->dttpPhiB.push_back(dataReader->bmtfPhBandAng->At(i));

		product->dttpCmsPhi.push_back(Utility::DttpPhiToCmsPhi(product->dttpPhi.at(i), product->dttpSection.at(i)));
		product->dttpIPhi.push_back(Utility::CmsPhiToHoIPhi(product->dttpCmsPhi.at(i)));

		//product->dttpCmsEta.push_back(Utility::DttpEtaToCmsEta(product->dttpEta.at(i), product->dttpSection.at(i)));

		if (product->dttpStation.at(i) == 1) {
			product->dttpPt.push_back(Utility::PhiBMb1ToPt.at(product->dttpPhiB.at(i)) * 0.5);
		} else if (product->dttpStation.at(i) == 2) {
			product->dttpPt.push_back(Utility::PhiBMb2ToPt.at(product->dttpPhiB.at(i)) * 0.5);
		} else {
			product->dttpPt.push_back(-999);
		}

		histCollection->histDttpBx->Fill(product->dttpBx.at(i));
		histCollection->histDttpWheel->Fill(product->dttpWheel.at(i));
		histCollection->histDttpSection->Fill(product->dttpSection.at(i));
		histCollection->histDttpStation->Fill(product->dttpStation.at(i));
		histCollection->histDttpQualityCode->Fill(product->dttpQualityCode.at(i));
		histCollection->histDttpTs2Tag->Fill(product->dttpTs2Tag.at(i));
		histCollection->histDttpPhi->Fill(product->dttpPhi.at(i));
		histCollection->histDttpPhiB->Fill(product->dttpPhiB.at(i));
		histCollection->histDttpPt->Fill(product->dttpPt.at(i));
		histCollection->histDttpCmsPhi->Fill(product->dttpCmsPhi.at(i));
		histCollection->histDttpIPhi->Fill(product->dttpIPhi.at(i));

		/*
		histCollection->histDttpCmsPhiSection1->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 0);
		histCollection->histDttpCmsPhiSection2->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 1);
		histCollection->histDttpCmsPhiSection3->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 2);
		histCollection->histDttpCmsPhiSection4->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 3);
		histCollection->histDttpCmsPhiSection5->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 4);
		histCollection->histDttpCmsPhiSection6->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 5);
		histCollection->histDttpCmsPhiSection7->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 6);
		histCollection->histDttpCmsPhiSection8->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 7);
		histCollection->histDttpCmsPhiSection9->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 8);
		histCollection->histDttpCmsPhiSection10->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 9);
		histCollection->histDttpCmsPhiSection11->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 10);
		histCollection->histDttpCmsPhiSection12->Fill(product->dttpCmsPhi.at(i), product->dttpSection.at(i) == 11);
		*/


		product->dttpIsLq.push_back((0 < product->dttpQualityCode.at(i)) && (product->dttpQualityCode.at(i) < 4));
		product->dttpIsHq.push_back((3 < product->dttpQualityCode.at(i)) && (product->dttpQualityCode.at(i) < 7));
	}

	const int &thSize = *dataReader->bmtfThSize->Get();
	histCollection->histBmtfThSize->Fill(thSize);
	for (int i = 0; i < thSize; i++) {
		histCollection->histBmtfThBx->Fill(dataReader->bmtfThBx->At(i));
		histCollection->histBmtfThWh->Fill(dataReader->bmtfThWh->At(i));
		histCollection->histBmtfThSe->Fill(dataReader->bmtfThSe->At(i));
		histCollection->histBmtfThSt->Fill(dataReader->bmtfThSt->At(i));
		histCollection->histBmtfThTheta->Fill(dataReader->bmtfThTheta->At(i));
		histCollection->histBmtfThCode->Fill(dataReader->bmtfThCode->At(i));
	}

	//const unsigned short &tfMuon = *dataReader->bmtfThSize->Get(); // This seems buggy..
	//The track finder Muon is what we call a bmtf muon which is given the bmtf prefix
	const unsigned short &bmtfSize = dataReader->tfMuonHwPt->GetSize();
	histCollection->histNBmtf->Fill(bmtfSize);
	product->bmtfSize = bmtfSize;
	for (unsigned short i = 0; i < bmtfSize; i++) {
		const short bmtfPt = dataReader->tfMuonHwPt->At(i);
		const short bmtfEta = dataReader->tfMuonHwEta->At(i);

		const double bmtfCmsPt = Utility::BmtfPtToCmsPt(bmtfPt);
		const double bmtfCmsEta = Utility::BmtfEtaToCmsEta(bmtfEta);

		product->bmtfBx.push_back(dataReader->tfMuonBx->At(i));
		product->bmtfPt.push_back(bmtfPt);
		product->bmtfEta.push_back(bmtfEta);
		product->bmtfGlobalPhi.push_back(dataReader->tfMuonGlobalPhi->At(i));
		product->bmtfCmsPt.push_back(bmtfCmsPt);
		product->bmtfCmsEta.push_back(bmtfCmsEta);
		product->bmtfCmsPhi.push_back(Utility::BmtfGlobalPhiToCmsPhi(product->bmtfGlobalPhi.at(i)));
		product->bmtfTrackerAddresses.push_back({
			dataReader->tfMuonTrAdd->At(4 * i + 0),
			dataReader->tfMuonTrAdd->At(4 * i + 1),
			dataReader->tfMuonTrAdd->At(4 * i + 2),
			dataReader->tfMuonTrAdd->At(4 * i + 3)
		});
		product->bmtfTrackType.push_back(Utility::GetBmtfStationMask(product->bmtfTrackerAddresses.at(i)));

		histCollection->histBmtfHwPt->Fill(product->bmtfPt.at(i));
		histCollection->histBmtfHwEta->Fill(product->bmtfEta.at(i));
		histCollection->histBmtfHwPhi->Fill(dataReader->tfMuonHwPhi->At(i));
		histCollection->histBmtfGlobalPhi->Fill(product->bmtfGlobalPhi.at(i));
		histCollection->histBmtfHwSign->Fill(dataReader->tfMuonHwSign->At(i));
		histCollection->histBmtfHwSignValid->Fill(dataReader->tfMuonHwSignValid->At(i));
		histCollection->histBmtfHwQual->Fill(dataReader->tfMuonHwQual->At(i));
		histCollection->histBmtfLink->Fill(dataReader->tfMuonLink->At(i));
		histCollection->histBmtfProcessor->Fill(dataReader->tfMuonProcessor->At(i));
		histCollection->histBmtfTrackFinderType->Fill(dataReader->tfMuonTrackFinderType->At(i));
		histCollection->histBmtfHwHF->Fill(dataReader->tfMuonHwHF->At(i));
		histCollection->histBmtfBx->Fill(product->bmtfBx.at(i));
		histCollection->histBmtfWh->Fill(dataReader->tfMuonWh->At(i));
		histCollection->histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.at(i).at(0));
		histCollection->histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.at(i).at(1));
		histCollection->histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.at(i).at(2));
		histCollection->histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.at(i).at(3));
		histCollection->histBmtfTrAddSt1->Fill(product->bmtfTrackerAddresses.at(i).at(0));
		histCollection->histBmtfTrAddSt2->Fill(product->bmtfTrackerAddresses.at(i).at(1));
		histCollection->histBmtfTrAddSt3->Fill(product->bmtfTrackerAddresses.at(i).at(2));
		histCollection->histBmtfTrAddSt4->Fill(product->bmtfTrackerAddresses.at(i).at(3));
		histCollection->histBmtfTrackType->Fill(product->bmtfTrackType.at(i));
		histCollection->histBmtfCmsPt->Fill(product->bmtfCmsPt.at(i));
		histCollection->histBmtfCmsPt20->Fill(product->bmtfCmsPt.at(i));
		histCollection->histBmtfCmsEta->Fill(product->bmtfCmsEta.at(i));
		histCollection->histBmtfCmsPhi->Fill(product->bmtfCmsPhi.at(i));
	}
	//product->bmtfSize = product->bmtfCmsPt.size();
}

void BmtfInputProducer::EndJob(HoHistogramCollection* histCollection) {}

BmtfInputProducer::~BmtfInputProducer() {}
