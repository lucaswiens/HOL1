#include <HOAnalysis/HOL1/interface/Producer/HoCoincidenceProducer.h>

//HoCoincidenceProducer::HoCoincidenceProducer(const int &iEtaCut, const double &etaCut, const double &ptCut, const double &deltaPhiCut, const double &deltaRCut):
HoCoincidenceProducer::HoCoincidenceProducer(const int &iEtaCut, const double &etaCut, const double &l1EtaCut, const double &ptCut, const double &l1PtCut, const double &deltaPhiCut, const double &deltaRCut):
	iEtaCut(iEtaCut),
	etaCut(etaCut),
	l1EtaCut(l1EtaCut),
	ptCut(ptCut),
	l1PtCut(l1PtCut),
	deltaPhiCut(deltaPhiCut),
	deltaRCut(deltaRCut) {
		Name = "HO Coincidence Producer";
		std::cout << "The applied cuts are:\n" <<
			"recoPt    > " << ptCut       << std::endl <<
			"|recoEta| < " << etaCut      << std::endl <<
			"l1Pt      > " << l1PtCut   << std::endl <<
			"|l1Eta|   < " << l1EtaCut  << std::endl <<
			"|iEtaCut| < " << iEtaCut     << std::endl <<
			"deltaR    < " << deltaRCut   << std::endl <<
			"deltaPhi  < " << deltaPhiCut << std::endl;
	}

HoCoincidenceProducer::~HoCoincidenceProducer() {}

/*
	Explanation of the names, since it gets confusing
	bmtf prefix -> Track Finder Muon (tfMuon) variables
	dttp prefix -> The BMTF input variables, this is the TwinMux output
	muon prefix -> Reco level muons
	xMatchedY   -> y type variables matched to x
*/

void HoCoincidenceProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {

	if (product->tfMuonSize.at(Utility::Bmtf) != 0) {
		// Match BMTF with DTTP
		product->isBmtfMatchedDttp = std::vector(product->tfMuonSize.at(Utility::Bmtf), false);
		product->isBmtfMb34HoMatched = std::vector(product->tfMuonSize.at(Utility::Bmtf), false);
		product->isMb3HoIEtaMatched = std::vector(product->tfMuonSize.at(Utility::Bmtf), false);
		product->isMb4HoIEtaMatched = std::vector(product->tfMuonSize.at(Utility::Bmtf), false);

		//Indices for better matching
		product->bmtfMatchedDttpIndex = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);

		// Bmtf Matched Dttp
		product->bmtfMatchedDttpDeltaPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMatchedDttpCmsPt = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMatchedDttpPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -9999.); // dttpPhi range is [-2048, 2048]
		product->bmtfMatchedDttpCmsPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);

		product->bmtfMatchedDttpDeltaPhiPerStation = std::vector<std::vector<double>>(product->tfMuonSize.at(Utility::Bmtf), {-999., -999., -999., -999.});
		product->bmtfMatchedDttpIndexPerStation = std::vector<std::vector<int>>(product->tfMuonSize.at(Utility::Bmtf), {-999, -999, -999, -999});

		// Bmtf MB34 matched Ho
		product->bmtfMb34MatchedHoDeltaR = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedHoPt = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedHoCmsEta = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedHoCmsPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedHoDeltaPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedHoIEta = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);
		product->bmtfMb34MatchedHoIPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);
		product->bmtfMb34MatchedHoDeltaIPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);
		product->bmtfMb3MatchedHoDeltaPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb3MatchedHoDeltaIPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);
		product->bmtfMb3MatchedHoIPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);
		product->bmtfMb4MatchedHoDeltaPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb4MatchedHoDeltaIPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);
		product->bmtfMb4MatchedHoIPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);
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
		product->dttpMatchedHoCmsPt = std::vector(product->dttpSize, -999.);
		product->dttpMatchedHoCmsPhi = std::vector(product->dttpSize, -999.);
		product->dttpMatchedHoCmsEta = std::vector(product->dttpSize, -999.);
		product->dttpMatchedMuonNHo3x3Hit = std::vector(product->dttpSize, 999);
		product->dttpNHo3x3Hit = std::vector(product->dttpSize, -999);
	}

	if (product->hcalIEta.size() != 0) {
		//Indices for better matching
		product->bmtfMb34MatchedHoIndex = std::vector(product->hcalIEta.size(), (unsigned int)999);
		product->bmtfMb3MatchedHoIndex = std::vector(product->hcalIEta.size(), (unsigned int)999);
		product->bmtfMb4MatchedHoIndex = std::vector(product->hcalIEta.size(), (unsigned int)999);
		product->dttpMatchedHoIndex = std::vector(product->hcalIEta.size(), (unsigned int)999);
	}


	if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
		// Muon Variable
		product->muonNHo3x3Hit = std::vector(product->nProbeMuon, -999);
		// Match BMTF with DTTP
		product->isBmtfMatchedMuon = std::vector(product->tfMuonSize.at(Utility::Bmtf), false);
		product->isDttpMatchedMuon = std::vector(product->dttpSize, false);
		product->isMuonMatchedBmtf = std::vector(product->nProbeMuon, false);
		product->isMuonMatchedDttp = std::vector(product->nProbeMuon, false);

		//Indices for better matching
		product->bmtfMatchedMuonIndex = std::vector(product->tfMuonSize.at(Utility::Bmtf), (unsigned short)999);
		product->dttpMatchedMuonIndex = std::vector(product->dttpSize, (unsigned short)999);
		product->muonMatchedBmtfIndex = std::vector(product->nProbeMuon, (unsigned short)999);
		product->muonMatchedDttpIndex = std::vector(product->nProbeMuon, -999);

		// Bmtf matched Muon
		product->muonMatchedBmtfCmsPt = std::vector(product->nProbeMuon, -999.);
		product->muonMatchedBmtfCmsEta = std::vector(product->nProbeMuon, -999.);

		// Bmtf Matched Dttp
		product->bmtfMatchedMuonDeltaR = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMatchedMuonPt = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMatchedMuonEta = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMatchedMuonPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMatchedMuonCharge = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999);
		product->bmtfMatchedMuonDeltaPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);

		// Bmtf MB34 matched Ho
		product->bmtfMb34MatchedMuonPt = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedMuonEta = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedMuonPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedMuonDeltaPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);

		// Dttp Matched Muon
		product->dttpMatchedMuonDeltaR = std::vector(product->dttpSize, -999.);
		product->muonMatchedDttpNHo3x3Hit = std::vector(product->nProbeMuon, -999);
	}

	if (product->tagMuonPt.size() == 0) { product->nProbeMuon = 0; return;}

	if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
		for (unsigned short iMuon = 0; iMuon < product->nProbeMuon; iMuon++) {
			const double &probeMuonEta = product->probeMuonHasMb2.at(iMuon) ? product->probeMuonEtaSt2.at(iMuon) : product->probeMuonEtaSt1.at(iMuon);
			const double &probeMuonPhi = product->probeMuonHasMb2.at(iMuon) ? product->probeMuonPhiSt2.at(iMuon) : product->probeMuonPhiSt1.at(iMuon);

			double bmtfMatchedMuonDeltaRMin = -999;
			for (unsigned short iBmtf = 0; iBmtf < product->tfMuonSize.at(Utility::Bmtf); iBmtf++) {
				if (product->isBmtfMatchedMuon.at(iBmtf)) { continue;}
				if (product->tfMuonBx.at(Utility::Bmtf).at(iBmtf) != 0) { continue;}
				if (fabs(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf)) > l1EtaCut) { continue;}

				const double &bmtfMatchedMuonDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf), product->tfMuonCmsPhi.at(Utility::Bmtf).at(iBmtf), probeMuonEta, probeMuonPhi);
				if (bmtfMatchedMuonDeltaR < fabs(bmtfMatchedMuonDeltaRMin)) {
					if (bmtfMatchedMuonDeltaR < deltaRCut) {
						product->isMuonMatchedBmtf.at(iMuon) = true;
						bmtfMatchedMuonDeltaRMin = bmtfMatchedMuonDeltaR;
						product->muonMatchedBmtfCmsPt.at(iMuon) = product->tfMuonCmsPt.at(Utility::Bmtf).at(iBmtf);
						product->muonMatchedBmtfCmsEta.at(iMuon) = product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf);
						product->muonMatchedBmtfIndex.at(iMuon) = iBmtf;
					}
				}
			}

			if (product->isMuonMatchedBmtf.at(iMuon)) {
				product->bmtfMatchedMuonDeltaR.at(product->muonMatchedBmtfIndex.at(iMuon)) = bmtfMatchedMuonDeltaRMin;
				product->isBmtfMatchedMuon.at(product->muonMatchedBmtfIndex.at(iMuon)) = product->isMuonMatchedBmtf.at(iMuon);
				product->bmtfMatchedMuonPt.at(product->muonMatchedBmtfIndex.at(iMuon)) = product->probeMuonPt.at(iMuon);
				product->bmtfMatchedMuonEta.at(product->muonMatchedBmtfIndex.at(iMuon)) = product->probeMuonEta.at(iMuon);
				product->bmtfMatchedMuonPhi.at(product->muonMatchedBmtfIndex.at(iMuon)) = product->probeMuonPhi.at(iMuon);
				product->bmtfMatchedMuonCharge.at(product->muonMatchedBmtfIndex.at(iMuon)) = product->probeMuonCharge.at(iMuon);
				product->bmtfMatchedMuonIndex.at(product->muonMatchedBmtfIndex.at(iMuon)) = iMuon;
			}
		}
	}

	for (unsigned short iBmtf = 0; iBmtf < product->tfMuonSize.at(Utility::Bmtf); iBmtf++) {
		if (product->tfMuonBx.at(Utility::Bmtf).at(iBmtf) != 0) { continue;}
		if (product->tagMuonMatchedBmtfIndex == iBmtf) { continue;}

		//if (product->tfMuonCmsPt.at(Utility::Bmtf).at(iBmtf) < ptCut || fabs(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf)) > etaCut) { continue;}
		if (product->tfMuonCmsPt.at(Utility::Bmtf).at(iBmtf) < l1PtCut || fabs(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf)) > l1EtaCut) { continue;}

		int bmtfMatchedDttpIndex = -999, bmtfStation = -999;
		for (int iBmtfStation = 1; iBmtfStation <= 4; iBmtfStation++) {
			// For Mb1, TrackAddress it should not be 3, but for MB2, MB3 and MB4 it should not be 15
			if (iBmtfStation == 1) {
				if (product->bmtfTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(iBmtfStation - 1) == 3) { continue;}
			} else {
				if (product->bmtfTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(iBmtfStation - 1) == 15) { continue;}
			}
			for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) {
				if (product->dttpBx.at(iDttp) != 0) { continue;}
				// Skip if already associated to a BMTF
				if (product->isDttpMatchedBmtf.at(iDttp)) { continue;}

				if (product->dttpStation.at(iDttp) != iBmtfStation) { continue;} // Select the correct station
				if (product->dttpStation.at(iDttp) == 1 && abs(product->dttpWheel.at(iDttp)) == 2) { continue;} // For station 1 exclude Wheel +-2

				double bmtfMatchedDttpDeltaPhi = Utility::DeltaPhi(product->tfMuonCmsPhi.at(Utility::Bmtf).at(iBmtf), product->dttpCmsPhi.at(iDttp));
				if (fabs(bmtfMatchedDttpDeltaPhi) < fabs(product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(iBmtfStation - 1))) {
					bmtfStation = iBmtfStation;
					product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(iBmtfStation - 1) = bmtfMatchedDttpDeltaPhi;
					product->bmtfMatchedDttpDeltaPhi.at(iBmtf) = bmtfMatchedDttpDeltaPhi;
					product->bmtfMatchedDttpCmsPt.at(iBmtf) = product->dttpCmsPt.at(iDttp);
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
			product->bmtfMatchedDttpIndexPerStation.at(iBmtf).at(bmtfStation - 1) = bmtfMatchedDttpIndex;
		}
	}

	for (unsigned short iBmtf = 0; iBmtf < product->tfMuonSize.at(Utility::Bmtf); iBmtf++) {
		if (product->tfMuonBx.at(Utility::Bmtf).at(iBmtf) != 0) { continue;}
		if (product->tfMuonCmsPt.at(Utility::Bmtf).at(iBmtf) < l1PtCut || fabs(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf)) > l1EtaCut) { continue;}

		// BMTF Tracks with Hits only in MB3 and MB4
		if (product->bmtfTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(0) == 3 ||
			product->bmtfTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(1) == 15 ||
			product->bmtfTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(2) != 15 ||
			product->bmtfTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(3) != 15
		) {
			unsigned int bmtfMb34MatchedHoIndex = 999;
			for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
				//if (std::find(product->bmtfMb34MatchedHoIndex.begin(), product->bmtfMb34MatchedHoIndex.end(), iHo) != product->bmtfMb34MatchedHoIndex.end()) { continue;}

				const double &bmtfMb34MatchedHoDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf), product->tfMuonCmsPhi.at(Utility::Bmtf).at(iBmtf), product->hcalCmsEta.at(iHo), product->hcalCmsPhi.at(iHo));

				if (bmtfMb34MatchedHoDeltaR < fabs(product->bmtfMb34MatchedHoDeltaR.at(iBmtf))) {
					product->isBmtfMb34HoMatched.at(iBmtf) = true;
					product->bmtfMb34MatchedHoDeltaR.at(iBmtf) = bmtfMb34MatchedHoDeltaR;
					product->bmtfMb34MatchedHoCmsEta.at(iBmtf) = product->hcalCmsEta.at(iHo);
					product->bmtfMb34MatchedHoCmsPhi.at(iBmtf) = product->hcalCmsPhi.at(iHo);
					product->bmtfMb34MatchedHoIEta.at(iBmtf) = product->hcalIEta.at(iHo);
					product->bmtfMb34MatchedHoIPhi.at(iBmtf) = product->hcalIPhi.at(iHo);
					bmtfMb34MatchedHoIndex = iHo;

				}
			}

			// Store the muon variables matched to this particular BMTF Muon
			if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
				if (product->bmtfMatchedMuonIndex.at(iBmtf) != 999) {
					unsigned int iMuon = product->bmtfMatchedMuonIndex.at(iBmtf);
					product->bmtfMb34MatchedMuonPt.at(iBmtf) = product->probeMuonPt.at(iMuon);
					product->bmtfMb34MatchedMuonEta.at(iBmtf) = product->probeMuonEta.at(iMuon);
					product->bmtfMb34MatchedMuonPhi.at(iBmtf) = product->probeMuonPhi.at(iMuon);
				} else if (product->isBmtfMb34HoMatched.at(iBmtf)) {
					product->bmtfMb34MatchedMuonPt.at(iBmtf) = product->tfMuonCmsPt.at(Utility::Bmtf).at(iBmtf);
					product->bmtfMb34MatchedMuonEta.at(iBmtf) = product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf);
					product->bmtfMb34MatchedMuonPhi.at(iBmtf) = product->tfMuonCmsPhi.at(Utility::Bmtf).at(iBmtf);
				}
			}

			if (!product->isBmtfMb34HoMatched.at(iBmtf) && abs(product->bmtfMb34MatchedHoIEta.at(iBmtf)) > iEtaCut) { continue;}

			for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) { // No HoMb34 coincidence unless hits are in MB3 or MB4

				if (product->dttpCmsPt.at(iDttp) < l1PtCut) { continue;} // TODO: In the DN this was only applied for rate.. Think about it and make it sensible

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

				const double &bmtfMb34MatchedHoDeltaPhi = Utility::DeltaPhi(product->tfMuonCmsPhi.at(Utility::Bmtf).at(iBmtf), product->dttpCmsPhi.at(iDttp));
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
		if (product->dttpBx.at(iDttp) != 0 ||
			product->dttpStation.at(iDttp) > 2 ||
			abs(product->dttpWheel.at(iDttp)) == 2 ||
			!product->dttpIsHq.at(iDttp) ||
			product->isDttpMatchedBmtf.at(iDttp) || // this is equivalent to (!isIsoMb1)
			product->dttpCmsPt.at(iDttp) < l1PtCut //FIXME
		) { continue;}

		unsigned int dttpMatchedHoIndex = 99999;
		for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
			unsigned int tmpHo = iHo;
			//tmpHo = product->nHcalDetIds - iHo - 1;

			if (product->isDttpMatchedHo.at(iDttp)) { continue;}

			const int deltaIPhi = Utility::DeltaIPhi(product->dttpIPhi.at(iDttp), product->hcalIPhi.at(tmpHo));
			const double deltaPhi = Utility::DeltaPhi(product->dttpCmsPhi.at(iDttp), product->hcalCmsPhi.at(tmpHo));
			if (abs(deltaIPhi) < abs(product->dttpMatchedHoDeltaIPhi.at(iDttp))) {
				if (((product->dttpStation.at(iDttp) == 1 && abs(deltaIPhi) <= 1) || (product->dttpStation.at(iDttp) == 2 && abs(deltaIPhi) <= 2)) &&
					product->dttpSection.at(iDttp) == product->hcalSection.at(tmpHo) &&
					product->dttpWheel.at(iDttp) == product->hcalWheel.at(tmpHo)
				) {
					int nHo3x3Hit = 0;
					for (unsigned int iHo2 = 0; iHo2 < product->nHcalDetIds; iHo2++) {
						if (iHo2 == tmpHo) { continue;}
						int deltaIPhi2 = Utility::DeltaIPhi(product->dttpMatchedHoIPhi.at(iDttp), product->hcalIPhi.at(iHo2));
						if ((product->dttpStation.at(iDttp) == 1 && abs(deltaIPhi2) <= 1) &&
							product->dttpSection.at(iDttp) == product->hcalSection.at(iHo2) &&
							product->dttpWheel.at(iDttp) == product->hcalWheel.at(iHo2)
						) { nHo3x3Hit++; }
					}
					product->dttpNHo3x3Hit.at(iDttp) = nHo3x3Hit;

					product->dttpMatchedHoDeltaIPhi.at(iDttp) = deltaIPhi;
					product->dttpMatchedHoDeltaPhi.at(iDttp) = deltaPhi;
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
			product->dttpMatchedHoCmsPt.at(iDttp) = product->dttpCmsPt.at(iDttp);
			product->dttpMatchedHoIndex.at(dttpMatchedHoIndex) = iDttp;
		}

		if (!product->isDttpMatchedHo.at(iDttp)) { continue;}

		if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
			for (unsigned short iMuon = 0; iMuon < product->nProbeMuon; iMuon++) {
				//if (std::find(product->dttpMatchedMuonIndex.begin(), product->dttpMatchedMuonIndex.end(), iMuon) != product->dttpMatchedMuonIndex.end()) { continue;}
				if (!product->probeMuonHasMb1.at(iMuon)) { continue;}
				if (product->isDttpMatchedMuon.at(iDttp)) { continue;}
				if (product->probeMuonIEta.at(iMuon) > iEtaCut) { continue;}


				std::vector<double> dttpMatchedMuonDeltaPhiVec, dttpMatchedMuonDeltaRVec;

				dttpMatchedMuonDeltaPhiVec.push_back(Utility::DeltaPhi(product->dttpMatchedHoCmsPhi.at(iDttp), product->probeMuonPhi.at(iMuon)));
				dttpMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->dttpMatchedHoCmsEta.at(iDttp), product->dttpMatchedHoCmsPhi.at(iDttp), product->probeMuonEta.at(iMuon), product->probeMuonPhi.at(iMuon)));

				dttpMatchedMuonDeltaPhiVec.push_back(Utility::DeltaPhi(product->dttpMatchedHoCmsPhi.at(iDttp), product->probeMuonPhiSt1.at(iMuon)));
				dttpMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->dttpMatchedHoCmsEta.at(iDttp), product->dttpMatchedHoCmsPhi.at(iDttp), product->probeMuonEtaSt1.at(iMuon), product->probeMuonPhiSt1.at(iMuon)));

				dttpMatchedMuonDeltaPhiVec.push_back(Utility::DeltaPhi(product->dttpMatchedHoCmsPhi.at(iDttp), product->probeMuonPhiSt2.at(iMuon)));
				dttpMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->dttpMatchedHoCmsEta.at(iDttp), product->dttpMatchedHoCmsPhi.at(iDttp), product->probeMuonEtaSt2.at(iMuon), product->probeMuonPhiSt2.at(iMuon)));

				const int &matchedStation = std::min_element(dttpMatchedMuonDeltaRVec.begin(), dttpMatchedMuonDeltaRVec.end()) - dttpMatchedMuonDeltaRVec.begin();
				const double &deltaR   = dttpMatchedMuonDeltaRVec.at(matchedStation);

				int nHo3x3Hit = 0;
				for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
					int deltaIPhi = Utility::DeltaIPhi(product->dttpMatchedHoIPhi.at(iDttp), product->hcalIPhi.at(iHo));
					int deltaIEta = product->dttpMatchedHoIEta.at(iDttp) - product->hcalIEta.at(iHo);
					if (abs(deltaIEta) <= 1 && abs(deltaIPhi) <= 1) { nHo3x3Hit++;}
				}
				// Remove double counting for the same hit (deltaIPhi == 0 && deltaIEta == 0)
				nHo3x3Hit--;

				product->muonNHo3x3Hit.at(iMuon) = nHo3x3Hit;

				if (product->isDttpMatchedMuon.at(iDttp)) { continue;}

				if (deltaR < fabs(product->dttpMatchedMuonDeltaR.at(iDttp))) {
					product->isDttpMatchedMuon.at(iDttp) = deltaR < deltaRCut;
					product->dttpMatchedMuonIndex.at(iDttp) = iMuon;
					product->dttpMatchedMuonNHo3x3Hit.at(iDttp) = nHo3x3Hit;
					product->dttpMatchedMuonDeltaR.at(iDttp) = deltaR;
					product->dttpMatchedMuonIndex.at(iDttp) = iMuon;
				}
			}

			if (product->isDttpMatchedMuon.at(iDttp)) {
				product->muonMatchedDttpIndex.at(product->dttpMatchedMuonIndex.at(iDttp)) = iDttp;
				product->isMuonMatchedDttp.at(product->dttpMatchedMuonIndex.at(iDttp)) = true;
				product->muonMatchedDttpNHo3x3Hit.at(product->dttpMatchedMuonIndex.at(iDttp)) = product->dttpMatchedMuonNHo3x3Hit.at(iDttp);
			}
		}
	}

	//if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
	if (false) { // TODO THis is probably useless..
		for (unsigned short iMuon = 0; iMuon < product->nProbeMuon; iMuon++) {
			//used muons
			if (product->isMuonMatchedBmtf.at(iMuon) || product->isMuonMatchedDttp.at(iMuon)) {
				product->isMediumUsedMuon.push_back(product->isMediumMuon.at(iMuon));
				product->usedMuonHltIsoMu.push_back(product->probeMuonHltIsoMu.at(iMuon));
				product->usedMuonHltMu.push_back(product->probeMuonHltMu.at(iMuon));
				product->usedMuonPassesSingleMuon.push_back(product->probeMuonPassesSingleMuon.at(iMuon));
				product->usedMuonHasMb1.push_back(product->probeMuonHasMb1.at(iMuon));
				product->usedMuonCharge.push_back(product->probeMuonCharge.at(iMuon));
				product->usedMuonIEta.push_back(product->probeMuonIEta.at(iMuon));
				product->usedMuonE.push_back(product->probeMuonE.at(iMuon));
				product->usedMuonEt.push_back(product->probeMuonEt.at(iMuon));
				product->usedMuonPt.push_back(product->probeMuonPt.at(iMuon));
				product->usedMuonEta.push_back(product->probeMuonEta.at(iMuon));
				product->usedMuonPhi.push_back(product->probeMuonPhi.at(iMuon));
				product->usedMuonIso.push_back(product->probeMuonIso.at(iMuon));
				product->usedMuonHltIsoDeltaR.push_back(product->probeMuonHltIsoDeltaR.at(iMuon));
				product->usedMuonDeltaR.push_back(product->probeMuonDeltaR.at(iMuon));
				product->usedMuonEtaSt1.push_back(product->probeMuonEtaSt1.at(iMuon));
				product->usedMuonPhiSt1.push_back(product->probeMuonPhiSt1.at(iMuon));
				product->usedMuonEtaSt2.push_back(product->probeMuonEtaSt2.at(iMuon));
				product->usedMuonPhiSt2.push_back(product->probeMuonPhiSt2.at(iMuon));
				product->usedMuonMet.push_back(product->probeMuonMet.at(iMuon));
				product->usedMuonMt.push_back(product->probeMuonMt.at(iMuon));
				product->usedMuonNHo3x3Hit.push_back(product->probeMuonNHo3x3Hit.at(iMuon));
			} else {
				product->isMediumUnusedMuon.push_back(product->isMediumMuon.at(iMuon));
				product->unusedMuonHltIsoMu.push_back(product->probeMuonHltIsoMu.at(iMuon));
				product->unusedMuonHltMu.push_back(product->probeMuonHltMu.at(iMuon));
				product->unusedMuonPassesSingleMuon.push_back(product->probeMuonPassesSingleMuon.at(iMuon));
				product->unusedMuonHasMb1.push_back(product->probeMuonHasMb1.at(iMuon));
				product->unusedMuonCharge.push_back(product->probeMuonCharge.at(iMuon));
				product->unusedMuonIEta.push_back(product->probeMuonIEta.at(iMuon));
				product->unusedMuonE.push_back(product->probeMuonE.at(iMuon));
				product->unusedMuonEt.push_back(product->probeMuonEt.at(iMuon));
				product->unusedMuonPt.push_back(product->probeMuonPt.at(iMuon));
				product->unusedMuonEta.push_back(product->probeMuonEta.at(iMuon));
				product->unusedMuonPhi.push_back(product->probeMuonPhi.at(iMuon));
				product->unusedMuonIso.push_back(product->probeMuonIso.at(iMuon));
				product->unusedMuonHltIsoDeltaR.push_back(product->probeMuonHltIsoDeltaR.at(iMuon));
				product->unusedMuonDeltaR.push_back(product->probeMuonDeltaR.at(iMuon));
				product->unusedMuonEtaSt1.push_back(product->probeMuonEtaSt1.at(iMuon));
				product->unusedMuonPhiSt1.push_back(product->probeMuonPhiSt1.at(iMuon));
				product->unusedMuonEtaSt2.push_back(product->probeMuonEtaSt2.at(iMuon));
				product->unusedMuonPhiSt2.push_back(product->probeMuonPhiSt2.at(iMuon));
				product->unusedMuonMet.push_back(product->probeMuonMet.at(iMuon));
				product->unusedMuonMt.push_back(product->probeMuonMt.at(iMuon));
				product->unusedMuonNHo3x3Hit.push_back(product->probeMuonNHo3x3Hit.at(iMuon));
			}
			product->nUnusedMuon = product->isMediumUnusedMuon.size();
			product->nUsedMuon = product->isMediumUsedMuon.size();
		}
	}
}

void HoCoincidenceProducer::EndJob(HoHistogramCollection* histCollection) {}
