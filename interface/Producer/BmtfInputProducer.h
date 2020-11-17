#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

class BmtfInputProducer : public BaseProducer {
	private:
		TH1I *histDttpSize, *histBmtfThSize, *histDttpBx, *histDttpWheel, *histDttpSection, *histDttpStation, *histDttpQualityCode, *histDttpTs2Tag, *histBmtfThBx, *histBmtfThWh, *histBmtfThSe, *histBmtfThSt, *histBmtfThTheta, *histBmtfThCode;
		TH1S *histNBmtf, *histBmtfHwPt, *histBmtfHwEta, *histBmtfHwPhi, *histBmtfGlobalPhi, *histBmtfHwSign, *histBmtfHwSignValid, *histBmtfHwQual, *histBmtfLink, *histBmtfProcessor, *histBmtfTrackFinderType, *histBmtfHwHF, *histBmtfBx, *histBmtfWh, *histBmtfTrAdd;
		TH1F *histDttpPhi, *histDttpPhiB;
		TH1D *histBmtfCmsPt, *histBmtfCmsEta, *histBmtfCmsPhi, *histDttpCmsPhi;

	//TH2D *histDttpStation_vs_DttpWheel, *histDttpStation_vs_DttpWheel_Hq, *histDttpStation_vs_DttpWheel_Lq,
		//*histUsedDttpStation_vs_DttpWheel, *histUsedDttpStation_vs_DttpWheel_Hq, *histUsedDttpStation_vs_DttpWheel_Lq,
		//*histUnusedDttpStation_vs_DttpWheel, *histUnusedDttpStation_vs_DttpWheel_Hq, *histUnusedDttpStation_vs_DttpWheel_Lq;
	public:
		BmtfInputProducer();
		~BmtfInputProducer();
		void Produce(DataReader* dataReader, HoProduct* product);
};
