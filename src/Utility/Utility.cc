#include <HOAnalysis/HOL1/interface/Utility/Utility.h>

double Utility::DeltaPhi(double phi1, double phi2) {
	double deltaPhi = phi1 - phi2;
	while (deltaPhi > M_PI) deltaPhi -= 2 * M_PI;
	while (deltaPhi < -M_PI) deltaPhi += 2 * M_PI;
	return deltaPhi;
}

int Utility::DeltaIPhi(int iPhi1, int iPhi2) {
	int deltaIPhi = iPhi1 - iPhi2;
	deltaIPhi = (deltaIPhi > 36) ? deltaIPhi - 72 : deltaIPhi;
	deltaIPhi = (deltaIPhi < -36) ? deltaIPhi + 72 : deltaIPhi;
	return deltaIPhi;
}

double Utility::DeltaR(const double &eta1, const double &phi1, const double &eta2, const double &phi2) {
	return std::sqrt(std::pow(phi1 - phi2, 2) + std::pow(eta1 - eta2, 2));
}

//double Utility::PhiBToPt(int phiB, std::vector <int> *v_phiB, std::vector <double> *v_pT);
//DTTP conversion functions
double Utility::DttpPhiToCmsPhi(double phi, int dttpSection) {
	// dttpSection must be [1, 12]
	//if ((dttpSection < 1) && (12 < dttpSection)) { return -999;} // TODO use assure instead

	double cmsPhi = phi / 4096.0 + M_PI / 6 * (dttpSection - 1);
	return (cmsPhi > M_PI) ? cmsPhi - 2 * M_PI : cmsPhi;
}

double Utility::CmsPhiToHoIPhi(double cmsPhi) {
	// [-pi, pi] to [1, 72]
	double dPhi = 2 * M_PI / 72;
	cmsPhi = (cmsPhi < 0) ? cmsPhi + 2 * M_PI : cmsPhi;
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
	// Eta segmentation in HO is 2*pi/72 = ~0.087
	double dEta = 2 * M_PI / 72;
	int sign = (hoIEta >= 0) - (hoIEta < 0);

	// use (|iEta| + |iEta|-1) / 2 as mean
	double meanEta = (hoIEta - sign / 2) * dEta;
	return meanEta;
}

double Utility::HoIPhiToCmsPhi(int hoIPhi) {
	// Phi segmentation in HO is 0.087
	double dPhi = 2.0 * M_PI / 72.0;
	// Take the mean phi
	//double phi = (fabs(iPhi)-1 + fabs(iPhi)) / 2 * dPhi;
	int sign = (hoIPhi > 0) - (hoIPhi < 0);
	double meanPhi = (hoIPhi - sign / 2) * dPhi;
	return (meanPhi > M_PI) ? meanPhi - 2 * M_PI : meanPhi;
}

int Utility::HoIPhiToSection(int iPhi) {
	int secNum = (iPhi + 1) % 72;
	secNum = (int) (secNum / 6.0 + 1);
	return secNum;
}
int Utility::HoIEtaToWheel(int iEta) {
	if(iEta < -10) { return -2;}
	if(-11 < iEta && iEta < -4) { return -1;}
	if( -5 < iEta && iEta <  5) { return 0;}
	if(  4 < iEta && iEta < 11) { return 1;}
	if(iEta > 10) { return 2;}
	return -999;
}

//double Utility::IEtaToEta(int iEta);
//double Utility::IPhiToPhi(int iPhi);
//int Utility::PhiToIPhi(double phi);
//int Utility::GetBmtfstationMask(int trackerAddressMB1, int trackerAddressMB2, int trackerAddressMB3, int trackerAddressMB4) {
//bool Utility::IsEtaMatchedMB34HO(int iEtaHO, int whNumDttp, int stNumDttp);
//int Utility::GetHo3x3Hits(int HoTpIEta, int HoTpIPhi, std::vector <int> *v_HoTpIEta, std::vector <int> *v_HoTpIPhi, std::vector <int> *v_HoTpBits, int HoTpBitsSoi);
