#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>

HoProducer::HoProducer() {
	histSumQ = new TH1D("sumQ", "sumQ", 50, 0, 50);
	histNHcalDetIds = new TH1I("hcalDetIds", "hcalDetIds", 50, 500, 1000);
	histNHcalQIESamples = new TH1I("hcalQIESamples", "hcalQIESamples", 50, 5000, 12500);
	histHcalDetIdIEta = new TH1I("hcalDetIdIEta", "hcalDetIdIEta", 30, -15, 16);
	histHcalDetIdIPhi = new TH1I("hcalDetIdIPhi", "hcalDetIdIPhi", 72, 1, 73);
	histHcalQIESample = new TH1I("hcalQIESample", "hcalQIESample", 50, 0, 50);
	histHcalQIESampleAdc = new TH1I("hcalQIESampleAdc", "hcalQIESampleAdc", 50, 0, 50);
	histHcalQIESampleDv = new TH1I("hcalQIESampleDv", "hcalQIESampleDv", 2, 0, 2);
	histHcalQIESampleEr = new TH1I("hcalQIESampleEr", "hcalQIESampleEr", 25, 0, 1);

	histHoCmsEta = new TH1D("HoCmsEta", "HoCmsEta", 68, -3, 3);
	histHoCmsPhi = new TH1D("HoCmsPhi", "HoCmsPhi", 72, -M_PI, M_PI);

	histSampleEnergy = new TH1F("SampleEnergy", "SampleEnergy", 25, 0, 1);
	histQIESampleFc = new TH1F("QIESampleFc", "QIESampleFc", 50, 0, 100);
	histQIESamplePedestal = new TH1F("QIESamplePedestal", "QIESamplePedestal", 30, -10, 10);
	histQIESampleFc_MPedestals = new TH1F("QIESampleFc_MPedestals", "QIESampleFc_MPedestals", 50, 0, 100);
}

void HoProducer::Produce(DataReader* dataReader, HoProduct* product) {
	product->sumQ = *dataReader->sumQ->Get();
	product->nHcalDetIds = *dataReader->nHcalDetIds->Get();
	product->nHcalQIESamples = *dataReader->nHcalQIESamples->Get();

	histSumQ->Fill(product->sumQ);
	histNHcalDetIds->Fill(product->nHcalDetIds);
	histNHcalQIESamples->Fill(product->nHcalQIESamples);

	//unsigned int size = dataReader->hcalDetIdIEta->GetSize();
	for (unsigned i = 0; i < dataReader->hcalDetIdIEta->GetSize(); i++) {
		const int &qieSample = dataReader->hcalQIESample->At(i);
		if (qieSample != 4) { continue;}
		product->hcalIEta.push_back(dataReader->hcalDetIdIEta->At(i));
		product->hcalIPhi.push_back(dataReader->hcalDetIdIPhi->At(i));
		product->hcalQIESample.push_back(qieSample);
		product->hcalQIESampleAdc.push_back(dataReader->hcalQIESampleAdc->At(i));
		product->hcalQIESampleDv.push_back(dataReader->hcalQIESampleDv->At(i));
		product->hcalQIESampleEr.push_back(dataReader->hcalQIESampleEr->At(i));

		product->SampleEnergy.push_back(dataReader->SampleEnergy->At(i));
		product->QIESampleFc.push_back(dataReader->QIESampleFc->At(i));
		product->QIESamplePedestal.push_back(dataReader->QIESamplePedestal->At(i));
		product->QIESampleFc_MPedestals.push_back(dataReader->QIESampleFc_MPedestals->At(i));

		product->hcalCmsEta.push_back(Utility::HoIEtaToCmsEta(product->hcalIEta.back()));
		product->hcalCmsPhi.push_back(Utility::HoIPhiToCmsPhi(product->hcalIPhi.back()));

		product->hcalWheel.push_back(Utility::HoIEtaToWheel(product->hcalIEta.back()));
		product->hcalSection.push_back(Utility::HoIPhiToSection(product->hcalIPhi.back()));

		histHcalDetIdIEta->Fill(product->hcalIEta.back());
		histHcalDetIdIPhi->Fill(product->hcalIPhi.back());
		histHcalQIESample->Fill(product->hcalQIESample.back());
		histHcalQIESampleAdc->Fill(product->hcalQIESampleAdc.back());
		histHcalQIESampleDv->Fill(product->hcalQIESampleDv.back());
		histHcalQIESampleEr->Fill(product->hcalQIESampleEr.back());

		histSampleEnergy->Fill(product->SampleEnergy.back());
		histQIESampleFc->Fill(product->QIESampleFc.back());
		histQIESamplePedestal->Fill(product->QIESamplePedestal.back());
		histQIESampleFc_MPedestals->Fill(product->QIESampleFc_MPedestals.back());

		histHoCmsEta->Fill(product->hcalCmsEta.back());
		histHoCmsPhi->Fill(product->hcalCmsPhi.back());
	}
}

HoProducer::~HoProducer() {}
