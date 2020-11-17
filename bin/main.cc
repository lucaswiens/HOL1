#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>

#include <HOAnalysis/HOL1/interface/DataReader.h>
#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>

void ProgressBar(const int &, const int &);

int main(int argc, char* argv[]) {
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	std::string inputFile = std::string(argv[1]);

	DataReader* dataReader = new DataReader(inputFile);

	TFile *file = new TFile("L1Histograms.root", "RECREATE");

	//Declare vector of Producers which will fill Histograms
	std::vector<std::shared_ptr<BaseProducer>> producers = {
		std::shared_ptr<HoProducer>(new HoProducer()),
		std::shared_ptr<MuonProducer>(new MuonProducer()),
		std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer()),
	};

	int processed = 0;
	ProgressBar(0, 0);
	while(dataReader->Next()){
		//ProgressBar
		if(processed % 10000) {
			ProgressBar(processed, processed / std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count());
		}

		for (std::shared_ptr<BaseProducer> producer: producers) {
			producer->Produce(dataReader);
		}
	}
	ProgressBar(100, processed / std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count());

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

	if (progress == 100) std::cout << std::endl;
}

