void nice_canv1(TVirtualPad * c)
{
    c -> SetBottomMargin(0.15);
    c -> SetLeftMargin(0.15);
    gStyle -> SetTitleSize(0.07, "xy");
    gStyle -> SetLabelSize(0.06, "xy");
    gStyle -> SetTitleOffset(1.1, "xy");
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
    TH1F *hrealXSum = new TH1F("hrealXSum", "hrealXSum", nbinsX, minX, maxX);
    TH1F *hLallSumSc = new TH1F("hLallSumSc", "hLallSumSc", nbinsL, minL, maxL);
    TH1F *hrealLSumSc = new TH1F("hrealLSumSc", "hrealLSumSc", nbinsL, minL, maxL);
    TH1F *hrealXSumSc = new TH1F("hrealXSumSc", "hrealXSumSc", nbinsX, minX, maxX);

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
    TH1F *hLall90Peak = new TH1F("hLall90Peak", "hLall90Peak", nbinsL, minL, maxL);
    TH1F *hrealL90Peak = new TH1F("hrealL90Peak", "hrealL90Peak", nbinsL, minL, maxL);
    TH1F *hrealX90Peak = new TH1F("hrealX90Peak", "hrealX90Peak", nbinsX, minX, maxX);
    TH1F *hLall90ScPeak = new TH1F("hLall90ScPeak", "hLall90ScPeak", nbinsL, minL, maxL);
    TH1F *hrealL90ScPeak = new TH1F("hrealL90ScPeak", "hrealL90ScPeak", nbinsL, minL, maxL);
    TH1F *hrealX90ScPeak = new TH1F("hrealX90ScPeak", "hrealX90ScPeak", nbinsX, minX, maxX);
    
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
    TH1F *hrealLSumLmass = new TH1F("hrealLSumLmass", "hrealLSumLmass", nbinsL, minL, maxL);
    TH1F *hrealXSumMtd = new TH1F("hrealXSumMtd", "hrealXSumMtd", nbinsX, minX, maxX);
    TH1F *hLallSumScMtd = new TH1F("hLallSumScMtd", "hLallSumScMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumScLmassMtd = new TH1F("hrealLSumScLmassMtd", "hrealLSumScLmassMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumScMtd = new TH1F("hrealLSumScMtd", "hrealLSumScMtd", nbinsL, minL, maxL);
    TH1F *hrealXSumScMtd = new TH1F("hrealXSumScMtd", "hrealXSumScMtd", nbinsX, minX, maxX);

    TH1F *hLallSumBGMtd = new TH1F("hLallSumBGMtd", "hLallSumBGMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumBGMtd = new TH1F("hrealLSumBGMtd", "hrealLSumBGMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakMtd = new TH1F("hrealLSumPeakMtd", "hrealLSumPeakMtd", nbinsL, minL, maxL);
    TH1F *hLallSumBGScMtd = new TH1F("hLallSumBGScMtd", "hLallSumBGScMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumBGScMtd = new TH1F("hrealLSumBGScMtd", "hrealLSumBGScMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakScMtd = new TH1F("hrealLSumPeakScMtd", "hrealLSumPeakScMtd", nbinsL, minL, maxL);

    TH1F *hLallSumBGLmass = new TH1F("hLallSumBGLmass", "hLallSumBGLmass", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakLmass = new TH1F("hrealLSumPeakLmass", "hrealLSumPeakLmass", nbinsL, minL, maxL);
    TH1F *hLallSumBGScLmass = new TH1F("hLallSumBGScLmass", "hLallSumBGScLmass", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakScLmass = new TH1F("hrealLSumPeakScLmass", "hrealLSumPeakScLmass", nbinsL, minL, maxL);

     TH1F *hXallSumBGMtd = new TH1F("hXallSumBGMtd", "hXallSumBGMtd", nbinsX, minX, maxX);
     TH1F *hrealXSumBGMtd = new TH1F("hrealXSumBGMtd", "hrealXSumBGMtd", nbinsX, minX, maxX);
     TH1F *hrealXSumPeakMtd = new TH1F("hrealXSumPeakMtd", "hrealXSumPeakMtd", nbinsX, minX,maxX);
     TH1F *hXallSumBGScMtd = new TH1F("hXallSumBGScMtd", "hXallSumBGScMtd", nbinsX, minX, maxX);
     TH1F *hrealXSumBGScMtd = new TH1F("hrealXSumBGScMtd", "hrealXSumBGScMtd", nbinsX, minX, maxX);
     TH1F *hrealXSumPeakScMtd = new TH1F("hrealXSumPeakScMtd", "hrealXSumPeakScMtd", nbinsX, minX, maxX);
    
    //only signal channel 090
    TH1F *hLall90Mtd, *hrealL90Mtd, *hrealX90Mtd, *hLall90ScMtd, *hrealL90ScMtd, *hrealX90ScMtd;
    TH1F *hLall90MtdPeak = new TH1F("hLall90MtdPeak", "hLall90MtdPeak", nbinsL, minL, maxL);
    TH1F *hrealL90MtdPeak = new TH1F("hrealL90MtdPeak", "hrealL90MtdPeak", nbinsL, minL, maxL);
    TH1F *hrealX90MtdPeak = new TH1F("hrealX90MtdPeak", "hrealX90MtdPeak", nbinsX, minX,maxX);
    TH1F *hLall90ScMtdPeak = new TH1F("hLall90ScMtdPeak", "hLall90ScMtdPeak", nbinsL, minL, maxL);
    TH1F *hrealL90ScMtdPeak = new TH1F("hrealL90ScMtdPeak", "hrealL90ScMtdPeak", nbinsL, minL, maxL);
    TH1F *hrealX90ScMtdPeak = new TH1F("hrealX90ScMtdPeak", "hrealX90ScMtdPeak", nbinsX, minX,maxX);;

    TCanvas *cLambdaXiMassMtd = new TCanvas("cLambdaXiMassMtd", "Lambda & Xi invariant mass, MTD_L, Lmass, MTD_X", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels
    TCanvas *cLambdaXiMassScMtd = new TCanvas("cLambdaXiMassScMtd", "Lambda & Xi invariant mass (cr sc), MTD_L, Lmass, MTD_X", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels with crsec
    cLambdaXiMassMtd -> Divide(3,2);
    cLambdaXiMassScMtd -> Divide(3,2);

    //MTD_L, Lmass, MTD_X, Vertz_X
    //Lambda1115
    TH1F *hLVertex_sig = new TH1F("hLVertex_sig", "hLVertex_sig", 150, -100, 500); //Lambda1115 vertex_z signal
    TH1F *hLVertex_bg = new TH1F("hLVertex_bg", "hLVertex_bg", 150, -100, 500); //Lambda1115 vertex_z bg
    TH1F *hLVertex_bg_sum = new TH1F("hLVertex_bg_sum", "#Lambda/(1115/) vertex reconstruction --- background channels sum", 150, -100, 500); //Xi vertex_z bg sum

    TH1F *hLallSumVert = new TH1F("hLallSumVert", "hLallSumVert", nbinsL, minL, maxL);
    TH1F *hrealLSumVert = new TH1F("hrealLSumVert", "hrealLSumVert", nbinsL, minL, maxL);
    TH1F *hrealXSumVert = new TH1F("hrealXSumVert", "hrealXSumVert", nbinsX, minX, maxX);
    TH1F *hLallSumScVert = new TH1F("hLallSumScVert", "hLallSumScVert", nbinsL, minL, maxL);
    TH1F *hrealLSumScVert = new TH1F("hrealLSumScVert", "hrealLSumScVert", nbinsL, minL, maxL);
    TH1F *hrealXSumScVert = new TH1F("hrealXSumScVert", "hrealXSumScVert", nbinsX, minX, maxX);

    TH1F *hLallSumBGVert = new TH1F("hLallSumBGVert", "hLallSumBGVert", nbinsL, minL, maxL);
    TH1F *hrealLSumBGVert = new TH1F("hrealLSumBGVert", "hrealLSumBGVert", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakVert = new TH1F("hrealLSumPeakVert", "hrealLSumPeakVert", nbinsL, minL, maxL);
    TH1F *hLallSumBGScVert = new TH1F("hLallSumBGScVert", "hLallSumBGScVert", nbinsL, minL, maxL);
    TH1F *hrealLSumBGScVert = new TH1F("hrealLSumBGScVert", "hrealLSumBGScVert", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakScVert = new TH1F("hrealLSumPeakScVert", "hrealLSumPeakScVert", nbinsL, minL, maxL);

    TH1F *hXallSumBGVert = new TH1F("hXallSumBGVert", "hXallSumBGVert", nbinsX, minX, maxX);
    TH1F *hrealXSumBGVert = new TH1F("hrealXSumBGVert", "hrealXSumBGVert", nbinsX, minX, maxX);
    TH1F *hrealXSumPeakVert = new TH1F("hrealXSumPeakVert", "hrealXSumPeakVert", nbinsX, minX, maxX);
    TH1F *hXallSumBGScVert = new TH1F("hXallSumBGScVert", "hXallSumBGScVert", nbinsX, minX, maxX);
    TH1F *hrealXSumBGScVert = new TH1F("hrealXSumBGScVert", "hrealXSumBGScVert", nbinsX, minX, maxX);
    TH1F *hrealXSumPeakScVert = new TH1F("hrealXSumPeakScVert", "hrealXSumPeakScVert", nbinsX, minX, maxX);

    //only signal channel 090
    TH1F *hLall90Vert, *hrealL90Vert, *hrealX90Vert, *hLall90ScVert, *hrealL90ScVert, *hrealX90ScVert;
    TH1F *hLall90VertPeak = new TH1F("hLall90VertPeak", "hLall90VertPeak", nbinsL, minL, maxL);
    TH1F *hrealL90VertPeak = new TH1F("hrealL90VertPeak", "hrealL90VertPeak", nbinsL, minL, maxL);
    TH1F *hrealX90VertPeak = new TH1F("hrealX90VertPeak", "hrealX90VertPeak", nbinsX, minX, maxX);
    TH1F *hLall90ScVertPeak  = new TH1F("hLall90ScVertPeak", "hLall90ScVertPeak", nbinsL, minL, maxL);
    TH1F *hrealL90ScVertPeak = new TH1F("hLall90ScVertPeak", "hLall90ScVertPeak", nbinsL, minL, maxL);
    TH1F *hrealX90ScVertPeak = new TH1F("hrealX90ScVertPeak", "hrealX90ScVertPeak", nbinsX, minX, maxX);
    
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

    for(int i = 0; i < 7; i++){
      sprintf(chanNo, "../XiRealPID/outputs_ch/output_%03d_test5.root", chan[i]);
      	TFile *f1 = TFile::Open(chanNo, "READ");

	TPaveText *ptch = new TPaveText(.5, .7, .8, .85, "NDC");
	ptch -> SetFillColor(0);
	ptch -> SetBorderSize(0);
	ptch -> SetTextSize(0.07);
	ptch -> AddText(reac[i].c_str());

	//no cuts
	TH1F *hAllHFd = (TH1F*)f1->Get("hMLAll"); //all combinations of H-FD
	TH1F *hLall = (TH1F*)f1->Get("hMLPiHades"); //pi in H, anth in FD
	TH1F *hrealL = (TH1F*)f1->Get("hMLPiHpF"); //pion in H, p in FD
	TH1F *hrealX = (TH1F*)f1->Get("hMXAll"); //Lambda and pion in H, in mL range

	hAllHFd -> Rebin(2);
	hLall -> Rebin(2);
	hrealL -> Rebin(2);
	hrealX -> Rebin(2);

	//spectrum MTD_L
	TH1F *hMTD_Lall = (TH1F*)f1 -> Get("hTDpiFD"); //distance between anything in FD and pion in H
	TH1F *hMTD_Lreal = (TH1F*)f1 -> Get("hTDpip"); //distance between proton in FD and pion in H

	//spectrum MTD_X
	TH1F *hMTD_Xreal = (TH1F*)f1 -> Get("hTDpiL"); //distance between Lambda and pion in H
	
	//MTD_L, Lmass, MTD_X
	TH1F *hLallMtd = (TH1F*)f1->Get("hMLPiHadesMTD"); //pion in H, anything in FD, MTD_X
	TH1F *hrealLMtd = (TH1F*)f1->Get("hMLPiHpFMTD"); //pion in H, proton in FD, MTD_X
	TH1F *hrealXMtd = (TH1F*)f1->Get("hMXPiLMTD"); //Lambda and pion in H, MTD_X

	hLallMtd -> Rebin(2);
	hrealLMtd -> Rebin(2);
	hrealXMtd -> Rebin(2);

	//spectrum Vertz_L
	TH1F *hVertz_Lall = (TH1F*)f1 -> Get("hVertpiFD"); //vertZ of anything in FD and pion in H 
	TH1F *hVertz_Lreal = (TH1F*)f1 -> Get("hVertpip"); //vertZ of proton in FD and pion in H 

	//spectrum Vertz_X
	TH1F *hVertz_Xreal = (TH1F*)f1 -> Get("hXVertpiL"); //vertZ of Lambda and pion in H 

	//MTD_L, Lmass, MTD_X, Vertz_X
	TH1F *hLallVert = (TH1F*)f1->Get("hMLPiHadesMTDVert"); //pion in H, anything in FD, MTD_X
	TH1F *hrealLVert = (TH1F*)f1->Get("hMLPiHpFMTDVert"); //pion in H, proton in FD, MTD_X
	TH1F *hrealXVert = (TH1F*)f1->Get("hMXPiLMTDVert"); //Lambda and pion in H, MTD_X

	hLallVert -> Rebin(2);
	hrealLVert -> Rebin(2);
	hrealXVert -> Rebin(2);

	int col = i+1;
	if(i == 2) col = 8;
	if(i == 4) col = 42;
	if(i == 6) col = 15;

	//no cuts
	TH1F *hLall1 = (TH1F*)hLall -> Clone("hLall1_c");
	TH1F *hLall1sc = (TH1F*)hLall -> Clone("hLall1sc_c");
	TH1F *hrealL1 = (TH1F*)hrealL -> Clone("hrealL1_c");
	TH1F *hrealL1sc = (TH1F*)hrealL -> Clone("hrealL1sc_c");
	TH1F *hrealX1 = (TH1F*)hrealX -> Clone("hrealX1_c");
	TH1F *hrealX1sc = (TH1F*)hrealX -> Clone("hrealX1sc_c");

	TH1F *clLambdaSc = (TH1F*)hrealL -> Clone("hLall_chan");
	TH1F *clXiSc = (TH1F*)hrealX -> Clone("hrealX_chan");

      	hLall1sc -> Scale(cr_sec[i]);
	hrealL1sc -> Scale(cr_sec[i]);
	hrealX1sc -> Scale(cr_sec[i]);

	hLallSum -> Add(hLall1);
	hrealLSum -> Add(hrealL1);
	hrealXSum -> Add(hrealX1);
	
	hLallSumSc -> Add(hLall1sc);
	hrealLSumSc -> Add(hrealL1sc);
	hrealXSumSc -> Add(hrealX1sc);

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
	TH1F *hrealX1Mtd = (TH1F*)hrealXMtd -> Clone("hrealX1_cMtd");
      	TH1F *hrealX1scMtd = (TH1F*)hrealXMtd -> Clone("hrealX1sc_cMtd");

	TH1F *clXiSc_fin = (TH1F*)hrealXMtd -> Clone("hrealX1sc_cMtd_fin");
	
      	hLall1scMtd -> Scale(cr_sec[i]);
	hrealL1scMtd -> Scale(cr_sec[i]);
	hrealX1scMtd -> Scale(cr_sec[i]);

	hLallSumMtd -> Add(hLall1Mtd);
	hrealLSumMtd -> Add(hrealL1Mtd);
	hrealXSumMtd -> Add(hrealX1Mtd);

	hLallSumScMtd -> Add(hLall1scMtd);
	hrealLSumScMtd -> Add(hrealL1scMtd);
	hrealXSumScMtd -> Add(hrealX1scMtd);

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

	TH1F *hrealX1Vert = (TH1F*)hrealXVert -> Clone("hrealX1_cVert");
	TH1F *hrealX1scVert = (TH1F*)hrealXVert -> Clone("hrealX1sc_cVert");
	
        TH1F *clLambdaScVertrec = (TH1F*)hrealLVert -> Clone("hLallVert_chan");
	
      	hLall1scVert -> Scale(cr_sec[i]);
	hrealL1scVert -> Scale(cr_sec[i]);
	hrealX1scVert -> Scale(cr_sec[i]);

	hLallSumVert -> Add(hLall1Vert);
	hrealLSumVert -> Add(hrealL1Vert);
	hrealXSumVert -> Add(hrealX1Vert);

	hLallSumScVert -> Add(hLall1scVert);
	hrealLSumScVert -> Add(hrealL1scVert);
	hrealXSumScVert -> Add(hrealX1scVert);

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
	}


    }//***********************************************************************************
    //no cuts
    //Lambda1115
    double MassminL = 1105;
    double MassmaxL = 1125;
    double massL, massLSc;
    int nL = hrealLSum -> GetNbinsX();
    int nLSc = hrealLSumSc -> GetNbinsX();

    double s_bg_vL[150];
    double binL[150]; 
    int kL = -1;
    double s_bg_vLSc[150];
    double binLSc[150];
    int kLSc = -1;

    /*hrealLSum -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealLSum -> GetXaxis() -> FindBin(MassminL);
    b = hrealLSum -> GetXaxis() -> FindBin(MassmaxL);
/*    MassminL = m3sigma;
    MassmaxL = p3sigma;*/
    
    for(int j = 1; j <= nL; j++){
      massL = hrealLSum -> GetBinLowEdge(j);
      if(massL < MassminL) continue;
      else if(massL > MassmaxL) break;
      else{
	hrealLSumPeak -> SetBinContent(j, hrealLSum -> GetBinContent(j));
	hrealL90Peak -> SetBinContent(j, hrealL90 -> GetBinContent(j));
      }
    }

    /*hrealLSumSc -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealLSumSc -> GetXaxis() -> FindBin(MassminL);
    b = hrealLSumSc -> GetXaxis() -> FindBin(MassmaxL);
/*    MassminL = m3sigma;
    MassmaxL = p3sigma;*/
    for(int j = 1; j <= nLSc; j++){
      massLSc = hrealLSumSc -> GetBinLowEdge(j);
      if(massLSc < MassminL) continue;
      else if(massLSc > MassmaxL) break;
      else{
	  hrealLSumPeakSc -> SetBinContent(j, hrealLSumSc -> GetBinContent(j));
	  hrealL90ScPeak -> SetBinContent(j, hrealL90Sc -> GetBinContent(j));
      }
    }
    cout << "peak made" << endl;
    TH1F *hrealLSumPeakCl = (TH1F*)hrealLSumPeak -> Clone();
    TH1F *hrealLSumPeakScCl = (TH1F*)hrealLSumPeakSc -> Clone();

    hLallSumBG -> Add(hLallSum, hrealLSumPeakCl, 1, -1); 
    hLallSumBGSc -> Add(hLallSumSc, hrealLSumPeakScCl, 1, -1); 
    hrealLSumBG -> Add(hrealLSum, hrealL90Peak, 1, -1);
    hrealLSumBGSc -> Add(hrealLSumSc, hrealL90ScPeak, 1, -1);

    
    hLallSumBG -> SetLineColor(5);
    hLallSumBGSc -> SetLineColor(5);
    hrealLSumBG -> SetLineColor(kRed);
    hrealLSumBGSc -> SetLineColor(kRed);
    hrealLSumPeak -> SetLineColor(8);
    hrealLSumPeakSc -> SetLineColor(8);
    hrealL90Peak -> SetLineColor(1);
    hrealL90ScPeak -> SetLineColor(1);
    hLallSum -> SetLineColor(4);
    hLallSumSc -> SetLineColor(4);
    hrealLSum -> SetLineColor(46);
    hrealLSumSc -> SetLineColor(46);
       
    cout << "nc: MassminL: " << MassminL << " " << a << " MassmaxL: " << MassmaxL << " " << b << endl;
    
    cntSL = hrealLSum -> Integral(a,b);
    cntBL = hrealLSumBG -> Integral(a,b);
//    cntBL = hLallSumBG -> Integral(a,b);
    cntSLsc = hrealLSumSc -> Integral(a,b);
    cntBLsc = hrealLSumBGSc -> Integral(a,b);
//    cntBLsc = hLallSumBGSc -> Integral(a,b);

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
    double MassminX = 1305;
    double MassmaxX = 1335;
    double massX, massXSc;
    int nX = hrealXSum -> GetNbinsX();
    int nXSc = hrealXSumSc -> GetNbinsX();

    double s_bg_vX[150];
    double binX[150]; 
    int kX = -1;
    double s_bg_vXSc[150];
    double binXSc[150];
    int kXSc = -1;
/*
    hrealXSum -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealXSum -> GetXaxis() -> FindBin(MassminX);
    b = hrealXSum -> GetXaxis() -> FindBin(MassmaxX);
/*    MassminX = m3sigma;
    MassmaxX = p3sigma;*/

    for(int j = 1; j <= nX; j++){
      massX = hrealXSum -> GetBinLowEdge(j);
      if(massX < MassminX) continue;
      else if(massX > MassmaxX) break;
      else{
	  hrealXSumPeak -> SetBinContent(j, hrealXSum -> GetBinContent(j));
	  hrealX90Peak -> SetBinContent(j, hrealX90 -> GetBinContent(j));
      }
    }/*
    hrealXSumSc -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealXSumSc -> GetXaxis() -> FindBin(MassminX);
    b = hrealXSumSc -> GetXaxis() -> FindBin(MassmaxX);
/*    MassminX = m3sigma;
    MassmaxX = p3sigma;*/
    for(int j = 1; j <= nXSc; j++){
	massXSc = hrealXSumSc -> GetBinLowEdge(j);
	if(massXSc < MassminX) continue;
	else if(massXSc > MassmaxX) break;
	else{
	    hrealXSumPeakSc -> SetBinContent(j, hrealXSumSc -> GetBinContent(j));
	    hrealX90ScPeak -> SetBinContent(j, hrealX90Sc -> GetBinContent(j));
	}
    }

    TH1F *hrealXSumPeakCl = (TH1F*)hrealXSumPeak -> Clone();
    TH1F *hrealXSumPeakScCl = (TH1F*)hrealXSumPeakSc -> Clone();
    hXallSumBG -> Add(hrealXSum, hrealXSumPeakCl, 1, -1); 
    hXallSumBGSc -> Add(hrealXSumSc, hrealXSumPeakScCl, 1, -1); 
    hrealXSumBG -> Add(hrealXSum, hrealX90Peak, 1, -1); 
    hrealXSumBGSc -> Add(hrealXSumSc, hrealX90ScPeak, 1, -1); 

    hXallSumBG -> SetLineColor(5);
    hXallSumBGSc -> SetLineColor(5);
    hrealXSumBG -> SetLineColor(kRed);
    hrealXSumBGSc -> SetLineColor(kRed);
    hrealXSumPeak -> SetLineColor(8);
    hrealXSumPeakSc -> SetLineColor(8);
    hrealX90Peak -> SetLineColor(1);
    hrealX90ScPeak -> SetLineColor(1);
    hrealXSum -> SetLineColor(4);
    hrealXSumSc -> SetLineColor(4);

    cout << "MassminX: " << MassminX  << " " << a << " MassmaxX: " << MassmaxX << " " << b << endl;
    
    cntSX = hrealXSum -> Integral(a,b);
    cntBX = hrealXSumBG -> Integral(a,b);
//    cntBX = hXallSumBG -> Integral(a,b);
    cntSXsc = hrealXSumSc -> Integral(a,b);
    cntBXsc = hrealXSumBGSc -> Integral(a,b);
//    cntBXsc = hXallSumBGSc -> Integral(a,b);

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

    l1 -> AddEntry(hLallSumSc, "sum all ch. (#pi^{-}-FD)", "L");
    l1 -> AddEntry(hrealLSumSc, "sum all ch. (#pi^{-}p)", "L");
    l1 -> AddEntry(hrealL90Sc, "#Xi^{-}2K^{+}p", "L");
    l1 -> AddEntry(hLallSumBGSc, "BG all", "L");
    l1 -> AddEntry(hrealLSumBGSc, "BG real", "L");
//    l1 -> AddEntry(hLallSumSc, "p#pi^{-} all", "L");
    l1 -> AddEntry(hrealL90ScPeak, "#Lambda cand. (peak 90)", "L");
//    l1a -> AddEntry(hLallSumBGSc, "BG", "L");
//    l1a -> AddEntry(hLallSumSc, "p#pi^{-}", "L");
//    l1a -> AddEntry(hrealLSumPeakSc, "#Lambda cand. (peak)", "L");

     //invM no scaling
    cLambdaXiMass -> cd(1);
    nice_canv1(gPad);
    hLallSum -> SetTitle("#pi^{-} in Hades + anything in FD");
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
    hrealLSumBG -> SetTitle("p#pi^{-}: real, peak90 and BG");
    hrealLSumBG -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBG -> GetYaxis() -> SetTitle("counts");
    hrealLSum -> Draw();
    hrealL90Peak -> Draw("same");
    hrealLSumBG -> Draw("same");
//    l1a -> Draw("same");
    
    cLambdaXiMass -> cd(4);
    nice_canv1(gPad);
    hrealXSum -> SetTitle("#Lambda + #pi^{-}");
    hrealXSum -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSum -> GetYaxis() -> SetTitle("counts");
    hrealXSum -> Draw();
    hrealX90 -> Draw("same");
//    l1 -> Draw("same");
    
    cLambdaXiMass -> cd(5);
    nice_canv1(gPad);
    hrealXSumBG -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBG -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBG -> GetYaxis() -> SetTitle("counts");
    hrealXSum -> Draw();
    hrealX90Peak -> Draw("same");
    hrealXSumBG -> Draw("same");

    cLambdaXiMass -> cd(6);
    l1 -> Draw("same");

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
    
    TLegend *lfin = new TLegend(.2,.35,.5,.8);
/*    lfin -> AddEntry(hLallSumSc, "sum of all channels");
    lfin -> AddEntry(hrealLSumPeakSc, "peak from all channels");
    lfin -> AddEntry(hLall90Sc, "real signal: #Xi^{-}2K^{+}p");
    lfin -> AddEntry(hLallSumBGSc, "BG");
*/
    //invM scaling
    /*TCanvas *cimLsAsc = new TCanvas("cimLsAsc", "cimLsAsc");
    TCanvas *cimLsRsc = new TCanvas("cimLsRsc", "cimLsRsc");
    TCanvas *cimLsBGsc = new TCanvas("cimLsBGsc", "cimLsBGsc");
    TCanvas *cimXsAsc = new TCanvas("cimXsAsc", "cimXsAsc");
    TCanvas *cimXsRsc = new TCanvas("cimXsRsc", "cimXsRsc");
    TCanvas *cimXsBGsc = new TCanvas("cimXsBGsc", "cimXsBGsc");
    */
    TCanvas *cimLNoCutsSc = new TCanvas("cimLNoCutsSc","cimLNoCutsSc"); //inv mass Lambda spectrum, no cuts, cr sec scaling
    TCanvas *cimXMtdlVertlMlSc = new TCanvas("cimXMtdlVerlMlSc","cimXMtdlVerlMlSc"); //inv mass Xi spectrum, MTD_L, VERTz_L, Lmass cuts, cr sec scaling
    //>>>>>>>>>>>>>>>>>
    cLambdaXiMassSc -> cd(1);
    nice_canv1(gPad);
    hLallSumSc -> SetTitle("#pi^{-} in Hades + anything in FD");
    hLallSumSc -> GetXaxis() -> SetTitle("M_{FD#pi^{-}} [MeV]");
    hLallSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumSc -> Draw();
    hrealLSumSc -> Draw(" same");
    hrealL90Sc -> Draw(" same");
//    l1 -> Draw("same");
    
    /*cimLsAsc -> cd();
    nice_canv1(gPad);
    hLallSumSc -> SetTitle("#pi^{-} in Hades - anything (p) in FwDet");
    hLallSumSc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLall90Sc -> SetMarkerStyle(20);
    hLall90Sc -> SetMarkerSize(.5);
    hLallSumSc -> Draw("pE1");
    hLall90Sc -> Draw("p same");
    l1 -> Draw("same");
    */
    cLambdaXiMassSc -> cd(2);
    nice_canv1(gPad);
    hLallSumBGSc -> SetTitle("p#pi^{-}: all, peak and BG");
    hLallSumBGSc -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumSc -> Draw();
    hrealLSumPeakSc -> Draw("same");
    hLallSumBGSc -> Draw("same");
//    l1a -> Draw("same");

    /*    cimLsRsc -> cd();
    nice_canv1(gPad);
    hrealLSumSc -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumSc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealLSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumSc -> SetMarkerStyle(20);
    hrealLSumSc -> SetMarkerSize(.5);
    hrealLSumSc -> SetMarkerColor(4);
    hrealL90Sc -> SetMarkerStyle(20);
    hrealL90Sc -> SetMarkerSize(.5);
    hrealLSumSc -> Draw("pE1");
    hrealL90Sc -> Draw("p same");
    l1 -> Draw("same");
*/
    cLambdaXiMassSc -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGSc -> SetTitle("p#pi^{-}: all, peak and BG");
    hrealLSumBGSc -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumSc -> Draw();
    hrealL90ScPeak -> Draw("same");
    hrealLSumBGSc -> Draw("same");
//    l1a -> Draw("same");
    
/*    cimLsBGsc -> cd();
    nice_canv1(gPad);
    hLallSumBGSc -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGSc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumBGSc -> SetMarkerStyle(20);
    hLallSumBGSc -> SetMarkerSize(.5);
    hLallSumBGSc -> SetMarkerColor(2);
    hrealLSumPeakSc -> SetMarkerStyle(20);
    hrealLSumPeakSc -> SetMarkerSize(.5);
    hrealLSumPeakSc -> SetMarkerColor(8);
    hLallSumBGSc -> Draw("pE1");
    hrealLSumPeakSc -> Draw("p same");
    l1a -> Draw("same");
*/
    cimLNoCutsSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hLallSumSc -> SetTitle("#Lambda reconstruction, no cuts");
    hLallSumSc -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumSc -> SetLineColor(40);
//    hLallSumSc -> SetLineStyle(2);
    hLallSumSc -> SetLineWidth(2);
    hrealLSumSc -> SetLineColor(46);
//    hrealLSumSc -> SetLineStyle(2);
    hrealLSumSc -> SetLineWidth(2);
    hrealLSumBGSc -> SetMarkerStyle(21);
    hrealLSumBGSc -> SetMarkerSize(.5);
    hrealLSumBGSc -> SetMarkerColor(2);
    hrealLSumPeakSc -> SetLineColor(8);
    hrealL90ScPeak -> SetLineColor(1);
    hLallSumSc -> Draw();
    hrealLSumSc -> Draw("same");
    hrealLSumBGSc -> Draw("p same");
//    hrealLSumPeakSc -> Draw("same");
    hrealL90ScPeak -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");

    lfin -> AddEntry(hLallSumSc, "sum all ch. (#pi^{-}-FD)");
    lfin -> AddEntry(hrealLSumSc, "sum all ch. (#pi^{-}p)");
    lfin -> AddEntry(hrealLSumBGSc, "BG=all-S");
    //  lfin -> AddEntry(hrealLSumPeakSc, "all-BG in mass range");
    lfin -> AddEntry(hrealL90ScPeak, "S in mass range");
    lfin -> Draw("same");//<<<<<<<<<<<<<<

    cLambdaXiMassSc -> cd(4);
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("#Lambda + #pi^{-}");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> Draw();
    hrealX90Sc -> Draw("same");
//    l1 -> Draw("same");
    
/*    cimXsAsc -> cd();
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("2#pi^{-} in Hades - anything (p) in FwDet");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> SetMarkerStyle(20);
    hrealXSumSc -> SetMarkerSize(.5);
    hrealXSumSc -> SetMarkerColor(4);
    hrealX90Sc -> SetMarkerStyle(20);
    hrealX90Sc -> SetMarkerSize(.5);
    hrealXSumSc -> Draw("pE1");
    hrealX90Sc -> Draw("p same");
    l1 -> Draw("same");
		     */  
    /* cLambdaXiMassSc -> cd(5);
    nice_canv1(gPad);
    hXrealLpimSumSc -> SetTitle("#pi^{-} and p from #Lambda(1115) + #pi^{-} in Hades");
    hXrealLpimSumSc -> GetXaxis() -> SetTitle("invM [MeV]");
    hXrealLpimSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hXrealLpimSumSc -> Draw();
    hXrealLpim90Sc -> Draw("same");
    */
/*    cLambdaXiMassSc -> cd(5);
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> Draw("pE1");
    hrealX90Sc -> Draw("p same");
    l1 -> Draw("same");
		     *//*  
    cimXsRsc -> cd();
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> SetMarkerStyle(20);
    hrealXSumSc -> SetMarkerSize(.5);
    hrealXSumSc -> SetMarkerColor(4);
    hrealX90Sc -> SetMarkerStyle(20);
    hrealX90Sc -> SetMarkerSize(.5);
    hrealXSumSc -> Draw("pE1");
    hrealX90Sc -> Draw("p same");
    l1 -> Draw("same");
		     */
    cLambdaXiMassSc -> cd(5);
    nice_canv1(gPad);
    hrealXSumBGSc -> SetTitle("#Xi^{-}: #lambda#pi^{-} all, peak and BG");
    hrealXSumBGSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> Draw();
    hrealX90ScPeak -> Draw("same");
    hrealXSumBGSc -> Draw("same");

    cLambdaXiMassSc -> cd(6);
    l1 -> Draw("same");
    
    /*cimXsBGsc -> cd();
    nice_canv1(gPad);
    hXallSumBGSc -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hXallSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hXallSumBGSc -> SetMarkerStyle(20);
    hXallSumBGSc -> SetMarkerSize(.5);
    hXallSumBGSc -> SetMarkerColor(2);
    hrealXSumPeakSc -> SetMarkerStyle(20);
    hrealXSumPeakSc -> SetMarkerSize(.5);
    hrealXSumPeakSc -> SetMarkerColor(8);
    hXallSumBGSc -> Draw("pE1");
    hrealXSumPeakSc -> Draw("p same");
    l1a -> Draw("same");
    */

    TLegend *lfin1 = new TLegend(.2,.35,.5,.8);

    cimXMtdlVertlMlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass cuts");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> SetLineColor(46);
//    hrealXSumSc -> SetLineStyle(2);
    hrealXSumSc -> SetLineWidth(2);
    hrealXSumBGSc -> SetMarkerStyle(21);
    hrealXSumBGSc -> SetMarkerSize(.5);
    hrealXSumBGSc -> SetMarkerColor(2);
//    hrealXSumPeakSc -> SetLineColor(8);
    hrealX90ScPeak -> SetLineColor(1);
    hrealXSumSc -> Draw();
    hrealXSumBGSc -> Draw("p same");
    hrealXSumPeakSc -> Draw("same");
    hrealX90ScPeak -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");

    lfin1 -> AddEntry(hrealXSumSc, "sum all ch. (#Lambda#pi^{-})");
    lfin1 -> AddEntry(hrealXSumBGSc, "BG=all-S");
    //  lfin1 -> AddEntry(hrealXSumPeakSc, "all-BG in mass range");
    lfin1 -> AddEntry(hrealX90ScPeak, "S in mass range");
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

/*    hrealLSumMtd -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealLSumMtd -> GetXaxis() -> FindBin(MassminL);
    b = hrealLSumMtd -> GetXaxis() -> FindBin(MassmaxL);	 
/*    MassminL = m3sigma;
    MassmaxL = p3sigma;*/
    for(int j = 1; j <= nLMtd; j++){
      massL = hrealLSumMtd -> GetBinLowEdge(j);
      if(massL < MassminL) continue;
      else if(massL > MassmaxL) break;
      else{
	hrealLSumPeakMtd -> SetBinContent(j, hrealLSumMtd -> GetBinContent(j));
	hrealL90MtdPeak -> SetBinContent(j, hrealL90Mtd -> GetBinContent(j));
      }
    }
/*
    hrealLSumScMtd -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealLSumScMtd -> GetXaxis() -> FindBin(MassminL);
    b = hrealLSumScMtd -> GetXaxis() -> FindBin(MassmaxL);
/*    MassminL = m3sigma;
    MassmaxL = p3sigma;*/
    for(int j = 1; j <= nLScMtd; j++){
      massLSc = hrealLSumScMtd -> GetBinLowEdge(j);
      if(massLSc < MassminL) continue;
      else if(massLSc > MassmaxL) break;
      else{
	  hrealLSumPeakScMtd -> SetBinContent(j, hrealLSumScMtd -> GetBinContent(j));
	  hrealL90ScMtdPeak -> SetBinContent(j, hrealL90ScMtd -> GetBinContent(j));
      }
    }

    TH1F *hrealLSumPeakClMtd = (TH1F*)hrealLSumPeakMtd -> Clone();
    TH1F *hrealLSumPeakScClMtd = (TH1F*)hrealLSumPeakScMtd -> Clone();
    hLallSumBGMtd -> Add(hLallSumMtd, hrealLSumPeakClMtd, 1, -1); 
    hLallSumBGScMtd -> Add(hLallSumScMtd, hrealLSumPeakScClMtd, 1, -1); 
    hrealLSumBGMtd -> Add(hrealLSumMtd, hrealL90MtdPeak, 1, -1); 
    hrealLSumBGScMtd -> Add(hrealLSumScMtd, hrealL90ScMtdPeak, 1, -1); 

    hLallSumBGMtd -> SetLineColor(5);
    hLallSumBGScMtd -> SetLineColor(5);
    hrealLSumBGMtd -> SetLineColor(kRed);
    hrealLSumBGScMtd -> SetLineColor(kRed);
    hrealLSumPeakMtd -> SetLineColor(8);
    hrealLSumPeakScMtd -> SetLineColor(8);
    hrealL90MtdPeak -> SetLineColor(1);
    hrealL90ScMtdPeak -> SetLineColor(1);
    hLallSumMtd -> SetLineColor(4);
    hLallSumScMtd -> SetLineColor(4);
    hrealLSumMtd -> SetLineColor(46);
    hrealLSumScMtd -> SetLineColor(46);

    cout << "Mtd: MassminL: " << MassminL << " " << a << " MassmaxL: " << MassmaxL << " " << b << endl;
    
    cntSLMtd = hrealLSumMtd -> Integral(a,b);
    cntBLMtd = hrealLSumBGMtd -> Integral(a,b);
//    cntBLMtd = hLallSumBGMtd -> Integral(a,b);
    cntSLscMtd = hrealLSumScMtd -> Integral(a,b);
    cntBLscMtd = hrealLSumBGScMtd -> Integral(a,b);
//    cntBLscMtd = hLallSumBGScMtd -> Integral(a,b);


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
	if(hrealLSumPeakMtd -> GetBinContent(j)){
	  kLMtd++;
	  s_bg_vLMtd[kLMtd] = (hrealLSumPeakMtd -> GetBinContent(j))/(hrealLSumBGMtd -> GetBinContent(j));
	  binLMtd[kLMtd] = (hrealLSumPeakMtd -> GetBinLowEdge(j)) + (hrealLSumPeakMtd -> GetBinWidth(j));
      	}
    }
    for(int j = 1; j <= nLScMtd; j++){
      if(hrealLSumPeakScMtd -> GetBinContent(j)){
	kLScMtd++;
	s_bg_vLScMtd[kLScMtd] = (hrealLSumPeakScMtd -> GetBinContent(j))/(hrealLSumBGScMtd -> GetBinContent(j));
	binLScMtd[kLScMtd] = (hrealLSumPeakScMtd -> GetBinLowEdge(j)) + (hrealLSumPeakScMtd -> GetBinWidth(j));
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

/*
    hrealXSumMtd -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealXSumMtd -> GetXaxis() -> FindBin(MassminX);
    b = hrealXSumMtd -> GetXaxis() -> FindBin(MassmaxX);	
/*    MassminX = m3sigma;
    MassmaxX = p3sigma;*/
    for(int j = 1; j <= nXMtd; j++){
      massX = hrealXSumMtd -> GetBinLowEdge(j);
      if(massX < MassminX) continue;
      else if(massX > MassmaxX) break;
      else{
	  hrealXSumPeakMtd -> SetBinContent(j, hrealXSumMtd -> GetBinContent(j));
	  hrealX90MtdPeak -> SetBinContent(j, hrealX90Mtd -> GetBinContent(j));
      }
    }/*
    hrealXSumScMtd -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealXSumScMtd -> GetXaxis() -> FindBin(MassminX);
    b = hrealXSumScMtd -> GetXaxis() -> FindBin(MassmaxX);
/*    MassminX = m3sigma;
    MassmaxX = p3sigma;*/
    for(int j = 1; j <= nXScMtd; j++){
      massXSc = hrealXSumScMtd -> GetBinLowEdge(j);
      if(massXSc < MassminX) continue;
      else if(massXSc > MassmaxX) break;
      else{
	  hrealXSumPeakScMtd -> SetBinContent(j, hrealXSumScMtd -> GetBinContent(j));
	  hrealX90ScMtdPeak -> SetBinContent(j, hrealX90ScMtd -> GetBinContent(j));
      }
    }

    TH1F *hrealXSumPeakClMtd = (TH1F*)hrealXSumPeakMtd -> Clone();
    TH1F *hrealXSumPeakScClMtd = (TH1F*)hrealXSumPeakScMtd -> Clone();
   
    hXallSumBGMtd -> Add(hrealXSumMtd, hrealXSumPeakClMtd, 1, -1); 
    hXallSumBGScMtd -> Add(hrealXSumScMtd, hrealXSumPeakScClMtd, 1, -1); 
    hrealXSumBGMtd -> Add(hrealXSumMtd, hrealX90MtdPeak, 1, -1); 
    hrealXSumBGScMtd -> Add(hrealXSumScMtd, hrealX90ScMtdPeak, 1, -1); 

    hXallSumBGMtd -> SetLineColor(5);
    hXallSumBGScMtd -> SetLineColor(5);
    hrealXSumBGMtd -> SetLineColor(kRed);
    hrealXSumBGScMtd -> SetLineColor(kRed);
    hrealXSumPeakMtd -> SetLineColor(8);
    hrealXSumPeakScMtd -> SetLineColor(8);
    hrealX90MtdPeak -> SetLineColor(1);
    hrealX90ScMtdPeak -> SetLineColor(1);
    hrealXSumMtd -> SetLineColor(4);
    hrealXSumScMtd -> SetLineColor(4);

    cout << "MassminX: " << MassminX << " " << a << " MassmaxX: " << MassmaxX << " " << b << endl;
    
    cntSXMtd = hrealXSumMtd -> Integral(a,b);
    cntBXMtd = hrealXSumBGMtd -> Integral(a,b);
//    cntBXMtd = hXallSumBGMtd -> Integral(a,b);
    cntSXscMtd = hrealXSumScMtd -> Integral(a,b);
    cntBXscMtd = hrealXSumBGScMtd -> Integral(a,b);
//    cntBXscMtd = hXallSumBGScMtd -> Integral(a,b);

    cntSXMtd90 = hrealX90MtdPeak -> Integral(a,b);
    
    for(int j = 1; j <= nXMtd; j++){
      if(hrealXSumPeakMtd -> GetBinContent(j)){
	kXMtd++;
	s_bg_vXMtd[kXMtd] = (hrealXSumPeakMtd -> GetBinContent(j))/(hrealXSumBGMtd -> GetBinContent(j));
	binXMtd[kXMtd] = (hrealXSumPeakMtd -> GetBinLowEdge(j)) + (hrealXSumPeakMtd -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nXScMtd; j++){
      if(hrealXSumPeakScMtd -> GetBinContent(j)){
	kXScMtd++;
	s_bg_vXScMtd[kXScMtd] = (hrealXSumPeakScMtd -> GetBinContent(j))/(hrealXSumBGScMtd -> GetBinContent(j));
	binXScMtd[kXScMtd] = (hrealXSumPeakScMtd -> GetBinLowEdge(j)) + (hrealXSumPeakScMtd -> GetBinWidth(j));
      }
    }

    //invM no scaling MTD
    cLambdaXiMassMtd -> cd(1);
    nice_canv1(gPad);
    hLallSumMtd -> SetTitle("#pi^{-} in Hades + anything in FD");
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
    hrealLSumPeakMtd -> Draw("same");
    hLallSumBGMtd -> Draw("same");
    
//    l1a -> Draw("same");

    cLambdaXiMassMtd -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGMtd -> SetTitle("p#pi^{-}: real, peak90 and BG");
    hrealLSumBGMtd -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hrealLSumMtd -> Draw();
    hrealL90MtdPeak -> Draw("same");
    hrealLSumBGMtd -> Draw("same");

//    l1a -> Draw("same");

    cLambdaXiMassMtd -> cd(4);
    nice_canv1(gPad);
    hrealXSumMtd -> SetTitle("#Lambda + #pi^{-}");
    hrealXSumMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumMtd -> GetYaxis() -> SetTitle("counts");
    hrealXSumMtd -> Draw();
    hrealX90Mtd -> Draw("same");
//   l1 -> Draw("same");

    cLambdaXiMassMtd -> cd(5);
    nice_canv1(gPad);
    hrealXSumBGMtd -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hrealXSumMtd -> Draw();
    hrealX90MtdPeak -> Draw("same");
    hrealXSumBGMtd -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassMtd -> cd(6);
    l1 -> Draw("same");

    //invM scaling MTD
/*    TCanvas *cimLsAmtdsc = new TCanvas("cimLsAmtdsc", "cimLsAmtdsc");
    TCanvas *cimLsRmtdsc = new TCanvas("cimLsRmtdsc", "cimLsRmtdsc");
    TCanvas *cimLsBGmtdsc = new TCanvas("cimLsBGmtdsc", "cimLsBGmtdsc");
    TCanvas *cimXsAmtdsc = new TCanvas("cimXsAmtdsc", "cimXsAmtdsc");
    TCanvas *cimXsRmtdsc = new TCanvas("cimXsRmtdsc", "cimXsRmtdsc");
    TCanvas *cimXsBGmtdsc = new TCanvas("cimXsBGmtdsc", "cimXsBGmtdsc");
*/
    TCanvas *cimLMtdlSc = new TCanvas("cimLMtdlSc","cimLMtdlSc"); //inv mass Lambda spectrum, MTD_L cut, cr sec scaling
    TCanvas *cimXMtdlVertlMlMtdxSc = new TCanvas("cimXMtdlVerlMlMtdxSc","cimXMtdlVerlMlMtdxSc"); //inv mass Xi spectrum, MTD_L, VERTz_L, Lmass, MTD_X cuts, cr sec scaling
    
    cLambdaXiMassScMtd -> cd(1);
    nice_canv1(gPad);
    hLallSumScMtd -> SetTitle("#pi^{-} in Hades + anything in FD");
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
    hrealLSumPeakScMtd -> Draw("same");
    hLallSumBGScMtd -> Draw("same");
//    l1a -> Draw("same");
      
    cLambdaXiMassScMtd -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGScMtd -> SetTitle("p#pi^{-}: real, peak90 and BG");
    hrealLSumBGScMtd -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumScMtd -> Draw();
    hrealL90ScMtdPeak -> Draw("same");
    hrealLSumBGScMtd -> Draw("same");
//    l1a -> Draw("same");
    
    TLegend *lfin2 = new TLegend(.2,.35,.5,.8);
    
    cimLMtdlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hLallSumScMtd -> SetTitle("#Lambda reconstruction, MTD_L cut");
    hLallSumScMtd -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScMtd -> SetLineColor(40);
//    hLallSumScMtd -> SetLineStyle(2);
    hLallSumScMtd -> SetLineWidth(2);
    hrealLSumScMtd -> SetLineColor(46);
//    hrealLSumScMtd -> SetLineStyle(2);
    hrealLSumScMtd -> SetLineWidth(2);
    hrealLSumBGScMtd -> SetMarkerStyle(21);
    hrealLSumBGScMtd -> SetMarkerSize(.5);
    hrealLSumBGScMtd -> SetMarkerColor(2);
    hrealLSumPeakScMtd -> SetLineColor(8);
    hrealL90ScMtd -> SetLineColor(1);
    hLallSumScMtd -> Draw();
    hrealLSumScMtd -> Draw("same");
    hrealLSumBGScMtd -> Draw("p same");
//    hrealLSumPeakScMtd -> Draw("same");
    hrealL90ScMtdPeak -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");

    lfin2 -> AddEntry(hLallSumScMtd, "sum all ch. (#pi^{-}-FD)");
    lfin2 -> AddEntry(hrealLSumScMtd, "sum all ch. (#pi^{-}p)");
    lfin2 -> AddEntry(hrealLSumBGScMtd, "BG=all-S");
    //  lfin2 -> AddEntry(hrealLSumPeakScMtd, "all-BG in mass range");
    lfin2 -> AddEntry(hrealL90ScMtdPeak, "S in mass range");
    lfin2 -> Draw("same");//<<<<<<<<<<<<<<

    cLambdaXiMassScMtd -> cd(4);
    nice_canv1(gPad);
    hrealXSumScMtd -> SetTitle("#Lambda + #pi^{-}");
    hrealXSumScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScMtd -> Draw();
    hrealX90ScMtd -> Draw("same");
//    l1 -> Draw("same");
    
    cLambdaXiMassScMtd -> cd(5);
    nice_canv1(gPad);
    hrealXSumBGScMtd -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScMtd -> Draw();
    hrealX90ScMtdPeak -> Draw("same");
    hrealXSumBGScMtd -> Draw("same");

    cLambdaXiMassScMtd -> cd(6);
    l1 -> Draw("same");

    TLegend *lfin3 = new TLegend(.2,.35,.5,.8);
        
    cimXMtdlVertlMlMtdxSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumScMtd -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass, MTD_X cuts");
    hrealXSumScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScMtd -> SetLineColor(46);
//    hrealXSumScMtd -> SetLineStyle(2);
    hrealXSumScMtd -> SetLineWidth(2);
    hrealXSumBGScMtd -> SetMarkerStyle(21);
    hrealXSumBGScMtd -> SetMarkerSize(.5);
    hrealXSumBGScMtd -> SetMarkerColor(2);
    hrealXSumPeakScMtd -> SetLineColor(8);
    hrealX90ScMtdPeak -> SetLineColor(1);
    hrealXSumScMtd -> Draw();   
    hrealXSumBGScMtd -> Draw("p same");
//    hrealXSumPeakScMtd -> Draw("same");
    hrealX90ScMtdPeak -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");

    lfin3 -> AddEntry(hrealXSumScMtd, "sum all ch. (#pi^{-}p)");
    lfin3 -> AddEntry(hrealXSumBGScMtd, "BG =all-S");
    //  lfin3 -> AddEntry(hrealXSumPeakScMtd, "all-BG in mass range");
    lfin3 -> AddEntry(hrealX90ScMtdPeak, "S in mass range");
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

    /*
    hrealLSumVert -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealLSumVert -> GetXaxis() -> FindBin(MassminL);
    b = hrealLSumVert -> GetXaxis() -> FindBin(MassmaxL);
/*    MassminL = m3sigma;
    MassmaxL = p3sigma;*/
    for(int j = 1; j <= nLVert; j++){
      massL = hrealLSumVert -> GetBinLowEdge(j);
      if(massL < MassminL) continue;
      else if(massL > MassmaxL) break;
      else{
	  hrealLSumPeakVert -> SetBinContent(j, hrealLSumVert -> GetBinContent(j));
	  hrealL90VertPeak -> SetBinContent(j, hrealL90Vert -> GetBinContent(j));
      }
    }/*
    hrealLSumScVert -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealLSumScVert -> GetXaxis() -> FindBin(MassminL);
    b = hrealLSumScVert -> GetXaxis() -> FindBin(MassmaxL);
/*    MassminL = m3sigma;
    MassmaxL = p3sigma;*/
    for(int j = 1; j <= nLScVert; j++){
      massLSc = hrealLSumScVert -> GetBinLowEdge(j);
      if(massLSc < MassminL) continue;
      else if(massLSc > MassmaxL) break;
      else{
	  hrealLSumPeakScVert -> SetBinContent(j, hrealLSumScVert -> GetBinContent(j));
	  hrealL90ScVertPeak -> SetBinContent(j, hrealL90ScVert -> GetBinContent(j));
      }
    }

    TH1F *hrealLSumPeakClVert = (TH1F*)hrealLSumPeakVert -> Clone();
    TH1F *hrealLSumPeakScClVert = (TH1F*)hrealLSumPeakScVert -> Clone();
    hLallSumBGVert -> Add(hLallSumVert, hrealLSumPeakClVert, 1, -1); 
    hLallSumBGScVert -> Add(hLallSumScVert, hrealLSumPeakScClVert, 1, -1);
    hrealLSumBGVert -> Add(hrealLSumVert, hrealL90VertPeak, 1, -1); 
    hrealLSumBGScVert -> Add(hrealLSumScVert, hrealL90ScVertPeak, 1, -1); 

    hLallSumBGVert -> SetLineColor(5);
    hLallSumBGScVert -> SetLineColor(5);
    hrealLSumBGVert -> SetLineColor(kRed);
    hrealLSumBGScVert -> SetLineColor(kRed);
    hrealLSumPeakVert -> SetLineColor(8);
    hrealLSumPeakScVert -> SetLineColor(8);
    hrealL90VertPeak -> SetLineColor(1);
    hrealL90ScVertPeak -> SetLineColor(1);
    hLallSumVert -> SetLineColor(4);
    hLallSumScVert -> SetLineColor(4);
    hrealLSumVert -> SetLineColor(46);
    hrealLSumScVert -> SetLineColor(46);

    cout << "Vert: MassminL: " << MassminL << " " << a << " MassmaxL: " << MassmaxL << " " << b << endl;
    
    cntSLVert = hrealLSumVert -> Integral(a,b);
    cntBLVert = hrealLSumBGVert -> Integral(a,b);
//    cntBLVert = hLallSumBGVert -> Integral(a,b);
    cntSLscVert = hrealLSumScVert -> Integral(a,b);
    cntBLscVert = hrealLSumBGScVert -> Integral(a,b);
//    cntBLscVert = hLallSumBGScVert -> Integral(a,b);

    //SB
    for(int j = 1; j <= nLVert; j++){
      if(hrealLSumPeakVert -> GetBinContent(j)){
	kLVert++;
	s_bg_vLVert[kLVert] = (hrealLSumPeakVert -> GetBinContent(j))/(hrealLSumBGVert -> GetBinContent(j));
	binLVert[kLVert] = (hrealLSumPeakVert -> GetBinLowEdge(j)) + (hrealLSumPeakVert -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nLScVert; j++){
      if(hrealLSumPeakScVert -> GetBinContent(j)){
	kLScVert++;
	s_bg_vLScVert[kLScVert] = (hrealLSumPeakScVert -> GetBinContent(j))/(hrealLSumBGScVert -> GetBinContent(j));
	binLScVert[kLScVert] = (hrealLSumPeakScVert -> GetBinLowEdge(j)) + (hrealLSumPeakScVert -> GetBinWidth(j));
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

    /*hrealXSumVert-> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealXSumVert -> GetXaxis() -> FindBin(MassminX);
    b = hrealXSumVert -> GetXaxis() -> FindBin(MassmaxX);
/*    MassminX = m3sigma;
    MassmaxX = p3sigma;*/
    for(int j = 1; j <= nXVert; j++){
      massX = hrealXSumVert -> GetBinLowEdge(j);
      if(massX < MassminX) continue;
      else if(massX > MassmaxX) break;
      else{
	  hrealXSumPeakVert -> SetBinContent(j, hrealXSumVert -> GetBinContent(j));
	  hrealX90VertPeak -> SetBinContent(j, hrealX90Vert -> GetBinContent(j));
      }
    }/*
    hrealXSumScVert-> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;*/
    a = hrealXSumScVert -> GetXaxis() -> FindBin(MassminX);
    b = hrealXSumScVert -> GetXaxis() -> FindBin(MassmaxX);
/*    MassminX = m3sigma;
    MassmaxX = p3sigma;*/
    for(int j = 1; j <= nXScVert; j++){
      massXSc = hrealXSumScVert -> GetBinLowEdge(j);
      if(massXSc < MassminX) continue;
      else if(massXSc > MassmaxX) break;
      else{
	  hrealXSumPeakScVert -> SetBinContent(j, hrealXSumScVert -> GetBinContent(j));
	  hrealX90ScVertPeak -> SetBinContent(j, hrealX90ScVert -> GetBinContent(j));
      }
    }

    TH1F *hrealXSumPeakClVert = (TH1F*)hrealXSumPeakVert -> Clone();
    TH1F *hrealXSumPeakScClVert = (TH1F*)hrealXSumPeakScVert -> Clone();

    hXallSumBGVert -> Add(hrealXSumVert, hrealXSumPeakClVert, 1, -1); 
    hXallSumBGScVert -> Add(hrealXSumScVert, hrealXSumPeakScClVert, 1, -1); 
    hrealXSumBGVert -> Add(hrealXSumVert, hrealX90VertPeak, 1, -1); 
    hrealXSumBGScVert -> Add(hrealXSumScVert, hrealX90ScVertPeak, 1, -1); 

    hXallSumBGVert -> SetLineColor(5);
    hXallSumBGScVert -> SetLineColor(5);
    hrealXSumBGVert -> SetLineColor(kRed);
    hrealXSumBGScVert -> SetLineColor(kRed);
    hrealXSumPeakVert -> SetLineColor(8);
    hrealXSumPeakScVert -> SetLineColor(8);
    hrealX90VertPeak -> SetLineColor(1);
    hrealX90ScVertPeak -> SetLineColor(1);
    hrealXSumVert -> SetLineColor(4);
    hrealXSumScVert -> SetLineColor(4);

    cout << "MassminX: " << MassminX << " " << a << " MassmaxX: " << MassmaxX << " " << b << endl;
    
    cntSXVert = hrealXSumVert -> Integral(a,b);
    cntBXVert = hrealXSumBGVert -> Integral(a,b);
//    cntBXVert = hXallSumBGVert -> Integral(a,b);
    cntSXscVert = hrealXSumScVert -> Integral(a,b);
    cntBXscVert = hrealXSumBGScVert -> Integral(a,b);
//    cntBXscVert = hXallSumBGScVert -> Integral(a,b);

    //SB
    for(int j = 1; j <= nXVert; j++){
      if(hrealXSumPeakVert -> GetBinContent(j)){
	kXVert++;
	s_bg_vXVert[kXVert] = (hrealXSumPeakVert -> GetBinContent(j))/(hrealXSumBGVert -> GetBinContent(j));
	binXVert[kXVert] = (hrealXSumPeakVert -> GetBinLowEdge(j)) + (hrealXSumPeakVert -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nXScVert; j++){
      if(hrealXSumPeakScVert -> GetBinContent(j)){
	kXScVert++;
	s_bg_vXScVert[kXScVert] = (hrealXSumPeakScVert -> GetBinContent(j))/(hrealXSumBGScVert -> GetBinContent(j));
	binXScVert[kXScVert] = (hrealXSumPeakScVert -> GetBinLowEdge(j)) + (hrealXSumPeakScVert -> GetBinWidth(j));
      }
    }

    //invM no scaling MTD, Vert
    cLambdaXiMassVert -> cd(1);
    nice_canv1(gPad);
    hLallSumVert -> SetTitle("#pi^{-} in Hades + anything in FD");
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
    hrealLSumPeakVert -> Draw("same");
    hLallSumBGVert -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassVert -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGVert -> SetTitle("p#pi^{-}: real, peak90 and BG");
    hrealLSumBGVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGVert -> GetYaxis() -> SetTitle("counts");
    hrealLSumVert -> Draw();
    hrealL90VertPeak -> Draw("same");
    hrealLSumBGVert -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassVert -> cd(4);
    nice_canv1(gPad);
    hrealXSumVert -> SetTitle("#Lambda + #pi^{-}");
    hrealXSumVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumVert -> GetYaxis() -> SetTitle("counts");
    hrealXSumVert -> Draw();
    hrealX90Vert -> Draw("same");
//    l1 -> Draw("same");

    cLambdaXiMassVert -> cd(5);
    nice_canv1(gPad);
    hrealXSumBGVert -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGVert -> GetYaxis() -> SetTitle("counts");
    hrealXSumVert -> Draw();
    hrealX90VertPeak -> Draw("same");
    hrealXSumBGVert -> Draw("same");

    cLambdaXiMassVert -> cd(6);
    l1 -> Draw("same");

    //invM scaling MTD, Vert
/*    TCanvas *cimLsAvertsc = new TCanvas("cimLsAvertsc", "cimLsAvertsc");
    TCanvas *cimLsRvertsc = new TCanvas("cimLsRvertsc", "cimLsRvertsc");
    TCanvas *cimLsBGvertsc = new TCanvas("cimLsBGvertsc", "cimLsBGvertsc");
    TCanvas *cimXsAvertsc = new TCanvas("cimXsAvertsc", "cimXsAvertsc");
    TCanvas *cimXsRvertsc = new TCanvas("cimXsRvertsc", "cimXsRvertsc");
    TCanvas *cimXsBGvertsc = new TCanvas("cimXsBGvertsc", "cimXsBGvertsc");
*/    
    TCanvas *cimLMtdlVertlSc = new TCanvas("cimLMtdlVertlSc","cimLMtdlVertlSc"); //inv mass Lambda spectrum, MTD_L, VERTz_L cuts, cr sec scaling
    TCanvas *cimXMtdlVertlMlMtdxVertxSc = new TCanvas("cimXMtdlVerlMlMtdxVertxSc","cimXMtdlVerlMlMtdxVertxSc"); //inv mass Xi spectrum, MTD_L, VERTz_L, Lmass, MTD_X, VERTz_X cuts, cr sec scaling
 
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
    hLallSumScVert -> SetTitle("#pi^{-} in Hades + anything in FD");
    hLallSumScVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
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
    hrealLSumPeakScVert -> Draw("same");
    hLallSumBGScVert -> Draw("same");
//    l1a -> Draw("same");

    cLambdaXiMassScVert -> cd(3);
    nice_canv1(gPad);
    hrealLSumBGScVert -> SetTitle("p#pi^{-}: real, peak90 and BG");
    hrealLSumBGScVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealLSumBGScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumScVert -> Draw();
    hrealL90ScVertPeak -> Draw("same");
    hrealLSumBGScVert -> Draw("same");
//    l1a -> Draw("same");
    
    TLegend *lfin4 = new TLegend(.2,.35,.5,.8);
    
    cimLMtdlVertlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hLallSumScVert -> SetTitle("#Lambda reconstruction, MTD_L, VERTz_L cuts");
    hLallSumScVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hLallSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScVert -> SetLineColor(40);
//    hLallSumScVert -> SetLineStyle(2);
    hLallSumScVert -> SetLineWidth(2);
    hrealLSumScVert -> SetLineColor(46);
//    hrealLSumScVert -> SetLineStyle(2);
    hrealLSumScVert -> SetLineWidth(2);
    hLallSumBGScVert -> SetMarkerStyle(21);
    hLallSumBGScVert -> SetMarkerSize(.5);
    hLallSumBGScVert -> SetMarkerColor(2);
    hrealLSumPeakScVert -> SetLineColor(8);
//    hrealLSumPeakScVert -> SetLineStyle(10);
    hrealL90ScVert -> SetLineColor(1);
    hLallSumScVert -> Draw();
    hrealLSumScVert -> Draw("same");
    hrealLSumBGScVert -> Draw("p same");
//    hrealLSumPeakScVert -> Draw("same");
    hrealL90ScVertPeak -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");

    lfin4 -> AddEntry(hLallSumScVert, "sum all ch. (#pi^{-}-FD)");
    lfin4 -> AddEntry(hrealLSumScVert, "sum all ch. (#pi^{-}p)");
    lfin4 -> AddEntry(hrealLSumBGScVert, "BG=all-S");
    //  lfin4 -> AddEntry(hrealLSumPeakScVert, "all-BG in mass range");
    lfin4 -> AddEntry(hrealL90ScVertPeak, "S in mass range");
    lfin4 -> Draw("same");//<<<<<<<<<<<<<<
    
    cLambdaXiMassScVert -> cd(4);
    nice_canv1(gPad);
    hrealXSumScVert -> SetTitle("#Lambda + #pi^{-}");
    hrealXSumScVert -> GetXaxis() -> SetTitle("M_{p#pi^{-}} [MeV]");
    hrealXSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScVert -> Draw();
    hrealX90ScVert -> Draw("same");
//    l1 -> Draw("same");
    
    cLambdaXiMassScVert -> cd(5);
    nice_canv1(gPad);
    hrealXSumBGScVert -> SetTitle("#Xi^{-}: #Lambda#pi^{-} all, peak and BG");
    hrealXSumBGScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumBGScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScVert -> Draw();
    hrealX90ScVertPeak -> Draw("same");
    hrealXSumBGScVert -> Draw("same");

    cLambdaXiMassScVert -> cd(6);
    l1 -> Draw("same");

    TLegend *lfin5 = new TLegend(.2,.35,.5,.8);
        
    cimXMtdlVertlMlMtdxVertxSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumScVert -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass, MTD_X, VERTz_X");
    hrealXSumScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi^{-}} [MeV]");
    hrealXSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScVert -> SetLineColor(46);
//    hrealXSumScVert -> SetLineStyle(2);
    hrealXSumScVert -> SetLineWidth(2);
    hrealXSumBGScVert -> SetMarkerStyle(21);
    hrealXSumBGScVert -> SetMarkerSize(.5);
    hrealXSumBGScVert -> SetMarkerColor(2);
    hrealXSumPeakScVert -> SetLineColor(8);
    hrealX90ScVertPeak -> SetLineColor(1);
    hrealXSumScVert -> Draw();
    hrealXSumBGScVert -> Draw("p same");
//    hrealXSumPeakScVert -> Draw("same");
    hrealX90ScVertPeak -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");

    lfin5 -> AddEntry(hrealXSumScVert, "sum all ch. (#pi^{-}p)");
    lfin5 -> AddEntry(hrealXSumBGScVert, "BG=all-S");
    //  lfin5 -> AddEntry(hrealXSumPeakScVert, "all-BG in mass range");
    lfin5 -> AddEntry(hrealX90ScVertPeak, "S in mass range");
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
    int nall = 50000; //n evt*100 -> [%]
    double brLxchn = 0.64*5; //BR for Lambda->p pim * number of simulated channels with real Lambda1115
    printf("Effi rec.:\nL: MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f\nX: MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f\n", cntSLMtd/nall/brLxchn, cntSLscMtd/nall/brLxchn, cntSLVert/nall/brLxchn, cntSLscVert/nall/brLxchn, cntSXMtd/nall, cntSXscMtd/nall, cntSXVert/nall, cntSXscVert/nall);

    //3sigma Xi
    cout << "-3s:" << m3sigma << " +3s:" << p3sigma << " a:" << a << " b:" << b << endl;
    //Xi counts:
    cout << "Xi(MTD_L, Vert_L, Lmass, MTD_X, no_sc): " << cntSXMtd << endl;
    cout << "cntSXMtd90Peak: " << cntSXMtd90 << endl;

    TCanvas *cL_nocuts_sc = new TCanvas("cL_nocuts_sc", "Reconstruction of #Lambda(1115) (no cuts, #sigma sc.)", 1000, 600);
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

    TCanvas *cL_rec_sc = new TCanvas("cL_rec_sc", "Reconstruction of #Lambda(1115) (all cuts, #sigma sc.)", 1000, 600);
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

    TCanvas *cX_nocuts_sc = new TCanvas("cXi_nocuts_sc", "Reconstruction of #Xi^{-} (MTD_L, MassL, #sigma sc.)", 1000, 600);
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

    TCanvas *cX_fin_sc = new TCanvas("cXi_fin_sc", "Reconstruction of #Xi^{-} (all cuts, #sigma sc.)", 1000, 600);
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

        
    TFile *f = new TFile("./out_ana/out_anaBkgd_test5.root", "RECREATE");
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
  
    /*cimLsAsc -> Write();
    cimLsRsc -> Write();
    cimLsBGsc -> Write();
    cimXsAsc -> Write();
    cimXsRsc -> Write();
    cimXsBGsc -> Write();

    cimLsAmtdsc -> Write();
    cimRmtdsc -> Write();
    cimLsBGmtdsc -> Write();
    cimXsAmtdsc -> Write();
    cimXsRmtdsc -> Write();
    cimXsBGmtdsc -> Write();

    cimLsAvertsc -> Write();
    cimLsRvertsc -> Write();
    cimLsBGvertsc -> Write();
    cimXsAvertsc -> Write();
    cimXsRvertsc -> Write();
    cimXsBGvertsc -> Write();
    */
    
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
