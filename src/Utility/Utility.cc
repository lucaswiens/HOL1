#include <HOAnalysis/HOL1/interface/Utility/Utility.h>

double Utility::DeltaPhi(double phi1, double phi2) {
	double deltaPhi = phi1 - phi2;
	while (deltaPhi >  M_PI) deltaPhi -= 2 * M_PI;
	while (deltaPhi < -M_PI) deltaPhi += 2 * M_PI;
	return deltaPhi;
}

int Utility::DeltaIPhi(int iPhi1, int iPhi2) {
	int deltaIPhi = iPhi1 - iPhi2;
	deltaIPhi = (deltaIPhi >  36) ? deltaIPhi - 72 : deltaIPhi;
	deltaIPhi = (deltaIPhi < -36) ? deltaIPhi + 72 : deltaIPhi;
	return deltaIPhi;
}

double Utility::DeltaR(const double &eta1, const double &phi1, const double &eta2, const double &phi2) {
	double deltaEta = eta1 - eta2;
	double deltaPhi = Utility::DeltaPhi(phi1, phi2);
	return std::sqrt(deltaPhi * deltaPhi + deltaEta * deltaEta);
}

//DTTP conversion functions
double Utility::DttpPhiToCmsPhi(double phi, int dttpSection) {
	// dttpSection must be [0, 11]
	double cmsPhi = phi / 4096.0 + M_PI / 6 * dttpSection;
	return (cmsPhi > M_PI) ? cmsPhi - 2 * M_PI : cmsPhi;
}

int Utility::CmsPhiToHoIPhi(double cmsPhi) {
	// [-pi, pi] to [1, 72]
	//cmsPhi = (cmsPhi <= 0) ? cmsPhi + 2 * M_PI : cmsPhi;
	//double iPhi  = cmsPhi * 72 / 2 / M_PI + 0.5;
	//return (int)std::round(iPhi);

	double dPhi = 2*M_PI/72;
	cmsPhi = (cmsPhi < 0)? cmsPhi + 2 * M_PI : cmsPhi;
	int iPhi = (int) (fabs(cmsPhi)/dPhi + 1);
	return iPhi;
}

// BMTF Muon conversion functions
// https://github.com/HOTriggerLink/cmssw/blob/HO_dev/DataFormats/L1TMuon/interface/RegionalMuonCand.h
double Utility::BmtfGlobalPhiToCmsPhi(int bmtfGlobalPhi) {
	// globalPhi in [0, 576]
	double cmsPhi = 2 * M_PI / 576 * bmtfGlobalPhi;
	return (cmsPhi > M_PI) ? cmsPhi - 2 * M_PI : cmsPhi;
}

double Utility::BmtfEtaToCmsEta(int bmtfEta) {
	return bmtfEta * 0.010875;
}

double Utility::BmtfPtToCmsPt(int bmtfPt) {
	return bmtfPt * 0.5;
}

int Utility::GetBmtfStationMask(std::vector<int> trackerAddresses) {
	int stationMask = 0;

	if(trackerAddresses.at(0) != 3) { stationMask |= (1<<0);} //MB1
	if(trackerAddresses.at(1) != 15) { stationMask |= (1<<1);} //MB2
	if(trackerAddresses.at(2) != 15) { stationMask |= (1<<2);} //MB3
	if(trackerAddresses.at(3) != 15) { stationMask |= (1<<3);} //MB4

	return stationMask;
}

//HO conversion Functions
int Utility::CmsEtaToHoIEta(double cmsEta) {
	const double &dEta = 2 * M_PI / 72;
	int sign = (cmsEta >= 0) - (cmsEta < 0);
	int iEta = (int)(cmsEta / dEta + sign);
	return iEta;
}

int Utility::CmsEtaToHoSubIEta(double cmsEta, int nDiv) {
	const double &dEta = 2 * M_PI / 72;
	double dSubEta = dEta / nDiv;
	int sign = (cmsEta >= 0) - (cmsEta < 0);

	double remainderEta = fmod(fabs(cmsEta), dEta);
	int subIEta = int(remainderEta / dSubEta + 1);
	return sign * subIEta;
}
double Utility::HoIEtaToCmsEta(int hoIEta) {
	/*
	// Eta segmentation in HO is 2*pi/72 = ~0.087
	double dEta = 2 * M_PI / 72;

	// use (|iEta| + |iEta|-1) / 2 as mean
	int sign = (hoIEta >= 0) - (hoIEta < 0);
	double cmsEta = (hoIEta - sign / 2) * dEta;

	//double cmsEta = hoIEta * dEta;
	return cmsEta;
	*/
	// Eta segmentation in HO is 2*pi/72 = ~0.087
	double dEta = 2*M_PI/72;

	double sign = (hoIEta < 0) ? -1: 1;

	// Take the mean eta
	double eta = (fabs(hoIEta)-1 + fabs(hoIEta)) / 2 * dEta;
	eta *= sign;

	return eta;
}

double Utility::HoIPhiToCmsPhi(int hoIPhi) {
	/*
	/// // Phi segmentation in HO is 0.087
	double cmsPhi = (hoIPhi - 0.5) * 2 * M_PI / 72;
	//double cmsPhi = hoIPhi * 2 * M_PI / 72;
	return (cmsPhi > M_PI) ? cmsPhi - 2 * M_PI : cmsPhi;
	*/
	// Phi segmentation in HO is 0.087
	double dPhi = 2.0*M_PI/72.0;

	// Take the mean phi
	double phi = (fabs(hoIPhi)-1 + fabs(hoIPhi)) / 2 * dPhi;

	if(phi > M_PI)
	{
		phi -= 2*M_PI;
	}

	return phi;
}

int Utility::HoIPhiToSection(int iPhi) {
	int secNum = (iPhi + 1) % 72;
	secNum = (int) (secNum / 6.0);
	return secNum;
	//return iPhi / 6;
}

int Utility::HoIEtaToWheel(int iEta) {
	if(iEta < -10) { return -2;}
	if(-11 < iEta && iEta < -4) { return -1;}
	if( -5 < iEta && iEta <  5) { return 0;}
	if(  4 < iEta && iEta < 11) { return 1;}
	if(iEta > 10) { return 2;}
	return -999;
}

bool Utility::BmtfMuonIndexToIsBmtf(short index) {
	//TF_index = 36 + (int)(L1UpgradeTree.muonTfMuonIdx[iMu] / 3.);
	//where TF_index is:
	//EMTF+ : 36-41,
	//OMTF+ : 42-47,
	//BMTF : 48-59,
	//OMTF- : 60-65,
	//EMTF- : 66-71
	int tfIndex = 36 + (int)(index / 3);
	return 47 < tfIndex && tfIndex < 60;
}
