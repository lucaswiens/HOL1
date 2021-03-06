#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class HoProducer : public BaseProducer {
	private:

	public:
		HoProducer(HoHistogramCollection* histCollection);
		~HoProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};
