#include <HOAnalysis/HOL1/interface/Producer/TagAndProbeProducer.h>

TagAndProbeProducer::TagAndProbeProducer(const double &tagPtCut, const double &probePtCut, const double &l1PtCut, const double &etaCut, const double &deltaRTagAndTfCut, const double &deltaRTagAndProbeCut, const char &tagWorkingPointCut, const char &probeWorkingPointCut):
	tagPtCut(tagPtCut),
	probePtCut(probePtCut),
	l1PtCut(l1PtCut),
	etaCut(etaCut),
	deltaRTagAndTfCut(deltaRTagAndTfCut),
	deltaRTagAndProbeCut(deltaRTagAndProbeCut),
	tagWorkingPointCut(tagWorkingPointCut),
	probeWorkingPointCut(probeWorkingPointCut)
	{
		Name = "Tag and Probe Producer";
		std::map<char, std::string> workingPointMap = {
			{'l', "loose"},
			{'m', "medium"},
			{'t', "tight"},
			{'a', "all"}
		};
		std::cout << "The cuts for the Tag and Probes are:\n" <<
			"Tag Muon WP        = " << workingPointMap[tagWorkingPointCut] << std::endl <<
			"Probe Muon WP      = " << workingPointMap[probeWorkingPointCut] << std::endl <<
			"Tag   Muon Pt      > " << tagPtCut   << std::endl <<
			"Probe Muon Pt      > " << probePtCut   << std::endl <<
			"l1Pt               > " << l1PtCut   << std::endl <<
			"|muonEta|          < " << etaCut  << std::endl <<
			"deltaR(Tag, Tf)    < " << deltaRTagAndTfCut   << std::endl <<
			"deltaR(Tag, Probe) > " << deltaRTagAndProbeCut   << std::endl;
	}


void TagAndProbeProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	if (product->nMuon < 2) { product->nMuon = 0; return;}
	product->nProbeMuon = 0;
	product->nTagMuon = 0;

	// Tag Muons
	std::vector<unsigned short> tagIndices;
	std::vector<unsigned short> probeIndices;
	for (unsigned short iTag = 0; iTag < product->nMuon; iTag++) {
		//if (tagIndices.size() >= 1) { continue;}
		//Only get muons that have eta and phi variables propagated to the second station
		const double &tagMuonEtaSt1 = product->muonEtaSt1.at(iTag);
		const double &tagMuonPhiSt1 = product->muonPhiSt1.at(iTag);
		const bool &hasMb1 = (tagMuonEtaSt1 > -99) && (tagMuonPhiSt1 > -99);

		const double &tagMuonEtaSt2 = product->muonEtaSt2.at(iTag);
		const double &tagMuonPhiSt2 = product->muonPhiSt2.at(iTag);
		const bool &hasMb2 = (tagMuonEtaSt2 > -99) && (tagMuonPhiSt2 > -99);

		if (!(hasMb1 || hasMb2)) { continue;}

		bool passesWorkingPoint = false;

		const bool &isLooseTagMuon = product->isLooseMuon.at(iTag);
		const bool &isMediumTagMuon = product->isMediumMuon.at(iTag);
		const bool &isTightTagMuon = product->isTightMuon.at(iTag);
		if (tagWorkingPointCut == 't') {
			passesWorkingPoint = isTightTagMuon;
		} else if (tagWorkingPointCut == 'm') {
			passesWorkingPoint = isMediumTagMuon;
		} else if (tagWorkingPointCut == 'l') {
			passesWorkingPoint = isLooseTagMuon;
		} else if (tagWorkingPointCut == 'a') {
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
		if (tagMuonPt < tagPtCut) { continue;}

		const double &tagMuonIso = product->muonIso.at(iTag);
		if (tagMuonIso > 0.1) { continue;}

		for (int tfType : {Utility::Bmtf, Utility::Omtf, Utility::Emtf}) {
			if (product->tfMuonSize.at(tfType) == 0) { continue;}
			for (unsigned short iTf = 0; iTf < product->tfMuonSize.at(tfType); iTf++){
				if (product->tfMuonBx.at(tfType).at(iTf) != 0) { continue;}
				if (product->tfMuonCmsPt.at(tfType).at(iTf) < tagPtCut - 4.01) { continue;}
				//if (product->tfMuonCmsPt.at(tfType).at(iTf) < tagMuonPt - 4) { continue;}

				double tfMuonMatchedMuonDeltaR = 0.;
				if (hasMb2) {
					tfMuonMatchedMuonDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(tfType).at(iTf), product->tfMuonCmsPhi.at(tfType).at(iTf), tagMuonEtaSt2, tagMuonPhiSt2);
				} else if (hasMb1) {
					tfMuonMatchedMuonDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(tfType).at(iTf), product->tfMuonCmsPhi.at(tfType).at(iTf), tagMuonEtaSt1, tagMuonPhiSt1);
				} else {
					tfMuonMatchedMuonDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(tfType).at(iTf), product->tfMuonCmsPhi.at(tfType).at(iTf), product->muonEta.at(iTag), product->muonPhi.at(iTag));
				}
				tfMuonMatchedMuonDeltaR = Utility::DeltaR(product->tfMuonCmsEta.at(tfType).at(iTf), product->tfMuonCmsPhi.at(tfType).at(iTf), product->muonEta.at(iTag), product->muonPhi.at(iTag));

				if (tfMuonMatchedMuonDeltaR < deltaRTagAndTfCut) {

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

					product->tagMuonHasMb1.push_back(hasMb1);
					product->tagMuonHasMb2.push_back(hasMb2);

					histCollection->histTagMuonMet->Fill(product->tagMuonMet.back());
					histCollection->histTagMuonMt->Fill(product->tagMuonMt.back());

					histCollection->histIsLooseTagMuon->Fill(product->isLooseTagMuon.back());
					histCollection->histIsMediumTagMuon->Fill(product->isMediumTagMuon.back());
					histCollection->histIsTightTagMuon->Fill(product->isTightTagMuon.back());
					histCollection->histTagMuonHltIsoMu->Fill(product->tagMuonHltIsoMu.back());
					histCollection->histTagMuonHltMu->Fill(product->tagMuonHltMu.back());
					histCollection->histTagMuonPassesSingleMuon->Fill(product->tagMuonPassesSingleMuon.back());
					histCollection->histTagMuonCharge->Fill(product->tagMuonCharge.back());

					histCollection->histTagMuonE->Fill(product->tagMuonE.back());
					histCollection->histTagMuonEt->Fill(product->tagMuonEt.back());
					histCollection->histTagMuonPt->Fill(product->tagMuonPt.back());
					histCollection->histTagMuonEta->Fill(product->tagMuonEta.back());
					histCollection->histTagMuonPhi->Fill(product->tagMuonPhi.back());
					histCollection->histTagMuonIso->Fill(product->tagMuonIso.back());
					histCollection->histTagMuonHltIsoDeltaR->Fill(product->tagMuonHltIsoDeltaR.back());
					histCollection->histTagMuonEtaSt1->Fill(product->tagMuonEtaSt1.back());
					histCollection->histTagMuonPhiSt1->Fill(product->tagMuonPhiSt1.back());
					histCollection->histTagMuonEtaSt2->Fill(product->tagMuonEtaSt2.back());
					histCollection->histTagMuonPhiSt2->Fill(product->tagMuonPhiSt2.back());

					//histCollection->histTagMuonIEta->Fill(product->tagMuonIEta.back());

					histCollection->histTagMuonPt_vs_TagMuonEta->Fill(product->tagMuonPt.back(), product->tagMuonEta.back());
					histCollection->histTagMuonEta_vs_TagMuonPt->Fill(product->tagMuonEta.back(), product->tagMuonPt.back());
					histCollection->histTagMuonEta_vs_TagMuonPhi->Fill(product->tagMuonEta.back(), product->tagMuonPhi.back());
				}
			}
		}
	}

	product->nTagMuon = product->tagMuonPt.size();
	if (product->nTagMuon == 0) { product->nMuon = 0; return;} // If no Tag muons are found, skip the event

	// Probe Muons
	//std::vector<std::pair<int, int>> tagAndProbePair;
	std::vector<int> probeMatchedTagIndex;
	for (unsigned short iProbe = 0; iProbe < product->nMuon; iProbe++) {
		if (std::find(probeMatchedTagIndex.begin(), probeMatchedTagIndex.end(), iProbe) != probeMatchedTagIndex.end()) { continue;} // If the reco muon with index iProbe is an already matched tag muon, don't use it again

		const double &probeMuonEtaSt1 = product->muonEtaSt1.at(iProbe);
		const double &probeMuonPhiSt1 = product->muonPhiSt1.at(iProbe);
		const bool &hasMb1 = (probeMuonEtaSt1 > -99) && (probeMuonPhiSt1 > -99);

		const double &probeMuonEtaSt2 = product->muonEtaSt2.at(iProbe);
		const double &probeMuonPhiSt2 = product->muonPhiSt2.at(iProbe);
		const bool &hasMb2 = (probeMuonEtaSt2 > -99) && (probeMuonPhiSt2 > -99);

		if (!(hasMb1 || hasMb2)) { continue;}


		bool passesWorkingPoint = false;
		const bool &isLooseProbeMuon = product->isLooseMuon.at(iProbe);
		const bool &isMediumProbeMuon = product->isMediumMuon.at(iProbe);
		const bool &isTightProbeMuon = product->isTightMuon.at(iProbe);
		if (probeWorkingPointCut == 't') {
			passesWorkingPoint = isTightProbeMuon;
		}else if (probeWorkingPointCut == 'm') {
			passesWorkingPoint = isMediumProbeMuon;
		} else if (probeWorkingPointCut == 'l') {
			passesWorkingPoint = isLooseProbeMuon;
		} else if (probeWorkingPointCut == 'a') {
			passesWorkingPoint = true;
		} else {
			std::cerr << "Chosen invalid working point!" << std::endl;
		}

		if (!passesWorkingPoint) {
			continue;
		}

		const double &probeMuonPt = product->muonPt.at(iProbe);
		if (probeMuonPt < probePtCut) { continue;}
		const double &probeMuonEta = product->muonEta.at(iProbe);
		if (fabs(probeMuonEta) > etaCut) { continue;}

		const double &probeMuonPhi = product->muonPhi.at(iProbe);
		ROOT::Math::PtEtaPhiMVector probeMuonP4 = ROOT::Math::PtEtaPhiMVector(probeMuonPt, probeMuonEta, probeMuonPhi, muonMass);

		unsigned short tagAndProbeIndex = 999;
		for (unsigned short iTag = 0; iTag < product->nTagMuon; iTag++){
			//if (iProbe == tagIndices.at(iTag)) { continue;} // Tags cannot become probes
			unsigned short &tagIndex = tagIndices.at(iTag);
			if (std::find(probeMatchedTagIndex.begin(), probeMatchedTagIndex.end(), tagIndex) != probeMatchedTagIndex.end()) { continue;} // If tag has already found a probe pair, then don't use it again
			//if (std::find(probeIndices.begin(), probeIndices.end(), tagIndex) != probeIndices.end()) { continue;} // If a tag is already a probe, don't use it again
			if (product->tagMuonCharge.at(iTag) == product->muonCharge.at(iProbe)){ continue;}

			double tagAndProbeDeltaR = Utility::DeltaR(product->tagMuonEta.at(iTag), product->tagMuonPhi.at(iTag), probeMuonEta, probeMuonPhi);
			ROOT::Math::PtEtaPhiMVector tagMuonP4 = ROOT::Math::PtEtaPhiMVector(product->tagMuonPt.at(iTag), product->tagMuonEta.at(iTag), product->tagMuonPhi.at(iTag), muonMass);
			const double &diMuonMass = (probeMuonP4 + tagMuonP4).M();

			histCollection->histDiMuonMass->Fill(diMuonMass);

			if (tagAndProbeDeltaR < deltaRTagAndProbeCut) { continue;}
			//if (product->tagMuonPt.at(iTag) > 10) {
			//	if (std::abs(diMuonMass - zBosonMass)/zBosonMass > 0.32) { continue;}
			//} else {
			//	if (std::abs(diMuonMass - jPsiMass)/jPsiMass > 0.32) { continue;}
			//}
			//if (std::abs(diMuonMass - zBosonMass) > 30) { continue;}
			if (diMuonMass < 50 || 120 < diMuonMass) { continue;}

			tagAndProbeIndex = tagIndices.at(iTag);
			histCollection->histTagAndProbeDiMuonMass->Fill(diMuonMass);
			break;
		}

		if (tagAndProbeIndex > 899) { continue;}
		probeIndices.push_back(iProbe);
		probeMatchedTagIndex.push_back(tagAndProbeIndex);

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
		product->probeMuonIPhi.push_back(Utility::CmsPhiToHoIPhi(product->probeMuonPhi.back()));
		product->probeMuonHasMb1.push_back(hasMb1);
		product->probeMuonHasMb2.push_back(hasMb2);

		histCollection->histProbeMuonMet->Fill(product->probeMuonMet.back());
		histCollection->histProbeMuonMt->Fill(product->probeMuonMt.back());

		histCollection->histIsLooseProbeMuon->Fill(product->isLooseProbeMuon.back());
		histCollection->histIsMediumProbeMuon->Fill(product->isMediumProbeMuon.back());
		histCollection->histIsTightProbeMuon->Fill(product->isTightProbeMuon.back());
		histCollection->histProbeMuonHltIsoMu->Fill(product->probeMuonHltIsoMu.back());
		histCollection->histProbeMuonHltMu->Fill(product->probeMuonHltMu.back());
		histCollection->histProbeMuonPassesSingleMuon->Fill(product->probeMuonPassesSingleMuon.back());
		histCollection->histProbeMuonCharge->Fill(product->probeMuonCharge.back());

		histCollection->histProbeMuonE->Fill(product->probeMuonE.back());
		histCollection->histProbeMuonEt->Fill(product->probeMuonEt.back());
		histCollection->histProbeMuonPt->Fill(product->probeMuonPt.back());
		histCollection->histProbeMuonEta->Fill(product->probeMuonEta.back());
		histCollection->histProbeMuonPhi->Fill(product->probeMuonPhi.back());
		histCollection->histProbeMuonIso->Fill(product->probeMuonIso.back());
		histCollection->histProbeMuonHltIsoDeltaR->Fill(product->probeMuonHltIsoDeltaR.back());
		histCollection->histProbeMuonEtaSt1->Fill(product->probeMuonEtaSt1.back());
		histCollection->histProbeMuonPhiSt1->Fill(product->probeMuonPhiSt1.back());
		histCollection->histProbeMuonEtaSt2->Fill(product->probeMuonEtaSt2.back());
		histCollection->histProbeMuonPhiSt2->Fill(product->probeMuonPhiSt2.back());

		histCollection->histProbeMuonIEta->Fill(product->probeMuonIEta.back());

		histCollection->histProbeMuonPt_vs_ProbeMuonEta->Fill(product->probeMuonPt.back(), product->probeMuonEta.back());
		histCollection->histProbeMuonEta_vs_ProbeMuonPt->Fill(product->probeMuonEta.back(), product->probeMuonPt.back());
		histCollection->histProbeMuonEta_vs_ProbeMuonPhi->Fill(product->probeMuonEta.back(), product->probeMuonPhi.back());
	}
	product->nProbeMuon = product->probeMuonPt.size();
	histCollection->histNTagMuon->Fill(product->nTagMuon);
	histCollection->histNProbeMuon->Fill(product->nProbeMuon);
	histCollection->histNTagMuon_vs_nProbeMuon->Fill(product->nProbeMuon, product->nTagMuon);
}

void TagAndProbeProducer::EndJob(HoHistogramCollection* histCollection) {}
TagAndProbeProducer::~TagAndProbeProducer() {}
