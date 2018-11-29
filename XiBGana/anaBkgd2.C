void nice_canv1(TVirtualPad * c)
{
    c -> SetBottomMargin(0.15);
    c -> SetLeftMargin(0.15);
    gStyle -> SetTitleSize(0.035, "xy");
    gStyle -> SetLabelSize(0.035, "xy");
    gStyle -> SetTitleOffset(1.2, "xy");
}

//void anaBkgd2(char* inpath){
void anaBkgd2(){
    TGaxis::SetMaxDigits(3);
    
    int nbinsL = 125;
    int nbinsX = 100;
    int minL = 1050;
    int maxL = 1200;
    int minX = 1200;
    int maxX = 1400;

    //no cuts
    //inv mass Lambda1115 & Xi
    TH1F *hLallSum = new TH1F("hLallSum", "hLallSum", nbinsL, minL, maxL);
    TH1F *hrealLSum = new TH1F("hrealLSum", "hrealLSum", nbinsL, minL, maxL);
    TH1F *hLGeantIDSum = new TH1F("hLGeantIDSum", "hLGeantIDSum", nbinsL, minL, maxL);
    TH1F *hrealXSum = new TH1F("hrealXSum", "hrealXSum", nbinsX, minX, maxX);
    TH1F *hXGeantIDSum = new TH1F("hXGeantIDSum", "hXGeantIDSum", nbinsX, minX, maxX);
    TH1F *hLallSumSc = new TH1F("hLallSumSc", "hLallSumSc", nbinsL, minL, maxL);
    TH1F *hrealLSumSc = new TH1F("hrealLSumSc", "hrealLSumSc", nbinsL, minL, maxL);
    TH1F *hLGeantIDSumSc = new TH1F("hLGeantIDSumSc", "hLGeantIDSumSc", nbinsL, minL, maxL);
    TH1F *hrealXSumSc = new TH1F("hrealXSumSc", "hrealXSumSc", nbinsX, minX, maxX);
    TH1F *hXGeantIDSumSc = new TH1F("hXGeantIDSumSc", "hXGeantIDSumSc", nbinsX, minX, maxX);
    
    TH1F *hLallSumBG = new TH1F("hLallSumBG", "hLallSumBG", nbinsL, minL, maxL);
    TH1F *hrealLSumBG = new TH1F("hrealLSumBG", "hrealLSumBG", nbinsL, minL, maxL);
    TH1F *hrealLSumPeak = new TH1F("hrealLSumPeak", "hrealLSumPeak", nbinsL, minL, maxL);
    TH1F *hLallSumBGSc = new TH1F("hLallSumBGSc", "hLallSumBGSc", nbinsL, minL, maxL);
    TH1F *hrealLSumBGSc = new TH1F("hrealLSumBGSc", "hrealLSumBGSc", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakSc = new TH1F("hrealLSumPeakSc", "hrealLSumPeakSc", nbinsL, minL, maxL);

    TH1F *hXallSumBG = new TH1F("hXallSumBG", "hXallSumBG", nbinsX, minX, maxX);
    TH1F *hrealXSumBG = new TH1F("hrealXSumBG", "hrealXSumBG", nbinsX, minX, maxX);
    TH1F *hrealXSumPeak = new TH1F("hrealXSumPeak", "hrealXSumPeak", nbinsX, minX, maxX);
    TH1F *hXallSumBGSc = new TH1F("hXallSumBGSc", "hXallSumBGSc", nbinsX, minX, maxX);
    TH1F *hrealXSumBGSc = new TH1F("hrealXSumBGSc", "hrealXSumBGSc", nbinsX, minX, maxX);
    TH1F *hrealXSumPeakSc = new TH1F("hrealXSumPeakSc", "hrealXSumPeakSc", nbinsX, minX, maxX);

    //only signal channel 090
    TH1F *hLall90, *hrealL90, *hrealX90, *hLall90Sc, *hrealL90Sc, *hrealX90Sc;
    TH1F *hLGeantIDPeak = new TH1F("hLGeantIDPeak", "hLGeantIDPeak", nbinsL, minL, maxL);
    TH1F *hXGeantIDPeak = new TH1F("hXGeantIDPeak", "hXGeantIDPeak", nbinsX, minX, maxX);
    TH1F *hLGeantIDScPeak = new TH1F("hLGeantIDScPeak", "hLGeantIDScPeak", nbinsL, minL, maxL);
    TH1F *hXGeantIDScPeak = new TH1F("hXGeantIDScPeak", "hXGeantIDScPeak", nbinsX, minX, maxX);
    
    TCanvas *cLambdaXiMass = new TCanvas("cLambdaXiMass", "Lambda & Xi invariant mass", 1800, 1000); //M_inv for Lambda & Xi reconstruction from all simulated channels
    TCanvas *cLambdaXiMassSc = new TCanvas("cLambdaXiMassSc", "Lambda & Xi invariant mass (cr sc)", 1800, 1000); //M_inv for Lambda & Xi reconstruction from all simulated channels with crsec
    cLambdaXiMass -> Divide(3,2);
    cLambdaXiMassSc -> Divide(3,2);

    THStack *hLmass_sc = new THStack(); //Lambda scaled with cr_sec, no cuts
    THStack *hLmass_sc_rec = new THStack(); //Lambda scaled with cr_sec, all L cuts
    THStack *hXmass_sc = new THStack(); //Xi, scaled with cr_sec, no cuts
    THStack *hXmass_sc_fin = new THStack(); //Xi, scaled with cr_sec, up to MTD_X cut

    //MTD_L, Lmass, MTD_X
    //inv mass Lambda1115 & Xi
    TH1F *hLallSumMtd = new TH1F("hLallSumMtd", "hLallSumMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumMtd = new TH1F("hrealLSumMtd", "hrealLSumMtd", nbinsL, minL, maxL);
    TH1F *hLGeantIDSumMtd = new TH1F("hLGeantIDSumMtd", "hLGeantIDSumMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumLmass = new TH1F("hrealLSumLmass", "hrealLSumLmass", nbinsL, minL, maxL);
    TH1F *hrealXSumMtd = new TH1F("hrealXSumMtd", "hrealXSumMtd", nbinsX, minX, maxX);
    TH1F *hXGeantIDSumMtd = new TH1F("hXGeantIDSumMtd", "hXGeantIDSumMtd", nbinsX, minX, maxX);
    TH1F *hLallSumScMtd = new TH1F("hLallSumScMtd", "hLallSumScMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumScLmassMtd = new TH1F("hrealLSumScLmassMtd", "hrealLSumScLmassMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumScMtd = new TH1F("hrealLSumScMtd", "hrealLSumScMtd", nbinsL, minL, maxL);
    TH1F *hLGeantIDSumScMtd = new TH1F("hLGeantIDSumScMtd", "hLGeantIDSumScMtd", nbinsL, minL, maxL);
    TH1F *hrealXSumScMtd = new TH1F("hrealXSumScMtd", "hrealXSumScMtd", nbinsX, minX, maxX);
    TH1F *hXGeantIDSumScMtd = new TH1F("hXGeantIDSumScMtd", "hXGeantIDSumScMtd", nbinsX, minX, maxX);
    
    TH1F *hLallSumBGMtd = new TH1F("hLallSumBGMtd", "hLallSumBGMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumBGMtd = new TH1F("hrealLSumBGMtd", "hrealLSumBGMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumMtdPeak = new TH1F("hrealLSumMtdPeak", "hrealLSumMtdPeak", nbinsL, minL, maxL);
    TH1F *hLallSumBGScMtd = new TH1F("hLallSumBGScMtd", "hLallSumBGScMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumBGScMtd = new TH1F("hrealLSumBGScMtd", "hrealLSumBGScMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumMtdPeakSc = new TH1F("hrealLSumMtdPeakSc", "hrealLSumMtdPeakSc", nbinsL, minL, maxL);

    TH1F *hLallSumBGLmass = new TH1F("hLallSumBGLmass", "hLallSumBGLmass", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakLmass = new TH1F("hrealLSumPeakLmass", "hrealLSumPeakLmass", nbinsL, minL, maxL);
    TH1F *hLallSumBGScLmass = new TH1F("hLallSumBGScLmass", "hLallSumBGScLmass", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakScLmass = new TH1F("hrealLSumPeakScLmass", "hrealLSumPeakScLmass", nbinsL, minL, maxL);

     TH1F *hXallSumBGMtd = new TH1F("hXallSumBGMtd", "hXallSumBGMtd", nbinsX, minX, maxX);
     TH1F *hrealXSumBGMtd = new TH1F("hrealXSumBGMtd", "hrealXSumBGMtd", nbinsX, minX, maxX);
     TH1F *hrealXSumMtdPeak = new TH1F("hrealXSumMtdPeak", "hrealXSumMtdPeak", nbinsX, minX,maxX);
     TH1F *hXallSumBGScMtd = new TH1F("hXallSumBGScMtd", "hXallSumBGScMtd", nbinsX, minX, maxX);
     TH1F *hrealXSumBGScMtd = new TH1F("hrealXSumBGScMtd", "hrealXSumBGScMtd", nbinsX, minX, maxX);
     TH1F *hrealXSumMtdPeakSc = new TH1F("hrealXSumMtdPeakSc", "hrealXSumMtdPeakSc", nbinsX, minX, maxX);
    
    //only signal channel 090
    TH1F *hLall90Mtd, *hrealL90Mtd, *hrealX90Mtd, *hLall90ScMtd, *hrealL90ScMtd, *hrealX90ScMtd;
    TH1F *hLGeantIDMtdPeak = new TH1F("hLGeantIDMtdPeak", "hLGeantIDMtdPeak", nbinsL, minL, maxL);
    TH1F *hXGeantIDMtdPeak = new TH1F("hXGeantIDMtdPeak", "hXGeantIDMtdPeak", nbinsX, minX, maxX);
    TH1F *hLGeantIDScMtdPeak = new TH1F("hLGeantIDScMtdPeak", "hLGeantIDScMtdPeak", nbinsL, minL, maxL);
    TH1F *hXGeantIDScMtdPeak = new TH1F("hXGeantIDScMtdPeak", "hXGeantIDScMtdPeak", nbinsX, minX, maxX);

    TCanvas *cLambdaXiMassMtd = new TCanvas("cLambdaXiMassMtd", "Lambda & Xi invariant mass, MTD_L, Lmass, MTD_X", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels
    TCanvas *cLambdaXiMassScMtd = new TCanvas("cLambdaXiMassScMtd", "Lambda & Xi invariant mass (cr sc), MTD_L, Lmass, MTD_X", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels with crsec
    cLambdaXiMassMtd -> Divide(3,2);
    cLambdaXiMassScMtd -> Divide(3,2);

    //MTD_L, Lmass, MTD_X, Vertz_X
    //Lambda1115
    TH1F *hLVertex_sig = new TH1F("hLVertex_sig", "hLVertex_sig", 150, -100, 500); //Lambda1115 vertex_z signal
    TH1F *hLVertex_bg = new TH1F("hLVertex_bg", "hLVertex_bg", 150, -100, 500); //Lambda1115 vertex_z bg
    TH1F *hLVertex_bg_sum = new TH1F("hLVertex_bg_sum", "#Lambda/(1115/) vertex reconstruction --- backgroundchannels sum", 150, -100, 500); //Xi vertex_z bg sum

    TH1F *hLallSumVert = new TH1F("hLallSumVert", "hLallSumVert", nbinsL, minL, maxL);
    TH1F *hrealLSumVert = new TH1F("hrealLSumVert", "hrealLSumVert", nbinsL, minL, maxL);
    TH1F *hLGeantIDSumVert = new TH1F("hLGeantIDSumVert", "hLGeantIDSumVert", nbinsL, minL, maxL);
    TH1F *hrealXSumVert = new TH1F("hrealXSumVert", "hrealXSumVert", nbinsX, minX, maxX);
    TH1F *hXGeantIDSumVert = new TH1F("hXGeantIDSumVert", "hXGeantIDSumVert", nbinsX, minX, maxX);
    TH1F *hLallSumScVert = new TH1F("hLallSumScVert", "hLallSumScVert", nbinsL, minL, maxL);
    TH1F *hrealLSumScVert = new TH1F("hrealLSumScVert", "hrealLSumScVert", nbinsL, minL, maxL);
    TH1F *hLGeantIDSumScVert = new TH1F("hLGeantIDSumScVert", "hLGeantIDSumScVert", nbinsL, minL, maxL);
    TH1F *hrealXSumScVert = new TH1F("hrealXSumScVert", "hrealXSumScVert", nbinsX, minX, maxX);
    TH1F *hXGeantIDSumScVert = new TH1F("hXGeantIDSumScVert", "hXGeantIDSumScVert", nbinsX, minX, maxX);

    TH1F *hLallSumBGVert = new TH1F("hLallSumBGVert", "hLallSumBGVert", nbinsL, minL, maxL);
    TH1F *hrealLSumBGVert = new TH1F("hrealLSumBGVert", "hrealLSumBGVert", nbinsL, minL, maxL);
    TH1F *hrealLSumVertPeak = new TH1F("hrealLSumVertPeak", "hrealLSumVertPeak", nbinsL, minL, maxL);
    TH1F *hLallSumBGScVert = new TH1F("hLallSumBGScVert", "hLallSumBGScVert", nbinsL, minL, maxL);
    TH1F *hrealLSumBGScVert = new TH1F("hrealLSumBGScVert", "hrealLSumBGScVert", nbinsL, minL, maxL);
    TH1F *hrealLSumVertPeakSc = new TH1F("hrealLSumVertPeakSc", "hrealLSumVertPeakSc", nbinsL, minL, maxL);

    TH1F *hXallSumBGVert = new TH1F("hXallSumBGVert", "hXallSumBGVert", nbinsX, minX, maxX);
    TH1F *hrealXSumBGVert = new TH1F("hrealXSumBGVert", "hrealXSumBGVert", nbinsX, minX, maxX);
    TH1F *hrealXSumVertPeak = new TH1F("hrealXSumVertPeak", "hrealXSumVertPeak", nbinsX, minX, maxX);
    TH1F *hXallSumBGScVert = new TH1F("hXallSumBGScVert", "hXallSumBGScVert", nbinsX, minX, maxX);
    TH1F *hrealXSumBGScVert = new TH1F("hrealXSumBGScVert", "hrealXSumBGScVert", nbinsX, minX, maxX);
    TH1F *hrealXSumVertPeakSc = new TH1F("hrealXSumVertPeakSc", "hrealXSumVertPeakSc", nbinsX, minX, maxX);

    //only signal channel 090
    TH1F *hLall90Vert, *hrealL90Vert, *hrealX90Vert, *hLall90ScVert, *hrealL90ScVert, *hrealX90ScVert;
    TH1F *hLGeantIDVertPeak = new TH1F("hLGeantIDVertPeak", "hLGeantIDVertPeak", nbinsL, minL, maxL);
    TH1F *hXGeantIDVertPeak = new TH1F("hXGeantIDVertPeak", "hXGeantIDVertPeak", nbinsX, minX, maxX);
    TH1F *hLGeantIDScVertPeak = new TH1F("hLGeantIDScVertPeak", "hLGeantIDScVertPeak", nbinsL, minL, maxL);
    TH1F *hXGeantIDScVertPeak = new TH1F("hXGeantIDScVertPeak", "hXGeantIDScVertPeak", nbinsX, minX, maxX);
    
    TCanvas *cLambdaXiMassVert = new TCanvas("cLambdaXiMassVert", "Lambda & Xi invariant mass, MTD, Vert", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels after MTD_L, MassL, MTD_X, 
    TCanvas *cLambdaXiMassScVert = new TCanvas("cLambdaXiMassScVert", "Lambda & Xi invariant mass (cr sc), MTD, Vert", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels
    cLambdaXiMassVert -> Divide(3,2);
    cLambdaXiMassScVert -> Divide(3,2);


    TCanvas *cVertZ_L = new TCanvas("cVertZ_L", "#Lambda/(1115/) vertex reconstruction - z", 2000, 1000);
    cVertZ_L -> Divide(4,2);
    
    //Xi
    TH1F *hXVertex_sig = new TH1F("hXVertex_sig", "hXVertex_sig", 150, -100, 500); //Xi vertex_z signal
    TH1F *hXVertex_bg = new TH1F("hXVertex_bg", "hXVertex_bg", 150, -100, 500); //Xi vertex_z bg
    TH1F *hXVertex_bg_sum = new TH1F("hXVertex_bg_sum", "Xi vertex reconstruction --- background channels sum", 150, -100, 500); //Xi vertex_z bg sum
    
    TCanvas *cVertZ_X = new TCanvas("cVertZ_X", "Xi vertex reconstruction - z", 2000, 1000);
    cVertZ_X -> Divide(4,2);

    //MTD & VERT all channels
    //Lambda
    TCanvas *cMTDL = new TCanvas("cMTDL", "cMTDL", 1000, 500);
    cMTDL -> Divide(2,1);
    TCanvas *cVERTL = new TCanvas("cVERTL", "cVERTL", 1000, 500);
    cVERTL -> Divide(2,1);
    TCanvas *cVERTL1 = new TCanvas("cVERTL1", "cVERTL1");
    TH1F *hLVertex_sigSum = new TH1F("hLVertex_sigSum", "hLVertex_sigSum", 150, -100, 500); //Lambda1115 vertex_z signal sum
    TH1F *hLVertex_allSum = new TH1F("hLVertex_allSum", "hLVertex_allSum", 150, -100, 500); //Lambda1115 vertex_z all cand. sum
    //Xi
    TCanvas *cMTDX = new TCanvas("cMTDX", "cMTDX", 1000, 500);
    cMTDX -> Divide(2,1);
    TCanvas *cVERTX = new TCanvas("cVERTX", "cVERTX", 1000, 500);
    cVERTX -> Divide(2,1);
    TCanvas *cVERTX1 = new TCanvas("cVERTX1", "cVERTX1");
    TH1F *hXVertex_sigSum = new TH1F("hXVertex_sigSum", "hXVertex_sigSum", 150, -100, 500); //Xi vertex_z signal sum
    TH1F *hXVertex_allSum = new TH1F("hXVertex_allSum", "hXVertex_allSum", 150, -100, 500); //Xi vertex_z all cand. sum

    cMTDL -> cd(1);
    nice_canv1(gPad);
    cMTDL -> cd(2);
    nice_canv1(gPad);
    cMTDX -> cd(1);
    nice_canv1(gPad);
    cMTDX -> cd(2);
    nice_canv1(gPad);

    cVERTL -> cd(1);
    nice_canv1(gPad);
    cVERTL -> cd(2);
    nice_canv1(gPad);
    cVERTX -> cd(1);
    nice_canv1(gPad);
    cVERTX -> cd(2);
    nice_canv1(gPad);
    //*******************************************************************************
    //fit function for gauss estimation
    TF1 *fit = new TF1("fit", "gaus");
    double mmax, center_fit, sigma_fit, s_b, m3sigma, p3sigma;
    int a, b;
    double cntSL, cntSLsc, cntBL, cntBLsc, cntSX, cntSXsc, cntBX, cntBXsc, cntSLMtd, cntSLscMtd, cntSLLmass, cntSLscLmass, cntBLscLmass, cntSXMtd, cntSXscMtd, cntBLMtd, cntBLscMtd, cntBXMtd, cntBXscMtd, cntSLVert, cntSLscVert, cntSXVert, cntSXscVert, cntBLVert, cntBLscVert, cntBXVert, cntBXscVert, cntSXMtd90;
    double cntSLGeant, cntSLscGeant, cntSXGeant, cntSXscGeant, cntSLMtdGeant, cntSLscMtdGeant, cntSXMtdGeant, cntSXscMtdGeant, cntSLVertGeant, cntSLscVertGeant, cntSXVertGeant, cntSXscVertGeant;
    double nallL = 0;
    double nallX = 0;
    double ninch = 0;
    
    //channels
    char chanNo[64];
    int chan[] = {90, 10, 21, 22, 23, 62, 100};
    Double_t cr_sec[] = {4.8, 600., 100., 30., 30., 20., 20.};
    string reac[] = {"#Xi^{-}K^{+}K^{+}p",
		     "pp2#pi^{+}2#pi^{-}",
		     "p#LambdaK^{0}_{s}#pi^{+}",
		     "p#LambdaK^{+}#pi^{+}#pi^{-}",
		     "n#LambdaK^{0}_{s}2#pi^{+}",
		     "p#Sigma^{0}K^{0}_{s}#pi^{+}",
		     "ppK^{0}_{s}K^{0}_{s}"};
  
    //cuts
    Double_t zlim_minL = -20; //[mm]
    Double_t zlim_minX = -50; //[mm]
    Double_t zlim_max = 300; //[mm]
    Double_t distcut_minL = 25; //[mm]
    Double_t distcut_minX = 20; //[mm]
    Double_t mLam_min = 1106; //[MeV]	  
    Double_t mLam_max = 1126; //[MeV]	  


    //legends
    TLegend *l1 = new TLegend(.2, .5, .35, .85);
    l1 -> SetFillStyle(0);
    l1 -> SetBorderSize(0);
    l1 -> SetTextSize(.04);
    TLegend *l2 = new TLegend(.2, .1, .35, .45);
    l2 -> SetFillStyle(0);
    l2 -> SetBorderSize(0);
    l2 -> SetTextSize(.04);
    TLegend *l1a = new TLegend(.2, .5, .35, .85);
    l1a -> SetFillStyle(0);
    l1a -> SetBorderSize(0);
    l1a -> SetTextSize(.04);
    TLegend *l1Mtd = new TLegend(.2, .5, .35, .85);
    l1Mtd -> SetFillStyle(0);
    l1Mtd -> SetBorderSize(0);
    l1Mtd -> SetTextSize(.04);
    TLegend *lChan = new TLegend(.2, .5, .5, .8);
    lChan -> SetFillStyle(0);
    lChan -> SetBorderSize(0);
    lChan -> SetTextSize(.04);

    TCanvas *ctmp = new TCanvas("ctmp", "ctmp");
    
    for(int i = 0; i < 7; i++){
      sprintf(chanNo, "../XiRealPID/outputs_ch/output_%03d_test5c.root", chan[i]);
      	TFile *f1 = TFile::Open(chanNo, "READ");

	TPaveText *ptch = new TPaveText(.5, .7, .8, .85, "NDC");
	ptch -> SetFillColor(0);
	ptch -> SetBorderSize(0);
	ptch -> SetTextSize(0.07);
	ptch -> AddText(reac[i].c_str());

	TH1I *tmpevnt = (TH1I*)f1 -> Get("heventNo");
	ninch = tmpevnt -> GetEntries();
	
	//no cuts
	TH1F *hAllHFd = (TH1F*)f1->Get("hMLAll"); //all combinations of H-FD
	TH1F *hLall = (TH1F*)f1->Get("hMLPiHades"); //pi in H, anth in FD
	TH1F *hrealL = (TH1F*)f1->Get("hMLPiHpF"); //pion in H, p in FD
        TH1F *hLGeantID = (TH1F*)f1->Get("hrealL"); //pion in H, p in FD from L -> Geant ID
	TH1F *hrealX = (TH1F*)f1->Get("hMXAll"); //Lambda and pion in H, in mL range
        TH1F *hXGeantID = (TH1F*)f1->Get("hrealX"); //pion in H from X, L -> Geant ID
	
	hAllHFd -> Rebin(2);
	hLall -> Rebin(2);
	hrealL -> Rebin(2);
	hLGeantID -> Rebin(2);
	hrealX -> Rebin(2);
	hXGeantID -> Rebin(2);
	
	//spectrum MTD_L
	TH1F *hMTD_Lall = (TH1F*)f1 -> Get("hTDpiFD"); //distance between anything in FD and pion in H
	TH1F *hMTD_Lreal = (TH1F*)f1 -> Get("hTDpip"); //distance between proton in FD and pion in H

	//spectrum MTD_X
	TH1F *hMTD_Xreal = (TH1F*)f1 -> Get("hTDpiL"); //distance between Lambda and pion in H
	
	//MTD_L, Lmass, MTD_X
	TH1F *hLallMtd = (TH1F*)f1->Get("hMLPiHadesMTD"); //pion in H, anything in FD, MTD_L
	TH1F *hrealLMtd = (TH1F*)f1->Get("hMLPiHpFMTD"); //pion in H, proton in FD, MTD_L
	TH1F *hLGeantIDMtd = (TH1F*)f1->Get("hrealLMTD"); //pion in H, p in FD from L -> Geant ID, MTD_L
	TH1F *hrealXMtd = (TH1F*)f1->Get("hMXPiLMTD"); //Lambda and pion in H, MTD_X
        TH1F *hXGeantIDMtd = (TH1F*)f1->Get("hrealXMTD"); //pion in H from X, L -> Geant ID, MTD_X
	
	hLallMtd -> Rebin(2);
	hrealLMtd -> Rebin(2);
	hLGeantIDMtd -> Rebin(2);
	hrealXMtd -> Rebin(2);
	hXGeantIDMtd -> Rebin(2);
	
	//spectrum Vertz_L
	TH1F *hVertz_Lall = (TH1F*)f1 -> Get("hVertpiFD"); //vertZ of anything in FD and pion in H 
	TH1F *hVertz_Lreal = (TH1F*)f1 -> Get("hVertpip"); //vertZ of proton in FD and pion in H 

	//spectrum Vertz_X
	TH1F *hVertz_Xreal = (TH1F*)f1 -> Get("hXVertpiL"); //vertZ of Lambda and pion in H 

	//MTD_L, Lmass, MTD_X, Vertz_X
	TH1F *hLallVert = (TH1F*)f1->Get("hMLPiHadesMTDVert"); //pion in H, anything in FD, MTD_L, VertL
	TH1F *hrealLVert = (TH1F*)f1->Get("hMLPiHpFMTDVert"); //pion in H, proton in FD, MTD_L, VertL
	TH1F *hLGeantIDVert = (TH1F*)f1->Get("hrealLMTDVert"); //pion in H, p in FD from L -> Geant ID, MTD_L, VertL
	TH1F *hrealXVert = (TH1F*)f1->Get("hMXPiLMTDVert"); //Lambda and pion in H, MTD_X, VertX
	TH1F *hXGeantIDVert = (TH1F*)f1->Get("hrealXMTDVert"); //pion in H from X, L -> Geant ID, MTD_X, VertX

	hLallVert -> Rebin(2);
	hrealLVert -> Rebin(2);
	hLGeantIDVert -> Rebin(2);
	hrealXVert -> Rebin(2);
	hXGeantIDVert -> Rebin(2);

	int col = i+1;
	if(i == 2) col = 8;
	if(i == 4) col = 42;
	if(i == 6) col = 15;

	//no cuts
	TH1F *hLall1 = (TH1F*)hLall -> Clone("hLall1_c");
	TH1F *hLall1sc = (TH1F*)hLall -> Clone("hLall1sc_c");
	TH1F *hrealL1 = (TH1F*)hrealL -> Clone("hrealL1_c");
	TH1F *hrealL1sc = (TH1F*)hrealL -> Clone("hrealL1sc_c");
	TH1F *hLGeantID1 = (TH1F*)hLGeantID -> Clone("hLGeantID1_c");
	TH1F *hLGeantID1sc = (TH1F*)hLGeantID -> Clone("hLGeant1sc_c");
	TH1F *hrealX1 = (TH1F*)hrealX -> Clone("hrealX1_c");
	TH1F *hrealX1sc = (TH1F*)hrealX -> Clone("hrealX1sc_c");
	TH1F *hXGeantID1 = (TH1F*)hXGeantID -> Clone("hXGeantID1_c");
	TH1F *hXGeantID1sc = (TH1F*)hXGeantID -> Clone("hXGeant1sc_c");

	TH1F *clLambdaSc = (TH1F*)hrealL -> Clone("hrealL_chan");
	TH1F *clXiSc = (TH1F*)hrealX -> Clone("hrealX_chan");

      	hLall1sc -> Scale(cr_sec[i]);
	hrealL1sc -> Scale(cr_sec[i]);
	hLGeantID1sc -> Scale(cr_sec[i]);
	hrealX1sc -> Scale(cr_sec[i]);
	hXGeantID1sc -> Scale(cr_sec[i]);

	hLallSum -> Add(hLall1);
	hrealLSum -> Add(hrealL1);
	hLGeantIDSum -> Add(hLGeantID1);
	hrealXSum -> Add(hrealX1);
	hXGeantIDSum -> Add(hXGeantID1);
	
	hLallSumSc -> Add(hLall1sc);
	hrealLSumSc -> Add(hrealL1sc);
	hLGeantIDSumSc -> Add(hLGeantID1sc);
	hrealXSumSc -> Add(hrealX1sc);
	hXGeantIDSumSc -> Add(hXGeantID1sc);

	clLambdaSc -> Scale(cr_sec[i]);
	hLmass_sc -> Add(clLambdaSc);
	clLambdaSc -> SetLineColor(col);	
	
	clXiSc -> Scale(cr_sec[i]);
	hXmass_sc -> Add(clXiSc);
	clXiSc -> SetLineColor(col);	

	//MTD_L, Lmass, MTD_X
	TH1F *hLall1Mtd = (TH1F*)hLallMtd -> Clone("hLall1_cMtd");
	TH1F *hLall1scMtd = (TH1F*)hLallMtd -> Clone("hLall1sc_cMtd");
	TH1F *hrealL1Mtd = (TH1F*)hrealLMtd -> Clone("hrealL1_cMtd");
	TH1F *hrealL1scMtd = (TH1F*)hrealLMtd -> Clone("hrealL1sc_cMtd");
	TH1F *hLGeantID1Mtd = (TH1F*)hLGeantIDMtd -> Clone("hLGeantID1_cMtd");
	TH1F *hLGeantID1scMtd = (TH1F*)hLGeantIDMtd -> Clone("hLGeant1sc_cMtd");
	TH1F *hrealX1Mtd = (TH1F*)hrealXMtd -> Clone("hrealX1_cMtd");
      	TH1F *hrealX1scMtd = (TH1F*)hrealXMtd -> Clone("hrealX1sc_cMtd");
	TH1F *hXGeantID1Mtd = (TH1F*)hXGeantIDMtd -> Clone("hXGeantID1_cMtd");
	TH1F *hXGeantID1scMtd = (TH1F*)hXGeantIDMtd -> Clone("hXGeant1sc_cMtd");

	TH1F *clXiSc_fin = (TH1F*)hrealXMtd -> Clone("hrealXMtd_chan");
	
      	hLall1scMtd -> Scale(cr_sec[i]);
	hrealL1scMtd -> Scale(cr_sec[i]);
	hLGeantID1scMtd -> Scale(cr_sec[i]);
	hrealX1scMtd -> Scale(cr_sec[i]);
	hXGeantID1scMtd -> Scale(cr_sec[i]);

	hLallSumMtd -> Add(hLall1Mtd);
	hrealLSumMtd -> Add(hrealL1Mtd);
	hLGeantIDSumMtd -> Add(hLGeantID1Mtd);
	hrealXSumMtd -> Add(hrealX1Mtd);
	hXGeantIDSumMtd -> Add(hXGeantID1Mtd);

	hLallSumScMtd -> Add(hLall1scMtd);
	hrealLSumScMtd -> Add(hrealL1scMtd);
	hLGeantIDSumScMtd -> Add(hLGeantID1scMtd);
	hrealXSumScMtd -> Add(hrealX1scMtd);
	hXGeantIDSumScMtd -> Add(hXGeantID1scMtd);

	clXiSc_fin -> Scale(cr_sec[i]);
	hXmass_sc_fin -> Add(clXiSc_fin);
	clXiSc_fin -> SetLineColor(col);

	//***************************************************************
	//spectrum Vertz_L
	TH1F *hVertz_Lall1 = (TH1F*)hVertz_Lall -> Clone("hVertz_Lall_c");
	TH1F *hVertz_Lreal1 = (TH1F*)hVertz_Lreal -> Clone("hVertz_Lreal_c");

	//spectrum Vertz_X
	TH1F *hVertz_Xreal1 = (TH1F*)hVertz_Xreal -> Clone("hVertz_Xreal_c");

	hVertz_Lall1 -> Scale(cr_sec[i]);
	hVertz_Lreal1 -> Scale(cr_sec[i]);
	hVertz_Xreal1 -> Scale(cr_sec[i]);

	hVertz_Lall1 -> SetLineColor(col);
	hVertz_Lreal1 -> SetLineColor(col);
	hVertz_Xreal1 -> SetLineColor(col);

	cVertZ_L -> cd(i+1);
	nice_canv1(gPad);
	hVertz_Lall1 -> GetXaxis() -> SetTitle("z [mm]");
	hVertz_Lall1 -> GetYaxis() -> SetRangeUser(0, 20000000);
	hVertz_Lall1 -> Draw();
	hVertz_Lreal1 -> Draw("same");
	ptch -> Draw("same");
	lChan -> AddEntry(hVertz_Lall1, reac[i].c_str());

	cVertZ_X -> cd(i+1);
	nice_canv1(gPad);
	hVertz_Xreal1 -> GetXaxis() -> SetTitle("z [mm]");
	hVertz_Xreal1 -> GetYaxis() -> SetRangeUser(0, 1100000);
	hVertz_Xreal1 -> Draw();
	hVertz_Xreal1 -> Draw("same");
	ptch -> Draw("same");


	//spectrum MTD_L
	TH1F *hMTD_Lall1 = (TH1F*)hMTD_Lall -> Clone("hMTD_Lall_c");
	TH1F *hMTD_Lreal1 = (TH1F*)hMTD_Lreal -> Clone("hMTD_Lreal_c");

	//spectrum MTD_X
	TH1F *hMTD_Xreal1 = (TH1F*)hMTD_Xreal -> Clone("hMTD_Xreal_c");

	hMTD_Lall1 -> Scale(cr_sec[i]);
	hMTD_Lreal1 -> Scale(cr_sec[i]);
	hMTD_Xreal1 -> Scale(cr_sec[i]);

	hMTD_Lall1 -> SetLineColor(col);
	hMTD_Lreal1 -> SetLineColor(col);
	hMTD_Xreal1 -> SetLineColor(col);

	cMTDL -> cd(1);
	gPad->SetLogy();
	hMTD_Lall1 -> GetYaxis() -> SetRangeUser(100, 5000000000);
	hMTD_Lall1 -> SetTitle("MTD_L: all Lambda candidates");
	hMTD_Lall1 -> GetXaxis() -> SetTitle("MTD_L [mm]");
	hMTD_Lall1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hMTD_Lall1 -> Draw("same");
	cMTDL -> cd(2);
	gPad->SetLogy();
	hMTD_Lreal1 -> GetYaxis() -> SetRangeUser(100, 5000000000);
	hMTD_Lreal1 -> SetTitle("MTD_L: real Lambda");
	hMTD_Lreal1 -> GetXaxis() -> SetTitle("MTD [mm]");
	hMTD_Lreal1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hMTD_Lreal1 -> Draw("same");

	cMTDX -> cd(2);
	gPad->SetLogy();
	hMTD_Xreal1 -> GetYaxis() -> SetRangeUser(1, 10000000);
	hMTD_Xreal1 -> SetTitle("MTD_X: real Xi");
	hMTD_Xreal1 -> GetXaxis() -> SetTitle("MTD_X [mm]");
	hMTD_Xreal1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hMTD_Xreal1 -> Draw("same");
	
	cVERTL -> cd(1);
	gPad->SetLogy();
	hVertz_Lall1 -> GetYaxis() -> SetRangeUser(100, 50000000);
	hVertz_Lall1 -> SetTitle("VERTz_L: all Lambda candidates");
	hVertz_Lall1 -> GetXaxis() -> SetTitle("VERTz_L [mm]");
	hVertz_Lall1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertz_Lall1 -> Draw("same");
	hLVertex_allSum -> Add(hVertz_Lall1);
	cVERTL -> cd(2);
	gPad->SetLogy();
	hVertz_Lreal1 -> GetYaxis() -> SetRangeUser(100, 50000000);
	hVertz_Lreal1 -> SetTitle("VERTz_L: real Lambda");
	hVertz_Lreal1 -> GetXaxis() -> SetTitle("VERTz_L [mm]");
	hVertz_Lreal1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertz_Lreal1 -> Draw("same");
	hLVertex_sigSum -> Add(hVertz_Lreal1);

	gPad->SetLogy();
	hVertz_Xreal1 -> GetYaxis() -> SetRangeUser(10, 5000000);
	hVertz_Xreal1 -> SetTitle("VERTz_X: real Xi");
	hVertz_Xreal1 -> GetXaxis() -> SetTitle("VERTz_X [mm]");
	hVertz_Xreal1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertz_Xreal1 -> Draw("same");
	hXVertex_sigSum -> Add(hVertz_Xreal1);
	

	//MTD_L, Lmass, MTD_X, Vertz_X
	TH1F *hLall1Vert = (TH1F*)hLallVert -> Clone("hLall1_cVert");
	TH1F *hLall1scVert = (TH1F*)hLallVert -> Clone("hLall1sc_cVert");
	TH1F *hrealL1Vert = (TH1F*)hrealLVert -> Clone("hrealL1_cVert");
	TH1F *hrealL1scVert = (TH1F*)hrealLVert -> Clone("hrealL1sc_cVert");
	TH1F *hLGeantID1Vert = (TH1F*)hLGeantIDVert -> Clone("hLGeantID1_cVert");
	TH1F *hLGeantID1scVert = (TH1F*)hLGeantIDVert -> Clone("hLGeantID1sc_cVert");

	TH1F *hrealX1Vert = (TH1F*)hrealXVert -> Clone("hrealX1_cVert");
	TH1F *hrealX1scVert = (TH1F*)hrealXVert -> Clone("hrealX1sc_cVert");
	TH1F *hXGeantID1Vert = (TH1F*)hXGeantIDVert -> Clone("hXGeantID1_cVert");
	TH1F *hXGeantID1scVert = (TH1F*)hXGeantIDVert -> Clone("hXGeantID1sc_cVert");
	
        TH1F *clLambdaScVertrec = (TH1F*)hrealLVert -> Clone("hrealLVert_chan");
	
      	hLall1scVert -> Scale(cr_sec[i]);
	hrealL1scVert -> Scale(cr_sec[i]);
	hLGeantID1scVert -> Scale(cr_sec[i]);
	hrealX1scVert -> Scale(cr_sec[i]);
	hXGeantID1scVert -> Scale(cr_sec[i]);

	hLallSumVert -> Add(hLall1Vert);
	hrealLSumVert -> Add(hrealL1Vert);
	hLGeantIDSumVert -> Add(hLGeantID1Vert);
	hrealXSumVert -> Add(hrealX1Vert);
	hXGeantIDSumVert -> Add(hXGeantID1Vert);

	hLallSumScVert -> Add(hLall1scVert);
	hrealLSumScVert -> Add(hrealL1scVert);
	hLGeantIDSumScVert -> Add(hLGeantID1scVert);
	hrealXSumScVert -> Add(hrealX1scVert);
	hXGeantIDSumScVert -> Add(hXGeantID1scVert);

	clLambdaScVertrec -> Scale(cr_sec[i]);
	hLmass_sc_rec -> Add(clLambdaScVertrec);
	clLambdaScVertrec -> SetLineColor(col);

	//*******************************************************

	if(i == 0){
	  //no cuts
	  hLall90 = (TH1F*)hLall1 -> Clone("hLall90");
	  hrealL90 = (TH1F*)hrealL1 -> Clone("hrealL90");
	  hrealX90 = (TH1F*)hrealX1 -> Clone("hrealX90");
	
	  hLall90Sc = (TH1F*)hLall1sc -> Clone("hLall90Sc");
	  hrealL90Sc = (TH1F*)hrealL1sc -> Clone("hrealL90Sc");
	  hrealX90Sc = (TH1F*)hrealX1sc -> Clone("hrealX90Sc");

	  hLall90 -> SetLineColor(kBlack);
	  hrealL90 -> SetLineColor(kBlack);
	  hrealX90 -> SetLineColor(kBlack);
	
	  hLall90Sc -> SetLineColor(kBlack);
	  hrealL90Sc -> SetLineColor(kBlack);
	  hrealX90Sc -> SetLineColor(kBlack);

	  clLambdaSc -> SetLineWidth(2);
	  clXiSc -> SetLineWidth(2);
	  
	  //MTD_L, Lmass, MTD_X
	  hLall90Mtd = (TH1F*)hLall1Mtd -> Clone("hLall90Mtd");
	  hrealL90Mtd = (TH1F*)hrealL1Mtd -> Clone("hrealL90Mtd");
	  hrealX90Mtd = (TH1F*)hrealX1Mtd -> Clone("hrealX90Mtd");
	
	  hLall90ScMtd = (TH1F*)hLall1scMtd -> Clone("hLall90ScMtd");
	  hrealL90ScMtd = (TH1F*)hrealL1scMtd -> Clone("hrealL90ScMtd");
	  hrealX90ScMtd = (TH1F*)hrealX1scMtd -> Clone("hrealX90ScMtd");

	  hLall90Mtd -> SetLineColor(kBlack);
	  hrealL90Mtd -> SetLineColor(kBlack);
	  hrealX90Mtd -> SetLineColor(kBlack);
	
	  hLall90ScMtd -> SetLineColor(kBlack);
	  hrealL90ScMtd -> SetLineColor(kBlack);
	  hrealX90ScMtd -> SetLineColor(kBlack);

	  clXiSc_fin -> SetLineWidth(2);
	  	  
	  //MTD_L, Lmass, MTD_X, Vertz_X
	  hLall90Vert = (TH1F*)hLall1Vert -> Clone("hLall90Vert");
	  hrealL90Vert = (TH1F*)hrealL1Vert -> Clone("hrealL90Vert");
	  hrealX90Vert = (TH1F*)hrealX1Vert -> Clone("hrealX90Vert");
	
	  hLall90ScVert = (TH1F*)hLall1scVert -> Clone("hLall90ScVert");
	  hrealL90ScVert = (TH1F*)hrealL1scVert -> Clone("hrealL90ScVert");
	  hrealX90ScVert = (TH1F*)hrealX1scVert -> Clone("hrealX90ScVert");

	  hLall90Vert -> SetLineColor(kBlack);
	  hrealL90Vert -> SetLineColor(kBlack);
	  hrealX90Vert -> SetLineColor(kBlack);
	
	  hLall90ScVert -> SetLineColor(kBlack);
	  hrealL90ScVert -> SetLineColor(kBlack);
	  hrealX90ScVert -> SetLineColor(kBlack);

          clLambdaScVertrec -> SetLineWidth(2);

	  nallX += ninch;
	  cout << "nallX1=" << nallX << endl;
	}
	if(i!=1 &&  i!=6){
	    nallL += ninch;
	    cout << "nallL1=" << nallL << endl;
	}


    }//***********************************************************************************
    //no cuts
    //Lambda1115
    double MassminL;// = 1105;
    double MassmaxL;// = 1125;
    double massL, massLSc;
    int nL = hrealLSum -> GetNbinsX();
    int nLSc = hrealLSumSc -> GetNbinsX();

    double s_bg_vL[150];
    double binL[150]; 
    int kL = -1;
    double s_bg_vLSc[150];
    double binLSc[150];
    int kLSc = -1;

    hLGeantIDSum -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealLSum -> GetXaxis() -> FindBin(m3sigma);
    b = hrealLSum -> GetXaxis() -> FindBin(p3sigma);
    MassminL = m3sigma;
    MassmaxL = p3sigma;
    
    for(int j = 1; j <= nL; j++){
      massL = hrealLSum -> GetBinLowEdge(j);
      if(massL < MassminL) continue;
      else if(massL > MassmaxL) break;
      else{
	  //hrealLSumPeak -> SetBinContent(j, hrealLSum -> GetBinContent(j));
	hLGeantIDPeak -> SetBinContent(j, hLGeantIDSum -> GetBinContent(j));
      }
    }

    hLGeantIDSumSc -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealLSumSc -> GetXaxis() -> FindBin(m3sigma);
    b = hrealLSumSc -> GetXaxis() -> FindBin(p3sigma);
    MassminL = m3sigma;
    MassmaxL = p3sigma;
    for(int j = 1; j <= nLSc; j++){
      massLSc = hrealLSumSc -> GetBinLowEdge(j);
      if(massLSc < MassminL) continue;
      else if(massLSc > MassmaxL) break;
      else{
	  //hrealLSumPeakSc -> SetBinContent(j, hrealLSumSc -> GetBinContent(j));
	  hLGeantIDScPeak -> SetBinContent(j, hLGeantIDSumSc -> GetBinContent(j));
      }
    }
//    TH1F *hrealLSumPeakCl = (TH1F*)hrealLSumPeak -> Clone();
//    TH1F *hrealLSumPeakScCl = (TH1F*)hrealLSumPeakSc -> Clone();

//    hLallSumBG -> Add(hrealLSum, hrealLSumPeakCl, 1, -1); 
//    hLallSumBGSc -> Add(hrealLSumSc, hrealLSumPeakScCl, 1, -1); 
//    hrealLSumBG -> Add(hrealLSum, hLGeantIDPeak, 1, -1);
//    hrealLSumBGSc -> Add(hrealLSumSc, hLGeantIDScPeak, 1, -1);

    //BG subtr.
    float BGpar = 6;
/*    TString nameL = "hrealLSumCl";
    TString nameLsc = "hrealLSumScCl";
    TH1F *hrealLSumCl = (TH1F*)hrealLSum -> Clone();
    TH1F *hrealLSumScCl = (TH1F*)hrealLSumSc -> Clone();
    hrealLSumCl -> SetName(nameL);
    hrealLSumScCl -> SetName(nameLsc);
    hrealLSumCl -> ShowBackground(BGpar);
    hrealLSumScCl -> ShowBackground(BGpar);
    TString bg = "_background";
    TString nameLbg = nameL + bg;
    TString nameLscbg = nameLsc + bg;
    hrealLSumBG = (TH1F*)gDirectory -> Get(nameLbg);
    hrealLSumBGSc = (TH1F*)gDirectory -> Get(nameLscbg);
    hrealLSumPeak -> Add(hrealLSumCl, hrealLSumBG, 1, -1);
    hrealLSumPeakSc -> Add(hrealLSumScCl, hrealLSumBGSc, 1, -1);
*/
    
    TString nameL = "hrealLSumCl";
    TH1F *hrealLSumCl = (TH1F*)hrealLSum -> Clone();
    TString bg = "_background";
    cout << ">>>>>>>>fit lno<<<<<<<<<" << endl;
    TF1 * ffL = new TF1("ffL", "gaus(0)+gaus(3)+pol2(6)", 1080,1190);
    ffL -> SetParameters(
	2984560,1114.29,4.12196,
	8.78103e+06,1.11469e+03,1.95058,
	-4.32460e+09,7.51569e+06,-3.25342e+03,1,1);
    ffL -> SetParLimits(0, 0, 100000000);
    ffL -> SetParLimits(1, 1110, 1120);
    ffL -> SetParLimits(2, 0, 10);
    ffL -> SetParLimits(3, 0, 100000000);
    ffL -> SetParLimits(4, 1110, 1120);
    ffL -> SetParLimits(5, 0, 10);
    hrealLSumCl -> Fit("ffL", "", "", 1090, 1140);
    hrealLSumCl -> SetName(nameL);
    TF1 * ffLsig = new TF1("ffLsig", "gaus(0)+gaus(3)", 1070,1200);
    TString nameLbg = nameL + bg;
    TF1 * ffLbg = new TF1("ffLbg", "pol2(0)", 1090,1140);
    double par[12];
    ffL -> GetParameters(par);
    ffLsig -> SetParameters(par);
    ffLsig -> Draw("same");
    ffLbg -> SetParameters(&par[6]);
    ffLbg -> Draw("same");

    hrealLSumBG = (TH1F*)hrealLSumCl -> Clone("hrealLSumBG");
    hrealLSumBG -> Add(ffLsig, -1);

    hrealLSumPeak = (TH1F*)hrealLSumCl -> Clone("hrealLSumPeak");
    hrealLSumPeak -> Add(hrealLSumBG, -1);
     
    //scaled
    TString nameLsc = "hrealLSumScCl";
    TH1F *hrealLSumScCl = (TH1F*)hrealLSumSc -> Clone();
    cout << ">>>>>>>>fitlss<<<<<<<<<" << endl;
    TF1 * ffLsc = new TF1("ffLsc", "gaus(0)+gaus(3)+pol2(6)", 1080,1190);
    ffLsc -> SetParameters(
	2984560,1114.29,4.12196,
	8.78103e+06,1.11469e+03,1.95058,
	-4.32460e+09,7.51569e+06,-3.25342e+03,1,1);
    ffLsc -> SetParLimits(0, 0, 100000000);
    ffLsc -> SetParLimits(1, 1110, 1120);
    ffLsc -> SetParLimits(2, 0, 10);
    ffLsc -> SetParLimits(3, 0, 100000000);
    ffLsc -> SetParLimits(4, 1110, 1120);
    ffLsc -> SetParLimits(5, 0, 10);
    hrealLSumScCl -> Fit("ffLsc", "", "", 1090, 1140);
    hrealLSumScCl -> SetName(nameLsc);
    TF1 * ffLsigsc = new TF1("ffLsigsc", "gaus(0)+gaus(3)", 1070,1200);
    TString nameLscbg = nameLsc + bg;
    TF1 * ffLbgsc = new TF1("ffLbgsc", "pol2(0)", 1090,1140);
    par[12] = 0;
    ffLsc -> GetParameters(par);
    ffLsigsc -> SetParameters(par);
    ffLsigsc -> Draw("same");
    ffLbgsc -> SetParameters(&par[6]);
    ffLbgsc -> Draw("same");

    hrealLSumBGSc = (TH1F*)hrealLSumScCl -> Clone("hrealLSumBGSc");
    hrealLSumBGSc -> Add(ffLsigsc, -1);
    
    hrealLSumPeakSc = (TH1F*)hrealLSumScCl -> Clone("hrealLSumPeakSc");
    hrealLSumPeakSc -> Add(hrealLSumBGSc, -1);  
    //end BG subtr.
    
    hrealLSumBG -> SetLineColor(kRed);
    hrealLSumBGSc -> SetLineColor(kRed);
    hrealLSum -> SetLineColor(8);
    hrealLSumSc -> SetLineColor(8);
    hLGeantIDSum -> SetLineColor(1);
    hLGeantIDSumSc -> SetLineColor(1);
    hrealLSumPeak -> SetLineColor(6);
    hrealLSumPeakSc -> SetLineColor(6);
	
    cntSL = hrealLSumPeak -> Integral(a,b);
    cntSLGeant = hLGeantIDSum -> Integral(a,b);
    cntBL = hrealLSumBG -> Integral(a,b);
    cntSLsc = hrealLSumPeakSc -> Integral(a,b);
    cntSLscGeant = hLGeantIDSumSc -> Integral(a,b);
    cntBLsc = hrealLSumBGSc -> Integral(a,b);

    for(int j = 1; j <= nL; j++){
      if(hrealLSumPeak -> GetBinContent(j)){
	kL++;
	s_bg_vL[kL] = (hrealLSumPeak -> GetBinContent(j))/(hrealLSumBG -> GetBinContent(j));
	binL[kL] = (hrealLSumPeak -> GetBinLowEdge(j)) + (hrealLSumPeak -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nLSc; j++){
      if(hrealLSumPeakSc -> GetBinContent(j)){
	kLSc++;
	s_bg_vLSc[kLSc] = (hrealLSumPeakSc -> GetBinContent(j))/(hrealLSumBGSc -> GetBinContent(j));
	binLSc[kLSc] = (hrealLSumPeakSc -> GetBinLowEdge(j)) + (hrealLSumPeakSc -> GetBinWidth(j));
      }
    }

    //Xi
    double MassminX;// = 1305;
    double MassmaxX;// = 1335;
    double massX, massXSc;
    int nX = hrealXSum -> GetNbinsX();
    int nXSc = hrealXSumSc -> GetNbinsX();

    double s_bg_vX[150];
    double binX[150]; 
    int kX = -1;
    double s_bg_vXSc[150];
    double binXSc[150];
    int kXSc = -1;

    hXGeantIDSum -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealXSum -> GetXaxis() -> FindBin(m3sigma);
    b = hrealXSum -> GetXaxis() -> FindBin(p3sigma);
    MassminX = m3sigma;
    MassmaxX = p3sigma;

    for(int j = 1; j <= nX; j++){
      massX = hrealXSum -> GetBinLowEdge(j);
      if(massX < MassminX) continue;
      else if(massX > MassmaxX) break;
      else{
//	  hrealXSumPeak -> SetBinContent(j, hrealXSum -> GetBinContent(j));
	  hXGeantIDPeak -> SetBinContent(j, hXGeantIDSum -> GetBinContent(j));
      }
    }
    hXGeantIDSumSc -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealXSumSc -> GetXaxis() -> FindBin(m3sigma);
    b = hrealXSumSc -> GetXaxis() -> FindBin(p3sigma);
    MassminX = m3sigma;
    MassmaxX = p3sigma;
    for(int j = 1; j <= nXSc; j++){
	massXSc = hrealXSumSc -> GetBinLowEdge(j);
	if(massXSc < MassminX) continue;
	else if(massXSc > MassmaxX) break;
	else{
//	    hrealXSumPeakSc -> SetBinContent(j, hrealXSumSc -> GetBinContent(j));
	    hXGeantIDScPeak -> SetBinContent(j, hXGeantIDSumSc -> GetBinContent(j));
	}
    }

//    TH1F *hrealXSumPeakCl = (TH1F*)hrealXSumPeak -> Clone();
//    TH1F *hrealXSumPeakScCl = (TH1F*)hrealXSumPeakSc -> Clone();

//    hXallSumBG -> Add(hrealXSum, hrealXSumPeakCl, 1, -1); 
//    hXallSumBGSc -> Add(hrealXSumSc, hrealXSumPeakScCl, 1, -1); 
//    hrealXSumBG -> Add(hrealXSum, hXGeantIDPeak, 1, -1); 
//    hrealXSumBGSc -> Add(hrealXSumSc, hXGeantIDScPeak, 1, -1); 

    //BG subtr.
    TString nameX = "hrealXSumCl";
    TH1F *hrealXSumCl = (TH1F*)hrealXSum -> Clone();
    cout << ">>>>>>>>fit Xno<<<<<<<<<" << endl;
    TF1 * ffX = new TF1("ffX", "gaus(0)+gaus(3)+pol5(6)", 1280,1360);
    ffX -> SetParameters(
	3.73999e+05,1.31872e+03,4.05039,
	2.78539e+04,1.31000e+03,9,
	-2.85281e+07,1.64862e+04,1.59317e+01,-3.03469e-03,-4.53008e-06);
    ffX -> SetParLimits(0, 0, 100000000);
    ffX -> SetParLimits(1, 1310, 1330);
    ffX -> SetParLimits(2, 0, 9);
    ffX -> SetParLimits(3, 0, 100000000);
    ffX -> SetParLimits(4, 1310, 1330);
    ffX -> SetParLimits(5, 0, 9);
    hrealXSumCl -> Fit("ffX", "", "", 1280, 1365);
    hrealXSumCl -> SetName(nameX);
    TF1 * ffXsig = new TF1("ffXsig", "gaus(0)+gaus(3)", 1280,1360);
    TString nameXbg = nameX + bg;
    TF1 * ffXbg = new TF1("ffXbg", "pol5(0)", 1280,1360);
    double par[12];
    ffX -> GetParameters(par);
    ffXsig -> SetParameters(par);
    ffXsig -> Draw("same");
    ffXbg -> SetParameters(&par[6]);
    ffXbg -> Draw("same");

    hrealXSumBG = (TH1F*)hrealXSumCl -> Clone("hrealXSumBG");
    hrealXSumBG -> Add(ffXsig, -1);

    hrealXSumPeak = (TH1F*)hrealXSumCl -> Clone("hrealXSumPeak");
    hrealXSumPeak -> Add(hrealXSumBG, -1);

    //scaled
    TString nameXsc = "hrealXSumScCl";
    TH1F *hrealXSumScCl = (TH1F*)hrealXSumSc -> Clone();
    cout << ">>>>>>>>fit Xscno<<<<<<<<<" << endl;
    TF1 * ffXsc = new TF1("ffXsc", "gaus(0)+gaus(3)+pol5(6)", 1280,1360);
    ffXsc -> SetParameters(
	3.73999e+05,1.31872e+03,4.05039,
	2.78539e+04,1.31000e+03,9,
	-2.85281e+07,1.64862e+04,1.59317e+01,-3.03469e-03,-4.53008e-06);
//pol4:
//	3.43758e+05,1.31861e+03,3.84611, 
//	6.36039e+04,1.31822e+03,9,
//	-1.44681e+07,1.12006e+04,7.94111e+00,-6.04656e-03);
    ffXsc -> SetParLimits(0, 0, 100000000);
    ffXsc -> SetParLimits(1, 1310, 1330);
    ffXsc -> SetParLimits(2, 0, 9);
    ffXsc -> SetParLimits(3, 0, 100000000);
    ffXsc -> SetParLimits(4, 1310, 1330);
    ffXsc -> SetParLimits(5, 0, 9);
    hrealXSumScCl -> Fit("ffXsc", "", "", 1280, 1365);
    hrealXSumScCl -> Fit("ffXsc", "", "", 1280, 1365);
    hrealXSumScCl -> SetName(nameXsc);
    TF1 * ffXsigsc = new TF1("ffXsigsc", "gaus(0)+gaus(3)", 1280,1360);
    TString nameXscbg = nameXsc + bg;
    TF1 * ffXbgsc = new TF1("ffXbgsc", "pol5(0)", 1280,1360);
    double parX[12];
    ffXsc -> GetParameters(parX);
    ffXsigsc -> SetParameters(parX);
    ffXsigsc -> Draw("same");
    ffXbgsc -> SetParameters(&parX[6]);
    ffXbgsc -> Draw("same");

    hrealXSumBGSc = (TH1F*)hrealXSumScCl -> Clone("hrealXSumBGSc");
    hrealXSumBGSc -> Add(ffXsigsc, -1);

    hrealXSumPeakSc = (TH1F*)hrealXSumScCl -> Clone("hrealXSumPeakSc");
    hrealXSumPeakSc -> Add(hrealXSumBGSc, -1);
    //end BG subtr.       
    
    hrealXSumBG -> SetLineColor(kRed);
    hrealXSumBGSc -> SetLineColor(kRed);
    hrealXSum -> SetLineColor(8);
    hrealXSumSc -> SetLineColor(8);
    hXGeantIDSum -> SetLineColor(1);
    hXGeantIDSumSc -> SetLineColor(1);
    hrealXSumPeak -> SetLineColor(6);
    hrealXSumPeakSc -> SetLineColor(6);
   
    cntSX = hrealXSumPeak -> Integral(a,b);
    cntSXGeant = hXGeantIDSum -> Integral(a,b);
    cntBX = hrealXSumBG -> Integral(a,b);
    cntSXsc = hrealXSumPeakSc -> Integral(a,b);
    cntSXscGeant = hXGeantIDSumSc -> Integral(a,b);
    cntBXsc = hrealXSumBGSc -> Integral(a,b);

    for(int j = 1; j <= nX; j++){
      if(hrealXSumPeak -> GetBinContent(j)){
	kX++;
	s_bg_vX[kX] = (hrealXSumPeak -> GetBinContent(j))/(hrealXSumBG -> GetBinContent(j));
	binX[kX] = (hrealXSumPeak -> GetBinLowEdge(j)) + (hrealXSumPeak -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nXSc; j++){
      if(hrealXSumPeakSc -> GetBinContent(j)){
	kXSc++;
	s_bg_vXSc[kXSc] = (hrealXSumPeakSc -> GetBinContent(j))/(hrealXSumBGSc -> GetBinContent(j));
	binXSc[kXSc] = (hrealXSumPeakSc -> GetBinLowEdge(j)) + (hrealXSumPeakSc -> GetBinWidth(j));
      }
    }

    l1 -> AddEntry(hrealLSumSc, "sum all ch. (#pi^{-}p)", "L");
    l1 -> AddEntry(hrealLSumPeakSc, "peak=all-BG", "L");
    l1 -> AddEntry(hLGeantIDSumSc, "real #Lambda - GeantID", "L");
    l1 -> AddEntry(hrealLSumBGSc, "BG", "L");

    l2 -> AddEntry(hrealXSumSc, "sum all ch. (2#pi^{-}p)", "L");
    l2 -> AddEntry(hrealXSumPeakSc, "peak=all-BG", "L");
    l2 -> AddEntry(hXGeantIDSumSc, "real #Xi^{-} - GeantID", "L");
    l2 -> AddEntry(hrealXSumBGSc, "BG", "L");
    
     //invM no scaling
    cLambdaXiMass -> cd(1);
    nice_canv1(gPad);
    hLallSum -> SetTitle("#pi^{-} in Hades + anything in FD (all,real,90)");
    hLallSum -> GetXaxis() -> SetTitle("M_{FD#pi^{-}} [MeV]");
    hLallSum -> GetYaxis() -> SetTitle("counts");
    hLallSum -> Draw();
    hrealLSum -> Draw("same");
    hrealL90 -> Draw("same");
//    l1 -> Draw("same");

    cLambdaXiMass -> cd(2);
    nice_canv1(gPad);
    hLallSumBG -> SetTitle("p#pi^{-}: all, peak and BG");
    hLallSumBG -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumBG -> GetYaxis() -> SetTitle("counts");
    hLallSum -> Draw();
    hrealLSumPeak -> Draw("same");
    hLallSumBG -> Draw("same");
//    l1a -> Draw("same");
    
    cLambdaXiMass -> cd(3);
    nice_canv1(gPad);
    hrealLSumBG -> SetTitle("p#pi^{-}: real, Geant and BG");
    hrealLSumBG -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBG -> GetYaxis() -> SetTitle("counts");
    hrealLSum -> Draw();
    hLGeantIDSum -> Draw("same");
    hrealLSumBG -> Draw("same");
//    l1a -> Draw("same");
    
    cLambdaXiMass -> cd(4);
    nice_canv1(gPad);
    hrealXSumBG -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBG -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBG -> GetYaxis() -> SetTitle("counts");
    hrealXSum -> Draw();
    hXGeantIDSum -> Draw("same");
    hrealXSumBG -> Draw("same");

    cLambdaXiMass -> cd(6);
    l1 -> Draw();
    l2 -> Draw("same");

    //
    TLine *massL_min = new TLine(MassminL, 0, MassminL, 80000000);
    TLine *massL_max = new TLine(MassmaxL, 0, MassmaxL, 80000000);
    TLine *massX_min = new TLine(MassminX, 0, MassminX, 16000000);
    TLine *massX_max = new TLine(MassmaxX, 0, MassmaxX, 16000000);
    massL_min -> SetLineWidth(2);
    massL_max -> SetLineWidth(2);
    massX_min -> SetLineWidth(2);
    massX_max -> SetLineWidth(2);
    massL_min -> SetLineColor(kRed);
    massL_max -> SetLineColor(kRed);
    massX_min -> SetLineColor(kRed);
    massX_max -> SetLineColor(kRed);
    
    TLegend *lfin = new TLegend(.2,.5,.35,.8);
    
    TCanvas *cimLNoCutsSc = new TCanvas("cimLNoCutsSc","cimLNoCutsSc", 1000, 800); //inv mass Lambda spectrum, no cuts, cr sec scaling
    TCanvas *cimXMtdlVertlMlSc = new TCanvas("cimXMtdlVerlMlSc","cimXMtdlVerlMlSc", 1000, 800); //inv mass Xi spectrum, MTD_L, VERTz_L, Lmass cuts, cr sec scaling
    //>>>>>>>>>>>>>>>>>
    cLambdaXiMassSc -> cd(1);
    nice_canv1(gPad);
    hLallSumSc -> SetTitle("#pi^{-} in Hades + anything in FD (all,real,90)");
    hLallSumSc -> GetXaxis() -> SetTitle("M_{FD#pi^{-}} [MeV]");
    hLallSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumSc -> Draw();
    hrealLSumSc -> Draw(" same");
    hrealL90Sc -> Draw(" same");
//    l1 -> Draw("same");
    
    cLambdaXiMassSc -> cd(2);
    nice_canv1(gPad);
    hLallSumBGSc -> SetTitle("p#pi^{-}: all, peak and BG");
    hLallSumBGSc -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumSc -> Draw();
    hrealLSumPeakSc -> Draw("same");
    hLallSumBGSc -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassSc -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGSc -> SetTitle("p#pi^{-}: real, Geant and BG");
    hrealLSumBGSc -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumSc -> Draw();
    hLGeantIDSumSc -> Draw("same");
    hrealLSumBGSc -> Draw("same");
//    l1a -> Draw("same");
    
    cimLNoCutsSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealLSumSc -> SetTitle("#Lambda reconstruction, no cuts");
    hrealLSumSc -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
//    hrealLSumSc -> SetLineColor(40);
//    hLallSumSc -> SetLineStyle(2);
//    hLallSumSc -> SetLineWidth(2);
//    hrealLSumSc -> SetLineColor(46);
//    hrealLSumSc -> SetLineStyle(2);
    hrealLSumSc -> SetLineWidth(2);
    hrealLSumBGSc -> SetMarkerStyle(21);
    hrealLSumBGSc -> SetMarkerSize(.5);
    hrealLSumBGSc -> SetMarkerColor(2);
//    hrealLSumPeakSc -> SetLineColor(8);
//    hLGeantIDScPeak -> SetLineColor(1);
//    hLallSumSc -> Draw();
    hrealLSumSc -> Draw();
    hrealLSumPeakSc -> Draw("same");
    hrealLSumBGSc -> Draw("p same");
    hLGeantIDSumSc -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");
    
//    lfin -> AddEntry(hLallSumSc, "sum all ch. (#pi^{-}-FD)");
    lfin -> AddEntry(hrealLSumSc, "sum all ch. (#pi^{-}p)");
    lfin -> AddEntry(hrealLSumBGSc, "BG");
    lfin -> AddEntry(hrealLSumPeakSc, "peak=all-BG");
    lfin -> AddEntry(hLGeantIDSumSc, "real #Lambda");
    lfin -> Draw("same");//<<<<<<<<<<<<<<

    cLambdaXiMassSc -> cd(4);
    nice_canv1(gPad);
    hrealXSumBGSc -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> Draw();
    hXGeantIDSumSc -> Draw("same");
    hrealXSumBGSc -> Draw("same");

    cLambdaXiMassSc -> cd(6);
    l1 -> Draw();
    l2 -> Draw("same");
    

    TLegend *lfin1 = new TLegend(.2,.5,.35,.8);

    cimXMtdlVertlMlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass cuts");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
//    hrealXSumSc -> SetLineColor(46);
//    hrealXSumSc -> SetLineStyle(2);
    hrealXSumSc -> SetLineWidth(2);
    hrealXSumBGSc -> SetMarkerStyle(21);
    hrealXSumBGSc -> SetMarkerSize(.5);
    hrealXSumBGSc -> SetMarkerColor(2);
    //  hrealXSumPeakSc -> SetLineColor(8);
//    hXGeantIDSumSc -> SetLineColor(1);
    hrealXSumSc -> Draw();
    hrealXSumPeakSc -> Draw("same");
    hrealXSumBGSc -> Draw("p same");
    hXGeantIDSumSc -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");

    lfin1 -> AddEntry(hrealXSumSc, "sum all ch. (#Lambda#pi^{-})");
    lfin1 -> AddEntry(hrealXSumBGSc, "BG");
    lfin1 -> AddEntry(hrealXSumPeakSc, "peak=all-BG");
    lfin1 -> AddEntry(hXGeantIDSumSc, "real #Xi^{-}");
    lfin1 -> Draw("same");//<<<<<<<<<<<<<<


    //MTD_L, Lmass, MTD_X
    //Lambda1115
    int nLMtd = hrealLSumMtd -> GetNbinsX();
    int nLScMtd = hrealLSumScMtd -> GetNbinsX();

    double s_bg_vLMtd[150];
    double binLMtd[150]; 
    int kLMtd = -1;
    double s_bg_vLScMtd[150];
    double binLScMtd[150]; 
    int kLScMtd = -1;

    hLGeantIDSumMtd -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealLSumMtd -> GetXaxis() -> FindBin(m3sigma);
    b = hrealLSumMtd -> GetXaxis() -> FindBin(p3sigma);	 
    MassminL = m3sigma;
    MassmaxL = p3sigma;
    for(int j = 1; j <= nLMtd; j++){
      massL = hrealLSumMtd -> GetBinLowEdge(j);
      if(massL < MassminL) continue;
      else if(massL > MassmaxL) break;
      else{
//	hrealLSumPeakMtd -> SetBinContent(j, hrealLSumMtd -> GetBinContent(j));
	hLGeantIDMtdPeak -> SetBinContent(j, hLGeantIDSumMtd -> GetBinContent(j));
      }
    }
    hLGeantIDSumScMtd -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealLSumScMtd -> GetXaxis() -> FindBin(m3sigma);
    b = hrealLSumScMtd -> GetXaxis() -> FindBin(p3sigma);
    MassminL = m3sigma;
    MassmaxL = p3sigma;
    for(int j = 1; j <= nLScMtd; j++){
      massLSc = hrealLSumScMtd -> GetBinLowEdge(j);
      if(massLSc < MassminL) continue;
      else if(massLSc > MassmaxL) break;
      else{
//	  hrealLSumPeakScMtd -> SetBinContent(j, hrealLSumScMtd -> GetBinContent(j));
	  hLGeantIDScMtdPeak -> SetBinContent(j, hLGeantIDSumScMtd -> GetBinContent(j));
      }
    }

//  TH1F *hrealLSumPeakClMtd = (TH1F*)hrealLSumPeakMtd -> Clone();
//    TH1F *hrealLSumPeakScClMtd = (TH1F*)hrealLSumPeakScMtd -> Clone();
    
//   hLallSumBGMtd -> Add(hLallSumMtd, hrealLSumPeakClMtd, 1, -1);
//   hLallSumBGScMtd -> Add(hLallSumScMtd, hrealLSumPeakScClMtd, 1, -1); 
//    hrealLSumBGMtd -> Add(hrealLSumMtd, hLGeantIDMtdPeak, 1, -1); 
//   hrealLSumBGScMtd -> Add(hrealLSumScMtd, hLGeantIDScMtdPeak, 1, -1); 
    ctmp -> cd();
    //BG subtr.                                                                          
    TString nameLMtd = "hrealLSumMtdCl";
    TH1F *hrealLSumMtdCl = (TH1F*)hrealLSumMtd -> Clone();
    cout << ">>>>>>>>fit lmtd<<<<<<<<<" << endl;
    TF1 * ffLmtd = new TF1("ffLmtd", "gaus(0)+gaus(3)+pol2(6)", 1080,1190);
    ffLmtd -> SetParameters(
	2984560,1114.29,4.12196,
	8.78103e+06,1.11469e+03,1.95058,
	-4.32460e+09,7.51569e+06,-3.25342e+03,1,1);
    ffLmtd -> SetParLimits(0, 0, 100000000);
    ffLmtd -> SetParLimits(1, 1110, 1120);
    ffLmtd -> SetParLimits(2, 0, 10);
    ffLmtd -> SetParLimits(3, 0, 100000000);
    ffLmtd -> SetParLimits(4, 1110, 1120);
    ffLmtd -> SetParLimits(5, 0, 10);
    hrealLSumMtdCl -> Fit("ffLmtd", "", "", 1090, 1140);
    hrealLSumMtdCl -> SetName(nameLMtd);
    TF1 * ffLmtdsig = new TF1("ffLmtdsig", "gaus(0)+gaus(3)", 1070,1200);
    TString nameLmtdbg = nameLMtd + bg;
    TF1 * ffLmtdbg = new TF1("ffLmtdbg", "pol2(0)", 1090,1140);
    par[12] = 0;
    ffLmtd -> GetParameters(par);
    ffLmtdsig -> SetParameters(par);
    ffLmtdsig -> Draw("same");
    ffLmtdbg -> SetParameters(&par[6]);
    ffLmtdbg -> Draw("same");

    hrealLSumBGMtd = (TH1F*)hrealLSumMtdCl -> Clone("hrealLSumBGMtd");
    hrealLSumBGMtd -> Add(ffLmtdsig, -1);

    hrealLSumMtdPeak = (TH1F*)hrealLSumMtdCl -> Clone("hrealLSumMtdPeak");
    hrealLSumMtdPeak -> Add(hrealLSumBGMtd, -1);

    //scaled
    TString nameLmtdsc = "hrealLSumScMtdCl";
    TH1F *hrealLSumScMtdCl = (TH1F*)hrealLSumScMtd -> Clone();
    cout << ">>>>>>>>fit Lscmtd<<<<<<<<<" << endl;
    TF1 * ffLmtdsc = new TF1("ffLmtdsc", "gaus(0)+gaus(3)+pol2(6)", 1080,1190);
    ffLmtdsc -> SetParameters(
	2984560,1114.29,4.12196,
	8.78103e+06,1.11469e+03,1.95058,
	-4.32460e+09,7.51569e+06,-3.25342e+03,1,1);
    ffLmtdsc -> SetParLimits(0, 0, 100000000);
    ffLmtdsc -> SetParLimits(1, 1110, 1120);
    ffLmtdsc -> SetParLimits(2, 0, 10);
    ffLmtdsc -> SetParLimits(3, 0, 100000000);
    ffLmtdsc -> SetParLimits(4, 1110, 1120);
    ffLmtdsc -> SetParLimits(5, 0, 10);
    hrealLSumScMtdCl -> Fit("ffLmtdsc", "", "", 1090, 1140);
    hrealLSumScMtdCl -> SetName(nameLmtdsc);
    TF1 * ffLmtdsigsc = new TF1("ffLmtdsigsc", "gaus(0)+gaus(3)", 1070,1200);
    TString nameLmtdscbg = nameLmtdsc + bg;
    TF1 * ffLmtdbgsc = new TF1("ffLmtdbgsc", "pol2(0)", 1090,1140);
    double par[12];
    ffLmtdsc -> GetParameters(par);
    ffLmtdsigsc -> SetParameters(par);
    ffLmtdsigsc -> Draw("same");
    ffLmtdbgsc -> SetParameters(&par[6]);
    ffLmtdbgsc -> Draw("same");

    hrealLSumBGScMtd = (TH1F*)hrealLSumScMtdCl -> Clone("hrealLSumBGScMtd");
    hrealLSumBGScMtd -> Add(ffLmtdsigsc, -1);

    hrealLSumMtdPeakSc = (TH1F*)hrealLSumScMtdCl -> Clone("hrealLSumMtdPeakSc");
    hrealLSumMtdPeakSc -> Add(hrealLSumBGScMtd, -1);
    //end BG subtr.            
    
    hrealLSumBGMtd -> SetLineColor(kRed);
    hrealLSumBGScMtd -> SetLineColor(kRed);
    hrealLSumMtd -> SetLineColor(8);
    hrealLSumScMtd -> SetLineColor(8);
    hLGeantIDSumMtd -> SetLineColor(1);
    hLGeantIDSumScMtd -> SetLineColor(1);
    hrealLSumMtdPeak -> SetLineColor(6);
    hrealLSumMtdPeakSc -> SetLineColor(6);

    cntSLMtd = hrealLSumMtdPeak -> Integral(a,b);
    cntSLMtdGeant = hLGeantIDSumMtd -> Integral(a,b);
    cntBLMtd = hrealLSumBGMtd -> Integral(a,b);
    cntSLscMtd = hrealLSumMtdPeakSc -> Integral(a,b);
    cntSLscMtdGeant = hLGeantIDSumScMtd -> Integral(a,b);
    cntBLscMtd = hrealLSumBGScMtd -> Integral(a,b);

    //Lmass
    /*  int nLLmass = hrealLSumLmass -> GetNbinsX();
    int nLScLmass = hrealLSumScLmass -> GetNbinsX();

    hrealLSumLmass -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealLSumLmass -> GetXaxis() -> FindBin(m3sigma);
    b = hrealLSumLmass -> GetXaxis() -> FindBin(p3sigma);
    MassminL = m3sigma;
    MassmaxL = p3sigma;
    cout << "+/-3#sigma L:" << m3sigma << " " << p3sigma << endl;
    for(int j = 1; j <= nLLmass; j++){
      massL = hrealLSumLmass -> GetBinLowEdge(j);
      if(massL < MassminL) continue;
      else if(massL > MassmaxL) break;
      else hrealLSumPeakLmass -> SetBinContent(j, hrealLSumLmass -> GetBinContent(j));    
    }  
    hrealLSumScLmass -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealLSumScLmass -> GetXaxis() -> FindBin(m3sigma);
    b = hrealLSumScLmass -> GetXaxis() -> FindBin(p3sigma);
    MassminL = m3sigma;
    MassmaxL = p3sigma;
    cout << "+/-3#sigma L:" << m3sigma << " " << p3sigma << endl;
    for(int j = 1; j <= nLScLmass; j++){
      massLSc = hrealLSumScLmass -> GetBinLowEdge(j);
      if(massLSc < MassminL) continue;
      else if(massLSc > MassmaxL) break;
      else hrealLSumPeakScLmass -> SetBinContent(j, hrealLSumScLmass -> GetBinContent(j));    
    }


    TH1F *hrealLSumPeakScClLmass = (TH1F*)hrealLSumPeakScLmass -> Clone();
    hLallSumBGScLmass -> Add(hLallSumScLmass, hrealLSumPeakScClLmass, 1, -1); 

    hLallSumBGScLmass -> SetLineColor(kRed);
    hrealLSumPeakScLmass -> SetLineColor(8);

    cntSLscLmass = hrealLSumScLmass -> Integral(a,b);
    cntBLscLmass = hLallSumBGScLmass -> Integral(a,b);

    cout << "cntSLscLmass: " << cntSLscLmass << " cntBLscLmass: " << cntBLscLmass << " s1: " << hrealLSumScLmass -> Integral() << " b1: " << hLallSumBGScLmass -> Integral(a,b) << endl;
    */
    //SB L mtd
    for(int j = 1; j <= nLMtd; j++){
	if(hrealLSumMtdPeak -> GetBinContent(j)){
	  kLMtd++;
	  s_bg_vLMtd[kLMtd] = (hrealLSumMtdPeak -> GetBinContent(j))/(hrealLSumBGMtd -> GetBinContent(j));
	  binLMtd[kLMtd] = (hrealLSumMtdPeak -> GetBinLowEdge(j)) + (hrealLSumMtdPeak -> GetBinWidth(j));
      	}
    }
    for(int j = 1; j <= nLScMtd; j++){
      if(hrealLSumMtdPeakSc -> GetBinContent(j)){
	kLScMtd++;
	s_bg_vLScMtd[kLScMtd] = (hrealLSumMtdPeakSc -> GetBinContent(j))/(hrealLSumBGScMtd -> GetBinContent(j));
	binLScMtd[kLScMtd] = (hrealLSumMtdPeakSc -> GetBinLowEdge(j)) + (hrealLSumMtdPeakSc -> GetBinWidth(j));
      }
    }

    //Xi
    int nXMtd = hrealXSumMtd -> GetNbinsX();
    int nXScMtd = hrealXSumScMtd -> GetNbinsX();

    double s_bg_vXMtd[150];
    double binXMtd[150]; 
    int kXMtd = -1;
    double s_bg_vXScMtd[150];
    double binXScMtd[150];
    int kXScMtd = -1;


    hXGeantIDSumMtd -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealXSumMtd -> GetXaxis() -> FindBin(m3sigma);
    b = hrealXSumMtd -> GetXaxis() -> FindBin(p3sigma);	
    MassminX = m3sigma;
    MassmaxX = p3sigma;

    for(int j = 1; j <= nXMtd; j++){
      massX = hrealXSumMtd -> GetBinLowEdge(j);
      if(massX < MassminX) continue;
      else if(massX > MassmaxX) break;
      else{
//	  hrealXSumPeakMtd -> SetBinContent(j, hrealXSumMtd -> GetBinContent(j));
	  hXGeantIDMtdPeak -> SetBinContent(j, hXGeantIDSumMtd -> GetBinContent(j));
      }
    }
    hXGeantIDSumScMtd -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealXSumScMtd -> GetXaxis() -> FindBin(m3sigma);
    b = hrealXSumScMtd -> GetXaxis() -> FindBin(p3sigma);
    MassminX = m3sigma;
    MassmaxX = p3sigma;
    for(int j = 1; j <= nXScMtd; j++){
      massXSc = hrealXSumScMtd -> GetBinLowEdge(j);
      if(massXSc < MassminX) continue;
      else if(massXSc > MassmaxX) break;
      else{
//	  hrealXSumPeakScMtd -> SetBinContent(j, hrealXSumScMtd -> GetBinContent(j));
	  hXGeantIDScMtdPeak -> SetBinContent(j, hXGeantIDSumScMtd -> GetBinContent(j));
      }
    }

//    TH1F *hrealXSumPeakClMtd = (TH1F*)hrealXSumPeakMtd -> Clone();
//    TH1F *hrealXSumPeakScClMtd = (TH1F*)hrealXSumPeakScMtd -> Clone();
   
//    hXallSumBGMtd -> Add(hrealXSumMtd, hrealXSumPeakClMtd, 1, -1); 
//    hXallSumBGScMtd -> Add(hrealXSumScMtd, hrealXSumPeakScClMtd, 1, -1); 
//    hrealXSumBGMtd -> Add(hrealXSumMtd, hXGeantIDMtdPeak, 1, -1); 
//    hrealXSumBGScMtd -> Add(hrealXSumScMtd, hXGeantIDScMtdPeak, 1, -1); 
    ctmp -> cd();
    //BG subtr.
    TString nameXMtd = "hrealXSumMtdCl";
    TH1F *hrealXSumMtdCl = (TH1F*)hrealXSumMtd -> Clone();
    cout << ">>>>>>>>fit xmtd<<<<<<<<<" << endl;
    TF1 * ffXmtd = new TF1("ffXmtd", "gaus(0)+gaus(3)+pol5(6)", 1280,1360);
    ffXmtd -> SetParameters(
	3.73999e+05,1.31872e+03,4.05039,
	2.78539e+04,1.31000e+03,9,
	-2.85281e+07,1.64862e+04,1.59317e+01,-3.03469e-03,-4.53008e-06);
    ffXmtd -> SetParLimits(0, 0, 100000000);
    ffXmtd -> SetParLimits(1, 1310, 1330);
    ffXmtd -> SetParLimits(2, 0, 9);
    ffXmtd -> SetParLimits(3, 0, 100000000);
    ffXmtd -> SetParLimits(4, 1310, 1330);
    ffXmtd -> SetParLimits(5, 0, 9);
    hrealXSumMtdCl -> Fit("ffXmtd", "", "",1280,1365);
    hrealXSumMtdCl -> SetName(nameXMtd);
    TF1 * ffXmtdsig = new TF1("ffXmtdsig", "gaus(0)+gaus(3)", 1280,1360);
    TString nameXmtdbg = nameXMtd + bg;
    TF1 * ffXmtdbg = new TF1("ffXmtdbg", "pol5(0)", 1280,1360);
    double par[12];
    ffXmtd -> GetParameters(par);
    ffXmtdsig -> SetParameters(par);
    ffXmtdsig -> Draw("same");
    ffXmtdbg -> SetParameters(&par[6]);
    ffXmtdbg -> Draw("same");

    hrealXSumBGMtd = (TH1F*)hrealXSumMtdCl -> Clone("hrealXSumBGMtd");
    hrealXSumBGMtd -> Add(ffXmtdsig, -1);

    hrealXSumMtdPeak = (TH1F*)hrealXSumCl -> Clone("hrealXSumMtdPeak");
    hrealXSumMtdPeak -> Add(hrealXSumBGMtd, -1);

    //scaled
    TString nameXmtdsc = "hrealXSumScMtdCl";
    TH1F *hrealXSumScMtdCl = (TH1F*)hrealXSumScMtd -> Clone();
    cout << ">>>>>>>>fit Xscmtd<<<<<<<<<" << endl;
    TF1 * ffXmtdsc = new TF1("ffXmtdsc", "gaus(0)+gaus(3)+pol5(6)", 1280,1360);
    ffXmtdsc -> SetParameters(
	3.73999e+05,1.31872e+03,4.05039,
	2.78539e+04,1.31000e+03,9,
	-2.85281e+07,1.64862e+04,1.59317e+01,-3.03469e-03,-4.53008e-06);
    ffXmtdsc -> SetParLimits(0, 0, 100000000);
    ffXmtdsc -> SetParLimits(1, 1310, 1330);
    ffXmtdsc -> SetParLimits(2, 0, 9);
    ffXmtdsc -> SetParLimits(3, 0, 100000000);
    ffXmtdsc -> SetParLimits(4, 1310, 1330);
    ffXmtdsc -> SetParLimits(5, 0, 9);
    hrealXSumScMtdCl -> Fit("ffXmtdsc", "", "", 1290, 1365);
    hrealXSumScMtdCl -> SetName(nameXmtdsc);
    TF1 * ffXmtdsigsc = new TF1("ffXmtdsigsc", "gaus(0)+gaus(3)", 1280,1360);
    TString nameXmtdscbg = nameXmtdsc + bg;
    TF1 * ffXmtdbgsc = new TF1("ffXmtdbgsc", "pol5(0)", 1280,1360);
    double par[12];
    ffXmtdsc -> GetParameters(par);
    ffXmtdsigsc -> SetParameters(par);
    ffXmtdsigsc -> Draw("same");
    ffXmtdbgsc -> SetParameters(&par[6]);
    ffXmtdbgsc -> Draw("same");

    hrealXSumBGScMtd = (TH1F*)hrealXSumScMtdCl -> Clone("hrealXSumBGScMtd");
    hrealXSumBGScMtd -> Add(ffXmtdsigsc, -1);

    hrealXSumMtdPeakSc = (TH1F*)hrealXSumScMtdCl -> Clone("hrealXSumMtdPeakSc");
    hrealXSumMtdPeakSc -> Add(hrealXSumBGScMtd, -1);
    //end BG subtr.

    hrealXSumBGMtd -> SetLineColor(kRed);
    hrealXSumBGScMtd -> SetLineColor(kRed);
    hrealXSumMtd -> SetLineColor(8);
    hrealXSumScMtd -> SetLineColor(8);
    hXGeantIDSumMtd -> SetLineColor(1);
    hXGeantIDSumScMtd -> SetLineColor(1);
    hrealXSumMtdPeak -> SetLineColor(6);
    hrealXSumMtdPeakSc -> SetLineColor(6);

    cntSXMtd = hrealXSumMtdPeak -> Integral(a,b);
    cntSXMtdGeant = hXGeantIDSumMtd -> Integral(a,b);
    cntBXMtd = hrealXSumBGMtd -> Integral(a,b);
    cntSXscMtd = hrealXSumMtdPeakSc -> Integral(a,b);
    cntSXscMtdGeant = hXGeantIDSumScMtd -> Integral(a,b);
    cntBXscMtd = hrealXSumBGScMtd -> Integral(a,b);

    for(int j = 1; j <= nXMtd; j++){
      if(hrealXSumMtdPeak -> GetBinContent(j)){
	kXMtd++;
	s_bg_vXMtd[kXMtd] = (hrealXSumMtdPeak -> GetBinContent(j))/(hrealXSumBGMtd -> GetBinContent(j));
	binXMtd[kXMtd] = (hrealXSumMtdPeak -> GetBinLowEdge(j)) + (hrealXSumMtdPeak -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nXScMtd; j++){
      if(hrealXSumMtdPeakSc -> GetBinContent(j)){
	kXScMtd++;
	s_bg_vXScMtd[kXScMtd] = (hrealXSumMtdPeakSc -> GetBinContent(j))/(hrealXSumBGScMtd -> GetBinContent(j));
	binXScMtd[kXScMtd] = (hrealXSumMtdPeakSc -> GetBinLowEdge(j)) + (hrealXSumMtdPeakSc -> GetBinWidth(j));
      }
    }

    //invM no scaling MTD
    cLambdaXiMassMtd -> cd(1);
    nice_canv1(gPad);
    hLallSumMtd -> SetTitle("#pi^{-} in Hades + anything in FD (all, real, 90)");
    hLallSumMtd -> GetXaxis() -> SetTitle("M_{FD#pi^{-}} [MeV]");
    hLallSumMtd -> GetYaxis() -> SetTitle("counts");
    hLallSumMtd -> Draw();
    hrealLSumMtd -> Draw("same");
    hLall90Mtd -> Draw("same");
//    l1 -> Draw("same");
    
    cLambdaXiMassMtd -> cd(2);
    nice_canv1(gPad);
    hLallSumBGMtd -> SetTitle("p#pi^{-}: all, peak and BG");
    hLallSumBGMtd -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hLallSumMtd -> Draw();
    hrealLSumMtdPeak -> Draw("same");
    hLallSumBGMtd -> Draw("same");
    
//    l1a -> Draw("same");

    cLambdaXiMassMtd -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGMtd -> SetTitle("p#pi^{-}: real, Geant and BG");
    hrealLSumBGMtd -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hrealLSumMtd -> Draw();
    hLGeantIDSumMtd -> Draw("same");
    hrealLSumBGMtd -> Draw("same");

//    l1a -> Draw("same");

    cLambdaXiMassMtd -> cd(5);
    nice_canv1(gPad);
    hrealXSumBGMtd -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hrealXSumMtd -> Draw();
    hXGeantIDSumMtd -> Draw("same");
    hrealXSumBGMtd -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassMtd -> cd(6);
    l1 -> Draw();
    l2 -> Draw("same");

    TCanvas *cimLMtdlSc = new TCanvas("cimLMtdlSc","cimLMtdlSc", 1000, 800); //inv mass Lambda spectrum, MTD_L cut, cr sec scaling
    TCanvas *cimXMtdlVertlMlMtdxSc = new TCanvas("cimXMtdlVerlMlMtdxSc","cimXMtdlVerlMlMtdxSc", 1000, 800); //inv mass Xi spectrum, MTD_L, VERTz_L, Lmass, MTD_X cuts, cr sec scaling
    
    cLambdaXiMassScMtd -> cd(1);
    nice_canv1(gPad);
    hLallSumScMtd -> SetTitle("#pi^{-} in Hades + anything in FD (all, real, 90)");
    hLallSumScMtd -> GetXaxis() -> SetTitle("M_{FD#pi^{-}} [MeV]");
    hLallSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScMtd -> Draw();
    hrealLSumScMtd -> Draw("same");
    hrealL90ScMtd -> Draw("same");
//    l1 -> Draw("same");

    cLambdaXiMassScMtd -> cd(2);
    nice_canv1(gPad);
    hLallSumBGScMtd -> SetTitle("p#pi^{-}: all, peak and BG");
    hLallSumBGScMtd -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScMtd -> Draw();
    hrealLSumMtdPeakSc -> Draw("same");
    hLallSumBGScMtd -> Draw("same");
//    l1a -> Draw("same");
      
    cLambdaXiMassScMtd -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGScMtd -> SetTitle("p#pi^{-}: real, Geant and BG");
    hrealLSumBGScMtd -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumScMtd -> Draw();
    hLGeantIDScMtdPeak -> Draw("same");
    hrealLSumBGScMtd -> Draw("same");
//    l1a -> Draw("same");
    
    TLegend *lfin2 = new TLegend(.2,.5,.35,.8);
    
    cimLMtdlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealLSumScMtd -> SetTitle("#Lambda reconstruction, MTD_L cut");
    hrealLSumScMtd -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
//    hrealLSumScMtd -> SetLineColor(40);
//    hLallSumScMtd -> SetLineStyle(2);
    //  hLallSumScMtd -> SetLineWidth(2);
//    hrealLSumScMtd -> SetLineColor(46);
//    hrealLSumScMtd -> SetLineStyle(2);
    hrealLSumScMtd -> SetLineWidth(2);
    hrealLSumBGScMtd -> SetMarkerStyle(21);
    hrealLSumBGScMtd -> SetMarkerSize(.5);
    hrealLSumBGScMtd -> SetMarkerColor(2);
//    hrealLSumScMtd -> SetLineColor(8);
//    hLGeantIDSumScMtd -> SetLineColor(1);
    hrealLSumScMtd -> Draw();
    hrealLSumBGScMtd -> Draw("p same");
    hrealLSumMtdPeakSc -> Draw("same");
    hLGeantIDSumScMtd -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");

//    lfin2 -> AddEntry(hLallSumScMtd, "sum all ch. (#pi^{-}-FD)");
    lfin2 -> AddEntry(hrealLSumScMtd, "sum all ch. (#pi^{-}p)");
    lfin2 -> AddEntry(hrealLSumBGScMtd, "BG");
    lfin2 -> AddEntry(hrealLSumMtdPeakSc, "peak=all-BG");
    lfin2 -> AddEntry(hLGeantIDSumScMtd, "real #Lambda");
    lfin2 -> Draw("same");//<<<<<<<<<<<<<<

    cLambdaXiMassScMtd -> cd(4);
    nice_canv1(gPad);
    hrealXSumBGScMtd -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScMtd -> Draw();
    hXGeantIDSumScMtd -> Draw("same");
    hrealXSumBGScMtd -> Draw("same");

    cLambdaXiMassScMtd -> cd(6);
    l1 -> Draw();
    l2 -> Draw("same");

    TLegend *lfin3 = new TLegend(.2,.5,.35,.8);
        
    cimXMtdlVertlMlMtdxSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumScMtd -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass, MTD_X cuts");
    hrealXSumScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
//    hrealXSumScMtd -> SetLineColor(46);
//    hrealXSumScMtd -> SetLineStyle(2);
    hrealXSumScMtd -> SetLineWidth(2);
    hrealXSumBGScMtd -> SetMarkerStyle(21);
    hrealXSumBGScMtd -> SetMarkerSize(.5);
    hrealXSumBGScMtd -> SetMarkerColor(2);
    //  hrealXSumPeakScMtd -> SetLineColor(8);
//    hXGeantIDSumScMtd -> SetLineColor(1);
    hrealXSumScMtd -> Draw();   
    hrealXSumBGScMtd -> Draw("p same");
    hrealXSumMtdPeakSc -> Draw("same");
    hXGeantIDSumScMtd -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");

    lfin3 -> AddEntry(hrealXSumScMtd, "sum all ch. (#Lambda#pi^{-})");
    lfin3 -> AddEntry(hrealXSumBGScMtd, "BG");
    lfin3 -> AddEntry(hrealXSumMtdPeakSc, "peak=all-BG");
    lfin3 -> AddEntry(hXGeantIDSumScMtd, "real #Xi^{-}");
    lfin3 -> Draw("same");//<<<<<<<<<<<<<<

    //MTD_L, Lmass, MTD_X, VERTZ_L, VERTZ_X
    //Lambda1115
    int nLVert = hrealLSumVert -> GetNbinsX();
    int nLScVert = hrealLSumScVert -> GetNbinsX();

    double s_bg_vLVert[150];
    double binLVert[150]; 
    int kLVert = -1;
    double s_bg_vLScVert[150];
    double binLScVert[150]; 
    int kLScVert = -1;

    hLGeantIDSumVert -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealLSumVert -> GetXaxis() -> FindBin(m3sigma);
    b = hrealLSumVert -> GetXaxis() -> FindBin(p3sigma);
    MassminL = m3sigma;
    MassmaxL = p3sigma;
    for(int j = 1; j <= nLVert; j++){
      massL = hrealLSumVert -> GetBinLowEdge(j);
      if(massL < MassminL) continue;
      else if(massL > MassmaxL) break;
      else{
//	  hrealLSumPeakVert -> SetBinContent(j, hrealLSumVert -> GetBinContent(j));
	  hLGeantIDVertPeak -> SetBinContent(j, hLGeantIDSumVert -> GetBinContent(j));
      }
    }
    hLGeantIDSumScVert -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealLSumScVert -> GetXaxis() -> FindBin(m3sigma);
    b = hrealLSumScVert -> GetXaxis() -> FindBin(p3sigma);
    MassminL = m3sigma;
    MassmaxL = p3sigma;
    for(int j = 1; j <= nLScVert; j++){
      massLSc = hrealLSumScVert -> GetBinLowEdge(j);
      if(massLSc < MassminL) continue;
      else if(massLSc > MassmaxL) break;
      else{
//	  hrealLSumPeakScVert -> SetBinContent(j, hrealLSumScVert -> GetBinContent(j));
	  hLGeantIDScVertPeak -> SetBinContent(j, hLGeantIDSumScVert -> GetBinContent(j));
      }
    }

//    TH1F *hrealLSumPeakClVert = (TH1F*)hrealLSumPeakVert -> Clone();
//    TH1F *hrealLSumPeakScClVert = (TH1F*)hrealLSumPeakScVert -> Clone();
    
//    hLallSumBGVert -> Add(hLallSumVert, hrealLSumPeakClVert, 1, -1); 
//    hLallSumBGScVert -> Add(hLallSumScVert, hrealLSumPeakScClVert, 1, -1);
//    hrealLSumBGVert -> Add(hrealLSumVert, hLGeantIDVertPeak, 1, -1); 
//    hrealLSumBGScVert -> Add(hrealLSumScVert, hLGeantIDScVertPeak, 1, -1); 
    ctmp -> cd();
    //BG subtr.
    TString nameLVert = "hrealLSumVertCl";
    TH1F *hrealLSumVertCl = (TH1F*)hrealLSumVert -> Clone();
    cout << ">>>>>>>>fit lvert<<<<<<<<<" << endl;
    TF1 * ffLvert = new TF1("ffLvert", "gaus(0)+gaus(3)+pol2(6)", 1080,1190);
    ffLvert -> SetParameters(
	2984560,1114.29,4.12196,
	8.78103e+06,1.11469e+03,1.95058,
	-4.32460e+09,7.51569e+06,-3.25342e+03,1,1);
    ffLvert -> SetParLimits(0, 0, 100000000);
    ffLvert -> SetParLimits(1, 1110, 1120);
    ffLvert -> SetParLimits(2, 0, 10);
    ffLvert -> SetParLimits(3, 0, 100000000);
    ffLvert -> SetParLimits(4, 1110, 1120);
    ffLvert -> SetParLimits(5, 0, 10);
    hrealLSumVertCl -> Fit("ffLvert", "", "", 1090, 1140);
    hrealLSumVertCl -> SetName(nameLVert);
    TF1 * ffLvertsig = new TF1("ffLvertsig", "gaus(0)+gaus(3)", 1070,1200);
    TString nameLvertbg = nameLVert + bg;
    TF1 * ffLvertbg = new TF1("ffLvertbg", "pol2(0)", 1090,1140);
    double par[12];
    ffLvert -> GetParameters(par);
    ffLvertsig -> SetParameters(par);
    ffLvertsig -> Draw("same");
    ffLvertbg -> SetParameters(&par[6]);
    ffLvertbg -> Draw("same");

    hrealLSumBGVert = (TH1F*)hrealLSumVertCl -> Clone("hrealLSumBGVert");
    hrealLSumBGVert -> Add(ffLvertsig, -1);

    hrealLSumVertPeak = (TH1F*)hrealLSumVertCl -> Clone("hrealLSumVertPeak");
    hrealLSumVertPeak -> Add(hrealLSumBGVert, -1);
    
    //scaled
    TString nameLvertsc = "hrealLSumScVertCl";
    TH1F *hrealLSumScVertCl = (TH1F*)hrealLSumScVert -> Clone();
    cout << ">>>>>>>>fit Lscvert<<<<<<<<<" << endl;
    TF1 * ffLvertsc = new TF1("ffLvertsc", "gaus(0)+gaus(3)+pol2(6)", 1080,1190);
    ffLvertsc -> SetParameters(
	8.82592e+06,1.11484e+03,2.20163,
	1.28201e+06,1.11448e+03,8.34705,
	-8.79549e+07,8.12041e+04);
    ffLvertsc -> SetParLimits(0, 0, 100000000);
    ffLvertsc -> SetParLimits(1, 1110, 1120);
    ffLvertsc -> SetParLimits(2, 0, 10);
    ffLvertsc -> SetParLimits(3, 0, 100000000);
    ffLvertsc -> SetParLimits(4, 1110, 1120);
    ffLvertsc -> SetParLimits(5, 0, 10);
    hrealLSumScVertCl -> Fit("ffLvertsc", "", "", 1090, 1140);
    hrealLSumScVertCl -> SetName(nameLvertsc);
    TF1 * ffLvertsigsc = new TF1("ffLvertsigsc", "gaus(0)+gaus(3)", 1070,1200);
    TString nameLvertscbg = nameLvertsc + bg;
    TF1 * ffLvertbgsc = new TF1("ffLvertbgsc", "pol2(0)", 1090,1140);
    double par[12];
    ffLvertsc -> GetParameters(par);
    ffLvertsigsc -> SetParameters(par);
    ffLvertsigsc -> Draw("same");
    ffLvertbgsc -> SetParameters(&par[6]);
    ffLvertbgsc -> Draw("same");

    hrealLSumBGScVert = (TH1F*)hrealLSumScVertCl -> Clone("hrealLSumBGScVert");
    hrealLSumBGScVert -> Add(ffLvertsigsc, -1);

    hrealLSumVertPeakSc = (TH1F*)hrealLSumScVertCl -> Clone("hrealLSumVertPeakSc");
    hrealLSumVertPeakSc -> Add(hrealLSumBGScVert, -1);
    //end BG subtr.

    hrealLSumBGVert -> SetLineColor(kRed);
    hrealLSumBGScVert -> SetLineColor(kRed);
    hrealLSumVert -> SetLineColor(8);
    hrealLSumScVert -> SetLineColor(8);
    hLGeantIDSumVert -> SetLineColor(1);
    hLGeantIDSumScVert -> SetLineColor(1);
    hrealLSumVertPeak -> SetLineColor(6);
    hrealLSumVertPeakSc -> SetLineColor(6);
    
    cntSLVert = hrealLSumVertPeak -> Integral(a,b);
    cntSLVertGeant = hLGeantIDSumVert -> Integral(a,b);
    cntBLVert = hrealLSumBGVert -> Integral(a,b);
    cntSLscVert = hrealLSumVertPeakSc -> Integral(a,b);
    cntSLscVertGeant = hLGeantIDSumScVert -> Integral(a,b);
    cntBLscVert = hrealLSumBGScVert -> Integral(a,b);

    //SB
    for(int j = 1; j <= nLVert; j++){
      if(hrealLSumVertPeak -> GetBinContent(j)){
	kLVert++;
	s_bg_vLVert[kLVert] = (hrealLSumVertPeak -> GetBinContent(j))/(hrealLSumBGVert -> GetBinContent(j));
	binLVert[kLVert] = (hrealLSumVertPeak -> GetBinLowEdge(j)) + (hrealLSumVertPeak -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nLScVert; j++){
      if(hrealLSumVertPeakSc -> GetBinContent(j)){
	kLScVert++;
	s_bg_vLScVert[kLScVert] = (hrealLSumVertPeakSc -> GetBinContent(j))/(hrealLSumBGScVert -> GetBinContent(j));
	binLScVert[kLScVert] = (hrealLSumVertPeakSc -> GetBinLowEdge(j)) + (hrealLSumVertPeakSc -> GetBinWidth(j));
      }
    }

    //Xi
    int nXVert = hrealXSumVert -> GetNbinsX();
    int nXScVert = hrealXSumScVert -> GetNbinsX();

    double s_bg_vXVert[150];
    double binXVert[150]; 
    int kXVert = -1;
    double s_bg_vXScVert[150];
    double binXScVert[150];
    int kXScVert = -1;

    hXGeantIDSumVert-> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealXSumVert -> GetXaxis() -> FindBin(m3sigma);
    b = hrealXSumVert -> GetXaxis() -> FindBin(p3sigma);
    MassminX = m3sigma;
    MassmaxX = p3sigma;
    for(int j = 1; j <= nXVert; j++){
      massX = hrealXSumVert -> GetBinLowEdge(j);
      if(massX < MassminX) continue;
      else if(massX > MassmaxX) break;
      else{
//	  hrealXSumPeakVert -> SetBinContent(j, hrealXSumVert -> GetBinContent(j));
	  hXGeantIDVertPeak -> SetBinContent(j, hXGeantIDSumVert -> GetBinContent(j));
      }
    }
    hXGeantIDSumScVert-> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealXSumScVert -> GetXaxis() -> FindBin(m3sigma);
    b = hrealXSumScVert -> GetXaxis() -> FindBin(p3sigma);
    MassminX = m3sigma;
    MassmaxX = p3sigma;
    for(int j = 1; j <= nXScVert; j++){
      massXSc = hrealXSumScVert -> GetBinLowEdge(j);
      if(massXSc < MassminX) continue;
      else if(massXSc > MassmaxX) break;
      else{
//	  hrealXSumPeakScVert -> SetBinContent(j, hrealXSumScVert -> GetBinContent(j));
	  hXGeantIDScVertPeak -> SetBinContent(j, hXGeantIDSumScVert -> GetBinContent(j));
      }
    }

//    TH1F *hrealXSumPeakClVert = (TH1F*)hrealXSumPeakVert -> Clone();
//    TH1F *hrealXSumPeakScClVert = (TH1F*)hrealXSumPeakScVert -> Clone();

//    hXallSumBGVert -> Add(hrealXSumVert, hrealXSumPeakClVert, 1, -1); 
//    hXallSumBGScVert -> Add(hrealXSumScVert, hrealXSumPeakScClVert, 1, -1); 
//    hrealXSumBGVert -> Add(hrealXSumVert, hXGeantIDVertPeak, 1, -1); 
//    hrealXSumBGScVert -> Add(hrealXSumScVert, hXGeantIDScVertPeak, 1, -1); 
    ctmp -> cd();
    //BG subtr.
    TString nameXVert = "hrealXSumVertCl";
    TH1F *hrealXSumVertCl = (TH1F*)hrealXSumVert -> Clone();
    cout << ">>>>>>>>fit xvert<<<<<<<<<" << endl;
    TF1 * ffXvert = new TF1("ffXvert", "gaus(0)+gaus(3)+pol5(6)", 1280,1360);
    ffXvert -> SetParameters(
        3.73999e+05,1.31872e+03,4.05039,
	2.78539e+04,1.31000e+03,9,
	-2.85281e+07,1.64862e+04,1.59317e+01,-3.03469e-03,-4.53008e-06);
    ffXvert -> SetParLimits(0, 0, 100000000);
    ffXvert -> SetParLimits(1, 1310, 1330);
    ffXvert -> SetParLimits(2, 0, 9);
    ffXvert -> SetParLimits(3, 0, 100000000);
    ffXvert -> SetParLimits(4, 1310, 1330);
    ffXvert -> SetParLimits(5, 0, 9);
    hrealXSumVertCl -> Fit("ffXvert", "", "", 1280, 1365);
    hrealXSumVertCl -> SetName(nameXVert);
    TF1 * ffXvertsig = new TF1("ffXvertsig", "gaus(0)+gaus(3)", 1280,1360);
    TString nameXvertbg = nameXVert + bg;
    TF1 * ffXvertbg = new TF1("ffXvertbg", "pol5(0)", 1280,1360);
    double par[12];
    ffXvert -> GetParameters(par);
    ffXvertsig -> SetParameters(par);
    ffXvertsig -> Draw("same");
    ffXvertbg -> SetParameters(&par[6]);
    ffXvertbg -> Draw("same");

    hrealXSumBGVert = (TH1F*)hrealXSumVertCl -> Clone("hrealXSumBGVert");
    hrealXSumBGVert -> Add(ffXvertsig, -1);

    hrealXSumVertPeak = (TH1F*)hrealXSumVertCl -> Clone("hrealXSumVertPeak");
    hrealXSumVertPeak -> Add(hrealXSumBGVert, -1);

    //scaled
    TString nameXvertsc = "hrealXSumScVertCl";
    TH1F *hrealXSumScVertCl = (TH1F*)hrealXSumScVert -> Clone();
    cout << ">>>>>>>>fit Xscvert<<<<<<<<<" << endl;
    TF1 * ffXvertsc = new TF1("ffXvertsc", "gaus(0)+gaus(3)+pol5(6)", 1280,1360);
    ffXvertsc -> SetParameters(
        3.73999e+05,1.31872e+03,4.05039,
	2.78539e+04,1.31000e+03,9,
	-2.85281e+07,1.64862e+04,1.59317e+01,-3.03469e-03,-4.53008e-06);
    ffXvertsc -> SetParLimits(0, 0, 100000000);
    ffXvertsc -> SetParLimits(1, 1310, 1330);
    ffXvertsc -> SetParLimits(2, 0, 9);
    ffXvertsc -> SetParLimits(3, 0, 100000000);
    ffXvertsc -> SetParLimits(4, 1310, 1330);
    ffXvertsc -> SetParLimits(5, 0, 9);
    hrealXSumScVertCl -> Fit("ffXvertsc", "", "", 1280, 1365);
    hrealXSumScVertCl -> SetName(nameXvertsc);
    TF1 * ffXvertsigsc = new TF1("ffXvertsigsc", "gaus(0)+gaus(3)", 1280,1360);
    TString nameXvertscbg = nameXvertsc + bg;
    TF1 * ffXvertbgsc = new TF1("ffXvertbgsc", "pol5(0)", 1280,1360);
    double par[12];
    ffXvertsc -> GetParameters(par);
    ffXvertsigsc -> SetParameters(par);
    ffXvertsigsc -> Draw("same");
    ffXvertbgsc -> SetParameters(&par[6]);
    ffXvertbgsc -> Draw("same");

    hrealXSumBGScVert = (TH1F*)hrealXSumScVertCl -> Clone("hrealXSumBGScVert");
    hrealXSumBGScVert -> Add(ffXvertsigsc, -1);

    hrealXSumVertPeakSc = (TH1F*)hrealXSumScVertCl -> Clone("hrealXSumVertPeakSc");
    hrealXSumVertPeakSc -> Add(hrealXSumBGScVert, -1);
    //end BG subtr.                          

    hrealXSumBGVert -> SetLineColor(kRed);
    hrealXSumBGScVert -> SetLineColor(kRed);
    hrealXSumVert -> SetLineColor(8);
    hrealXSumScVert -> SetLineColor(8);
    hXGeantIDSumVert -> SetLineColor(1);
    hXGeantIDSumScVert -> SetLineColor(1);
    hrealXSumVertPeak -> SetLineColor(6);
    hrealXSumVertPeakSc -> SetLineColor(6);
        
    cntSXVert = hrealXSumVertPeak -> Integral(a,b);
    cntSXVertGeant = hXGeantIDSumVert -> Integral(a,b);
    cntBXVert = hrealXSumBGVert -> Integral(a,b);
    cntSXscVert = hrealXSumVertPeakSc -> Integral(a,b);
    cntSXscVertGeant = hXGeantIDSumScVert -> Integral(a,b);
    cntBXscVert = hrealXSumBGScVert -> Integral(a,b);

    //SB
    for(int j = 1; j <= nXVert; j++){
      if(hrealXSumVertPeak -> GetBinContent(j)){
	kXVert++;
	s_bg_vXVert[kXVert] = (hrealXSumVertPeak -> GetBinContent(j))/(hrealXSumBGVert -> GetBinContent(j));
	binXVert[kXVert] = (hrealXSumVertPeak -> GetBinLowEdge(j)) + (hrealXSumVertPeak -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nXScVert; j++){
      if(hrealXSumVertPeakSc -> GetBinContent(j)){
	kXScVert++;
	s_bg_vXScVert[kXScVert] = (hrealXSumVertPeakSc -> GetBinContent(j))/(hrealXSumBGScVert -> GetBinContent(j));
	binXScVert[kXScVert] = (hrealXSumVertPeakSc -> GetBinLowEdge(j)) + (hrealXSumVertPeakSc -> GetBinWidth(j));
      }
    }

    //invM no scaling MTD, Vert
    cLambdaXiMassVert -> cd(1);
    nice_canv1(gPad);
    hLallSumVert -> SetTitle("#pi^{-} in Hades + anything in FD (all, real, 90)");
    hLallSumVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumVert -> GetYaxis() -> SetTitle("counts");
    hLallSumVert -> Draw();
    hrealLSumVert -> Draw("same");
    hLall90Vert -> Draw("same");
//    l1 -> Draw("same");
    
    cLambdaXiMassVert -> cd(2);
    nice_canv1(gPad);
    hLallSumBGVert -> SetTitle("p#pi^{-}: all, peak and BG");
    hLallSumBGVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumBGVert -> GetYaxis() -> SetTitle("counts");
    hLallSumBGVert -> Draw();
    hrealLSumVertPeak -> Draw("same");
    hLallSumBGVert -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassVert -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGVert -> SetTitle("p#pi^{-}: real, Geant and BG");
    hrealLSumBGVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGVert -> GetYaxis() -> SetTitle("counts");
    hrealLSumVert -> Draw();
    hLGeantIDSumVert -> Draw("same");
    hrealLSumBGVert -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassVert -> cd(4);
    nice_canv1(gPad);
    hrealXSumBGVert -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGVert -> GetYaxis() -> SetTitle("counts");
    hrealXSumVert -> Draw();
    hXGeantIDVertPeak -> Draw("same");
    hrealXSumBGVert -> Draw("same");

    cLambdaXiMassVert -> cd(6);
    l1 -> Draw();
    l2 -> Draw("same");

    TCanvas *cimLMtdlVertlSc = new TCanvas("cimLMtdlVertlSc","cimLMtdlVertlSc", 1000, 800); //inv mass Lambda spectrum, MTD_L, VERTz_L cuts, cr sec scaling
    TCanvas *cimXMtdlVertlMlMtdxVertxSc = new TCanvas("cimXMtdlVerlMlMtdxVertxSc","cimXMtdlVerlMlMtdxVertxSc", 1000, 800); //inv mass Xi spectrum, MTD_L, VERTz_L, Lmass, MTD_X, VERTz_X cuts, cr sec scaling
 
    Double_t ymax;
    ymax = 2300000;
    massL_min = new TLine(MassminL, 0, MassminL, ymax);
    massL_max = new TLine(MassmaxL, 0, MassmaxL, ymax);
    massL_min -> SetLineColor(kRed);
    massL_min -> SetLineWidth(2);
    massL_max -> SetLineColor(kRed);
    massL_max -> SetLineWidth(2);
    ymax = 1800;
    massX_min = new TLine(MassminX, 0, MassminX, ymax);
    massX_max = new TLine(MassmaxX, 0, MassmaxX, ymax);
    massX_min -> SetLineColor(kRed);
    massX_min -> SetLineWidth(2);
    massX_max -> SetLineColor(kRed);
    massX_max -> SetLineWidth(2);

    cLambdaXiMassScVert -> cd(1);
    nice_canv1(gPad);
    hLallSumScVert -> SetTitle("#pi^{-} in Hades + anything in FD (all, real, 90)");
    hLallSumScVert -> GetXaxis() -> SetTitle("M_{FD#pi^{-}} [MeV]");
    hLallSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScVert -> Draw();
    hrealLSumScVert -> Draw("same");
    hrealL90ScVert -> Draw("same");
//    l1 -> Draw("same");
    
    cLambdaXiMassScVert -> cd(2);
    nice_canv1(gPad);
    hLallSumBGScVert -> SetTitle("p#pi^{-}: all, peak and BG");
    hLallSumBGScVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumBGScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScVert -> Draw();
    hrealLSumVertPeakSc -> Draw("same");
    hLallSumBGScVert -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassScVert -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGScVert -> SetTitle("p#pi^{-}: real, Geant and BG");
    hrealLSumBGScVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumScVert -> Draw();
    hLGeantIDScVertPeak -> Draw("same");
    hrealLSumBGScVert -> Draw("same");
//    l1a -> Draw("same");
    
    TLegend *lfin4 = new TLegend(.2,.5,.35,.8);
    
    cimLMtdlVertlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealLSumScVert -> SetTitle("#Lambda reconstruction, MTD_L, VERTz_L cuts");
    hrealLSumScVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
//    hrealLSumScVert -> SetLineColor(40);
//    hLallSumScVert -> SetLineStyle(2);
    //  hLallSumScVert -> SetLineWidth(2);
//    hrealLSumScVert -> SetLineColor(46);
//    hrealLSumScVert -> SetLineStyle(2);
    hrealLSumScVert -> SetLineWidth(2);
    hrealLSumBGScVert -> SetMarkerStyle(21);
    hrealLSumBGScVert -> SetMarkerSize(.5);
    hrealLSumBGScVert -> SetMarkerColor(2);
    //  hrealLSumPeakScVert -> SetLineColor(8);
    // hrealLSumPeakScVert -> SetLineStyle(8);
    // hLGeantIDSumScVert -> SetLineColor(1);
    // hLallSumScVert -> Draw();
    hrealLSumScVert -> Draw();
    hrealLSumBGScVert -> Draw("p same");
    hrealLSumVertPeakSc -> Draw("same");
    hLGeantIDSumScVert -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");

//    lfin4 -> AddEntry(hLallSumScVert, "sum all ch. (#pi^{-}-FD)");
    lfin4 -> AddEntry(hrealLSumScVert, "sum all ch. (#pi^{-}p)");
    lfin4 -> AddEntry(hrealLSumBGScVert, "BG");
    lfin4 -> AddEntry(hrealLSumVertPeakSc, "peak=all-BG");
    lfin4 -> AddEntry(hLGeantIDSumScVert, "real #Lambda");
    lfin4 -> Draw("same");//<<<<<<<<<<<<<<
    
    cLambdaXiMassScVert -> cd(4);
    nice_canv1(gPad);
    hrealXSumBGScVert -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScVert -> Draw();
    hXGeantIDSumScVert -> Draw("same");
    hrealXSumBGScVert -> Draw("same");

    cLambdaXiMassScVert -> cd(6);
    l1 -> Draw();
    l2 -> Draw("same");

    TLegend *lfin5 = new TLegend(.2,.5,.35,.8);
        
    cimXMtdlVertlMlMtdxVertxSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumScVert -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass, MTD_X, VERTz_X");
    hrealXSumScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
//    hrealXSumScVert -> SetLineColor(46);
//    hrealXSumScVert -> SetLineStyle(2);
    hrealXSumScVert -> SetLineWidth(2);
    hrealXSumBGScVert -> SetMarkerStyle(21);
    hrealXSumBGScVert -> SetMarkerSize(.5);
    hrealXSumBGScVert -> SetMarkerColor(2);
    //  hrealXSumPeakScVert -> SetLineColor(8);
    // hXGeantIDSumScVert -> SetLineColor(1);
    hrealXSumScVert -> Draw();
    hrealXSumBGScVert -> Draw("p same");
    hrealXSumVertPeakSc -> Draw("same");
    hXGeantIDSumScVert -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");

    lfin5 -> AddEntry(hrealXSumScVert, "sum all ch. (#Lambda#pi^{-})");
    lfin5 -> AddEntry(hrealXSumBGScVert, "BG");
    lfin5 -> AddEntry(hrealXSumVertPeakSc, "peak=all-BG");
    lfin5 -> AddEntry(hXGeantIDSumScVert, "real #Xi^{-}");
    lfin5 -> Draw("same");//<<<<<<<<<<<<<<

    //
    ymax = 100000000;//hMTD_Lall1 -> GetMaximum();
    TLine *lim_min = new TLine(distcut_minL, 0, distcut_minL, ymax);
    lim_min -> SetLineColor(kRed);
    lim_min -> SetLineWidth(2);
    cMTDL -> cd(1);
    lChan -> Draw("same");
    lim_min -> Draw("same");

    lim_min -> SetLineColor(kRed);
    lim_min -> SetLineWidth(2);
    cMTDL -> cd(2);
    lChan -> Draw("same");
    lim_min -> Draw("same");

    ymax = 5000000;//hMTD_Xall1 -> GetMaximum();
    lim_min = new TLine(distcut_minX, 0, distcut_minX, ymax);
    lim_min -> SetLineColor(kRed);
    lim_min -> SetLineWidth(2);
    cMTDX -> cd(1);
    lChan -> Draw("same");
    lim_min -> Draw("same");

    lim_min -> SetLineColor(kRed);
    lim_min -> SetLineWidth(2);
    cMTDX -> cd(2);
    lChan -> Draw("same");
    lim_min -> Draw("same");


    ymax = 10000000;//hVertz_Lall1 -> GetMaximum();
    lim_min = new TLine(zlim_minL, 0, zlim_minL, ymax);
    TLine *lim_max = new TLine(zlim_max, 0, zlim_max, ymax);
    lim_min -> SetLineColor(kRed);
    lim_max -> SetLineColor(kRed);
    lim_min -> SetLineWidth(2);
    lim_max -> SetLineWidth(2);
    cVERTL -> cd(1);
    lChan -> Draw("same");
    lim_min -> Draw("same");
    lim_max -> Draw("same");

    lim_min -> SetLineColor(kRed);
    lim_max -> SetLineColor(kRed);
    lim_min -> SetLineWidth(2);
    lim_max -> SetLineWidth(2);
    cVERTL -> cd(2);
    lChan -> Draw("same");
    lim_min -> Draw("same");
    lim_max -> Draw("same");


    ymax = 1000000;//hVertz_Xall1 -> GetMaximum();
    lim_min = new TLine(zlim_minX, 0, zlim_minX, ymax);
    lim_max = new TLine(zlim_max, 0, zlim_max, ymax);
    lim_min -> SetLineColor(kRed);
    lim_max -> SetLineColor(kRed);
    lim_min -> SetLineWidth(2);
    lim_max -> SetLineWidth(2);
    cVERTX -> cd(1);
    lChan -> Draw("same");
    lim_min -> Draw("same");
    lim_max -> Draw("same");

    lim_min -> SetLineColor(kRed);
    lim_max -> SetLineColor(kRed);
    lim_min -> SetLineWidth(2);
    lim_max -> SetLineWidth(2);
    cVERTX -> cd(2);
    lChan -> Draw("same");
    lim_min -> Draw("same");
    lim_max -> Draw("same");

    cVERTL1 -> cd();
    hLVertex_allSum -> Draw();
    hLVertex_sigSum -> Draw("same");
    cVERTX1 -> cd();
    hXVertex_allSum -> Draw();
    hXVertex_sigSum -> Draw("same");    
       
    //S/B
    double SBL = cntSL/cntBL;
    double SBLsc = cntSLsc/cntBLsc;
    double SBLMtd = cntSLMtd/cntBLMtd;
    double SBLMtdsc = cntSLscMtd/cntBLscMtd;
    double SBLLmasssc = cntSLscLmass/cntBLscLmass;

    double SBX = cntSX/cntBX;
    double SBXsc = cntSXsc/cntBXsc;
    double SBXMtd = cntSXMtd/cntBXMtd;
    double SBXMtdsc = cntSXscMtd/cntBXscMtd;

    double SBLVert = cntSLVert/cntBLVert;
    double SBLVertsc = cntSLscVert/cntBLscVert;
    double SBXVert = cntSXVert/cntBXVert;
    double SBXVertsc = cntSXscVert/cntBXscVert;

    printf("S:\nL: noCut: %f, noCutsc: %f, MTDL: %f, MTDLsc: %f, VERTL: %f, VERTLsc: %f, Lmasssc: %f\nX: noCut: %f, noCutsc: %f, MTDX: %f, MTDXsc: %f, VERTX: %f, VERTXsc: %f\n", cntSL, cntSLsc, cntSLMtd, cntSLscMtd, cntSLVert, cntSLscVert, cntSLscLmass, cntSX, cntSXsc, cntSXMtd, cntSXscMtd, cntSXVert, cntSXscVert);
    printf("S:\nLGeant: noCut: %f, noCutsc: %f, MTDL: %f, MTDLsc: %f, VERTL: %f, VERTLsc: %f\nX: noCut: %f, noCutsc: %f, MTDX: %f, MTDXsc: %f, VERTX: %f, VERTXsc: %f\n", cntSLGeant, cntSLscGeant, cntSLMtdGeant, cntSLscMtdGeant, cntSLVertGeant, cntSLscVertGeant, cntSXGeant, cntSXscGeant, cntSXMtdGeant, cntSXscMtdGeant, cntSXVertGeant, cntSXscVertGeant);
    
    printf("B:\nL: noCut: %f, noCutsc: %f, MTDL: %f, MTDLsc: %f, VERTL: %f, VERTLsc: %f, Lmasssc: %f\nX: noCut: %f, noCutsc: %f, MTDX: %f, MTDXsc: %f, VERTX: %f, VERTXsc: %f\n", cntBL, cntBLsc, cntBLMtd, cntBLscMtd, cntBLVert, cntBLscVert, cntBLscLmass, cntBX, cntBXsc, cntBXMtd, cntBXscMtd, cntBXVert, cntBXscVert);

    printf("S/B:\nL: noCut: %f, noCutsc: %f, MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f, Lmassc: %f\nX: noCut: %f, noCutsc: %f, MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f\n", SBL, SBLsc, SBLMtd, SBLMtdsc, SBLVert, SBLVertsc, SBLLmasssc, SBX, SBXsc, SBXMtd, SBXMtdsc, SBXVert, SBXVertsc);

    //significance
    double SgnL = cntSL/TMath::Sqrt(cntBL+cntSL);
    double SgnLsc = cntSLsc/TMath::Sqrt(cntBLsc+cntSLsc);
    double SgnLMtd = cntSLMtd/TMath::Sqrt(cntSLMtd+cntBLMtd);
    double SgnLMtdsc = cntSLscMtd/TMath::Sqrt(cntBLscMtd+cntSLscMtd);
    double SgnLLmasssc = cntSLscLmass/TMath::Sqrt(cntBLscLmass+cntSLscLmass);
  
    double SgnX = cntSX/TMath::Sqrt(cntBX+cntSX);
    double SgnXsc = cntSXsc/TMath::Sqrt(cntBXsc+cntSXsc);
    double SgnXMtd = cntSXMtd/TMath::Sqrt(cntBXMtd+cntSXMtd);
    double SgnXMtdsc = cntSXscMtd/TMath::Sqrt(cntBXscMtd+cntSXscMtd);

    double SgnLVert = cntSLVert/TMath::Sqrt(cntBLVert+cntSLVert);
    double SgnLVertsc = cntSLscVert/TMath::Sqrt(cntBLscVert+cntSLscVert);
    double SgnXVert = cntSXVert/TMath::Sqrt(cntBXVert+cntSXVert);
    double SgnXVertsc = cntSXscVert/TMath::Sqrt(cntBXscVert+cntSXscVert);
    
    printf("significance:\nL: noCut: %f, noCutsc: %f, MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f, Lmasssc: %f\nX: noCut, %f, noCutsc %f, MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f\n", SgnL, SgnLsc, SgnLMtd, SgnLMtdsc, SgnLVert, SgnLVertsc, SgnLLmasssc, SgnX, SgnXsc, SgnXMtd, SgnXMtdsc, SgnXVert, SgnXVertsc);

    //effi
    cout << "nallX2=" << nallX << "nallL2=" << nallL << endl;
    nallL /= 100; //n evt -> [%]
    nallX /= 100; //n evt -> [%]
    double brL = 0.64; //BR for Lambda->p pim 
    printf("Effi rec.:\nL: MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f\nX: MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f\n", cntSLMtd/nallL/brL, cntSLscMtd/nallL/brL, cntSLVert/nallL/brL, cntSLscVert/nallL/brL, cntSXMtd/nallX, cntSXscMtd/nallX, cntSXVert/nallX, cntSXscVert/nallX);

    //3sigma Xi
    cout << "-3s:" << m3sigma << " +3s:" << p3sigma << " a:" << a << " b:" << b << endl;
    //Xi counts:
    cout << "Xi(MTD_L, Vert_L, Lmass, MTD_X, no_sc): " << cntSXMtd << endl;
  
    TCanvas *cL_nocuts_sc = new TCanvas("cL_nocuts_sc", "Reconstruction of #Lambda(1115) (no cuts, #sigma sc.)", 1000, 800);
    cL_nocuts_sc -> cd();
    nice_canv1(gPad);
    hLmass_sc -> Add(hrealLSumSc);
    hLmass_sc -> Draw("nostack");
    hLmass_sc -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLmass_sc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLmass_sc -> GetYaxis() -> SetRangeUser(0, 100000000);
    //hLallSumSc -> Draw("same");
    cL_nocuts_sc -> Modified();
    lChan -> AddEntry(hrealLSumSc, "sum of all channels");
    lChan -> Draw("same");

    TCanvas *cL_rec_sc = new TCanvas("cL_rec_sc", "Reconstruction of #Lambda(1115) (all cuts, #sigma sc.)", 1000, 800);
    cL_rec_sc -> cd();
    nice_canv1(gPad);
    hLmass_sc_rec -> Add(hrealLSumScVert);
    hLmass_sc_rec -> Draw("nostack");
    hLmass_sc_rec -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLmass_sc_rec -> GetYaxis() -> SetTitle("counts*#sigma");
    hLmass_sc_rec -> GetYaxis() -> SetRangeUser(0, 100000000);
    //hLallSumSc -> Draw("same");
    cL_rec_sc -> Modified();
    lChan -> Draw("same");

    TCanvas *cX_nocuts_sc = new TCanvas("cXi_nocuts_sc", "Reconstruction of #Xi^{-} (MTD_L, MassL, #sigma sc.)", 1000, 800);
    cX_nocuts_sc -> cd();
    nice_canv1(gPad);
    hXmass_sc -> Add(hrealXSumSc); 
    hXmass_sc -> Draw("nostack");
    hXmass_sc -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hXmass_sc -> GetYaxis() -> SetTitle("counts*#sigma");
    hXmass_sc -> GetYaxis() -> SetRangeUser(0, 100000000);
    //hXallSumSc -> Draw("same");
    cX_nocuts_sc -> Modified();
    lChan -> Draw("same");

    TCanvas *cX_fin_sc = new TCanvas("cXi_fin_sc", "Reconstruction of #Xi^{-} (all cuts, #sigma sc.)", 1000, 800);
    cX_fin_sc -> cd();
    nice_canv1(gPad);
    hXmass_sc_fin -> Add(hrealXSumScMtd);
    hXmass_sc_fin -> Draw("nostack");
    hXmass_sc_fin -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hXmass_sc_fin -> GetYaxis() -> SetTitle("counts*#sigma");
    hXmass_sc_fin -> GetYaxis() -> SetRangeUser(0, 2000000);
    //hXallSumScMtd -> Draw("same");
    cX_fin_sc -> Modified();
    lChan -> Draw("same");

        
    TFile *f = new TFile("./out_ana/out_anaBkgd_test8.root", "RECREATE");
    cLambdaXiMass -> Write();
    cLambdaXiMassSc -> Write();
    cLambdaXiMassMtd -> Write();
    cLambdaXiMassScMtd -> Write();
    cLambdaXiMassVert -> Write();
    cLambdaXiMassScVert -> Write();
    cMTDL -> Write();
    cMTDX -> Write();
    cVERTL -> Write();
    cVERTX -> Write();
    cVERTL1 -> Write();
    cVERTX1 -> Write();
    cVertZ_L -> Write();
    cVertZ_X -> Write();
  
    cimLNoCutsSc -> Write();
    cimXMtdlVertlMlSc -> Write();
    cimLMtdlSc -> Write();
    cimXMtdlVertlMlMtdxSc -> Write();
    cimLMtdlVertlSc -> Write();
    cimXMtdlVertlMlMtdxVertxSc -> Write();
								      
    cL_nocuts_sc -> Write();
    cL_rec_sc -> Write();
    cX_nocuts_sc -> Write();
    cX_fin_sc -> Write();
    
    f -> Close();
    
    
     
}
