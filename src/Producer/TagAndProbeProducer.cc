#include <HOAnalysis/HOL1/interface/Producer/TagAndProbeProducer.h>

TagAndProbeProducer::TagAndProbeProducer(const double &ptCut, const double &l1PtCut, const double &etaCut, const char &workingPointCut):
	ptCut(ptCut),
	l1PtCut(l1PtCut),
	etaCut(etaCut),
	workingPointCut(workingPointCut)
	{
		Name = "Reco Muon Producer";
		std::map<char, std::string> workingPointMap = {
			{'l', "loose"},
			{'m', "medium"},
			{'t', "tight"},
			{'a', "all"}
		};
		std::cout << "Using " << workingPointMap[workingPointCut] << " Muons." << std::endl;
	}

void TagAndProbeProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {

	product->nMuon = *dataReader->nMuon->Get();
	// Select only events with 2 muons but this might also reduce statistics too much.. But otherwise tag and probe does not make sense
	//if (product->nMuon != 2) { product->nMuon = 0; return;}
	if (product->nMuon < 2) { product->nMuon = 0; return;}


	// Find a tag muon
	unsigned short tagMuonIndex = 999;
	int tagMuonCharge = -999;
	product->tagMuonMatchedBmtfIndex = -999;
	double tagMuonMatchedBmtfDeltaR = -999;
	for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++) {

		bool passesWorkingPoint = false;

		const bool &isLooseMuon = dataReader->muonIsLooseMuon->At(iMuon);
		const bool &isMediumMuon = dataReader->muonIsMediumMuon->At(iMuon);
		const bool &isTightMuon = dataReader->muonIsTightMuon->At(iMuon);

		if (workingPointCut == 'm') {
			passesWorkingPoint = isMediumMuon;
		} else if (workingPointCut == 't') {
			passesWorkingPoint = isTightMuon;
		} else if (workingPointCut == 'l') {
			passesWorkingPoint = isLooseMuon;
		} else if (workingPointCut == 'a') {
			passesWorkingPoint = true;
		} else {
			std::cerr << "Chosen invalid working point!" << std::endl;
		}

		if (passesWorkingPoint) {
			//product->tagMuonMatchedBmtfIndex = iMuon;
			//break;

			//tagMuonIndex = iMuon;
			const double &tagMuonPt = dataReader->muonPt->At(iMuon);
			const double &tagMuonEta = dataReader->muonEta->At(iMuon);
			if (tagMuonPt < ptCut || fabs(tagMuonEta) > etaCut) { continue;}
			//if (tagMuonPt < ptCut || fabs(tagMuonEta) > etaCut) { continue;}
			//tagMuonIndex = iMuon;
			const double &tagMuonPhi = dataReader->muonPhi->At(iMuon);
			const double &tagMuonEtaSt1 = dataReader->muonEtaSt1->At(iMuon);
			const double &tagMuonPhiSt1 = dataReader->muonPhiSt1->At(iMuon);
			const double &tagMuonEtaSt2 = dataReader->muonEtaSt2->At(iMuon);
			const double &tagMuonPhiSt2 = dataReader->muonPhiSt2->At(iMuon);

			////std::cout << std::endl << "Found a " << workingPointCut << " muon(" << tagMuonIndex+1 << "/" << product->nMuon << ")";
			//tagMuonCharge = dataReader->muonCharge->At(iMuon);

			if (product->bmtfSize != 0) {
				for (unsigned short iBmtf = 0; iBmtf < product->bmtfSize; iBmtf++){
					if (product->bmtfBx.at(iBmtf) != 0 && product->bmtfCmsPt.at(iBmtf) < 22) { continue;} //TODO think about pt cut.. probabyl not smart!
					//if (product->bmtfBx.at(iBmtf) != 0 && product->bmtfCmsPt.at(iBmtf) < l1PtCut) { continue;} //TODO think about pt cut.. probabyl not smart!
					if (product->bmtfBx.at(iBmtf) != 0) { continue;}

					std::vector<double> bmtfMatchedMuonDeltaRVec;
					bmtfMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), tagMuonEta, tagMuonPhi));
					bmtfMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), tagMuonEtaSt1, tagMuonPhiSt1));
					bmtfMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), tagMuonEtaSt2, tagMuonPhiSt2));

					const int &matchedStation = std::min_element(bmtfMatchedMuonDeltaRVec.begin(), bmtfMatchedMuonDeltaRVec.end()) - bmtfMatchedMuonDeltaRVec.begin();
					const double &bmtfMatchedMuonDeltaR = bmtfMatchedMuonDeltaRVec.at(matchedStation);

					//const double &bmtfMatchedMuonDeltaR = Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), tagMuonEta, tagMuonPhi);

					//if (bmtfMatchedMuonDeltaR < 0.1 && bmtfMatchedMuonDeltaR < fabs(tagMuonMatchedBmtfDeltaR)) {
					if (bmtfMatchedMuonDeltaR < 0.1 && bmtfMatchedMuonDeltaR < fabs(tagMuonMatchedBmtfDeltaR)) {
						tagMuonIndex = iMuon;
						product->tagMuonMatchedBmtfIndex = iBmtf;
						//std::cout << "TagMuon found!" << std::endl;
					}

				}
			}
		}
		if (product->tagMuonMatchedBmtfIndex > 0) { break; }
	}

	if (product->tagMuonMatchedBmtfIndex > 0) {
	//if (tagMuonIndex < 999) {

		//TODO declare as member of this producer maybe
		const double &muonMass = 0.10571289;
		const double &zBosonMass = 91.1876;
		const double &jPsiMass = 3.096916;

		const float &tagMuonPt = dataReader->muonPt->At(tagMuonIndex);
		const float &tagMuonEta = dataReader->muonEta->At(tagMuonIndex);
		const float &tagMuonPhi = dataReader->muonPhi->At(tagMuonIndex);
		ROOT::Math::PtEtaPhiMVector tagMuonP4 = ROOT::Math::PtEtaPhiMVector(tagMuonPt, tagMuonEta, tagMuonPhi, muonMass);

		bool probeMuonFound = false;
		unsigned short probeMuonIndex = 999; // If you want to use best mass method
		double bestDiMuonMass = -999;
		for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++) {
			if (tagMuonIndex == iMuon) { continue;}
			const int &muonCharge = dataReader->muonCharge->At(iMuon);
			if (tagMuonCharge == muonCharge) { continue;}
			//if (probeMuonFound) { continue;}


			const float &muonPt = dataReader->muonPt->At(iMuon);
			const float &muonEta = dataReader->muonEta->At(iMuon);
			if (muonPt < ptCut || fabs(muonEta) > etaCut) { continue;}
			const float &muonPhi = dataReader->muonPhi->At(iMuon);

			//const int &matchedStation = std::min_element(bmtfMatchedMuonDeltaRVec.begin(), bmtfMatchedMuonDeltaRVec.end()) - bmtfMatchedMuonDeltaRVec.begin();
			const double &probeMuonMatchedMuonDeltaR = Utility::DeltaR(muonEta, muonPhi, tagMuonEta, tagMuonPhi);// probeMuonMatchedMuonDeltaRVec.at(matchedStation);
			if (probeMuonMatchedMuonDeltaR > 0.4) { continue;}

			ROOT::Math::PtEtaPhiMVector muonP4 = ROOT::Math::PtEtaPhiMVector(muonPt, muonEta, muonPhi, muonMass);
			const double &diMuonMass= (tagMuonP4 + muonP4).M();
			//std::cout << std::fixed << std::setprecision(4) << "tagMuon(" << tagMuonIndex << ")\t=\t" << tagMuonP4.M() << ",\tprobeMuon(" << iMuon << ")\t=\t" << muonP4.M() << ",\tDiMuon\t=\t" << diMuonMass << std::endl;


			//if (muonPt < ptCut || fabs(muonEta) > etaCut || !passesWorkingPoint) { continue;}
			//if (!isInMassWindow) { continue;}
			histCollection->histDiMuonMass->Fill(diMuonMass);

			// if is closer to jpsi or not closer to jpsi and closer to zboson
			//bool isJPsi   = fabs(diMuonMass - jPsiMass)   < fabs(bestDiMuonMass - jPsiMass)   && fabs(diMuonMass / jPsiMass   - 1) < 0.32;
			//bool isZBoson = fabs(diMuonMass - zBosonMass) < fabs(bestDiMuonMass - zBosonMass) && fabs(diMuonMass / zBosonMass - 1) < 0.32;
			//bool isJPsi   = fabs(diMuonMass - jPsiMass)   < fabs(bestDiMuonMass - jPsiMass)   && fabs(diMuonMass / jPsiMass   - 1) < fabs(diMuonMass / zBosonMass - 1);
			//bool isZBoson = fabs(diMuonMass - zBosonMass) < fabs(bestDiMuonMass - zBosonMass) && fabs(diMuonMass / zBosonMass - 1) < fabs(diMuonMass / jPsiMass   - 1);
			bool isJPsi   = false;
			bool isZBoson = fabs(diMuonMass - zBosonMass) < fabs(bestDiMuonMass - zBosonMass);

			//bool isJPsi = fabs(diMuonMass - jPsiMass)/jPsiMass < .6; //FIXME THIS ONLY MAKES SENSE TO nmuon==2
			//bool isJPsi = fabs(diMuonMass - zBosonMass) < fabs(bestDiMuonMass - zBosonMass);
			//bool isJPsi = diMuonMass < 6; //FIXME THIS ONLY MAKES SENSE TO nmuon==2
			//bool isJPsi = fabs(diMuonMass - jPsiMass)   < fabs(bestDiMuonMass - jPsiMass);
			//This is good probably but test other stuff for now
			//bool isJPsi   = fabs(diMuonMass - jPsiMass)   < fabs(bestDiMuonMass - jPsiMass)   && fabs(diMuonMass - jPsiMass) / jPsiMass < fabs(diMuonMass - zBosonMass) / zBosonMass;

			//FIXME this is somewhat reasonable maybe
			//bool isJPsi = false;
			//bool isZBoson = fabs(diMuonMass - zBosonMass) < fabs(bestDiMuonMass - zBosonMass) && fabs(diMuonMass - jPsiMass) / jPsiMass > fabs(diMuonMass - zBosonMass) / zBosonMass;
			//bool isZBoson = fabs(diMuonMass - zBosonMass) < fabs(bestDiMuonMass - zBosonMass);
			//std::cout << "isJpsi = " << isJPsi << "; isZBoson = " << isZBoson << std::endl;

			// FIXME this is probably a good idea but stats are just too low..
			////TEst to just cut out a window
			//if (isJPsi) {
			//	isJPsi   = fabs(diMuonMass - jPsiMass)   / jPsiMass   < 0.32;
			//} else {
			//	isZBoson = fabs(diMuonMass - zBosonMass) / zBosonMass < 0.32;
			//}

			//std::cout << std::fixed << std::setprecision(4) << std::endl << product->nMuon << "\tmass(" << iMuon << ", " << tagMuonIndex << ")\t=\t" << diMuonMass << "\t" << (diMuonMass - jPsiMass) << "\t" << (diMuonMass - zBosonMass) << "\t" << (diMuonMass - jPsiMass) / jPsiMass << "\t" << (diMuonMass - zBosonMass) / zBosonMass;
			//std::cout << std::endl << std::fixed << std::setprecision(4) << std::endl << product->nMuon << "\tmass(" << iMuon << ", " << tagMuonIndex << ")\t=\t" << diMuonMass << "\t?=\t" << zBosonMass << "; " << "\t" << fabs(diMuonMass - zBosonMass) << "\t" << fabs(diMuonMass - zBosonMass) / zBosonMass;

			if (isJPsi) {
				probeMuonIndex = iMuon;
				bestDiMuonMass = diMuonMass;
				probeMuonFound = true;
				//std::cout << std::fixed << std::setprecision(4) << std::endl << product->nMuon << "\tjPsi mass(" << iMuon << ", " << tagMuonIndex << ")\t=\t" << diMuonMass << "\t" << (diMuonMass - jPsiMass) / jPsiMass << "\t" << (diMuonMass - zBosonMass) / zBosonMass;
				std::cout << std::fixed << std::setprecision(4) << std::endl << product->nMuon << " mass(" << iMuon << ", " << tagMuonIndex << ")\t=\t" << diMuonMass << "\t" << fabs(diMuonMass - jPsiMass) / jPsiMass << "\t" << fabs(diMuonMass - zBosonMass) / zBosonMass;
				std::cout << "\tIs a jpsi!" << std::endl;
			//}
			} else if (isZBoson) {
				probeMuonIndex = iMuon;
				bestDiMuonMass = diMuonMass;
				probeMuonFound = true;
				std::cout << std::fixed << std::setprecision(4) << std::endl << product->nMuon << " mass(p=" << iMuon << ", t=" << tagMuonIndex << ") =\t" << diMuonMass << "\t" << (diMuonMass - jPsiMass) / jPsiMass << "\t" << (diMuonMass - zBosonMass) / zBosonMass;
				std::cout << "\tIs a zboson!" << std::endl;
			}
		}

		if (probeMuonFound) {
			std::cout << "Probe Muon Found!" << std::endl;
			unsigned short iMuon = probeMuonIndex;

			const float &muonPt = dataReader->muonPt->At(iMuon);
			const float &muonEta = dataReader->muonEta->At(iMuon);
			const float &muonPhi = dataReader->muonPhi->At(iMuon);

			const bool &isLooseMuon = dataReader->muonIsLooseMuon->At(iMuon);
			const bool &isMediumMuon = dataReader->muonIsMediumMuon->At(iMuon);
			const bool &isTightMuon = dataReader->muonIsTightMuon->At(iMuon);

			const int &muonCharge = dataReader->muonCharge->At(iMuon);
			histCollection->histSelectedDiMuonMass->Fill(bestDiMuonMass);

			product->isLooseMuon.push_back(isLooseMuon);
			product->isMediumMuon.push_back(isMediumMuon);
			product->isTightMuon.push_back(isTightMuon);
			product->muonHltIsoMu.push_back(dataReader->muonHlt_isomu->At(iMuon));
			product->muonHltMu.push_back(dataReader->muonHlt_mu->At(iMuon));
			product->muonPassesSingleMuon.push_back(dataReader->muonPassesSingleMuon->At(iMuon));
			product->muonCharge.push_back(muonCharge);
			//product->muonCharge.push_back(dataReader->muonCharge->At(iMuon));
			product->muonE.push_back(dataReader->muonE->At(iMuon));
			product->muonEt.push_back(dataReader->muonEt->At(iMuon));
			product->muonPt.push_back(muonPt);
			product->muonEta.push_back(muonEta);
			product->muonPhi.push_back(muonPhi);
			product->muonIso.push_back(dataReader->muonIso->At(iMuon));
			product->muonHltIsoDeltaR.push_back(dataReader->muonHlt_isoDeltaR->At(iMuon));
			product->muonDeltaR.push_back(dataReader->muonHlt_deltaR->At(iMuon));
			product->muonEtaSt1.push_back(dataReader->muonEtaSt1->At(iMuon));
			product->muonPhiSt1.push_back(dataReader->muonPhiSt1->At(iMuon));
			product->muonEtaSt2.push_back(dataReader->muonEtaSt2->At(iMuon));
			product->muonPhiSt2.push_back(dataReader->muonPhiSt2->At(iMuon));
			product->muonMet.push_back(dataReader->muonMet->At(iMuon));
			product->muonMt.push_back(dataReader->muonMt->At(iMuon));

			product->muonIEta.push_back(Utility::CmsEtaToHoIEta(product->muonEta.back()));
			product->muonHasMb1.push_back((fabs(product->muonEtaSt1.back()) < 5) && (fabs(product->muonPhiSt1.back()) < M_PI));
			product->muonHasMb2.push_back((fabs(product->muonEtaSt2.back()) < 5) && (fabs(product->muonPhiSt2.back()) < M_PI));

			histCollection->histMuonMet->Fill(product->muonMet.back());
			histCollection->histMuonMt->Fill(product->muonMt.back());

			histCollection->histIsLooseMuon->Fill(product->isLooseMuon.back());
			histCollection->histIsMediumMuon->Fill(product->isMediumMuon.back());
			histCollection->histIsTightMuon->Fill(product->isTightMuon.back());
			histCollection->histMuonHltIsoMu->Fill(product->muonHltIsoMu.back());
			histCollection->histMuonHltMu->Fill(product->muonHltMu.back());
			histCollection->histMuonPassesSingleMuon->Fill(product->muonPassesSingleMuon.back());
			histCollection->histMuonCharge->Fill(product->muonCharge.back());

			histCollection->histMuonE->Fill(product->muonE.back());
			histCollection->histMuonEt->Fill(product->muonEt.back());
			histCollection->histMuonPt->Fill(product->muonPt.back());
			histCollection->histMuonPt20->Fill(product->muonPt.back());
			histCollection->histMuonEta->Fill(product->muonEta.back());
			histCollection->histMuonPhi->Fill(product->muonPhi.back());
			histCollection->histMuonIso->Fill(product->muonIso.back());
			histCollection->histMuonHltIsoDeltaR->Fill(product->muonHltIsoDeltaR.back());
			histCollection->histMuonDeltaR->Fill(product->muonDeltaR.back());
			histCollection->histMuonEtaSt1->Fill(product->muonEtaSt1.back());
			histCollection->histMuonPhiSt1->Fill(product->muonPhiSt1.back());
			histCollection->histMuonEtaSt2->Fill(product->muonEtaSt2.back());
			histCollection->histMuonPhiSt2->Fill(product->muonPhiSt2.back());

			histCollection->histMuonIEta->Fill(product->muonIEta.back());
		}
	}
	product->nMuon = product->muonPt.size();
	//std::cout << std::endl << "muonPt = ";
	//std::cout << "n_muon = " << product->nMuon << std::endl;
}

void TagAndProbeProducer::EndJob(HoHistogramCollection* histCollection) {}
TagAndProbeProducer::~TagAndProbeProducer() {}
