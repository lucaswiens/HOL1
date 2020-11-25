#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>

BmtfInputProducer::BmtfInputProducer() {
	int nBinsPt = 200, nBinsPhi = 72, nBinsEta = 68, nBinsWheel = 7, nBinsStation = 5, nBinsSection = 12, nBinsQualityCode = 10;
	int maxPt = 1000, maxPhi = M_PI, minEta = -3, minWheel = -3, minStation = 0, minSection = 0, minQualityCode = 0;
	int minPt = 0, minPhi = -M_PI, maxEta = 3, maxWheel = 4, maxStation = 5, maxSection = 12, maxQualityCode = 10;

	histDttpSize = new TH1I("dttpSize", "dttpSize", 15, 0, 15);
	histDttpBx = new TH1I("dttpBx", "dttpBx", 5, -2, 2);
	histDttpWheel = new TH1I("dttpWheel", "dttpWheel", nBinsWheel, minWheel, maxWheel);
	histDttpSection = new TH1I("dttpSection", "dttpSection", nBinsSection, minSection, maxSection);
	histDttpStation = new TH1I("dttpStation", "dttpStation", nBinsStation, minStation, maxStation);
	histDttpQualityCode = new TH1I("dttpQualitytCode", "dttpQualitytCode", nBinsQualityCode, minQualityCode, maxQualityCode);
	histDttpTs2Tag = new TH1I("dttpTs2Tag", "dttpTs2Tag", 2, 0, 2);
	histDttpPhi = new TH1F("dttpPhi", "dttpPhi", 100, -1750, 1750);
	histDttpPhiB = new TH1F("dttpPhiB", "dttpPhiB", 100, -250, 250);
	histDttpCmsPhi = new TH1D("dttpCmsPhi", "dttpCmsPhi", nBinsPhi, minPhi, maxPhi);

	histBmtfThSize = new TH1I("bmtfThSize", "bmtfThSize", 25, 0, 25);
	histBmtfThBx = new TH1I("bmtfThBx", "bmtfThBx", 6, -3, 3);
	histBmtfThWh = new TH1I("bmtfThWh", "bmtfThWh", 6, -3, 3);
	histBmtfThSe = new TH1I("bmtfThSe", "bmtfThSe", 15, 0, 15);
	histBmtfThSt = new TH1I("bmtfThSt", "bmtfThSt", 5, 0, 5);
	histBmtfThTheta = new TH1I("bmtfThTheta", "bmtfThTheta", 100, 8e7, 1e8);
	histBmtfThCode = new TH1I("bmtfThCode", "bmtfThCode", 10, 8e7, 2e8);

	// TODO FIND PROPER HIST BINS
	histNBmtf = new TH1S("nTfMuon", "nTfMuon", 25, 0, 25);
	histBmtfHwPt = new TH1S("tfMuonHwPt", "tfMuonHwPt", 25, 0, 25);
	histBmtfHwEta = new TH1S("tfMuonHwEta", "tfMuonHwEta", 25, 0, 25);
	histBmtfHwPhi = new TH1S("tfMuonHwPhi", "tfMuonHwPhi", 25, 0, 25);
	histBmtfGlobalPhi = new TH1S("tfMuonGlobalPhi", "tfMuonGlobalPhi", 25, 0, 25);
	histBmtfHwSign = new TH1S("tfMuonHwSign", "tfMuonHwSign", 25, 0, 25);
	histBmtfHwSignValid = new TH1S("tfMuonHwSignValid", "tfMuonHwSignValid", 25, 0, 25);
	histBmtfHwQual = new TH1S("tfMuonHwQual", "TfMuonHwQual", 25, 0, 25);
	histBmtfLink = new TH1S("tfMuonLink", "TfMuonLink", 25, 0, 25);
	histBmtfProcessor = new TH1S("tfMuonProcessor", "TfMuonProcessor", 25, 0, 25);
	histBmtfTrackFinderType = new TH1S("tfMuonTrackFinderType", "TfMuonTrackFinderType", 25, 0, 25);
	histBmtfHwHF = new TH1S("tfMuonHwHF", "TfMuonHwHF", 25, 0, 25);
	histBmtfBx = new TH1S("tfMuonBx", "TfMuonBx", 25, 0, 25);
	histBmtfWh = new TH1S("tfMuonWh", "TfMuonWh", 25, 0, 25);
	histBmtfTrAdd = new TH1S("tfMuonTrAdd", "TfMuonTrAdd", 25, 0, 25);
	histBmtfCmsPt = new TH1D("bmtfCmsPt", "bmtfCmsPt", nBinsPt, minPt, maxPt);
	histBmtfCmsEta = new TH1D("bmtfCmsEta", "bmtfCmsEta", nBinsEta, minEta, maxEta);
	histBmtfCmsPhi = new TH1D("bmtfCmsPhi", "bmtfCmsPhi", nBinsPhi, minPhi, maxPhi);

	//histDttpStation_vs_DttpWheel = new TH2D("MB_station_vs_wheel", "MB_station_vs_wheel", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histDttpStation_vs_DttpWheel_Hq = new TH2D("MB_station_vs_wheel_Hq", "MB_station_vs_wheel_Hq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histDttpStation_vs_DttpWheel_Lq = new TH2D("MB_station_vs_wheel_Lq", "MB_station_vs_wheel_Lq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUsedDttpStation_vs_DttpWheel = new TH2D("usedMB_station_vs_wheel", "usedMB_station_vs_wheel", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUsedDttpStation_vs_DttpWheel_Hq = new TH2D("usedMB_station_vs_wheel_Hq", "usedMB_station_vs_wheel_Hq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUsedDttpStation_vs_DttpWheel_Lq = new TH2D("usedMB_station_vs_wheel_Lq", "usedMB_station_vs_wheel_Lq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUnusedDttpStation_vs_DttpWheel = new TH2D("unusedMB_station_vs_wheel", "unusedMB_station_vs_wheel", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUnusedDttpStation_vs_DttpWheel_Hq = new TH2D("unusedMB_station_vs_wheel_Hq", "unusedMB_station_vs_wheel_Hq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
	//histUnusedDttpStation_vs_DttpWheel_Lq = new TH2D("unusedMB_station_vs_wheel_Lq", "unusedMB_station_vs_wheel_Lq", nBinsWheel, minWheel, maxWheel, nBinsStation, minStation, maxStation);
}

void BmtfInputProducer::Produce(DataReader* dataReader, HoProduct* product) {
	const int &dttpSize = *dataReader->bmtfPhSize->Get();
	histDttpSize->Fill(dttpSize);
	product->dttpSize = dttpSize;

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

		histDttpBx->Fill(product->dttpBx.back());
		histDttpWheel->Fill(product->dttpWheel.back());
		histDttpSection->Fill(product->dttpSection.back());
		histDttpStation->Fill(product->dttpStation.back());
		histDttpQualityCode->Fill(product->dttpQualityCode.back());
		histDttpTs2Tag->Fill(product->dttpTs2Tag.back());
		histDttpPhi->Fill(product->dttpPhi.back());
		histDttpPhiB->Fill(product->dttpPhiB.back());
		histDttpCmsPhi->Fill(product->dttpCmsPhi.back());

		//TODO these will not always be filled.. Maybe just construct dttpPt later if needed?
		if (product->dttpStation.back() == 1) {
			product->dttpPt.push_back(Utility::PhiBMb1ToPt.at(product->dttpPhiB.back()) * 0.5);
		} else if (product->dttpStation.back() == 2) {
			product->dttpPt.push_back(Utility::PhiBMb2ToPt.at(product->dttpPhiB.back()) * 0.5);
		} else {
			product->dttpPt.push_back(-999);
		}

		product->dttpIsHq.push_back((3 < product->dttpQualityCode.back()) && (product->dttpQualityCode.back() < 7));
	}

	const int &thSize = *dataReader->bmtfThSize->Get();
	histBmtfThSize->Fill(thSize);
	for (int i = 0; i < thSize; i++) {
		histBmtfThBx->Fill(dataReader->bmtfThBx->At(i));
		histBmtfThWh->Fill(dataReader->bmtfThWh->At(i));
		histBmtfThSe->Fill(dataReader->bmtfThSe->At(i));
		histBmtfThSt->Fill(dataReader->bmtfThSt->At(i));
		histBmtfThTheta->Fill(dataReader->bmtfThTheta->At(i));
		histBmtfThCode->Fill(dataReader->bmtfThCode->At(i));
	}

	//const unsigned short &tfMuon = *dataReader->bmtfThSize->Get(); // This seems buggy..
	const unsigned short &bmtfSize = dataReader->tfMuonHwPt->GetSize();
	histNBmtf->Fill(bmtfSize);
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

		histBmtfHwPt->Fill(product->bmtfPt.back());
		histBmtfHwEta->Fill(product->bmtfEta.back());
		histBmtfHwPhi->Fill(dataReader->tfMuonHwPhi->At(i));
		histBmtfGlobalPhi->Fill(product->bmtfGlobalPhi.back());
		histBmtfHwSign->Fill(dataReader->tfMuonHwSign->At(i));
		histBmtfHwSignValid->Fill(dataReader->tfMuonHwSignValid->At(i));
		histBmtfHwQual->Fill(dataReader->tfMuonHwQual->At(i));
		histBmtfLink->Fill(dataReader->tfMuonLink->At(i));
		histBmtfProcessor->Fill(dataReader->tfMuonProcessor->At(i));
		histBmtfTrackFinderType->Fill(dataReader->tfMuonTrackFinderType->At(i));
		histBmtfHwHF->Fill(dataReader->tfMuonHwHF->At(i));
		histBmtfBx->Fill(product->bmtfBx.back());
		histBmtfWh->Fill(dataReader->tfMuonWh->At(i));
		histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.back().at(0));
		histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.back().at(1));
		histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.back().at(2));
		histBmtfTrAdd->Fill(product->bmtfTrackerAddresses.back().at(3));
		histBmtfCmsPt->Fill(product->bmtfCmsPt.back());
		histBmtfCmsEta->Fill(product->bmtfCmsEta.back());
		histBmtfCmsPhi->Fill(product->bmtfCmsPhi.back());
	}
}

BmtfInputProducer::~BmtfInputProducer() {}
