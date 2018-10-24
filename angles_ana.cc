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
#include <TPaveText.h>

#define PR(x) std::cout << "++DEBUG: " << #x << " = |" << x << "| (" << __FILE__ << ", " << __LINE__ << ")\n";

using namespace std;

bool primary_vertex=false;//should I take into consideration onlu primary particles?
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
    fFwDetStrawCal = HCategoryManager::getCategory(catFwDetStrawCal, kTRUE, "catFwDetStrawCalSim");
    if (!fFwDetStrawCal)
    {
        cout << "No catFwDetStrawCal!" << endl;
        exit(EXIT_FAILURE);  // do you want a brute force exit ?
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
    output_file->cd();
    //
    cout << "NEW ROOT TREE , vertex_ana" << endl;
    //

    TCanvas* cHADES=new TCanvas("cHADES","Info for HADES detector");
    TH1I* hHparticleID=new TH1I("hHparticleID","Particles in HADES ID",30,0,30);
    TH1I* hHADESmultiplicity=new TH1I("hHADESmultiplicity","Tracks Multiplicity in HADES",20,0,20);
    TH1I* hHFwDetmultiplicity=new TH1I("hHFwDetmultiplicity","Tracks multiplicyty inFwDet",20,0,20);
    
    TCanvas* cTrackDistance=new TCanvas("cTrackDistance", "Distances between tracks");
    int nTDscale=150;
    TH1F* hTDAll=new TH1F("hTDAll","Distance for all combination between tracks in HADES and FW",1000,0,nTDscale);
    TH1F* hTDPiProton= new TH1F("hTDPiProton","Distance between protons in FW and Pions in HADES",1000,0,nTDscale);
    TH1F* hTDAllCh2=new TH1F("hTDAllCh2","Distance for all combination between tracks in HADES and FW, Ch2<x",1000,0,nTDscale);
    TH1F* hTDPiProtonCh2= new TH1F("hTDPiProtonCh2","Distance between protons in FW and Pions in HADES, Ch2<x",1000,0,nTDscale);

    TCanvas* cTrackDistanceRes= new TCanvas("cTrackDistanceRes","Z-vertex reconstructed-simulated");
    TH1F* hTDRAll=new TH1F("hTDRall","For all combinations",400,1,-1);
    TH1F* hTDRPiProton=new TH1F("hTDRall","For all combinations of protons and pions",400,1,-1);
    TH1F* hTDRAllCh2=new TH1F("hTDRall","For all combinations of protons and pions, ch2",400,1,-1);
    TH1F* hTDRPiProtonCh2=new TH1F("hTDRPiProtonCh2","For all combinations of protons and pions, ch2",400,1,-1);
     
    TCanvas* cControlPanel=new TCanvas("cControlPanel","Control");
    TH1F* hCPChi2Hades=new TH1F("hCPChi2Hades","Chi2 for Hades particle candidtes",1000,0,100);
    TH1F* hCPChi2FW=new TH1F("hCPChi2FW","Chi2 for FW vector candidtes",1000,0,100);
    TH2F* h2CPtargetPosition=new TH2F("h2CPtargetPosition","Origin point for particles from primaty vertex",100,1,-1,100,1,-1); 
    
    TCanvas* cMassLambda=new TCanvas("cMassLambda","Reconstructed lambda mass");
    int immin=1050;
    int immax=1200;
    int imres=250;
    TH1F* hMLAll=new TH1F("hMLAll","reconstraced mass of all particles combination",imres,immin,immax);
    TH1F* hMLPiHades=new TH1F("hMLPiHades","reconstraced mass of all combination, pion in HADES",imres,immin,immax);
    TH1F* hMLDist=new TH1F("hMLDist","Pion in Hades, distance between tracks <x",imres,immin,immax);
    TH1F* hMLDistSel=new TH1F("hMLDistSel","Pion in Hades, distance between tracks <x, only the best tracks",imres,immin,immax);
    TH1F* hMLDistMass=new TH1F("hMLDistMass","Pion in Hades, distance between tracks <x, Lambda mass in range",imres,immin,immax);
    TH1F* hMLDistMassReal=new TH1F("hMLDistMassReal","Pion in Hades, distance between tracks <x, Lambda mass in range, real Lambda",imres,immin,immax);
    TH1F* hMLDistVert=new TH1F("hMLDistVert","Pion in Hades, distance between tracks <x, #Lambda_{Vert_z}, only the best tracks",imres,immin,immax);
    
    TCanvas* cIntersection=new TCanvas("cIntersection","How many times veccand intersect with particlecand");
    TH1I* hIAll=new TH1I("hIAll","All combinations",10,0,10);
    TH1I* hIPiHades=new TH1I("hIPiHades","Pion in HADES",10,0,10);
    TH1I* hIDist=new TH1I("hIDist","Pion in HADES, distance between tracks <x",10,0,10);
    TH1I* hIDistSel=new TH1I("hIDistSel","Pion in HADES, distance between tracks <x, only the best tracks",10,0,10);

    TCanvas* cKineLambdaRec=new TCanvas("cKineLambdaRec","Lambda reconstraction, ideal identyfication (mother index)");
    TH1F* hKLMass=new TH1F("hKLMass","Lambda mass",imres,immin,immax);
    TH1F* hKLMassDist=new TH1F("hKLMassDist","Lambda mass, distance between tracks <x",imres,immin,immax);
    TH1F* hKLMassDistVert=new TH1F("hKLMassDistVert","Real #Lambda1115, distance between tracks <x, #Lambda_{Vert_z}, only the best tracks",imres,immin,immax);
   
    TH1F* hKLDistance=new TH1F("hKLDistance","Distance measured between tracks from lambda decay",70,0,70);
    TH2F* h2KLVertexZRRec=new TH2F("h2KLVertexZRRec","X-R vertex coordinate reconstructed from detector",750,-250,500,200,0,200);
    TH1F* hKLVertexZRec=new TH1F("hKLVertexZRec","Z-coordinate of vertex reconstructed in detector",350,-200,500);
    TH2F* h2KLVertexZRSim=new TH2F("h2KLVertexZRSim","X-R vertex coordinate, reconstructed from hKine",750,-250,500,200,0,200);
    TH1F* hKLVertexZSim=new TH1F("hKLVertexZSim","Z-coordinate of vertex reconstructed from hKine",350,-200,500);

    TCanvas* cVertexRes= new TCanvas("cVertexRes","Resolution for vertex reconstruction");
    TH1F* hVRradial=new TH1F("hVRradial","Resolution for radial coordinate",200,-50,200);
    TH1F* hVRz=new TH1F("hVRz","Resolution for z coordinate",150,-300,300);
    TH1F* hVRradialSel=new TH1F("hVRradialSel","Resolution for radial coordinate",200,-50,200);
    TH1F* hVRzSel=new TH1F("hVRzSel","Resolution for z coordinate",150,-300,300);

    TH2F* hVertexXZL = new TH2F("hVertexXZL", "Lambda vertex reconstruction", 150, 0, 500, 150, -50, 50);
    TH1F* hVertexXZLproj = new TH1F("hVertexXZLproj", "Lambda vertex_z reconstruction", 150, -100, 500);
    TH2F* hVertexXZX_nocuts = new TH2F("hVertexXZX_nocuts", "Xi vertex reconstruction - no cuts", 150, -100, 500, 150, -50, 50);
    TH1F* hVertexXZXproj_nocuts = new TH1F("hVertexXZXproj_nocuts", "Xi vertex_z reconstruction - no cuts", 150, -100, 500);
    TH2F* hVertexXZX = new TH2F("hVertexXZX", "Xi vertex reconstruction - dist cut", 150, -100, 500, 150, -50, 50);
    TH1F* hVertexXZXproj = new TH1F("hVertexXZXproj", "Xi vertex_z reconstruction - dist cut", 150, -100, 500);
    TH2F* hVertexXZX_vertcut = new TH2F("hVertexXZX_vertcut", "Xi vertex reconstruction - vert cut", 150, -100, 500, 150, -50, 50);
    TH1F* hVertexXZXproj_vertcut = new TH1F("hVertexXZXproj_vertcut", "Xi vertex_z reconstruction - vert cut", 150, -100, 500);
    TH2F* hVertexXZX_distvertcut = new TH2F("hVertexXZX_distvertcut", "Xi vertex reconstruction - dist&vert cut", 150, -100, 500, 150, -50, 50);
    TH1F* hVertexXZXproj_distvertcut = new TH1F("hVertexXZXproj_distvertcut", "Xi vertex_z reconstruction - dist&vert cut", 150, -100, 500);
    
    TH1F* hVertexXZLreal = new TH1F("hVertexXZLreal", "Real #Lambda1115 vertex_z reconstruction", 150, -100, 500);
    TH1F* hVertexXZXreal = new TH1F("hVertexXZXreal", "Real #Xi^{-} vertex_z reconstruction", 150, -100, 500);

    TH1F *hCutMTDLAll[20], *hCutMTDLReal[20];
    char hNameLAllmtd[24], hNameLRealmtd[24];
    for(int i = 0; i < 20; i++){
	sprintf(hNameLAllmtd, "hCutMTDLAll_%d", i);
	hCutMTDLAll[i] = new TH1F(hNameLAllmtd, hNameLAllmtd, imres,immin,immax);
	sprintf(hNameLRealmtd, "hCutMTDLReal_%d", i);
	hCutMTDLReal[i] = new TH1F(hNameLRealmtd, hNameLRealmtd, imres,immin,immax);
    }
    
    TH1F *hCutVertLAll[30], *hCutVertLReal[30];
    char hNameLAll[24], hNameLReal[24];
    for(int i = -10; i < 20; i++){
	sprintf(hNameLAll, "hCutVertLAll_%d", i);
	hCutVertLAll[i+10] = new TH1F(hNameLAll, hNameLAll, imres,immin,immax);
	sprintf(hNameLReal, "hCutVertLReal_%d", i);
	hCutVertLReal[i+10] = new TH1F(hNameLReal, hNameLReal, imres,immin,immax);
    }
    
    TCanvas* cPrimaryKine=new TCanvas("cPrimaryKine","kinematcs of primary particles");
    TH2F* h2PKpion=new TH2F("h2PKpion", "kinematics for Ksi-",500,0,3500,500,0,35);
    TH2F* h2PKkaon=new TH2F("h2PKkaon", "kinematics for kaons",500,0,3500,500,0,35);
    TH2F* h2PKproton=new TH2F("h2PKproton", "kinematics for protons",500,0,3500,1000,0,70); 
    TH2F* h2PKall=new TH2F("h2PKHall", "kinematics for all particles from primary vertex",500,0,3500,500,0,35);
    TH2F* h2PKpionpion=new TH2F("h2PKpionpion","kinematics for pion",500,0,3500,500,0,90);

    immin=1200;
    immax=1400;
    imres=200;
    TCanvas* cKsi=new TCanvas("cKsi","Ksi- measurment");
    TH1F* hKmassall=new TH1F("hKmassall","Mass reconstructed from lambda and pion",imres,immin,immax);
    TH1F* hKmassRX=new TH1F("hKmassRX","Mass reconstructed from real lambda and pion from Xi",imres,immin,immax);
    TH1F* hKmassRXDist=new TH1F("hKmassRXDist","Mass reconstructed from real lambda and pion from Xi, dist<x",imres,immin,immax);
    TH1F* hKmassRLpion=new TH1F("hKmassRLpion","Mass reconstructed from real lambda and some pion",imres,immin,immax);
    TH1F* hKdistanceall=new TH1F("hKdistanceall","distance between lambda and all pions", 200, -20, 200);
    TH1F* hKdistanceRealXi=new TH1F("hKdistanceRealXi","distance between lambda and pion from Xi", 200, -20, 200);
    TH1F* hKmassdist=new TH1F("hKmassdist","Mass reconstructed from lambda and pion, dist <x",imres,immin,immax);
    TH1F* hKmassdistVert=new TH1F("hKmassdistVert","Mass reconstructed from lambda and pion, dist <x, #Xi_{Vert_z}",imres,immin,immax);
    TH1F* hKmassRXDistVert=new TH1F("hKmassRXDistVert","Mass reconstructed from real lambda and pion from Xi, dist <x, #Xi_{Vert_z}",imres,immin,immax);
    
    TH1F* hKvertexAll=new TH1F("hKvertexAll","Distance between ksi and lambda vertex - no cuts, all cand",250,-100,300);
    TH1F* hKvertexReal=new TH1F("hKvertexReal","Distance between ksi and lambda vertex - no cuts, real Xi and Lambda",250,-100,300);
    TH1F* hKvertexdistAll=new TH1F("hKvertexdistAll","Distance between ksi and lambda vertex - dist cut, all cand",250,-100,300);
    TH1F* hKvertexdistReal=new TH1F("hKvertexdistReal","Distance between ksi and lambda vertex - dist cut, real Xi and Lambda",250,-100,300);
    TH1F* hKtofproperties=new TH1F("hKtofproperties","value of fTofRec for events from ksi peak",5,0,5);
    TH1F* hKtofHitInd=new TH1F("hKtofHitInd","value of fTofHitInd for events from ksi peak",10,1,-1);
    TH1I* hKpeakID=new TH1I("hKpeakID","counter how many real Ksis are in peak",4,0,4);
    
    TCanvas* cParticlesDiff=new TCanvas("cParticlesDiff","Differences between particles properies in dacay chain");
    TH1F* hPDthetaKsiLambda=new TH1F("hPDthetaKsiLambda","theta Ksi - theta Lambda",600,-1.2,0.2);
    TH1F* hPDphiKsiLambda=new TH1F("hPDphiKsiLambda","phi Ksi - phi Lambda",400,-8,8);
    TH1F* hPDgamma=new TH1F("hPDgamma","angle between lambda and ksi track",500,1,-1);

    TCanvas* cEff=new TCanvas("cEff","Detection efficiency for different particles");
    TH1F* hEprotons4Pi=new TH1F("hEprotons4Pi","Protons from kine; theta",180,0,180);
    TH1F* hEprotonsdet=new TH1F("hEprotonsdet","Protons registered in detector; theta",180,0,180);
    TH1F* hEprotonsEff=new TH1F("hEprotonsEff","Detection efficiency; theta;efficiency",180,0,180);
    TH1F* hEpions4Pi=new TH1F("hEpions4Pi","Pions from kine; theta",180,0,180);
    TH1F* hEpionsdet=new TH1F("hEpionsdet","Pions registered in detector; theta",180,0,180);
    TH1F* hEprotondetL=new TH1F("hEprotondetL","Protons from Lambda registered in detector; theta",180,0,180);
    TH1F* hEpionsEff=new TH1F("hEpionsEff","Detection efficiency; theta;efficiency",180,0,180);
    TH1F* hEleptons4Pi=new TH1F("hEleptons4Pi","Leptons from kine; theta",180,0,180);
    TH1F* hEleptonsdet=new TH1F("hEleptonsdet","Leptons registered in detector; theta",180,0,180);
    TH2F* h2Eproton4Pi=new TH2F("h2Eproton4Pi","Proton emitted in 4Pi; phi; theta",100,0,360,50,0,180);
    TH2F* h2Eprotondet=new TH2F("h2Eprotondet","Proton detected in 4Pi; phi; theta",100,0,360,50,0,180);
    TH2F* h2EprotonEff=new TH2F("h2EprotonEff","Proton efficiency in 4Pi; phi; theta",100,0,360,50,0,180);
    TH2F* h2Epion4Pi=new TH2F("h2Epion4Pi","Pion emitted in 4Pi; phi; theta",100,0,360,50,0,180);
    TH2F* h2Epiondet=new TH2F("h2Epiondet","Pion detected in 4Pi; phi; theta",100,0,360,50,0,180);
    TH2F* h2EpionEff=new TH2F("h2EpionEff","Pion efficiency in 4Pi; phi; theta",100,0,360,50,0,180);

    TCanvas* cCounter=new TCanvas("cCounter","Counter for particles");
    TH1F* hCgen=new TH1F("hCgen","Partiles generated in simulation",30,0,30);
    TH1F* hCdet=new TH1F("hCdet","Partiles detected in simulation",30,0,30);
    TH1F* hCLambdaGen=new TH1F("hCLambdaGen","Partiles from Lambda generated",30,0,30);
    TH1F* hCLambdaDet=new TH1F("hCLambdaDet","Partiles from Lambda detected",30,0,30);
    TH1F* hCXsiGen=new TH1F("hCXsiGen","Partiles from Xsi generated",30,0,30);
    TH1F* hCXsiDet=new TH1F("hCXsiDet","Partiles from Xsi detected",30,0,30);

    TCanvas* cPionDist=new TCanvas("cPionDist","distance beween pions and particles");
    TH1F* hPDpionproton=new TH1F("hPDpionproton","Distance between proton and pion for all combinations; dist[mm]",200,-20,200);
    TH1F* hPDlambda=new TH1F("hPDlambda","Distance between proton and pion from Lambda decay; dist[mm]",200,-20,200);

    TH1I* hHmoduls=new TH1I("hHmoduls","how many moduls for track was used",5,0,5); 
    TH1I* hHNDetector=new TH1I("hHNDetector","value of getNDetector for pions from Xi peak",100,1,100);
    TH1F* hKmassvert=new TH1F("hKmassvert","Mass reconstructed from lambda and pion --- vertex cut",imres,immin,immax);
    TH1F* hKmassdistvert=new TH1F("hKmassdistvert","Mass reconstructed from lambda and pion --- dist & vertex cut",imres,immin,immax);
    
    TH1F* hKvertexvert=new TH1F("hKvertexvert","Distance between ksi and lambda vertex - vert cut",250,-100,300);
    TH1F* hKvertexdistvert=new TH1F("hKvertexdistvert","Distance between ksi and lambda vertex - dist&vert cut",250,-100,300);

    TH1F *hCutMTDXAll[20], *hCutMTDXReal[20];
    char hNameXAllmtd[24], hNameXRealmtd[24];
    for(int i = 0; i < 20; i++){
	sprintf(hNameXAllmtd, "hCutMTDXAll_%d", i);
	hCutMTDXAll[i] = new TH1F(hNameXAllmtd, hNameXAllmtd, imres,immin,immax);
	sprintf(hNameXRealmtd, "hCutMTDXReal_%d", i);
	hCutMTDXReal[i] = new TH1F(hNameXRealmtd, hNameXRealmtd, imres,immin,immax);
    }
    
    
    TH1F *hCutVertAll[30], *hCutVertReal[30];
    char hNameAll[24], hNameReal[24];
    for(int i = -10; i < 20; i++){
	sprintf(hNameAll, "hCutVertAll_%d", i);
	hCutVertAll[i+10] = new TH1F(hNameAll, hNameAll, imres,immin,immax);
	sprintf(hNameReal, "hCutVertReal_%d", i);
	hCutVertReal[i+10] = new TH1F(hNameReal, hNameReal, imres,immin,immax);
    }
    
    TCanvas* cVertexResInZ=new TCanvas("cVertexResInZ","Resolution along Z in function of Z");
    TH1F* hVRIZ [7];
    TF1* fVRIZgaus[7];
    TGraphErrors* gVRIZ=new TGraphErrors(7);
    for(int i=0; i<7;i++)
      {
	ostringstream hname;
	hname << "resolution_in_h_" << i;
	ostringstream gname;
	gname << "gaus_no_" << i;
	hVRIZ[i]=new TH1F(hname.str().c_str(),hname.str().c_str(),100,-300,300);
	fVRIZgaus[i]=new TF1(gname.str().c_str(),"gaus",-300,300);
      }


    
    //event loop *************************************************
    //*********************************************************
    for (Int_t i = 0; i < entries; i++)                   
    {
        loop->nextEvent(i);         // get next event. categories will be cleared before
        if(i%5000==0)
	  cout<<"event no. "<<i<<endl;
        HParticleCandSim* particlecand =nullptr;
	HParticleCandSim* ksicand =nullptr;
	HFwDetCandSim* fwdetstrawvec = nullptr;
	HGeantKine* hkine=nullptr;
	HGeantKine* hkine2=nullptr;
	HGeantKine* hkineparent=nullptr;
	HParticleTool particle_tool;
 	//vector candidate reconstraction
	Int_t vcnt=fCatFwDetCandSim->getEntries();
	Int_t pcnt=fCatParticleCandSim->getEntries();
	Int_t gknt=fCatGeantKine->getEntries();
	Double_t tof;
	//cout<<gknt<<endl;
	

	//All prticles from kine
	//**********************************************************
	for(int k=0; k<gknt; k++)//find particle ID
	  {
	    hkine = HCategoryManager::getObject(hkine, fCatGeantKine,k);
	    int vectorcand_creationID=hkine->getMechanism();
	    int particleID=hkine->getID();
	    // hkineparent=hkine->getParent();
	    int particleparentTID=hkine->getParentTrack();
	    int particleparentID=0;
	    //find parent ID
	    for(int z=0;z<gknt;z++)
	      {
		hkineparent=HCategoryManager::getObject(hkineparent,fCatGeantKine,z);
		if(hkineparent->getTrack()==particleparentTID)
		  particleparentID=hkineparent->getID();
	      }
	    Float_t v_x;
	    Float_t v_y;
	    Float_t v_z;
	    HGeomVector mom;
	    hkine->getVertex(v_x,v_y,v_z);
	    hkine->getMomentum(mom);
	    hCgen->Fill(particleID);
	    if(vectorcand_creationID==0)//particles from primary vertex
	      {
		h2PKall->Fill(mom.length(),hkine->getThetaDeg());
		h2CPtargetPosition->Fill(v_z,TMath::Sqrt(v_x*v_x+v_y*v_y));
		if(particleID==14)//proton
		  {
		  h2PKproton->Fill(mom.length(),hkine->getThetaDeg());
		  hEprotons4Pi->Fill(hkine->getThetaDeg());
		  }
		if(particleID==23)//Ksi-
		  h2PKpion->Fill(mom.length(),hkine->getThetaDeg());
		if(particleID==11)//K+
		  h2PKkaon->Fill(mom.length(),hkine->getThetaDeg());
	      }
	    if(particleID==9 && (particleparentID==23 || particleparentID==18))//pion from lambda and ksi
	      {
		h2PKpionpion->Fill(mom.length(),hkine->getThetaDeg());
		hEpions4Pi->Fill(hkine->getThetaDeg());
	      }
	    if(particleID==14 && particleparentID==18)//proton from lambda
	      {
		hEprotons4Pi->Fill(hkine->getThetaDeg());
		h2PKproton->Fill(mom.length(),hkine->getThetaDeg());
	      }
	    
	    if(particleID==23)//ksi
	      for(int l=0; l<gknt; l++)
		{
		  hkine2=HCategoryManager::getObject(hkine2, fCatGeantKine,l);
		  int particleID2=hkine2->getID();
		  if(particleID2==18)//lambda
		    {
		      double phi1=hkine->getPhiDeg()*TMath::DegToRad();
		      double phi2=hkine2->getPhiDeg()*TMath::DegToRad();
		      double theta1=hkine->getThetaDeg()*TMath::DegToRad();
		      double theta2=hkine2->getThetaDeg()*TMath::DegToRad();
		      hPDphiKsiLambda->Fill(phi1-phi2);
		      hPDthetaKsiLambda->Fill(theta1-theta2);
		      double gamma=TMath::Cos(phi1+phi2)*TMath::Abs(TMath::Sin(theta1)*TMath::Sin(theta2))+TMath::Cos(theta1)*TMath::Cos(theta2);
		      hPDgamma->Fill(TMath::ACos(gamma));
		    }
		}
	    if(particleparentID==18)
	      hCLambdaGen->Fill(particleID);
	    if(particleparentID==23)
	      hCXsiGen->Fill(particleID);
	  }
	//********************************************************* 
	//end kine
	
	hHADESmultiplicity->Fill(pcnt);
	hHFwDetmultiplicity->Fill(vcnt);

	//all possible tracks' combinations from HADES and FW
	
	for(int j=0; j<vcnt; j++)//vector candidates, FwDetCand loop
	  {
	    fwdetstrawvec=HCategoryManager::getObject(fwdetstrawvec, fCatFwDetCandSim, j);
	    Int_t vectorcandID=-1;
	    Int_t vectorcandTID=fwdetstrawvec->getGeantTrack();
	    Int_t vectorcandparentTID=-1;
	    Int_t vectorcandparentID=-1;
	    Int_t vectorcand_creationID=-1;
	    //intersection counters
	    Int_t nInsertAll=0;
	    Int_t nInsertPion=0;
	    Int_t nInsertDistance=0;
	    Int_t nInsertDistanceSel=0;
	    	    
	    /* for(int k=0; k<gknt; k++)//find particle ID
	      {
		hkine = HCategoryManager::getObject(hkine, fCatGeantKine,k);
		vectorcand_creationID=hkine->getMechanism();
		vectorcandparentTID=hkine->getParentTrack();
		Float_t v_x;
		Float_t v_y;
		Float_t v_z;
		hkine->getVertex(v_x,v_y,v_z);
		if(vectorcandTID==hkine->getTrack())
		  {
		    vectorcandID=hkine->getID();
		    vectorcandparentTID=hkine->getParentTrack();
		    break;
		  }		
		  }*/
	    vectorcandID = fwdetstrawvec -> getGeantPID();
	    vectorcandparentTID = fwdetstrawvec -> getGeantParentTrackNum();
	    hCdet->Fill(vectorcandID);
	    
	    for(int k=0; k<gknt; k++)//find particle parent ID
	      {
		hkine = HCategoryManager::getObject(hkine, fCatGeantKine,k);
		if(vectorcandparentTID==hkine->getTrack())
		  {
		    vectorcandparentID=hkine->getID();
		    break;
		  }
	      }
	    	    
	    if(primary_vertex)//by defoult no!
	      if(vectorcand_creationID!=0)//skip all particles different then from elementary reaction
		continue;

	    tof = fwdetstrawvec -> getTofRec();
	    if(tof == 0.0)
		fwdetstrawvec -> setTofRec(-1);

	   		
	    // if(tof == 0)
	    //	    cout << " #tof: " << tof << endl;
	    //if(tof == 0)
	    //	continue;
	    
	    hCPChi2FW->Fill(fwdetstrawvec->getChi2());
	    if(vectorcandID==14 && (vectorcandparentID==18 || vectorcand_creationID==0))//protons in FwDet
	      {
		fwdetstrawvec->calc4vectorProperties(938);
		hEprotonsdet->Fill(fwdetstrawvec->Theta()*180/TMath::Pi());
	      }
	    if(vectorcandID==14 && vectorcandparentID==18)//protons from lambda
	      {
		hCLambdaDet->Fill(hkine->getID());
		hEprotondetL->Fill(fwdetstrawvec->Theta()*180/TMath::Pi());
	      }
	    
	    
	    for(int i=0;i<pcnt;i++)//particle candidates from HADES--------------------------------------------------
	      {
		particlecand = HCategoryManager::getObject(particlecand, fCatParticleCandSim,i);
		
		Int_t hades_ID=particlecand->getGeantPID();
		Int_t particlecand_creationID=particlecand->getGeantParentTrackNum();
		//Int_t particlecandTID=particlecand->getGeantTrack();
		Int_t particlecand_parentID=particlecand->getGeantParentPID();
		Int_t particlecand_geanttrack=particlecand->getGeantTrack();
		double max_distanceL = 25; // !!
		double max_distanceX = 20; // !!
		double cut_vertex_z_minL = 0; // !!
		double cut_vertex_z_minX = -50; // !!
		double cut_vertex_z_max = 300; // !!
		double cutVert;

		hHparticleID->Fill(hades_ID);
		
		if(primary_vertex)
		  if(particlecand_creationID!=0)//skip all particles different then from elementary reaction
		    continue;
		hCPChi2Hades->Fill(particlecand->getChi2());

		
		HGeomVector particlecandVertexKine;
		particlecandVertexKine.setX(particlecand->getGeantxVertex());
		particlecandVertexKine.setY(particlecand->getGeantyVertex());
		particlecandVertexKine.setZ(particlecand->getGeantzVertex());
		
		HGeomVector base_FW;
		base_FW.setX(fwdetstrawvec->getPointX());
		base_FW.setY(fwdetstrawvec->getPointY());
		base_FW.setZ(fwdetstrawvec->getPointZ());
		HGeomVector dir_FW;
		dir_FW.setX(fwdetstrawvec->getDirTx());
		dir_FW.setY(fwdetstrawvec->getDirTy());
		dir_FW.setZ(1);//konwencja, tak jest ustawione w fwdetstrawvec
		
		HGeomVector base_H;
		HGeomVector dir_H;
		particle_tool.calcSegVector(particlecand->getZ(),particlecand->getR(),TMath::DegToRad()*particlecand->getPhi(),TMath::DegToRad()*particlecand->getTheta(),base_H,dir_H);
		
		double distance=particle_tool.calculateMinimumDistance(base_FW,dir_FW,base_H,dir_H);
		hTDAll->Fill(distance);
		
		HGeomVector vertex;
		vertex=particle_tool.calcVertexAnalytical(base_FW,dir_FW,base_H,dir_H);
		Float_t vertex_x=vertex.X();
		Float_t vertex_z=vertex.Z();
		Float_t vertex_r=TMath::Sqrt(vertex.X()*vertex.X()+vertex.Y()*vertex.Y());
		Float_t vertex_z_sim=particlecand->getGeantzVertex();
		Float_t vertex_r_sim=TMath::Sqrt(particlecand->getGeantxVertex()*particlecand->getGeantxVertex()+particlecand->getGeantyVertex()*particlecand->getGeantyVertex());
		  
		fwdetstrawvec->calc4vectorProperties(938);
		particlecand->calc4vectorProperties(HPhysicsConstants::mass(hades_ID));
		TLorentzVector sum_mass = *fwdetstrawvec + *particlecand;
		Float_t mass=sum_mass.M();

		hTDRAll->Fill(vertex_z_sim-vertex_z);
		hMLAll->Fill(mass);
		//if(tof == 0)
		//  cout << " #bad tof: " << tof << endl;
		nInsertAll++;//increase number of intersections
		// if(mass > 1715 && mass < 1740){
		//     particlecand -> print();
		//     fwdetstrawvec -> print();
		// }
		
		if(vectorcandID==14 && hades_ID==9)//Pion in Hades, proton in FW
		  {
		    hTDPiProton->Fill(distance);
		    hTDRPiProton->Fill(vertex_z_sim-vertex_z);
		  }
		if(particlecand->isFlagBit(kIsUsed) && hades_ID==9)//pion in HADES, everything in FwDet
		  {
		      for(int d = 0; d < 20; d++){
			  if(distance < (d*5)+5)
			      hCutMTDLAll[d] -> Fill(mass);
		      }
		      		      
		    hMLPiHades->Fill(mass);
		    hPDpionproton->Fill(distance);
		    nInsertPion++;
		  }
		if(distance<max_distanceL && hades_ID==9)//pion in HADES, everything in FwDet, for close tracks
		{
		    hMLDist->Fill(mass);
		    nInsertDistance++;
		  }
		
		if(particlecand->isFlagBit(kIsUsed) && distance<max_distanceL)//only the best tracks from HADES
		  {
		      hTDAllCh2->Fill(distance);
		      hTDRAllCh2->Fill(vertex_z_sim-vertex_z);
		      if(vectorcandID==14 && hades_ID ==9)
		      {
			  hTDPiProtonCh2->Fill(distance);
			  hTDRPiProtonCh2->Fill(vertex_z_sim-vertex_z);
		      }
		      if(hades_ID==9)
		      {
			  hMLDistSel->Fill(mass);
			  nInsertDistanceSel++;
			  hVRradialSel->Fill(-(vertex_r_sim-vertex_r));
			  hVRzSel->Fill(-(vertex_z_sim-vertex_z));

			  if(vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max)
			      hMLDistVert -> Fill(mass);

			  for(int v = -10; v < 20; v++){
			      if(vertex_z > v*10 && vertex_z < cut_vertex_z_max)
				  hCutVertLAll[v+10] -> Fill(mass);
			  }

			  if(mass>1105 && mass<1125){
			      hVertexXZL -> Fill(vertex_z, vertex_x);
			      hVertexXZLproj -> Fill(vertex_z);
			  }

		      }
		  }
		
		if(particlecand_parentID==18 && vectorcandparentID==18 && particlecand->isFlagBit(kIsUsed))//particles from lambda vertex
		{
		    for(int d = 0; d < 20; d++){
			if(distance < (d*5)+5)
			    hCutMTDLReal[d] -> Fill(mass);
		    }
		      
		    hKLDistance->Fill(distance);
		    hPDlambda->Fill(distance);
		    hKLMass->Fill(mass);

		    if(distance<max_distanceL){ 
			hKLMassDist -> Fill(mass);
			if(vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max)
			    hKLMassDistVert -> Fill(mass);
			
			for(int v = -10; v < 20; v++){
			    if(vertex_z > v*10 && vertex_z < cut_vertex_z_max)
				hCutVertLReal[v+10] -> Fill(mass);
			}
			
			if(mass>1105 && mass<1125){
			    hVertexXZLreal -> Fill(vertex_z);
			}

		    }
		    hKLVertexZRec->Fill(vertex_z);
		    hKLVertexZSim->Fill(vertex_z_sim);

		    h2KLVertexZRRec->Fill(vertex_z,vertex_r);
		    h2KLVertexZRSim->Fill(vertex_z_sim, vertex_r_sim);

		    hVRz->Fill(-(vertex_z_sim-vertex_z));
		    hVRradial->Fill(-(vertex_r_sim-vertex_r));
		    for(int d=0; d<7;d++)
		      {
			if(vertex_z_sim<-50+(d+1)*50)
			  {
			    hVRIZ[d]->Fill(-(vertex_z_sim-vertex_z));
			  break;
			  }
		      }
		  }
	      
		//Xi reconstruction
		//****************
		if(mass>1106 && mass<1126 && particlecand->isFlagBit(kIsUsed) && hades_ID==9 && vertex_z > cut_vertex_z_minL && vertex_z < cut_vertex_z_max && distance<max_distanceL)
		{
		  hMLDistMass -> Fill(mass);
		  if(particlecand_parentID==18 && vectorcandparentID==18) //real Lambda and pion
		      hMLDistMassReal -> Fill(mass);
		  
		  for(int f=0;f<pcnt;f++)//scan all particles detected in HADES except Pion used for Lambda reconstraction
		    {
		      if(f==i)
			continue;//skip pion from lambda decay

		      ksicand = HCategoryManager::getObject(ksicand, fCatParticleCandSim,f);
		      Int_t ksi_ID=ksicand->getGeantPID();
		      Int_t ksi_parentID=ksicand->getGeantParentPID();
		      Int_t ksi_geanttrack=ksicand->getGeantTrack();
		      if(ksi_ID==9)//particle in Hades is pion
			{
			  ksicand->calc4vectorProperties(HPhysicsConstants::mass(hades_ID));
			  HGeomVector base_pion;
			  HGeomVector dir_pion;
			  particle_tool.calcSegVector(ksicand->getZ(),ksicand->getR(),TMath::DegToRad()*ksicand->getPhi(),TMath::DegToRad()*ksicand->getTheta(),base_pion,dir_pion);
			  HGeomVector base_lambda=vertex;
			  HGeomVector dir_lambda(sum_mass.X(),sum_mass.Y(),sum_mass.Z());
			  //calculate distance between pion and lambda
			  double distance_ksi=particle_tool.calculateMinimumDistance(base_lambda,dir_lambda,base_pion,dir_pion);			  
			  TLorentzVector ksiVector=sum_mass+*ksicand;
			  hKdistanceall->Fill(distance_ksi);
			  hKmassall->Fill(ksiVector.M());

			  //get informations about hits from kine
			  int particlecand_nhits[6];
			  int ksi_nhits[6];
			  int particlecand_moduls=0;
			  int ksi_modules=0;

			  //not importatnt************************************
			  for(int k=0; k<gknt; k++)
			    {
			      hkine = HCategoryManager::getObject(hkine, fCatGeantKine,k);
			      if(ksi_geanttrack==hkine->getTrack())
				{
				  hkine->getNHitsDecayBit(ksi_nhits[0],ksi_nhits[1],ksi_nhits[2],ksi_nhits[3],ksi_nhits[4],ksi_nhits[5]);
				}
			      if(particlecand_geanttrack==hkine->getTrack())
				{
				  hkine->getNHitsDecayBit(particlecand_nhits[0],particlecand_nhits[1],particlecand_nhits[2],particlecand_nhits[3],particlecand_nhits[4],particlecand_nhits[5]);
				}
			    }
			  
			  for(int s=0;s<4;s++)
			    {
			      //cout<<ksi_nhits[s]<<" ";
			      //if(s==3)
			      //cout<<endl;
			      if(particlecand_nhits[s]>0)
				particlecand_moduls++;
			      if(ksi_nhits[s]>0)
				ksi_modules++;
			    }
			  //end of information about hits
			  //end of not important part **********************

			  HGeomVector vertex_ksi;
			  vertex_ksi=particle_tool.calcVertexAnalytical(base_lambda,dir_lambda,base_pion,dir_pion);
			  hVertexXZX_nocuts -> Fill(vertex_ksi.Z(), vertex_ksi.X());
			  hVertexXZXproj_nocuts -> Fill(vertex_ksi.Z());

			  if(particlecand_parentID==18 && vectorcandparentID==18){ //real Lambda and pion
			      hKmassRLpion -> Fill(ksiVector.M());
			  }
			  
			  if(particlecand_parentID==18 && vectorcandparentID==18 && ksi_parentID==23 && ksicand->isFlagBit(kIsUsed)){ //real Xi -- Lambda and pion from Xi
			      for(int d = 0; d < 20; d++){
				  if(distance_ksi < (d*5)+5)
				      hCutMTDXReal[d] -> Fill(ksiVector.M());
			      }
			      			      
			      hKdistanceRealXi -> Fill(distance_ksi);
			      hKmassRX -> Fill(ksiVector.M());
			      hKvertexReal->Fill((vertex-vertex_ksi).length());
			  }

			  if(ksicand->isFlagBit(kIsUsed)){
			      for(int d = 0; d < 20; d++){
				  if(distance_ksi < (d*5)+5)
				      hCutMTDXAll[d] -> Fill(ksiVector.M());
			      }
			      hKvertexAll->Fill((vertex-vertex_ksi).length());
			  }
			  			  
			  if(distance_ksi<max_distanceX && ksicand->isFlagBit(kIsUsed)) //cut on dist Lambda - pim
			    {
			      hKmassdist->Fill(ksiVector.M());
//			      HGeomVector vertex_ksi;
//			      vertex_ksi=particle_tool.calcVertexAnalytical(base_lambda,dir_lambda,base_pion,dir_pion);
			      hKvertexdistAll->Fill((vertex-vertex_ksi).length());//*TMath::Sign(1.0,vertex.Z()-vertex_ksi.Z()));//distance between vertexes multyply by order of them (+ or -)
			      hKtofproperties->Fill(ksicand->getTofRec());
			      hKtofproperties->Fill(particlecand->getTofRec());
			      hKtofHitInd->Fill(ksicand->getTofHitInd());
			      hKtofHitInd->Fill(particlecand->getTofHitInd());

			      hVertexXZX -> Fill(vertex_ksi.Z(), vertex_ksi.X());
			      hVertexXZXproj -> Fill(vertex_ksi.Z());

			      if(vertex_ksi.Z() > cut_vertex_z_minX && vertex_ksi.Z() < cut_vertex_z_max)
				  hKmassdistVert -> Fill(ksiVector.M());

			      for(int v = -10; v < 20; v++){
				  if(vertex_ksi.Z() > v*10 && vertex_ksi.Z() < cut_vertex_z_max)
				      hCutVertAll[v+10] -> Fill(ksiVector.M());
			      }
			      
			      if(particlecand_parentID==18 && vectorcandparentID==18 && ksi_parentID==23){ //real Xi -- Lambda and pion from Xi
				hKpeakID->Fill(1);
				hKdistanceRealXi -> Fill(distance_ksi);
				hKmassRXDist -> Fill(ksiVector.M());
				hVertexXZXreal -> Fill(vertex_ksi.Z());
				hKvertexdistReal->Fill((vertex-vertex_ksi).length());
				
				if(vertex_ksi.Z() > cut_vertex_z_minX && vertex_ksi.Z() < cut_vertex_z_max)
				    hKmassRXDistVert -> Fill(ksiVector.M());


				for(int v = -10; v < 20; v++){
				    if(vertex_ksi.Z() > v*10 && vertex_ksi.Z() < cut_vertex_z_max)
					hCutVertReal[v+10] -> Fill(ksiVector.M());
				}
				
			      }
			      else
				hKpeakID->Fill(0);

			      hHmoduls->Fill(ksi_modules);
			      hHmoduls->Fill(particlecand_moduls);
			      
			      hHNDetector->Fill(ksicand->getNDetector());
			      hHNDetector->Fill(particlecand->getNDetector());
			    }

			  //HGeomVector vertex_ksi1;
			  // vertex_ksi1=particle_tool.calcVertexAnalytical(base_lambda,dir_lambda,base_pion,dir_pion);
			  if(vertex_ksi.Z() > cut_vertex_z_minX && vertex_ksi.Z() < cut_vertex_z_max && ksicand->isFlagBit(kIsUsed)) //cut on vertex_z
			   {
			       hKmassvert->Fill(ksiVector.M());
			      
			       hKvertexvert->Fill((vertex-vertex_ksi).length());//*TMath::Sign(1.0,vertex.Z()-vertex_ksi1.Z()));//distance between vertexes multyply by order of them (+ or -)

			       hVertexXZX_vertcut -> Fill(vertex_ksi.Z(), vertex_ksi.X());
			       hVertexXZXproj_vertcut -> Fill(vertex_ksi.Z());
			      			       
			   }

			   if(distance_ksi<max_distanceX && vertex_ksi.Z() > cut_vertex_z_minX && vertex_ksi.Z() < cut_vertex_z_max && ksicand->isFlagBit(kIsUsed))
			   {
			       hKmassdistvert->Fill(ksiVector.M());
			       hKvertexdistvert->Fill((vertex-vertex_ksi).length());//*TMath::Sign(1.0,vertex.Z()-vertex_ksi1.Z()));//distance between vertexes multyply by order of them (+ or -)
			       hVertexXZX_distvertcut -> Fill(vertex_ksi.Z(), vertex_ksi.X());
			       hVertexXZXproj_distvertcut -> Fill(vertex_ksi.Z());
			   }
			  			   
			}
		    }
		}
		//end*of*Xi**************
	  }//end of HADES loop
	    hIAll->Fill(nInsertAll);
	    hIPiHades->Fill(nInsertPion);
	    hIDist->Fill(nInsertDistance);
	    hIDistSel->Fill(nInsertDistanceSel);
    }//end of FW loop


	//Only HADES
	for(int i=0;i<pcnt;i++)//particle candidates from HADES
	  {
	    particlecand = HCategoryManager::getObject(particlecand, fCatParticleCandSim,i);
		
	    Int_t hades_ID=particlecand->getGeantPID();
	    Int_t particlecand_creationID=particlecand->getGeantParentTrackNum();
	    //Int_t particlecandTID=particlecand->getGeantTrack();
	    Int_t particlecand_parentID=particlecand->getGeantParentPID();
	    hCdet->Fill(hades_ID);
	    if(particlecand->isFlagBit(kIsUsed))// only reasonable tracks
	      {
		if(hades_ID==9 && (particlecand_parentID==18 || particlecand_parentID==23))//pion from lambda or Ksi
		  {
		    hEpionsdet->Fill(particlecand->getTheta());
		  }
		if(particlecand_parentID==18)//particles from Lambda
		  hCLambdaDet->Fill(hades_ID);
		if(particlecand_parentID==23)//particles from Xsi
		  hCXsiDet->Fill(hades_ID);
	      }
	  }
	//End only HADES
} // end eventloop
	//***********************************************************************************

    TPaveText *ptMTDCut = new TPaveText(.25, .7, .3, .85, "NDC");
    ptMTDCut -> SetFillColor(0);
    ptMTDCut -> SetBorderSize(0);
    ptMTDCut -> SetTextSize(.07);
    char dc[12];
    
    
    TPaveText *ptVertCut = new TPaveText(.25, .7, .3, .85, "NDC");
    ptVertCut -> SetFillColor(0);
    ptVertCut -> SetBorderSize(0);
    ptVertCut -> SetTextSize(.07);
    char vc[12];

    for(int i = 0; i < 20; i++){
	ptMTDCut -> Clear();
	sprintf(dc, "MTD<%d", (i*5)+5);
	ptMTDCut -> AddText(dc);
	hCutMTDLAll[i] -> GetXaxis() -> SetTitle("inv M [MeV]");
	hCutMTDLAll[i] -> GetYaxis() -> SetTitle("counts");
	hCutMTDLAll[i] -> Draw();
	ptMTDCut -> Draw("same");
	hCutMTDLAll[i] -> Write();

	hCutMTDLReal[i] -> GetXaxis() -> SetTitle("inv M [MeV]");
	hCutMTDLReal[i] -> GetYaxis() -> SetTitle("counts");
	hCutMTDLReal[i] -> Draw();
	ptMTDCut -> Draw("same");
	hCutMTDLReal[i] -> Write();

	hCutMTDXAll[i] -> GetXaxis() -> SetTitle("inv M [MeV]");
	hCutMTDXAll[i] -> GetYaxis() -> SetTitle("counts");
	hCutMTDXAll[i] -> Draw();
	ptMTDCut -> Draw("same");
	hCutMTDXAll[i] -> Write();

	hCutMTDXReal[i] -> GetXaxis() -> SetTitle("inv M [MeV]");
	hCutMTDXReal[i] -> GetYaxis() -> SetTitle("counts");
	hCutMTDXReal[i] -> Draw();
	ptMTDCut -> Draw("same");
	hCutMTDXReal[i] -> Write();
    }
    
    
    TCanvas *cVertCutScanLAll = new TCanvas("cVertCutScanLAll", "cVertCutScanLAll", 1800, 1400);
    cVertCutScanLAll -> Divide(5,6);
    for(int i = -10; i < 20; i++){
  	cVertCutScanLAll -> cd(i+11);
	ptVertCut -> Clear();
	sprintf(vc, "Vert>%d", i*10);
	ptVertCut -> AddText(vc);
	hCutVertLAll[i+10] -> GetXaxis() -> SetTitle("inv M [MeV]");
	hCutVertLAll[i+10] -> GetYaxis() -> SetTitle("counts");
	hCutVertLAll[i+10] -> Draw();
	ptVertCut -> Draw("same");
	hCutVertLAll[i+10] -> Write();
    }
    cVertCutScanLAll -> Write();

    TCanvas *cVertCutScanLReal = new TCanvas("cVertCutScanLReal", "cVertCutScanLReal", 1800, 1400);
    cVertCutScanLReal -> Divide(5,6);
    for(int i = -10; i < 20; i++){
	cVertCutScanLReal -> cd(i+11);
	ptVertCut -> Clear();
	sprintf(vc, "Vert>%d", i*10);
	ptVertCut -> AddText(vc);
	hCutVertLReal[i+10] -> GetXaxis() -> SetTitle("inv M [MeV]");
	hCutVertLReal[i+10] -> GetYaxis() -> SetTitle("counts");
	hCutVertLReal[i+10] -> Draw();
	ptVertCut -> Draw("same");
	hCutVertLReal[i+10] -> Write();
  }
    cVertCutScanLReal -> Write();
    
    TCanvas *cVertCutScanAll = new TCanvas("cVertCutScanAll", "cVertCutScanAll", 1800, 1400);
    cVertCutScanAll -> Divide(5,6);
    for(int i = -10; i < 20; i++){
  	cVertCutScanAll -> cd(i+11);
	ptVertCut -> Clear();
	sprintf(vc, "Vert>%d", i*10);
	ptVertCut -> AddText(vc);
	hCutVertAll[i+10] -> GetXaxis() -> SetTitle("inv M [MeV]");
	hCutVertAll[i+10] -> GetYaxis() -> SetTitle("counts");
	hCutVertAll[i+10] -> Draw();
	ptVertCut -> Draw("same");
	hCutVertAll[i+10] -> Write();
    }
    cVertCutScanAll -> Write();

    TCanvas *cVertCutScanReal = new TCanvas("cVertCutScanReal", "cVertCutScanReal", 1800, 1400);
    cVertCutScanReal -> Divide(5,4);
    for(int i = -10; i < 20; i++){
	cVertCutScanReal -> cd(i+11);
	ptVertCut -> Clear();
	sprintf(vc, "Vert>%d", i*10);
	ptVertCut -> AddText(vc);
	hCutVertReal[i+10] -> GetXaxis() -> SetTitle("inv M [MeV]");
	hCutVertReal[i+10] -> GetYaxis() -> SetTitle("counts");
	hCutVertReal[i+10] -> Draw();
	ptVertCut -> Draw("same");
	hCutVertReal[i+10] -> Write();
  }
    cVertCutScanReal -> Write();

    hVertexXZL -> Draw("colz");
    hVertexXZL -> Write();
    hVertexXZLproj -> Draw();
    hVertexXZLproj -> Write();
    hKLVertexZRec -> Draw();
    hKLVertexZRec -> Write();

    hVertexXZX_nocuts -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZX_nocuts -> GetYaxis() -> SetTitle("x [mm]");
    hVertexXZX_nocuts -> Draw("colz");
    hVertexXZX_nocuts -> Write();
    hVertexXZXproj_nocuts -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZXproj_nocuts -> Draw();
    hVertexXZXproj_nocuts -> Write();
    hVertexXZX -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZX -> GetYaxis() -> SetTitle("x [mm]");
    hVertexXZX -> Draw("colz");
    hVertexXZX -> Write();
    hVertexXZXproj -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZXproj -> Draw();
    hVertexXZXproj -> Write();
    hVertexXZX_vertcut -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZX_vertcut -> GetYaxis() -> SetTitle("x [mm]");
    hVertexXZX_vertcut -> Draw("colz");
    hVertexXZX_vertcut -> Write();
    hVertexXZXproj_vertcut -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZXproj_vertcut -> Draw();
    hVertexXZXproj_vertcut -> Write();
    hVertexXZX_distvertcut -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZX_distvertcut -> GetYaxis() -> SetTitle("x [mm]");
    hVertexXZX_distvertcut -> Draw("colz");
    hVertexXZX_distvertcut -> Write();
    hVertexXZXproj_distvertcut -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZXproj_distvertcut -> Draw();
    hVertexXZXproj_distvertcut -> Write();

    hVertexXZLreal -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZLreal -> Draw();
    hVertexXZLreal -> Write();
    hVertexXZXreal -> GetXaxis() -> SetTitle("z [mm]");
    hVertexXZXreal -> Draw();
    hVertexXZXreal -> Write();

    hMLDistMass -> GetXaxis() -> SetTitle("M [MeV]");
    hMLDistMass -> Draw(); 
    hMLDistMass -> Write();
    hMLDistMassReal -> GetXaxis() -> SetTitle("M [MeV]");
    hMLDistMassReal -> Draw();
    hMLDistMassReal -> Write();
    hKmassdist -> GetXaxis() -> SetTitle("M [MeV]");
    hKmassdist -> Draw(); 
    hKmassdist -> Write();
    hKmassvert -> GetXaxis() -> SetTitle("M [MeV]");
    hKmassvert -> Draw(); 
    hKmassvert -> Write();
    hKmassdistvert -> GetXaxis() -> SetTitle("M [MeV]");
    hKmassdistvert -> Draw();
    hKmassdistvert-> Write();
    hKmassRLpion -> Write();
    hKmassRX -> Write();
    hKmassRXDist -> Write();

    TCanvas *cVertdiff = new TCanvas("cVertdiff", "cVertdiff");
    cVertdiff -> Divide(2,2);
    cVertdiff -> cd(1);
    hKvertexAll -> GetXaxis() -> SetTitle("dist [mm]");
    hKvertexAll -> Draw();
    hKvertexAll -> Write();
    cVertdiff -> cd(2);
    hKvertexReal -> GetXaxis() -> SetTitle("dist [mm]");
    hKvertexReal -> Draw();
    hKvertexReal -> Write();
    cVertdiff -> cd(3);
    hKvertexdistAll -> GetXaxis() -> SetTitle("dist [mm]");
    hKvertexdistAll -> Draw();
    hKvertexdistAll -> Write();
    cVertdiff -> cd(4);
    hKvertexdistReal -> GetXaxis() -> SetTitle("dist [mm]");
    hKvertexdistReal -> Draw();
    hKvertexdistReal -> Write();
    cVertdiff -> Write();

    
    hKvertexvert -> GetXaxis() -> SetTitle("z [mm]");
    hKvertexvert -> Draw();
    hKvertexvert -> Write();
    hKvertexdistvert -> GetXaxis() -> SetTitle("z [mm]");
    hKvertexdistvert -> Draw();
    hKvertexdistvert -> Write();
    
    hMLDistVert -> GetXaxis() -> SetTitle("z [mm]");
    hMLDistVert -> Draw();
    hMLDistVert -> Write();
    hKLMassDistVert -> GetXaxis() -> SetTitle("z [mm]");
    hKLMassDistVert -> Draw();
    hKLMassDistVert -> Write();
    hKmassdistVert -> GetXaxis() -> SetTitle("z [mm]");
    hKmassdistVert -> Draw();
    hKmassdistVert -> Write();
    hKmassRXDistVert -> GetXaxis() -> SetTitle("z [mm]");
    hKmassRXDistVert -> Draw();
    hKmassRXDistVert -> Write();

    
    hTDPiProton -> GetXaxis() -> SetTitle("dist z [mm]");
    hTDPiProton -> Draw();
    hTDPiProton -> Write();
    hPDpionproton -> GetXaxis() -> SetTitle("dist z [mm]");
    hPDpionproton -> Draw();
    hPDpionproton -> Write();
    hPDlambda -> GetXaxis() -> SetTitle("dist [mm]");
    hPDlambda -> Draw();
    hPDlambda -> Write();
    hKdistanceall -> GetXaxis() -> SetTitle("dist [mm]");
    hKdistanceall -> Draw();
    hKdistanceall -> Write();
    hKdistanceRealXi -> GetXaxis() -> SetTitle("dist [mm]");
    hKdistanceRealXi -> Draw();
    hKdistanceRealXi -> Write();
    
    //draw all
    cTrackDistance->Divide(2,2);
    cTrackDistance->cd(1);
    hTDAll->Draw();
    cTrackDistance->cd(2);
    hTDPiProton->Draw();
    cTrackDistance->cd(3);
    hTDAllCh2->Draw();
    cTrackDistance->cd(4);
    hTDPiProtonCh2->Draw();

    cTrackDistanceRes->Divide(2,2);
    cTrackDistanceRes->cd(1);
    hTDRAll->Draw();
    cTrackDistanceRes->cd(2);
    hTDRPiProton->Draw();
    cTrackDistanceRes->cd(3);
    hTDRAllCh2->Draw();
    cTrackDistanceRes->cd(4);
    hTDRPiProtonCh2->Draw();
    
    cControlPanel->Divide(2,2);
    cControlPanel->cd(1);
    hCPChi2Hades->Draw();
    cControlPanel->cd(2);
    hCPChi2FW->Draw();
    cControlPanel->cd(3);
    h2CPtargetPosition->Draw("COLZ");

    cMassLambda->Divide(2,2);
    cMassLambda->cd(1);
    hMLAll -> GetXaxis() -> SetTitle("M [MeV]");
    hMLAll->Draw();
    cMassLambda->cd(2);
    hMLPiHades->Draw();
    hMLDistSel->SetLineColor(kRed);
    hMLDistSel->Draw("SAME");
    cMassLambda->cd(3);
    hMLDist->Draw();
    cMassLambda->cd(4);
    hMLDistSel->Draw();
    hMLAll->Write();
    hMLDist->Write();
    hMLPiHades->Write();
    hMLDistSel -> Write();
    
    cIntersection->Divide(2,2);
    cIntersection->cd(1);
    hIAll->Draw();
    cIntersection->cd(2);
    hIPiHades->Draw();
    cIntersection->cd(3);
    hIDist->Draw();
    cIntersection->cd(4);
    hIDistSel->Draw();

    cKineLambdaRec->Divide(2,3);
    cKineLambdaRec->cd(1);
    hKLMass->Draw();
    cKineLambdaRec->cd(2);
    hKLDistance->Draw();
    cKineLambdaRec->cd(3);
    h2KLVertexZRSim->Draw("COLZ");
    cKineLambdaRec->cd(4);
    hKLVertexZSim->Draw();
    cKineLambdaRec->cd(5);
    h2KLVertexZRRec->Draw("COLZ");
    cKineLambdaRec->cd(6);
    hKLVertexZRec->Draw();
    hKLMass->Write();
    hKLMassDist->Write();
    
    cVertexRes->Divide(2,2);
    cVertexRes->cd(1);
    hVRradial->Draw();
    cVertexRes->cd(2);
    hVRz->Draw();
    cVertexRes->cd(3);
    hVRradialSel->Draw();
    cVertexRes->cd(4);
    hVRzSel->Draw();
    

    cVertexResInZ->Divide(4,2);
    for(int i=0;i<7;i++)
      {
	cVertexResInZ->cd(i+1);
	hVRIZ[i]->Draw();
	hVRIZ[i]->Fit(fVRIZgaus[i]);
	gVRIZ->SetPoint(i,i*50-25,fVRIZgaus[i]->GetParameter(1));
	gVRIZ->SetPointError(i,0,fVRIZgaus[i]->GetParameter(2));
      }
    cVertexResInZ->cd(8);
    gVRIZ->SetTitle("R_sim-R_rec in function of Z");
    gVRIZ->SetMarkerColor(4);
    gVRIZ->SetMarkerStyle(21);
    gVRIZ->Draw("ALP");

    cHADES->Divide(2,2);
    cHADES->cd(1);
    hHADESmultiplicity->Draw();
    cHADES->cd(2);
    hHFwDetmultiplicity->Draw();
    cHADES->cd(3);
    hHparticleID->Draw();
    cHADES->cd(4);

    cPrimaryKine->Divide(2,3);
    cPrimaryKine->cd(1);
    h2PKall->Draw("COLZ");
    cPrimaryKine->cd(2);
    h2PKpion->Draw("COLZ");
    cPrimaryKine->cd(3);
    h2PKproton->Draw("COLZ");
    cPrimaryKine->cd(4);
    h2PKkaon->Draw("COLZ");
    cPrimaryKine->cd(5);
    h2PKpionpion->Draw("COLZ");
    
    cKsi->Divide(2,2);
    cKsi->cd(1);
    hKmassall -> GetXaxis() -> SetTitle("M [MeV]");
    hKmassall->Draw();
    cKsi->cd(2);
    hKdistanceall->Draw();
    cKsi->cd(3);
    hKmassdist->Draw();
    cKsi->cd(4);
    hKvertexdistAll->Draw();
    hKmassall->Write();
    hKmassdist->Write();

    cParticlesDiff->Divide(2,2);
    cParticlesDiff->cd(1);
    hPDphiKsiLambda->Draw();
    cParticlesDiff->cd(2);
    hPDthetaKsiLambda->Draw();
    cParticlesDiff->cd(3);
    hPDgamma->Draw();

    cEff->Divide(4,2);
    cEff->cd(1);
    hEprotons4Pi->Draw();
    hEprotonsdet->SetLineColor(kRed);
    hEprotonsdet->Draw("SAME");
    cEff->cd(2);
    hEprotonsdet->Draw();
    cEff->cd(3);
    hEprotonsEff->Divide(hEprotonsdet,hEprotons4Pi);
    hEprotonsEff->Draw();
    cEff->cd(4);
    hEprotondetL->Draw();
    cEff->cd(5);
    hEpions4Pi->Draw();
    hEpionsdet->SetLineColor(kRed);
    hEpionsdet->Draw("SAME");
    cEff->cd(6);
    hEpionsdet->Draw();
    cEff->cd(7);
    hEpionsEff->Divide(hEpionsdet,hEpions4Pi);
    hEpionsEff->Draw();
    cEff->cd(8);
    h2EpionEff->Divide(h2Epiondet,h2Epion4Pi);
    h2EpionEff->Draw("COLZ");

    cCounter->Divide(2,3);
    cCounter->cd(1);
    hCgen->Draw();
    cCounter->cd(2);
    hCdet->Draw();
    cCounter->cd(3);
    hCLambdaGen->Draw();
    cCounter->cd(4);
    hCLambdaDet->Draw();
    cCounter->cd(5);
    hCXsiGen->Draw();
    cCounter->cd(6);
    hCXsiDet->Draw();

    cPionDist->Divide(2);
    cPionDist->cd(1);
    hPDpionproton->Draw();
    hPDlambda->SetLineColor(kRed);
    hPDlambda->Draw("SAME");
    cPionDist->cd(2);
    TH1F* hratio=(TH1F*)hPDpionproton->Clone("hratio");
    hratio->Divide(hPDlambda);
    hratio->Draw();
    
    //save histograms
    hKtofproperties->Write();
    hKtofHitInd->Write();
    hKpeakID->Write();
    hHmoduls->Write();
    hHNDetector->Write();
    //Save canvases
    cTrackDistance->Write();
    cTrackDistanceRes->Write();
    cControlPanel->Write();
    cMassLambda->Write();
    cIntersection->Write();
    cKineLambdaRec->Write();
    cVertexRes->Write();
    cVertexResInZ->Write();
    cHADES->Write();
    cPrimaryKine->Write();
    cKsi->Write();
    cParticlesDiff->Write();
    cEff->Write();
    cCounter->Write();
    cPionDist->Write();

    output_file->Close();
    cout << "writing root tree done" << endl;

    timer.Stop();
    timer.Print();

    return 0;
}
