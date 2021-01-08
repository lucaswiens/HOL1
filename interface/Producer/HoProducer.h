#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class HoProducer : public BaseProducer {
	private:
		TH1D *histSumQ, *histHcalCmsPhi, *histHcalCmsEta;
		TH1I *histNHcalDetIds, *histNHcalQIESamples, *histHcalDetIdIEta, *histHcalDetIdIPhi, *histHcalQIESample, *histHcalQIESampleAdc, *histHcalQIESampleDv, *histHcalQIESampleEr;
		TH1F *histSampleEnergy, *histQIESampleFc,  *histQIESamplePedestal, *histQIESampleFc_MPedestals;

	public:
		HoProducer();
		~HoProducer();
		void Produce(DataReader* dataReader, HoProduct* product);
};
