#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>
#include <iostream>
#include <typeinfo>
#include <algorithm>

HoProducer::HoProducer() {
	Name = "HO Producer";
}

//int sum=0;
bool qie4cut = false;

void HoProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {

	product->sumQ = *dataReader->sumQ->Get();
	product->nHcalDetIds = *dataReader->nHcalDetIds->Get();
	product->nHcalQIESamples = *dataReader->nHcalQIESamples->Get();

	histCollection->histSumQ->Fill(product->sumQ);
	histCollection->histNHcalDetIds->Fill(product->nHcalDetIds);
	histCollection->histNHcalQIESamples->Fill(product->nHcalQIESamples);
	// #############
	//std::vector<int> vec = {4,3,1,7,2,0};
	std::vector<int> vec_adc, vec_qie; //::iterator
	//auto vec = (dataReader->hcalQIESampleAdc); // product

	//histCollection->histHcalQIESampleAdc->Fill(product->hcalQIESampleAdc);

	//unsigned int size = dataReader->hcalDetIdIEta->GetSize();
	for (unsigned i = 0; i < dataReader->hcalDetIdIEta->GetSize(); i++) {
		const int &qieSample = dataReader->hcalQIESample->At(i);
		const int &qieSampleAdc = dataReader->hcalQIESampleAdc->At(i);
		histCollection->histHcalQIESamples_vs_HcalQIESampleAdc->Fill(qieSample, qieSampleAdc);

		vec_qie.push_back(qieSample);
		vec_adc.push_back(qieSampleAdc);
		if (qieSample != 4) { qie4cut=true; continue;}

		product->hcalIEta.push_back(dataReader->hcalDetIdIEta->At(i));
		product->hcalIPhi.push_back(dataReader->hcalDetIdIPhi->At(i));
		product->hcalQIESample.push_back(qieSample);
		product->hcalQIESampleAdc.push_back(qieSampleAdc);
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

		//##############
		// new stuff
		//std::unique_ptr<TTreeReaderArray<int> > vec;
		// int vec = (dataReader->hcalQIESampleAdc->At(i));
		// std::cout << vec << "\n";
		//int argMax = std::distance(vector.begin(), std::max_element(vector.begin(), vector.end()));
		//product->ToA_TS_QIE.push_back(dataReader->hcalQIESampleAdc)

		 // double min = *std::min_element(x.begin(), x.end());
		// double max = *std::max_element(x.begin(), x.end());

		// int argMin = std::distance(x.begin(), std::min_element(x.begin(), x.end()));
		// int argMax = std::distance(x.begin(), std::max_element(x.begin(), x.end()));


		//##############

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

	/*

	//for (auto i: vec_adc)
	//	std::cout << i << ' ';
	//auto max_iter = std::max_element(vec, vec.size());
	//auto max_iter = std::max_element(vec_adc.begin(), vec_adc.end());
	auto argmax = std::distance(vec_adc.begin(), std::max_element(vec_adc.begin(), vec_adc.end()));

	//if (max_iter == vec_adc.end()) {
		// //auto s = typeid(*max_iter).name();
	//	std::cout << "\nMax Element = skipped " << "\n";
		// //std::cout  << "\n type:" << typeid(max_iter).name() << std::endl;
	//	// //std::cout  << "\n type:" << typeid(vec.end()).name() << std::endl;
	//}
	//else {
	//int max = *max_iter;
	//int argmax = *argmax_iter;

	// // std::cout << "\nMax Element = "
    // // << *max_element(vec.begin(), vec.end());

	//}
	auto vec_size = vec_adc.size();
	int signedInt = (int) vec_size;
	//std::cout << "\nVec Size " << signedInt;

	//sum += signedInt;

	if (argmax == 0 || argmax > (signedInt-2) ){ // || argmax > 10000
		std::cout << "\n ArgMax Element = skipped " << argmax << " Vec Size " << signedInt << " ";
	}
	else{

	float int_weighted = ((double)(vec_adc.at(argmax-1) * vec_qie.at(argmax-1) + vec_adc.at(argmax) * vec_qie.at(argmax)  +vec_adc.at(argmax+1) * vec_qie.at(argmax+1) )
					/ (vec_adc.at(argmax-1) + vec_adc.at(argmax) + vec_adc.at(argmax+1)));

	//std::cout << "\nMax Arg Element at " << argmax << " with weighted value " << vec_adc.at(argmax);
	//td::cout << "\n Total vec size " << sum << " ";

	//histCollection->hist_Weighted_HcalQIESampleAdc->Fill(int_weighted);
	product->weighted_hcalQIESampleAdc.push_back(int_weighted);
	}

	*/
}

void HoProducer::EndJob(HoHistogramCollection* histCollection) {
		if (qie4cut){
		std::cout << "\nqie4 cut\n";
		}
		if (!qie4cut){
		std::cout << "\nINactive qie4 cut\n";
		}
		}
HoProducer::~HoProducer() {}
