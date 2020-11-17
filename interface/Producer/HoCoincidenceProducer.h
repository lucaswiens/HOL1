#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

#include <TMath.h>

class HoCoincidenceProducer : public BaseProducer {
	public:
		HoCoincidenceProducer();
		~HoCoincidenceProducer();
		void Produce(DataReader *dataReader, HoProduct *product);
};
