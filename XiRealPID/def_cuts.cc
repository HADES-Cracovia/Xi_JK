#include "fwdet_res.h"

#include "hgeantfwdet.h"
#include "fwdetdef.h"
#include "hfwdetstrawcalsim.h"
#include "hfwdetcand.h"
#include "hfwdetcandsim.h"

#include "hparticlecandsim.h"
#include "hparticlecand.h"
#include "hparticletool.h"

#include "hloop.h"
#include "hcategory.h"

#include <TCanvas.h>
#include <TStyle.h>
#include <sstream>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TPaveText.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TLine.h>
#include <TSpectrum.h>

#include "massPID.cc"
#include "mass2PID.cc"
#include "mass2PIDfit.cc"
#include "tofPID.cc"

#define PR(x) std::cout << "++DEBUG: " << #x << " = |" << x << "| (" << __FILE__ << ", " << __LINE__ << ")\n";

using namespace std;

HGeomVector calcPrimVertex_Track_Mother(const std::vector<HParticleCand *>cands, const HGeomVector & DecayVertex, const HGeomVector & dirMother, int trackA_num, int trackB_num);
HGeomVector calcPrimVertex_Track_Mother(const std::vector<HParticleCand *>cands, const HGeomVector & beamVector, const HGeomVector & DecayVertex, const HGeomVector & dirMother, int trackA_num, int trackB_num);

Int_t fwdet_tests(HLoop * loop, const AnaParameters & anapars)
{
    if (!loop->setInput(""))
    {                                                    // reading file structure
        std::cerr << "READBACK: ERROR : cannot read input !" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    gStyle->SetOptStat(1);
    gStyle->SetOptFit(1);

    TStopwatch timer;
    timer.Reset();
    timer.Start();

    //////////////////////////////////////////////////////////////////////////////
    //      Fast tree builder for creating of ntuples                            //
    //////////////////////////////////////////////////////////////////////////////

    loop->printCategories();    // print all categories found in input + status

    HCategory * fCatGeantKine = nullptr;
    fCatGeantKine = HCategoryManager::getCategory(catGeantKine, kTRUE, "catGeantKine");
    if (!fCatGeantKine)
    {
        cout << "No catGeantKine!" << endl;
        exit(EXIT_FAILURE);  // do you want a brute force exit ?
    }

    HCategory * fFwDetStrawCal = nullptr;
    fFwDetStrawCal = HCategoryManager::getCategory(catFwDetStrawCal, kTRUE, "catFwDetStrawCal");
    if (!fFwDetStrawCal)
    {
        cout << "No catFwDetStrawCal!" << endl;
        exit(EXIT_FAILURE);  // do you want a brute force exit ?
    }

    HCategory * fFwDetStrawCalSim = nullptr;
    fFwDetStrawCalSim = HCategoryManager::getCategory(catFwDetStrawCal, kTRUE, "catFwDetStrawCalSim");
    if (!fFwDetStrawCalSim)
    {
	cout << "No catFwDetStrawCalSim!" << endl;
	//exit(EXIT_FAILURE);  // do you want a brute force exit ?
    }
    
    HCategory * fCatFwDetCandSim = nullptr;
    fCatFwDetCandSim = HCategoryManager::getCategory(catFwDetCand, kTRUE, "catFwDetCand");
    if (!fCatFwDetCandSim)
    {
        cout << "No catFwDetCand!" << endl;
	//exit(EXIT_FAILURE);  // do you want a brute force exit ?
    }

    HCategory * fCatParticleCandSim= nullptr;
    fCatParticleCandSim = HCategoryManager::getCategory(catParticleCand, kTRUE, "catParticleCand");
    if(!fCatParticleCandSim)
    {
	cout<< "No catParticleCandSim!"<<endl;
    }

    Int_t entries = loop->getEntries();
    //     //setting numbers of events regarding the input number of events by the user
    if (anapars.events < entries and anapars.events >= 0 ) entries = anapars.events;

    //     // specify output file
    TFile * output_file = TFile::Open(anapars.outfile, "RECREATE");
   
    //    //read defined cuts from file
    TFile *fCut = TFile::Open(anapars.cutfile);
    int partN = 15;
    TCutG *gCut[partN];
    int pidNo = 0;
    int k = 0;

    //this PID not used now -> use mass2PID()
    for(pidNo; pidNo < partN; pidNo++){
	char cutName[50];
	sprintf(cutName, "CUTG_%02d", pidNo);
	if(!(TCutG*)fCut -> Get(cutName)) sprintf(cutName, "CUTG_%02d", 0);
	gCut[k] = (TCutG*)fCut -> Get(cutName) -> Clone();
	cout << "cutName: " << cutName << endl;
	k++;
    }

    //check the strange structure on dEdx tof spectrum
    TFile *fCutdedx = TFile::Open("cut_dedxtof.root");
    TCutG *gCutdedx = (TCutG*)fCutdedx -> Get("CUTG") -> Clone();;
    
    //read parametrization for mass cut PID
    ifstream fPID;
    fPID.open(anapars.pidfile);
    int npar = 16;
    double fitpar[npar];
    while(fPID.is_open()){
	cout << "fitpar: ";
	for(int i = 0; i < npar; i++){
    	    fPID >> fitpar[i];
	    cout << "i=" << i << " " << fitpar[i] << endl; 
    	}
	fPID.close();
	}
    int nPartSpec = 4;

    int mom1 = -2000;
    int mom2 = 2000;
    double bet1 = 0;
    double bet2 = 2;
    int ekin1 = 0;
    int ekin2 = 2000;
    int mas1 = -500;
    int mas2 = 2000;
    int mas21 = -200000;
    int mas22 = 1500000;
    int dex1 = 0;
    int dex2 = 30;
    int tofh1 = 0;
    int tofh2 = 50;
    int toff1 = 0;
    int toff2 = 40;

    int nbins2 = 400;
    int nbins1 = 200; 
    
    //HADES only
    TH2F *hdEdx_mdc = new TH2F("hdEdx_mdc", "hdEdx_mdc", nbins2, mom1, mom2, nbins1, dex1, dex2);
    TH2F *hBeta_h = new TH2F("hBeta_h", "hBeta_h", nbins2, mom1, mom2, nbins1, bet1, bet2);
    TH2F *hEkin_h = new TH2F("hEkin_h", "hEkin_h", nbins2, mom1, mom2, nbins1, ekin1, ekin2);
    TH2F *hM2_h = new TH2F("hM2_h", "hM2_h", nbins2, mom1, mom2 , nbins1, mas1, mas2);
    TH2F *hM22_h = new TH2F("hM22_h", "hM22_h", nbins2, mom1, mom2 , nbins1, mas21, mas22);
    TH1F *hM1_h = new TH1F("hM1_h", "hM1_h", nbins1, mas1, mas2);
    TH1F *hM12_h = new TH1F("hM12_h", "hM12_h", nbins1, mas21, mas22);
    TH1F *hM12_h_m2 = new TH1F("hM12_h_m2", "hM12_h_m2", nbins1, mas21, mas22);
    TH1F *hM12_h_pos = new TH1F("hM12_h_pos", "hM12_h_pos", nbins1, mas21, mas22);
    TH1F *hM12_h_neg = new TH1F("hM12_h_neg", "hM12_h_neg", nbins1, mas21, mas22);
    TH1F *hM12_h_pions = new TH1F("hM12_h_pions", "hM12_h_pions", nbins1, -60000, 60000);
//    TH2F *hBeta_q_h = new TH2F("hBeta_q_h", "hBeta_q_h", nbins2, -10, 10, nbins1, bet1, bet2);
    TH2F *hBeta_m_h = new TH2F("hBeta_m_h", "hBeta_h_afterMassPID", nbins2, mom1, mom2, nbins1, bet1, bet2);
    TH2F *hM2_m_h = new TH2F("hM2_m_h", "hM2_m_h", nbins2, mom1, mom2, nbins1, mas1, mas2);
    TH2F *hM22_m_h = new TH2F("hM22_m_h", "hM22_m_h", nbins2, mom1, mom2, nbins1, mas21, mas22);
    TH1F *hM1_m_h = new TH1F("hM1_m_h", "hM1_m_h", nbins1, mas1, mas2);
    TH1F *hM12_m_h = new TH1F("hM12_m_h", "hM12_m_h", nbins1, mas21, mas22);
    TCanvas *cBetaPID_h = new TCanvas("cBetaPID_h", "cBetaPID_h");
    TCanvas *cMassPID_h = new TCanvas("cMassPID_h", "cMassPID_h", 1200, 800);
    TCanvas *cMassPID_pions = new TCanvas("cMassPID_pions","cMassPID_pions", 1200, 800);
    
    //tof (system==1)
    TH2F *hdEdx_tof = new TH2F("hdEdx_tof", "hdEdx_tof", nbins2, mom1, mom2, nbins1, dex1, dex2);
    TH2F *hBeta_tof = new TH2F("hBeta_tof", "hBeta_tof", nbins2, mom1, mom2, nbins1, bet1, bet2);
    TH2F *hEkin_tof = new TH2F("hEkin_tof", "hEkin_tof", nbins2, mom1, mom2, nbins1, ekin1, ekin2);
    TH2F *hM2_tof = new TH2F("hM2_tof", "hM2_tof", nbins2, mom1, mom2, nbins1, mas1, mas2);
    TH2F *hM22_tof = new TH2F("hM22_tof", "hM22_tof", nbins2, mom1, mom2, nbins1, mas21, mas22);
    TH1F *hM1_tof = new TH1F("hM1_tof", "hM1_tof", nbins1, mas1, mas2);
    TH1F *hM12_tof = new TH1F("hM12_tof", "hM12_tof", nbins1, mas21, mas22);
    TH2F *hBeta_m_tof = new TH2F("hBeta_m_tof", "hBeta_m_tof", nbins2, mom1, mom2, nbins1, bet1, bet2);
    TH2F *hM2_m_tof = new TH2F("hM2_m_tof", "hM2_m_tof", nbins2, mom1, mom2, nbins1, mas1, mas2);
    TH2F *hM22_m_tof = new TH2F("hM22_m_tof", "hM22_m_tof", nbins2, mom1, mom2, nbins1, mas21, mas22);
    TH1F *hM1_m_tof = new TH1F("hM1_m_tof", "hM1_m_tof", nbins1, mas1, mas2);
    TH1F *hM12_m_tof = new TH1F("hM12_m_tof", "hM12_m_tof", nbins1, mas21, mas22);
    TCanvas *cBetaPID_tof = new TCanvas("cBetaPID_tof", "cBetaPID_tof");

    //check dedx tof
    TH2F *hcheckdedx_dedxmdc = new TH2F("hcheckdedx_dedxmdc", "hcheckdedx_dedxmdc", nbins2, mom1, mom2, nbins1, dex1, dex2);
    TH2F *hcheckdedx_btof = new TH2F("hcheckdedx_btof", "hcheckdedx_btof", nbins2, mom1, mom2, nbins1, bet1, bet2);
    

    //RPC (system==0)
    TH2F *hdEdx_rpc = new TH2F("hdEdx_rpc", "hdEdx_rpc", nbins2, mom1, mom2, nbins1, dex1, dex2);
    TH2F *hBeta_rpc = new TH2F("hBeta_rpc", "hBeta_rpc", nbins2, mom1, mom2, nbins1, bet1, bet2);
    TH2F *hEkin_rpc = new TH2F("hEkin_rpc", "hEkin_rpc", nbins2, mom1, mom2, nbins1, ekin1, ekin2);
    TH2F *hM2_rpc = new TH2F("hM2_rpc", "hM2_rpc", nbins2, mom1, mom2, nbins1, mas1, mas2);
    TH2F *hM22_rpc = new TH2F("hM22_rpc", "hM22_rpc", nbins2, mom1, mom2, nbins1, mas21, mas22);
    TH1F *hM1_rpc = new TH1F("hM1_rpc", "hM1_rpc", nbins1, mas1, mas2);
    TH1F *hM12_rpc = new TH1F("hM12_rpc", "hM12_rpc", nbins1, mas21, mas22);
    TH2F *hBeta_m_rpc = new TH2F("hBeta_m_rpc", "hBeta_m_rpc", nbins2, mom1, mom2, nbins1, bet1, bet2);
    TH2F *hM2_m_rpc = new TH2F("hM2_m_rpc", "hM2_m_rpc", nbins2, mom1, mom2, nbins1, mas1, mas2);
    TH2F *hM22_m_rpc = new TH2F("hM22_m_rpc", "hM22_m_rpc", nbins2, mom1, mom2, nbins1, mas21, mas22);
    TH1F *hM1_m_rpc = new TH1F("hM1_m_rpc", "hM1_m_rpc", nbins1, mas1, mas2);
    TH1F *hM12_m_rpc = new TH1F("hM12_m_rpc", "hM12_m_rpc", nbins1, mas21, mas22);
    TCanvas *cBetaPID_rpc = new TCanvas("cBetaPID_rpc", "cBetaPID_rpc");
    
    //FwDet only
    TH1F *hdE_fd = new TH1F("hdE_fd", "hdE_fd", 200, 0, .1);
    TH1F *hr_fd = new TH1F("hr_fd", "hr_fd", 20, 0, 10);
    TH2F *hBeta_fd = new TH2F("hBeta_fd", "hBeta_fd", 400, -2000, 2000, 200, bet1, bet2);
    TH2F *hM22_fd = new TH2F("hM22_fd", "hM22_fd", nbins2, mom1, mom2 , nbins1, mas21, mas22);
    TH2F *hdetof_fd = new TH2F("hdetof_fd", "hdetof_fd", nbins2, 0, .1 , nbins1, toff1, toff2);
    TH2F *hdetof_fd_Geant = new TH2F("hdetof_fd_Geant", "hdetof_fd_Geant", nbins2, 0, .1 , nbins1, toff1, toff2);
    TH2F *hdetof_fd_Geant9 = new TH2F("hdetof_fd_Geant9", "hdetof_fd_Geant9", nbins2, 0, .1 , nbins1, toff1, toff2);
    TH2F *hdetof_fd_Geant11 = new TH2F("hdetof_fd_Geant11", "hdetof_fd_Geant11", nbins2, 0, .1 , nbins1, toff1, toff2);
    TH2F *hdetof_fd_Geant14 = new TH2F("hdetof_fd_Geant14", "hdetof_fd_Geant14", nbins2, 0, .1 , nbins1, toff1, toff2);
    
    //ToF
    //H&FD
    TH1F *hTof_pim = new TH1F("hTof_pim", "hTof_pim", nbins1, tofh1, tofh2);
    TH1F *hTof_pip = new TH1F("hTof_pip", "hTof_pip", nbins1, tofh1, tofh2);
    TH1F *hTof_Kp = new TH1F("hTof_Kp", "hTof_Kp", nbins1, tofh1, tofh2);
    TH1F *hTof_p = new TH1F("hTof_p", "hTof_p", nbins1, tofh1, tofh2);
    TH1F *hTof_all = new TH1F("hTof_all", "hTof_all", nbins1, tofh1, tofh2);
    TCanvas *cTof = new TCanvas("cTof", "cTof");
    cTof -> Divide(2,2);
    //H
    TH1F *hTof_pim_h = new TH1F("hTof_pim_h", "hTof_pim_h", nbins1, tofh1, tofh2);
    TH1F *hTof_pip_h = new TH1F("hTof_pip_h", "hTof_pip_h", nbins1, tofh1, tofh2);
    TH1F *hTof_Kp_h = new TH1F("hTof_Kp_h", "hTof_Kp_h", nbins1, tofh1, tofh2);
    TH1F *hTof_p_h = new TH1F("hTof_p_h", "hTof_p_h", nbins1, tofh1, tofh2);
    TH1F *hTof_all_h = new TH1F("hTof_all_h", "hTof_all_h", nbins1, tofh1, tofh2);
    TCanvas *cTof_h = new TCanvas("cTof_h", "cTof_h");
    cTof_h -> Divide(2,2);
    //FD
    TH1F *hTof_pim_fd = new TH1F("hTof_pim_fd", "hTof_pim_fd", nbins1, toff1, toff2);
    TH1F *hTof_pip_fd = new TH1F("hTof_pip_fd", "hTof_pip_fd", nbins1, toff1, toff2);
    TH1F *hTof_Kp_fd = new TH1F("hTof_Kp_fd", "hTof_Kp_fd", nbins1, toff1, toff2);
    TH1F *hTof_p_fd = new TH1F("hTof_p_fd", "hTof_p_fd", nbins1, toff1, toff2);
    TH1F *hTof_all_fd = new TH1F("hTof_all_fd", "hTof_all_fd", nbins1, toff1, toff2);
    TCanvas *cTof_fd = new TCanvas("cTof_fd", "cTof_fd");
    cTof_fd -> Divide(2,2);
    TCanvas *cTof1_fd = new TCanvas("cTof1_fd", "cTof1_fd");

    //ToF _GeantID
    //H&FD
    TH1F *hTof_pim_GeantID = new TH1F("hTof_pim_GeantID", "hTof_pim_GeantID", nbins1, tofh1, tofh2);
    TH1F *hTof_pip_GeantID = new TH1F("hTof_pip_GeantID", "hTof_pip_GeantID", nbins1, tofh1, tofh2);
    TH1F *hTof_Kp_GeantID = new TH1F("hTof_Kp_GeantID", "hTof_Kp_GeantID", nbins1, tofh1, tofh2);
    TH1F *hTof_p_GeantID = new TH1F("hTof_p_GeantID", "hTof_p_GeantID", nbins1, tofh1, tofh2);
    TH1F *hTof_all_GeantID = new TH1F("hTof_all_GeantID", "hTof_all_GeantID", nbins1, tofh1, tofh2);
    TCanvas *cTof_GeantID = new TCanvas("cTof_GeantID", "cTof_GeantID");
    cTof_GeantID -> Divide(2,2);
    //H
    TH1F *hTof_pim_h_GeantID = new TH1F("hTof_pim_h_GeantID", "hTof_pim_h_GeantID", nbins1, tofh1, tofh2);
    TH1F *hTof_pip_h_GeantID = new TH1F("hTof_pip_h_GeantID", "hTof_pip_h_GeantID", nbins1, tofh1, tofh2);
    TH1F *hTof_Kp_h_GeantID = new TH1F("hTof_Kp_h_GeantID", "hTof_Kp_h_GeantID", nbins1, tofh1, tofh2);
    TH1F *hTof_p_h_GeantID = new TH1F("hTof_p_h_GeantID", "hTof_p_h_GeantID", nbins1, tofh1, tofh2);
    TH1F *hTof_all_h_GeantID = new TH1F("hTof_all_h_GeantID", "hTof_all_h_GeantID", nbins1, tofh1, tofh2);
    TCanvas *cTof_h_GeantID = new TCanvas("cTof_h_GeantID", "cTof_h_GeantID");
    cTof_h_GeantID -> Divide(2,2);
    //FD
    TH1F *hTof_pim_fd_GeantID = new TH1F("hTof_pim_fd_GeantID", "hTof_pim_fd_GeantID", nbins1, toff1, toff2);
    TH1F *hTof_pip_fd_GeantID = new TH1F("hTof_pip_fd_GeantID", "hTof_pip_fd_GeantID", nbins1, toff1, toff2);
    TH1F *hTof_Kp_fd_GeantID = new TH1F("hTof_Kp_fd_GeantID", "hTof_Kp_fd_GeantID", nbins1, toff1, toff2);
    TH1F *hTof_p_fd_GeantID = new TH1F("hTof_p_fd_GeantID", "hTof_p_fd_GeantID", nbins1, toff1, toff2);
    TH1F *hTof_all_fd_GeantID = new TH1F("hTof_all_fd_GeantID", "hTof_all_fd_GeantID", nbins1, toff1, toff2);
    TCanvas *cTof_fd_GeantID = new TCanvas("cTof_fd_GeantID", "cTof_fd_GeantID");
    cTof_fd_GeantID -> Divide(2,2);
    TCanvas *cTof1_fd_GeantID = new TCanvas("cTof1_fd_GeantID", "cTof1_fd_GeantID");
    
    TLegend *l1 = new TLegend(.7,.6,.9,.8);
    l1 -> SetFillStyle(0);
    l1 -> SetBorderSize(0);
    l1 -> SetTextSize(.05);

    TCanvas *cBetaPID = new TCanvas("cBetaPID", "cBetaPID", 800, 600);
    cBetaPID -> Divide(2,2);


    //mass spectra
    //Lambda
    int immin=1050;
    int immax=1200;
    int imres=250;
    //no cuts
    //H-H + H-F
    TCanvas* cMassLambda=new TCanvas("cMassLambda","Reconstructed Lambda mass");
    TH1F* hMLAll=new TH1F("hMLAll","reconstructed mass of all particles combinations",imres,immin,immax);
    TH1F* hMLPiHades=new TH1F("hMLPiHades","reconstructed mass of all combinations: pion in HADES",imres,immin,immax);
    TH1F* hMLPiHpF=new TH1F("hMLPiHpF","reconstructed mass of all combinations: pion in HADES, 2. part. proton",imres,immin,immax);
    TH1F* hrealL=new TH1F("hrealL","reconstructed mass of pion (in HADES) and proton from #Lambda",imres,immin,immax);
    //H-H
    TH1F* hMLAll_HH=new TH1F("hMLAll_HH","reconstructed mass of all particles combinations (H-H)",imres,immin,immax);
    TH1F* hMLPiHades_HH=new TH1F("hMLPiHades_HH","reconstructed mass of all combinations: pion and 2. part. in HADES",imres,immin,immax);
    TH1F* hMLPiHpF_HH=new TH1F("hMLPiHpF_HH","reconstructed mass of all combinations: pion and proton in HADES",imres,immin,immax);
    TH1F* hrealL_HH=new TH1F("hrealL_HH","reconstructed mass of pion and proton (in HADES) from #Lambda",imres,immin,immax);
    //H-F
    TH1F* hMLAll_HF=new TH1F("hMLAll_HF","reconstructed mass of all particles combinations (H-F)",imres,immin,immax);
    TH1F* hMLPiHades_HF=new TH1F("hMLPiHades_HF","reconstructed mass of all combinations: pion in HADES and 2. part. in FD",imres,immin,immax);
    TH1F* hMLPiHpF_HF=new TH1F("hMLPiHpF_HF","reconstructed mass of all combinations: pion in HADES, proton in FD",imres,immin,immax);
    TH1F* hrealL_HF=new TH1F("hrealL_HF","reconstructed mass of pion in HADES and proton in FD from #Lambda",imres,immin,immax);

    //MTD_L
    //H-H + H-F
    TH1F* hMLPiHadesMTD=new TH1F("hMLPiHadesMTD","reconstraced mass of all combinations: pion in Hades, distance between tracks <x",imres,immin,immax);
    TH1F* hMLPiHpFMTD=new TH1F("hMLPiHpFMTD","reconstraced mass of all combinations: pion in HADES, proton in FD, distance between tracks <x",imres,immin,immax);
    TH1F* hrealLMTD=new TH1F("hrealLMTD","reconstraced mass of pion in HADES and proton in FD from #Lambda, distance between tracks <x",imres,immin,immax);
    //H-H
    TH1F* hMLPiHadesMTD_HH=new TH1F("hMLPiHadesMTD_HH","reconstructed mass of all combinations: pion in Hades, 2. part. in HADES, distance between tracks <x",imres,immin,immax);
    TH1F* hMLPiHpFMTD_HH=new TH1F("hMLPiHpFMTD_HH","reconstructed mass of all combinations: pion in HADES, proton in HADES, distance between tracks <x",imres,immin,immax);
    TH1F* hrealLMTD_HH=new TH1F("hrealLMTD_HH","reconstructed mass of pion in HADES and proton in HADES from #Lambda, distance between tracks <x",imres,immin,immax);
    //H-F
    TH1F* hMLPiHadesMTD_HF=new TH1F("hMLPiHadesMTD_HF","reconstructed mass of all combinations: pion in Hades, 2. part. in FD, distance between tracks <x",imres,immin,immax);
    TH1F* hMLPiHpFMTD_HF=new TH1F("hMLPiHpFMTD_HF","reconstructed mass of all combinations: pion in HADES, proton in FD, distance between tracks <x",imres,immin,immax);
    TH1F* hrealLMTD_HF=new TH1F("hrealLMTD_HF","reconstructed mass of pion in HADES and proton in FD from #Lambda, distance between tracks <x",imres,immin,immax);
    
    //VERTz_L
    //H-H + H-F
    TH1F* hMLPiHadesMTDVert=new TH1F("hMLPiHadesMTDVert","reconstructed mass of all combinations: pion in Hades, 2. part in HADES/FD distance between tracks <x, Vertz_L in range",imres,immin,immax);
    TH1F* hMLPiHpFMTDVert=new TH1F("hMLPiHpFMTDVert","reconstructed mass of all combinations: pion in HADES, proton in HADES/FD, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    TH1F* hrealLMTDVert=new TH1F("hrealLMTDVert","reconstraced mass of pion in HADES and proton in HADES/FD from #Lambda, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    //H-H
    TH1F* hMLPiHadesMTDVert_HH=new TH1F("hMLPiHadesMTDVert_HH","reconstructed mass of all combinations: pion in Hades, 2. part. in HADES, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    TH1F* hMLPiHpFMTDVert_HH=new TH1F("hMLPiHpFMTDVert_HH","reconstructed mass of all combinations: pion in HADES, proton in HADES, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    TH1F* hrealLMTDVert_HH=new TH1F("hrealLMTDVert_HH","reconstraced mass of pion in HADES and proton in HADES from #Lambda, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    //H-F
    TH1F* hMLPiHadesMTDVert_HF=new TH1F("hMLPiHadesMTDVert_HF","reconstructed mass of all combinations: pion in Hades, 2. part. in FD, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    TH1F* hMLPiHpFMTDVert_HF=new TH1F("hMLPiHpFMTDVert_HF","reconstructed mass of all combinations: pion in HADES, proton in FD, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    TH1F* hrealLMTDVert_HF=new TH1F("hrealLMTDVert_HF","reconstructed mass of pion in HADES and proton in FD from #Lambda, distance between tracks <x, Vertz_L in range",imres,immin,immax);

    
    int thmin = 0;
    int thmax = 4;
    int costhmin = -1;
    int costhmax = 1;
    int mommin = 0;
    int mommax = 1500;
    int phimin = -4;
    int phimax = 4;
    int ymin = 0;
    int ymax = 1;
    int nbins3 = 100;
    int dvertmin = -200;
    int dvertmax = 200;
    
    TH1F* hThetaL = new TH1F("hThetaL", "hThetaL", nbins3, thmin, thmax);
    TH1F* hThetaLcm = new TH1F("hThetaLcm", "hThetaLcm", nbins3, thmin, thmax);
    TH1F* hCosThetaL = new TH1F("hCosThetaL", "hCosThetaL", nbins3, costhmin, costhmax);
    TH1F* hCosThetaLcm = new TH1F("hCosThetaLcm", "hCosThetaLcm", nbins3, costhmin, costhmax);
    TH2F* hMomThetaL = new TH2F("hMomThetaL", "hMomThetaL", nbins3, mommin, mommax, nbins3, thmin, thmax);
    TH2F* hMomThetaLcm = new TH2F("hMomThetaLcm", "hMomThetaLcm", nbins3, mommin, mommax, nbins3, thmin, thmax);
    TH1F* hPhiL = new TH1F("hPhiL", "hPhiL", nbins3, phimin, phimax);
    TH1F* hPhiLcm = new TH1F("hPhiLcm", "hPhiLcm", nbins3, phimin, phimax);
    TH1F* hMomL = new TH1F("hMomL", "hMomL", nbins3, mommin, mommax);
    TH1F* hMomLcm = new TH1F("hMomLcm", "hMomLcm", nbins3, mommin, mommax);
    TH1F* hRapL = new TH1F("hRapL", "hRapL", nbins3, ymin, ymax);
    TH1F* hRapLcm = new TH1F("hRapLcm", "hRapLcm", nbins3, ymin, ymax);
    TH1F* hPseuRapL = new TH1F("hPseuRapL", "hPseuRapL", nbins3, ymin, ymax);
    TH1F* hPseuRapLcm = new TH1F("hPseuRapLcm", "hPseuRapLcm", nbins3, ymin, ymax);
    
    TH1F* hThetaH1 = new TH1F("hThetaH1", "hThetaH1", nbins3, thmin, thmax);
    TH1F* hPhiH1 = new TH1F("hPhiH1", "hPhiH1", nbins3, phimin, phimax);
    TH1F* hThetaV = new TH1F("hThetaV", "hThetaV", nbins3, thmin, thmax);
    TH1F* hPhiV = new TH1F("hPhiV", "hPhiV", nbins3, phimin, phimax);
    TH1F* hThetaH2 = new TH1F("hThetaH2", "hThetaH2", nbins3, thmin, thmax);
    TH1F* hPhiH2 = new TH1F("hPhiH2", "hPhiH2", nbins3, phimin, phimax);
    TH1F* hThetaX = new TH1F("hThetaX", "hThetaX", nbins3, thmin, thmax);
    TH1F* hPhiX = new TH1F("hPhiX", "hPhiX", nbins3, phimin, phimax);

    TH1F* hThetaH1_cm = new TH1F("hThetaH1_cm", "hThetaH1_cm", nbins3, thmin, thmax);
    TH1F* hPhiH1_cm = new TH1F("hPhiH1_cm", "hPhiH1_cm", nbins3, phimin, phimax);
    TH1F* hThetaV_cm = new TH1F("hThetaV_cm", "hThetaV_cm", nbins3, thmin, thmax);
    TH1F* hPhiV_cm = new TH1F("hPhiV_cm", "hPhiV_cm", nbins3, phimin, phimax);
    TH1F* hThetaH2_cm = new TH1F("hThetaH2_cm", "hThetaH2_cm", nbins3, thmin, thmax);
    TH1F* hPhiH2_cm = new TH1F("hPhiH2_cm", "hPhiH2_cm", nbins3, phimin, phimax);
    TH1F* hThetaX_cm = new TH1F("hThetaX_cm", "hThetaX_cm", nbins3, thmin, thmax);
    TH1F* hPhiX_cm = new TH1F("hPhiX_cm", "hPhiX_cm", nbins3, phimin, phimax);

    //vert_sim - vert_rec
    TH1F* hdvertlX = new TH1F("hdvertlX", "d(vertl_sim-vertl_rec)x", nbins2, dvertmin, dvertmax);
    TH1F* hdvertlY = new TH1F("hdvertlY", "d(vertl_sim-vertl_rec)y", nbins2, dvertmin, dvertmax);
    TH1F* hdvertlZ = new TH1F("hdvertlZ", "d(vertl_sim-vertl_rec)z", nbins2, dvertmin, dvertmax);
    TH1F* hdvertlR = new TH1F("hdvertlR", "d(vertl_sim-vertl_rec)r", nbins2, dvertmin, dvertmax);
    TH1F* hdvertxiX = new TH1F("hdvertxiX", "d(vertxi_sim-vertxi_rec)x", nbins2, dvertmin, dvertmax);
    TH1F* hdvertxiY = new TH1F("hdvertxiY", "d(vertxi_sim-vertxi_rec)y", nbins2, dvertmin, dvertmax);
    TH1F* hdvertxiZ = new TH1F("hdvertxiZ", "d(vertxi_sim-vertxi_rec)z", nbins2, dvertmin, dvertmax);
    TH1F* hdvertxiR = new TH1F("hdvertxiR", "d(vertxi_sim-vertxi_rec)r", nbins2, dvertmin, dvertmax);

    TH1F* hGeantxVertexA = new TH1F("hGeantxVertexA", "vert_sim_x A [mm]", nbins2, dvertmin, dvertmax);
    TH1F* hGeantyVertexA = new TH1F("hGeantyVertexA", "vert_sim_y A [mm]", nbins2, dvertmin, dvertmax);
    TH1F* hGeantzVertexA = new TH1F("hGeantzVertexA", "vert_sim_z A [mm]", nbins2, dvertmin, dvertmax);
    TH1F* hGeantxVertexB = new TH1F("hGeantxVertexB", "vert_sim_x B [mm]", nbins2, dvertmin, dvertmax);
    TH1F* hGeantyVertexB = new TH1F("hGeantyVertexB", "vert_sim_y B [mm]", nbins2, dvertmin, dvertmax);
    TH1F* hGeantzVertexB = new TH1F("hGeantzVertexB", "vert_sim_z B [mm]", nbins2, dvertmin, dvertmax);

    TH1F* hGeantPIDA = new TH1F("hGeantPIDA", "Geant ID", nbins3,  0, 100);
    TH1F* hGeantPIDB = new TH1F("hGeantPIDB", "Geant ID", nbins3,  0, 100);
    TH1F* hGeantPIDAparent = new TH1F("hGeantPIDAparent", "Geant ID", nbins3,  0, 100);
    TH1F* hGeantPIDBparent = new TH1F("hGeantPIDBparent", "Geant ID", nbins3,  0, 100);

    TH1F* hvertex_x = new TH1F("hvertex_x", "vertl_rec_x [mm]", nbins2, dvertmin, dvertmax);
    TH1F* hvertex_y = new TH1F("hvertex_y", "vertl_rec_y [mm]", nbins2, dvertmin, dvertmax);
    TH1F* hvertex_z = new TH1F("hvertex_z", "vertl_rec_z [mm]", nbins2, dvertmin, dvertmax);

    TH1F* hrA = new TH1F("hrA", "hrA", nbins2, -100, 100);
    TH1F* hrB = new TH1F("hrB", "hrB", nbins2, -100, 100);
    TH1F* hzA = new TH1F("hzA", "hzA", nbins2, -100, 100);
    TH1F* hzB = new TH1F("hzB", "hzB", nbins2, -100, 100);
    TH1F* hPhiA = new TH1F("hPhiA", "hPhiA", nbins3, phimin, phimax);
    TH1F* hPhiB = new TH1F("hPhiB", "hPhiB", nbins3, phimin, phimax);
    TH1F* hThetaA = new TH1F("hThetaA", "hThetaA", nbins3, thmin, thmax);
    TH1F* hThetaB = new TH1F("hThetaB", "hThetaB", nbins3, thmin, thmax);

    int dmommin = -400;
    int dmommax = 400;
    int mommin1 = -1000;
    int mommax1 = 1000;
    int momzmin = 0;
    int momzmax = 3000;

    //part A
    TH1F* hMomAResx = new TH1F("hMomAResx", "MomAResx", nbins1, dmommin, dmommax);
    TH1F* hMomAResy = new TH1F("hMomAResy", "MomAResy", nbins1, dmommin, dmommax);
    TH1F* hMomAResz = new TH1F("hMomAResz", "MomAResz", nbins1, dmommin, dmommax);

    TH1F* hMomArecox = new TH1F("hMomArecox", "MomArecox", nbins1, mommin1, mommax1);
    TH1F* hMomArecoy = new TH1F("hMomArecoy", "MomArecoy", nbins1, mommin1, mommax1);
    TH1F* hMomArecoz = new TH1F("hMomArecoz", "MomArecoz", nbins1, momzmin, momzmax);

    TH1F* hMomAGeax = new TH1F("hMomAGeax", "MomAGeax", nbins1, mommin1, mommax1);
    TH1F* hMomAGeay = new TH1F("hMomAGeay", "MomAGeay", nbins1, mommin1, mommax1);
    TH1F* hMomAGeaz = new TH1F("hMomAGeaz", "MomAGeaz", nbins1, momzmin, momzmax);

    //part B
    TH1F* hMomBResx = new TH1F("hMomBResx", "MomBResx", nbins1, dmommin, dmommax);
    TH1F* hMomBResy = new TH1F("hMomBResy", "MomBResy", nbins1, dmommin, dmommax);
    TH1F* hMomBResz = new TH1F("hMomBResz", "MomBResz", nbins1, dmommin, dmommax);

    TH1F* hMomBrecox = new TH1F("hMomBrecox", "MomBrecox", nbins1, mommin1, mommax1);
    TH1F* hMomBrecoy = new TH1F("hMomBrecoy", "MomBrecoy", nbins1, mommin1, mommax1);
    TH1F* hMomBrecoz = new TH1F("hMomBrecoz", "MomBrecoz", nbins1, momzmin, momzmax);

    TH1F* hMomBGeax = new TH1F("hMomBGeax", "MomBGeax", nbins1, mommin1, mommax1);
    TH1F* hMomBGeay = new TH1F("hMomBGeay", "MomBGeay", nbins1, mommin1, mommax1);
    TH1F* hMomBGeaz = new TH1F("hMomBGeaz", "MomBGeaz", nbins1, momzmin, momzmax);

    //Xi
    immin=1200;
    immax=1400;
    imres=200;
    //m lambda
    //H-H-H + H-F-H
    TH1F* hMXAll=new TH1F("hMXAll","Mass reconstructed from Lambda and proton",imres,immin,immax);
    TH1F* hrealX=new TH1F("hrealX","reconstraced mass of pion in HADES from #Xi and real #Lambda",imres,immin,immax);
    //H-H-H
    TH1F* hMXAll_HH=new TH1F("hMXAll_HH","Mass reconstructed from Lambda and proton (H-H-H)",imres,immin,immax);
    TH1F* hrealX_HH=new TH1F("hrealX_HH","reconstructed mass of pion in HADES from #Xi and real #Lambda (H-H-H)",imres,immin,immax);
    //H-F-H
    TH1F* hMXAll_HF=new TH1F("hMXAll_HF","Mass reconstructed from Lambda and proton (H-F-H)",imres,immin,immax);
    TH1F* hrealX_HF=new TH1F("hrealX_HF","reconstructed mass of pion in HADES from #Xi and real #Lambda (H-F-H)",imres,immin,immax);
    
    //MTD_X
    //H-H-H + H-F-H
    TH1F* hMXPiLMTD=new TH1F("hMXPiLMTD","Mass reconstructed from Lambda and proton, dist <x",imres,immin,immax);
    TH1F* hrealXMTD=new TH1F("hrealXMTD","reconstraced mass of pion in HADES from #Xi and real #Lambda, dist <x",imres,immin,immax);
    //H-H-H
    TH1F* hMXPiLMTD_HH=new TH1F("hMXPiLMTD_HH","Mass reconstructed from Lambda and proton, dist <x (H-H-H)",imres,immin,immax);
    TH1F* hrealXMTD_HH=new TH1F("hrealXMTD_HH","reconstructed mass of pion in HADES from #Xi and real #Lambda, dist <x (H-H-H)",imres,immin,immax);
    //H-F-H
    TH1F* hMXPiLMTD_HF=new TH1F("hMXPiLMTD_HF","Mass reconstructed from Lambda and proton, dist <x (H-F-H)",imres,immin,immax);
    TH1F* hrealXMTD_HF=new TH1F("hrealXMTD_HF","reconstructed mass of pion in HADES from #Xi and real #Lambda, dist <x (H-F-H)",imres,immin,immax);
    
    //VERTz_L
    //H-H-H + H-F-H
    TH1F* hMXPiLMTDVert=new TH1F("hMXPiLMTDVert","Mass reconstructed from Lambda and proton, dist <x, #Xi_{Vert_z}",imres,immin,immax);
    TH1F* hrealXMTDVert=new TH1F("hrealXMTDVert","reconstraced mass of pion in HADES from #Xi and real #Lambda, dist <x, #Xi_{Vert_z}",imres,immin,immax);
    //H-H-H
    TH1F* hMXPiLMTDVert_HH=new TH1F("hMXPiLMTDVert_HH","Mass reconstructed from Lambda and proton, dist <x, #Xi_{Vert_z} (H-H-H)",imres,immin,immax);
    TH1F* hrealXMTDVert_HH=new TH1F("hrealXMTDVert_HH","reconstructed mass of pion in HADES from #Xi and real #Lambda, dist <x, #Xi_{Vert_z} (H-H-H)",imres,immin,immax);
    //H-F-H
    TH1F* hMXPiLMTDVert_HF=new TH1F("hMXPiLMTDVert_HF","Mass reconstructed from Lambda and proton, dist <x, #Xi_{Vert_z} (H-F-H)",imres,immin,immax);
    TH1F* hrealXMTDVert_HF=new TH1F("hrealXMTDVert_HF","reconstructed mass of pion in HADES from #Xi and real #Lambda, dist <x, #Xi_{Vert_z} (H-F-H)",imres,immin,immax);

    //AngLamXiVert
    //...

    
    //cuts
    //Dist Lambda
    //H-H + H-F
    TH1F* hTDpip=new TH1F("hTDpip","Distance between proton in H/FD and pion in H; dist[mm]",200,-20,200);
    TH1F* hTDpiFD=new TH1F("hTDpiFD","Distance between anything in H/FD and pion in H; dist[mm]",200,-20,200);
    //H-H
    TH1F* hTDpip_HH=new TH1F("hTDpip_HH","Distance between proton in H and pion in H; dist[mm]",200,-20,200);
    TH1F* hTDpiFD_HH=new TH1F("hTDpiFD_HH","Distance between anything in H and pion in H; dist[mm]",200,-20,200);
    //H-F
    TH1F* hTDpip_HF=new TH1F("hTDpip_HF","Distance between proton in FD and pion in H; dist[mm]",200,-20,200);
    TH1F* hTDpiFD_HF=new TH1F("hTDpiFD_HF","Distance between anything in FD and pion in H; dist[mm]",200,-20,200);
    
    //Vertex lambda
    //H-H + H-F
    TH1F* hVertpip=new TH1F("hVertpip","Z-coordinate of vertex reconstructed form pion in H and proton in H/FD", 150,-100,500);
    TH1F* hVertpiFD=new TH1F("hVertpiFD","Z-coordinate of vertex reconstructed from pion in H and anything in H/FD",150,-100,500);
    //H-H 
    TH1F* hVertpip_HH=new TH1F("hVertpip_HH","Z-coordinate of vertex reconstructed form pion in H and proton in H", 150,-100,500);
    TH1F* hVertpiFD_HH=new TH1F("hVertpiFD_HH","Z-coordinate of vertex reconstructed from pion in H and anything in H",150,-100,500);
    //H-F
    TH1F* hVertpip_HF=new TH1F("hVertpip_HF","Z-coordinate of vertex reconstructed form pion in H and proton in FD", 150,-100,500);
    TH1F* hVertpiFD_HF=new TH1F("hVertpiFD_HF","Z-coordinate of vertex reconstructed from pion in H and anything in GD",150,-100,500);
    
    //Dist Xi
    //H-H-H + H-F-H
    TH1F* hTDpiL=new TH1F("hTDpiL","distance between lambda and all pions (H-H-H + H-F-H)", nbins1, -20, 200);
    //H-H-H
    TH1F* hTDpiL_HH=new TH1F("hTDpiL_HH","distance between lambda and all pions (H-H-H)", nbins1, -20, 200);
    //H-F-H
    TH1F* hTDpiL_HF=new TH1F("hTDpiL_HF","distance between lambda and all pions (H-F-H)", nbins1, -20, 200);

    //Ang Lam Xi Vert
    //H-H-H + H-F-H
    TH1F* hAngLX=new TH1F("hAngLX","Anlge between reconstructed #Lambda track and #Xi vertex (H-H-H + H-F-H)", nbins1, phimin, phimax);
    //H-H-H
    TH1F* hAngLX_HH=new TH1F("hAngLX_HH","Anlge between reconstructed #Lambda track and #Xi vertex (H-H-H)", nbins1, phimin, phimax);
    //H-F-H
    TH1F* hAngLX_HF=new TH1F("hAngLX_HF","Anlge between reconstructed #Lambda track and #Xi vertex (H-F-H)", nbins1, phimin, phimax);
        
    //Vertex Xi
    //H-H-H + H-F-H
    TH1F* hXVertpiL=new TH1F("hXVertpiL","Z-coordinate of vertex reconstructed form pion in H and Lambda (H-H-H + H-F-H)", 150,-100,500);
    //H-H-H 
    TH1F* hXVertpiL_HH=new TH1F("hXVertpiL_HH","Z-coordinate of vertex reconstructed form pion in H and Lambda (H-H-H)", 150,-100,500);
    //H-F-H
    TH1F* hXVertpiL_HF=new TH1F("hXVertpiL_HF","Z-coordinate of vertex reconstructed form pion in H and Lambda (H-F-H)", 150,-100,500);

    //PID
    TH1D *hPpid = new TH1D("hPpid", "hPpid", 102, -1, 100);
    TH1D *hVpid = new TH1D("hVpid", "hVpid", 102, -1, 100);

    //
    int start1 = -1000;
    int start2 = 1000;
    int base1 = -200;
    int base2 = 200;
    TH1D *hstartt = new TH1D("hstartt", "hstartt", nbins1, -1, 50);
    TH1D *hstopt = new TH1D("hstopt", "hstopt", nbins1, toff1, toff2);
    TH1D *hstartx = new TH1D("hstartx", "hstartx", nbins1, -5, 5);
    TH1D *hstarty = new TH1D("hstarty", "hstarty", nbins1, -5, 5);
    TH1D *hstartz = new TH1D("hstartz", "hstartz", nbins1, -5, 5);
    TH1D *hstopx = new TH1D("hstopx", "hstopx", nbins3, start1, start2);
    TH1D *hstopy = new TH1D("hstopy", "hstopy", nbins3, start1, start2);
    TH1D *hstopz = new TH1D("hstopz", "hstopz", nbins1, 5500, 6000);
    TH1D *hbaseHx = new TH1D("hbaseHx", "hbaseHx", nbins1, base1, base2);
    TH1D *hbaseHy = new TH1D("hbaseHy", "hbaseHy", nbins1, base1, base2);
    TH1D *hbaseHz = new TH1D("hbaseHz", "hbaseHz", nbins1, base1, base2);
    TH1D *hdirHx = new TH1D("hdirHx", "hdirHx", nbins1, -5, 5);
    TH1D *hdirHy = new TH1D("hdirHy", "hdirHy", nbins1, -5, 5);
    TH1D *hdirHz = new TH1D("hdirHz", "hdirHz", nbins1, -5, 5);
    TH1D *hbaseFWx = new TH1D("hbaseFWx", "hbaseFWx", nbins1, -10000, 10000);
    TH1D *hbaseFWy = new TH1D("hbaseFWy", "hbaseFWy", nbins1, -10000, 10000);
    TH1D *hbaseFWz = new TH1D("hbaseFWz", "hbaseFWz", nbins1, -10000, 10000);
    TH1D *hdirFWx = new TH1D("hdirFWx", "hdirFWx", nbins1, -10000, 10000);
    TH1D *hdirFWy = new TH1D("hdirFWy", "hdirFWy", nbins1, -10000, 10000);
    TH1D *hdirFWz = new TH1D("hdirFWz", "hdirFWz", nbins1, -10000, 10000);
    TH1D *hdistH = new TH1D("hdistH", "hdistH", nbins1, -10, 500);
    TH1D *htofH = new TH1D("htofH", "htofH", nbins1, 0, 10);
    TH1D *hdifftofH= new TH1D("hdifftofH", "hdifftofH", nbins1, -10, 50);
    TH1D *hdistFW = new TH1D("hdistFW", "hdistFW", nbins1, -10, 500);
    TH1D *hbetaFW = new TH1D("hbetaFW", "hbetaFW", nbins1, bet1, bet2);
    TH1D *htofFW = new TH1D("htofFW", "htofFW", nbins1, toff1, toff2);
    TH1D *hdifftofFW = new TH1D("hdifftofFW", "hdifftofFW", nbins1, -10, 50);
    TH1D *hmomFW = new TH1D("hmomFW", "hmomFW", nbins1, -30000, 30000);
    
    
    //cuts values
    double max_distanceL = 25; // !!
    double max_distanceX = 20; // !!
    double cut_vertex_z_minL = -20; // !!
    double cut_vertex_z_minX = -50; // !!
    double cut_vertex_z_max = 300; // !!
    double massLmin = 1106; // !!
    double massLmax = 1126; //!!

    //beam vector
    double beam_en = 4.5; //[GeV]
    double p_mass = .938; //[GeV]
    double beam_mom = sqrt(beam_en*beam_en - p_mass*p_mass);
    TLorentzVector *proj = new TLorentzVector(0, 0, beam_mom, beam_en);
    TLorentzVector *targ = new TLorentzVector(0, 0, 0, p_mass);
    TLorentzVector *beam = new TLorentzVector(0,0,0,0);;
    *beam= *proj + *targ;
    
    int eventNo = -1;
    TH1I *heventNo = new TH1I();
    heventNo -> SetName("heventNo");
    //event loop *************************************************
    //*********************************************************
    for (Int_t i = 0; i < entries; i++)                   
    {
        loop->nextEvent(i);         // get next event. categories will be cleared before
        if(i%5000==0)
	    cout<<"event no. "<<i<<endl;
	HParticleCandSim* particlecand =nullptr;
	HParticleCandSim* ksicand =nullptr;  //candidate for pion to Xi reconstr
	HFwDetCandSim* fwdetstrawvec = nullptr; //with FD!!!
	HParticleCandSim* particlecand2 = nullptr; //if no FD!!!
	HFwDetStrawCalSim* fwdetstrawcal = nullptr;

	HParticleTool particle_tool;
       	//vector candidate reconstraction
	Int_t vcnt=fCatFwDetCandSim->getEntries();
	Int_t pcnt=fCatParticleCandSim->getEntries();
	int particleID=0;
	int vectorcandID, ksicandID;
	int particleGeantID, vectorcandGeantID, ksicandGeantID;
	int graphiID=0;
	Int_t particlecand_parentID, vectorcand_parentID, ksicand_parentID;

	// H-
	for(int l=0;l<pcnt;l++)//particle candidates from HADES--------------------------------------------------
	{ 
	    particlecand = HCategoryManager::getObject(particlecand, fCatParticleCandSim,l);
	    if(!particlecand->isFlagBit(kIsUsed)) continue; //only the best tracks
	    
	    float mom_h = particlecand -> getMomentum();
	    float charge_h = particlecand -> getCharge();
	    float dEdx_mdc = particlecand -> getMdcdEdx();
	    float dEdx_tof = particlecand -> getTofdEdx();
	    float beta_h = particlecand -> getBeta();
	    //float mass_h = particlecand -> getMass(); //hParticleCandSim
	    //float mass2_h = particlecand -> getMass2(); //hParticleCandSim
	    float mass_h =  mom_h*(TMath::Sqrt((1/beta_h/beta_h)-1)); 
	    float mass2_h = mass_h*mass_h;
	    float ener_h = mass_h*((1/TMath::Sqrt(1-beta_h*beta_h))-1);
	    float pq_h = mom_h*charge_h;
	    float tofRec_h = particlecand -> getTofRec();
	    float tof_h = particlecand -> getTof();
	    float r_hA = particlecand -> getR();
	    float r_vB = 0;
	    float z_hA = particlecand -> getZ();
	    float z_vB = 0;

	    double phi_hA = particlecand -> getPhi();
	    double phi_vB = 0;
	    double theta_hA = particlecand -> getTheta();
	    double theta_vB = 0;
	    double hitx_hA = particlecand -> X();
	    double hity_hA = particlecand -> Y();
	    double hitz_hA = particlecand -> Z();
	    
	    Float_t momArecox = particlecand -> Px();
	    Float_t momArecoy = particlecand -> Py();
	    Float_t momArecoz = particlecand -> Pz();
	    Float_t momAsimx = particlecand -> getGeantxMom();
	    Float_t momAsimy = particlecand -> getGeantyMom();
	    Float_t momAsimz = particlecand -> getGeantzMom();

	    /*	    //this PID not used now -> use mass2PID() or mass2PIDfit() below
	    if(beta_h!=-1){
		for(int npid = 0; npid < partN; npid++){
		    if(gCut[npid] -> GetName() == "CUTG_00") continue;
		    else if(gCut[npid] -> IsInside(pq_h,beta_h))
			graphiID = npid;
		}
	    }
	    if(graphiID < 1 || graphiID > partN){
//	    	cout << "break: invalid particle ID: " << particleID << endl;
	     	continue;
		}
*/
	    // PID	    
	    if(beta_h!=-1)
//		particleID = mass2PID(mass2_h, charge_h); //PID as ranges in m2(pq) spectrum
		particleID = mass2PIDfit(fitpar, mass2_h, charge_h, nPartSpec); //PID based on m2 spectrum
	    else break;
	    hPpid -> Fill(particleID);

	    particlecand->calc4vectorProperties(HPhysicsConstants::mass(particleID));
	    particleGeantID = particlecand -> getGeantPID();
	    particlecand_parentID = particlecand -> getGeantParentPID();
	    
	    TLorentzVector pi1Vector = *particlecand;
	    float thh1 = pi1Vector.Theta();
	    float phh1 = pi1Vector.Phi();
	    //cm
	    TLorentzVector *pi1Vector_cm = new TLorentzVector(0,0,0,0);
	    *pi1Vector_cm = *particlecand;
	    pi1Vector_cm -> Boost(-(*beam).BoostVector());
	    Float_t thh1cm = pi1Vector_cm->Theta();
	    Float_t phh1cm = pi1Vector_cm->Phi();

	    //geant vertex pi^- from Lambda(1115)
	    double lamVertXgeantA = particlecand -> getGeantxVertex();
	    double lamVertYgeantA = particlecand -> getGeantyVertex();
	    double lamVertZgeantA = particlecand -> getGeantzVertex();
	    Float_t lamVertRgeantA = TMath::Sqrt(lamVertXgeantA*lamVertXgeantA + lamVertYgeantA*lamVertYgeantA);
	    
	    // cout << "tof:" << tof_h << " beta:" << beta << " p:" << mom << " q:" << charge << " mass:" << mass << endl;
	    if(beta_h != -1){
		hdEdx_mdc -> Fill(pq_h, dEdx_mdc);
		//hBeta_h -> Fill(pq_h, beta_h);
		//hEkin_h -> Fill(pq_h, ener_h);
		hM1_h -> Fill(mass_h*charge_h);
		hM12_h -> Fill(mass2_h*charge_h);
		hM2_h -> Fill(pq_h, mass_h);
		hM22_h -> Fill(pq_h, mass2_h);
		hM12_h_m2 -> Fill(mass2_h);
		  
		if(charge_h < 0)
		    hM12_h_neg -> Fill(mass2_h*charge_h);
		else
		    hM12_h_pos -> Fill(mass2_h*charge_h);
		if(particleID > 0){
		    hBeta_m_h -> Fill(pq_h, beta_h);
		    hM1_m_h -> Fill(mass_h*charge_h);
		    hM12_m_h -> Fill(mass2_h);
		    hM2_m_h -> Fill(pq_h, mass_h);
		    hM22_m_h -> Fill(pq_h, mass2_h);
		    if(particleID==8 || particleID==9)
			hM12_h_pions -> Fill(mass2_h*charge_h);
		}
		
		if(particlecand -> getSystem() == 1){
		    hdEdx_tof -> Fill(pq_h, dEdx_tof);
		    hBeta_tof -> Fill(pq_h, beta_h);
		    hEkin_tof -> Fill(pq_h, ener_h);
		    hM1_tof -> Fill(mass_h*charge_h);
		    hM12_tof -> Fill(mass2_h*charge_h);
		    hM2_tof -> Fill(pq_h, mass_h);
		    hM22_tof -> Fill(pq_h, mass2_h);
		    if(particleID > 0){
			hBeta_m_tof -> Fill(pq_h, beta_h);
			hM1_m_tof -> Fill(mass_h*charge_h);
			hM12_m_h -> Fill(mass2_h);
			hM2_m_tof -> Fill(pq_h, mass_h);
			hM22_m_tof -> Fill(pq_h, mass2_h);	
		    }	 
		    if(gCutdedx -> IsInside(pq_h,dEdx_tof)){
			hcheckdedx_dedxmdc -> Fill(pq_h, dEdx_mdc);
			hcheckdedx_btof -> Fill(pq_h, beta_h);
		    }
		}

		if(particlecand -> getSystem() == 0){
		    //hdEdx_rpc -> Fill(pq_h, dEdx_tof);
		    hBeta_rpc -> Fill(pq_h, beta_h);
		    hEkin_rpc -> Fill(pq_h, ener_h);
		    hM1_rpc -> Fill(mass_h*charge_h);
		    hM12_rpc -> Fill(mass2_h*charge_h);
		    hM2_rpc -> Fill(pq_h, mass_h);
		    hM22_rpc -> Fill(pq_h, mass2_h);
		    if(particleID > 0){
			hBeta_m_rpc -> Fill(pq_h, beta_h);
			hM12_m_rpc -> Fill(mass2_h);
			hM1_m_rpc -> Fill(mass_h*charge_h);
			hM2_m_rpc -> Fill(pq_h, mass_h);
			hM22_m_rpc -> Fill(pq_h, mass2_h);
		    }
		}
	    }
	    if(tof_h != -1){
		//	cout << "tofRec_h: " << tofRec_h << " tof_h: " << tof_h << endl;
		if(particleID == 9){
		    hTof_pim_h -> Fill(tof_h);
		    hTof_pim -> Fill(tof_h);
		    hTof_all_h -> Fill(tof_h);
		    hTof_all -> Fill(tof_h);
		    hThetaH1 -> Fill(thh1);
		    hPhiH1 -> Fill(phh1);
		    hThetaH1_cm -> Fill(thh1cm);
		    hPhiH1_cm -> Fill(phh1cm);
		}
		else if(particleID == 11){
		    hTof_Kp_h -> Fill(tof_h);
		    hTof_Kp -> Fill(tof_h);
		    hTof_all_h -> Fill(tof_h);
		    hTof_all -> Fill(tof_h);
		}
		else if(particleID == 14){
		    hTof_p_h -> Fill(tof_h);
		    hTof_p -> Fill(tof_h);
		    hTof_all_h -> Fill(tof_h);
		    hTof_all -> Fill(tof_h);
		}
		if(particleGeantID == 9){
		    hTof_pim_h_GeantID -> Fill(tof_h);
		    hTof_pim_GeantID -> Fill(tof_h);
		    hTof_all_h_GeantID -> Fill(tof_h);
		    hTof_all_GeantID -> Fill(tof_h);
		}
		else if(particleGeantID == 11){
		    hTof_Kp_h_GeantID -> Fill(tof_h);
		    hTof_Kp_GeantID -> Fill(tof_h);
		    hTof_all_h_GeantID -> Fill(tof_h);
		    hTof_all_GeantID -> Fill(tof_h);
		}
		else if(particleGeantID == 14){
		    hTof_p_h_GeantID -> Fill(tof_h);
		    hTof_p_GeantID -> Fill(tof_h);
		    hTof_all_h_GeantID -> Fill(tof_h);
		    hTof_all_GeantID -> Fill(tof_h);
		}
	    }

	
		//	cout << "beta: " << beta << " mom: " << mom << " dEdx: " << dEdx << " ener: " << ener << endl;
	    //##############################
	    // H-F-
	    for(int j=0; j<vcnt; j++){//vector candidates, FwDetCand loop-------------------------------------------------- with FD!!!
		
		float tof_v = 0; //with FD!!!
		float dE_v = 0; 
		float r_v = 0; 
		float tofEloss_v = 0;
		//with FD!!!
		fwdetstrawvec=HCategoryManager::getObject(fwdetstrawvec, fCatFwDetCandSim, j);
		tof_v = fwdetstrawvec -> getTof();
		r_vB = fwdetstrawvec -> getR();
		z_vB = fwdetstrawvec -> getZ();
		phi_vB = fwdetstrawvec -> getPhi();
		theta_vB = fwdetstrawvec -> getTheta();
		vectorcandID = tofPID(tof_v);

		int nh = fwdetstrawvec -> getNofHits();
		for(int n = 0; n < nh; n++){
		    int m = fwdetstrawvec -> getHitIndex(n);
		    fwdetstrawcal=HCategoryManager::getObject(fwdetstrawcal, fFwDetStrawCalSim, m);
		    dE_v += fwdetstrawcal -> getEloss(); //E loss in the straw
		    r_v = fwdetstrawcal -> getDriftRadius(); //drift radius
		    if(tof_v != -1)
			hr_fd -> Fill(r_v);
//		    cout << "dE=" << dE_v << " dr=" << r_v << endl;
		}
		tofEloss_v = tof_v*dE_v;
		//end with FD!!!
		Float_t momBrecox = fwdetstrawvec -> Px();
		Float_t momBrecoy = fwdetstrawvec -> Py();
		Float_t momBrecoz = fwdetstrawvec -> Pz();
                Float_t momBsimx = fwdetstrawvec -> getGeantxMom();
                Float_t momBsimy = fwdetstrawvec -> getGeantyMom();
                Float_t momBsimz = fwdetstrawvec -> getGeantzMom();

		//              vectorcandID = 14;
		hVpid -> Fill(vectorcandID);

		//
		float startt = fwdetstrawvec -> getStartTime();
		float stopt = fwdetstrawvec -> getStopTime();
		float startx = fwdetstrawvec -> getStartX();
		float starty = fwdetstrawvec -> getStartY();
		float startz = fwdetstrawvec -> getStartZ();
		float stopx = fwdetstrawvec -> getStopX();
		float stopy = fwdetstrawvec -> getStopY();
		float stopz = fwdetstrawvec -> getStopZ();

		HGeomVector base_H;
		HGeomVector dir_H;
		particle_tool.calcSegVector(particlecand->getZ(),particlecand->getR(),TMath::DegToRad()*particlecand->getPhi(),TMath::DegToRad()*particlecand->getTheta(),base_H,dir_H);
	
		HGeomVector base_FW;
		base_FW.setX(fwdetstrawvec->getBaseX()); //with FD!!!
		base_FW.setY(fwdetstrawvec->getBaseY());
		base_FW.setZ(fwdetstrawvec->getBaseZ());
		HGeomVector dir_FW;
		dir_FW.setX(fwdetstrawvec->getDirTx());  //with FD!!!
		dir_FW.setY(fwdetstrawvec->getDirTy());
		dir_FW.setZ(1);//konwencja, tak jest ustawione w fwdetstrawvec
		//*******************
		double distance=particle_tool.calculateMinimumDistance(base_FW,dir_FW,base_H,dir_H);

//                cout << "base,dir FW: " << base_FW.X() << " " << base_FW.Y() << " " << base_FW.Z() << " " << dir_FW.X() << " " << dir_FW.Y() << " " << dir_FW.Z() << endl;

/*		float distH = TMath::Sqrt((hitx_hA - base_H.X())*(hitx_hA - base_H.X()) + (hity_hA - base_H.Y())*(hity_hA - base_H.Y()) + (hitz_hA - base_H.Z())*(hitz_hA - base_H.Z()));
		float tofH = distH/(300.*beta_h); //300 -> from c
		float tLdec = tof_h - tofH; //time of the Lambda decay        

		
		float distFW = TMath::Sqrt((stopx - base_H.X())*(stopx - base_H.X()) + (stopy - base_H.Y())*(stopy - base_H.Y()) + (stopz - base_H.Z())*(stopz - base_H.Z()));
		float tofFW = tof_v - tLdec;
		float betaFW = distFW/(300.*tofFW);
		double momFW = HPhysicsConstants::mass(vectorcandID) / (TMath::Sqrt((1/(betaFW*betaFW)) - 1));
*/		
//		cout << "distH: " << distH << " tofH: " << tofH << " tof_h: " << tof_h << " beta_h: " << beta_h << " tLdec: " << tLdec <<  " distFW: " << distFW << " tofFW: " << tofFW << " tof_v: " << tof_v << " betaFW: " << betaFW << " momFW: " << momFW  << endl;

/*		hdistH -> Fill(distH);
		htofH -> Fill(tofH);
		hdifftofH -> Fill(tof_h - tofH); //time of the Lambda decay
		hdistFW -> Fill(distFW);
		hbetaFW -> Fill(betaFW);
		htofFW -> Fill(tofFW);
		hdifftofFW -> Fill(tof_v - tofFW);
		hmomFW -> Fill(momFW);
*/		
		hbaseHx -> Fill(base_H.X());
		hbaseHy -> Fill(base_H.Y());
		hbaseHz -> Fill(base_H.Z());
		hdirHx -> Fill(dir_H.X());
		hdirHy -> Fill(dir_H.Y());
		hdirHz -> Fill(dir_H.Z());
		hbaseFWx -> Fill(base_FW.X());
		hbaseFWy -> Fill(base_FW.Y());
		hbaseFWz -> Fill(base_FW.Z());
		hdirFWx -> Fill(dir_FW.X());
		hdirFWy -> Fill(dir_FW.Y());
		hdirFWz -> Fill(dir_FW.Z());

		fwdetstrawvec -> calc4vectorProperties(HPhysicsConstants::mass(vectorcandID));
		vectorcandGeantID = fwdetstrawvec -> getGeantPID();
		vectorcand_parentID = fwdetstrawvec -> getGeantParentPID();
	   
		TLorentzVector pVector = *fwdetstrawvec;
		float thv = pVector.Theta();
		float phv = pVector.Phi();
		//cm
		TLorentzVector *pVector_cm = new TLorentzVector(0,0,0,0);
		*pVector_cm = *fwdetstrawvec;
		pVector_cm -> Boost(-(*beam).BoostVector());
		Float_t thvcm = pVector_cm->Theta();
		Float_t phvcm = pVector_cm->Phi();

		
		if(tof_v != -1){
		    //	cout << "tofRec_v: " << tofRec_v << " tof_v: " << tof_v << endl;
		    hdE_fd -> Fill(dE_v);
		    hdetof_fd -> Fill(dE_v, tof_v);

		    hTof_all_fd -> Fill(tof_v);
		    hTof_all -> Fill(tof_v);
		    hstartt -> Fill(startt);
		    hstopt -> Fill(stopt);
		    hstartx -> Fill(startx);
		    hstarty -> Fill(starty);
		    hstartz -> Fill(startz);
		    hstopx -> Fill(stopx);
		    hstopy -> Fill(stopy);
		    hstopz -> Fill(stopz);
		    if(vectorcandID == 9){
			hTof_pim_fd -> Fill(tof_v);
			hTof_pim -> Fill(tof_v);
		    }
		    else if(vectorcandID == 11){
			hTof_Kp_fd -> Fill(tof_v);
			hTof_Kp -> Fill(tof_v);
		    }
		    else if(vectorcandID == 14){
			hTof_p_fd -> Fill(tof_v);
			hTof_p -> Fill(tof_v);
			hThetaV -> Fill(thv);
			hPhiV -> Fill(phv);
			hThetaV_cm -> Fill(thvcm);
			hPhiV_cm -> Fill(phvcm);
		    }
		}
		if(tof_v != -1){
		    //	cout << "tofRec_v: " << tofRec_v << " tof_v: " << tof_v << endl;
		    hTof_all_fd_GeantID -> Fill(tof_v);
		    hTof_all_GeantID -> Fill(tof_v);
		    if(vectorcandGeantID == 9){
			hTof_pim_fd_GeantID -> Fill(tof_v);
			hTof_pim_GeantID -> Fill(tof_v);
			hdetof_fd_Geant -> Fill(dE_v, tof_v);
			hdetof_fd_Geant9 -> Fill(dE_v, tof_v);
		    }
		    else if(vectorcandGeantID == 11){
			hTof_Kp_fd_GeantID -> Fill(tof_v);
			hTof_Kp_GeantID -> Fill(tof_v);
			hdetof_fd_Geant -> Fill(dE_v, tof_v);
			hdetof_fd_Geant11 -> Fill(dE_v, tof_v);
		    }
		    else if(vectorcandGeantID == 14){
			hTof_p_fd_GeantID -> Fill(tof_v);
			hTof_p_GeantID -> Fill(tof_v);
			hdetof_fd_Geant -> Fill(dE_v, tof_v);
			hdetof_fd_Geant14 -> Fill(dE_v, tof_v);
		    }
		}



		HGeomVector vertex;
		vertex=particle_tool.calcVertexAnalytical(base_FW,dir_FW,base_H,dir_H);
		Float_t vertex_x = vertex.X();
		Float_t vertex_y = vertex.Y();
		Float_t vertex_z = vertex.Z();
		Float_t vertex_r = TMath::Sqrt(vertex.X()*vertex.X()+vertex.Y()*vertex.Y());

		//geant vertex p from Lambda(1115)
		double lamVertXgeantB = fwdetstrawvec -> getGeantxVertex();
		double lamVertYgeantB = fwdetstrawvec -> getGeantyVertex();
		double lamVertZgeantB = fwdetstrawvec -> getGeantzVertex();
		Float_t lamVertRgeantB = TMath::Sqrt(lamVertXgeantB*lamVertXgeantB + lamVertYgeantB*lamVertYgeantB);
		double dvertlX, dvertlY, dvertlZ, dvertlR;
		dvertlX = lamVertXgeantB - vertex_x;
		dvertlY = lamVertYgeantB - vertex_y;
		dvertlZ = lamVertZgeantB - vertex_z;
		dvertlR = TMath::Sqrt(dvertlX*dvertlX + dvertlY*dvertlY + dvertlZ*dvertlZ);

		int GeantPIDA = particlecand -> getGeantPID();
		int GeantPIDB = fwdetstrawvec -> getGeantPID();

		int GeantPIDAparent = particlecand -> getGeantParentPID();
		int GeantPIDBparent = fwdetstrawvec -> getGeantParentPID();

		int GeantPIDAGparent = particlecand -> getGeantGrandParentPID();
		int GeantPIDBGparent = fwdetstrawvec -> getGeantGrandParentPID();
				
		TLorentzVector sum_mass = *fwdetstrawvec + *particlecand;
		Float_t mass=sum_mass.M();
		Float_t betaL=sum_mass.Beta();
		//lab
		Float_t thetaL=sum_mass.Theta(); 
		Float_t cosThetaL=sum_mass.CosTheta(); 
		Float_t phiL=sum_mass.Phi(); 
		Float_t momL=sum_mass.P();
		Float_t yL=sum_mass.Rapidity();
//		Float_t pseudoyL=sum_mass.PseudoRapidity();
		//cm
		TLorentzVector *sum_mass_cm = new TLorentzVector(0,0,0,0);
		*sum_mass_cm = *fwdetstrawvec + *particlecand;
		sum_mass_cm -> Boost(-(*beam).BoostVector());
		Float_t thetaLcm=sum_mass_cm->Theta();
		Float_t cosThetaLcm=sum_mass_cm->CosTheta();
		Float_t phiLcm=sum_mass_cm->Phi();
		Float_t momLcm=sum_mass_cm->P();
		Float_t yLcm=sum_mass_cm->Rapidity();
//		Float_t pseudoyLcm=sum_mass_cm->PseudoRapidity();
	      		
		hMLAll -> Fill(mass);
		hMLAll_HF -> Fill(mass);

		if(particleID == 9){ //pion in HADES, anything in FD
		    //   cout << "H 9" << "mass=" << mass << endl;
		    hMLPiHades -> Fill(mass);
		    hTDpiFD -> Fill(distance);
		    hMLPiHades_HF -> Fill(mass);
		    hTDpiFD_HF -> Fill(distance);

		    if(vectorcandID == 14){ //pion in HADES, proton in FD
			hMLPiHpF -> Fill(mass);
			hTDpip -> Fill(distance);
			hMLPiHpF_HF -> Fill(mass);
			hTDpip_HF -> Fill(distance);
			if(particlecand_parentID==18 && vectorcand_parentID==18){ //pion and proton from real Lambda
			    hrealL -> Fill(mass);
			    hrealL_HF -> Fill(mass);
			}
		    }
		
		    if(distance < max_distanceL){ //MTD_L cut
			//pion in HADES, anything in FD
			hMLPiHadesMTD -> Fill(mass);
			hVertpiFD -> Fill(vertex_z);
			hMLPiHadesMTD_HF -> Fill(mass);
			hVertpiFD_HF -> Fill(vertex_z);
			    
			if(vectorcandID == 14){ //pion in HADES, proton in FD
			    hMLPiHpFMTD -> Fill(mass);
			    hVertpip -> Fill(vertex_z);
			    hMLPiHpFMTD_HF -> Fill(mass);
			    hVertpip_HF -> Fill(vertex_z);
			    if(particlecand_parentID==18 && vectorcand_parentID==18){ //pion and proton from real Lambda
				hrealLMTD -> Fill(mass);
				hrealLMTD_HF -> Fill(mass);
			    }
			}
		    
			if(vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max){ //VERTz_L cut
			    //pion in HADES, anything in FD
			    hMLPiHadesMTDVert -> Fill(mass);
			    hMLPiHadesMTDVert_HF -> Fill(mass);

			    if(vectorcandID == 14){ //pion in HADES, proton in FD
				hMLPiHpFMTDVert -> Fill(mass);
				hMLPiHpFMTDVert_HF -> Fill(mass);
							
				if(particlecand_parentID==18 && vectorcand_parentID==18){ //pion and proton from	real Lambda
				    hrealLMTDVert -> Fill(mass);
				    hrealLMTDVert_HF -> Fill(mass);
				    
				    hThetaLcm -> Fill(thetaLcm);
				    hThetaL -> Fill(thetaL);
				    hCosThetaLcm -> Fill(cosThetaLcm);
				    hMomThetaLcm -> Fill(momLcm, thetaLcm);
				    hPhiLcm -> Fill(phiLcm);
				    hPhiL -> Fill(phiL);
				    hMomLcm -> Fill(momLcm);
				    hRapLcm -> Fill(yLcm);
//				hPseuRapLcm -> Fill(pseudoyLcm);
				}
			    }
			}	
		    }
		}
		
		//xxxxxxxxxxxxxxxxxxxxxxxxx
		//Xi reconstruction
		// H-F-H
//		if(mass > massLmin && mass < massLmax && particlecand->isFlagBit(kIsUsed) && particleID == 9 && vectorcandID == 14 && vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max && distance < max_distanceL){
		if(mass > massLmin && mass < massLmax && particlecand->isFlagBit(kIsUsed)){
		    for(int f=0;f<pcnt;f++)//scan all particles detected in HADES except Pion used for Lambda reconstraction
		    {
		      if(f==l)
			  continue;//skip pion from lambda decay

		      ksicand = HCategoryManager::getObject(ksicand, fCatParticleCandSim,f);
		      if(!ksicand->isFlagBit(kIsUsed)) continue; // only the best tracks
		      ksicandGeantID = ksicand -> getGeantPID();
		      ksicand_parentID = ksicand -> getGeantParentPID();
			    
		      float mom_h_Xi = ksicand -> getMomentum();
		      float charge_h_Xi = ksicand -> getCharge();
		      float dEdx_h_Xi = ksicand -> getMdcdEdx();
		      float beta_h_Xi = ksicand -> getBeta();
		      //float mass_h_Xi = ksicand -> getMass();
		      float mass_h_Xi =  mom_h_Xi*(TMath::Sqrt((1/beta_h_Xi/beta_h_Xi)-1)); 
		      float mass2_h_Xi = mass_h_Xi*mass_h_Xi;
		      //float ener_h_Xi = .5*mom_h*mom_h/mass_h;
		      float pq_h_Xi = mom_h_Xi*charge_h_Xi;
		      //float tof_h_Xi = ksicand -> getTof();

		      // PID
		      if(beta_h_Xi!=-1)
			  ksicandID = mass2PIDfit(fitpar, mass2_h_Xi, charge_h_Xi, nPartSpec);
		      else break;
		      // cout << "ksicandID: " << ksicandID << endl;
		      // cout << "mass2ksicand: " << mass2_h_Xi << endl;
		      // cout << "qksicand: " << charge_h_Xi << endl;
		      hPpid -> Fill(ksicandID+30);
		      
		      if(!ksicandID){
			  cout << "break: invalid ksicandID: " << ksicandID << endl;
		      }

		      ksicand->calc4vectorProperties(HPhysicsConstants::mass(ksicandID));

		      TLorentzVector pi2Vector = *ksicand;
		      float thh2 = pi2Vector.Theta();
		      float phh2 = pi2Vector.Phi();
		      //cm
		      TLorentzVector *pi2Vector_cm = new TLorentzVector(0,0,0,0);
		      *pi2Vector_cm = *ksicand;
		      pi2Vector_cm -> Boost(-(*beam).BoostVector());
		      Float_t thh2cm = pi2Vector_cm->Theta();
		      Float_t phh2cm = pi2Vector_cm->Phi();
		      
		      HGeomVector base_pion;
		      HGeomVector dir_pion;
		      particle_tool.calcSegVector(ksicand->getZ(),ksicand->getR(),TMath::DegToRad()*ksicand->getPhi(),TMath::DegToRad()*ksicand->getTheta(),base_pion,dir_pion);
		      HGeomVector base_lambda=vertex;
		      HGeomVector dir_lambda(sum_mass.X(),sum_mass.Y(),sum_mass.Z());
		      //calculate distance between pion and lambda
		      double distance_ksi=particle_tool.calculateMinimumDistance(base_lambda,dir_lambda,base_pion,dir_pion);			  
		      TLorentzVector ksiVector=sum_mass+*ksicand;
		      double ksiMass = ksiVector.M();

		      //calculate vertex Xi
		      HGeomVector vertex_ksi;
		      vertex_ksi=particle_tool.calcVertexAnalytical(base_lambda,dir_lambda,base_pion,dir_pion);
		      double ksiVertX = vertex_ksi.X();
		      double ksiVertY = vertex_ksi.Y();
		      double ksiVert  = vertex_ksi.Z();
		      Float_t ksiVertR = TMath::Sqrt(ksiVertX*ksiVertX + ksiVertY*ksiVertY);
		      
		      //geant vertex Xi
		      double ksiVertXgeant = ksicand -> getGeantxVertex();
		      double ksiVertYgeant = ksicand -> getGeantyVertex();
		      double ksiVertZgeant = ksicand -> getGeantzVertex();
		      Float_t ksiVertRgeant = TMath::Sqrt(ksiVertXgeant*ksiVertXgeant + ksiVertYgeant*ksiVertYgeant);

		      double dvertxiX, dvertxiY, dvertxiZ, dvertxiR;
		      dvertxiX = ksiVertXgeant - ksiVertX;
		      dvertxiY = ksiVertYgeant - ksiVertY;
		      dvertxiZ = ksiVertZgeant - ksiVert;
		      dvertxiR = TMath::Sqrt(dvertxiX*dvertxiX + dvertxiY*dvertxiY + dvertxiZ*dvertxiZ);
		      
		      float thx = ksiVector.Theta();
		      float phx = ksiVector.Phi();
		      //cm
		      TLorentzVector *ksiVector_cm = new TLorentzVector(0,0,0,0);
		      *ksiVector_cm = sum_mass+*ksicand;
		      ksiVector_cm -> Boost(-(*beam).BoostVector());
		      Float_t thxcm = ksiVector_cm->Theta();
		      Float_t phxcm = ksiVector_cm->Phi();

		      
		      if(vectorcandGeantID == 14 && particleGeantID == 9 && vectorcand_parentID == 18 && particlecand_parentID == 18){
			  hGeantxVertexA -> Fill(lamVertXgeantA);
			  hGeantyVertexA -> Fill(lamVertYgeantA);
			  hGeantzVertexA -> Fill(lamVertZgeantA);
			  hGeantxVertexB -> Fill(lamVertXgeantB);
			  hGeantyVertexB -> Fill(lamVertYgeantB);
			  hGeantzVertexB -> Fill(lamVertZgeantB);

			  hGeantPIDA -> Fill(GeantPIDA);
			  hGeantPIDB -> Fill(GeantPIDB);

			  hGeantPIDAparent -> Fill(GeantPIDAparent);
			  hGeantPIDBparent -> Fill(GeantPIDBparent);

			  hdvertlX -> Fill(dvertlX);
			  hdvertlY -> Fill(dvertlY);
			  hdvertlZ -> Fill(dvertlZ);
			  hdvertlR -> Fill(dvertlR);
			  hdvertxiX -> Fill(dvertxiX);
			  hdvertxiY -> Fill(dvertxiY);
			  hdvertxiZ -> Fill(dvertxiZ);
			  hdvertxiR -> Fill(dvertxiR);

			  hvertex_x -> Fill(vertex_x);
			  hvertex_y -> Fill(vertex_y);
			  hvertex_z -> Fill(vertex_z);

			  hMomArecox -> Fill(momArecox);
			  hMomArecoy -> Fill(momArecoy);
			  hMomArecoz -> Fill(momArecoz);
			  hMomAGeax -> Fill(momAsimx);
			  hMomAGeay -> Fill(momAsimy);
			  hMomAGeaz -> Fill(momAsimz);
			  hMomAResx -> Fill(momAsimx - momArecox);
			  hMomAResy -> Fill(momAsimy - momArecoy);
			  hMomAResz -> Fill(momAsimz - momArecoz);

			  hMomBrecox -> Fill(momBrecox);
			  hMomBrecoy -> Fill(momBrecoy);
			  hMomBrecoz -> Fill(momBrecoz);
			  hMomBGeax -> Fill(momBsimx);
			  hMomBGeay -> Fill(momBsimy);
			  hMomBGeaz -> Fill(momBsimz);
			  hMomBResx -> Fill(momBsimx - momBrecox);
			  hMomBResy -> Fill(momBsimy - momBrecoy);
			  hMomBResz -> Fill(momBsimz - momBrecoz);

			  hrA -> Fill(r_hA);
			  hrB -> Fill(r_vB);
			  hzA -> Fill(z_hA);
			  hzB -> Fill(z_vB);
			  hPhiA -> Fill(phi_hA);
			  hPhiB -> Fill(phi_vB);
			  hThetaA -> Fill(theta_hA);
			  hThetaB -> Fill(theta_vB);
			  
		      }
		      
		      if(particleID != 9 || vectorcandID != 14 || vertex_z < cut_vertex_z_minL || vertex_z > cut_vertex_z_max || distance > max_distanceL)
			  continue;
		      
		      if(ksicandID==9){ //particle in Hades is pion
    			  hTDpiL -> Fill(distance_ksi);  //dist between L and pi
			  hMXAll -> Fill(ksiMass); //mass Xi: MTD_L, VERTzL, mL
			  hTDpiL_HF -> Fill(distance_ksi);  
			  hMXAll_HF -> Fill(ksiMass); 
			  
			  hThetaH2 -> Fill(thh2);
			  hPhiH2 -> Fill(phh2);		    
			  hThetaH2_cm -> Fill(thh2cm);
			  hPhiH2_cm -> Fill(phh2cm);		    
			  if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23){ //pion and proton from real Lambda
			      hrealX -> Fill(ksiMass);
			      hrealX_HF -> Fill(ksiMass);
			  }
			  if(distance_ksi < max_distanceX){
			      hMXPiLMTD -> Fill(ksiMass);
			      hMXPiLMTD_HF -> Fill(ksiMass);
			      
			      hThetaX -> Fill(thx);
			      hPhiX -> Fill(phx);
			      hThetaX_cm -> Fill(thxcm);
			      hPhiX_cm -> Fill(phxcm);		    
			      hXVertpiL -> Fill(ksiVert);
			      hXVertpiL_HF -> Fill(ksiVert);
			      
			      if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23){ //pion and proton from real Lambda
				  hrealXMTD -> Fill(ksiMass);
				  hrealXMTD_HF -> Fill(ksiMass);
			      }
			  			      
			      if(ksiVert > cut_vertex_z_minX && ksiVert < cut_vertex_z_max){
				  hMXPiLMTDVert -> Fill(ksiMass);
				  hMXPiLMTDVert_HF -> Fill(ksiMass);
				  if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23){ //pion and proton from real Lambda
				      hrealXMTDVert -> Fill(ksiMass);
				      hrealXMTDVert_HF -> Fill(ksiMass);
				  }
			      }
			  }
		      }
		    } //end scan for second pion
		} //end Xi reconstruction
	    } //end H-F
//>>>>>>>>>>>>>>>>
	    // H-H-
	    for(int j=0; j<pcnt; j++){//vector candidates, HADES loop-------------------------------------------------- no FD!!!
		if(j==l)
		    continue; //skip pion from lambda decay, no FD!!!
		
		float dE_v = 0; 
		float r_v = 0; 
		float tofEloss_v = 0;

                //no FD!!!
		particlecand2 = HCategoryManager::getObject(particlecand2, fCatParticleCandSim,j);
		if(!particlecand2->isFlagBit(kIsUsed)) continue; //only the best tracks

		r_vB = particlecand2 -> getR();
		z_vB = particlecand2 -> getZ();
		phi_vB = particlecand2 -> getPhi();
		theta_vB = particlecand2 -> getTheta();
		
		float mom_v = particlecand2 -> getMomentum();
		float charge_v = particlecand2 -> getCharge();
		float dEdx_v = particlecand2 -> getMdcdEdx();
		float beta_v = particlecand2 -> getBeta();
		float mass_v =  mom_v*(TMath::Sqrt((1/beta_v/beta_v)-1));
		float mass2_v = mass_v*mass_v;
		float ener_v = mass_v*((1/TMath::Sqrt(1-beta_v*beta_v))-1);
		float pq_v = mom_v*charge_v;
		float tofRec_v = particlecand2 -> getTofRec();
		float tof_v = particlecand2 -> getTof();

		// PID
		if(beta_v!=-1)
		    //particleID = mass2PID(mass2_h, charge_h); //PID as ranges in m2(pq) spectrum
		    vectorcandID = mass2PIDfit(fitpar, mass2_v, charge_v, nPartSpec); //PID based on m2 spectrum
		else break;
		//end no FD!!!

		Float_t momBrecox = particlecand2 -> Px();
		Float_t momBrecoy = particlecand2 -> Py();
		Float_t momBrecoz = particlecand2 -> Pz();
		Float_t momBsimx = particlecand2 -> getGeantxMom();
		Float_t momBsimy = particlecand2 -> getGeantyMom();
		Float_t momBsimz = particlecand2 -> getGeantzMom();
		
		//              vectorcandID = 14;
		hPpid -> Fill(vectorcandID+20);

		particlecand2 -> calc4vectorProperties(HPhysicsConstants::mass(vectorcandID));
		vectorcandGeantID = particlecand2 -> getGeantPID();
		vectorcand_parentID = particlecand2 -> getGeantParentPID();
	   
		TLorentzVector pVector = *particlecand2;
		float thv = pVector.Theta();
		float phv = pVector.Phi();
		//cm
		TLorentzVector *pVector_cm = new TLorentzVector(0,0,0,0);
		*pVector_cm = *particlecand2;
		pVector_cm -> Boost(-(*beam).BoostVector());
		Float_t thvcm = pVector_cm->Theta();
		Float_t phvcm = pVector_cm->Phi();
						
/*		if(tof_v != -1){
		    //	cout << "tofRec_v: " << tofRec_v << " tof_v: " << tof_v << endl;
		    hdE_fd -> Fill(dE_v);
		    hdetof_fd -> Fill(dE_v, tof_v);

		    hTof_all_fd -> Fill(tof_v);
		    hTof_all -> Fill(tof_v);
		    if(vectorcandID == 9){
			hTof_pim_fd -> Fill(tof_v);
			hTof_pim -> Fill(tof_v);
		    }
		    else if(vectorcandID == 11){
			hTof_Kp_fd -> Fill(tof_v);
			hTof_Kp -> Fill(tof_v);
		    }
		    else if(vectorcandID == 14){
			hTof_p_fd -> Fill(tof_v);
			hTof_p -> Fill(tof_v);
			hThetaV -> Fill(thv);
			hPhiV -> Fill(phv);
			hThetaV_cm -> Fill(thvcm);
			hPhiV_cm -> Fill(phvcm);
		    }
		}
		if(tof_v != -1){
		    //	cout << "tofRec_v: " << tofRec_v << " tof_v: " << tof_v << endl;
		    hTof_all_fd_GeantID -> Fill(tof_v);
		    hTof_all_GeantID -> Fill(tof_v);
		    if(vectorcandGeantID == 9){
			hTof_pim_fd_GeantID -> Fill(tof_v);
			hTof_pim_GeantID -> Fill(tof_v);
			hdetof_fd_Geant -> Fill(dE_v, tof_v);
			hdetof_fd_Geant9 -> Fill(dE_v, tof_v);
		    }
		    else if(vectorcandGeantID == 11){
			hTof_Kp_fd_GeantID -> Fill(tof_v);
			hTof_Kp_GeantID -> Fill(tof_v);
			hdetof_fd_Geant -> Fill(dE_v, tof_v);
			hdetof_fd_Geant11 -> Fill(dE_v, tof_v);
		    }
		    else if(vectorcandGeantID == 14){
			hTof_p_fd_GeantID -> Fill(tof_v);
			hTof_p_GeantID -> Fill(tof_v);
			hdetof_fd_Geant -> Fill(dE_v, tof_v);
			hdetof_fd_Geant14 -> Fill(dE_v, tof_v);
		    }
		}
*/
		HGeomVector base_H;
		HGeomVector dir_H;
		particle_tool.calcSegVector(particlecand->getZ(),particlecand->getR(),TMath::DegToRad()*particlecand->getPhi(),TMath::DegToRad()*particlecand->getTheta(),base_H,dir_H);
	
		HGeomVector base_FW;
		HGeomVector dir_FW;
		particle_tool.calcSegVector(particlecand2->getZ(),particlecand2->getR(),TMath::DegToRad()*particlecand2->getPhi(),TMath::DegToRad()*particlecand2->getTheta(),base_FW,dir_FW); //no FD!!!
		//*******************
		double distance=particle_tool.calculateMinimumDistance(base_FW,dir_FW,base_H,dir_H);

		HGeomVector vertex;
		vertex=particle_tool.calcVertexAnalytical(base_FW,dir_FW,base_H,dir_H);
		Float_t vertex_x = vertex.X();
		Float_t vertex_y = vertex.Y();
		Float_t vertex_z = vertex.Z();
		Float_t vertex_r = TMath::Sqrt(vertex.X()*vertex.X()+vertex.Y()*vertex.Y());

		//geant vertex pi^- from Lambda(1115)
		double lamVertXgeantB = particlecand2 -> getGeantxVertex();
		double lamVertYgeantB = particlecand2 -> getGeantyVertex();
		double lamVertZgeantB = particlecand2 -> getGeantzVertex();
		Float_t lamVertRgeantB = TMath::Sqrt(lamVertXgeantB*lamVertXgeantB + lamVertYgeantB*lamVertYgeantB);
		double dvertlX, dvertlY, dvertlZ, dvertlR;
		dvertlX = lamVertXgeantB - vertex_x;
		dvertlY = lamVertYgeantB - vertex_y;
		dvertlZ = lamVertZgeantB - vertex_z;
		dvertlR = TMath::Sqrt(dvertlX*dvertlX + dvertlY*dvertlY + dvertlZ*dvertlZ);

		int GeantPIDA = particlecand -> getGeantPID();
		int GeantPIDB = particlecand2 -> getGeantPID();

		int GeantPIDAparent = particlecand -> getGeantParentPID();
		int GeantPIDBparent = particlecand2 -> getGeantParentPID();

		int GeantPIDAGparent = particlecand -> getGeantGrandParentPID();
		int GeantPIDBGparent = particlecand2 -> getGeantGrandParentPID();

		TLorentzVector sum_mass = *particlecand2 + *particlecand;
		Float_t mass=sum_mass.M();
		Float_t betaL=sum_mass.Beta();
		//lab
		Float_t thetaL=sum_mass.Theta(); 
		Float_t cosThetaL=sum_mass.CosTheta(); 
		Float_t phiL=sum_mass.Phi(); 
		Float_t momL=sum_mass.P();
		Float_t yL=sum_mass.Rapidity();
//		Float_t pseudoyL=sum_mass.PseudoRapidity();
		//cm
		TLorentzVector *sum_mass_cm = new TLorentzVector(0,0,0,0);
		*sum_mass_cm = *particlecand2 + *particlecand;
		sum_mass_cm -> Boost(-(*beam).BoostVector());
		Float_t thetaLcm=sum_mass_cm->Theta();
		Float_t cosThetaLcm=sum_mass_cm->CosTheta();
		Float_t phiLcm=sum_mass_cm->Phi();
		Float_t momLcm=sum_mass_cm->P();
		Float_t yLcm=sum_mass_cm->Rapidity();
//		Float_t pseudoyLcm=sum_mass_cm->PseudoRapidity();
	      		
		hMLAll -> Fill(mass);
		hMLAll_HH -> Fill(mass);

		if(particleID == 9){ //pion in HADES, any second part.
		    //   cout << "H 9" << "mass=" << mass << endl;
		    hMLPiHades -> Fill(mass);
		    hTDpiFD -> Fill(distance);
		    hMLPiHades_HH -> Fill(mass);
		    hTDpiFD_HH -> Fill(distance);

		    if(vectorcandID == 14){ //pion in HADES, proton in HADES
			hMLPiHpF -> Fill(mass);
			hTDpip -> Fill(distance);
			hMLPiHpF_HH -> Fill(mass);
			hTDpip_HH -> Fill(distance);
			if(particlecand_parentID==18 && vectorcand_parentID==18){ //pion and proton from real Lambda
			    hrealL -> Fill(mass);
			    hrealL_HH -> Fill(mass);
			}
		    }
		
		    if(distance < max_distanceL){ //MTD_L cut
			//pion in HADES, any second part.
			hMLPiHadesMTD -> Fill(mass);
			hVertpiFD -> Fill(vertex_z);
			hMLPiHadesMTD_HH -> Fill(mass);
			hVertpiFD_HH -> Fill(vertex_z);
			
			if(vectorcandID == 14){ //pion in HADES, proton in HADES
			    hMLPiHpFMTD -> Fill(mass);
			    hVertpip -> Fill(vertex_z);
			    hMLPiHpFMTD_HH -> Fill(mass);
			    hVertpip_HH -> Fill(vertex_z);
			    if(particlecand_parentID==18 && vectorcand_parentID==18){ //pion and proton from real Lambda
				hrealLMTD -> Fill(mass);
				hrealLMTD_HH -> Fill(mass);
			    }
			}
		    
			if(vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max){ //VERTz_L cut
			    //pion in HADES, any second part.
			    hMLPiHadesMTDVert -> Fill(mass);
			    hMLPiHadesMTDVert_HH -> Fill(mass);

			    if(vectorcandID == 14){ //pion in HADES, proton in HADES
				hMLPiHpFMTDVert -> Fill(mass);
				hMLPiHpFMTDVert_HH -> Fill(mass);
						
				if(particlecand_parentID==18 && vectorcand_parentID==18){ //pion and proton from	real Lambda
				    hrealLMTDVert -> Fill(mass);
				    hrealLMTDVert_HH -> Fill(mass);
				    
				    hThetaLcm -> Fill(thetaLcm);
				    hThetaL -> Fill(thetaL);
				    hCosThetaLcm -> Fill(cosThetaLcm);
				    hMomThetaLcm -> Fill(momLcm, thetaLcm);
				    hPhiLcm -> Fill(phiLcm);
				    hPhiL -> Fill(phiL);
				    hMomLcm -> Fill(momLcm);
				    hRapLcm -> Fill(yLcm);
//				hPseuRapLcm -> Fill(pseudoyLcm);
				}
			    }
			}	
		    }
		}
		
		//xxxxxxxxxxxxxxxxxxxxxxxxx
		//Xi reconstruction
		// H-H-H
//		if(mass > massLmin && mass < massLmax && particlecand->isFlagBit(kIsUsed) && particleID == 9 && vectorcandID == 14 && vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max && distance < max_distanceL){
		if(mass > massLmin && mass < massLmax && particlecand->isFlagBit(kIsUsed) && particlecand2->isFlagBit(kIsUsed)){
		    for(int f=0;f<pcnt;f++)//scan all particles detected in HADES except Pion used for Lambda reconstraction
		    {
		      if(f==l)
			  continue;//skip pion from lambda decay
		      if(f==j)
			  continue;//skip proton from lambda decay if there is no FD!!!

		      ksicand = HCategoryManager::getObject(ksicand, fCatParticleCandSim,f);
		      if(!ksicand->isFlagBit(kIsUsed)) continue; // only the best tracks
		      ksicandGeantID = ksicand -> getGeantPID();
		      ksicand_parentID = ksicand -> getGeantParentPID();
			    
		      float mom_h_Xi = ksicand -> getMomentum();
		      float charge_h_Xi = ksicand -> getCharge();
		      float dEdx_h_Xi = ksicand -> getMdcdEdx();
		      float beta_h_Xi = ksicand -> getBeta();
		      //float mass_h_Xi = ksicand -> getMass();
		      float mass_h_Xi =  mom_h_Xi*(TMath::Sqrt((1/beta_h_Xi/beta_h_Xi)-1)); 
		      float mass2_h_Xi = mass_h_Xi*mass_h_Xi;
		      //float ener_h_Xi = .5*mom_h*mom_h/mass_h;
		      float pq_h_Xi = mom_h_Xi*charge_h_Xi;
		      //float tof_h_Xi = ksicand -> getTof();

		      // PID
		      if(beta_h_Xi!=-1)
			  ksicandID = mass2PIDfit(fitpar, mass2_h_Xi, charge_h_Xi, nPartSpec);
		      else break;
		      // cout << "ksicandID: " << ksicandID << endl;
		      // cout << "mass2ksicand: " << mass2_h_Xi << endl;
		      // cout << "qksicand: " << charge_h_Xi << endl;
		      hPpid -> Fill(ksicandID+30);
		      
		      if(!ksicandID){
			  cout << "break: invalid ksicandID: " << ksicandID << endl;
		      }

		      ksicand->calc4vectorProperties(HPhysicsConstants::mass(ksicandID));

		      TLorentzVector pi2Vector = *ksicand;
		      float thh2 = pi2Vector.Theta();
		      float phh2 = pi2Vector.Phi();
		      //cm
		      TLorentzVector *pi2Vector_cm = new TLorentzVector(0,0,0,0);
		      *pi2Vector_cm = *ksicand;
		      pi2Vector_cm -> Boost(-(*beam).BoostVector());
		      Float_t thh2cm = pi2Vector_cm->Theta();
		      Float_t phh2cm = pi2Vector_cm->Phi();
		      
		      HGeomVector base_pion;
		      HGeomVector dir_pion;
		      particle_tool.calcSegVector(ksicand->getZ(),ksicand->getR(),TMath::DegToRad()*ksicand->getPhi(),TMath::DegToRad()*ksicand->getTheta(),base_pion,dir_pion);
		      HGeomVector base_lambda=vertex;
		      HGeomVector dir_lambda(sum_mass.X(),sum_mass.Y(),sum_mass.Z());
		      //calculate distance between pion and lambda
		      double distance_ksi=particle_tool.calculateMinimumDistance(base_lambda,dir_lambda,base_pion,dir_pion);			  
		      TLorentzVector ksiVector=sum_mass+*ksicand;
		      double ksiMass = ksiVector.M();
		      
		      //calculate vertex Xi
		      HGeomVector vertex_ksi;
		      vertex_ksi=particle_tool.calcVertexAnalytical(base_lambda,dir_lambda,base_pion,dir_pion);
		      double ksiVertX = vertex_ksi.X();
		      double ksiVertY = vertex_ksi.Y();
		      double ksiVert  = vertex_ksi.Z();
		      Float_t ksiVertR = TMath::Sqrt(ksiVertX*ksiVertX + ksiVertY*ksiVertY);
		      
		      //geant vertex Xi
		      double ksiVertXgeant = ksicand -> getGeantxVertex();
		      double ksiVertYgeant = ksicand -> getGeantyVertex();
		      double ksiVertZgeant = ksicand -> getGeantzVertex();
		      Float_t ksiVertRgeant = TMath::Sqrt(ksiVertXgeant*ksiVertXgeant + ksiVertYgeant*ksiVertYgeant);

		      double dvertxiX, dvertxiY, dvertxiZ, dvertxiR;
		      dvertxiX = ksiVertXgeant - ksiVertX;
		      dvertxiY = ksiVertYgeant - ksiVertY;
		      dvertxiZ = ksiVertZgeant - ksiVert;
		      dvertxiR = TMath::Sqrt(dvertxiX*dvertxiX + dvertxiY*dvertxiY + dvertxiZ*dvertxiZ);
		      
		      float thx = ksiVector.Theta();
		      float phx = ksiVector.Phi();
		      //cm
		      TLorentzVector *ksiVector_cm = new TLorentzVector(0,0,0,0);
		      *ksiVector_cm = sum_mass+*ksicand;
		      ksiVector_cm -> Boost(-(*beam).BoostVector());
		      Float_t thxcm = ksiVector_cm->Theta();
		      Float_t phxcm = ksiVector_cm->Phi();

		      
		      if(vectorcandGeantID == 14 && particleGeantID == 9 && vectorcand_parentID == 18 && particlecand_parentID == 18){
			  hGeantxVertexA -> Fill(lamVertXgeantA);
			  hGeantyVertexA -> Fill(lamVertYgeantA);
			  hGeantzVertexA -> Fill(lamVertZgeantA);
			  hGeantxVertexB -> Fill(lamVertXgeantB);
			  hGeantyVertexB -> Fill(lamVertYgeantB);
			  hGeantzVertexB -> Fill(lamVertZgeantB);

			  hGeantPIDA -> Fill(GeantPIDA);
			  hGeantPIDB -> Fill(GeantPIDB);

			  hGeantPIDAparent -> Fill(GeantPIDAparent);
			  hGeantPIDBparent -> Fill(GeantPIDBparent);

			  hdvertlX -> Fill(dvertlX);
			  hdvertlY -> Fill(dvertlY);
			  hdvertlZ -> Fill(dvertlZ);
			  hdvertlR -> Fill(dvertlR);
			  hdvertxiX -> Fill(dvertxiX);
			  hdvertxiY -> Fill(dvertxiY);
			  hdvertxiZ -> Fill(dvertxiZ);
			  hdvertxiR -> Fill(dvertxiR);

			  hvertex_x -> Fill(vertex_x);
			  hvertex_y -> Fill(vertex_y);
			  hvertex_z -> Fill(vertex_z);

			  hMomArecox -> Fill(momArecox);
			  hMomArecoy -> Fill(momArecoy);
			  hMomArecoz -> Fill(momArecoz);
			  hMomAGeax -> Fill(momAsimx);
			  hMomAGeay -> Fill(momAsimy);
			  hMomAGeaz -> Fill(momAsimz);
			  hMomAResx -> Fill(momAsimx - momArecox);
			  hMomAResy -> Fill(momAsimy - momArecoy);
			  hMomAResz -> Fill(momAsimz - momArecoz);
			  hMomBrecox -> Fill(momBrecox);
			  hMomBrecoy -> Fill(momBrecoy);
			  hMomBrecoz -> Fill(momBrecoz);
			  hMomBGeax -> Fill(momBsimx);
			  hMomBGeay -> Fill(momBsimy);
			  hMomBGeaz -> Fill(momBsimz);
			  hMomBResx -> Fill(momBsimx - momBrecox);
			  hMomBResy -> Fill(momBsimy - momBrecoy);
			  hMomBResz -> Fill(momBsimz - momBrecoz);

			  hrA -> Fill(r_hA);
			  hrB -> Fill(r_vB);
			  hzA -> Fill(z_hA);
			  hzB -> Fill(z_vB);
			  hPhiA -> Fill(phi_hA);
			  hPhiB -> Fill(phi_vB);
			  hThetaA -> Fill(theta_hA);
			  hThetaB -> Fill(theta_vB);

		      }

		      if(particleID != 9 || vectorcandID != 14 || vertex_z < cut_vertex_z_minL || vertex_z > cut_vertex_z_max || distance > max_distanceL)
			  continue;

		      
		      if(ksicandID==9){ //particle in Hades is pion
    			  hTDpiL->Fill(distance_ksi);  //dist between L and pi
			  hMXAll->Fill(ksiMass); //mass Xi: MTD_L, VERTzL, mL
			  hTDpiL_HH->Fill(distance_ksi);  //dist between L and pi
			  hMXAll_HH->Fill(ksiMass); //mass Xi: MTD_L, VERTzL, mL
			  
			  hThetaH2 -> Fill(thh2);
			  hPhiH2 -> Fill(phh2);		    
			  hThetaH2_cm -> Fill(thh2cm);
			  hPhiH2_cm -> Fill(phh2cm);		    
			  if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23){ //pion and proton from real Lambda
			      hrealX -> Fill(ksiMass);
			      hrealX_HH -> Fill(ksiMass);
			  }
			                   
			  if(distance_ksi < max_distanceX){
			      hMXPiLMTD -> Fill(ksiMass);
			      hMXPiLMTD_HH -> Fill(ksiMass);
			      
			      hThetaX -> Fill(thx);
			      hPhiX -> Fill(phx);
			      hThetaX_cm -> Fill(thxcm);
			      hPhiX_cm -> Fill(phxcm);		    
			      hXVertpiL -> Fill(ksiVert);
			      hXVertpiL_HH -> Fill(ksiVert);
					      
			      if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23){ //pion and proton from real Lambda
				  hrealXMTD -> Fill(ksiMass);
				  hrealXMTD_HH -> Fill(ksiMass);
			      }
			      if(ksiVert > cut_vertex_z_minX && ksiVert < cut_vertex_z_max){
				  hMXPiLMTDVert -> Fill(ksiMass);
				  hMXPiLMTDVert_HH -> Fill(ksiMass);
				  if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23){ //pion and proton from real Lambda
				      hrealXMTDVert -> Fill(ksiMass);
				      hrealXMTDVert_HH -> Fill(ksiMass);
				  }
			      }
			  }
		      }
		    } //end scan for second pion
		} //end Xi reconstruction
	    } //end H-H-
//<<<<<<<<<<<<<<<
	} //end HADES

	eventNo = i;
	heventNo -> Fill(i);
    }//end event loop

    hM12_h = massPID(hM12_h);
    
    output_file->cd();
    gPad -> SetLogz();
    //MDC only
    hdEdx_mdc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hEkin_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_m_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM1_h -> GetXaxis() -> SetTitle("m [MeV]");
    hM12_h -> GetXaxis() -> SetTitle("m^{2}*q [MeV]");
    hM12_h_m2 -> GetXaxis() -> SetTitle("m^{2} [MeV]");
    hM12_h_pos -> GetXaxis() -> SetTitle("m^{2}*q [MeV]");
    hM12_h_neg -> GetXaxis() -> SetTitle("m^{2}*q [MeV]");
    hM12_h_pions -> GetXaxis() -> SetTitle("m^{2}*q [MeV]");
    hM2_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM22_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM1_m_h -> GetXaxis() -> SetTitle("m*q [MeV]");
    hM2_m_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM22_m_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");

    hdEdx_mdc -> GetYaxis() -> SetTitle("dE/dx");
    hBeta_h -> GetYaxis() -> SetTitle("#beta");
    hEkin_h -> GetYaxis() -> SetTitle("E_{kin} [MeV]");
    hBeta_m_h -> GetYaxis() -> SetTitle("#beta");
    hM1_h -> GetYaxis() -> SetTitle("counts");
    hM12_h -> GetYaxis() -> SetTitle("counts");
    hM12_h_m2 -> GetYaxis() -> SetTitle("counts");
    hM12_h_pos -> GetYaxis() -> SetTitle("counts");
    hM12_h_neg -> GetYaxis() -> SetTitle("counts");
    hM12_h_pions -> GetYaxis() -> SetTitle("counts");
    hM2_h -> GetYaxis() -> SetTitle("m*q [MeV]");
    hM22_h -> GetYaxis() -> SetTitle("m^{2}*q [(MeV)^{2}]");
    hM1_m_h -> GetYaxis() -> SetTitle("counts");
    hM2_m_h -> GetYaxis() -> SetTitle("m*q [MeV]");
    hM22_m_h -> GetYaxis() -> SetTitle("m^{2}*q [(MeV)^{2}]");
    
    hdEdx_mdc -> Write();
    hBeta_h -> Write();
    hEkin_h -> Write();
    hBeta_m_h -> Write();
    hM1_h -> Write();
    hM12_h -> Write();
    hM12_h_m2 -> Write();
    hM12_h_pos -> Write();
    hM12_h_neg -> Write();
    hM12_h_pions -> Write();
    hM2_h -> Write();
    hM22_h -> Write();
    hM1_m_h -> Write();
    hM12_m_h -> Write();
    hM2_m_h -> Write();
    hM22_m_h -> Write();

    //pid
    cMassPID_h -> cd();
    hM12_h -> Draw();
    float a1 = 0;
    float a2 = 0;
    float hmax = hM12_h -> GetBinContent(hM12_h -> GetMaximumBin());
    TLine *lpid1 = new TLine(a1, 0, a1, hmax);
    TLine *lpid2 = new TLine(a2, 0, a2, hmax);
    TLine *lpid3 = new TLine(a1, hmax, a2, hmax);
    TPaveText *ptp = new TPaveText(.14, .8, .16, .85, "NDC");
    ptp -> SetFillColor(0);
    ptp -> SetBorderSize(0);
//    ptp -> SetTextSize(0.07);

    for(int j = 0; j < nPartSpec; j++){
	float mean = fitpar[3*j+1];
	float sigma = -1;
	if(j < 2)
	    sigma = 3*fitpar[3*j+2]; //for pions: 3sigma
	else
	    sigma = 2*fitpar[3*j+2]; //for p and K: 2sigma
	if(j == 0){
	    a1 = mean-sigma;
	    a2 = 0;
	    lpid1 = new TLine(a1, 0, a1, hmax);
	    lpid2 = new TLine(a2, 0, a2, hmax);
	    lpid1 -> SetLineColor(2);
	    lpid1 -> SetLineWidth(3);
	    lpid2 -> SetLineColor(2);
	    lpid2 -> SetLineWidth(3);
	    lpid1 -> Draw("same");
	    lpid2 -> Draw("same");
	    lpid3 = new TLine(a1, hmax*3/4, a2, hmax*3/4);
	    lpid3 -> SetLineColor(2);
	    lpid3 -> SetLineWidth(3);
	    lpid3 -> SetLineStyle(9);
	    lpid3 -> Draw("same");
	    ptp -> AddText("#pi^{-}");
	    ptp -> SetTextColor(2);
	    ptp -> Draw("same");
	}else if(j == 1){
	    a1 = 0;
	    a2 = mean+sigma;
	    lpid1 = new TLine(a1, 0, a1, hmax);
	    lpid2 = new TLine(a2, 0, a2, hmax);
	    lpid1 -> SetLineColor(6);
	    lpid1 -> SetLineWidth(3);
	    lpid2 -> SetLineColor(6);
	    lpid2 -> SetLineWidth(3);
	    lpid1 -> Draw("same");
	    lpid2 -> Draw("same");
	    lpid3 = new TLine(a1, hmax/2, a2, hmax/2);
	    lpid3 -> SetLineColor(6);
	    lpid3 -> SetLineWidth(3);
	    lpid3 -> SetLineStyle(9);
	    lpid3 -> Draw("same");
	    ptp = new TPaveText(.22, .8, .24, .85, "NDC");
	    ptp -> SetFillColor(0);
	    ptp -> AddText("#pi^{+}");
	    ptp -> SetTextColor(6);
	    ptp -> Draw("same");
	}else{
	    a1 = mean-sigma;
	    a2 = mean+sigma;
	    lpid1 = new TLine(a1, 0, a1, hmax);
	    lpid2 = new TLine(a2, 0, a2, hmax);
	    lpid3 = new TLine(a1, hmax/2, a2, hmax/2);
	    lpid1 -> SetLineWidth(3);
	    lpid2 -> SetLineWidth(3);
	    lpid3 -> SetLineWidth(3);
	    lpid3 -> SetLineStyle(9);
	    if(j == 2){
		lpid1 -> SetLineColor(4);
		lpid2 -> SetLineColor(4);
		lpid3 -> SetLineColor(4);
		ptp = new TPaveText(.3, .8, .32, .85, "NDC");
		ptp -> SetFillColor(0);
		ptp -> AddText("K^{+}");
		ptp -> SetTextColor(4);
	    }else if(j == 3){
		lpid1 -> SetLineColor(8);
		lpid2 -> SetLineColor(8);
		lpid3 -> SetLineColor(8);
		ptp = new TPaveText(.58, .8, .6, .85, "NDC");
		ptp -> SetFillColor(0);
		ptp -> SetFillColor(0);
		ptp -> AddText("p");
		ptp -> SetTextColor(8);
	    }
	    lpid1 -> Draw("same");
	    lpid2 -> Draw("same");
	    lpid3 -> Draw("same");
	    ptp -> Draw("same");
	}
    }
    cMassPID_h -> Write();

    //pions PID
    cMassPID_pions -> cd();
    hM12_h_pions -> Draw();
    a1 = 0;
    a2 = 0;
    float a1a = 0;
    hmax = hM12_h_pions -> GetBinContent(hM12_h_pions -> GetMaximumBin());
    TLine *lpid1a = new TLine(a1a, 0, a1a, hmax);
    for(int j = 0; j < 2; j++){
	float mean = fitpar[3*j+1];
	float sigma = -1;
	sigma = 3*fitpar[3*j+2]; //for pions: 3sigma
	if(j == 0){
	    a1 = mean-sigma;
	    a2 = 0;
	    a1a = mean+sigma;
	    lpid1 = new TLine(a1, 0, a1, hmax);
	    lpid2 = new TLine(a2, 0, a2, hmax);
	    lpid1 -> SetLineColor(2);
	    lpid1 -> SetLineWidth(3);
	    lpid2 -> SetLineColor(2);
	    lpid2 -> SetLineWidth(3);
	    lpid1 -> Draw("same");
	    lpid2 -> Draw("same");
	    lpid3 = new TLine(a1, hmax*3/4, a2, hmax*3/4);
	    lpid3 -> SetLineColor(2);
	    lpid3 -> SetLineWidth(3);
	    lpid3 -> SetLineStyle(9);
	    lpid3 -> Draw("same");
	    lpid1a = new TLine(a1a, 0, a1a, hmax);
	    lpid1a -> SetLineColor(2);
	    lpid1a -> Draw("same");
	    ptp = new TPaveText(.33, .8, .35, .85, "NDC");
	    ptp -> SetFillColor(0);
	    ptp -> AddText("#pi^{-}");
	    ptp -> SetTextColor(2);
	    ptp -> Draw("same");
	}else if(j == 1){
	    a1 = 0;
	    a2 = mean+sigma;
	    a1a = mean-sigma;
	    lpid1 = new TLine(a1, 0, a1, hmax);
	    lpid2 = new TLine(a2, 0, a2, hmax);
	    lpid1 -> SetLineColor(6);
	    lpid1 -> SetLineWidth(3);
	    lpid2 -> SetLineColor(6);
	    lpid2 -> SetLineWidth(3);
	    lpid1 -> Draw("same");
	    lpid2 -> Draw("same");
	    lpid3 = new TLine(a1, hmax/2, a2, hmax/2);
	    lpid3 -> SetLineColor(6);
	    lpid3 -> SetLineWidth(3);
	    lpid3 -> SetLineStyle(9);
	    lpid3 -> Draw("same");
	    lpid1a = new TLine(a1a, 0, a1a, hmax);
	    lpid1a -> SetLineColor(6);
	    lpid1a -> Draw("same");
	    ptp = new TPaveText(.65, .8, .67, .85, "NDC");
	    ptp -> SetFillColor(0);
	    ptp -> AddText("#pi^{+}");
	    ptp -> SetTextColor(6);
	    ptp -> Draw("same");

	}
    }
    cMassPID_pions -> Write();

    
//    hBeta_q_h -> GetXaxis() -> SetTitle("q");
//    hBeta_q_h -> GetYaxis() -> SetTitle("#beta");
//    hBeta_q_h -> Write();

    cBetaPID_h -> cd();
    cBetaPID_h -> SetLogz();
    hBeta_h -> Draw("colz");
    int j=0;
    while(j < k){
	gCut[j] -> Draw("same");
	j++;
    }
    cBetaPID_h -> Write();
    
    //tof
    hdEdx_tof -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_tof -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hEkin_tof -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_m_tof -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM1_tof -> GetXaxis() -> SetTitle("m*q [MeV]");
    hM12_tof -> GetXaxis() -> SetTitle("m^{2}*q [MeV]");
    hM2_tof -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM22_tof -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM1_m_tof -> GetXaxis() -> SetTitle("m*q [MeV]");
    hM12_m_tof -> GetXaxis() -> SetTitle("m^{2}*q [MeV]");
    hM2_m_tof -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM22_m_tof -> GetXaxis() -> SetTitle("p*q [MeV/c]");
   
    hdEdx_tof -> GetYaxis() -> SetTitle("dE/dx");
    hBeta_tof -> GetYaxis() -> SetTitle("#beta");
    hEkin_tof -> GetYaxis() -> SetTitle("E_{kin} [MeV]");
    hBeta_m_tof -> GetYaxis() -> SetTitle("#beta");
    hM1_tof -> GetYaxis() -> SetTitle("counts");
    hM12_tof -> GetYaxis() -> SetTitle("counts");
    hM2_tof -> GetYaxis() -> SetTitle("m*q [MeV]");
    hM22_tof -> GetYaxis() -> SetTitle("m^{2}*q [MeV^{2}]");
    hM1_m_tof -> GetYaxis() -> SetTitle("counts");
    hM12_m_tof -> GetYaxis() -> SetTitle("counts");
    hM2_m_tof -> GetYaxis() -> SetTitle("m*q [MeV]");
    hM22_m_tof -> GetYaxis() -> SetTitle("m^{2}*q [MeV^{2}]");
    
    hdEdx_tof -> Write();
    hBeta_tof -> Write();
    hEkin_tof -> Write();
    hBeta_m_tof -> Write();
    hM1_tof -> Write();
    hM12_tof -> Write();
    hM2_tof -> Write();
    hM22_tof -> Write();
    hM1_m_tof -> Write();
    hM1_m_tof -> Write();
    hM2_m_tof -> Write();
    hM22_m_tof -> Write();

    hcheckdedx_dedxmdc -> Write();
    hcheckdedx_btof -> Write();
    
    cBetaPID_tof -> cd();
    cBetaPID_tof -> SetLogz();
    hBeta_tof -> Draw("colz");
    j=0;
    while(j < k){
	gCut[j] -> Draw("same");
	j++;
    }
    cBetaPID_tof -> Write();
    
    //RPC
    hdEdx_rpc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_rpc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hEkin_rpc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_m_rpc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM1_rpc -> GetXaxis() -> SetTitle("m*q [MeV]");
    hM12_rpc -> GetXaxis() -> SetTitle("m^{2}*q [MeV^{2}]");
    hM2_rpc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM22_rpc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM1_m_rpc -> GetXaxis() -> SetTitle("m*q [MeV]");
    hM12_m_rpc -> GetXaxis() -> SetTitle("m^{2}*q [MeV^{2}]");
    hM2_m_rpc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM22_m_rpc -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    
    hdEdx_rpc -> GetYaxis() -> SetTitle("dE/dx");
    hBeta_rpc -> GetYaxis() -> SetTitle("#beta");
    hEkin_rpc -> GetYaxis() -> SetTitle("E_{kin} [MeV]");
    hBeta_m_rpc -> GetYaxis() -> SetTitle("#beta");
    hM1_rpc -> GetYaxis() -> SetTitle("counts");
    hM12_rpc -> GetYaxis() -> SetTitle("counts");
    hM2_rpc -> GetYaxis() -> SetTitle("m*q [MeV]");
    hM22_rpc -> GetYaxis() -> SetTitle("m^{2}*q [(MeV)^{2}]");
    hM1_m_rpc -> GetYaxis() -> SetTitle("counts");
    hM12_m_rpc -> GetYaxis() -> SetTitle("counts");
    hM2_m_rpc -> GetYaxis() -> SetTitle("m*q [MeV]");
    hM22_m_rpc -> GetYaxis() -> SetTitle("m^{2}*q [(MeV)^{2}]");
    
    hdEdx_rpc -> Write();
    hBeta_rpc -> Write();
    hEkin_rpc -> Write();
    hBeta_m_rpc -> Write();
    hM1_rpc -> Write();
    hM12_rpc -> Write();
    hM2_rpc -> Write();
    hM22_rpc -> Write();
    hM1_m_rpc -> Write();
    hM12_m_rpc -> Write();
    hM2_m_rpc -> Write();
    hM22_m_rpc -> Write();
    
    cBetaPID_rpc -> cd();
    cBetaPID_rpc -> SetLogz();
    hBeta_rpc -> Draw("colz");
    j=0;
    while(j < k){
	gCut[j] -> Draw("same");
	j++;
    }
    cBetaPID_rpc -> Write();
    
    //FwDet only
    hdE_fd -> GetXaxis() -> SetTitle("dE in straws [MeV]");
    hdE_fd -> GetYaxis() -> SetTitle("#");
    hdE_fd -> Write();
    hdetof_fd -> GetXaxis() -> SetTitle("dE in straws [MeV]");
    hdetof_fd -> GetYaxis() -> SetTitle("tof [ns]");
    hdetof_fd -> Write();
    hdetof_fd_Geant -> GetXaxis() -> SetTitle("dE in straws [MeV]");
    hdetof_fd_Geant -> GetYaxis() -> SetTitle("tof [ns]");
    hdetof_fd_Geant -> Write();
    hdetof_fd_Geant9 -> GetXaxis() -> SetTitle("dE in straws [MeV]");
    hdetof_fd_Geant9 -> GetYaxis() -> SetTitle("tof [ns]");
    hdetof_fd_Geant9 -> Write();
    hdetof_fd_Geant11 -> GetXaxis() -> SetTitle("dE in straws [MeV]");
    hdetof_fd_Geant11 -> GetYaxis() -> SetTitle("tof [ns]");
    hdetof_fd_Geant11 -> Write();
    hdetof_fd_Geant14 -> GetXaxis() -> SetTitle("dE in straws [MeV]");
    hdetof_fd_Geant14 -> GetYaxis() -> SetTitle("tof [ns]");
    hdetof_fd_Geant14 -> Write();
    hr_fd -> GetXaxis() -> SetTitle("drift radius [mm]");
    hr_fd -> GetYaxis() -> SetTitle("#");
    hr_fd -> Write();
 /*hBeta_fd -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_fd -> GetYaxis() -> SetTitle("#beta");
    hBeta_fd -> Write();

    cBetaPID_fd -> cd();
    cBetaPID_fd -> SetLogz();
    hBeta_fd -> Draw("colz");
    j=0;
    while(j < k){
	gCut[j] -> Draw("same");
	j++;
    }
    cBetaPID_fd -> Write();
    */
    //
    /* cBetaPID -> SetLogz();
    cBetaPID -> cd(1);
    hBeta_tof -> Draw("colz");
    j=0;
    while(j < k){
	gCut[j] -> Draw("same");
	j++;
    }
    cBetaPID -> cd(2);
    hBeta_rpc -> Draw("colz");
    j=0;
    while(j < k){
	gCut[j] -> Draw("same");
	j++;
    }
    cBetaPID -> cd(3);
    hBeta_h -> Draw("colz");
    j=0;
    while(j < k){
	gCut[j] -> Draw("same");
	j++;
    }
    cBetaPID -> cd(4);
    hBeta_fd -> Draw("colz");
    j=0;
    while(j < k){
	gCut[j] -> Draw("same");
	j++;
    }
    cBetaPID -> Write();
    */

    //Hades&FwDet ToF
    hTof_pim -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_pim -> GetYaxis() -> SetTitle("counts");
    hTof_Kp -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_Kp -> GetYaxis() -> SetTitle("counts");
    hTof_p -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_p -> GetYaxis() -> SetTitle("counts");
    hTof_all -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_all -> GetYaxis() -> SetTitle("counts");
    hTof_pim -> Write();
    hTof_Kp -> Write();
    hTof_p -> Write();
    hTof_all -> Write();

    cTof -> cd(1);
    hTof_pim -> Draw();
    cTof -> cd(2);
    hTof_Kp -> Draw();
    cTof -> cd(3);
    hTof_p -> Draw();
    cTof -> cd(4);
    hTof_all -> Draw();

    cTof -> Write();

    //Hades Tof
    hTof_pim_h -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_pim_h -> GetYaxis() -> SetTitle("counts");
    hTof_Kp_h -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_Kp_h -> GetYaxis() -> SetTitle("counts");
    hTof_p_h -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_p_h -> GetYaxis() -> SetTitle("counts");
    hTof_all_h -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_all_h -> GetYaxis() -> SetTitle("counts");
    hTof_pim_h -> Write();
    hTof_Kp_h -> Write();
    hTof_p_h -> Write();
    hTof_all_h -> Write();

    cTof_h -> cd(1);
    hTof_pim_h -> Draw();
    cTof_h-> cd(2);
    hTof_Kp_h -> Draw();
    cTof_h -> cd(3);
    hTof_p_h -> Draw();
    cTof_h -> cd(4);
    hTof_all_h -> Draw();

    cTof_h -> Write();

    //FwDet Tof
    hTof_pim_fd -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_pim_fd -> GetYaxis() -> SetTitle("counts");
    hTof_Kp_fd -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_Kp_fd -> GetYaxis() -> SetTitle("counts");
    hTof_p_fd -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_p_fd -> GetYaxis() -> SetTitle("counts");
    hTof_all_fd -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_all_fd -> GetYaxis() -> SetTitle("counts");
    hTof_pim_fd -> Write();
    hTof_Kp_fd -> Write();
    hTof_p_fd -> Write();
    hTof_all_fd -> Write();

    cTof_fd -> cd(1);
    hTof_pim_fd -> Draw();
    cTof_fd -> cd(2);
    hTof_Kp_fd -> Draw();
    cTof_fd -> cd(3);
    hTof_p_fd -> Draw();
    cTof_fd -> cd(4);
    hTof_all_fd -> Draw();

    cTof_fd -> Write();

    cTof1_fd -> cd();
    hTof_all_fd -> SetLineColor(1);
    hTof_all_fd -> Draw("same");
    hTof_pim_fd -> SetLineColor(2);
    hTof_pim_fd -> Draw("same");
    hTof_Kp_fd -> SetLineColor(4);
    hTof_Kp_fd -> Draw("same");
    hTof_p_fd -> SetLineColor(8);
    hTof_p_fd -> Draw("same");
    ///////////////////

     //Hades&FwDet ToF
    hTof_pim_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_pim_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_Kp_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_Kp_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_p_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_p_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_all_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_all_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_pim_GeantID -> Write();
    hTof_Kp_GeantID -> Write();
    hTof_p_GeantID -> Write();
    hTof_all_GeantID -> Write();

    cTof_GeantID -> cd(1);
    hTof_pim_GeantID -> Draw();
    cTof_GeantID -> cd(2);
    hTof_Kp_GeantID -> Draw();
    cTof_GeantID -> cd(3);
    hTof_p_GeantID -> Draw();
    cTof_GeantID -> cd(4);
    hTof_all_GeantID -> Draw();

    cTof_GeantID -> Write();

    //Hades Tof
    hTof_pim_h_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_pim_h_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_Kp_h_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_Kp_h_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_p_h_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_p_h_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_all_h_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_all_h_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_pim_h_GeantID -> Write();
    hTof_Kp_h_GeantID -> Write();
    hTof_p_h_GeantID -> Write();
    hTof_all_h_GeantID -> Write();

    cTof_h_GeantID -> cd(1);
    hTof_pim_h_GeantID -> Draw();
    cTof_h_GeantID -> cd(2);
    hTof_Kp_h_GeantID -> Draw();
    cTof_h_GeantID -> cd(3);
    hTof_p_h_GeantID -> Draw();
    cTof_h_GeantID -> cd(4);
    hTof_all_h_GeantID -> Draw();

    cTof_h_GeantID -> Write();

    //FwDet Tof
    hTof_pim_fd_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_pim_fd_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_Kp_fd_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_Kp_fd_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_p_fd_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_p_fd_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_all_fd_GeantID -> GetXaxis() -> SetTitle("tof [ns]");
    hTof_all_fd_GeantID -> GetYaxis() -> SetTitle("counts");
    hTof_pim_fd_GeantID -> Write();
    hTof_Kp_fd_GeantID -> Write();
    hTof_p_fd_GeantID -> Write();
    hTof_all_fd_GeantID -> Write();

    cTof_fd_GeantID -> cd(1);
    hTof_pim_fd_GeantID -> Draw();
    cTof_fd_GeantID -> cd(2);
    hTof_Kp_fd_GeantID -> Draw();
    cTof_fd_GeantID -> cd(3);
    hTof_p_fd_GeantID -> Draw();
    cTof_fd_GeantID -> cd(4);
    hTof_all_fd_GeantID -> Draw();

    cTof_fd_GeantID -> Write();

    cTof1_fd_GeantID -> cd();
    hTof_all_fd_GeantID -> SetLineColor(1);
    hTof_all_fd_GeantID -> Draw("same");
    hTof_pim_fd_GeantID -> SetLineColor(2);
    hTof_pim_fd_GeantID -> Draw("same");
    hTof_Kp_fd_GeantID -> SetLineColor(4);
    hTof_Kp_fd_GeantID -> Draw("same");
    hTof_p_fd_GeantID -> SetLineColor(8);
    hTof_p_fd_GeantID -> Draw("same");
    /////////
       
    l1 -> AddEntry(hTof_pim_fd, "#pi^{-}");
    l1 -> AddEntry(hTof_Kp_fd, "K^{+}");
    l1 -> AddEntry(hTof_p_fd, "p");
    l1 -> AddEntry(hTof_all_fd, "sum");
    l1 -> Draw("same");
    cTof1_fd -> Write();
  //
     //******************
    //PID
    hPpid -> GetXaxis() -> SetTitle("ID");
    hPpid -> Write();
    hVpid -> GetXaxis() -> SetTitle("ID");
    hVpid -> Write();
    hGeantPIDA -> GetXaxis() -> SetTitle("ID");
    hGeantPIDA -> Write();
    hGeantPIDB -> GetXaxis() -> SetTitle("ID");
    hGeantPIDB -> Write();
    hGeantPIDAparent -> GetXaxis() -> SetTitle("ID");
    hGeantPIDAparent -> Write();
    hGeantPIDBparent -> GetXaxis() -> SetTitle("ID");
    hGeantPIDBparent -> Write();
    
    //inv mass spectra
    //Lambda
    hTDpiFD -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpiFD -> GetYaxis() -> SetTitle("counts");
    hTDpiFD -> Write();
    hTDpip -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpip -> GetYaxis() -> SetTitle("counts");
    hTDpip -> Write();

    hTDpiFD_HH -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpiFD_HH -> GetYaxis() -> SetTitle("counts");
    hTDpiFD_HH -> Write();
    hTDpip_HH -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpip_HH -> GetYaxis() -> SetTitle("counts");
    hTDpip_HH -> Write();

    hTDpiFD_HF -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpiFD_HF -> GetYaxis() -> SetTitle("counts");
    hTDpiFD_HF -> Write();
    hTDpip_HF -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpip_HF -> GetYaxis() -> SetTitle("counts");
    hTDpip_HF -> Write();
    
    hVertpiFD -> GetXaxis() -> SetTitle("z [mm]");
    hVertpiFD -> GetYaxis() -> SetTitle("counts");
    hVertpiFD -> Write();
    hVertpip -> GetXaxis() -> SetTitle("z [mm]");
    hVertpip -> GetYaxis() -> SetTitle("counts");
    hVertpip -> Write();
    
    hVertpiFD_HH -> GetXaxis() -> SetTitle("z [mm]");
    hVertpiFD_HH -> GetYaxis() -> SetTitle("counts");
    hVertpiFD_HH -> Write();
    hVertpip_HH -> GetXaxis() -> SetTitle("z [mm]");
    hVertpip_HH -> GetYaxis() -> SetTitle("counts");
    hVertpip_HH -> Write();
    
    hVertpiFD_HF -> GetXaxis() -> SetTitle("z [mm]");
    hVertpiFD_HF -> GetYaxis() -> SetTitle("counts");
    hVertpiFD_HF -> Write();
    hVertpip_HF -> GetXaxis() -> SetTitle("z [mm]");
    hVertpip_HF -> GetYaxis() -> SetTitle("counts");
    hVertpip_HF -> Write();
    
    hMLAll -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLAll -> GetYaxis() -> SetTitle("counts");
    hMLAll -> Write();
    hMLPiHades -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHades -> GetYaxis() -> SetTitle("counts");
    hMLPiHades -> Write(); 
    hMLPiHpF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpF -> GetYaxis() -> SetTitle("counts");
    hMLPiHpF -> Write();
    hrealL -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealL -> GetYaxis() -> SetTitle("counts");
    hrealL -> Write();

    hMLAll_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLAll_HH -> GetYaxis() -> SetTitle("counts");
    hMLAll_HH -> Write();
    hMLPiHades_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHades_HH -> GetYaxis() -> SetTitle("counts");
    hMLPiHades_HH -> Write(); 
    hMLPiHpF_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpF_HH -> GetYaxis() -> SetTitle("counts");
    hMLPiHpF_HH -> Write();
    hrealL_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealL_HH -> GetYaxis() -> SetTitle("counts");
    hrealL_HH -> Write();

    hMLAll_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLAll_HF -> GetYaxis() -> SetTitle("counts");
    hMLAll_HF -> Write();
    hMLPiHades_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHades_HF -> GetYaxis() -> SetTitle("counts");
    hMLPiHades_HF -> Write(); 
    hMLPiHpF_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpF_HF -> GetYaxis() -> SetTitle("counts");
    hMLPiHpF_HF -> Write();
    hrealL_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealL_HF -> GetYaxis() -> SetTitle("counts");
    hrealL_HF -> Write();
    
    hMLPiHadesMTD -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHadesMTD -> GetYaxis() -> SetTitle("counts");
    hMLPiHadesMTD -> Write(); 
    hMLPiHpFMTD -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpFMTD -> GetYaxis() -> SetTitle("counts");
    hMLPiHpFMTD -> Write();
    hrealLMTD -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealLMTD -> GetYaxis() -> SetTitle("counts");
    hrealLMTD -> Write();

    hMLPiHadesMTD_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHadesMTD_HH -> GetYaxis() -> SetTitle("counts");
    hMLPiHadesMTD_HH -> Write(); 
    hMLPiHpFMTD_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpFMTD_HH -> GetYaxis() -> SetTitle("counts");
    hMLPiHpFMTD_HH -> Write();
    hrealLMTD_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealLMTD_HH -> GetYaxis() -> SetTitle("counts");
    hrealLMTD_HH -> Write();

    hMLPiHadesMTD_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHadesMTD_HF -> GetYaxis() -> SetTitle("counts");
    hMLPiHadesMTD_HF -> Write(); 
    hMLPiHpFMTD_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpFMTD_HF -> GetYaxis() -> SetTitle("counts");
    hMLPiHpFMTD_HF -> Write();
    hrealLMTD_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealLMTD_HF -> GetYaxis() -> SetTitle("counts");
    hrealLMTD_HF -> Write();
    
    hMLPiHadesMTDVert -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHadesMTDVert -> GetYaxis() -> SetTitle("counts");
    hMLPiHadesMTDVert -> Write(); 
    hMLPiHpFMTDVert -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpFMTDVert -> GetYaxis() -> SetTitle("counts");
    hMLPiHpFMTDVert -> Write();
    hrealLMTDVert -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealLMTDVert -> GetYaxis() -> SetTitle("counts");
    hrealLMTDVert -> Write();

    hMLPiHadesMTDVert_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHadesMTDVert_HH -> GetYaxis() -> SetTitle("counts");
    hMLPiHadesMTDVert_HH -> Write(); 
    hMLPiHpFMTDVert_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpFMTDVert_HH -> GetYaxis() -> SetTitle("counts");
    hMLPiHpFMTDVert_HH -> Write();
    hrealLMTDVert_HH -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealLMTDVert_HH -> GetYaxis() -> SetTitle("counts");
    hrealLMTDVert_HH -> Write();

    hMLPiHadesMTDVert_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHadesMTDVert_HF -> GetYaxis() -> SetTitle("counts");
    hMLPiHadesMTDVert_HF -> Write(); 
    hMLPiHpFMTDVert_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpFMTDVert_HF -> GetYaxis() -> SetTitle("counts");
    hMLPiHpFMTDVert_HF -> Write();
    hrealLMTDVert_HF -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealLMTDVert_HF -> GetYaxis() -> SetTitle("counts");
    hrealLMTDVert_HF -> Write();
    
    hThetaLcm -> GetXaxis() -> SetTitle("#theta_{CM} [rad]");
    hThetaL -> GetXaxis() -> SetTitle("#theta_{lab} [rad]");
    hMomThetaLcm -> GetXaxis() -> SetTitle("p [Gev/c]");
    hCosThetaLcm -> GetXaxis() -> SetTitle("cos#theta");
    hPhiLcm -> GetXaxis() -> SetTitle("#phi_{cm} [rad]");
    hPhiL -> GetXaxis() -> SetTitle("#phi_{lab} [rad]");
    hMomLcm -> GetXaxis() -> SetTitle("p [Gev/c]");
    hRapLcm -> GetXaxis() -> SetTitle("y []");
//    hPseuRapLcm -> GetXaxis() -> SetTitle("");
    hThetaH1 -> GetXaxis() -> SetTitle("#theta_{lab} [rad]");
    hThetaH2 -> GetXaxis() -> SetTitle("#theta_{lab} [rad]");
    hThetaV -> GetXaxis() -> SetTitle("#theta_{lab} [rad]");
    hThetaX -> GetXaxis() -> SetTitle("#theta_{lab} [rad]");
    hPhiH1 -> GetXaxis() -> SetTitle("#phi_{lab} [rad]");
    hPhiH2 -> GetXaxis() -> SetTitle("#phi_{lab} [rad]");
    hPhiV -> GetXaxis() -> SetTitle("#phi_{lab} [rad]");
    hPhiX -> GetXaxis() -> SetTitle("#phi_{lab} [rad]");
    hThetaH1_cm -> GetXaxis() -> SetTitle("#theta_{cm} [rad]");
    hThetaH2_cm -> GetXaxis() -> SetTitle("#theta_{cm} [rad]");
    hThetaV_cm -> GetXaxis() -> SetTitle("#theta_{cm} [rad]");
    hThetaX_cm -> GetXaxis() -> SetTitle("#theta_{cm} [rad]");
    hPhiH1_cm -> GetXaxis() -> SetTitle("#phi_{cm} [rad]");
    hPhiH2_cm -> GetXaxis() -> SetTitle("#phi_{cm} [rad]");
    hPhiV_cm -> GetXaxis() -> SetTitle("#phi_{cm} [rad]");
    hPhiX_cm -> GetXaxis() -> SetTitle("#phi_{cm} [rad]");

    hThetaLcm -> GetYaxis() -> SetTitle("counts");
    hThetaL -> GetYaxis() -> SetTitle("counts");
    hMomThetaLcm -> GetYaxis() -> SetTitle("#theta_{CM} [rad]");
    hCosThetaLcm -> GetYaxis() -> SetTitle("counts");
    hPhiLcm -> GetYaxis() -> SetTitle("counts");
    hPhiL -> GetYaxis() -> SetTitle("counts");
    hMomLcm -> GetYaxis() -> SetTitle("counts");
    hRapLcm -> GetYaxis() -> SetTitle("counts");
//    hPseuRapLcm -> GetYaxis() -> SetTitle("counts");
    hThetaH1 -> GetYaxis() -> SetTitle("counts");
    hThetaH2 -> GetYaxis() -> SetTitle("counts");
    hThetaV -> GetYaxis() -> SetTitle("counts");
    hThetaX -> GetYaxis() -> SetTitle("counts");
    hPhiH1 -> GetYaxis() -> SetTitle("counts");
    hPhiH2 -> GetYaxis() -> SetTitle("counts");
    hPhiV -> GetYaxis() -> SetTitle("counts");
    hPhiX -> GetYaxis() -> SetTitle("counts");
    hThetaH1_cm -> GetYaxis() -> SetTitle("counts");
    hThetaH2_cm -> GetYaxis() -> SetTitle("counts");
    hThetaV_cm -> GetYaxis() -> SetTitle("counts");
    hThetaX_cm -> GetYaxis() -> SetTitle("counts");
    hPhiH1_cm -> GetYaxis() -> SetTitle("counts");
    hPhiH2_cm -> GetYaxis() -> SetTitle("counts");
    hPhiV_cm -> GetYaxis() -> SetTitle("counts");
    hPhiX_cm -> GetYaxis() -> SetTitle("counts");
    
    hThetaLcm -> Write();
    hThetaL -> Write();
    hMomThetaLcm -> Write();
    hCosThetaLcm -> Write();
    hPhiLcm -> Write();
    hPhiL -> Write();
    hMomLcm -> Write();
    hRapLcm -> Write();
//    hPseuRapLcm -> Write();
    hThetaH1 -> Write();
    hThetaH2 -> Write();
    hThetaV -> Write();
    hThetaX -> Write();
    hPhiH1 -> Write();
    hPhiH2 -> Write();
    hPhiV -> Write();
    hPhiX -> Write();
    hThetaH1_cm -> Write();
    hThetaH2_cm -> Write();
    hThetaV_cm -> Write();
    hThetaX_cm -> Write();
    hPhiH1_cm -> Write();
    hPhiH2_cm -> Write();
    hPhiV_cm -> Write();
    hPhiX_cm -> Write();

    //vert_sim - vert_rec
    hGeantxVertexA -> GetXaxis() -> SetTitle("vertL_sim x [mm]");
    hGeantyVertexA -> GetXaxis() -> SetTitle("vertL_sim y [mm]");
    hGeantzVertexA -> GetXaxis() -> SetTitle("vertL_sim z [mm]");
    hGeantxVertexB -> GetXaxis() -> SetTitle("vertL_sim x [mm]");
    hGeantyVertexB -> GetXaxis() -> SetTitle("vertL_sim y [mm]");
    hGeantzVertexB -> GetXaxis() -> SetTitle("vertL_sim z [mm]");
    hvertex_x -> GetXaxis() -> SetTitle("vertL_reco x [mm]");
    hvertex_y -> GetXaxis() -> SetTitle("vertL_reco y [mm]");
    hvertex_z -> GetXaxis() -> SetTitle("vertL_reco z [mm]");
    hdvertlX -> GetXaxis() -> SetTitle("d(vertL_sim - vertL_rec)x [mm]");
    hdvertlY -> GetXaxis() -> SetTitle("d(vertL_sim - vertL_rec)y [mm]");
    hdvertlZ -> GetXaxis() -> SetTitle("d(vertL_sim - vertL_rec)z [mm]");
    hdvertlR -> GetXaxis() -> SetTitle("d(vertL_sim - vertL_rec)r [mm]");
    hdvertxiX -> GetXaxis() -> SetTitle("d(vertXi_sim - vertXi_rec)x [mm]");
    hdvertxiY -> GetXaxis() -> SetTitle("d(vertXi_sim - vertXi_rec)y [mm]");
    hdvertxiZ -> GetXaxis() -> SetTitle("d(vertXi_sim - vertXi_rec)z [mm]");
    hdvertxiR -> GetXaxis() -> SetTitle("d(vertXi_sim - vertXi_rec)r [mm]");
    hrA -> GetXaxis() -> SetTitle("r_#pi^{-} [mm]");
    hrB -> GetXaxis() -> SetTitle("r_p [mm]");
    hzA -> GetXaxis() -> SetTitle("z_#pi^{-} [mm]");
    hzB -> GetXaxis() -> SetTitle("z_p [mm]");
    hPhiA -> GetXaxis() -> SetTitle("#phi [rad]");
    hPhiB -> GetXaxis() -> SetTitle("#phi [rad]");
    hThetaA -> GetXaxis() -> SetTitle("#theta [rad]");
    hThetaB -> GetXaxis() -> SetTitle("#theta [rad]");
    
    hGeantxVertexA -> GetYaxis() -> SetTitle("counts");
    hGeantyVertexA -> GetYaxis() -> SetTitle("counts");
    hGeantzVertexA -> GetYaxis() -> SetTitle("counts");
    hGeantxVertexB -> GetYaxis() -> SetTitle("counts");
    hGeantyVertexB -> GetYaxis() -> SetTitle("counts");
    hGeantzVertexB -> GetYaxis() -> SetTitle("counts");
    hvertex_x -> GetYaxis() -> SetTitle("counts");
    hvertex_y -> GetYaxis() -> SetTitle("counts");
    hvertex_z -> GetYaxis() -> SetTitle("counts");
    hdvertlX -> GetYaxis() -> SetTitle("counts");
    hdvertlY -> GetYaxis() -> SetTitle("counts");
    hdvertlZ -> GetYaxis() -> SetTitle("counts");
    hdvertlR -> GetYaxis() -> SetTitle("counts");
    hdvertxiX -> GetYaxis() -> SetTitle("counts");
    hdvertxiY -> GetYaxis() -> SetTitle("counts");
    hdvertxiZ -> GetYaxis() -> SetTitle("counts");
    hdvertxiR -> GetYaxis() -> SetTitle("counts");
    hrA -> GetYaxis() -> SetTitle("counts");
    hrB -> GetYaxis() -> SetTitle("counts");
    hzA -> GetYaxis() -> SetTitle("counts");
    hzB -> GetYaxis() -> SetTitle("counts");
    hPhiA -> GetYaxis() -> SetTitle("counts");
    hPhiB -> GetYaxis() -> SetTitle("counts");
    hThetaA -> GetYaxis() -> SetTitle("counts");
    hThetaB -> GetYaxis() -> SetTitle("counts");
    
    hGeantxVertexA -> Write();
    hGeantyVertexA -> Write();
    hGeantzVertexA -> Write();
    hGeantxVertexB -> Write();
    hGeantyVertexB -> Write();
    hGeantzVertexB -> Write();
    hvertex_x -> Write();
    hvertex_y -> Write();
    hvertex_z -> Write();
    hdvertlX -> Write();
    hdvertlY -> Write();
    hdvertlZ -> Write();
    hdvertlR -> Write();
    hdvertxiX -> Write();
    hdvertxiY -> Write();
    hdvertxiZ -> Write();
    hdvertxiR -> Write();
    hrA -> Write();
    hrB -> Write();
    hzA -> Write();
    hzB -> Write();
    hPhiA -> Write();
    hPhiB -> Write();
    hThetaA -> Write();
    hThetaB -> Write();
    
    TCanvas *cdvertl = new TCanvas("cdvertl", "cdvertl");
    cdvertl -> Divide(2,2);
    cdvertl->cd(1);
    hdvertlX -> Draw();
    cdvertl->cd(2);
    hdvertlY -> Draw();
    cdvertl->cd(3);
    hdvertlZ -> Draw();
    cdvertl->cd(4);
    hdvertlR -> Draw();
    cdvertl -> Write();
    TCanvas *cdvertx = new TCanvas("cdvertx", "cdvertx");
    cdvertx -> Divide(2,2);
    cdvertx->cd(1);
    hdvertxiX -> Draw();
    cdvertx->cd(2);
    hdvertxiY -> Draw();
    cdvertx->cd(3);
    hdvertxiZ -> Draw();
    cdvertx->cd(4);
    hdvertxiR -> Draw();
    cdvertx -> Write();

    //mom resolution
    hMomArecox -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    hMomArecoy -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    hMomArecoz -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    hMomAGeax -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    hMomAGeay -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    hMomAGeaz -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    hMomAResx -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    hMomAResy -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    hMomAResz -> GetXaxis() -> SetTitle("p_{#pi^{-}}");
    
    hMomBrecox -> GetXaxis() -> SetTitle("p_{p}");
    hMomBrecoy -> GetXaxis() -> SetTitle("p_{p}");
    hMomBrecoz -> GetXaxis() -> SetTitle("p_{p}");
    hMomBGeax -> GetXaxis() -> SetTitle("p_{p}");
    hMomBGeay -> GetXaxis() -> SetTitle("p_{p}");
    hMomBGeaz -> GetXaxis() -> SetTitle("p_{p}");
    hMomBResx -> GetXaxis() -> SetTitle("p_{p}");
    hMomBResy -> GetXaxis() -> SetTitle("p_{p}");
    hMomBResz -> GetXaxis() -> SetTitle("p_{p}");
    
    hMomArecox -> GetYaxis() -> SetTitle("counts");
    hMomArecoy -> GetYaxis() -> SetTitle("counts");
    hMomArecoz -> GetYaxis() -> SetTitle("counts");
    hMomAGeax -> GetYaxis() -> SetTitle("counts");
    hMomAGeay -> GetYaxis() -> SetTitle("counts");
    hMomAGeaz -> GetYaxis() -> SetTitle("counts");
    hMomAResx -> GetYaxis() -> SetTitle("counts");
    hMomAResy -> GetYaxis() -> SetTitle("counts");
    hMomAResz -> GetYaxis() -> SetTitle("counts");
    
    hMomBrecox -> GetYaxis() -> SetTitle("counts");
    hMomBrecoy -> GetYaxis() -> SetTitle("counts");
    hMomBrecoz -> GetYaxis() -> SetTitle("counts");
    hMomBGeax -> GetYaxis() -> SetTitle("counts");
    hMomBGeay -> GetYaxis() -> SetTitle("counts");
    hMomBGeaz -> GetYaxis() -> SetTitle("counts");
    hMomBResx -> GetYaxis() -> SetTitle("counts");
    hMomBResy -> GetYaxis() -> SetTitle("counts");
    hMomBResz -> GetYaxis() -> SetTitle("counts");
    
    hMomArecox -> Write();
    hMomArecoy -> Write();
    hMomArecoz -> Write();
    hMomAGeax -> Write();
    hMomAGeay -> Write();
    hMomAGeaz -> Write();
    hMomAResx -> Write();
    hMomAResy -> Write();
    hMomAResz -> Write();
    
    hMomBrecox -> Write();
    hMomBrecoy -> Write();
    hMomBrecoz -> Write();
    hMomBGeax -> Write();
    hMomBGeay -> Write();
    hMomBGeaz -> Write();
    hMomBResx -> Write();
    hMomBResy -> Write();
    hMomBResz -> Write();

    //Xi
    hTDpiL -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpiL -> GetYaxis() -> SetTitle("counts");
    hTDpiL -> Write();

    hTDpiL_HH -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpiL_HH -> GetYaxis() -> SetTitle("counts");
    hTDpiL_HH -> Write();

    hTDpiL_HF -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpiL_HF -> GetYaxis() -> SetTitle("counts");
    hTDpiL_HF -> Write();

    hXVertpiL -> GetXaxis() -> SetTitle("z [mm]");
    hXVertpiL -> GetYaxis() -> SetTitle("counts");
    hXVertpiL -> Write();

    hXVertpiL_HH -> GetXaxis() -> SetTitle("z [mm]");
    hXVertpiL_HH -> GetYaxis() -> SetTitle("counts");
    hXVertpiL_HH -> Write();

    hXVertpiL_HF -> GetXaxis() -> SetTitle("z [mm]");
    hXVertpiL_HF -> GetYaxis() -> SetTitle("counts");
    hXVertpiL_HF -> Write();
        
    hMXAll -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXAll -> GetYaxis() -> SetTitle("counts");
    hMXAll -> Write();
    hrealX -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealX -> GetYaxis() -> SetTitle("counts");
    hrealX -> Write();

    hMXAll_HH -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXAll_HH -> GetYaxis() -> SetTitle("counts");
    hMXAll_HH -> Write();
    hrealX_HH -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealX_HH -> GetYaxis() -> SetTitle("counts");
    hrealX_HH -> Write();

    hMXAll_HF -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXAll_HF -> GetYaxis() -> SetTitle("counts");
    hMXAll_HF -> Write();
    hrealX_HF -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealX_HF -> GetYaxis() -> SetTitle("counts");
    hrealX_HF -> Write();

    hMXPiLMTD -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXPiLMTD -> GetYaxis() -> SetTitle("counts");
    hMXPiLMTD -> Write(); 
    hrealXMTD -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealXMTD -> GetYaxis() -> SetTitle("counts");
    hrealXMTD -> Write();
  
    hMXPiLMTD_HH -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXPiLMTD_HH -> GetYaxis() -> SetTitle("counts");
    hMXPiLMTD_HH -> Write(); 
    hrealXMTD_HH -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealXMTD_HH -> GetYaxis() -> SetTitle("counts");
    hrealXMTD_HH -> Write();
  
    hMXPiLMTD_HF -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXPiLMTD_HF -> GetYaxis() -> SetTitle("counts");
    hMXPiLMTD_HF -> Write(); 
    hrealXMTD_HF -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealXMTD_HF -> GetYaxis() -> SetTitle("counts");
    hrealXMTD_HF -> Write();
  
    hMXPiLMTDVert -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXPiLMTDVert -> GetYaxis() -> SetTitle("counts");
    hMXPiLMTDVert -> Write();
    hrealXMTDVert -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealXMTDVert -> GetYaxis() -> SetTitle("counts");
    hrealXMTDVert -> Write();

    hMXPiLMTDVert_HH -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXPiLMTDVert_HH -> GetYaxis() -> SetTitle("counts");
    hMXPiLMTDVert_HH -> Write();
    hrealXMTDVert_HH -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealXMTDVert_HH -> GetYaxis() -> SetTitle("counts");
    hrealXMTDVert_HH -> Write();

    hMXPiLMTDVert_HF -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXPiLMTDVert_HF -> GetYaxis() -> SetTitle("counts");
    hMXPiLMTDVert_HF -> Write();
    hrealXMTDVert_HF -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealXMTDVert_HF -> GetYaxis() -> SetTitle("counts");
    hrealXMTDVert_HF -> Write();

    hstartt -> Write();
    hstopt -> Write();
    hstartx -> Write();
    hstarty -> Write();
    hstartz -> Write();
    hstopx -> Write();
    hstopy -> Write();
    hstopz -> Write();
    hbaseHx -> Write();
    hbaseHy -> Write();
    hbaseHz -> Write();
    hdirHx -> Write();
    hdirHy -> Write();
    hdirHz -> Write();
    hbaseFWx -> Write();
    hbaseFWy -> Write();
    hbaseFWz -> Write();
    hdirFWx -> Write();
    hdirFWy -> Write();
    hdirFWz -> Write();
    /* hdistH -> Write();
    htofH -> Write();
    hdifftofH -> Write();
    hdistFW -> Write();
    hbetaFW -> Write();
    htofFW -> Write();
    hdifftofFW -> Write();
    hmomFW -> Write();
    */
    //*******************
    heventNo -> Write();
    
    output_file->Close();
    cout << "writing root tree done" << endl;
    
    timer.Stop();
    timer.Print();

    return 0;

}
    
