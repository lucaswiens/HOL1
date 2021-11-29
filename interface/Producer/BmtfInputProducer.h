#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class BmtfInputProducer : public BaseProducer {
	private:
	public:
		BmtfInputProducer();
		~BmtfInputProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};

