#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>

BmtfInputProducer::BmtfInputProducer(HoHistogramCollection* histCollection) {}

void BmtfInputProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	Name = "BMTF Producer";
	const int &dttpSize = *dataReader->bmtfPhSize->Get();
	histCollection->histDttpSize->Fill(dttpSize);
	product->dttpSize = dttpSize;

	// The bmtfPh variables are input variables for the bmtf algorithm and here called DTTP, because they are trigger primitves constructed with the drift tube information
	for (int i = 0; i < dttpSize; i++) {
		product->dttpBx.push_back(dataReader->bmtfPhBx->At(i));
		product->dttpWheel.push_back(dataReader->bmtfPhWh->At(i));
		product->dttpSection.push_back(dataReader->bmtfPhSe->At(i));
		product->dttpStation.push_back(dataReader->bmtfPhSt->At(i));
		product->dttpQualityCode.push_back(dataReader->bmtfPhCode->At(i));
		product->dttpTs2Tag.push_back(dataReader->bmtfPhTs2Tag->At(i));
		product->dttpPhi.push_back(dataReader->bmtfPhAng->At(i));
		product->dttpPhiB.push_back(dataReader->bmtfPhBandAng->At(i));

		product->dttpCmsPhi.push_back(Utility::DttpPhiToCmsPhi(product->dttpPhi.back(), product->dttpSection.back()));
		product->dttpIPhi.push_back(Utility::CmsPhiToHoIPhi(product->dttpCmsPhi.back()));

		//product->dttpCmsEta.push_back(Utility::DttpEtaToCmsEta(product->dttpEta.back(), product->dttpSection.back()));

		if (product->dttpStation.back() == 1) {
			product->dttpPt.push_back(Utility::PhiBMb1ToPt.at(product->dttpPhiB.back()) * 0.5);
		} else if (product->dttpStation.back() == 2) {
			product->dttpPt.push_back(Utility::PhiBMb2ToPt.at(product->dttpPhiB.back()) * 0.5);
		} else {
			product->dttpPt.push_back(-999);
		}

		histCollection->histDttpBx->Fill(product->dttpBx.back());
		histCollection->histDttpWheel->Fill(product->dttpWheel.back());
		histCollection->histDttpSection->Fill(product->dttpSection.back());
		histCollection->histDttpStation->Fill(product->dttpStation.back());
		histCollection->histDttpQualityCode->Fill(product->dttpQualityCode.back());
		histCollection->histDttpTs2Tag->Fill(product->dttpTs2Tag.back());
		histCollection->histDttpPhi->Fill(product->dttpPhi.back());
		histCollection->histDttpPhiB->Fill(product->dttpPhiB.back());
		histCollection->histDttpPt->Fill(product->dttpPt.back());
		histCollection->histDttpCmsPhi->Fill(product->dttpCmsPhi.back());
		histCollection->histDttpIPhi->Fill(product->dttpIPhi.back());

		/*
		histCollection->histDttpCmsPhiSection1->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 0);
		histCollection->histDttpCmsPhiSection2->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 1);
		histCollection->histDttpCmsPhiSection3->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 2);
		histCollection->histDttpCmsPhiSection4->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 3);
		histCollection->histDttpCmsPhiSection5->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 4);
		histCollection->histDttpCmsPhiSection6->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 5);
		histCollection->histDttpCmsPhiSection7->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 6);
		histCollection->histDttpCmsPhiSection8->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 7);
		histCollection->histDttpCmsPhiSection9->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 8);
		histCollection->histDttpCmsPhiSection10->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 9);
		histCollection->histDttpCmsPhiSection11->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 10);
		histCollection->histDttpCmsPhiSection12->Fill(product->dttpCmsPhi.back(), product->dttpSection.back() == 11);
		*/


		product->dttpIsLq.push_back((0 < product->dttpQualityCode.back()) && (product->dttpQualityCode.back() < 4));
		product->dttpIsHq.push_back((3 < product->dttpQualityCode.back()) && (product->dttpQualityCode.back() < 7));
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
		product->bmtfBx.push_back(dataReader->tfMuonBx->At(i));
		product->bmtfGlobalPhi.push_back(dataReader->tfMuonGlobalPhi->At(i));
		product->bmtfPt.push_back(dataReader->tfMuonHwPt->At(i));
		product->bmtfEta.push_back(dataReader->tfMuonHwEta->At(i));
		product->bmtfCmsPt.push_back(Utility::BmtfPtToCmsPt(product->bmtfPt.back()));
		product->bmtfCmsEta.push_back(Utility::BmtfEtaToCmsEta(product->bmtfEta.back()));
		product->bmtfCmsPhi.push_back(Utility::BmtfGlobalPhiToCmsPhi(product->bmtfGlobalPhi.back()));
		product->bmtfTrackerAddresses.push_back({
			dataReader->tfMuonTrAdd->At(4 * i + 0),
			dataReader->tfMuonTrAdd->At(4 * i + 1),
			dataReader->tfMuonTrAdd->At(4 * i + 2),
			dataReader->tfMuonTrAdd->At(4 * i + 3)
		});
		product->bmtfTrackType.push_back(Utility::GetBmtfStationMask(product->bmtfTrackerAddresses.back()));

		histCollection->histBmtfHwPt->Fill(product->bmtfPt.back());
		histCollection->histBmtfHwEta->Fill(product->bmtfEta.back());
		histCollection->histBmtfHwPhi->Fill(dataReader->tfMuonHwPhi->At(i));
		histCollection->histBmtfGlobalPhi->Fill(product->bmtfGlobalPhi.back());
		histCollection->histBmtfHwSign->Fill(dataReader->tfMuonHwSign->At(i));
		histCollection->histBmtfHwSignValid->Fill(dataReader->tfMuonHwSignValid->At(i));
		histCollection->histBmtfHwQual->Fill(dataReader->tfMuonHwQual->At(i));
		histCollection->histBmtfLink->Fill(dataReader->tfMuonLink->At(i));
		histCollection->histBmtfProcessor->Fill(dataReader->tfMuonProcessor->At(i));
		histCollection->histBmtfTrackFinderType->Fill(dataReader->tfMuonTrackFinderType->At(i));
		histCollection->histBmtfHwHF->Fill(dataReader->tfMuonHwHF->At(i));
		histCollection->histBmtfBx->Fill(product->bmtfBx.back());
		histCollection->histBmtfWh->Fill(dataReader->tfMuonWh->At(i));
		histCollection->histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.back().at(0));
		histCollection->histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.back().at(1));
		histCollection->histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.back().at(2));
		histCollection->histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.back().at(3));
		histCollection->histBmtfTrAddSt1->Fill(product->bmtfTrackerAddresses.back().at(0));
		histCollection->histBmtfTrAddSt2->Fill(product->bmtfTrackerAddresses.back().at(1));
		histCollection->histBmtfTrAddSt3->Fill(product->bmtfTrackerAddresses.back().at(2));
		histCollection->histBmtfTrAddSt4->Fill(product->bmtfTrackerAddresses.back().at(3));
		histCollection->histBmtfTrackType->Fill(product->bmtfTrackType.back());
		histCollection->histBmtfCmsPt->Fill(product->bmtfCmsPt.back());
		histCollection->histBmtfCmsPt20->Fill(product->bmtfCmsPt.back());
		histCollection->histBmtfCmsEta->Fill(product->bmtfCmsEta.back());
		histCollection->histBmtfCmsPhi->Fill(product->bmtfCmsPhi.back());
	}
	//product->bmtfSize = product->bmtfCmsPt.size();
}

void BmtfInputProducer::EndJob(HoHistogramCollection* histCollection) {}

BmtfInputProducer::~BmtfInputProducer() {}
