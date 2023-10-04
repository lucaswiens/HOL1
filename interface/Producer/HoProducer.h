#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>
#include <TRandom.h>

class HoProducer : public BaseProducer {
	public:
		HoProducer();
		~HoProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};

