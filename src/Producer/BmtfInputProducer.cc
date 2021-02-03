#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>

BmtfInputProducer::BmtfInputProducer(HoHistogramCollection* histCollection) {
	double maxPt = 20, maxPhi = M_PI, minEta = -3, minWheel = -3, minStation = 1, minSection = 0, minQualityCode = 0;
	double minPt = 0, minPhi = -M_PI, maxEta = 3, maxWheel = 4, maxStation = 5, maxSection = 12, maxQualityCode = 10;
	int nBinsPt = (maxPt - minPt), nBinsPhi = 256, nBinsEta = 68, nBinsWheel = 7, nBinsStation = 4, nBinsSection = 12, nBinsQualityCode = 10;

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

	histCollection->histBmtfThSize = new TH1I("bmtfThSize", "bmtfThSize", 25, 0, 25);
	histCollection->histBmtfThBx = new TH1I("bmtfThBx", "bmtfThBx", 6, -3, 3);
	histCollection->histBmtfThWh = new TH1I("bmtfThWh", "bmtfThWh", 6, -3, 3);
	histCollection->histBmtfThSe = new TH1I("bmtfThSe", "bmtfThSe", 15, 0, 15);
	histCollection->histBmtfThSt = new TH1I("bmtfThSt", "bmtfThSt", 5, 0, 5);
	histCollection->histBmtfThTheta = new TH1I("bmtfThTheta", "bmtfThTheta", 100, 8e7, 1e8);
	histCollection->histBmtfThCode = new TH1I("bmtfThCode", "bmtfThCode", 10, 8e7, 2e8);
}

void BmtfInputProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
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
		histCollection->histBmtfCmsEta->Fill(product->bmtfCmsEta.back());
		histCollection->histBmtfCmsPhi->Fill(product->bmtfCmsPhi.back());
	}
}

void BmtfInputProducer::EndJob(HoHistogramCollection* histCollection) {}

BmtfInputProducer::~BmtfInputProducer() {}
