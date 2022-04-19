#include <HOAnalysis/HOL1/interface/Producer/BxMatchingProducer.h>
//#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>
#include <iostream>
#include <typeinfo>
#include <algorithm>

BxMatchingProducer::BxMatchingProducer() {
	Name = "Bx Producer";
}

int false_bx_count, right_bx_count, leftover_count, correction_count;

void BxMatchingProducer::Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) {
	//int bx_size = product->dttpBx.size();
	//std::cout << "\nbx dttp size " << bx_size << "\n";
	std::vector<int> vec_adc = product->hcalQIESampleAdc;
	std::vector<int> vec_qie = product->hcalQIESample;

	for (unsigned int i = 0; i <product->isMuonMatchedDttp.size(); i++) { // product->dttpBx

		//if (product->isDttpMatchedHo.at(i)){
		//if (product->isMuonMatchedDttp.at(i)){
		// if (product->isBmtfMatchedMuon.at(i)){

			int dttp_bx = product->dttpBx.at(i);
			histCollection->hist_HoMatched_DttpBx->Fill(dttp_bx);
			//auto qie = product->hcalQIESample.at(i);
			//double TS_w = product->weighted_hcalQIESampleAdc.at(i);

			//int qie = vec_qie.at(i);
			//int adc = vec_adc.at(i);

			int argmax = std::distance(vec_adc.begin(), std::max_element(vec_adc.begin(), vec_adc.end()));
			//int max_qie = vec_qie.at(argmax);

	        auto vec_size = vec_adc.size();
	        int signedInt = (int) vec_size;
	        //std::cout << "\nVec Size " << signedInt;

	        //sum += signedInt;

	        if (argmax == 0 || argmax > (signedInt-2) ){ // || argmax > 10000
                //std::cout << "\n ArgMax Element = skipped " << argmax << " Vec Size " << signedInt << " ";
				continue;
			}
	        else{
	        float int_weighted = ((double)(vec_adc.at(argmax-1) * vec_qie.at(argmax-1) + vec_adc.at(argmax) * vec_qie.at(argmax)  +vec_adc.at(argmax+1) * vec_qie.at(argmax+1) )
	                                        / (vec_adc.at(argmax-1) + vec_adc.at(argmax) + vec_adc.at(argmax+1)));

	        histCollection->hist_Weighted_HcalQIESampleAdc->Fill(int_weighted);
	        product->weighted_hcalQIESampleAdc.push_back(int_weighted);
	        }

			// if (qie != TS_w){
			//std::cout << "\nTS_w qie diff " << TS_w << max_qie << " dttp_bx " << dttp_bx << " ";
			// }
			/*if (dttp_bx == 0 and qie == 4){
				right_bx_count +=1;
			}
			else if(dttp_bx != 0 and qie == 4){
				false_bx_count += 1;
				//dttp_bx = 0;
			}
			else if (dttp_bx != 0 and qie != 4){
				leftover_count += 1;
				//std::cout << "\nbx dttp is " << dttp_bx <<  " qie  " << qie;
			}else */
			if (product->isMuonMatchedDttp.at(i)){ //  and and dttp_bx != 0
			//std::cout << "\nbx dttp is " << dttp_bx <<  " qie  " << qie;
				correction_count += 1;
				dttp_bx = 0;
			}


			histCollection->hist_corrected_DttpBx->Fill(dttp_bx);
		//}


	//std::cout << "\nbx dttp is " << dttp_bx <<  " max qie  " << max_qie;
	//std::cout << "\nbx dttp is " << dttp_bx << " and qie is " << qie << " max qie  " << max_qie << " TS_W " << TS_w	;

	}
	//std::cout << "\nright bx: " << right_bx_count << " false bx: " << false_bx_count << " ratio " << ((double)false_bx_count)/right_bx_count << " " ;
}

void BxMatchingProducer::EndJob(HoHistogramCollection* histCollection) {
	std::cout << "\nright bx: " << right_bx_count << " false bx: " << false_bx_count << " ratio " << ((double)false_bx_count)/right_bx_count;
	std::cout << "\n" << "leftover: " << leftover_count << " corrected bx: " << correction_count << "\n";
}
BxMatchingProducer::~BxMatchingProducer() {}
