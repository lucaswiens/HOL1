#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>

MuonProducer::MuonProducer() {
	Name = "Reco Muon Producer";
}

void MuonProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	product->nMuon = *dataReader->nMuon->Get();
	for (unsigned short iMuon = 0; iMuon < product->nMuon; iMuon++) {
		// The chimneys/cryogenics of the magnet cause an inefficiency
		// The trigger perfomance paper do not mention how they deal with this
		// We just don't use muons from that region
		// https://link.springer.com/content/pdf/10.1140/epjc/s10052-008-0756-6.pdf
		// https://publications.rwth-aachen.de/record/689785
		const float &muonEta = dataReader->muonEta->At(iMuon);
		const float &muonPhi = dataReader->muonPhi->At(iMuon);
		const bool &isAtChimneyRegion1 =
			 0.17 <= muonEta && muonEta <=  0.35 &&
			 1.13 <= muonPhi && muonPhi <=  2.01;
		const bool &isAtChimneyRegion2 =
			-0.35 <= muonEta && muonEta <= -0.17 &&
			 0.60 <= muonPhi && muonPhi <=  1.60;

		if (isAtChimneyRegion1 || isAtChimneyRegion2) { continue;}

		const float &muonEtaSt1 = dataReader->muonEtaSt1->At(iMuon);
		const float &muonPhiSt1 = dataReader->muonPhiSt1->At(iMuon);
		const bool &hasMB1 = (fabs(muonEtaSt1) < 5) && (fabs(muonPhiSt1) < M_PI);

		const float &muonEtaSt2 = dataReader->muonEtaSt2->At(iMuon);
		const float &muonPhiSt2 = dataReader->muonPhiSt2->At(iMuon);
		const bool &hasMB2 = (fabs(muonEtaSt2) < 5) && (fabs(muonPhiSt2) < M_PI);

		product->isLooseMuon.push_back(dataReader->muonIsLooseMuon->At(iMuon));
		product->isMediumMuon.push_back(dataReader->muonIsMediumMuon->At(iMuon));
		product->isTightMuon.push_back(dataReader->muonIsTightMuon->At(iMuon));
		product->muonHltIsoMu.push_back(dataReader->muonHlt_isomu->At(iMuon));
		product->muonHltMu.push_back(dataReader->muonHlt_mu->At(iMuon));
		product->muonPassesSingleMuon.push_back(dataReader->muonPassesSingleMuon->At(iMuon));
		product->muonCharge.push_back(dataReader->muonCharge->At(iMuon));
		product->muonE.push_back(dataReader->muonE->At(iMuon));
		product->muonEt.push_back(dataReader->muonEt->At(iMuon));
		product->muonPt.push_back(std::min(dataReader->muonPt->At(iMuon), (float)149.99)); // Keep this for now to be the same as eff_L1T.py
		//product->muonPt.push_back(dataReader->muonPt->At(iMuon));
		product->muonEta.push_back(muonEta);
		product->muonPhi.push_back(muonPhi);
		product->muonIso.push_back(dataReader->muonIso->At(iMuon));
		product->muonHltIsoDeltaR.push_back(dataReader->muonHlt_isoDeltaR->At(iMuon));
		product->muonDeltaR.push_back(dataReader->muonHlt_deltaR->At(iMuon));
		product->muonEtaSt1.push_back(muonEtaSt1);
		product->muonPhiSt1.push_back(muonPhiSt1);
		product->muonEtaSt2.push_back(muonEtaSt2);
		product->muonPhiSt2.push_back(muonPhiSt2);
		product->muonMet.push_back(dataReader->muonMet->At(iMuon));
		product->muonMt.push_back(dataReader->muonMt->At(iMuon));

		product->muonIEta.push_back(Utility::CmsEtaToHoIEta(muonEta));
		product->muonIPhi.push_back(Utility::CmsPhiToHoIPhi(muonPhi));
		product->muonHasMb1.push_back(hasMB1);
		product->muonHasMb2.push_back(hasMB2);

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
		histCollection->histMuonPtFineBinning->Fill(product->muonPt.back());
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

		histCollection->histMuonPt_vs_MuonEta->Fill(product->muonPt.back(), product->muonEta.back());
		histCollection->histMuonEta_vs_MuonPt->Fill(product->muonEta.back(), product->muonPt.back());
		histCollection->histMuonEta_vs_MuonPhi->Fill(product->muonEta.back(), product->muonPhi.back());

		//histCollection->histMuonPt_vs_MuonEta->Fill(product->muonPt.at(iMuon), product->muonEta.at(iMuon));
		//histCollection->histMuonEta_vs_MuonPt->Fill(product->muonEta.at(iMuon), product->muonPt.at(iMuon));
		//histCollection->histMuonEta_vs_MuonPhi->Fill(product->muonEta.at(iMuon), product->muonPhi.at(iMuon));

		/*
		if (product->muonIEta.back() == 3) {
			histCollection->histMuonPtAtIEtaP3->Fill(product->muonPt.back());
		} else if (product->muonIEta.back() == -3) {
			histCollection->histMuonPtAtIEtaM3->Fill(product->muonPt.back());
		}

		if (product->muonPt.back() > 20) {
			histCollection->histMuonEtaHighPt->Fill(product->muonEta.back());
		} else {
			histCollection->histMuonEtaLowPt->Fill(product->muonEta.back());
		}
		*/
	}
	product->nMuon = product->muonPt.size();
}

void MuonProducer::EndJob(HoHistogramCollection* histCollection) {}
MuonProducer::~MuonProducer() {}
