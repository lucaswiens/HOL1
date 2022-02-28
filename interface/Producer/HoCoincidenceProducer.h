#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

#include <TMath.h>

class HoCoincidenceProducer : public BaseProducer {
	private:
		int iEtaCut;
		double etaCut, l1EtaCut, ptCut, l1PtCut, deltaPhiCut, deltaRCut;
	public:
		HoCoincidenceProducer(const int &iEtaCut, const double &etaCut, const double &l1EtaCut, const double &ptCut, const double &l1PtCut, const double &deltaPhiCut, const double &deltaRCut);
		~HoCoincidenceProducer();
		void Produce(DataReader *dataReader, HoProduct *product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};

