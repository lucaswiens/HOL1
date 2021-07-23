#include <HOAnalysis/HOL1/interface/Producer/HoCoincidenceProducer.h>

HoCoincidenceProducer::HoCoincidenceProducer() {}
HoCoincidenceProducer::~HoCoincidenceProducer() {}

/*
	Explanation of the names, since it gets confusing
	bmtf prefix -> Track Finder Muon (tfMuon) variables
	dttp prefix -> The BMTF input variables, this is the TwinMux output
	muon prefix -> Reco level muons
	xMatchedY   -> y type variables matched to x
*/

void HoCoincidenceProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	Name = "HO Coincidence Producer";

	if (product->bmtfSize != 0) {
		// Match BMTF with DTTP
		product->isBmtfMatchedDttp = std::vector(product->bmtfSize, false);
		product->isBmtfMb34HoMatched = std::vector(product->bmtfSize, false);
		product->isMb3HoIEtaMatched = std::vector(product->bmtfSize, false);
		product->isMb4HoIEtaMatched = std::vector(product->bmtfSize, false);

		//Indices for better matching
		product->bmtfMatchedDttpIndex = std::vector(product->bmtfSize, -999);

		// Bmtf Matched Dttp
		product->bmtfMatchedDttpDeltaPhi = std::vector(product->bmtfSize, -999.);
		product->bmtfMatchedDttpPt = std::vector(product->bmtfSize, -999.);
		product->bmtfMatchedDttpPhi = std::vector(product->bmtfSize, -9999.); // dttpPhi range is [-2048, 2048]
		product->bmtfMatchedDttpCmsPhi = std::vector(product->bmtfSize, -999.);

		product->bmtfMatchedDttpDeltaPhiPerStation = std::vector<std::vector<double>>(product->bmtfSize, {-999., -999., -999., -999.});
		product->bmtfMatchedDttpIndexPerStation = std::vector<std::vector<int>>(product->bmtfSize, {-999, -999, -999, -999});

		// Bmtf MB34 matched Ho
		product->bmtfMb34MatchedHoDeltaR = std::vector(product->bmtfSize, -999.);
		product->bmtfMb34MatchedHoPt = std::vector(product->bmtfSize, -999.);
		product->bmtfMb34MatchedHoCmsEta = std::vector(product->bmtfSize, -999.);
		product->bmtfMb34MatchedHoCmsPhi = std::vector(product->bmtfSize, -999.);
		product->bmtfMb34MatchedHoDeltaPhi = std::vector(product->bmtfSize, -999.);
		product->bmtfMb34MatchedHoIEta = std::vector(product->bmtfSize, -999);
		product->bmtfMb34MatchedHoIPhi = std::vector(product->bmtfSize, -999);
		product->bmtfMb34MatchedHoDeltaIPhi = std::vector(product->bmtfSize, -999);
		product->bmtfMb3MatchedHoDeltaPhi = std::vector(product->bmtfSize, -999.);
		product->bmtfMb3MatchedHoDeltaIPhi = std::vector(product->bmtfSize, -999);
		product->bmtfMb3MatchedHoIPhi = std::vector(product->bmtfSize, -999);
		product->bmtfMb4MatchedHoDeltaPhi = std::vector(product->bmtfSize, -999.);
		product->bmtfMb4MatchedHoDeltaIPhi = std::vector(product->bmtfSize, -999);
		product->bmtfMb4MatchedHoIPhi = std::vector(product->bmtfSize, -999);
	}

	if (product->dttpSize != 0) {
		// Match BMTF with DTTP
		product->isDttpMatchedBmtf = std::vector(product->dttpSize, false);
		product->isDttpMatchedHo = std::vector(product->dttpSize, false);

		//Indices for better matching
		product->dttpMatchedBmtfIndex = std::vector(product->dttpSize, (unsigned short)999);

		// Dttp matched HO
		product->dttpMatchedHoDeltaIPhi = std::vector(product->dttpSize, -999);
		product->dttpMatchedHoDeltaPhi = std::vector(product->dttpSize, -999.);
		product->dttpMatchedHoIPhi = std::vector(product->dttpSize, -999);
		product->dttpMatchedHoIEta = std::vector(product->dttpSize, -999);
		product->dttpMatchedHoCmsPhi = std::vector(product->dttpSize, -999.);
		product->dttpMatchedHoCmsEta = std::vector(product->dttpSize, -999.);
	}

	if (product->hcalIEta.size()) {
		//Indices for better matching
		product->bmtfMb34MatchedHoIndex = std::vector(product->hcalIEta.size(), (unsigned int)999);
		product->bmtfMb3MatchedHoIndex = std::vector(product->hcalIEta.size(), (unsigned int)999);
		product->bmtfMb4MatchedHoIndex = std::vector(product->hcalIEta.size(), (unsigned int)999);
		product->dttpMatchedHoIndex = std::vector(product->hcalIEta.size(), (unsigned int)999);
	}


	if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
		// Match BMTF with DTTP
		product->isBmtfMatchedMuon = std::vector(product->bmtfSize, false);
		product->isDttpMatchedMuon = std::vector(product->dttpSize, false);
		product->isMuonMatchedBmtf = std::vector(product->nMuon, false);
		product->isMuonMatchedDttp = std::vector(product->nMuon, false);

		//Indices for better matching
		product->bmtfMatchedMuonIndex = std::vector(product->bmtfSize, (unsigned short)999);
		product->dttpMatchedMuonIndex = std::vector(product->dttpSize, (unsigned short)999);
		product->muonMatchedBmtfIndex = std::vector(product->nMuon, (unsigned short)999);
		product->muonMatchedDttpIndex = std::vector(product->nMuon, -999);

		// Bmtf matched Muon
		product->muonMatchedBmtfCmsPt = std::vector(product->nMuon, -999.);
		product->muonMatchedBmtfCmsEta = std::vector(product->nMuon, -999.);

		// Bmtf Matched Dttp
		product->bmtfMatchedMuonDeltaR = std::vector(product->bmtfSize, -999.);
		product->bmtfMatchedMuonPt = std::vector(product->bmtfSize, -999.);
		product->bmtfMatchedMuonEta = std::vector(product->bmtfSize, -999.);
		product->bmtfMatchedMuonPhi = std::vector(product->bmtfSize, -999.);
		product->bmtfMatchedMuonCharge = std::vector(product->bmtfSize, -999);
		product->bmtfMatchedMuonDeltaPhi = std::vector(product->bmtfSize, -999.);

		// Bmtf MB34 matched Ho
		product->bmtfMb34MatchedMuonPt = std::vector(product->bmtfSize, -999.);
		product->bmtfMb34MatchedMuonEta = std::vector(product->bmtfSize, -999.);
		product->bmtfMb34MatchedMuonPhi = std::vector(product->bmtfSize, -999.);
		product->bmtfMb34MatchedMuonDeltaPhi = std::vector(product->bmtfSize, -999.);

		// Dttp Matched Muon
		product->dttpMatchedMuonDeltaR = std::vector(product->dttpSize, -999.);
		product->muonMatchedDttpNHo3x3Hit = std::vector(product->nMuon, -999);
	}

	for (unsigned short iBmtf = 0; iBmtf < product->bmtfSize; iBmtf++){
		if (product->bmtfBx.at(iBmtf) != 0) { continue;}

		int bmtfMatchedDttpIndex = -999, bmtfStation = -999;
		for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) {
			if (product->dttpBx.at(iDttp) != 0) { continue;}

			for (int iBmtfStation = 0; iBmtfStation <= 3; iBmtfStation++) {
				if(std::find(product->bmtfMatchedDttpIndexPerStation.at(iBmtf).begin(), product->bmtfMatchedDttpIndexPerStation.at(iBmtf).end(), iDttp) != product->bmtfMatchedDttpIndexPerStation.at(iBmtf).end()) { continue;}
				//if(std::find(product->bmtfMatchedDttpIndex.begin(), product->bmtfMatchedDttpIndex.end(), iDttp) != product->bmtfMatchedDttpIndex.end()) { continue;}
				// Skip if already associated to a BMTF
				//if (product->isDttpMatchedBmtf.at(iDttp)) { continue;}
				// For Mb1, TrackAddress it should not be 3, but for MB2, MB3 and MB4 it should not be 15
				if (iBmtfStation == 0) {
					if (product->bmtfTrackerAddresses.at(iBmtf).at(iBmtfStation) == 3) { continue;}
				} else {
					if (product->bmtfTrackerAddresses.at(iBmtf).at(iBmtfStation) == 15) { continue;}
				}

				if (product->dttpStation.at(iDttp) != iBmtfStation + 1) { continue;} // Select the correct station
				//if (dttpStation.at(iDttp) == 1 && abs(product->dttpWheel.at(iDttp)) == 2) { continue;} // Exclude wheels +-2
				if (abs(product->dttpWheel.at(iDttp)) == 2) { continue;} // Exclude wheels +-2

				double bmtfMatchedDttpDeltaPhi = Utility::DeltaPhi(product->bmtfCmsPhi.at(iBmtf), product->dttpCmsPhi.at(iDttp));
				if (fabs(bmtfMatchedDttpDeltaPhi) < fabs(product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(iBmtfStation))) {
					product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(iBmtfStation) = bmtfMatchedDttpDeltaPhi;
					bmtfStation = iBmtfStation;

					product->bmtfMatchedDttpDeltaPhi.at(iBmtf) = bmtfMatchedDttpDeltaPhi;
					product->bmtfMatchedDttpPt.at(iBmtf) = product->dttpPt.at(iDttp);
					product->bmtfMatchedDttpPhi.at(iBmtf) = product->dttpPhi.at(iDttp);
					product->bmtfMatchedDttpCmsPhi.at(iBmtf) = product->dttpCmsPhi.at(iDttp);
					product->isBmtfMatchedDttp.at(iBmtf) = true;
					bmtfMatchedDttpIndex = iDttp;
				}
			}
		}

		if (product->isBmtfMatchedDttp.at(iBmtf)) {
			product->bmtfMatchedDttpIndex.at(iBmtf) = bmtfMatchedDttpIndex;
			product->dttpMatchedBmtfIndex.at(bmtfMatchedDttpIndex) = iBmtf;
			product->isDttpMatchedBmtf.at(bmtfMatchedDttpIndex) = true;
			product->bmtfMatchedDttpIndexPerStation.at(iBmtf).at(bmtfStation) = bmtfMatchedDttpIndex;
		}

		if (product->bmtfCmsPt.at(iBmtf) < 0 || fabs(product->bmtfCmsEta.at(iBmtf)) > 0.83) { continue;}

		unsigned short bmtfMatchedMuonIndex = 999;
		bool isBmtfMatchedMuon = false;
		if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
			for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++){
				if(std::find(product->bmtfMatchedMuonIndex.begin(), product->bmtfMatchedMuonIndex.end(), iMuon) != product->bmtfMatchedMuonIndex.end()) { continue;}
				//if (product->isMuonMatchedBmtf.at(iMuon)){ continue;}
				if (!product->isMediumMuon.at(iMuon) ||
					!product->muonHasMb1.at(iMuon) ||
					product->muonIEta.at(iMuon) > 10
				) { continue;}

				//TODO are these needed?
				//double mb1MatchedMuonDeltaEta = product->muonEta .at(iMuon) - product->muonEtaSt1.at(iMuon);
				//double mb1MatchedMuonDeltaPhi = Utility::DeltaPhi(product->muonPhi.at(iMuon), product->muonPhiSt1.at(iMuon));

				const double &bmtfMatchedMuonDeltaPhi = Utility::DeltaPhi(product->bmtfCmsPhi.at(iBmtf), product->muonPhi.at(iMuon));
				const double &bmtfMatchedMuonDeltaR = Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), product->muonEta.at(iMuon), product->muonPhi.at(iMuon));

				if (bmtfMatchedMuonDeltaR < fabs(product->bmtfMatchedMuonDeltaR.at(iBmtf))) {
					bool isBmtfMatchedMuon = bmtfMatchedMuonDeltaR < 0.4;
					if (isBmtfMatchedMuon) {
						product->isMuonMatchedBmtf.at(iMuon) = isBmtfMatchedMuon;
						product->isBmtfMatchedMuon.at(iBmtf) = isBmtfMatchedMuon;
						product->bmtfMatchedMuonDeltaR.at(iBmtf) = bmtfMatchedMuonDeltaR;
						product->bmtfMatchedMuonDeltaPhi.at(iBmtf) = bmtfMatchedMuonDeltaPhi;
						product->bmtfMatchedMuonPt.at(iBmtf) = product->muonPt.at(iMuon);
						product->bmtfMatchedMuonEta.at(iBmtf) = product->muonEta.at(iMuon);
						product->bmtfMatchedMuonPhi.at(iBmtf) = product->muonPhi.at(iMuon);
						product->bmtfMatchedMuonCharge.at(iBmtf) = product->muonCharge.at(iMuon);
						product->bmtfMatchedMuonDeltaPhi.at(iBmtf) = bmtfMatchedMuonDeltaPhi;
						bmtfMatchedMuonIndex = iMuon;
					}
					//product->bmtfMatchedMuonIndex.at(iBmtf) = iMuon;
					//product->bmtfMatchedMuonTrackType.at(iBmtf) = bmtfMatchedMuonTrackType;
				}
			}

			if (product->isBmtfMatchedMuon.at(iBmtf)) {
				product->bmtfMatchedMuonIndex.at(iBmtf) = bmtfMatchedMuonIndex;
				product->muonMatchedBmtfIndex.at(bmtfMatchedMuonIndex) = iBmtf;
			}
		}
	}

	for (unsigned short iBmtf = 0; iBmtf < product->bmtfSize; iBmtf++){
		// BMTF Tracks with Hits only in MB3 and MB4
		if (product->bmtfTrackerAddresses.at(iBmtf).at(0) == 3
			&& product->bmtfTrackerAddresses.at(iBmtf).at(1) == 15
			&& product->bmtfTrackerAddresses.at(iBmtf).at(2) != 15
			&& product->bmtfTrackerAddresses.at(iBmtf).at(3) != 15
		) {
			unsigned int bmtfMb34MatchedHoIndex = 999;
			for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
				if(std::find(product->bmtfMb34MatchedHoIndex.begin(), product->bmtfMb34MatchedHoIndex.end(), iHo) != product->bmtfMb34MatchedHoIndex.end()) { continue;}
				const double &bmtfMb34MatchedHoDeltaR = Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), product->hcalCmsEta.at(iHo), product->hcalCmsPhi.at(iHo));
				if (bmtfMb34MatchedHoDeltaR < fabs(product->bmtfMb34MatchedHoDeltaR.at(iBmtf))) {
					product->bmtfMb34MatchedHoDeltaR.at(iBmtf) = bmtfMb34MatchedHoDeltaR;
					product->bmtfMb34MatchedHoCmsEta.at(iBmtf) = product->hcalCmsEta.at(iHo);
					product->bmtfMb34MatchedHoCmsPhi.at(iBmtf) = product->hcalCmsPhi.at(iHo);
					product->bmtfMb34MatchedHoIEta.at(iBmtf) = product->hcalIEta.at(iHo);
					product->bmtfMb34MatchedHoIPhi.at(iBmtf) = product->hcalIPhi.at(iHo);
					bmtfMb34MatchedHoIndex = iHo;

				}
			}

			// Store the muon variables matched to this particular BMTF Muon
			if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
				if (product->bmtfMatchedMuonIndex.at(iBmtf) != 999) {
					unsigned int iMuon = product->bmtfMatchedMuonIndex.at(iBmtf);
					product->bmtfMb34MatchedMuonPt.at(iBmtf) = product->muonPt.at(iMuon);
					product->bmtfMb34MatchedMuonEta.at(iBmtf) = product->muonEta.at(iMuon);
					product->bmtfMb34MatchedMuonPhi.at(iBmtf) = product->muonPhi.at(iMuon);
				} else if (product->isBmtfMb34HoMatched.at(iBmtf)) {
					product->bmtfMb34MatchedMuonPt.at(iBmtf) = product->bmtfCmsPt.at(iBmtf);
					product->bmtfMb34MatchedMuonEta.at(iBmtf) = product->bmtfCmsEta.at(iBmtf);
					product->bmtfMb34MatchedMuonPhi.at(iBmtf) = product->bmtfCmsPhi.at(iBmtf);
				}
			}

			if (!product->isBmtfMb34HoMatched.at(iBmtf) && abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) > 10) { continue;}

			for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) { // No HoMb34 coincidence unless hits are in MB3 or MB4
				if (product->dttpStation.at(iDttp) != 3 && product->dttpStation.at(iDttp) != 4) { continue;}
				// If its outside the 5 wheels, there are no HO hits
				if (abs(product->dttpWheel.at(iDttp)) > 2) { continue;}
				// HO in iEta1/2, MB3/4 has to be in wheel 0
				if (abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) < 3 && abs(product->dttpWheel.at(iDttp)) != 0) { continue;}
				// HO in iEta3, MB3 has to be wheel 0/1
				else if (abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) == 3 && product->dttpStation.at(iDttp) == 3 && abs(product->dttpWheel.at(iDttp)) == 2) { continue;}
				// HO in iEta3, MB4 has to be wheel 1
				else if (abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) == 3 && product->dttpStation.at(iDttp) == 4 && abs(product->dttpWheel.at(iDttp)) != 1) { continue;}
				// HO in iEta4/5/6, MB3/4 in wheel 1
				else if (abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) > 3 && abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) < 7 && abs(product->dttpWheel.at(iDttp)) != 1) { continue;}
				// HO in iEta7, MB3 has to be wheel 1
				else if (abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) == 7 && product->dttpStation.at(iDttp) == 3 && abs(product->dttpWheel.at(iDttp)) != 1) { continue;}
				// HO in iEta7, MB4 has to be wheel 1/2
				else if (abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) == 7 && product->dttpStation.at(iDttp) == 4 && abs(product->dttpWheel.at(iDttp)) == 0) { continue;}
				// HO in iEta8/9/10, MB3/4 has to be wheel 2
				else if (abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) > 9 && abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) < 11 && abs(product->dttpWheel.at(iDttp)) != 2) { continue;}
				// HO Coincidence is geometrically possible

				const double &bmtfMb34MatchedHoDeltaPhi = Utility::DeltaPhi(product->bmtfCmsPhi.at(iBmtf), product->dttpPhi.at(iDttp));
				product->isBmtfMb34HoMatched.at(iBmtf) = true;
				product->bmtfMb34MatchedHoDeltaPhi.at(iBmtf) = bmtfMb34MatchedHoDeltaPhi;
				product->bmtfMb34MatchedHoDeltaIPhi.at(iBmtf) = Utility::DeltaIPhi(product->bmtfMb34MatchedHoIPhi.at(iBmtf), product->dttpIPhi.at(iDttp));

				if (product->isBmtfMb34HoMatched.at(iBmtf)) {
					product->bmtfMb34MatchedHoIndex.at(iBmtf) = bmtfMb34MatchedHoIndex;
					product->bmtfMb34MatchedHoIndex.at(bmtfMb34MatchedHoIndex) = iBmtf;
				}

				if (product->dttpStation.at(iDttp) == 3 && fabs(bmtfMb34MatchedHoDeltaPhi) < fabs(product->bmtfMb3MatchedHoDeltaPhi.at(iBmtf))) {
					product->isMb3HoIEtaMatched.at(iBmtf) = true;
					product->bmtfMb3MatchedHoDeltaPhi.at(iBmtf) = bmtfMb34MatchedHoDeltaPhi;
					product->bmtfMb3MatchedHoDeltaIPhi.at(iBmtf) = Utility::DeltaIPhi(product->bmtfMb34MatchedHoIPhi.at(iBmtf), product->dttpIPhi.at(iDttp));
				} else if (product->dttpStation.at(iDttp) == 4 && fabs(bmtfMb34MatchedHoDeltaPhi) < fabs(product->bmtfMb4MatchedHoDeltaPhi.at(iBmtf))) {
					product->isMb4HoIEtaMatched.at(iBmtf) = true;
					product->bmtfMb4MatchedHoDeltaPhi.at(iBmtf) = bmtfMb34MatchedHoDeltaPhi;
					product->bmtfMb4MatchedHoDeltaIPhi.at(iBmtf) = Utility::DeltaIPhi(product->bmtfMb34MatchedHoIPhi.at(iBmtf), product->dttpIPhi.at(iDttp));
				}
			}
		}
	}

	for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) {
		// isDttpMatchedBmtf means used BMTF Muon
		// try to recover unused muons using HO
		if (product->dttpBx.at(iDttp) != 0 ||
			product->dttpStation.at(iDttp) > 2 ||
			abs(product->dttpWheel.at(iDttp)) == 2 ||
			!product->dttpIsHq.at(iDttp) ||
			product->isDttpMatchedBmtf.at(iDttp) ||
			product->dttpPt.at(iDttp) < 0
		) { continue;}

		unsigned int dttpMatchedHoIndex = 99999;
		int deltaIPhiMin = -999;
		double deltaPhiMin = -999;
		for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
			unsigned int tmpHo = iHo;
			//tmpHo = product->nHcalDetIds - iHo - 1;

			if(std::find(product->dttpMatchedHoIndex.begin(), product->dttpMatchedHoIndex.end(), tmpHo) != product->dttpMatchedHoIndex.end()) { continue;}

			const int deltaIPhi = Utility::DeltaIPhi(product->dttpIPhi.at(iDttp), product->hcalIPhi.at(tmpHo));
			const double deltaPhi = Utility::DeltaPhi(product->dttpPhi.at(iDttp), product->hcalCmsPhi.at(tmpHo));
			if (abs(deltaPhi) < abs(deltaPhiMin)) {
				if (((product->dttpStation.at(iDttp) == 1 && abs(deltaIPhi) <= 1) || (product->dttpStation.at(iDttp) == 2 && abs(deltaIPhi) <= 2))
					&& product->dttpSection.at(iDttp) == product->hcalSection.at(tmpHo)
					&& product->dttpWheel.at(iDttp) == product->hcalWheel.at(tmpHo)
				) {
					deltaPhiMin = deltaPhi;
					deltaIPhiMin = deltaIPhi;
					product->dttpMatchedHoDeltaIPhi.at(iDttp) = deltaIPhiMin;
					product->dttpMatchedHoDeltaPhi.at(iDttp) = deltaPhiMin;
					product->isDttpMatchedHo.at(iDttp) = true;
					product->dttpMatchedHoCmsPhi.at(iDttp) = product->hcalCmsPhi.at(tmpHo);
					product->dttpMatchedHoCmsEta.at(iDttp) = product->hcalCmsEta.at(tmpHo);
					product->dttpMatchedHoIPhi.at(iDttp) = product->hcalIPhi.at(tmpHo);
					product->dttpMatchedHoIEta.at(iDttp) = product->hcalIEta.at(tmpHo);
					dttpMatchedHoIndex = tmpHo;
				}
			}
		}

		if (product->isDttpMatchedHo.at(iDttp)) {
			product->dttpMatchedHoIndex.at(iDttp) = dttpMatchedHoIndex;
			product->dttpMatchedHoIndex.at(dttpMatchedHoIndex) = iDttp;
		}

		if (!product->isDttpMatchedHo.at(iDttp)) { continue;}


		if (dataReader->GetHasRecoMuon()) {
			unsigned short dttpMatchedMuonIndex = 999;
			for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++){
				if(std::find(product->dttpMatchedMuonIndex.begin(), product->dttpMatchedMuonIndex.end(), iMuon) != product->dttpMatchedMuonIndex.end()) { continue;}
				if (!product->isMediumMuon.at(iMuon)
					|| !product->muonHasMb1.at(iMuon)
					|| product->muonIEta.at(iMuon) > 10
				) { continue;}

				const double &deltaR = Utility::DeltaR(product->dttpMatchedHoCmsEta.at(iDttp), product->dttpMatchedHoCmsPhi.at(iDttp), product->muonEta.at(iMuon), product->muonPhi.at(iMuon));

				if (deltaR < fabs(product->dttpMatchedMuonDeltaR.at(iDttp))) {
					product->dttpMatchedMuonDeltaR.at(iDttp) = deltaR;
					product->dttpMatchedMuonIndex.at(iDttp) = iMuon;
					product->isDttpMatchedMuon.at(iDttp) = true;
					dttpMatchedMuonIndex = iMuon;
				}

				int nHo3x3Hit = 0;
				for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
					int deltaIPhi = Utility::DeltaIPhi(product->dttpMatchedHoIPhi.at(iDttp), product->hcalIPhi.at(iHo));
					int deltaIEta = product->dttpMatchedHoIEta.at(iDttp) - product->hcalIEta.at(iHo);
					if (abs(deltaIEta) <= 1 && abs(deltaIPhi) <= 1) { nHo3x3Hit++;}
				}
				// Remove double counting for the same hit (deltaIPhi == 0 && deltaIEta == 0)
				nHo3x3Hit--;

				if (fabs(product->dttpMatchedMuonDeltaR.at(iDttp)) > 0.4) { continue;}
				product->muonMatchedDttpNHo3x3Hit.at(iMuon) = nHo3x3Hit;
			}

			if (product->isDttpMatchedMuon.at(iDttp)) {
				product->dttpMatchedMuonIndex.at(iDttp) = dttpMatchedMuonIndex;
				product->muonMatchedDttpIndex.at(dttpMatchedMuonIndex) = iDttp;
				product->isMuonMatchedDttp.at(dttpMatchedMuonIndex) = true;
			}
		}
	}

	if (dataReader->GetHasRecoMuon() && product->nMuon != 0) {
		for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++){
			//unused muons
			if (product->isMuonMatchedBmtf.at(iMuon) || product->isMuonMatchedDttp.at(iMuon)) {
				product->isMediumUsedMuon.push_back(product->isMediumMuon.at(iMuon));
				product->usedMuonHltIsoMu.push_back(product->muonHltIsoMu.at(iMuon));
				product->usedMuonHltMu.push_back(product->muonHltMu.at(iMuon));
				product->usedMuonPassesSingleMuon.push_back(product->muonPassesSingleMuon.at(iMuon));
				product->usedMuonHasMb1.push_back(product->muonHasMb1.at(iMuon));
				product->usedMuonCharge.push_back(product->muonCharge.at(iMuon));
				product->usedMuonIEta.push_back(product->muonIEta.at(iMuon));
				product->usedMuonE.push_back(product->muonE.at(iMuon));
				product->usedMuonEt.push_back(product->muonEt.at(iMuon));
				product->usedMuonPt.push_back(product->muonPt.at(iMuon));
				product->usedMuonEta.push_back(product->muonEta.at(iMuon));
				product->usedMuonPhi.push_back(product->muonPhi.at(iMuon));
				product->usedMuonIso.push_back(product->muonIso.at(iMuon));
				product->usedMuonHltIsoDeltaR.push_back(product->muonHltIsoDeltaR.at(iMuon));
				product->usedMuonDeltaR.push_back(product->muonDeltaR.at(iMuon));
				product->usedMuonEtaSt1.push_back(product->muonEtaSt1.at(iMuon));
				product->usedMuonPhiSt1.push_back(product->muonPhiSt1.at(iMuon));
				product->usedMuonEtaSt2.push_back(product->muonEtaSt2.at(iMuon));
				product->usedMuonPhiSt2.push_back(product->muonPhiSt2.at(iMuon));
				product->usedMuonMet.push_back(product->muonMet.at(iMuon));
				product->usedMuonMt.push_back(product->muonMt.at(iMuon));
			} else {
				product->isMediumUnusedMuon.push_back(product->isMediumMuon.at(iMuon));
				product->unusedMuonHltIsoMu.push_back(product->muonHltIsoMu.at(iMuon));
				product->unusedMuonHltMu.push_back(product->muonHltMu.at(iMuon));
				product->unusedMuonPassesSingleMuon.push_back(product->muonPassesSingleMuon.at(iMuon));
				product->unusedMuonHasMb1.push_back(product->muonHasMb1.at(iMuon));
				product->unusedMuonCharge.push_back(product->muonCharge.at(iMuon));
				product->unusedMuonIEta.push_back(product->muonIEta.at(iMuon));
				product->unusedMuonE.push_back(product->muonE.at(iMuon));
				product->unusedMuonEt.push_back(product->muonEt.at(iMuon));
				product->unusedMuonPt.push_back(product->muonPt.at(iMuon));
				product->unusedMuonEta.push_back(product->muonEta.at(iMuon));
				product->unusedMuonPhi.push_back(product->muonPhi.at(iMuon));
				product->unusedMuonIso.push_back(product->muonIso.at(iMuon));
				product->unusedMuonHltIsoDeltaR.push_back(product->muonHltIsoDeltaR.at(iMuon));
				product->unusedMuonDeltaR.push_back(product->muonDeltaR.at(iMuon));
				product->unusedMuonEtaSt1.push_back(product->muonEtaSt1.at(iMuon));
				product->unusedMuonPhiSt1.push_back(product->muonPhiSt1.at(iMuon));
				product->unusedMuonEtaSt2.push_back(product->muonEtaSt2.at(iMuon));
				product->unusedMuonPhiSt2.push_back(product->muonPhiSt2.at(iMuon));
				product->unusedMuonMet.push_back(product->muonMet.at(iMuon));
				product->unusedMuonMt.push_back(product->muonMt.at(iMuon));
			}
			product->nUnusedMuon = product->isMediumUnusedMuon.size();
			product->nUsedMuon = product->isMediumUsedMuon.size();
		}
	}
}

void HoCoincidenceProducer::EndJob(HoHistogramCollection* histCollection) {}
