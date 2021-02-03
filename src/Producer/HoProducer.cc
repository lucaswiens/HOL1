#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>

HoProducer::HoProducer(HoHistogramCollection* histCollection) {
	histCollection->histNHcalDetIds = new TH1I("hcalDetIds", "hcalDetIds", 50, 500, 1000);
	histCollection->histSampleEnergy = new TH1F("SampleEnergy", "SampleEnergy", 25, 0, 1);
	histCollection->histHcalDetIdIEta = new TH1I("hcalDetIdIEta", "hcalDetIdIEta", 40, -20, 20);
	histCollection->histHcalDetIdIPhi = new TH1I("hcalDetIdIPhi", "hcalDetIdIPhi", 72, 1, 73);
	histCollection->histHcalCmsEta = new TH1D("hcalCmsEta", "hcalCmsEta", 68, -3, 3);
	histCollection->histHcalCmsPhi = new TH1D("hcalCmsPhi", "hcalCmsPhi", 72, -M_PI, M_PI);
	histCollection->histHcalWheel = new TH1I("hcalWheel", "hcalWheel", 5, -2, 3);
	histCollection->histHcalSection = new TH1I("hcalSection", "hcalSection", 12, 0, 12);
	histCollection->histSumQ = new TH1D("sumQ", "sumQ", 50, 0, 50);
	histCollection->histNHcalQIESamples = new TH1I("hcalQIESamples", "hcalQIESamples", 50, 5000, 12500);
	histCollection->histHcalQIESample = new TH1I("hcalQIESample", "hcalQIESample", 10, 1, 11);
	histCollection->histHcalQIESampleAdc = new TH1I("hcalQIESampleAdc", "hcalQIESampleAdc", 50, 0, 50);
	histCollection->histHcalQIESampleDv = new TH1I("hcalQIESampleDv", "hcalQIESampleDv", 2, 0, 2);
	histCollection->histHcalQIESampleEr = new TH1I("hcalQIESampleEr", "hcalQIESampleEr", 25, 0, 1);
	histCollection->histQIESampleFc = new TH1F("QIESampleFc", "QIESampleFc", 50, 0, 100);
	histCollection->histQIESamplePedestal = new TH1F("QIESamplePedestal", "QIESamplePedestal", 30, -10, 10);
	histCollection->histQIESampleFc_MPedestals = new TH1F("QIESampleFc_MPedestals", "QIESampleFc_MPedestals", 50, 0, 100);
}

void HoProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	product->sumQ = *dataReader->sumQ->Get();
	product->nHcalDetIds = *dataReader->nHcalDetIds->Get();
	product->nHcalQIESamples = *dataReader->nHcalQIESamples->Get();

	histCollection->histSumQ->Fill(product->sumQ);
	histCollection->histNHcalDetIds->Fill(product->nHcalDetIds);
	histCollection->histNHcalQIESamples->Fill(product->nHcalQIESamples);

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

		histCollection->histHcalDetIdIEta->Fill(product->hcalIEta.back());
		histCollection->histHcalDetIdIPhi->Fill(product->hcalIPhi.back());
		histCollection->histHcalQIESample->Fill(product->hcalQIESample.back());
		histCollection->histHcalQIESampleAdc->Fill(product->hcalQIESampleAdc.back());
		histCollection->histHcalQIESampleDv->Fill(product->hcalQIESampleDv.back());
		histCollection->histHcalQIESampleEr->Fill(product->hcalQIESampleEr.back());

		histCollection->histSampleEnergy->Fill(product->SampleEnergy.back());
		histCollection->histQIESampleFc->Fill(product->QIESampleFc.back());
		histCollection->histQIESamplePedestal->Fill(product->QIESamplePedestal.back());
		histCollection->histQIESampleFc_MPedestals->Fill(product->QIESampleFc_MPedestals.back());

		histCollection->histHcalCmsEta->Fill(product->hcalCmsEta.back());
		histCollection->histHcalCmsPhi->Fill(product->hcalCmsPhi.back());

		histCollection->histHcalWheel->Fill(product->hcalWheel.back());
		histCollection->histHcalSection->Fill(product->hcalSection.back());
	}
}

void HoProducer::EndJob(HoHistogramCollection* histCollection) {}
HoProducer::~HoProducer() {}
