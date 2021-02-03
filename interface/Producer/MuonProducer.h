#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class MuonProducer : public BaseProducer {
	private:

	public:
		MuonProducer(HoHistogramCollection* histCollection);
		~MuonProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};
