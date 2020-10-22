#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>
#include <HOAnalysis/HOL1/interface/DataReader.h>

class BmtfInputProducer : public BaseProducer {
	private:
		TH1I *histBmtfPhSize, *histBmtfThSize, *histBmtfPhBx, *histBmtfPhWh, *histBmtfPhSe, *histBmtfPhSt, *histBmtfPhCode, *histBmtfPhTs2Tag, *histBmtfThBx, *histBmtfThWh, *histBmtfThSe, *histBmtfThSt, *histBmtfThTheta, *histBmtfThCode;
		TH1F *histBmtfPhAng, *histBmtfPhBandAng;
	public:
		BmtfInputProducer();
		~BmtfInputProducer();
		void Produce(DataReader*);
};
