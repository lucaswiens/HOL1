#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class MuonProducer : public BaseProducer {
	private:
		double ptCut, etaCut;
		char workingPointCut;
	public:
		MuonProducer(const double &ptCut, const double &etaCut, const char &workingPointCut);
		~MuonProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};

