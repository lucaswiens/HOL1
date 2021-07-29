#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>

HoProducer::HoProducer() {
	Name = "HO Producer";
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
