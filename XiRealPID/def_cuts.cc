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

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <TString.h>
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
    char buff[500];
    int pidNo = 0;
    int k = 0;

    //this PID not used now -> use mass2PID()
    for(pidNo; pidNo < partN; pidNo++){
	char cutName[50];
	sprintf(cutName, "CUTG_%02d", pidNo);
	//if(!(TCutG*)fCut -> Get()){
	//    continue;
	//}
	//else{
	if(!(TCutG*)fCut -> Get(cutName)) sprintf(cutName, "CUTG_%02d", 0);
	gCut[k] = (TCutG*)fCut -> Get(cutName) -> Clone();
	cout << "cutName: " << cutName << endl;
	k++;
	//}
    }

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
    int mom21 = -3000000;
    int mom22 = 3000000;
    int bet1 = 0;
    int bet2 = 2;
    int ekin1 = 0;
    int ekin2 = 2000;
    int mas1 = -500;
    int mas2 = 2000;
    int mas21 = -200000;
    int mas22 = 3000000;
    int dex1 = 0;
    int dex2 = 30;
    int tofh1 = 0;
    int tofh2 = 50;
    int toff1 = 15;
    int toff2 = 40;

    int nbins2 = 400;
    int nbins1 = 200; 
    
    //HADES only
    TH2F *hdEdx_h = new TH2F("hdEdx_h", "hdEdx_h", nbins2, mom1, mom2, nbins1, dex1, dex2);
    TH2F *hBeta_h = new TH2F("hBeta_h", "hBeta_h", nbins2, mom1, mom2, nbins1, bet1, bet2);
    TH2F *hEkin_h = new TH2F("hEkin_h", "hEkin_h", nbins2, mom1, mom2, nbins1, ekin1, ekin2);
    TH2F *hM2_h = new TH2F("hM2_h", "hM2_h", nbins2, mom1, mom2 , nbins1, mas1, mas2);
    TH2F *hM22_h = new TH2F("hM22_h", "hM22_h", nbins2, mom1, mom2 , nbins1, mas21, mas22);
    TH1F *hM1_h = new TH1F("hM1_h", "hM1_h", nbins1, mas1, mas2);
    TH1F *hM12_h = new TH1F("hM12_h", "hM12_h", nbins1, mas21, mas22);
//    TH2F *hBeta_q_h = new TH2F("hBeta_q_h", "hBeta_q_h", nbins2, -10, 10, nbins1, bet1, bet2);
    TH2F *hBeta_m_h = new TH2F("hBeta_m_h", "hBeta_h_afterMassPID", nbins2, mom1, mom2, nbins1, bet1, bet2);
    TH2F *hM2_m_h = new TH2F("hM2_m_h", "hM2_m_h", nbins2, mom1, mom2, nbins1, mas1, mas2);
    TH2F *hM22_m_h = new TH2F("hM22_m_h", "hM22_m_h", nbins2, mom1, mom2, nbins1, mas21, mas22);
    TH1F *hM1_m_h = new TH1F("hM1_m_h", "hM1_m_h", nbins1, mas1, mas2);
    TH1F *hM12_m_h = new TH1F("hM12_m_h", "hM12_m_h", nbins1, mas21, mas22);
    TCanvas *cBetaPID_h = new TCanvas("cBetaPID_h", "cBetaPID_h");
    TCanvas *cMassPID_h = new TCanvas("cMassPID_h", "cMassPID_h");
    
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
    TH2F *hBeta_fd = new TH2F("hBeta_fd", "hBeta_fd", 400, -2000, 2000, 200, 0, 1);
    TH2F *hM22_fd = new TH2F("hM22_fd", "hM22_fd", nbins2, mom1, mom2 , nbins1, mas21, mas22);
    TH2F *hdetof_fd = new TH2F("hdetof_fd", "hdetof_fd", nbins2, 0, .1 , nbins1, toff1, toff2);
    
    // TCanvas *cBetaPID_fd = new TCanvas("cBetaPID_fd", "cBetaPID_fd");

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
    TCanvas* cMassLambda=new TCanvas("cMassLambda","Reconstructed lambda mass");
    TH1F* hMLAll=new TH1F("hMLAll","reconstraced mass of all particles combination",imres,immin,immax);
    TH1F* hMLPiHades=new TH1F("hMLPiHades","reconstraced mass of all combinations: pion in HADES",imres,immin,immax);
    TH1F* hMLPiHpF=new TH1F("hMLPiHpF","reconstraced mass of all combinations: pion in HADES, proton in FD",imres,immin,immax);
    TH1F* hrealL=new TH1F("hrealL","reconstraced mass of pion in HADES and proton in FD from #Lambda",imres,immin,immax);
    //MTD_L
    TH1F* hMLPiHadesMTD=new TH1F("hMLPiHadesMTD","reconstraced mass of all combinations: pion in Hades, distance between tracks <x",imres,immin,immax);
    TH1F* hMLPiHpFMTD=new TH1F("hMLPiHpFMTD","reconstraced mass of all combinations: pion in HADES, proton in FD, distance between tracks <x",imres,immin,immax);
    TH1F* hrealLMTD=new TH1F("hrealLMTD","reconstraced mass of pion in HADES and proton in FD from #Lambda, distance between tracks <x",imres,immin,immax);
    //VERTz_L
    TH1F* hMLPiHadesMTDVert=new TH1F("hMLPiHadesMTDVert","reconstraced mass of all combinations: pion in Hades, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    TH1F* hMLPiHpFMTDVert=new TH1F("hMLPiHpFMTDVert","reconstraced mass of all combinations: pion in HADES, proton in FD, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    TH1F* hrealLMTDVert=new TH1F("hrealLMTDVert","reconstraced mass of pion in HADES and proton in FD from #Lambda, distance between tracks <x, Vertz_L in range",imres,immin,immax);
    
    //Xi
    immin=1200;
    immax=1400;
    imres=200;
    //m lambda
    TH1F* hMXAll=new TH1F("hMXAll","Mass reconstructed from Lambda and proton",imres,immin,immax);
    TH1F* hrealX=new TH1F("hrealX","reconstraced mass of pion in HADES from #Xi and real #Lambda",imres,immin,immax);
    //MTD_X
    TH1F* hMXPiLMTD=new TH1F("hMXPiLMTD","Mass reconstructed from Lambda and proton, dist <x",imres,immin,immax);
    TH1F* hrealXMTD=new TH1F("hrealXMTD","reconstraced mass of pion in HADES from #Xi and real #Lambda, dist <x",imres,immin,immax);
    //VERTz_L
    TH1F* hMXPiLMTDVert=new TH1F("hMXPiLMTDVert","Mass reconstructed from Lambda and proton, dist <x, #Xi_{Vert_z}",imres,immin,immax);
    TH1F* hrealXMTDVert=new TH1F("hrealXMTDVert","reconstraced mass of pion in HADES from #Xi and real #Lambda, dist <x, #Xi_{Vert_z}",imres,immin,immax);

    //cuts
    //Dist Lambda
    TH1F* hTDpip=new TH1F("hTDpip","Distance between proton in FD and pion in H; dist[mm]",200,-20,200);
    TH1F* hTDpiFD=new TH1F("hTDpiFD","Distance between anything in FD and pion in H; dist[mm]",200,-20,200);
    //Vertex lambda
    TH1F* hVertpip=new TH1F("hVertpip","Z-coordinate of vertex reconstructed form pion in H and proton in FD", 150,-100,500);
    TH1F* hVertpiFD=new TH1F("hVertpiFD","Z-coordinate of vertex reconstructed from pion in H and anything in GD",150,-100,500);
    //Dist Xi
    TH1F* hTDpiL=new TH1F("hTDpiL","distance between lambda and all pions", 200, -20, 200);
    //Vertex Xi
    TH1F* hXVertpiL=new TH1F("hXVertpiL","Z-coordinate of vertex reconstructed form pion in H and Lambda", 150,-100,500);

    //PID
    TH1D *hPpid = new TH1D("hPpid", "hPpid", 102, -1, 100);
    TH1D *hVpid = new TH1D("hVpid", "hVpid", 102, -1, 100);
    
    //cuts values
    double max_distanceL = 25; // !!
    double max_distanceX = 20; // !!
    double cut_vertex_z_minL = -20; // !!
    double cut_vertex_z_minX = -50; // !!
    double cut_vertex_z_max = 300; // !!
    double massLmin = 1106; // !!
    double massLmax = 1126; //!!

    int eventNo = -1;
    //event loop *************************************************
    //*********************************************************
    for (Int_t i = 0; i < entries; i++)                   
    {
        loop->nextEvent(i);         // get next event. categories will be cleared before
        if(i%5000==0)
	    cout<<"event no. "<<i<<endl;
	HParticleCandSim* particlecand =nullptr;
	HParticleCandSim* ksicand =nullptr;  //candidate for pion to Xi reconstr
	HFwDetCandSim* fwdetstrawvec = nullptr;
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
		
	for(int l=0;l<pcnt;l++)//particle candidates from HADES--------------------------------------------------
	{ 
	    particlecand = HCategoryManager::getObject(particlecand, fCatParticleCandSim,l);
	    if(!particlecand->isFlagBit(kIsUsed)) continue; //only the best tracks
	    
	    float mom_h = particlecand -> getMomentum();
	    float charge_h = particlecand -> getCharge();
	    float dEdx_h = particlecand -> getMdcdEdx();
	    float beta_h = particlecand -> getBeta();
	    //float mass_h = particlecand -> getMass(); //hParticleCandSim
	    //float mass2_h = particlecand -> getMass2(); //hParticleCandSim
	    float mass_h =  mom_h*(TMath::Sqrt((1/beta_h/beta_h)-1)); 
	    float mass2_h = mass_h*mass_h;
	    float ener_h = mass_h*((1/TMath::Sqrt(1-beta_h*beta_h))-1);
	    float pq_h = mom_h*charge_h;
	    float tofRec_h = particlecand -> getTofRec();
	    float tof_h = particlecand -> getTof();

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
	    if(beta_h!=-1 && mass_h > 0)
//		particleID = mass2PID(mass2_h, charge_h); //PID as ranges in m2(pq) spectrum
		particleID = mass2PIDfit(fitpar, mass2_h, charge_h, nPartSpec); //PID as +/-4sigma in m2 spectrum
	    else break;
	    hPpid -> Fill(particleID);
	    
	    particlecand->calc4vectorProperties(HPhysicsConstants::mass(particleID));
	    particleGeantID = particlecand -> getGeantPID();
	    particlecand_parentID = particlecand -> getGeantParentPID();
	    
	    // cout << "tof:" << tof_h << " beta:" << beta << " p:" << mom << " q:" << charge << " mass:" << mass << endl;
	    if(beta_h != -1 && mass_h > 0){
		hdEdx_h -> Fill(pq_h, dEdx_h);
		hBeta_h -> Fill(pq_h, beta_h);
		hEkin_h -> Fill(pq_h, ener_h);
		hM1_h -> Fill(mass_h*charge_h);
		hM12_h -> Fill(mass2_h*charge_h);
		hM2_h -> Fill(pq_h, mass_h);
		hM22_h -> Fill(pq_h, mass2_h);
		if(particleID > 0){
		    hBeta_m_h -> Fill(pq_h, beta_h);
		    hM1_m_h -> Fill(mass_h*charge_h);
		    hM12_m_h -> Fill(mass2_h);
		    hM2_m_h -> Fill(pq_h, mass_h);
		    hM22_m_h -> Fill(pq_h, mass2_h);
		}
		
		if(particlecand -> getSystem() == 1){
		    hdEdx_tof -> Fill(pq_h, dEdx_h);
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
		}

		if(particlecand -> getSystem() == 0){
		    hdEdx_rpc -> Fill(pq_h, dEdx_h);
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

	    for(int j=0; j<vcnt; j++)//vector candidates, FwDetCand loop--------------------------------------------------
	    {
		fwdetstrawvec=HCategoryManager::getObject(fwdetstrawvec, fCatFwDetCandSim, j);
		float tof_v = fwdetstrawvec -> getTof();
		float dE_v = 0; 
		float r_v = 0; 
		
		vectorcandID = tofPID(tof_v);
//		vectorcandID = 14;
		hVpid -> Fill(vectorcandID);
		
		fwdetstrawvec -> calc4vectorProperties(HPhysicsConstants::mass(vectorcandID));
		vectorcandGeantID = fwdetstrawvec -> getGeantPID();
		vectorcand_parentID = fwdetstrawvec -> getGeantParentPID();

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

		if(tof_v != -1){
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
		    }
		}
		if(tof_v != -1){
		    //	cout << "tofRec_v: " << tofRec_v << " tof_v: " << tof_v << endl;
		    hTof_all_fd_GeantID -> Fill(tof_v);
		    hTof_all_GeantID -> Fill(tof_v);
		    if(vectorcandGeantID == 9){
			hTof_pim_fd_GeantID -> Fill(tof_v);
			hTof_pim_GeantID -> Fill(tof_v);
		    }
		    else if(vectorcandGeantID == 11){
			hTof_Kp_fd_GeantID -> Fill(tof_v);
			hTof_Kp_GeantID -> Fill(tof_v);
		    }
		    else if(vectorcandGeantID == 14){
			hTof_p_fd_GeantID -> Fill(tof_v);
			hTof_p_GeantID -> Fill(tof_v);
		    }
		}

		HGeomVector base_H;
		HGeomVector dir_H;
		particle_tool.calcSegVector(particlecand->getZ(),particlecand->getR(),TMath::DegToRad()*particlecand->getPhi(),TMath::DegToRad()*particlecand->getTheta(),base_H,dir_H);
	
		HGeomVector base_FW;
		base_FW.setX(fwdetstrawvec->getPointX());
		base_FW.setY(fwdetstrawvec->getPointY());
		base_FW.setZ(fwdetstrawvec->getPointZ());
		HGeomVector dir_FW;
		dir_FW.setX(fwdetstrawvec->getDirTx());
		dir_FW.setY(fwdetstrawvec->getDirTy());
		dir_FW.setZ(1);//konwencja, tak jest ustawione w fwdetstrawvec

		//*******************
		double distance=particle_tool.calculateMinimumDistance(base_FW,dir_FW,base_H,dir_H);

		HGeomVector vertex;
		vertex=particle_tool.calcVertexAnalytical(base_FW,dir_FW,base_H,dir_H);
		Float_t vertex_x=vertex.X();
		Float_t vertex_z=vertex.Z();
		Float_t vertex_r=TMath::Sqrt(vertex.X()*vertex.X()+vertex.Y()*vertex.Y());

		TLorentzVector sum_mass = *fwdetstrawvec + *particlecand;
		Float_t mass=sum_mass.M();

		hMLAll -> Fill(mass);

		if(particleID == 9){ //pion in HADES, anything in FD
		    //   cout << "H 9" << "mass=" << mass << endl;
		    hMLPiHades -> Fill(mass);
		    hTDpiFD -> Fill(distance);

		    if(vectorcandID == 14){ //pion in HADES, proton in FD
			hMLPiHpF -> Fill(mass);
			hTDpip -> Fill(distance);
			if(particlecand_parentID==18 && vectorcand_parentID==18) //pion and proton from real Lambda
			    hrealL -> Fill(mass);
		    }
		
		    if(distance < max_distanceL){ //MTD_L cut
			//pion in HADES, anything in FD
			hMLPiHadesMTD -> Fill(mass);
			hVertpiFD -> Fill(vertex_z);
			    
			if(vectorcandID == 14){ //pion in HADES, proton in FD
			    hMLPiHpFMTD -> Fill(mass);
			    hVertpip -> Fill(vertex_z);
			    if(particlecand_parentID==18 && vectorcand_parentID==18) //pion and proton from real Lambda
				hrealLMTD -> Fill(mass);
			}
		    
			if(vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max){ //VERTz_L cut
			    //pion in HADES, anything in FD
			    hMLPiHadesMTDVert -> Fill(mass);

			    if(vectorcandID == 14){ //pion in HADES, proton in FD
				hMLPiHpFMTDVert -> Fill(mass);
				if(particlecand_parentID==18 && vectorcand_parentID==18) //pion and proton from	real Lambda
				    hrealLMTDVert -> Fill(mass);
			    }
			}	
		    }
		}
		
		//xxxxxxxxxxxxxxxxxxxxxxxxx
		//Xi reconstruction
		if(mass > massLmin && mass < massLmax && particlecand->isFlagBit(kIsUsed) && particleID == 9 && vectorcandID == 14 && vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max && distance < max_distanceL){
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
		      if(beta_h_Xi!=-1 && mass_h_Xi > 0)
			  ksicandID = mass2PIDfit(fitpar, mass2_h_Xi, charge_h_Xi, nPartSpec);
		      else break;
		      // cout << "ksicandID: " << ksicandID << endl;
		      // cout << "mass2ksicand: " << mass2_h_Xi << endl;
		      // cout << "qksicand: " << charge_h_Xi << endl;
		      hPpid -> Fill(ksicandID+20);
		      
		      if(!ksicandID){
			  cout << "break: invalid ksicandID: " << ksicandID << endl;
		      }

		      ksicand->calc4vectorProperties(HPhysicsConstants::mass(ksicandID));
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
		      double ksiVert = vertex_ksi.Z();
		      
		      if(ksicandID==9){ //particle in Hades is pion
    			  hTDpiL->Fill(distance_ksi);  //dist between L and pi
			  hMXAll->Fill(ksiMass); //mass Xi: MTD_L, VERTzL, mL
			  if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23) //pion and proton from real Lambda
			      hrealX -> Fill(ksiMass);
			                   
			  if(distance_ksi < max_distanceX){
			      hMXPiLMTD -> Fill(ksiMass);
			      hXVertpiL -> Fill(ksiVert);
			      if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23) //pion and proton from real Lambda
				  hrealXMTD -> Fill(ksiMass);
			  			      
			      if(ksiVert > cut_vertex_z_minX && ksiVert < cut_vertex_z_max){
				  hMXPiLMTDVert -> Fill(ksiMass);
				  if(particlecand_parentID==18 && vectorcand_parentID==18 && ksicand_parentID==23) //pion and proton from real Lambda
				      hrealXMTDVert -> Fill(ksiMass);
			      }
			  }
		      }
		    } //end scan for second pion
		} //end Xi reconstruction
	    } //end FD
	} //end HADES

	eventNo = i;
    }//end event loop

    hM12_h = massPID(hM12_h);
    
    output_file->cd();
    gPad -> SetLogz();
    //Hades only
    hdEdx_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hEkin_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hBeta_m_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM1_h -> GetXaxis() -> SetTitle("m [MeV]");
    hM12_h -> GetXaxis() -> SetTitle("m^{2}*q [MeV]");
    hM2_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM22_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM1_m_h -> GetXaxis() -> SetTitle("m*q [MeV]");
    hM2_m_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");
    hM22_m_h -> GetXaxis() -> SetTitle("p*q [MeV/c]");

    hdEdx_h -> GetYaxis() -> SetTitle("dE/dx");
    hBeta_h -> GetYaxis() -> SetTitle("#beta");
    hEkin_h -> GetYaxis() -> SetTitle("E_{kin} [MeV]");
    hBeta_m_h -> GetYaxis() -> SetTitle("#beta");
    hM1_h -> GetYaxis() -> SetTitle("counts");
    hM12_h -> GetYaxis() -> SetTitle("counts");
    hM2_h -> GetYaxis() -> SetTitle("m*q [MeV]");
    hM22_h -> GetYaxis() -> SetTitle("m^{2}*q [(MeV)^{2}]");
    hM1_m_h -> GetYaxis() -> SetTitle("counts");
    hM2_m_h -> GetYaxis() -> SetTitle("m*q [MeV]");
    hM22_m_h -> GetYaxis() -> SetTitle("m^{2}*q [(MeV)^{2}]");
    
    hdEdx_h -> Write();
    hBeta_h -> Write();
    hEkin_h -> Write();
    hBeta_m_h -> Write();
    hM1_h -> Write();
    hM12_h -> Write();
    hM2_h -> Write();
    hM22_h -> Write();
    hM1_m_h -> Write();
    hM12_m_h -> Write();
    hM2_m_h -> Write();
    hM22_m_h -> Write();

    cMassPID_h -> cd();
    hM12_h -> Draw();
    cMassPID_h -> Write();

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
    hdE_fd -> GetXaxis() -> SetTitle("dE in straws [MeV?]");
    hdE_fd -> GetYaxis() -> SetTitle("#");
    hdE_fd -> Write();
    hdetof_fd -> GetXaxis() -> SetTitle("dE in straws [MeV]");
    hdetof_fd -> GetYaxis() -> SetTitle("tof [ns]");
    hdetof_fd -> Write();
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
      
    //inv mass spectra
    //Lambda
    hTDpiFD -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpiFD -> GetYaxis() -> SetTitle("counts");
    hTDpiFD -> Write();
    hTDpip -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpip -> GetYaxis() -> SetTitle("counts");
    hTDpip -> Write();

    hVertpiFD -> GetXaxis() -> SetTitle("z [mm]");
    hVertpiFD -> GetYaxis() -> SetTitle("counts");
    hVertpiFD -> Write();
    hVertpip -> GetXaxis() -> SetTitle("z [mm]");
    hVertpip -> GetYaxis() -> SetTitle("counts");
    hVertpip -> Write();
    
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

    hMLPiHadesMTD -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHadesMTD -> GetYaxis() -> SetTitle("counts");
    hMLPiHadesMTD -> Write(); 
    hMLPiHpFMTD -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpFMTD -> GetYaxis() -> SetTitle("counts");
    hMLPiHpFMTD -> Write();
    hrealLMTD -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealLMTD -> GetYaxis() -> SetTitle("counts");
    hrealLMTD -> Write();

    hMLPiHadesMTDVert -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHadesMTDVert -> GetYaxis() -> SetTitle("counts");
    hMLPiHadesMTDVert -> Write(); 
    hMLPiHpFMTDVert -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hMLPiHpFMTDVert -> GetYaxis() -> SetTitle("counts");
    hMLPiHpFMTDVert -> Write();
    hrealLMTDVert -> GetXaxis() -> SetTitle("m_{p#pi^{-}} [MeV]");
    hrealLMTDVert -> GetYaxis() -> SetTitle("counts");
    hrealLMTDVert -> Write();

    //Xi
    hTDpiL -> GetXaxis() -> SetTitle("dist [mm]");
    hTDpiL -> GetYaxis() -> SetTitle("counts");
    hTDpiL -> Write();
   
    hXVertpiL -> GetXaxis() -> SetTitle("z [mm]");
    hXVertpiL -> GetYaxis() -> SetTitle("counts");
    hXVertpiL -> Write();
        
    hMXAll -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXAll -> GetYaxis() -> SetTitle("counts");
    hMXAll -> Write();
    hrealX -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealX -> GetYaxis() -> SetTitle("counts");
    hrealX -> Write();

    hMXPiLMTD -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXPiLMTD -> GetYaxis() -> SetTitle("counts");
    hMXPiLMTD -> Write(); 
    hrealXMTD -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealXMTD -> GetYaxis() -> SetTitle("counts");
    hrealXMTD -> Write();
  
    hMXPiLMTDVert -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hMXPiLMTDVert -> GetYaxis() -> SetTitle("counts");
    hMXPiLMTDVert -> Write();
    hrealXMTDVert -> GetXaxis() -> SetTitle("m_{#pi^{-}#Lambda} [MeV]");
    hrealXMTDVert -> GetYaxis() -> SetTitle("counts");
    hrealXMTDVert -> Write();
    //*******************
        
    output_file->Close();
    cout << "writing root tree done" << endl;
    
    timer.Stop();
    timer.Print();

    return 0;

}
    
