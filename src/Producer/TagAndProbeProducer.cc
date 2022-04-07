#include <HOAnalysis/HOL1/interface/Producer/TagAndProbeProducer.h>

TagAndProbeProducer::TagAndProbeProducer(const double &ptCut, const double &l1PtCut, const double &etaCut, const char &workingPointCut):
	ptCut(ptCut),
	l1PtCut(l1PtCut),
	etaCut(etaCut),
	workingPointCut(workingPointCut)
	{
		Name = "Tag and Probe Producer";
		std::map<char, std::string> workingPointMap = {
			{'l', "loose"},
			{'m', "medium"},
			{'t', "tight"},
			{'a', "all"}
		};
		std::cout << "Using " << workingPointMap[workingPointCut] << " Muons." << std::endl;
	}

void TagAndProbeProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	if (product->nMuon < 2) { product->nMuon = 0; return;}
	const double &deltaRCut = 0.4;//FIXME Add this as an argument to the constructor

	// Tag Muons
	std::vector<unsigned short> tagIndices;
	std::vector<unsigned short> probeIndices;
	for (unsigned short iTag = 0; iTag < product->nMuon; iTag++) {
		//Only get muons that have eta and phi variables propagated to the second station
		const double &tagMuonEtaSt1 = product->muonEtaSt1.at(iTag);
		const double &tagMuonPhiSt1 = product->muonPhiSt1.at(iTag);
		const bool &hasMB1 = (tagMuonEtaSt1 > -99) && (tagMuonPhiSt1 > -99);

		const double &tagMuonEtaSt2 = product->muonEtaSt2.at(iTag);
		const double &tagMuonPhiSt2 = product->muonPhiSt2.at(iTag);
		const bool &hasMB2 = (tagMuonEtaSt2 > -99) && (tagMuonPhiSt2 > -99);

		if (!(hasMB1 or hasMB2)) { continue;}

		bool passesWorkingPoint = false;

		const bool &isLooseTagMuon = product->isLooseMuon.at(iTag);
		const bool &isMediumTagMuon = product->isMediumMuon.at(iTag);
		const bool &isTightTagMuon = product->isTightMuon.at(iTag);
		if (workingPointCut == 'm') {
			passesWorkingPoint = isMediumTagMuon;
		} else if (workingPointCut == 't') {
			passesWorkingPoint = isTightTagMuon;
		} else if (workingPointCut == 'l') {
			passesWorkingPoint = isLooseTagMuon;
		} else if (workingPointCut == 'a') {
			passesWorkingPoint = true;
		} else {
			std::cerr << "Chosen invalid working point!" << std::endl;
		}

		if (!passesWorkingPoint) { continue;}

		const bool &isHLTIsoTagMuon = product->muonHltIsoMu.at(iTag);
		if (!isHLTIsoTagMuon) { continue;}

		const double &hltIsoTagMuonDeltaR = product->muonHltIsoDeltaR.at(iTag);
		if (hltIsoTagMuonDeltaR > 0.1) { continue;}

		const double &tagMuonPt = product->muonPt.at(iTag);
		if (tagMuonPt < ptCut) { continue;}

		const double &tagMuonIso = product->muonIso.at(iTag);
		if (tagMuonIso > 0.1) { continue;}

		for (int tfType : {Utility::Bmtf, Utility::Omtf, Utility::Emtf}) {
			if (product->tfMuonSize.at(tfType) == 0) { continue;}
			for (unsigned short iTf = 0; iTf < product->tfMuonSize.at(tfType); iTf++){

				if (product->tfMuonBx.at(tfType).at(iTf) != 0) { continue;}
				if (product->tfMuonCmsPt.at(tfType).at(iTf) < ptCut - 4.01) { continue;}

				double tfMuonMatchedMuonDeltaR = 0.;
				if (hasMB2) {
					tfMuonMatchedMuonDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(tfType).at(iTf), product->tfMuonCmsPhi.at(tfType).at(iTf), tagMuonEtaSt2, tagMuonPhiSt2);
				} else {
					tfMuonMatchedMuonDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(tfType).at(iTf), product->tfMuonCmsPhi.at(tfType).at(iTf), tagMuonEtaSt1, tagMuonPhiSt1);
				}

				if (tfMuonMatchedMuonDeltaR < deltaRCut) {

					if (std::find(tagIndices.begin(), tagIndices.end(), iTag) != tagIndices.end()) { continue;}
					tagIndices.push_back(iTag);

					product->isLooseTagMuon.push_back(isLooseTagMuon);
					product->isMediumTagMuon.push_back(isMediumTagMuon);
					product->isTightTagMuon.push_back(isTightTagMuon);
					product->tagMuonHltIsoMu.push_back(product->muonHltIsoMu.at(iTag));
					product->tagMuonHltMu.push_back(product->muonHltMu.at(iTag));
					product->tagMuonPassesSingleMuon.push_back(product->muonPassesSingleMuon.at(iTag));
					product->tagMuonCharge.push_back(product->muonCharge.at(iTag));
					product->tagMuonE.push_back(product->muonE.at(iTag));
					product->tagMuonEt.push_back(product->muonEt.at(iTag));
					product->tagMuonPt.push_back(tagMuonPt);
					product->tagMuonEta.push_back(product->muonEta.at(iTag));
					product->tagMuonPhi.push_back(product->muonPhi.at(iTag));
					product->tagMuonIso.push_back(product->muonIso.at(iTag));
					product->tagMuonHltIsoDeltaR.push_back(product->muonHltIsoDeltaR.at(iTag));
					product->tagMuonEtaSt1.push_back(tagMuonEtaSt1);
					product->tagMuonPhiSt1.push_back(tagMuonPhiSt1);
					product->tagMuonEtaSt2.push_back(tagMuonEtaSt2);
					product->tagMuonPhiSt2.push_back(tagMuonPhiSt2);
					product->tagMuonMet.push_back(product->muonMet.at(iTag));
					product->tagMuonMt.push_back(product->muonMt.at(iTag));

					product->tagMuonHasMb1.push_back(hasMB1);
					product->tagMuonHasMb2.push_back(hasMB2);
				}
			}
		}
	}

	product->nTagMuon = product->tagMuonPt.size();
	if (product->nTagMuon == 0) { product->nMuon = 0; return;} // If no Tag muons are found, skip the event
	//std::cout << product->nTagMuon << " Tag Muons(" << product->nMuon << ") found" << std::endl;

	// Probe Muons
	for (unsigned short iProbe = 0; iProbe < product->nMuon; iProbe++) {
		//std::cout << "\niProbe = " << iProbe << std::endl;
		const double &probeMuonEtaSt1 = product->muonEtaSt1.at(iProbe);
		const double &probeMuonPhiSt1 = product->muonPhiSt1.at(iProbe);
		const bool &hasMB1 = (probeMuonEtaSt1 > -99) && (probeMuonPhiSt1 > -99);

		const double &probeMuonEtaSt2 = product->muonEtaSt2.at(iProbe);
		const double &probeMuonPhiSt2 = product->muonPhiSt2.at(iProbe);
		const bool &hasMB2 = (probeMuonEtaSt2 > -99) && (probeMuonPhiSt2 > -99);

		if (hasMB2) {
			//std::cout << std::setprecision(4) << "Probe(" << iProbe << "): " << probeMuonEtaSt2 << ", " << probeMuonPhiSt2<< std::endl;
		} else {
			//std::cout << std::setprecision(4) << "Probe(" << iProbe << "): " << probeMuonEtaSt1 << ", " << probeMuonPhiSt1<< std::endl;
		}

		if (!(hasMB1 or hasMB2)) { continue;}

		bool passesWorkingPoint = false;
		const bool &isLooseProbeMuon = product->isLooseMuon.at(iProbe);
		const bool &isMediumProbeMuon = product->isMediumMuon.at(iProbe);
		const bool &isTightProbeMuon = product->isTightMuon.at(iProbe);
		if (workingPointCut == 'm') {
			passesWorkingPoint = isMediumProbeMuon;
		} else if (workingPointCut == 't') {
			passesWorkingPoint = isTightProbeMuon;
		} else if (workingPointCut == 'l') {
			passesWorkingPoint = isLooseProbeMuon;
		} else if (workingPointCut == 'a') {
			passesWorkingPoint = true;
		} else {
			std::cerr << "Chosen invalid working point!" << std::endl;
		}

		if (!passesWorkingPoint) {
			continue;
		}

		const double &probeMuonPt = product->muonPt.at(iProbe);
		if (probeMuonPt < ptCut) { continue;}
		double probeMuonEta;
		if (hasMB2) {
			probeMuonEta = product->muonEtaSt2.at(iProbe);
		} else {
			probeMuonEta = product->muonEtaSt1.at(iProbe);
		}
		if (fabs(probeMuonEta) > etaCut) { continue;}

		unsigned short tagAndProbeIndex = 999;
		for (unsigned short iTag = 0; iTag < product->nTagMuon; iTag++){
			if (iProbe == tagIndices.at(iTag)) { continue;}

			double tagAndProbeDeltaR = 0.;
			if (hasMB2) {
				tagAndProbeDeltaR = Utility::DeltaR(product->tagMuonEtaSt2.at(iTag), product->tagMuonPhiSt2.at(iTag), probeMuonEtaSt2, probeMuonPhiSt2);
			} else {
				tagAndProbeDeltaR = Utility::DeltaR(product->tagMuonEtaSt1.at(iTag), product->tagMuonPhiSt1.at(iTag), probeMuonEtaSt1, probeMuonPhiSt1);
			}

			if (tagAndProbeDeltaR < 2 * deltaRCut) { continue;}
			tagAndProbeIndex = tagIndices.at(iTag);
			break;
		}
		if (tagAndProbeIndex > 899) { continue;}
		probeIndices.push_back(iProbe);

		product->isLooseProbeMuon.push_back(isLooseProbeMuon);
		product->isMediumProbeMuon.push_back(isMediumProbeMuon);
		product->isTightProbeMuon.push_back(isTightProbeMuon);
		product->probeMuonHltIsoMu.push_back(product->muonHltIsoMu.at(iProbe));
		product->probeMuonHltMu.push_back(product->muonHltMu.at(iProbe));
		product->probeMuonPassesSingleMuon.push_back(product->muonPassesSingleMuon.at(iProbe));
		product->probeMuonCharge.push_back(product->muonCharge.at(iProbe));
		product->probeMuonE.push_back(product->muonE.at(iProbe));
		product->probeMuonEt.push_back(product->muonEt.at(iProbe));
		product->probeMuonPt.push_back(probeMuonPt);
		product->probeMuonEta.push_back(probeMuonEta);
		product->probeMuonPhi.push_back(product->muonPhi.at(iProbe));
		product->probeMuonIso.push_back(product->muonIso.at(iProbe));
		product->probeMuonHltIsoDeltaR.push_back(product->muonHltIsoDeltaR.at(iProbe));
		product->probeMuonEtaSt1.push_back(product->muonEtaSt1.at(iProbe));
		product->probeMuonPhiSt1.push_back(product->muonPhiSt1.at(iProbe));
		product->probeMuonEtaSt2.push_back(product->muonEtaSt2.at(iProbe));
		product->probeMuonPhiSt2.push_back(product->muonPhiSt2.at(iProbe));
		product->probeMuonMet.push_back(product->muonMet.at(iProbe));
		product->probeMuonMt.push_back(product->muonMt.at(iProbe));

		product->probeMuonIEta.push_back(Utility::CmsEtaToHoIEta(product->probeMuonEta.back()));
		product->probeMuonHasMb1.push_back((fabs(product->probeMuonEtaSt1.back()) < 5) && (fabs(product->probeMuonPhiSt1.back()) < M_PI));
		product->probeMuonHasMb2.push_back((fabs(product->probeMuonEtaSt2.back()) < 5) && (fabs(product->probeMuonPhiSt2.back()) < M_PI));

		histCollection->histMuonMet->Fill(product->probeMuonMet.back());
		histCollection->histMuonMt->Fill(product->probeMuonMt.back());

		histCollection->histIsLooseMuon->Fill(product->isLooseMuon.back());
		histCollection->histIsMediumMuon->Fill(product->isMediumMuon.back());
		histCollection->histIsTightMuon->Fill(product->isTightMuon.back());
		histCollection->histMuonHltIsoMu->Fill(product->probeMuonHltIsoMu.back());
		histCollection->histMuonHltMu->Fill(product->probeMuonHltMu.back());
		histCollection->histMuonPassesSingleMuon->Fill(product->probeMuonPassesSingleMuon.back());
		histCollection->histMuonCharge->Fill(product->probeMuonCharge.back());

		histCollection->histMuonE->Fill(product->probeMuonE.back());
		histCollection->histMuonEt->Fill(product->probeMuonEt.back());
		histCollection->histMuonPt->Fill(product->probeMuonPt.back());
		histCollection->histMuonPt20->Fill(product->probeMuonPt.back());
		histCollection->histMuonEta->Fill(product->probeMuonEta.back());
		histCollection->histMuonPhi->Fill(product->probeMuonPhi.back());
		histCollection->histMuonIso->Fill(product->probeMuonIso.back());
		histCollection->histMuonHltIsoDeltaR->Fill(product->probeMuonHltIsoDeltaR.back());
		histCollection->histMuonEtaSt1->Fill(product->probeMuonEtaSt1.back());
		histCollection->histMuonPhiSt1->Fill(product->probeMuonPhiSt1.back());
		histCollection->histMuonEtaSt2->Fill(product->probeMuonEtaSt2.back());
		histCollection->histMuonPhiSt2->Fill(product->probeMuonPhiSt2.back());

		histCollection->histMuonIEta->Fill(product->probeMuonIEta.back());
	}
	product->nProbeMuon = product->probeMuonPt.size();
	histCollection->histNTagMuon_vs_nProbeMuon->Fill(product->nProbeMuon, product->nTagMuon);
}

void TagAndProbeProducer::EndJob(HoHistogramCollection* histCollection) {}
TagAndProbeProducer::~TagAndProbeProducer() {}
