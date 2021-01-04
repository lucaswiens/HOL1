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
void HoCoincidenceProducer::Produce(DataReader* dataReader, HoProduct* product) {
	// Match BMTF with DTTP and Reco Muons
	product->isBmtfMatchedDttp = std::vector(product->bmtfSize, false);
	product->isBmtfMatchedMuon = std::vector(product->bmtfSize, false);
	product->isDttpMatchedBmtf = std::vector(product->dttpSize, false);
	product->isDttpMatchedMuon = std::vector(product->dttpSize, false);
	product->isMuonMatchedBmtf = std::vector(product->nMuon, false);
	product->isMuonMatchedDttp = std::vector(product->nMuon, false);
	for (unsigned short iBmtf = 0; iBmtf < product->bmtfSize; iBmtf++){
		if (product->bmtfBx.at(iBmtf)) { continue;}

		double bmtfMatchedDttpPt = -999, bmtfMatchedDttpPhi = -999, bmtfMatchedDttpCmsPhi = -999, bmtfMatchedDttpDeltaPhiMin = -999;
		bool isDttpMatchedBmtf = false;
		for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) {
			if (product->dttpBx.at(iDttp) != 0 &&
				isDttpMatchedBmtf
			) { continue;}

			for (int iBmtfStation = 0; iBmtfStation <= 3; iBmtfStation++) {
				// Skip if already associated to a BMTF
				if (product->isDttpMatchedBmtf.at(iDttp)) { continue;}
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
				if (fabs(bmtfMatchedDttpDeltaPhi) < fabs(bmtfMatchedDttpDeltaPhiMin)) {
					bmtfMatchedDttpDeltaPhiMin = bmtfMatchedDttpDeltaPhi;
					bmtfMatchedDttpPt = product->dttpPt.at(iDttp);
					bmtfMatchedDttpPhi = product->dttpPhi.at(iDttp);
					bmtfMatchedDttpCmsPhi = product->dttpCmsPhi.at(iDttp);
					isDttpMatchedBmtf = true;
				}
			}
			product->isDttpMatchedBmtf.at(iDttp) = isDttpMatchedBmtf;
		}

		product->isDttpMatchedBmtf.at(iBmtf) = isDttpMatchedBmtf;
		product->bmtfMatchedDttpDeltaPhi.push_back(bmtfMatchedDttpDeltaPhiMin);
		product->bmtfMatchedDttpPt.push_back(bmtfMatchedDttpPt);
		product->bmtfMatchedDttpPhi.push_back(bmtfMatchedDttpPhi);
		product->bmtfMatchedDttpCmsPhi.push_back(bmtfMatchedDttpCmsPhi);

		if (product->bmtfCmsPt.at(iBmtf) < 0 || fabs(product->bmtfCmsEta.at(iBmtf)) > 0.83) { continue;}

		double bmtfMatchedMuonDeltaRMin = 999;
		double bmtfMatchedMuonPt = -999, bmtfMatchedMuonEta = -999, bmtfMatchedMuonPhi = -999;
		//int bmtfMatchedMuonTrackType = -999, bmtfMatchedMuonCharge = -999;
		int bmtfMatchedMuonCharge = -999;
		double bmtfMatchedMuonDeltaPhi = -999;
		bool isMuonMatchedBmtf = false;
		for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++){
			if (isMuonMatchedBmtf){ continue;}
			if (!product->isMediumMuon.at(iMuon) &&
				!product->muonHasMb1.at(iMuon) &&
				product->muonIEta.at(iMuon) > 10
			) { continue;}

			//TODO are these needed?
			//double mb1MatchedMuonDeltaEta = product->muonEta .at(iMuon) - product->muonEtaSt1.at(iMuon);
			//double mb1MatchedMuonDeltaPhi = Utility::DeltaPhi(product->muonPhi.at(iMuon), product->muonPhiSt1.at(iMuon));

			const double &bmtfMuonDeltaPhi = Utility::DeltaPhi(product->bmtfCmsPhi.at(iBmtf), product->muonPhi.at(iMuon));
			const double &bmtfMatchedMuonDeltaR = Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), product->muonEta.at(iMuon), product->muonPhi.at(iMuon));

			if (bmtfMatchedMuonDeltaR < bmtfMatchedMuonDeltaRMin) {
				bmtfMatchedMuonDeltaRMin = bmtfMatchedMuonDeltaR;
				bmtfMatchedMuonPt = product->muonPt.at(iMuon);
				bmtfMatchedMuonEta = product->muonEta.at(iMuon);
				bmtfMatchedMuonPhi = product->muonPhi.at(iMuon);
				bmtfMatchedMuonCharge = product->muonCharge.at(iMuon);
				//bmtfMatchedMuonTrackType = bmtfTrackType;
				bmtfMatchedMuonDeltaPhi = bmtfMuonDeltaPhi;
				isMuonMatchedBmtf = bmtfMatchedMuonDeltaRMin < 0.4;

				product->isMuonMatchedBmtf.at(iMuon) = isMuonMatchedBmtf;
			}
		}

		product->isBmtfMatchedMuon.at(iBmtf) = isMuonMatchedBmtf;
		product->bmtfMatchedMuonDeltaR.push_back(bmtfMatchedMuonDeltaRMin);
		product->bmtfMatchedMuonPt.push_back(bmtfMatchedMuonPt);
		product->bmtfMatchedMuonEta.push_back(bmtfMatchedMuonEta);
		product->bmtfMatchedMuonPhi.push_back(bmtfMatchedMuonPhi);
		product->bmtfMatchedMuonCharge.push_back(bmtfMatchedMuonCharge);
		//product->bmtfMatchedMuonTrackType.push_back(bmtfMatchedMuonTrackType);
		product->bmtfMatchedMuonDeltaPhi.push_back(bmtfMatchedMuonDeltaPhi);
		//product->bmtfMatchedMuonIndex.push_back(bmtfMatchedMuonIndex);
	}

	for (unsigned short iBmtf = 0; iBmtf < product->bmtfSize; iBmtf++){
		// BMTF Tracks with Hits only in MB3 and MB4
		if(product->bmtfTrackerAddresses.at(iBmtf).at(0) == 3 &&
			product->bmtfTrackerAddresses.at(iBmtf).at(1) == 15 &&
			product->bmtfTrackerAddresses.at(iBmtf).at(2) != 15 &&
			product->bmtfTrackerAddresses.at(iBmtf).at(3) != 15
		) {
			double bmtfMb34MatchedHoDeltaRMin = 999, bmtfMb34MatchedHoPt = -999, bmtfMb34MatchedHoCmsEta = -999, bmtfMb34MatchedHoCmsPhi = -999, bmtfMb34MatchedMuonPt = -999, bmtfMb34MatchedMuonEta = -999, bmtfMb34MatchedMuonPhi = -999, bmtfMb34MatchedMuonDeltaPhi;
			int bmtfMb34MatchedHoIEta = -999, bmtfMb34MatchedHoIPhi = -999;
			bool isBmtfMb34HoMatched = false;
			for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
				const double &bmtfMb34MatchedHoDeltaR = Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), product->hcalCmsEta.at(iHo), product->hcalCmsPhi.at(iHo));
				if (bmtfMb34MatchedHoDeltaR < bmtfMb34MatchedHoDeltaRMin) {
					bmtfMb34MatchedHoDeltaRMin = bmtfMb34MatchedHoDeltaR;
					//bmtfMb34MatchedHoPt = product->hcalPt.at(iHo)
					bmtfMb34MatchedHoCmsEta = product->hcalCmsEta.at(iHo);
					bmtfMb34MatchedHoCmsPhi = product->hcalCmsPhi.at(iHo);
					bmtfMb34MatchedHoIEta = product->hcalIEta.at(iHo);
					bmtfMb34MatchedHoIPhi = product->hcalIPhi.at(iHo);
					isBmtfMb34HoMatched = bmtfMb34MatchedHoDeltaRMin < 0.4;
					// Store the muon variables matched to this particular BMTF Muon
					bmtfMb34MatchedMuonPt = product->bmtfMatchedMuonPt.at(iBmtf);
					bmtfMb34MatchedMuonEta = product->bmtfMatchedMuonEta.at(iBmtf);
					bmtfMb34MatchedMuonPhi = product->bmtfMatchedMuonPhi.at(iBmtf);
					bmtfMb34MatchedMuonDeltaPhi = product->bmtfMatchedMuonDeltaPhi.at(iBmtf);
				}
			}
			product->bmtfMb34MatchedHoDeltaR.push_back(bmtfMb34MatchedHoDeltaRMin);
			product->bmtfMb34MatchedHoPt.push_back(bmtfMb34MatchedHoPt);
			product->bmtfMb34MatchedHoCmsEta.push_back(bmtfMb34MatchedHoCmsEta);
			product->bmtfMb34MatchedHoCmsPhi.push_back(bmtfMb34MatchedHoCmsPhi);
			product->bmtfMb34MatchedHoIEta.push_back(bmtfMb34MatchedHoIEta);
			product->bmtfMb34MatchedHoIPhi.push_back(bmtfMb34MatchedHoIPhi);
			product->bmtfMb34MatchedHoPt.push_back(bmtfMb34MatchedHoPt);
			product->bmtfMb34MatchedMuonPt.push_back(bmtfMb34MatchedMuonPt);
			product->bmtfMb34MatchedMuonEta.push_back(bmtfMb34MatchedMuonEta);
			product->bmtfMb34MatchedMuonPhi.push_back(bmtfMb34MatchedMuonPhi);
			product->bmtfMb34MatchedMuonDeltaPhi.push_back(bmtfMb34MatchedMuonDeltaPhi);


			if (!isBmtfMb34HoMatched && abs(bmtfMb34MatchedHoIEta) > 10) { continue;}

			bool isMb3HoIEtaMatched = false, isMb4HoIEtaMatched = false;
			double bmtfMb3MatchedHoDeltaPhiMin = -999, bmtfMb4MatchedHoDeltaPhiMin = -999;
			int bmtfMb3MatchedHoDeltaIPhi = -999, bmtfMb4MatchedHoDeltaIPhi = -999;
			for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) { // No HoMb34 coincidence unless hits are in MB3 or MB4
				if(product->dttpStation.at(iDttp) != 3 && product->dttpStation.at(iDttp) != 4) { continue;}
				// If its outside the 5 wheels, there are no HO hits
				if(abs(product->dttpWheel.at(iDttp)) > 2) { continue;}
				// HO in iEta1/2, MB3/4 has to be in wheel 0
				if(abs(bmtfMb34MatchedHoIEta) < 3 && abs(product->dttpWheel.at(iDttp)) != 0) { continue;}
				// HO in iEta3, MB3 has to be wheel 0/1
				else if(abs(bmtfMb34MatchedHoIEta) == 3 && product->dttpStation.at(iDttp) == 3 && abs(product->dttpWheel.at(iDttp)) == 2) { continue;}
				// HO in iEta3, MB4 has to be wheel 1
				else if(abs(bmtfMb34MatchedHoIEta) == 3 && product->dttpStation.at(iDttp) == 4 && abs(product->dttpWheel.at(iDttp)) != 1) { continue;}
				// HO in iEta4/5/6, MB3/4 in wheel 1
				else if(abs(bmtfMb34MatchedHoIEta) > 3 && abs(bmtfMb34MatchedHoIEta) < 7 && abs(product->dttpWheel.at(iDttp)) != 1) { continue;}
				// HO in iEta7, MB3 has to be wheel 1
				else if(abs(bmtfMb34MatchedHoIEta) == 7 && product->dttpStation.at(iDttp) == 3 && abs(product->dttpWheel.at(iDttp)) != 1) { continue;}
				// HO in iEta7, MB4 has to be wheel 1/2
				else if(abs(bmtfMb34MatchedHoIEta) == 7 && product->dttpStation.at(iDttp) == 4 && abs(product->dttpWheel.at(iDttp)) == 0) { continue;}
				// HO in iEta8/9/10, MB3/4 has to be wheel 2
				else if(abs(bmtfMb34MatchedHoIEta) > 9 && abs(bmtfMb34MatchedHoIEta) < 11 && abs(product->dttpWheel.at(iDttp)) != 2) { continue;}
				// HO Coincidence is geometrically possible

				const double &bmtfMb34HoDeltaPhi = Utility::DeltaPhi(product->bmtfCmsPhi.at(iBmtf), product->dttpPhi.at(iDttp));

				if(product->dttpStation.at(iDttp) == 3 && fabs(bmtfMb34HoDeltaPhi) < fabs(bmtfMb3MatchedHoDeltaPhiMin)) {
					isMb3HoIEtaMatched = true;
					bmtfMb3MatchedHoDeltaPhiMin = bmtfMb34HoDeltaPhi;
					bmtfMb3MatchedHoDeltaIPhi = Utility::DeltaIPhi(bmtfMb34MatchedHoIPhi, product->dttpIPhi.at(iDttp));
				} else if(product->dttpStation.at(iDttp) == 4 && fabs(bmtfMb34HoDeltaPhi) < fabs(bmtfMb4MatchedHoDeltaPhiMin)) {
					isMb4HoIEtaMatched = true;
					bmtfMb4MatchedHoDeltaPhiMin = bmtfMb34HoDeltaPhi;
					bmtfMb4MatchedHoDeltaIPhi = Utility::DeltaIPhi(bmtfMb34MatchedHoIPhi, product->dttpIPhi.at(iDttp));
				}

			}

			product->isMb3HoIEtaMatched.push_back(isMb3HoIEtaMatched);
			product->isMb4HoIEtaMatched.push_back(isMb4HoIEtaMatched);
			if (isMb3HoIEtaMatched) {
				product->bmtfMb34MatchedHoDeltaPhi.push_back(bmtfMb3MatchedHoDeltaPhiMin);
				product->bmtfMb34MatchedHoDeltaIPhi.push_back(bmtfMb3MatchedHoDeltaIPhi);
			} else if (isMb4HoIEtaMatched) {
				product->bmtfMb34MatchedHoDeltaPhi.push_back(bmtfMb4MatchedHoDeltaPhiMin);
				product->bmtfMb34MatchedHoDeltaIPhi.push_back(bmtfMb4MatchedHoDeltaIPhi);
			} else {
				product->bmtfMb34MatchedHoDeltaPhi.push_back(-999);
				product->bmtfMb34MatchedHoDeltaIPhi.push_back(-999);
			}
		}
		//} //BMTF matched to Reco Muon
	}

	for (int iDttp = 0; iDttp < product->dttpSize; iDttp ++) {
		// isDttpMatchedBmtf means used BMTF Muon
		// try to recover unused muons using HO
		if (product->dttpBx.at(iDttp) != 0 &&
			product->dttpStation.at(iDttp) > 2 &&
			abs(product->dttpWheel.at(iDttp)) == 2 &&
			!product->dttpIsHq.at(iDttp) &&
			!product->isDttpMatchedBmtf.at(iDttp) &&
			product->dttpPt.at(iDttp) > 0
		) { continue;}

		bool isDttpMatchedHo = false;
		int dttpMatchedHoDeltaIPhiMin = -999, dttpMatchedHoIPhi, dttpMatchedHoIEta;
		double dttpMatchedHoCmsPhi = -999, dttpMatchedHoCmsEta = -999;
		for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
			if (isDttpMatchedHo) { break;}
			//TODO what is hoTPdigi_bits
			//if(input->v_hoTPdigi_bits->at(iHOTP) != HOTP_bits_SOI)
			const int deltaIPhi = Utility::DeltaIPhi(product->dttpIPhi.at(iDttp), product->hcalIPhi.at(iHo));
			if (abs(deltaIPhi) < abs(dttpMatchedHoDeltaIPhiMin)) {
				dttpMatchedHoDeltaIPhiMin = deltaIPhi;
				if (((product->dttpStation.at(iDttp) == 1 && abs(dttpMatchedHoDeltaIPhiMin) <= 1) || (product->dttpStation.at(iDttp) == 2 && abs(dttpMatchedHoDeltaIPhiMin) <= 2)) &&
					product->dttpSection == product->hcalSection &&
					product->dttpWheel == product->hcalWheel
				) {
					isDttpMatchedHo = true;
					dttpMatchedHoCmsPhi = product->hcalCmsPhi.at(iHo);
					dttpMatchedHoCmsEta = product->hcalCmsEta.at(iHo);
					dttpMatchedHoIPhi = product->hcalIPhi.at(iHo);
					dttpMatchedHoIEta = product->hcalIEta.at(iHo);
				}
			}
		}
		product->isDttpMatchedHo.push_back(isDttpMatchedHo);
		product->dttpMatchedHoCmsPhi.push_back(dttpMatchedHoCmsPhi);
		product->dttpMatchedHoCmsEta.push_back(dttpMatchedHoCmsEta);
		product->dttpMatchedHoDeltaIPhi.push_back(dttpMatchedHoDeltaIPhiMin);
		product->dttpMatchedHoIPhi.push_back(dttpMatchedHoIPhi);
		product->dttpMatchedHoIEta.push_back(dttpMatchedHoIEta);

		if (product->isDttpMatchedHo.at(iDttp)) { continue;}

		double dttpMatchedMuonDeltaRMin = 999;
		bool isMuonMatchedDttp = false;
		//int dttpMatchedMuonIndex = -999;
		for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++){
			if (!product->isMediumMuon.at(iMuon) &&
				!product->muonHasMb1.at(iMuon) &&
				product->muonIEta.at(iMuon) > 10 &&
				!isMuonMatchedDttp
			) { continue;}
			const double &deltaR = Utility::DeltaR(product->hcalCmsEta.at(iDttp), product->hcalCmsPhi.at(iDttp), product->muonEta.at(iMuon), product->muonPhi.at(iMuon));
			if (deltaR < dttpMatchedMuonDeltaRMin) {
				dttpMatchedMuonDeltaRMin = deltaR;
				//dttpMatchedMuonIndex = iMuon;
				isMuonMatchedDttp = true;
				product->isMuonMatchedDttp.at(iMuon) = isMuonMatchedDttp;
			}

			int nHo3x3Hit = 0;
			for (unsigned int iHo = 0; iHo < product->nHcalDetIds; iHo++) {
				//if(v_HOTP_bits->at(iHOTP) != HOTP_bits_SOI) { continue;}
				int deltaIPhi = Utility::DeltaIPhi(product->dttpMatchedHoIPhi.at(iDttp), product->hcalIPhi.at(iHo));
				int deltaIEta = product->dttpMatchedHoIEta.at(iDttp) - product->hcalIEta.at(iHo);
				if(abs(deltaIEta) <= 1 && abs(deltaIPhi) <= 1) { nHo3x3Hit++;}
			}
			// Remove double counting for the same hit (deltaIPhi == 0 && deltaIEta == 0)
			nHo3x3Hit--;

			if (dttpMatchedMuonDeltaRMin > 0.4) { continue;}
			product->nHo3x3Hit.push_back(nHo3x3Hit);
		}
	}

	for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++){
		//if(std::find(bmtfMatchedMuonIndex.begin(), bmtfMatchedMuonIndex.end(), iMuon) != bmtfMatchedMuonIndex.end()) { continue;}
		//if(std::find(dttpMatchedMuonIndex.begin(), dttpMatchedMuonIndex.end(), iMuon) != dttpMatchedMuonIndex.end()) { continue;}
		//unused muons
		if (product->isMuonMatchedBmtf.at(iMuon) || product->isMuonMatchedDttp.at(iMuon)) {
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
	}
}
