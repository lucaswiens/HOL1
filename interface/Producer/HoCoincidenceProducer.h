#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

#include <TMath.h>

class HoCoincidenceProducer : public BaseProducer {
	private:
		int iEtaCut;
		double etaCut, bmtfEtaCut, ptCut, bmtfPtCut, deltaPhiCut, deltaRCut;
	public:
		HoCoincidenceProducer(const int &iEtaCut, const double &etaCut, const double &bmtfEtaCut, const double &ptCut, const double &bmtfPtCut, const double &deltaPhiCut, const double &deltaRCut);
		~HoCoincidenceProducer();
		void Produce(DataReader *dataReader, HoProduct *product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};

