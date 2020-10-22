#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>

HoProducer::HoProducer() {
	histSumQ = new TH1D("sumQ", "sumQ", 50, 0, 50);
	histNHcalDetIds = new TH1I("hcalDetIds", "hcalDetIds", 50, 500, 1000);
	histNHcalQIESamples = new TH1I("hcalQIESamples", "hcalQIESamples", 50, 5000, 12500);
	histHcalDetIdIEta = new TH1I("hcalDetIdIEta", "hcalDetIdIEta", 32, -16, 16);
	histHcalDetIdIPhi = new TH1I("hcalDetIdIPhi", "hcalDetIdIPhi", 72, 0, 72);
	histHcalQIESample = new TH1I("hcalQIESample", "hcalQIESample", 50, 0, 50);
	histHcalQIESampleAdc = new TH1I("hcalQIESampleAdc", "hcalQIESampleAdc", 50, 0, 50);
	histHcalQIESampleDv = new TH1I("hcalQIESampleDv", "hcalQIESampleDv", 2, 0, 2);
	histHcalQIESampleEr = new TH1I("hcalQIESampleEr", "hcalQIESampleEr", 25, 0, 1);

	histSampleEnergy = new TH1F("SampleEnergy", "SampleEnergy", 25, 0, 1);
	histQIESampleFc = new TH1F("QIESampleFc", "QIESampleFc", 50, 0, 100);
	histQIESamplePedestal = new TH1F("QIESamplePedestal", "QIESamplePedestal", 30, -10, 10);
	histQIESampleFc_MPedestals = new TH1F("QIESampleFc_MPedestals", "QIESampleFc_MPedestals", 50, 0, 100);
}

void HoProducer::Produce(DataReader* dataReader) {
	histSumQ->Fill(*dataReader->sumQ->Get());
	histNHcalDetIds->Fill(*dataReader->nHcalDetIds->Get());
	histNHcalQIESamples->Fill(*dataReader->nHcalQIESamples->Get());

	unsigned int size = dataReader->hcalDetIdIEta->GetSize();
	for (unsigned i = 0; i < size; i++) {
		histHcalDetIdIEta->Fill(dataReader->hcalDetIdIEta->At(i));
		histHcalDetIdIPhi->Fill(dataReader->hcalDetIdIPhi->At(i));
		histHcalQIESample->Fill(dataReader->hcalQIESample->At(i));
		histHcalQIESampleAdc->Fill(dataReader->hcalQIESampleAdc->At(i));
		histHcalQIESampleDv->Fill(dataReader->hcalQIESampleDv->At(i));
		histHcalQIESampleEr->Fill(dataReader->hcalQIESampleEr->At(i));

		histSampleEnergy->Fill(dataReader->SampleEnergy->At(i));
		histQIESampleFc->Fill(dataReader->QIESampleFc->At(i));
		histQIESamplePedestal->Fill(dataReader->QIESamplePedestal->At(i));
		histQIESampleFc_MPedestals->Fill(dataReader->QIESampleFc_MPedestals->At(i));
	}
}

HoProducer::~HoProducer() {}
