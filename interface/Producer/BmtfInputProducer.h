#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class BmtfInputProducer : public BaseProducer {
	private:
		double l1EtaCut, l1PtCut;
	public:
		BmtfInputProducer(double l1EtaCut, double l1PtCut);
		~BmtfInputProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};

