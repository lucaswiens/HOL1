#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class BxMatchingProducer : public BaseProducer {
	private:

	public:
		BxMatchingProducer();
		~BxMatchingProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};
