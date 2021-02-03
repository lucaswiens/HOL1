#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

#include <TMath.h>

class HoHistogramProducer : public BaseProducer {
	private:


	public:
		HoHistogramProducer(HoHistogramCollection* histCollection);
		~HoHistogramProducer();
		void Produce(DataReader *dataReader, HoProduct *product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};
