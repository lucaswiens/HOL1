#include <HOAnalysis/HOL1/interface/Producer/HoCoincidenceProducer.h>

//HoCoincidenceProducer::HoCoincidenceProducer(const int &iEtaCut, const double &etaCut, const double &ptCut, const double &deltaPhiCut, const double &deltaRCut):
HoCoincidenceProducer::HoCoincidenceProducer(const int &iEtaCut, const double &etaCut, const double &l1EtaCut, const double &ptCut, const double &l1PtCut, const double &deltaPhiCut, const double &deltaRProbeAndTfCut, const double &deltaRProbeAndHoCut):
	iEtaCut(iEtaCut),
	etaCut(etaCut),
	l1EtaCut(l1EtaCut),
	ptCut(ptCut),
	l1PtCut(l1PtCut),
	deltaPhiCut(deltaPhiCut),
	deltaRProbeAndTfCut(deltaRProbeAndTfCut),
	deltaRProbeAndHoCut(deltaRProbeAndHoCut) {
		Name = "HO Coincidence Producer";
		std::cout << "The cuts used in the L1 and HO Matching are:\n" <<
			"probePt           > " << ptCut               << std::endl <<
			"|probeEta|        < " << etaCut              << std::endl <<
			"l1Pt              > " << l1PtCut             << std::endl <<
			"|l1Eta|           < " << l1EtaCut            << std::endl <<
			"|iEtaCut|         < " << iEtaCut             << std::endl <<
			"deltaR(Probe, Tf) < " << deltaRProbeAndTfCut << std::endl <<
			"deltaR(Probe, Ho) < " << deltaRProbeAndHoCut << std::endl <<
			"deltaPhi          < " << deltaPhiCut         << std::endl;
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
		product->dttpMatchedMuonHoN3x3Hit = std::vector(product->dttpSize, 999);
		product->dttpHoN3x3Hit = std::vector(product->dttpSize, -999);
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
		product->muonHoN3x3Hit = std::vector(product->nProbeMuon, -999);
		// Match BMTF with DTTP
		product->isDttpMatchedMuon = std::vector(product->dttpSize, false);
		product->isMuonMatchedTf = std::vector(product->nProbeMuon, false);
		product->isMuonMatchedDttp = std::vector(product->nProbeMuon, false);
		product->isTfMatchedMuon = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), false)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), false)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), false)}
		};

		//Indices for better matching
		product->dttpMatchedMuonIndex = std::vector(product->dttpSize, (unsigned short)999);
		product->muonMatchedDttpIndex = std::vector(product->nProbeMuon, -999);
		product->tfMatchedMuonIndex = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), (unsigned short)999)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), (unsigned short)999)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), (unsigned short)999)}
		};

		// Bmtf matched Muon
		product->tfMatchedMuonDeltaR = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), -999.)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), -999.)}
		};
		product->tfMatchedMuonPt = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), -999.)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), -999.)}
		};
		product->tfMatchedMuonEta = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), -999.)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), -999.)}
		};
		product->tfMatchedMuonPhi = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), -999.)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), -999.)}
		};
		product->tfMatchedMuonCharge = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), -999)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), -999)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), -999)}
		};
		product->tfMatchedMuonDeltaPhi = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), -999.)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), -999.)}
		};
		product->tfMatchedMuonTfType = {
			{Utility::Bmtf, std::vector(product->tfMuonSize.at(Utility::Bmtf), -999)},
			{Utility::Omtf, std::vector(product->tfMuonSize.at(Utility::Omtf), -999)},
			{Utility::Emtf, std::vector(product->tfMuonSize.at(Utility::Emtf), -999)}
		};


		// Bmtf MB34 matched Ho
		product->bmtfMb34MatchedMuonPt = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedMuonEta = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedMuonPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);
		product->bmtfMb34MatchedMuonDeltaPhi = std::vector(product->tfMuonSize.at(Utility::Bmtf), -999.);

		// Dttp Matched Muon
		product->dttpMatchedMuonDeltaR = std::vector(product->dttpSize, -999.);
		product->muonMatchedDttpHoN3x3Hit = std::vector(product->nProbeMuon, -999);
	}

	if (product->tagMuonPt.size() == 0) { product->nProbeMuon = 0; return;}

	if (dataReader->GetHasRecoMuon() && product->nProbeMuon != 0) {
		for (unsigned short iProbe = 0; iProbe < product->nProbeMuon; iProbe++) {
			int muonMatchedTfType = 999;
			unsigned int muonMatchedTfIndex = 999;
			const double &probeMuonEta = product->probeMuonHasMb2.at(iProbe) ? product->probeMuonEtaSt2.at(iProbe) : product->probeMuonEtaSt1.at(iProbe);
			const double &probeMuonPhi = product->probeMuonHasMb2.at(iProbe) ? product->probeMuonPhiSt2.at(iProbe) : product->probeMuonPhiSt1.at(iProbe);
			// testing
			//const double &probeMuonEta = product->probeMuonEta.at(iProbe);
			//const double &probeMuonPhi = product->probeMuonPhi.at(iProbe);

			double tfMatchedMuonDeltaRMin = 999;
			for (int tfType : Utility::TfAlgorithms) {
				for (unsigned short iTf = 0; iTf < product->tfMuonSize.at(tfType); iTf++) {
					if (product->isTfMatchedMuon.at(tfType).at(iTf)) { continue;}
					if (product->tfMuonBx.at(tfType).at(iTf) != 0) { continue;}
					if (fabs(product->tfMuonCmsEta.at(tfType).at(iTf)) > l1EtaCut) { continue;}

					const double &tfMatchedMuonDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(tfType).at(iTf), product->tfMuonCmsPhi.at(tfType).at(iTf), probeMuonEta, probeMuonPhi);
					if (tfMatchedMuonDeltaR < tfMatchedMuonDeltaRMin) {
						bool uGMTMatch = false;
						for (unsigned short iUGMT = 0; iUGMT < product->nUGMTMuons; iUGMT++) {
							if (product->tfMuonBx.at(tfType).at(iTf) == product->uGMTMuonBx.at(iUGMT) &&
								product->tfMuonEta.at(tfType).at(iTf) == product->uGMTMuonEta.at(iUGMT) &&
								product->tfMuonPt.at(tfType).at(iTf) == product->uGMTMuonPt.at(iUGMT)
							) { uGMTMatch = true;}
						}
						if (!uGMTMatch) { continue;}

						if (tfMatchedMuonDeltaR < deltaRProbeAndTfCut) {
							muonMatchedTfType = tfType;
							muonMatchedTfIndex = iTf;
							tfMatchedMuonDeltaRMin = tfMatchedMuonDeltaR;
						}
					}
				}
			}

			if (muonMatchedTfIndex < 999 && muonMatchedTfType < 999) {
				product->tfMatchedMuonDeltaR.at(muonMatchedTfType).at(muonMatchedTfIndex) = tfMatchedMuonDeltaRMin;
				product->isTfMatchedMuon.at(muonMatchedTfType).at(muonMatchedTfIndex) = true;
				product->tfMatchedMuonPt.at(muonMatchedTfType).at(muonMatchedTfIndex) = product->probeMuonPt.at(iProbe);
				product->tfMatchedMuonEta.at(muonMatchedTfType).at(muonMatchedTfIndex) = product->probeMuonEta.at(iProbe);
				product->tfMatchedMuonPhi.at(muonMatchedTfType).at(muonMatchedTfIndex) = product->probeMuonPhi.at(iProbe);
				product->tfMatchedMuonCharge.at(muonMatchedTfType).at(muonMatchedTfIndex) = product->probeMuonCharge.at(iProbe);
				product->tfMatchedMuonIndex.at(muonMatchedTfType).at(muonMatchedTfIndex) = iProbe;
				product->tfMatchedMuonTfType.at(muonMatchedTfType).at(muonMatchedTfIndex) = muonMatchedTfType;
				product->isMuonMatchedTf.at(iProbe) = true;
			}
		}
	}

	for (unsigned short iBmtf = 0; iBmtf < product->tfMuonSize.at(Utility::Bmtf); iBmtf++) {
		if (product->tfMuonBx.at(Utility::Bmtf).at(iBmtf) != 0) { continue;}
		if (product->tagMuonMatchedBmtfIndex == iBmtf) { continue;}

		//if (product->tfMuonCmsPt.at(Utility::Bmtf).at(iBmtf) < l1PtCut || std::abs(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf)) > l1EtaCut) { continue;}

		int bmtfMatchedDttpIndex = -999, bmtfStation = -999;
		for (int iBmtfStation = 1; iBmtfStation <= 4; iBmtfStation++) {
			// For Mb1, TrackAddress it should not be 3, but for MB2, MB3 and MB4 it should not be 15
			if (iBmtfStation == 1) {
				if (product->tfMuonTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(iBmtfStation - 1) == 3) { continue;}
			} else {
				if (product->tfMuonTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(iBmtfStation - 1) == 15) { continue;}
			}
			for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) {
				if (product->dttpBx.at(iDttp) != 0) { continue;}
				// Skip if already associated to a BMTF
				if (product->isDttpMatchedBmtf.at(iDttp)) { continue;}

				if (product->dttpStation.at(iDttp) != iBmtfStation) { continue;} // Select the correct station
				if (product->dttpStation.at(iDttp) == 1 && abs(product->dttpWheel.at(iDttp)) == 2) { continue;} // For station 1 exclude Wheel +-2

				double bmtfMatchedDttpDeltaPhi = Utility::DeltaPhi(product->tfMuonCmsPhi.at(Utility::Bmtf).at(iBmtf), product->dttpCmsPhi.at(iDttp));
				if (std::abs(bmtfMatchedDttpDeltaPhi) < std::abs(product->bmtfMatchedDttpDeltaPhiPerStation.at(iBmtf).at(iBmtfStation - 1))) {
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
		if (product->tfMuonCmsPt.at(Utility::Bmtf).at(iBmtf) < l1PtCut || std::abs(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf)) > l1EtaCut) { continue;}

		// BMTF Tracks with Hits only in MB3 and MB4
		if (product->tfMuonTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(0) == 3 ||
			product->tfMuonTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(1) == 15 ||
			product->tfMuonTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(2) != 15 ||
			product->tfMuonTrackerAddresses.at(Utility::Bmtf).at(iBmtf).at(3) != 15
		) {
			unsigned int bmtfMb34MatchedHoIndex = 999;
			for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
				//if (std::find(product->bmtfMb34MatchedHoIndex.begin(), product->bmtfMb34MatchedHoIndex.end(), iHo) != product->bmtfMb34MatchedHoIndex.end()) { continue;}

				const double &bmtfMb34MatchedHoDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(Utility::Bmtf).at(iBmtf), product->tfMuonCmsPhi.at(Utility::Bmtf).at(iBmtf), product->hcalCmsEta.at(iHo), product->hcalCmsPhi.at(iHo));

				if (bmtfMb34MatchedHoDeltaR < std::abs(product->bmtfMb34MatchedHoDeltaR.at(iBmtf))) {
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
				if (product->tfMatchedMuonIndex.at(Utility::Bmtf).at(iBmtf) != 999) {
					unsigned int iMuon = product->tfMatchedMuonIndex.at(Utility::Bmtf).at(iBmtf);
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

			for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) {
				if (product->dttpCmsPt.at(iDttp) < l1PtCut) { continue;}
				// No HoMb34 coincidence unless hits are in MB3 or MB4
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

				if (product->dttpStation.at(iDttp) == 3 && std::abs(bmtfMb34MatchedHoDeltaPhi) < std::abs(product->bmtfMb3MatchedHoDeltaPhi.at(iBmtf))) {
					product->isMb3HoIEtaMatched.at(iBmtf) = true;
					product->bmtfMb3MatchedHoDeltaPhi.at(iBmtf) = bmtfMb34MatchedHoDeltaPhi;
					product->bmtfMb3MatchedHoDeltaIPhi.at(iBmtf) = Utility::DeltaIPhi(product->bmtfMb34MatchedHoIPhi.at(iBmtf), product->dttpIPhi.at(iDttp));
				} else if (product->dttpStation.at(iDttp) == 4 && std::abs(bmtfMb34MatchedHoDeltaPhi) < std::abs(product->bmtfMb4MatchedHoDeltaPhi.at(iBmtf))) {
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
			product->dttpCmsPt.at(iDttp) < l1PtCut
		) { continue;}

		unsigned int dttpMatchedHoIndex = 99999;
		for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
			//unsigned int tmpHo = iHo;
			//tmpHo = product->nHcalDetIds - iHo - 1;

			if (product->isDttpMatchedHo.at(iDttp)) { continue;}

			const int deltaIPhi = Utility::DeltaIPhi(product->dttpIPhi.at(iDttp), product->hcalIPhi.at(iHo));
			const double deltaPhi = Utility::DeltaPhi(product->dttpCmsPhi.at(iDttp), product->hcalCmsPhi.at(iHo));

			if (abs(deltaIPhi) < abs(product->dttpMatchedHoDeltaIPhi.at(iDttp))) {
				if (((product->dttpStation.at(iDttp) == 1 && abs(deltaIPhi) <= 1) || (product->dttpStation.at(iDttp) == 2 && abs(deltaIPhi) <= 2)) &&
				//if (((product->dttpStation.at(iDttp) == 1 && abs(deltaIPhi) < 1) || (product->dttpStation.at(iDttp) == 2 && abs(deltaIPhi) < 2)) && // FIXME discuss this
					product->dttpSection.at(iDttp) == product->hcalSection.at(iHo) &&
					product->dttpWheel.at(iDttp) == product->hcalWheel.at(iHo)
				) {
					int nHo3x3Hit = 0;
					for (unsigned int iHo2 = 0; iHo2 < product->nHcalDetIds; iHo2++) {
						if (iHo2 == iHo) { continue;}
						int deltaIPhi2 = Utility::DeltaIPhi(product->hcalIPhi.at(iHo), product->hcalIPhi.at(iHo2));
						if ((product->dttpStation.at(iDttp) == 1 && abs(deltaIPhi2) <= 1) &&
							product->dttpSection.at(iDttp) == product->hcalSection.at(iHo2) &&
							product->dttpWheel.at(iDttp) == product->hcalWheel.at(iHo2)
						) { nHo3x3Hit++; }
					}
					product->dttpHoN3x3Hit.at(iDttp) = nHo3x3Hit;
					product->dttpMatchedHoDeltaIPhi.at(iDttp) = deltaIPhi;
					product->dttpMatchedHoDeltaPhi.at(iDttp) = deltaPhi;
					product->isDttpMatchedHo.at(iDttp) = true;
					product->dttpMatchedHoCmsPhi.at(iDttp) = product->hcalCmsPhi.at(iHo);
					product->dttpMatchedHoCmsEta.at(iDttp) = product->hcalCmsEta.at(iHo);
					product->dttpMatchedHoIPhi.at(iDttp) = product->hcalIPhi.at(iHo);
					product->dttpMatchedHoIEta.at(iDttp) = product->hcalIEta.at(iHo);
					dttpMatchedHoIndex = iHo;
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
				if (product->isDttpMatchedMuon.at(iDttp)) { continue;}
				if (product->probeMuonIEta.at(iMuon) > iEtaCut) { continue;}

				const double &probeMuonEta = product->probeMuonHasMb2.at(iMuon) ? product->probeMuonEtaSt2.at(iMuon) : product->probeMuonEtaSt1.at(iMuon);
				const double &probeMuonPhi = product->probeMuonHasMb2.at(iMuon) ? product->probeMuonPhiSt2.at(iMuon) : product->probeMuonPhiSt1.at(iMuon);
				const double &deltaR = Utility::DeltaR(product->dttpMatchedHoCmsEta.at(iDttp), product->dttpMatchedHoCmsPhi.at(iDttp), probeMuonEta, probeMuonPhi);

				int nHo3x3Hit = 0;
				for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
					int deltaIPhi = Utility::DeltaIPhi(product->dttpMatchedHoIPhi.at(iDttp), product->hcalIPhi.at(iHo));
					int deltaIEta = product->dttpMatchedHoIEta.at(iDttp) - product->hcalIEta.at(iHo);
					if (abs(deltaIEta) <= 1 && abs(deltaIPhi) <= 1) { nHo3x3Hit++;}
				}
				nHo3x3Hit--; // Remove double counting for the matched HOTP

				product->muonHoN3x3Hit.at(iMuon) = nHo3x3Hit;

				if (product->isDttpMatchedMuon.at(iDttp)) { continue;}

				//if (deltaR < std::abs(product->dttpMatchedMuonDeltaR.at(iDttp)) && deltaR < deltaRCut) {
				if (deltaR < std::abs(product->dttpMatchedMuonDeltaR.at(iDttp)) && deltaR < deltaRProbeAndHoCut) {
					product->isDttpMatchedMuon.at(iDttp) = deltaR < deltaRProbeAndHoCut;
					product->dttpMatchedMuonIndex.at(iDttp) = iMuon;
					product->dttpMatchedMuonHoN3x3Hit.at(iDttp) = nHo3x3Hit;
					product->dttpMatchedMuonDeltaR.at(iDttp) = deltaR;
					product->dttpMatchedMuonIndex.at(iDttp) = iMuon;
				}
			}

			if (product->isDttpMatchedMuon.at(iDttp)) {
				product->muonMatchedDttpIndex.at(product->dttpMatchedMuonIndex.at(iDttp)) = iDttp;
				product->isMuonMatchedDttp.at(product->dttpMatchedMuonIndex.at(iDttp)) = true;
				product->muonMatchedDttpHoN3x3Hit.at(product->dttpMatchedMuonIndex.at(iDttp)) = product->dttpMatchedMuonHoN3x3Hit.at(iDttp);
			}
		}
	}
}

void HoCoincidenceProducer::EndJob(HoHistogramCollection* histCollection) {}
