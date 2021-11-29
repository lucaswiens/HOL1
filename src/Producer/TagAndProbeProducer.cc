#include <HOAnalysis/HOL1/interface/Producer/TagAndProbeProducer.h>

TagAndProbeProducer::TagAndProbeProducer(const double &ptCut, const double &etaCut, const char &workingPointCut):
	ptCut(ptCut),
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
			//tagMuonIndex = iMuon;
			const double &tagMuonEta = dataReader->muonEta->At(iMuon);
			const double &tagMuonPhi = dataReader->muonPhi->At(iMuon);
			const double &tagMuonEtaSt1 = dataReader->muonEtaSt1->At(iMuon);
			const double &tagMuonPhiSt1 = dataReader->muonPhiSt1->At(iMuon);
			const double &tagMuonEtaSt2 = dataReader->muonEtaSt2->At(iMuon);
			const double &tagMuonPhiSt2 = dataReader->muonPhiSt2->At(iMuon);

			//std::cout << std::endl << "Found a " << workingPointCut << " muon(" << tagMuonIndex+1 << "/" << product->nMuon << ")";
			tagMuonCharge = dataReader->muonCharge->At(iMuon);

			if (product->bmtfSize != 0) {
				for (unsigned short iBmtf = 0; iBmtf < product->bmtfSize; iBmtf++){
					//if (product->bmtfBx.at(iBmtf) != 0 && product->bmtfCmsPt.at(iBmtf) > 24) { continue;} //TODO think about pt cut.. probabyl not smart!
					if (product->bmtfBx.at(iBmtf) != 0) { continue;}

					std::vector<double> bmtfMatchedMuonDeltaRVec;
					bmtfMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), tagMuonEta, tagMuonPhi));
					bmtfMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), tagMuonEtaSt1, tagMuonPhiSt1));
					bmtfMatchedMuonDeltaRVec.push_back(Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), tagMuonEtaSt2, tagMuonPhiSt2));

					const int &matchedStation = std::min_element(bmtfMatchedMuonDeltaRVec.begin(), bmtfMatchedMuonDeltaRVec.end()) - bmtfMatchedMuonDeltaRVec.begin();
					const double &bmtfMatchedMuonDeltaR = bmtfMatchedMuonDeltaRVec.at(matchedStation);

					//const double &bmtfMatchedMuonDeltaR = Utility::DeltaR(product->bmtfCmsEta.at(iBmtf), product->bmtfCmsPhi.at(iBmtf), tagMuonEta, tagMuonPhi);

					if (bmtfMatchedMuonDeltaR < 0.1 && bmtfMatchedMuonDeltaR < fabs(tagMuonMatchedBmtfDeltaR)) {
						tagMuonIndex = iMuon;
						product->tagMuonMatchedBmtfIndex = iBmtf;
					}

				}
			}
			if (product->tagMuonMatchedBmtfIndex) { break; }
		}
	}

	//if (product->tagMuonMatchedBmtfIndex > 0) {
	if (tagMuonIndex < 999) {

		//TODO declare as member of this producer maybe
		const double &muonMass = 0.10571289;
		const double &zBosonMass = 91.1876;
		const double &jPsiMass = 3.096916;

		const float &tagMuonPt = dataReader->muonPt->At(tagMuonIndex);
		const float &tagMuonEta = dataReader->muonEta->At(tagMuonIndex);
		const float &tagMuonPhi = dataReader->muonPhi->At(tagMuonIndex);
		ROOT::Math::PtEtaPhiMVector tagMuonP4 = ROOT::Math::PtEtaPhiMVector(tagMuonPt, tagMuonEta, tagMuonPhi, muonMass);

		bool probedMuonFound = false;
		unsigned short probedMuonIndex = 999; // If you want to use best mass method
		double bestDiMuonMass = -999;
		for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++) {
			if (tagMuonIndex == iMuon) { continue;}
			const int &muonCharge = dataReader->muonCharge->At(iMuon);
			if (tagMuonCharge == muonCharge) { continue;}
			//if (probedMuonFound) { continue;}


			const float &muonPt = dataReader->muonPt->At(iMuon);
			const float &muonEta = dataReader->muonEta->At(iMuon);
			const float &muonPhi = dataReader->muonPhi->At(iMuon);

			//const int &matchedStation = std::min_element(bmtfMatchedMuonDeltaRVec.begin(), bmtfMatchedMuonDeltaRVec.end()) - bmtfMatchedMuonDeltaRVec.begin();
			const double &probeMuonMatchedMuonDeltaR = Utility::DeltaR(muonEta, muonPhi, tagMuonEta, tagMuonPhi);// probeMuonMatchedMuonDeltaRVec.at(matchedStation);
			if (probeMuonMatchedMuonDeltaR > 0.4) { continue;}

			ROOT::Math::PtEtaPhiMVector muonP4 = ROOT::Math::PtEtaPhiMVector(muonPt, muonEta, muonPhi, muonMass);
			const double &diMuonMass= (tagMuonP4 + muonP4).M();

			histCollection->histDiMuonMass->Fill(diMuonMass);

			//if (muonPt < ptCut || fabs(muonEta) > etaCut || !passesWorkingPoint) { continue;}
			if (muonPt < ptCut || fabs(muonEta) > etaCut) { continue;}
			//if (!isInMassWindow) { continue;}

			// if is closer to jpsi or not closer to jpsi and closer to zboson
			//bool isJPsi   = fabs(diMuonMass - jPsiMass)   < fabs(bestDiMuonMass - jPsiMass)   && fabs(diMuonMass / jPsiMass   - 1) < 0.32;
			//bool isZBoson = fabs(diMuonMass - zBosonMass) < fabs(bestDiMuonMass - zBosonMass) && fabs(diMuonMass / zBosonMass - 1) < 0.32;

			bool isJPsi   = fabs(diMuonMass - jPsiMass)   < fabs(bestDiMuonMass - jPsiMass)   && fabs(diMuonMass - jPsiMass) / jPsiMass < fabs(diMuonMass - zBosonMass) / zBosonMass;
			bool isZBoson = fabs(diMuonMass - zBosonMass) < fabs(bestDiMuonMass - zBosonMass) && fabs(diMuonMass - jPsiMass) / jPsiMass > fabs(diMuonMass - zBosonMass) / zBosonMass;

			//std::cout << std::fixed << std::setprecision(4) << std::endl << product->nMuon << "\tmass(" << iMuon << ", " << tagMuonIndex << ") =\t" << diMuonMass << "\t" << (diMuonMass - jPsiMass) << "\t" << (diMuonMass - zBosonMass) << "\t" << (diMuonMass - jPsiMass) / jPsiMass << "\t" << (diMuonMass - zBosonMass) / zBosonMass;
			if (isJPsi) {
				probedMuonIndex = iMuon;
				bestDiMuonMass = diMuonMass;
				probedMuonFound = true;
				//std::cout << std::fixed << std::setprecision(4) << std::endl << product->nMuon << "\tjPsi mass(" << iMuon << ", " << tagMuonIndex << ") =\t" << diMuonMass << "\t" << (diMuonMass - jPsiMass) / jPsiMass << "\t" << (diMuonMass - zBosonMass) / zBosonMass;
				//std::cout << "Is a jpsi!" << std::endl;
			} else if (isZBoson) {
				probedMuonIndex = iMuon;
				bestDiMuonMass = diMuonMass;
				probedMuonFound = true;
				//std::cout << std::fixed << std::setprecision(4) << std::endl << product->nMuon << "\tZ    mass(" << iMuon << ", " << tagMuonIndex << ") =\t" << diMuonMass << "\t" << (diMuonMass - jPsiMass) / jPsiMass << "\t" << (diMuonMass - zBosonMass) / zBosonMass;
				//std::cout << "Is a zboson!" << std::endl;
			}
		}

		if (probedMuonFound) {
			unsigned short iMuon = probedMuonIndex;

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
