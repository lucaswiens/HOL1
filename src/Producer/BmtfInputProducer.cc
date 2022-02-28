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
	for (int i = 0; i < dttpSize; i++) {
		//const double &dttpPhi = product->dttpPhi.at(i)
		const int &dttpStation = dataReader->bmtfPhSt->At(i);
		const float &dttpPhiB = dataReader->bmtfPhBandAng->At(i);
		//const double &dttpCmsPt =

		double dttpCmsPt = -999;
		if (dttpStation == 1) {
			dttpCmsPt = Utility::PhiBMb1ToPt.at(dttpPhiB) * 0.5;
		} else if (dttpStation == 2) {
			dttpCmsPt = Utility::PhiBMb2ToPt.at(dttpPhiB) * 0.5;
		}

		if (fabs(dttpCmsPt) < l1PtCut) { continue;}
		product->dttpCmsPt.push_back(dttpCmsPt);

		product->dttpBx.push_back(dataReader->bmtfPhBx->At(i));
		product->dttpWheel.push_back(dataReader->bmtfPhWh->At(i));
		product->dttpSection.push_back(dataReader->bmtfPhSe->At(i));
		product->dttpStation.push_back(dttpStation);
		product->dttpQualityCode.push_back(dataReader->bmtfPhCode->At(i));
		product->dttpTs2Tag.push_back(dataReader->bmtfPhTs2Tag->At(i));
		product->dttpPhi.push_back(dataReader->bmtfPhAng->At(i));
		product->dttpPhiB.push_back(dttpPhiB);

		product->dttpCmsPhi.push_back(Utility::DttpPhiToCmsPhi(product->dttpPhi.back(), product->dttpSection.back()));
		product->dttpIPhi.push_back(Utility::CmsPhiToHoIPhi(product->dttpCmsPhi.back()));

		//product->dttpCmsEta.push_back(Utility::DttpEtaToCmsEta(product->dttpEta.back(), product->dttpSection.back()));

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
	product->dttpSize = product->dttpCmsPt.size();
	histCollection->histDttpSize->Fill(product->dttpSize);

	// Currently not used by the HOL1 algorithm but so just make histograms
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

	//The track finder Muon is what we call a bmtf muon which is given the bmtf prefix
	bool useTfMuon = true; // For now this is hardcoded switch.. Maybe define in bin/main.cc or take as argument or something to switch between this, that or emu
	if (useTfMuon) {
		product->bmtfSize = *dataReader->nTfMuon->Get();//dataReader->tfMuonHwPt->GetSize();
		for (unsigned short i = 0; i < product->bmtfSize; i++) {
			const short bmtfPt      = dataReader->tfMuonHwPt->At(i);
			const double bmtfCmsPt  = Utility::BmtfPtToCmsPt(bmtfPt);
			const short bmtfEta     = dataReader->tfMuonHwEta->At(i);
			const double bmtfCmsEta = Utility::BmtfEtaToCmsEta(bmtfEta);

			if (bmtfCmsPt < l1PtCut) { continue;}
			histCollection->histBmtfNumber->Fill(0);

			product->bmtfBx.push_back(dataReader->tfMuonBx->At(i));
			product->bmtfPt.push_back(bmtfPt);
			product->bmtfEta.push_back(bmtfEta);
			product->bmtfGlobalPhi.push_back(dataReader->tfMuonGlobalPhi->At(i));
			product->bmtfCmsPt.push_back(bmtfCmsPt);
			product->bmtfCmsEta.push_back(bmtfCmsEta);
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
		product->bmtfSize = product->bmtfPt.size();
		histCollection->histNBmtf->Fill(product->bmtfSize);
	} else {
		product->bmtfSize = *dataReader->nBmtfMuons->Get();//dataReader->tfMuonHwPt->GetSize();
		for (unsigned short i = 0; i < product->bmtfSize; i++) {
			//TF_index = 36 + (int)(L1UpgradeTree.muonTfMuonIdx[iMu] / 3.);
			//where TF_index is:  #EMTF+ : 36-41, OMTF+ : 42-47, BMTF : 48-59, OMTF- : 60-65, EMTF- : 66-71
			const short tfMuonIndex = dataReader->bmtfMuonTfMuonIdx->At(i);
			const bool isBmtf = Utility::BmtfMuonIndexToIsBmtf(tfMuonIndex);

			//std::cout << "tfMuonIndex = " << 36 + (int)(tfMuonIndex / 3) << " is a bmtf:" << isBmtf << std::endl;
			if (!isBmtf) { continue;}

			//const short bmtfPt      = dataReader->bmtfMuonEt->At(i);
			const double bmtfCmsPt  = dataReader->bmtfMuonEt->At(i);
			const short bmtfEta     = dataReader->bmtfMuonIEta->At(i);
			const double bmtfCmsEta = dataReader->bmtfMuonEta->At(i);

			if (bmtfCmsPt < l1PtCut) { continue;}
			histCollection->histBmtfNumber->Fill(0);

			product->bmtfBx.push_back(dataReader->bmtfMuonBx->At(i));
			//product->bmtfPt.push_back(bmtfPt);
			product->bmtfEta.push_back(bmtfEta);
			product->bmtfGlobalPhi.push_back(dataReader->bmtfMuonIPhi->At(i));
			product->bmtfCmsPt.push_back(bmtfCmsPt);
			product->bmtfCmsEta.push_back(bmtfCmsEta);
			product->bmtfCmsPhi.push_back(dataReader->bmtfMuonPhi->At(i));
			/* Adress doesn't exist.. THink about this later

			product->bmtfTrackerAddresses.push_back({
				dataReader->tfMuonTrAdd->At(4 * i + 0),
				dataReader->tfMuonTrAdd->At(4 * i + 1),
				dataReader->tfMuonTrAdd->At(4 * i + 2),
				dataReader->tfMuonTrAdd->At(4 * i + 3)
			});
			product->bmtfTrackType.push_back(Utility::GetBmtfStationMask(product->bmtfTrackerAddresses.back()));

			Fill with 0 for now */
			product->bmtfTrackerAddresses.push_back({0, 0, 0, 0 });
			product->bmtfTrackType.push_back(0);

			//histCollection->histBmtfHwPt->Fill(product->bmtfPt.back());
			histCollection->histBmtfHwEta->Fill(product->bmtfEta.back());
			//histCollection->histBmtfHwPhi->Fill(dataReader->tfMuonHwPhi->At(i));
			histCollection->histBmtfGlobalPhi->Fill(product->bmtfGlobalPhi.back());
			histCollection->histBmtfHwSign->Fill(dataReader->bmtfMuonChg->At(i));
			//histCollection->histBmtfHwSignValid->Fill(dataReader->tfMuonHwSignValid->At(i));
			histCollection->histBmtfHwQual->Fill(dataReader->bmtfMuonQual->At(i));
			//histCollection->histBmtfLink->Fill(dataReader->tfMuonLink->At(i));
			//histCollection->histBmtfProcessor->Fill(dataReader->tfMuonProcessor->At(i));
			//histCollection->histBmtfTrackFinderType->Fill(dataReader->tfMuonTrackFinderType->At(i));
			//histCollection->histBmtfHwHF->Fill(dataReader->tfMuonHwHF->At(i));
			histCollection->histBmtfBx->Fill(product->bmtfBx.back());
			//histCollection->histBmtfWh->Fill(dataReader->tfMuonWh->At(i));
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
		product->bmtfSize = product->bmtfEta.size();
		histCollection->histNBmtf->Fill(product->bmtfSize);
	}

}

void BmtfInputProducer::EndJob(HoHistogramCollection* histCollection) { }

BmtfInputProducer::~BmtfInputProducer() {}
