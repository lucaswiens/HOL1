#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>

#include <HOAnalysis/HOL1/interface/DataReader.h>
#include <HOAnalysis/HOL1/interface/HoProduct.h>
#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/HoCoincidenceProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>

void ProgressBar(const int &, const int &);

int main(int argc, char* argv[]) {
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	std::string inputFile = std::string(argv[1]);
	std::string outputFile = std::string(argv[2]);

	DataReader* dataReader = new DataReader(inputFile);

	TFile *file = new TFile((outputFile + ".root").c_str(), "RECREATE");

	//Declare vector of Producers which will fill Histograms
	std::vector<std::shared_ptr<BaseProducer>> producers = {
		std::shared_ptr<HoProducer>(new HoProducer()),
		std::shared_ptr<MuonProducer>(new MuonProducer()),
		std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer()),
		std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer()),
		std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer()),
	};

	int processed = 0;
	ProgressBar(0, 0);
	while(dataReader->Next()){
		//ProgressBar
		if(processed % 400) {
			ProgressBar((int) 101 * processed/dataReader->GetEntries(), processed / std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count());
		}
		processed++;

		HoProduct product;
		for (std::shared_ptr<BaseProducer> producer: producers) {
			producer->Produce(dataReader, &product);
		}
	}
	ProgressBar(100, processed / std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count());
	std::cout << std::endl;

	file->Write();
	file->Close();

	delete dataReader;
	delete file;

	return 0;
}

void ProgressBar(const int &progress, const int &rate) {
	std::string progressBar = "[";

	for (int i = 0; i < progress - 1; i++) {
		progressBar += "·";
	}
	if (progress == 100) { progressBar += "·";}
	else if (progress % 2 == 0) { progressBar += "c";}
	else { progressBar += "C";}

	for (int i = 0; i < 100 - progress; i++) {
		progressBar += "•";
	}

	progressBar = progressBar + "] " + std::to_string(progress) + "% of Events processed at a rate of " + std::to_string(rate) + " Hz." ;
	std::cout << "\r" << progressBar << std::flush;
}

