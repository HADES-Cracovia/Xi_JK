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
    TH1F *hXallSum = new TH1F("hXallSum", "hXallSum", nbinsX, minX, maxX);
    TH1F *hXrealLpimSum = new TH1F("hXrealLpimSum", "hXrealLpimSum", nbinsX, minX, maxX);
    TH1F *hrealXSum = new TH1F("hrealXSum", "hrealXSum", nbinsX, minX, maxX);
    TH1F *hLallSumSc = new TH1F("hLallSumSc", "hLallSumSc", nbinsL, minL, maxL);
    TH1F *hrealLSumSc = new TH1F("hrealLSumSc", "hrealLSumSc", nbinsL, minL, maxL);
    TH1F *hXallSumSc = new TH1F("hXallSumSc", "hXallSumSc", nbinsX, minX, maxX);
    TH1F *hXrealLpimSumSc = new TH1F("hXrealLpimSumSc", "hXrealLpimSumSc", nbinsX, minX, maxX);
    TH1F *hrealXSumSc = new TH1F("hrealXSumSc", "hrealXSumSc", nbinsX, minX, maxX);

    TH1F *hLallSumBG = new TH1F("hLallSumBG", "hLallSumBG", nbinsL, minL, maxL);
    TH1F *hrealLSumPeak = new TH1F("hrealLSumPeak", "hrealLSumPeak", nbinsL, minL, maxL);
    TH1F *hLallSumBGSc = new TH1F("hLallSumBGSc", "hLallSumBGSc", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakSc = new TH1F("hrealLSumPeakSc", "hrealLSumPeakSc", nbinsL, minL, maxL);

    TH1F *hXallSumBG = new TH1F("hXallSumBG", "hXallSumBG", nbinsX, minX, maxX);
    TH1F *hrealXSumPeak = new TH1F("hrealXSumPeak", "hrealXSumPeak", nbinsX, minX, maxX);
    TH1F *hXallSumBGSc = new TH1F("hXallSumBGSc", "hXallSumBGSc", nbinsX, minX, maxX);
    TH1F *hrealXSumPeakSc = new TH1F("hrealXSumPeakSc", "hrealXSumPeakSc", nbinsX, minX, maxX);

    //only signal channel 090
    TH1F *hLall90, *hrealL90, *hrealX90, *hLall90Sc, *hrealL90Sc, *hrealX90Sc;
    
    TCanvas *cLambdaXiMass = new TCanvas("cLambdaXiMass", "Lambda & Xi invariant mass", 1800, 1000); //M_inv for Lambda & Xi reconstruction from all simulated channels
    TCanvas *cLambdaXiMassSc = new TCanvas("cLambdaXiMassSc", "Lambda & Xi invariant mass (cr sc)", 1800, 1000); //M_inv for Lambda & Xi reconstruction from all simulated channels with crsec
    cLambdaXiMass -> Divide(3,2);
    cLambdaXiMassSc -> Divide(3,2);

    THStack *hLmass_sc = new THStack(); //Lambda scaled with cr_sec, no cuts
    THStack *hXmass_sc = new THStack(); //Xi, scaled with cr_sec, no cuts
    THStack *hXmass_sc_fin = new THStack(); //Xi, scaled with cr_sec, up to MTD_X cut

    //MTD_L, Lmass
    TH1F *hLallSumScLmass = new TH1F("hLallSumScLmass", "hLallSumScLmass", nbinsL, minL, maxL);
    TH1F *hrealLSumScLmass = new TH1F("hrealLSumScLmass", "hrealLSumScLmass", nbinsL, minL, maxL);

    //MTD_L, Lmass, MTD_X
    //inv mass Lambda1115 & Xi
    TH1F *hLallSumMtd = new TH1F("hLallSumMtd", "hLallSumMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumMtd = new TH1F("hrealLSumMtd", "hrealLSumMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumLmass = new TH1F("hrealLSumLmass", "hrealLSumLmass", nbinsL, minL, maxL);
    TH1F *hXallSumMtd = new TH1F("hXallSumMtd", "hXallSumMtd", nbinsX, minX, maxX);
    TH1F *hXrealLpimSumMtd = new TH1F("hXrealLpimSumMtd", "hXrealLpimSumMtd", nbinsX, minX, maxX);
    TH1F *hrealXSumMtd = new TH1F("hrealXSumMtd", "hrealXSumMtd", nbinsX, minX, maxX);
    TH1F *hLallSumScMtd = new TH1F("hLallSumScMtd", "hLallSumScMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumScLmassMtd = new TH1F("hrealLSumScLmassMtd", "hrealLSumScLmassMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumScMtd = new TH1F("hrealLSumScMtd", "hrealLSumScMtd", nbinsL, minL, maxL);
    TH1F *hXallSumScMtd = new TH1F("hXallSumScMtd", "hXallSumScMtd", nbinsX, minX, maxX);
    TH1F *hXrealLpimSumScMtd = new TH1F("hXrealLpimSumScMtd", "hXrealLpimSumScMtd", nbinsX, minX, maxX);
    TH1F *hrealXSumScMtd = new TH1F("hrealXSumScMtd", "hrealXSumScMtd", nbinsX, minX, maxX);

    TH1F *hLallSumBGMtd = new TH1F("hLallSumBGMtd", "hLallSumBGMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakMtd = new TH1F("hrealLSumPeakMtd", "hrealLSumPeakMtd", nbinsL, minL, maxL);
    TH1F *hLallSumBGScMtd = new TH1F("hLallSumBGScMtd", "hLallSumBGScMtd", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakScMtd = new TH1F("hrealLSumPeakScMtd", "hrealLSumPeakScMtd", nbinsL, minL, maxL);
    TH1F *hLallSumBGLmass = new TH1F("hLallSumBGLmass", "hLallSumBGLmass", nbinsL, minL, maxL);
     TH1F *hrealLSumPeakLmass = new TH1F("hrealLSumPeakLmass", "hrealLSumPeakLmass", nbinsL, minL, maxL);
     TH1F *hLallSumBGScLmass = new TH1F("hLallSumBGScLmass", "hLallSumBGScLmass", nbinsL, minL, maxL);
     TH1F *hrealLSumPeakScLmass = new TH1F("hrealLSumPeakScLmass", "hrealLSumPeakScLmass", nbinsL, minL, maxL);

    TH1F *hXallSumBGMtd = new TH1F("hXallSumBGMtd", "hXallSumBGMtd", nbinsX, minX, maxX);
    TH1F *hrealXSumPeakMtd = new TH1F("hrealXSumPeakMtd", "hrealXSumPeakMtd", nbinsX, minX, maxX);
    TH1F *hXallSumBGScMtd = new TH1F("hXallSumBGScMtd", "hXallSumBGScMtd", nbinsX, minX, maxX);
    TH1F *hrealXSumPeakScMtd = new TH1F("hrealXSumPeakScMtd", "hrealXSumPeakScMtd", nbinsX, minX, maxX);
    
    //only signal channel 090
    TH1F *hLall90Mtd, *hrealL90Mtd, *hrealX90Mtd, *hLall90ScMtd, *hrealL90ScMtd, *hrealX90ScMtd;

    TCanvas *cLambdaXiMassMtd = new TCanvas("cLambdaXiMassMtd", "Lambda & Xi invariant mass, MTD_L, Lmass, MTD_X", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels
    TCanvas *cLambdaXiMassScMtd = new TCanvas("cLambdaXiMassScMtd", "Lambda & Xi invariant mass (cr sc), MTD_L, Lmass, MTD_X", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels with crsec
    cLambdaXiMassMtd -> Divide(3,2);
    cLambdaXiMassScMtd -> Divide(3,2);

    //MTD_L scan
    TCanvas *cMTD_LscanAll = new TCanvas("cMTD_LscanAll", "cMTD_LscanAll", 2000, 1000);
    TCanvas *cMTD_LscanReal = new TCanvas("cMTD_LscanReal", "cMTD_LscanReal", 2000, 1000);
    cMTD_LscanAll -> Divide(5,4);
    cMTD_LscanReal -> Divide(5,4);
    
    TH1F *hLall1scMTDScanSum[20], *hrealL1scMTDScanSum[20];
    TH1F *hLallSumBGScMTDScan[20];
    TH1F *hrealLSumPeakScMTDScan[20];

    TCanvas *cMTD_LscanSB = new TCanvas("cMTD_LscanSB", "cMTD_LscanSB", 2000, 1000);
    cMTD_LscanSB -> Divide(5,4);
    
   //MTD_X scan
    TCanvas *cMTD_XscanAll = new TCanvas("cMTD_XscanAll", "cMTD_XscanAll", 2000, 1000);
    TCanvas *cMTD_XscanReal = new TCanvas("cMTD_XscanReal", "cMTD_XscanReal", 2000, 1000);
    cMTD_XscanAll -> Divide(5,4);
    cMTD_XscanReal -> Divide(5,4);
    
    TH1F *hXall1scMTDScanSum[20], *hrealX1scMTDScanSum[20];
    TH1F *hXallSumBGScMTDScan[20];
    TH1F *hrealXSumPeakScMTDScan[20];

    TCanvas *cMTD_XscanSB = new TCanvas("cMTD_XscanSB", "cMTD_XscanSB", 2000, 1000);
    cMTD_XscanSB -> Divide(5,4);
    

    //MTD_L, Lmass, MTD_X, Vertz_X
    //Lambda1115
    TH1F *hLVertex_sig = new TH1F("hLVertex_sig", "hLVertex_sig", 150, -100, 500); //Lambda1115 vertex_z signal
    TH1F *hLVertex_bg = new TH1F("hLVertex_bg", "hLVertex_bg", 150, -100, 500); //Lambda1115 vertex_z bg
    TH1F *hLVertex_bg_sum = new TH1F("hLVertex_bg_sum", "#Lambda/(1115/) vertex reconstruction --- background channels sum", 150, -100, 500); //Xi vertex_z bg sum

    TH1F *hLallSumVert = new TH1F("hLallSumVert", "hLallSumVert", nbinsL, minL, maxL);
    TH1F *hrealLSumVert = new TH1F("hrealLSumVert", "hrealLSumVert", nbinsL, minL, maxL);
    TH1F *hXallSumVert = new TH1F("hXallSumVert", "hXallSumVert", nbinsX, minX, maxX);
    TH1F *hrealXSumVert = new TH1F("hrealXSumVert", "hrealXSumVert", nbinsX, minX, maxX);
    TH1F *hLallSumScVert = new TH1F("hLallSumScVert", "hLallSumScVert", nbinsL, minL, maxL);
    TH1F *hrealLSumScVert = new TH1F("hrealLSumScVert", "hrealLSumScVert", nbinsL, minL, maxL);
    TH1F *hXallSumScVert = new TH1F("hXallSumScVert", "hXallSumScVert", nbinsX, minX, maxX);
    TH1F *hrealXSumScVert = new TH1F("hrealXSumScVert", "hrealXSumScVert", nbinsX, minX, maxX);

    TH1F *hLallSumBGVert = new TH1F("hLallSumBGVert", "hLallSumBGVert", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakVert = new TH1F("hrealLSumPeakVert", "hrealLSumPeakVert", nbinsL, minL, maxL);
    TH1F *hLallSumBGScVert = new TH1F("hLallSumBGScVert", "hLallSumBGScVert", nbinsL, minL, maxL);
    TH1F *hrealLSumPeakScVert = new TH1F("hrealLSumPeakScVert", "hrealLSumPeakScVert", nbinsL, minL, maxL);

    TH1F *hXallSumBGVert = new TH1F("hXallSumBGVert", "hXallSumBGVert", nbinsX, minX, maxX);
    TH1F *hrealXSumPeakVert = new TH1F("hrealXSumPeakVert", "hrealXSumPeakVert", nbinsX, minX, maxX);
    TH1F *hXallSumBGScVert = new TH1F("hXallSumBGScVert", "hXallSumBGScVert", nbinsX, minX, maxX);
    TH1F *hrealXSumPeakScVert = new TH1F("hrealXSumPeakScVert", "hrealXSumPeakScVert", nbinsX, minX, maxX);

    //only signal channel 090
    TH1F *hLall90Vert, *hrealL90Vert, *hrealX90Vert, *hLall90ScVert, *hrealL90ScVert, *hrealX90ScVert;
    
    TCanvas *cLambdaXiMassVert = new TCanvas("cLambdaXiMassVert", "Lambda & Xi invariant mass, MTD, Vert", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels after MTD_L, MassL, MTD_X, 
    TCanvas *cLambdaXiMassScVert = new TCanvas("cLambdaXiMassScVert", "Lambda & Xi invariant mass (cr sc), MTD, Vert", 1800, 1000); //M_inv for Lambda & Xi recnstruction from all simulated channels
    cLambdaXiMassVert -> Divide(3,2);
    cLambdaXiMassScVert -> Divide(3,2);


    TCanvas *cVertZ_L = new TCanvas("cVertZ_L", "#Lambda/(1115/) vertex reconstruction - z", 2000, 1000);
    cVertZ_L -> Divide(4,2);
    
    TCanvas *cVertZ_LscanAll1 = new TCanvas("cVertZ_LscanAll1", "cVertZ_LscanAll1", 2000, 1000);
    TCanvas *cVertZ_LscanAll2 = new TCanvas("cVertZ_LscanAll2", "cVertZ_LscanAll2", 2000, 1000);
    TCanvas *cVertZ_LscanReal1 = new TCanvas("cVertZ_LscanReal1", "cVertZ_LscanReal1", 2000, 1000);
    TCanvas *cVertZ_LscanReal2 = new TCanvas("cVertZ_LscanReal2", "cVertZ_LscanReal2", 2000, 1000);
    cVertZ_LscanAll1 -> Divide(5,3);
    cVertZ_LscanReal1 -> Divide(5,3);
    cVertZ_LscanAll2 -> Divide(5,3);
    cVertZ_LscanReal2 -> Divide(5,3);

    TH1F *hLall1scVertScanSum[30];
    TH1F *hrealL1scVertScanSum[30];
    TH1F *hLallSumBGScVertScan[30];
    TH1F *hrealLSumPeakScVertScan[30];

    TCanvas *cVertZ_LscanSB1 = new TCanvas("cVertZ_LscanSB1", "cVertZ_LscanSB1", 2000, 1000);
    cVertZ_LscanSB1 -> Divide(5,3);
    TCanvas *cVertZ_LscanSB2 = new TCanvas("cVertZ_LscanSB2", "cVertZ_LscanSB2", 2000, 1000);
    cVertZ_LscanSB2 -> Divide(5,3);

      
    //Xi
    TH1F *hXVertex_sig = new TH1F("hXVertex_sig", "hXVertex_sig", 150, -100, 500); //Xi vertex_z signal
    TH1F *hXVertex_bg = new TH1F("hXVertex_bg", "hXVertex_bg", 150, -100, 500); //Xi vertex_z bg
    TH1F *hXVertex_bg_sum = new TH1F("hXVertex_bg_sum", "Xi vertex reconstruction --- background channels sum", 150, -100, 500); //Xi vertex_z bg sum
    
    TCanvas *cVertZ_X = new TCanvas("cVertZ_X", "Xi vertex reconstruction - z", 2000, 1000);
    cVertZ_X -> Divide(4,2);

    TCanvas *cVertZ_XscanAll1 = new TCanvas("cVertZ_XscanAll1", "cVertZ_XscanAll1", 2000, 1000);
    TCanvas *cVertZ_XscanReal1 = new TCanvas("cVertZ_XscanReal1", "cVertZ_XscanReal1", 2000, 1000);
    cVertZ_XscanAll1 -> Divide(5,3);
    cVertZ_XscanReal1 -> Divide(5,3);
    TCanvas *cVertZ_XscanAll2 = new TCanvas("cVertZ_XscanAll2", "cVertZ_XscanAll2", 2000, 1000);
    TCanvas *cVertZ_XscanReal2 = new TCanvas("cVertZ_XscanReal2", "cVertZ_XscanReal2", 2000, 1000);
    cVertZ_XscanAll2 -> Divide(5,3);
    cVertZ_XscanReal2 -> Divide(5,3);

    TH1F *hXall1scVertScanSum[30], *hrealX1scVertScanSum[30];
    TH1F *hXallSumBGScVertScan[30];
    TH1F *hrealXSumPeakScVertScan[30];

    TCanvas *cVertZ_XscanSB1 = new TCanvas("cVertZ_XscanSB1", "cVertZ_XscanSB1", 2000, 1000);
    cVertZ_XscanSB1 -> Divide(5,3);
    TCanvas *cVertZ_XscanSB2 = new TCanvas("cVertZ_XscanSB2", "cVertZ_XscanSB2", 2000, 1000);
    cVertZ_XscanSB2 -> Divide(5,3);

    //    TCanvas *cVertDiff_allCh = new TCanvas("cVertDiff_allCh", "cVertDiff_allCh");
    //    cVertDiff_allCh -> Divide(2,1);
    //TCanvas *cVertDiff = new TCanvas("cVertDiff", "cVertDiff");
    //cVertDiff -> Divide(2,2);
    //TCanvas *cVertDiffMtd = new TCanvas("cVertDiffMtd", "cVertDiffMtd");
    //cVertDiffMtd -> Divide(2,2);


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
    /* TH1F *hVertDiff_realSumsc = new TH1F("hVertDiff_realSumsc", "hVertDiff_realSumsc", 150, -100, 300); //Difference between Lambda and Xi vertex, real sum, cr sec scaled
    TH1F *hVertDiff_allSumsc = new TH1F("hVertDiff_allSumsc", "hVertDiff_allSumsc", 150, -100, 300); //Difference between Lambda and Xi vertex, all cand. sum, cr sec scaled
    TH1F *hVertDiffMtd_realSumsc = new TH1F("hVertDiffMtd_realSumsc", "hVertDiffMtd_realSumsc", 150, -100, 300); //Difference between Lambda and Xi vertex, real sum after MTD_X cut, cr sec scaled
    TH1F *hVertDiffMtd_allSumsc = new TH1F("hVertDiffMtd_allSumsc", "hVertDiffMtd_allSumsc", 150, -100, 300); //Difference between Lambda and Xi vertex, all cand. sum after MTD_X cut, cr sec scaled
    */

    //fit function for gauss estimation
    TF1 *fit = new TF1("fit", "gaus");
    double mmax, center_fit, sigma_fit, s_b, m3sigma, p3sigma;
    int a, b;
    double cntSL, cntSLsc, cntBL, cntBLsc, cntSX, cntSXsc, cntBX, cntBXsc, cntSLMtd, cntSLscMtd, cntSLLmass, cntSLscLmass, cntBLscLmass, cntSXMtd, cntSXscMtd, cntBLMtd, cntBLscMtd, cntBXMtd, cntBXscMtd, cntSLVert, cntSLscVert, cntSXVert, cntSXscVert, cntBLVert, cntBLscVert, cntBXVert, cntBXscVert;

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
      sprintf(chanNo, "/u/jkubos/analiza/hades/pp45sim/Xi_rec/outputs_ch/output_%03d_all5.root", chan[i]);
      	TFile *f1 = TFile::Open(chanNo, "READ");

	TPaveText *ptch = new TPaveText(.5, .7, .8, .85, "NDC");
	ptch -> SetFillColor(0);
	ptch -> SetBorderSize(0);
	ptch -> SetTextSize(0.07);
	ptch -> AddText(reac[i].c_str());

	//no cuts
	TH1F *hLall = (TH1F*)f1->Get("hMLAll"); //all combinations of H-FD
	TH1F *hrealL = (TH1F*)f1->Get("hMLPiHpF"); //pion in H, p in FD
	//	TH1F *hXall = (TH1F*)f1->Get("hMXAll"); //Lambda and pion in H, in mL range
	//	TH1F *hXrealLpim = (TH1F*)f1->Get("hKmassRLpion");
	TH1F *hrealX = (TH1F*)f1->Get("hMXAll"); //Lambda and pion in H, in mL range
	
	hLall -> Rebin(2);
	hrealL -> Rebin(2);
	//	hXall -> Rebin(2);
	//	hXrealLpim -> Rebin(2);
	hrealX -> Rebin(2);

	//spectrum MTD_L
	TH1F *hMTD_Lall = (TH1F*)f1 -> Get("hTDpiFD"); //distance between anything in FD and pion in H
	TH1F *hMTD_Lreal = (TH1F*)f1 -> Get("hTDpip"); //distance between proton in FD and pion in H

	//spectrum MTD_X
	//	TH1F *hMTD_Xall = (TH1F*)f1 -> Get("hTDpiL"); //distance between Lambda and pion in H
	TH1F *hMTD_Xreal = (TH1F*)f1 -> Get("hTDpiL"); //distance between Lambda and pion in H
	
	//MTD_L, Lmass
	//	TH1F *hLallLmass = (TH1F*)f1->Get("hMLDistMass");
	//	TH1F *hrealLLmass = (TH1F*)f1->Get("hMLDistMassReal");
	
	//	hLallLmass -> Rebin(2);
	//	hrealLLmass -> Rebin(2);

	//MTD_L, Lmass, MTD_X
	TH1F *hLallMtd = (TH1F*)f1->Get("hMLPiHadesMTD"); //pion in H, anything in FD, MTD_X
	TH1F *hrealLMtd = (TH1F*)f1->Get("hMLPiHpFMTD"); //pion in H, proton in FD, MTD_X
	//	TH1F *hXallMtd = (TH1F*)f1->Get("hMXPiLMTD"); //Lambda and pion in H, MTD_X
	TH1F *hrealXMtd = (TH1F*)f1->Get("hMXPiLMTD"); //Lambda and pion in H, MTD_X

	hLallMtd -> Rebin(2);
	hrealLMtd -> Rebin(2);
	//	hXallMtd -> Rebin(2);
	hrealXMtd -> Rebin(2);
	/*
	//MTD_L scan
	TH1F *hLallMTDScan[20];
	TH1F *hrealLMTDScan[20];
	char hNameLAllmtd[24], hNameLRealmtd[24];
	for(int k = 0; k < 20; k++){
	  sprintf(hNameLAllmtd, "hCutMTDLAll_%d", k);
	  sprintf(hNameLRealmtd, "hCutMTDLReal_%d", k);
	  hLallMTDScan[k] = (TH1F*)f1->Get(hNameLAllmtd);
	  hrealLMTDScan[k] = (TH1F*)f1->Get(hNameLRealmtd);
	}

	//MTD_X scan
	TH1F *hXallMTDScan[20];
	TH1F *hrealXMTDScan[20];
	char hNameXAllmtd[24], hNameXRealmtd[24];
	for(int k = 0; k < 20; k++){
	  sprintf(hNameXAllmtd, "hCutMTDXAll_%d", k);
	  sprintf(hNameXRealmtd, "hCutMTDXReal_%d", k);
	  hXallMTDScan[k] = (TH1F*)f1->Get(hNameXAllmtd);
	  hrealXMTDScan[k] = (TH1F*)f1->Get(hNameXRealmtd);
	}
	*/

	//spectrum Vertz_L
	TH1F *hVertz_Lall = (TH1F*)f1 -> Get("hVertpiFD"); //vertZ of anything in FD and pion in H 
	TH1F *hVertz_Lreal = (TH1F*)f1 -> Get("hVertpip"); //vertZ of proton in FD and pion in H 

	//spectrum Vertz_X
	//	TH1F *hVertz_Xall = (TH1F*)f1 -> Get("hXVertpiL"); //vertZ of Lambda and pion in H 
	TH1F *hVertz_Xreal = (TH1F*)f1 -> Get("hXVertpiL"); //vertZ of Lambda and pion in H 

	//MTD_L, Lmass, MTD_X, Vertz_X
	TH1F *hLallVert = (TH1F*)f1->Get("hMLPiHadesMTDVert"); //pion in H, anything in FD, MTD_X
	TH1F *hrealLVert = (TH1F*)f1->Get("hMLPiHpFMTDVert"); //pion in H, proton in FD, MTD_X
	//	TH1F *hXallVert = (TH1F*)f1->Get("hMXPiLMTDVertVert"); //Lambda and pion in H, MTD_X
	TH1F *hrealXVert = (TH1F*)f1->Get("hMXPiLMTDVert"); //Lambda and pion in H, MTD_X

	hLallVert -> Rebin(2);
	hrealLVert -> Rebin(2);
	//	hXallVert -> Rebin(2);
	hrealXVert -> Rebin(2);
	/*
	//VERTz_L scan
	TH1F *hLallVertScan[30];
	TH1F *hrealLVertScan[30];
	char hNameLAll[24], hNameLReal[24];
	for(int k = -10; k < 20; k++){
	  sprintf(hNameLAll, "hCutVertLAll_%d", k);
	  sprintf(hNameLReal, "hCutVertLReal_%d", k);
	  hLallVertScan[k+10] = (TH1F*)f1->Get(hNameLAll);
	  hrealLVertScan[k+10] = (TH1F*)f1->Get(hNameLReal);
	}

	//VERTz_X scan
	TH1F *hXallVertScan[30];
	TH1F *hrealXVertScan[30];
	char hNameAll[24], hNameReal[24];
	for(int k = -10; k < 20; k++){
	  sprintf(hNameAll, "hCutVertAll_%d", k);
	  sprintf(hNameReal, "hCutVertReal_%d", k);
	  hXallVertScan[k+10] = (TH1F*)f1->Get(hNameAll);
	  hrealXVertScan[k+10] = (TH1F*)f1->Get(hNameReal);
	}
	*/
	int col = i+1;
	if(i == 2) col = 8;
	if(i == 4) col = 42;
	if(i == 6) col = 15;

	/*TH1F *hVertDiffAll = (TH1F*)f1 -> Get("hKvertexAll");
	TH1F *hVertDiffReal = (TH1F*)f1 -> Get("hKvertexReal");
	TH1F *hVertDiffMtdAll = (TH1F*)f1 -> Get("hKvertexdistAll");
	TH1F *hVertDiffMtdReal = (TH1F*)f1 -> Get("hKvertexdistReal");

	TH1F *hVertDiffAllsc = (TH1F*)hVertDiffAll -> Clone("hVertDiffAllsc_c");
	TH1F *hVertDiffRealsc = (TH1F*)hVertDiffReal -> Clone("hVertDiffRealsc_c");
	TH1F *hVertDiffMtdAllsc = (TH1F*)hVertDiffMtdAll -> Clone("hVertDiffMtdAllsc_c");
	TH1F *hVertDiffMtdRealsc = (TH1F*)hVertDiffMtdReal -> Clone("hVertDiffMtdRealsc_c");

	hVertDiffAllsc -> Rebin(3);
	hVertDiffRealsc -> Rebin(3);
	hVertDiffMtdAllsc -> Rebin(3);
	hVertDiffMtdRealsc -> Rebin(3);

	hVertDiffAllsc -> Scale(cr_sec[i]);
	hVertDiffRealsc -> Scale(cr_sec[i]);
	hVertDiffMtdAllsc -> Scale(cr_sec[i]);
	hVertDiffMtdRealsc -> Scale(cr_sec[i]);

	hVertDiffAllsc -> SetLineColor(col);
	hVertDiffRealsc -> SetLineColor(col);
	hVertDiffMtdAllsc -> SetLineColor(col);
	hVertDiffMtdRealsc -> SetLineColor(col);

	hVertDiff_realSumsc -> Add(hVertDiffRealsc);
	hVertDiff_allSumsc -> Add(hVertDiffAllsc);
	hVertDiffMtd_realSumsc -> Add(hVertDiffMtdRealsc);
	hVertDiffMtd_allSumsc -> Add(hVertDiffMtdAllsc);

	cVertDiff_allCh -> cd(1);
	nice_canv1(gPad);
	hVertDiffAllsc -> SetTitle("Distance between ksi and lambda VERT - no cuts, all cand, scaled");
	hVertDiffAllsc -> GetXaxis() -> SetTitle("dist [mm]");
	hVertDiffAllsc -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertDiffAllsc -> Draw("same");

	cVertDiff_allCh -> cd(2);
	nice_canv1(gPad);
	hVertDiffMtdAllsc -> SetTitle("Distance between ksi and lambda VERT - after MTD_X, all cand, scaled");
	hVertDiffMtdAllsc -> GetXaxis() -> SetTitle("dist [mm]");
	hVertDiffMtdAllsc -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertDiffMtdAllsc -> Draw("same");
	*/
	/*	cVertDiff_allCh -> cd(3);
	nice_canv1(gPad);
	hVertDiffRealsc -> SetTitle("Distance between ksi and lambda VERT - no cuts, real #Xi and #Lambda, scaled");
	hVertDiffRealsc -> GetXaxis() -> SetTitle("dist [mm]");
	hVertDiffRealsc -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertDiffRealsc -> Draw("same");

	cVertDiff_allCh -> cd(4);
	nice_canv1(gPad);
	hVertDiffMtdRealsc -> SetTitle("Distance between ksi and lambda VERT - after MTD_X, real #Xi and #Lambda, scaled");
	hVertDiffMtdRealsc -> GetXaxis() -> SetTitle("dist [mm]");
	hVertDiffMtdRealsc -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertDiffMtdRealsc -> Draw("same");
	*/
	//no cuts
	TH1F *hLall1 = (TH1F*)hLall -> Clone("hLall1_c");
	TH1F *hLall1sc = (TH1F*)hLall -> Clone("hLall1sc_c");
	TH1F *hrealL1 = (TH1F*)hrealL -> Clone("hrealL1_c");
	TH1F *hrealL1sc = (TH1F*)hrealL -> Clone("hrealL1sc_c");
	//	TH1F *hXall1 = (TH1F*)hXall -> Clone("hXall1_c");
	//	TH1F *hXall1sc = (TH1F*)hXall -> Clone("hXall1sc_c");
	//	TH1F *hXrealLpim1 = (TH1F*)hXrealLpim -> Clone("hXrealLpim1_c");
	//	TH1F *hXrealLpim1sc = (TH1F*)hXrealLpim -> Clone("hXrealLpim1sc_c");
	TH1F *hrealX1 = (TH1F*)hrealX -> Clone("hrealX1_c");
	TH1F *hrealX1sc = (TH1F*)hrealX -> Clone("hrealX1sc_c");

	TH1F *clLambdaSc = (TH1F*)hLall -> Clone("hLall_chan");
	TH1F *clXiSc = (TH1F*)hrealX -> Clone("hrealX_chan");

      	hLall1sc -> Scale(cr_sec[i]);
	hrealL1sc -> Scale(cr_sec[i]);
	//	hXall1sc -> Scale(cr_sec[i]);
	//	hXrealLpim1sc -> Scale(cr_sec[i]);
	hrealX1sc -> Scale(cr_sec[i]);

	hLallSum -> Add(hLall1);
	hrealLSum -> Add(hrealL1);
	//	hXallSum -> Add(hXall1);
	//	hXrealLpimSum -> Add(hXrealLpim1);
	hrealXSum -> Add(hrealX1);
	
	hLall1sc -> Sumw2();
	hrealLSumSc -> Sumw2();
	//	hXallSumSc -> Sumw2();
	//	hXrealLpimSumSc -> Sumw2();
	hrealXSumSc -> Sumw2();

	hLallSumSc -> Add(hLall1sc);
	hrealLSumSc -> Add(hrealL1sc);
	//	hXallSumSc -> Add(hXall1sc);
	//	hXrealLpimSumSc -> Add(hXrealLpim1sc);
	hrealXSumSc -> Add(hrealX1sc);

	clLambdaSc -> Scale(cr_sec[i]);
	//clLambdaSc -> Rebin(2);
	//clLambdaSc -> Sumw2();
	hLmass_sc -> Add(clLambdaSc);
	clLambdaSc -> SetLineColor(col);	
	// clLambdaSc -> SetMarkerColor(col);
	// clLambdaSc -> SetMarkerStyle(3);
	// clLambdaSc -> SetMarkerSize(2);
	// if(i==0){
	//   clLambdaSc -> SetMarkerStyle(20);
	//   clLambdaSc -> SetMarkerSize(1.5);
	// }

	clXiSc -> Scale(cr_sec[i]);
	//clXiSc -> Rebin(2);
	//clXiSc -> Sumw2();
	hXmass_sc -> Add(clXiSc);
	clXiSc -> SetLineColor(col);	
	// clXiSc -> SetMarkerColor(col);
	// clXiSc -> SetMarkerStyle(3);
	// clXiSc -> SetMarkerSize(2);
	// if(i==0){
	//   clXiSc -> SetMarkerStyle(20);
	//   clXiSc -> SetMarkerSize(1.5);
	// }

	//MTD_L, Lmass
	/*	TH1F *hLall1Lmass = (TH1F*)hLallLmass -> Clone("hLall1_cLmass");
	TH1F *hLall1scLmass = (TH1F*)hLallLmass -> Clone("hLall1sc_cLmass");
	TH1F *hrealL1Lmass = (TH1F*)hrealLLmass -> Clone("hrealL1_cLmass");
	TH1F *hrealL1scLmass = (TH1F*)hrealLLmass -> Clone("hrealL1sc_cLmass");

	hLall1scLmass -> Scale(cr_sec[i]);
	hrealL1scLmass -> Scale(cr_sec[i]);
	
	hLallSumScLmass -> Add(hLall1scLmass);
	hrealLSumScLmass -> Add(hrealL1scLmass);
	*/
	//MTD_L, Lmass, MTD_X
	TH1F *hLall1Mtd = (TH1F*)hLallMtd -> Clone("hLall1_cMtd");
	TH1F *hLall1scMtd = (TH1F*)hLallMtd -> Clone("hLall1sc_cMtd");
	TH1F *hrealL1Mtd = (TH1F*)hrealLMtd -> Clone("hrealL1_cMtd");
	TH1F *hrealL1scMtd = (TH1F*)hrealLMtd -> Clone("hrealL1sc_cMtd");
	//	TH1F *hXall1Mtd = (TH1F*)hXallMtd -> Clone("hXall1_cMtd");
	//	TH1F *hXall1scMtd = (TH1F*)hXallMtd -> Clone("hXall1sc_cMtd");
	TH1F *hrealX1Mtd = (TH1F*)hrealXMtd -> Clone("hrealX1_cMtd");
      	TH1F *hrealX1scMtd = (TH1F*)hrealXMtd -> Clone("hrealX1sc_cMtd");

	TH1F *clXiSc_fin = (TH1F*)hrealXMtd -> Clone("hrealX1sc_cMtd_fin");
	
      	hLall1scMtd -> Scale(cr_sec[i]);
	hrealL1scMtd -> Scale(cr_sec[i]);
	//	hXall1scMtd -> Scale(cr_sec[i]);
	//	hXrealLpim1sc -> Scale(cr_sec[i]);
	hrealX1scMtd -> Scale(cr_sec[i]);

	hLallSumMtd -> Add(hLall1Mtd);
	hrealLSumMtd -> Add(hrealL1Mtd);
	//	hXallSumMtd -> Add(hXall1Mtd);
	hrealXSumMtd -> Add(hrealX1Mtd);

	hLallSumScMtd -> Sumw2();
	hrealLSumScMtd -> Sumw2();
	//	hXallSumScMtd -> Sumw2();
	hrealXSumScMtd -> Sumw2();
	
	hLallSumScMtd -> Add(hLall1scMtd);
	hrealLSumScMtd -> Add(hrealL1scMtd);
	//	hXallSumScMtd -> Add(hXall1scMtd);
	hrealXSumScMtd -> Add(hrealX1scMtd);

	clXiSc_fin -> Scale(cr_sec[i]);
	//clXiSc_fin -> Rebin(2);
	//clXiSc_fin -> Sumw2();
	hXmass_sc_fin -> Add(clXiSc_fin);
	clXiSc_fin -> SetLineColor(col);
	//	clXiSc_fin -> SetMarkerColor(col);
	//	clXiSc_fin -> SetMarkerStyle(3);
	//	clXiSc_fin -> SetMarkerSize(2);
	//	if(i==0){ 
	//	  clXiSc_fin -> SetMarkerStyle(20);
	//	  clXiSc_fin -> SetMarkerSize(1.5);
	//	}
	//***************************************************************

	//spectrum Vertz_L
	TH1F *hVertz_Lall1 = (TH1F*)hVertz_Lall -> Clone("hVertz_Lall_c");
	TH1F *hVertz_Lreal1 = (TH1F*)hVertz_Lreal -> Clone("hVertz_Lreal_c");

	//spectrum Vertz_X
	//	TH1F *hVertz_Xall1 = (TH1F*)hVertz_Xall -> Clone("hVertz_Xall_c");
	TH1F *hVertz_Xreal1 = (TH1F*)hVertz_Xreal -> Clone("hVertz_Xreal_c");

	hVertz_Lall1 -> Scale(cr_sec[i]);
	hVertz_Lreal1 -> Scale(cr_sec[i]);
	//	hVertz_Xall1 -> Scale(cr_sec[i]);
	hVertz_Xreal1 -> Scale(cr_sec[i]);

	hVertz_Lall1 -> SetLineColor(col);
	hVertz_Lreal1 -> SetLineColor(col);
	//	hVertz_Lreal1 -> SetFillColor(col);
	//	hVertz_Xall1 -> SetLineColor(col);
	hVertz_Xreal1 -> SetLineColor(col);
	//	hVertz_Xreal1 -> SetFillColor(col);

	/*if(i>0){
	  hVertz_Lall1 -> SetLineStyle(i+4);
	  hVertz_Lreal1 -> SetLineStyle(i+4);
	  hVertz_Xall1 -> SetLineStyle(i+4);
	  hVertz_Xreal1 -> SetLineStyle(i+4);
	  }*/
	
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
	//	TH1F *hMTD_Xall1 = (TH1F*)hMTD_Xall -> Clone("hMTD_Xall_c");
	TH1F *hMTD_Xreal1 = (TH1F*)hMTD_Xreal -> Clone("hMTD_Xreal_c");

	hMTD_Lall1 -> Scale(cr_sec[i]);
	hMTD_Lreal1 -> Scale(cr_sec[i]);
	//	hMTD_Xall1 -> Scale(cr_sec[i]);
	hMTD_Xreal1 -> Scale(cr_sec[i]);

	hMTD_Lall1 -> SetLineColor(col);
	hMTD_Lreal1 -> SetLineColor(col);
	//	hMTD_Xall1 -> SetLineColor(col);
	hMTD_Xreal1 -> SetLineColor(col);
	/*
	if(i>0){
	  hMTD_Lall1 -> SetLineStyle(i+4);
	  hMTD_Lreal1 -> SetLineStyle(i+4);
	  hMTD_Xall1 -> SetLineStyle(i+4);
	  hMTD_Xreal1 -> SetLineStyle(i+4);
	  }*/

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

	/*cMTDX -> cd(1);
	gPad->SetLogy();
	hMTD_Xall1 -> GetYaxis() -> SetRangeUser(1, 10000000);
	hMTD_Xall1 -> SetTitle("MTD_X: all Xi candidates");
	hMTD_Xall1 -> GetXaxis() -> SetTitle("MTD_X [mm]");
	hMTD_Xall1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hMTD_Xall1 -> Draw("same");*/
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

	/*cVERTX -> cd(1);
	gPad->SetLogy();
	hVertz_Xall1 -> GetYaxis() -> SetRangeUser(10, 5000000);
	hVertz_Xall1 -> SetTitle("VERTz_X: all Xi candidates");
	hVertz_Xall1 -> GetXaxis() -> SetTitle("VERTz_X [mm]");
	hVertz_Xall1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertz_Xall1 -> Draw("same");
	hXVertex_allSum -> Add(hVertz_Xall1);*/
	cVERTX -> cd(2);
	gPad->SetLogy();
	hVertz_Xreal1 -> GetYaxis() -> SetRangeUser(10, 5000000);
	hVertz_Xreal1 -> SetTitle("VERTz_X: real Xi");
	hVertz_Xreal1 -> GetXaxis() -> SetTitle("VERTz_X [mm]");
	hVertz_Xreal1 -> GetYaxis() -> SetTitle("counts*#sigma");
	hVertz_Xreal1 -> Draw("same");
	hXVertex_sigSum -> Add(hVertz_Xreal1);
	
	/*	//MTD scan
	TH1F *hLall1MTDScan[20], *hLall1scMTDScan[20], *hrealL1MTDScan[20], *hrealL1scMTDScan[20];
	char clNameLAllmtd[24], clNameLRealmtd[24];

	for(int k = 0; k < 20; k++){
	  sprintf(clNameLAllmtd, "hLall1sc_cMTD_%d", k);
	  hLall1scMTDScan[k] = (TH1F*)hLallMTDScan[k] -> Clone(clNameLAllmtd);
	  hLall1scMTDScan[k] -> Scale(cr_sec[i]);
	  cMTD_LscanAll -> cd(k+1);
	  nice_canv1(gPad);
	  hLall1scMTDScan[k] -> SetLineColor(col);
	  if(i==0){
	    hLall1scMTDScan[k] -> GetXaxis() -> SetTitle("invM [MeV]");
	    hLall1scMTDScan[k] -> GetYaxis() -> SetTitle("counts*#sigma");
	    hLall1scMTDScan[k] -> Draw();
	    hLall1scMTDScanSum[k] = hLall1scMTDScan[k];
	  }else{
	    hLall1scMTDScan[k] -> Draw("same");
	    hLall1scMTDScanSum[k] -> Add(hLall1scMTDScan[k]);
	  }
	  
	  sprintf(clNameLRealmtd, "hrealL1sc_cMTD_%d", k);
	  hrealL1scMTDScan[k] = (TH1F*)hrealLMTDScan[k] -> Clone(clNameLRealmtd);
	  hrealL1scMTDScan[k] -> Scale(cr_sec[i]);
	  cMTD_LscanReal -> cd(k+1);
	  nice_canv1(gPad);
	  hrealL1scMTDScan[k] -> SetLineColor(col);
	  if(i==0){
	    hrealL1scMTDScan[k] -> GetXaxis() -> SetTitle("invM [MeV]");
	    hrealL1scMTDScan[k] -> GetYaxis() -> SetTitle("counts*#sigma");
	    hrealL1scMTDScan[k] -> Draw();
	    hrealL1scMTDScanSum[k] = hrealL1scMTDScan[k];
	  }else{
	    hrealL1scMTDScan[k] -> Draw("same");
	    hrealL1scMTDScanSum[k] -> Add(hrealL1scMTDScan[k]);
	  }
	}

	TH1F *hXall1MTDScan[20], *hXall1scMTDScan[20], *hrealX1MTDScan[20], *hrealX1scMTDScan[20];
	char clNameXAllmtd[24], clNameXRealmtd[24];

	for(int k = 0; k < 20; k++){
	  sprintf(clNameXAllmtd, "hXall1sc_cMTD_%d", k);
	  hXall1scMTDScan[k] = (TH1F*)hXallMTDScan[k] -> Clone(clNameXAllmtd);
	  hXall1scMTDScan[k] -> Scale(cr_sec[i]);
	  cMTD_XscanAll -> cd(k+1);
	  hXall1scMTDScan[k] -> SetLineColor(col);
	  if(i==0){
	    hXall1scMTDScan[k] -> GetXaxis() -> SetTitle("invM [MeV]");
	    hXall1scMTDScan[k] -> GetYaxis() -> SetTitle("counts*#sigma");
	    hXall1scMTDScan[k] -> Draw();
	    hXall1scMTDScanSum[k] = hXall1scMTDScan[k];
	  }else{
	    hXall1scMTDScan[k] -> Draw("same");
	    hXall1scMTDScanSum[k] -> Add(hXall1scMTDScan[k]);
	  }
	  
	  sprintf(clNameXRealmtd, "hrealX1sc_cMTD_%d", k);
	  hrealX1scMTDScan[k] = (TH1F*)hrealXMTDScan[k] -> Clone(clNameXRealmtd);
	  hrealX1scMTDScan[k] -> Scale(cr_sec[i]);
	  cMTD_XscanReal -> cd(k+1);
	  hrealX1scMTDScan[k] -> SetLineColor(col);
	  if(i==0){
	    hrealX1scMTDScan[k] -> GetXaxis() -> SetTitle("invM [MeV]");
	    hrealX1scMTDScan[k] -> GetYaxis() -> SetTitle("counts*#sigma");
	    hrealX1scMTDScan[k] -> Draw();
	    hrealX1scMTDScanSum[k] = hrealX1scMTDScan[k];
	  }else{
	    hrealX1scMTDScan[k] -> Draw("same");
	    hrealX1scMTDScanSum[k] -> Add(hrealX1scMTDScan[k]);
	  }
	}//end MTD scan

	//VERTz scan
	TH1F *hLall1VertScan[30], *hLall1scVertScan[30], *hrealL1VertScan[30], *hrealL1scVertScan[30];
	char clNameLAll[24], clNameLReal[24];

	for(int k = -10; k < 20; k++){
	  //sprintf(clNameLAll, "hLall1_cVert_%d", k);
	  //hLall1VertScan[k] = (TH1F*)hLallVertScan[k] -> Clone(clNameLAll);
	  sprintf(clNameLAll, "hLall1sc_cVert_%d", k);
	  hLall1scVertScan[k+10] = (TH1F*)hLallVertScan[k+10] -> Clone(clNameLAll);
	  hLall1scVertScan[k+10] -> Scale(cr_sec[i]);
	  if(k < 5) cVertZ_LscanAll1 -> cd(k+11);
	  else  cVertZ_LscanAll2 -> cd(k-4);
	  nice_canv1(gPad);
	  hLall1scVertScan[k+10] -> SetLineColor(col);
	  if(i==0){
	    hLall1scVertScan[k+10] -> GetXaxis() -> SetTitle("invM [MeV]");
	    hLall1scVertScan[k+10] -> GetYaxis() -> SetTitle("counts*#sigma");
	    hLall1scVertScan[k+10] -> Draw();
	    hLall1scVertScanSum[k+10] = hLall1scVertScan[k+10];
	  }else{
	    hLall1scVertScan[k+10] -> Draw("same");
	    hLall1scVertScanSum[k+10] -> Add(hLall1scVertScan[k+10]);
	  }
	  

	  // sprintf(clNameLReal, "hrealL1_cVert_%d", k);
	  //hrealL1VertScan[k] = (TH1F*)hrealLVertScan[k] -> Clone(clNameLReal);
	  sprintf(clNameLReal, "hrealL1sc_cVert_%d", k);
	  hrealL1scVertScan[k+10] = (TH1F*)hrealLVertScan[k+10] -> Clone(clNameLReal);
	  hrealL1scVertScan[k+10] -> Scale(cr_sec[i]);
	  if(k < 5) cVertZ_LscanReal1 -> cd(k+11);
	  else  cVertZ_LscanReal2 -> cd(k-4);
	  nice_canv1(gPad);
	  hrealL1scVertScan[k+10] -> SetLineColor(col);
	  if(i==0){
	    hrealL1scVertScan[k+10] -> GetXaxis() -> SetTitle("invM [MeV]");
	    hrealL1scVertScan[k+10] -> GetYaxis() -> SetTitle("counts*#sigma");
	    hrealL1scVertScan[k+10] -> Draw();
	    hrealL1scVertScanSum[k+10] = hrealL1scVertScan[k+10];
	  }else{
	    hrealL1scVertScan[k+10] -> Draw("same");
	    hrealL1scVertScanSum[k+10] -> Add(hrealL1scVertScan[k+10]);
	  }
	}

	
	TH1F *hXall1VertScan[30], *hXall1scVertScan[30], *hrealX1VertScan[30], *hrealX1scVertScan[30];
	char clNameAll[24], clNameReal[24];

	for(int k = -10; k < 20; k++){
	  // sprintf(clNameAll, "hXall1_cVert_%d", k);
	  //hXall1VertScan[k] = (TH1F*)hXallVertScan[k] -> Clone(clNameAll);
	  sprintf(clNameAll, "hXall1sc_cVert_%d", k);
	  hXall1scVertScan[k+10] = (TH1F*)hXallVertScan[k+10] -> Clone(clNameAll);
	  hXall1scVertScan[k+10] -> Scale(cr_sec[i]);
	  if(k < 5) cVertZ_XscanAll1 -> cd(k+11);
	  else  cVertZ_XscanAll2 -> cd(k-4);
	  nice_canv1(gPad);
	  hXall1scVertScan[k+10] -> SetLineColor(col);
	  if(i==0){
	    hXall1scVertScan[k+10] -> GetXaxis() -> SetTitle("invM [MeV]");
	    hXall1scVertScan[k+10] -> GetYaxis() -> SetTitle("counts*#sigma");
	    hXall1scVertScan[k+10] -> Draw();
	    hXall1scVertScanSum[k+10] = hXall1scVertScan[k+10];
	  }else{
	    hXall1scVertScan[k+10] -> Draw("same");
	    hXall1scVertScanSum[k+10] -> Add(hXall1scVertScan[k+10]);
	  }

	  //sprintf(clNameReal, "hrealX1_cVert_%d", k);
	  // hrealX1VertScan[k] = (TH1F*)hrealXVertScan[k] -> Clone(clNameReal);
	  sprintf(clNameReal, "hrealX1sc_cVert_%d", k);
	  hrealX1scVertScan[k+10] = (TH1F*)hrealXVertScan[k+10] -> Clone(clNameReal);
	  hrealX1scVertScan[k+10] -> Scale(cr_sec[i]);
	  if(k < 5) cVertZ_XscanReal1 -> cd(k+11);
	  else  cVertZ_XscanReal2 -> cd(k-4);
	  nice_canv1(gPad);
	  hrealX1scVertScan[k+10] -> SetLineColor(col);
	  if(i==0){
	    hrealX1scVertScan[k+10] -> GetXaxis() -> SetTitle("invM [MeV]");
	    hrealX1scVertScan[k+10] -> GetYaxis() -> SetTitle("counts*#sigma");
	    hrealX1scVertScan[k+10] -> Draw();
	    hrealX1scVertScanSum[k+10] = hrealX1scVertScan[k+10];
	  }else{
	    hrealX1scVertScan[k+10] -> Draw("same");
	    hrealX1scVertScanSum[k+10] -> Add(hrealX1scVertScan[k+10]);
	  }
	}
	//end VERTz scan
	*/

	//MTD_L, Lmass, MTD_X, Vertz_X
	TH1F *hLall1Vert = (TH1F*)hLallVert -> Clone("hLall1_cVert");
	TH1F *hLall1scVert = (TH1F*)hLallVert -> Clone("hLall1sc_cVert");
	TH1F *hrealL1Vert = (TH1F*)hrealLVert -> Clone("hrealL1_cVert");
	TH1F *hrealL1scVert = (TH1F*)hrealLVert -> Clone("hrealL1sc_cVert");
	//	TH1F *hXall1Vert = (TH1F*)hXallVert -> Clone("hXall1_cVert");
	//	TH1F *hXall1scVert = (TH1F*)hXallVert -> Clone("hXall1sc_cVert");
	TH1F *hrealX1Vert = (TH1F*)hrealXVert -> Clone("hrealX1_cVert");
	TH1F *hrealX1scVert = (TH1F*)hrealXVert -> Clone("hrealX1sc_cVert");
	
        TH1F *clLambdaScVertrec = (TH1F*)hLallVert -> Clone("hLallVert_chan");
	
      	hLall1scVert -> Scale(cr_sec[i]);
	hrealL1scVert -> Scale(cr_sec[i]);
	//	hXall1scVert -> Scale(cr_sec[i]);
	hrealX1scVert -> Scale(cr_sec[i]);

	hLallSumVert -> Add(hLall1Vert);
	hrealLSumVert -> Add(hrealL1Vert);
	//	hXallSumVert -> Add(hXall1Vert);
	hrealXSumVert -> Add(hrealX1Vert);
      
	hLallSumScVert -> Sumw2();
	hLallSumScVert -> Sumw2();
	hrealLSumScVert -> Sumw2();
	//	hXallSumScVert -> Sumw2();
	hrealXSumScVert -> Sumw2();

	hLallSumScVert -> Add(hLall1scVert);
	hrealLSumScVert -> Add(hrealL1scVert);
	//	hXallSumScVert -> Add(hXall1scVert);
	hrealXSumScVert -> Add(hrealX1scVert);
	//*******************************************************
	//		TH1F *hLall1 = (TH1F*)hLall -> Clone("hLall1_c");

	if(i == 0){
	  //no cuts
	  hLall90 = (TH1F*)hLall1 -> Clone("hLall90");
	  hrealL90 = (TH1F*)hrealL1 -> Clone("hrealL90");
	  //	  TH1F *hXall90 = hXall1 -> Clone("hXall90");
	  //	  TH1F *hXrealLpim90 = hXrealLpim1 -> Clone("hXrealLpim90");
	  hrealX90 = (TH1F*)hrealX1 -> Clone("hrealX90");
	
	  hLall90Sc = (TH1F*)hLall1sc -> Clone("hLall90Sc");
	  hrealL90Sc = (TH1F*)hrealL1sc -> Clone("hrealL90Sc");
	  //	  TH1F *hXall90Sc = hXall1sc -> Clone("hXall90Sc");
	  //	  TH1F *hXrealLpim90Sc = hXrealLpim1sc -> Clone("hXrealLpim90Sc");
	  hrealX90Sc = (TH1F*)hrealX1sc -> Clone("hrealX90Sc");

	  hLall90 -> SetLineColor(kBlack);
	  hrealL90 -> SetLineColor(kBlack);
	  //	  hXall90 -> SetLineColor(kBlack);
	  //	  hXrealLpim90 -> SetLineColor(kBlack);
	  hrealX90 -> SetLineColor(kBlack);
	
	  hLall90Sc -> SetLineColor(kBlack);
	  hrealL90Sc -> SetLineColor(kBlack);
	  //	  hXall90Sc -> SetLineColor(kBlack);
	  //	  hXrealLpim90Sc -> SetLineColor(kBlack);
	  hrealX90Sc -> SetLineColor(kBlack);

	  clLambdaSc -> SetLineWidth(2);
	  clXiSc -> SetLineWidth(2);
	  
	  //MTD_L, Lmass, MTD_X
	  hLall90Mtd = (TH1F*)hLall1Mtd -> Clone("hLall90Mtd");
	  hrealL90Mtd = (TH1F*)hrealL1Mtd -> Clone("hrealL90Mtd");
	  //	  TH1F *hXall90Mtd = hXall1Mtd -> Clone("hXall90Mtd");
	  hrealX90Mtd = (TH1F*)hrealX1Mtd -> Clone("hrealX90Mtd");
	
	  hLall90ScMtd = (TH1F*)hLall1scMtd -> Clone("hLall90ScMtd");
	  hrealL90ScMtd = (TH1F*)hrealL1scMtd -> Clone("hrealL90ScMtd");
	  //	  TH1F *hXall90ScMtd = hXall1scMtd -> Clone("hXall90ScMtd");
	  hrealX90ScMtd = (TH1F*)hrealX1scMtd -> Clone("hrealX90ScMtd");

	  hLall90Mtd -> SetLineColor(kBlack);
	  hrealL90Mtd -> SetLineColor(kBlack);
	  //	  hXall90Mtd -> SetLineColor(kBlack);
	  hrealX90Mtd -> SetLineColor(kBlack);
	
	  hLall90ScMtd -> SetLineColor(kBlack);
	  hrealL90ScMtd -> SetLineColor(kBlack);
	  //	  hXall90ScMtd -> SetLineColor(kBlack);
	  hrealX90ScMtd -> SetLineColor(kBlack);

	  clXiSc_fin -> SetLineWidth(2);
	  	  
	//MTD_L, Lmass, MTD_X, Vertz_X
	  hLall90Vert = (TH1F*)hLall1Vert -> Clone("hLall90Vert");
	  hrealL90Vert = (TH1F*)hrealL1Vert -> Clone("hrealL90Vert");
	  //	  TH1F *hXall90Vert = hXall1Vert -> Clone("hXall90Vert");
	  hrealX90Vert = (TH1F*)hrealX1Vert -> Clone("hrealX90Vert");
	
	  hLall90ScVert = (TH1F*)hLall1scVert -> Clone("hLall90ScVert");
	  hrealL90ScVert = (TH1F*)hrealL1scVert -> Clone("hrealL90ScVert");
	  //	  TH1F *hXall90ScVert = hXall1scVert -> Clone("hXall90ScVert");
	  hrealX90ScVert = (TH1F*)hrealX1scVert -> Clone("hrealX90ScVert");

	  hLall90Vert -> SetLineColor(kBlack);
	  hrealL90Vert -> SetLineColor(kBlack);
	  //	  hXall90Vert -> SetLineColor(kBlack);
	  hrealX90Vert -> SetLineColor(kBlack);
	
	  hLall90ScVert -> SetLineColor(kBlack);
	  hrealL90ScVert -> SetLineColor(kBlack);
	  //	  hXall90ScVert -> SetLineColor(kBlack);
	  hrealX90ScVert -> SetLineColor(kBlack);

          clLambdaScVertrec -> SetLineWidth(2);
	  	  
	  /*TH1F *hXall90Vert[20], *hrealX90Vert[20], *hXall90ScVert[20], *hrealX90ScVert[20];
	  char clNameAll90[24], clNameReal90[24];
	  for(int k = 0; k < 20; k++){
	    sprintf(clNameAll90, "hXall90Vert_%d", k);
	    hXall90Vert[k] = hXall1Vert -> Clone(clNameAll90);
	    sprintf(clNameAll90, "hXall90ScVert_%d", k);
	    hXall90ScVert[k] = hXall1scVert -> Clone(clNameAll90);
	    sprintf(clNameReal90, "hrealX90Vert_%d", k);
	    hrealX90Vert[k] = hrealX1Vert -> Clone(clNameReal90);
	    sprintf(clNameReal90, "hrealX90ScVert_%d", k);
	    hrealX90ScVert[k] = hrealX1scVert -> Clone(clNameReal90);
	    }*/
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

    hrealLSum -> Fit(fit, "0");
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
      else
	hrealLSumPeak -> SetBinContent(j, hrealLSum -> GetBinContent(j));
    }

    hrealLSumSc -> Fit(fit, "0");
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
      else hrealLSumPeakSc -> SetBinContent(j, hrealLSumSc -> GetBinContent(j));    
    }

    TH1F *hrealLSumPeakCl = (TH1F*)hrealLSumPeak -> Clone();
    TH1F *hrealLSumPeakScCl = (TH1F*)hrealLSumPeakSc -> Clone();
    hLallSumBG -> Add(hLallSum, hrealLSumPeakCl, 1, -1); 
    hLallSumBGSc -> Add(hLallSumSc, hrealLSumPeakScCl, 1, -1); 

    hLallSumBG -> SetLineColor(kRed);
    hLallSumBGSc -> SetLineColor(kRed);
    hrealLSumPeak -> SetLineColor(8);
    hrealLSumPeakSc -> SetLineColor(8);

    cntSL = hrealLSum -> Integral(a,b);
    cntBL = hLallSumBG -> Integral(a,b);
    cntSLsc = hrealLSumSc -> Integral(a,b);
    cntBLsc = hLallSumBGSc -> Integral(a,b);

    for(int j = 1; j <= nL; j++){
      if(hrealLSumPeak -> GetBinContent(j)){
	kL++;
	s_bg_vL[kL] = (hrealLSumPeak -> GetBinContent(j))/(hLallSumBG -> GetBinContent(j));
	binL[kL] = (hrealLSumPeak -> GetBinLowEdge(j)) + (hrealLSumPeak -> GetBinWidth(j));
	// cout << "kL:" << kL << " s_bg_vL[kL]:" << s_bg_vL[kL] << " S:" << hrealLSumPeak -> GetBinContent(j) << " B:" << hLallSumBG -> GetBinContent(j)  << endl;
      }
    }
    for(int j = 1; j <= nLSc; j++){
      if(hrealLSumPeakSc -> GetBinContent(j)){
	kLSc++;
	s_bg_vLSc[kLSc] = (hrealLSumPeakSc -> GetBinContent(j))/(hLallSumBGSc -> GetBinContent(j));
	binLSc[kLSc] = (hrealLSumPeakSc -> GetBinLowEdge(j)) + (hrealLSumPeakSc -> GetBinWidth(j));
	// cout << "kL:" << kL << " s_bg_vL[kL]:" << s_bg_vL[kL] << " S:" << hrealLSumPeak -> GetBinContent(j) << " B:" << hLallSumBG -> GetBinContent(j)  << endl;
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

    hrealXSumSc -> Fit(fit, "0");
    center_fit = fit -> GetParameter(1);
    sigma_fit = fit -> GetParameter(2);
    m3sigma = center_fit - 3*sigma_fit;
    p3sigma = center_fit + 3*sigma_fit;
    a = hrealXSumSc -> GetXaxis() -> FindBin(m3sigma);
    b = hrealXSumSc -> GetXaxis() -> FindBin(p3sigma);
    MassminX = m3sigma;
    MassmaxX = p3sigma;
    for(int j = 1; j <= nX; j++){
      massX = hrealXSum -> GetBinLowEdge(j);
      if(massX < MassminX) continue;
      else if(massX > MassmaxX) break;
      else hrealXSumPeak -> SetBinContent(j, hrealXSum -> GetBinContent(j));
    }
    for(int j = 1; j <= nXSc; j++){
      massXSc = hrealXSumSc -> GetBinLowEdge(j);
      if(massXSc < MassminX) continue;
      else if(massXSc > MassmaxX) break;
      else hrealXSumPeakSc -> SetBinContent(j, hrealXSumSc -> GetBinContent(j));
    }

    TH1F *hrealXSumPeakCl = (TH1F*)hrealXSumPeak -> Clone();
    TH1F *hrealXSumPeakScCl = (TH1F*)hrealXSumPeakSc -> Clone();
    //    hXallSumBG -> Add(hXallSum, hrealXSumPeakCl, 1, -1); 
    //    hXallSumBGSc -> Add(hXallSumSc, hrealXSumPeakScCl, 1, -1);
    hXallSumBG -> Add(hrealXSum, hrealXSumPeakCl, 1, -1); 
    hXallSumBGSc -> Add(hrealXSumSc, hrealXSumPeakScCl, 1, -1); 

    hXallSumBG -> SetLineColor(kRed);
    hXallSumBGSc -> SetLineColor(kRed);
    hrealXSumPeak -> SetLineColor(8);
    hrealXSumPeakSc -> SetLineColor(8);

    cntSX = hrealXSum -> Integral(a,b);
    cntBX = hXallSumBG -> Integral(a,b);
    cntSXsc = hrealXSumSc -> Integral(a,b);
    cntBXsc = hXallSumBGSc -> Integral(a,b);

    for(int j = 1; j <= nX; j++){
      if(hrealXSumPeak -> GetBinContent(j)){
	kX++;
	s_bg_vX[kX] = (hrealXSumPeak -> GetBinContent(j))/(hXallSumBG -> GetBinContent(j));
	binX[kX] = (hrealXSumPeak -> GetBinLowEdge(j)) + (hrealXSumPeak -> GetBinWidth(j));
	// cout << "kL:" << kL << " s_bg_vL[kL]:" << s_bg_vL[kL] << " S:" << hrealLSumPeak -> GetBinContent(j) << " B:" << hLallSumBG -> GetBinContent(j)  << endl;
      }
    }
    for(int j = 1; j <= nXSc; j++){
      if(hrealXSumPeakSc -> GetBinContent(j)){
	kXSc++;
	s_bg_vXSc[kXSc] = (hrealXSumPeakSc -> GetBinContent(j))/(hXallSumBGSc -> GetBinContent(j));
	binXSc[kXSc] = (hrealXSumPeakSc -> GetBinLowEdge(j)) + (hrealXSumPeakSc -> GetBinWidth(j));
	// cout << "kL:" << kL << " s_bg_vL[kL]:" << s_bg_vL[kL] << " S:" << hrealLSumPeak -> GetBinContent(j) << " B:" << hLallSumBG -> GetBinContent(j)  << endl;
      }
    }


    l1 -> AddEntry(hLallSum, "sum all channels", "L");
    l1 -> AddEntry(hLall90, "#Xi^{-}2K^{+}p", "L");
    l1a -> AddEntry(hLallSumBG, "BG", "L");
    l1a -> AddEntry(hrealLSumPeak, "signal", "L");

     //invM no scaling
    /*   TCanvas *cimLnsA = new TCanvas("cimLnsA", "cimLnsA");
    TCanvas *cimLnsR = new TCanvas("cimLnsR", "cimLnsR");
    TCanvas *cimLnsBG = new TCanvas("cimLnsBG", "cimLnsBG");
    TCanvas *cimXnsA = new TCanvas("cimXnsA", "cimXnsA");
    TCanvas *cimXnsR = new TCanvas("cimXnsR", "cimXnsR");
    TCanvas *cimXnsBG = new TCanvas("cimXnsBG", "cimXnsBG");*/

    cLambdaXiMass -> cd(1);
    nice_canv1(gPad);
    hLallSum -> SetTitle("#pi^{-} in Hades + anything (p) in FwDet");
    hLallSum -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSum -> GetYaxis() -> SetTitle("counts");
    hLallSum -> Draw();
    hLall90 -> Draw("same");
    l1 -> Draw("same");

    /*  cimLnsA -> cd();
    nice_canv1(gPad);
    hLallSum -> SetTitle("#pi^{-} in Hades + anything (p) in FwDet");
    hLallSum -> GetXaxis() -> SetTitle("invM [MeV]");
    hLallSum -> GetYaxis() -> SetTitle("counts");
    hLallSum -> Draw();
    hLall90 -> Draw("same");
    l1 -> Draw("same");
    */
    cLambdaXiMass -> cd(2);
    nice_canv1(gPad);
    hrealLSum -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSum -> GetXaxis() -> SetTitle("M_{#pi_{-}} [MeV]");
    hrealLSum -> GetYaxis() -> SetTitle("counts");
    hrealLSum -> Draw();
    hrealL90 -> Draw("same");
    l1 -> Draw("same");
    /*
    cimLnsR -> cd();
    nice_canv1(gPad);
    hrealLSum -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSum -> GetXaxis() -> SetTitle("invM [MeV]");
    hrealLSum -> GetYaxis() -> SetTitle("counts");
    hrealLSum -> Draw();
    hrealL90 -> Draw("same");
    l1 -> Draw("same");
    */
    cLambdaXiMass -> cd(3);
    nice_canv1(gPad);
    hLallSumBG -> SetTitle("Real #Lambda peak and BG");
    hLallSumBG -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumBG -> GetYaxis() -> SetTitle("counts");
    hLallSumBG -> Draw();
    hrealLSumPeak -> Draw("same");
    l1a -> Draw("same");
    /*
    cimLnsBG -> cd();
    nice_canv1(gPad);
    hLallSumBG -> SetTitle("Real #Lambda peak and BG");
    hLallSumBG -> GetXaxis() -> SetTitle("invM [MeV]");
    hLallSumBG -> GetYaxis() -> SetTitle("counts");
    hLallSumBG -> Draw();
    hrealLSumPeak -> Draw("same");
    l1a -> Draw("same");
    */
    cLambdaXiMass -> cd(4);
    nice_canv1(gPad);
    hrealXSum -> SetTitle("2#pi^{-} in Hades + anything (p) in FwDet");
    hrealXSum -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSum -> GetYaxis() -> SetTitle("counts");
    hrealXSum -> Draw();
    hrealX90 -> Draw("same");
    l1 -> Draw("same");
    /*
    cimXnsA -> cd();
    nice_canv1(gPad);
    hXallSum -> SetTitle("2#pi^{-} in Hades + anything (p) in FwDet");
    hXallSum -> GetXaxis() -> SetTitle("invM [MeV]");
    hXallSum -> GetYaxis() -> SetTitle("counts");
    hXallSum -> Draw();
    hXall90 -> Draw("same");
    l1 -> Draw("same");
    */
    /*  cLambdaXiMass -> cd(5);
    nice_canv1(gPad);
    hXrealLpimSum -> SetTitle("#pi^{-} and p from #Lambda(1115) + #pi^{-} in Hades");
    hXrealLpimSum -> GetXaxis() -> SetTitle("invM [MeV]");
    hXrealLpimSum -> GetYaxis() -> SetTitle("counts");
    hXrealLpimSum -> Draw();
    hXrealLpim90 -> Draw("same");
    */
    cLambdaXiMass -> cd(5);
    nice_canv1(gPad);
    hrealXSum -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSum -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSum -> GetYaxis() -> SetTitle("counts");
    hrealXSum -> Draw();
    hrealX90 -> Draw("same");
    l1 -> Draw("same");
    /*
    cimXnsR -> cd();
    nice_canv1(gPad);
    hrealXSum -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSum -> GetXaxis() -> SetTitle("invM [MeV]");
    hrealXSum -> GetYaxis() -> SetTitle("counts");
    hrealXSum -> Draw();
    hrealX90 -> Draw("same");
    */
    cLambdaXiMass -> cd(6);
    nice_canv1(gPad);
    hXallSumBG -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBG -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hXallSumBG -> GetYaxis() -> SetTitle("counts");
    hXallSumBG -> Draw();
    hrealXSumPeak -> Draw("same");
    l1a -> Draw("same");
    /*
    cimXnsBG -> cd();
    nice_canv1(gPad);
    hXallSumBG -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBG -> GetXaxis() -> SetTitle("invM [MeV]");
    hXallSumBG -> GetYaxis() -> SetTitle("counts");
    hXallSumBG -> Draw();
    hrealXSumPeak -> Draw("same");
    l1a -> Draw("same");
    */

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
    lfin -> AddEntry(hLallSumSc, "sum of all channels");
    lfin -> AddEntry(hrealLSumSc, "real signal");
    lfin -> AddEntry(hLallSumBGSc, "BG");

    /*hLallSumSc -> Rebin(2);
    hrealLSumSc -> Rebin(2);
    hLallSumBGSc -> Rebin(2);
    hLallSumScMtd -> Rebin(2);
    hrealLSumScMtd -> Rebin(2);
    hLallSumBGScMtd -> Rebin(2);
    hLallSumScVert -> Rebin(2);
    hrealLSumScVert -> Rebin(2);
    hLallSumBGScVert -> Rebin(2);

    hXallSumSc -> Rebin(2);
    hrealXSumSc -> Rebin(2);
    hXallSumBGSc -> Rebin(2);
    hXallSumScMtd -> Rebin(2);
    hrealXSumScMtd -> Rebin(2);
    hXallSumBGScMtd -> Rebin(2);
    hXallSumScVert -> Rebin(2);
    hrealXSumScVert -> Rebin(2);
    hXallSumBGScVert -> Rebin(2);
    */
    //invM scaling
    TCanvas *cimLsAsc = new TCanvas("cimLsAsc", "cimLsAsc");
    TCanvas *cimLsRsc = new TCanvas("cimLsRsc", "cimLsRsc");
    TCanvas *cimLsBGsc = new TCanvas("cimLsBGsc", "cimLsBGsc");
    TCanvas *cimXsAsc = new TCanvas("cimXsAsc", "cimXsAsc");
    TCanvas *cimXsRsc = new TCanvas("cimXsRsc", "cimXsRsc");
    TCanvas *cimXsBGsc = new TCanvas("cimXsBGsc", "cimXsBGsc");

    TCanvas *cimLNoCutsSc = new TCanvas("cimLNoCutsSc","cimLNoCutsSc"); //inv mass Lambda spectrum, no cuts, cr sec scaling
    TCanvas *cimXMtdlVertlMlSc = new TCanvas("cimXMtdlVerlMlSc","cimXMtdlVerlMlSc"); //inv mass Xi spectrum, MTD_L, VERTz_L, Lmass cuts, cr sec scaling
    //>>>>>>>>>>>>>>>>>
    cLambdaXiMassSc -> cd(1);
    nice_canv1(gPad);
    hLallSumSc -> SetTitle("#pi^{-} in Hades - anything (p) in FwDet");
    hLallSumSc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumSc -> Draw("pE1");
    hLall90Sc -> Draw("p same");
    l1 -> Draw("same");
    
    cimLsAsc -> cd();
    nice_canv1(gPad);
    hLallSumSc -> SetTitle("#pi^{-} in Hades - anything (p) in FwDet");
    hLallSumSc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
//    hLallSumSc -> SetMarkerStyle(20);
//    hLallSumSc -> SetMarkerSize(.5);
//    hLallSumSc -> SetMarkerColor(4);
    hLall90Sc -> SetMarkerStyle(20);
    hLall90Sc -> SetMarkerSize(.5);
    hLallSumSc -> Draw("pE1");
    hLall90Sc -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassSc -> cd(2);
    nice_canv1(gPad);
    hrealLSumSc -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumSc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealLSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumSc -> Draw("pE1");
    hrealL90Sc -> Draw("p same");
    l1 -> Draw("same");
    
    cimLsRsc -> cd();
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

    cLambdaXiMassSc -> cd(3);
    nice_canv1(gPad);
    hLallSumBGSc -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGSc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumBGSc -> Draw("pE1");
    hrealLSumPeakSc -> Draw("p same");
    l1a -> Draw("same");
    
    cimLsBGsc -> cd();
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

    cimLNoCutsSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hLallSumSc -> SetTitle("#Lambda reconstruction, no cuts");
    hLallSumSc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    // hLallSumSc -> SetMarkerStyle(34);
    //hLallSumSc -> SetMarkerSize(1.7);
    hLallSumSc -> SetLineColor(4);
    hLallSumSc -> SetLineStyle(2);
    hLallSumSc -> SetLineWidth(2);
    hLallSumBGSc -> SetMarkerStyle(21);
    hLallSumBGSc -> SetMarkerSize(1);
    hLallSumBGSc -> SetMarkerColor(2);
    //hrealLSumSc -> SetMarkerStyle(20);
    //hrealLSumSc -> SetMarkerSize(1.2);
    hrealLSumSc -> SetLineColor(8);
    hLallSumSc -> Draw();
    hLallSumBGSc -> Draw("p same");
    hrealLSumSc -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");
    lfin -> Draw("same");//<<<<<<<<<<<<<<

    cLambdaXiMassSc -> cd(4);
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("2#pi^{-} in Hades - anything (p) in FwDet");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> Draw("pE1");
    hrealX90Sc -> Draw("p same");
    l1 -> Draw("same");
    
    cimXsAsc -> cd();
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
    
    /* cLambdaXiMassSc -> cd(5);
    nice_canv1(gPad);
    hXrealLpimSumSc -> SetTitle("#pi^{-} and p from #Lambda(1115) + #pi^{-} in Hades");
    hXrealLpimSumSc -> GetXaxis() -> SetTitle("invM [MeV]");
    hXrealLpimSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hXrealLpimSumSc -> Draw();
    hXrealLpim90Sc -> Draw("same");
    */
    cLambdaXiMassSc -> cd(5);
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumSc -> Draw("pE1");
    hrealX90Sc -> Draw("p same");
    l1 -> Draw("same");
    
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

    cLambdaXiMassSc -> cd(6);
    nice_canv1(gPad);
    hXallSumBGSc -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hXallSumBGSc -> GetYaxis() -> SetTitle("counts*#sigma");
    hXallSumBGSc -> Draw("pE1");
    hrealXSumPeakSc -> Draw("p same");
    l1a -> Draw("same");
    
    cimXsBGsc -> cd();
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
    
    cimXMtdlVertlMlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumSc -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass cuts");
    hrealXSumSc -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumSc -> GetYaxis() -> SetTitle("counts*#sigma");
    //hrealXSumSc -> SetMarkerStyle(34);
    //hrealXSumSc -> SetMarkerSize(1.7);
    hrealXSumSc -> SetLineColor(4);
    hXallSumSc -> SetLineStyle(2);
    hXallSumSc -> SetLineWidth(2);
  //hrealXSumSc -> SetMarkerStyle(20);
    //hrealXSumSc -> SetMarkerSize(1.2);
    hrealXSumSc -> SetLineColor(8);
    hXallSumBGSc -> SetMarkerStyle(21);
    hXallSumBGSc -> SetMarkerSize(.5);
    hXallSumBGSc -> SetMarkerColor(2);
    hrealXSumSc -> Draw();
    hXallSumBGSc -> Draw("p same");
    hrealXSumSc -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");
    lfin -> Draw("same");//<<<<<<<<<<<<<<


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

    hrealLSumMtd -> Fit(fit, "0");
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
      else
	hrealLSumPeakMtd -> SetBinContent(j, hrealLSumMtd -> GetBinContent(j));
    }

    hrealLSumScMtd -> Fit(fit, "0");
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
      else hrealLSumPeakScMtd -> SetBinContent(j, hrealLSumScMtd -> GetBinContent(j));    
    }

    TH1F *hrealLSumPeakClMtd = (TH1F*)hrealLSumPeakMtd -> Clone();
    TH1F *hrealLSumPeakScClMtd = (TH1F*)hrealLSumPeakScMtd -> Clone();
    hLallSumBGMtd -> Add(hLallSumMtd, hrealLSumPeakClMtd, 1, -1); 
    hLallSumBGScMtd -> Add(hLallSumScMtd, hrealLSumPeakScClMtd, 1, -1); 

    hLallSumBGMtd -> SetLineColor(kRed);
    hLallSumBGScMtd -> SetLineColor(kRed);
    hrealLSumPeakMtd -> SetLineColor(8);
    hrealLSumPeakScMtd -> SetLineColor(8);

    cntSLMtd = hrealLSumMtd -> Integral(a,b);
    cntBLMtd = hLallSumBGMtd -> Integral(a,b);
    cntSLscMtd = hrealLSumScMtd -> Integral(a,b);
    cntBLscMtd = hLallSumBGScMtd -> Integral(a,b);


    //Lmass
    int nLLmass = hrealLSumLmass -> GetNbinsX();
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

    /*
    //MTD_L scan
    int nLScMTDScan[20];
    for(int k = 0; k < 20; k++){
      nLScMTDScan[k] = hrealL1scMTDScanSum[k] -> GetNbinsX();
      hrealLSumPeakScMTDScan[k] = new TH1F("hRLsigMTD", "hRLsigMTD", nLScMTDScan[k], minL, maxL);
      hLallSumBGScMTDScan[k] = new TH1F("hLbgMTD", "hLbgMTD", nLScMTDScan[k], minL, maxL);
      for(int j = 1; j <= nLScMTDScan[k]; j++){
	massLSc = hrealL1scMTDScanSum[k] -> GetBinLowEdge(j);
	if(massLSc < MassminL) continue;
	else if(massLSc > MassmaxL) break;
	else hrealLSumPeakScMTDScan[k] -> SetBinContent(j, hrealL1scMTDScanSum[k] -> GetBinContent(j));    
	}
      TH1F *hrealLSumPeakScClMTDScan = hrealLSumPeakScMTDScan[k] -> Clone();
      hLallSumBGScMTDScan[k] -> Add(hLall1scMTDScanSum[k], hrealLSumPeakScClMTDScan, 1, -1); 
      hLallSumBGScMTDScan[k] -> SetLineColor(kRed);
      hrealLSumPeakScMTDScan[k] -> SetLineColor(8);
    }
    //end MTD_L scan

    */

    //SB L mtd
    for(int j = 1; j <= nLMtd; j++){
	if(hrealLSumPeakMtd -> GetBinContent(j)){
	  kLMtd++;
	  s_bg_vLMtd[kLMtd] = (hrealLSumPeakMtd -> GetBinContent(j))/(hLallSumBGMtd -> GetBinContent(j));
	  binLMtd[kLMtd] = (hrealLSumPeakMtd -> GetBinLowEdge(j)) + (hrealLSumPeakMtd -> GetBinWidth(j));
      	}
    }
    for(int j = 1; j <= nLScMtd; j++){
      if(hrealLSumPeakScMtd -> GetBinContent(j)){
	kLScMtd++;
	s_bg_vLScMtd[kLScMtd] = (hrealLSumPeakScMtd -> GetBinContent(j))/(hLallSumBGScMtd -> GetBinContent(j));
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

    hrealXSumMtd -> Fit(fit, "0");
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
      else hrealXSumPeakMtd -> SetBinContent(j, hrealXSumMtd -> GetBinContent(j));
    }
    hrealXSumScMtd -> Fit(fit, "0");
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
      else hrealXSumPeakScMtd -> SetBinContent(j, hrealXSumScMtd -> GetBinContent(j));
    }

    TH1F *hrealXSumPeakClMtd = (TH1F*)hrealXSumPeakMtd -> Clone();
    TH1F *hrealXSumPeakScClMtd = (TH1F*)hrealXSumPeakScMtd -> Clone();
    //    hXallSumBGMtd -> Add(hXallSumMtd, hrealXSumPeakClMtd, 1, -1); 
    //    hXallSumBGScMtd -> Add(hXallSumScMtd, hrealXSumPeakScClMtd, 1, -1);
    hXallSumBGMtd -> Add(hrealXSumMtd, hrealXSumPeakClMtd, 1, -1); 
    hXallSumBGScMtd -> Add(hrealXSumScMtd, hrealXSumPeakScClMtd, 1, -1); 

    hXallSumBGMtd -> SetLineColor(kRed);
    hXallSumBGScMtd -> SetLineColor(kRed);
    hrealXSumPeakMtd -> SetLineColor(8);
    hrealXSumPeakScMtd -> SetLineColor(8);

    cntSXMtd = hrealXSumMtd -> Integral(a,b);
    cntBXMtd = hXallSumBGMtd -> Integral(a,b);
    cntSXscMtd = hrealXSumScMtd -> Integral(a,b);
    cntBXscMtd = hXallSumBGScMtd -> Integral(a,b);

    /* //MTD_X scan
    int nXScMTDScan[20];
    for(int k = 0; k < 20; k++){
      nXScMTDScan[k] = hrealX1scMTDScanSum[k] -> GetNbinsX();
      hrealXSumPeakScMTDScan[k] = new TH1F("hRXsigMTD", "hRXsigMTD", nXScMTDScan[k], minX, maxX);
      hXallSumBGScMTDScan[k] = new TH1F("hXbgMTD", "hXbgMTD", nXScMTDScan[k], minX, maxX);
      for(int j = 1; j <= nXScMTDScan[k]; j++){
	massXSc = hrealX1scMTDScanSum[k] -> GetBinLowEdge(j);
	if(massXSc < MassminX) continue;
	else if(massXSc > MassmaxX) break;
	else hrealXSumPeakScMTDScan[k] -> SetBinContent(j, hrealX1scMTDScanSum[k] -> GetBinContent(j));    
	}
      TH1F *hrealXSumPeakScClMTDScan = hrealXSumPeakScMTDScan[k] -> Clone();
      hXallSumBGScMTDScan[k] -> Add(hXall1scMTDScanSum[k], hrealXSumPeakScClMTDScan, 1, -1); 
      hXallSumBGScMTDScan[k] -> SetLineColor(kRed);
      hrealXSumPeakScMTDScan[k] -> SetLineColor(8);
    }
    //end MTD_X scan
    */


    for(int j = 1; j <= nXMtd; j++){
      if(hrealXSumPeakMtd -> GetBinContent(j)){
	kXMtd++;
	s_bg_vXMtd[kXMtd] = (hrealXSumPeakMtd -> GetBinContent(j))/(hXallSumBGMtd -> GetBinContent(j));
	binXMtd[kXMtd] = (hrealXSumPeakMtd -> GetBinLowEdge(j)) + (hrealXSumPeakMtd -> GetBinWidth(j));
	// cout << "kL:" << kL << " s_bg_vL[kL]:" << s_bg_vL[kL] << " S:" << hrealLSumPeak -> GetBinContent(j) << " B:" << hLallSumBG -> GetBinContent(j)  << endl;
      }
    }
    for(int j = 1; j <= nXScMtd; j++){
      if(hrealXSumPeakScMtd -> GetBinContent(j)){
	kXScMtd++;
	s_bg_vXScMtd[kXScMtd] = (hrealXSumPeakScMtd -> GetBinContent(j))/(hXallSumBGScMtd -> GetBinContent(j));
	binXScMtd[kXScMtd] = (hrealXSumPeakScMtd -> GetBinLowEdge(j)) + (hrealXSumPeakScMtd -> GetBinWidth(j));
	// cout << "kL:" << kL << " s_bg_vL[kL]:" << s_bg_vL[kL] << " S:" << hrealLSumPeak -> GetBinContent(j) << " B:" << hLallSumBG -> GetBinContent(j)  << endl;
      }
    }



    /*  l1Mtd -> AddEntry(hLallSumMtd, "sum all channels", "L");
    l1Mtd -> AddEntry(hLall90Mtd, "#Xi^{-}2K^{+}p", "L");
    l1Mtd -> AddEntry(hLallSumBGMtd, "BG", "L");
    l1Mtd -> AddEntry(hrealLSumPeakMtd, "signal", "L");
    */

    //invM no scaling MTD
    /*  TCanvas *cimLnsAmtd = new TCanvas("cimLnsAmtd", "cimLnsAmtd");
    TCanvas *cimLnsRmtd = new TCanvas("cimLnsRmtd", "cimLnsRmtd");
    TCanvas *cimLnsBGmtd = new TCanvas("cimLnsBGmtd", "cimLnsBGmtd");
    TCanvas *cimXnsAmtd = new TCanvas("cimXnsAmtd", "cimXnsAmtd");
    TCanvas *cimXnsRmtd = new TCanvas("cimXnsRmtd", "cimXnsRmtd");
    TCanvas *cimXnsBGmtd = new TCanvas("cimXnsBGmtd", "cimXnsBGmtd");
    */
    cLambdaXiMassMtd -> cd(1);
    nice_canv1(gPad);
    hLallSumMtd -> SetTitle("#pi^{-} in Hades + anything (p) in FwDet");
    hLallSumMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumMtd -> GetYaxis() -> SetTitle("counts");
    hLallSumMtd -> Draw();
    hLall90Mtd -> Draw("same");
    l1 -> Draw("same");
    /*
    cimLnsAmtd -> cd();
    nice_canv1(gPad);
    hLallSumMtd -> SetTitle("#pi^{-} in Hades + anything (p) in FwDet");
    hLallSumMtd -> GetXaxis() -> SetTitle("invM [MeV]");
    hLallSumMtd -> GetYaxis() -> SetTitle("counts");
    hLallSumMtd -> Draw();
    hLall90Mtd -> Draw("same");
    l1 -> Draw("same");
    */
    cLambdaXiMassMtd -> cd(2);
    nice_canv1(gPad);
    hrealLSumMtd -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealLSumMtd -> GetYaxis() -> SetTitle("counts");
    hrealLSumMtd -> Draw();
    hrealL90Mtd -> Draw("same");
    l1 -> Draw("same");
    /*
    cimLnsRmtd -> cd();
    nice_canv1(gPad);
    hrealLSumMtd -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumMtd -> GetXaxis() -> SetTitle("invM [MeV]");
    hrealLSumMtd -> GetYaxis() -> SetTitle("counts");
    hrealLSumMtd -> Draw();
    hrealL90Mtd -> Draw("same");
    */
    cLambdaXiMassMtd -> cd(3);
    nice_canv1(gPad);
    hLallSumBGMtd -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hrealLSumPeakMtd -> Draw();
    hLallSumBGMtd -> Draw("same");
    l1a -> Draw("same");
    /*
    cimLnsBGmtd -> cd();
    nice_canv1(gPad);
    hLallSumBGMtd -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGMtd -> GetXaxis() -> SetTitle("invM [MeV]");
    hLallSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hrealLSumPeakMtd -> Draw();
    hLallSumBGMtd -> Draw("same");
    l1a -> Draw("same");
    */
    cLambdaXiMassMtd -> cd(4);
    nice_canv1(gPad);
    hrealXSumMtd -> SetTitle("2#pi^{-} in Hades + anything (p) in FwDet");
    hrealXSumMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumMtd -> GetYaxis() -> SetTitle("counts");
    hrealXSumMtd -> Draw();
    hrealX90Mtd -> Draw("same");
    l1 -> Draw("same");
    /*
    cimXnsAmtd -> cd();
    nice_canv1(gPad);
    hXallSumMtd -> SetTitle("2#pi^{-} in Hades + anything (p) in FwDet");
    hXallSumMtd -> GetXaxis() -> SetTitle("invM [MeV]");
    hXallSumMtd -> GetYaxis() -> SetTitle("counts");
    hXallSumMtd -> Draw();
    hXall90Mtd -> Draw("same");
    l1 -> Draw("same");
    */
    /*  cLambdaXiMass -> cd(5);
    nice_canv1(gPad);
    hXrealLpimSum -> SetTitle("#pi^{-} and p from #Lambda(1115) + #pi^{-} in Hades");
    hXrealLpimSum -> GetXaxis() -> SetTitle("invM [MeV]");
    hXrealLpimSum -> GetYaxis() -> SetTitle("counts");
    hXrealLpimSum -> Draw();
    hXrealLpim90 -> Draw("same");
    */
    cLambdaXiMassMtd -> cd(5);
    nice_canv1(gPad);
    hrealXSumMtd -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumMtd -> GetYaxis() -> SetTitle("counts");
    hrealXSumMtd -> Draw();
    hrealX90Mtd -> Draw("same");
    l1 -> Draw("same");
    /*
    cimXnsRmtd -> cd();
    nice_canv1(gPad);
    hrealXSumMtd -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumMtd -> GetXaxis() -> SetTitle("invM [MeV]");
    hrealXSumMtd -> GetYaxis() -> SetTitle("counts");
    hrealXSumMtd -> Draw();
    hrealX90Mtd -> Draw("same");
    */
    cLambdaXiMassMtd -> cd(6);
    nice_canv1(gPad);
    hXallSumBGMtd -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hXallSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hrealXSumPeakMtd -> Draw();
    hXallSumBGMtd -> Draw("same");
    l1a -> Draw("same");
    /*
    cimXnsBGmtd -> cd();
    nice_canv1(gPad);
    hXallSumBGMtd -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGMtd -> GetXaxis() -> SetTitle("invM [MeV]");
    hXallSumBGMtd -> GetYaxis() -> SetTitle("counts");
    hrealXSumPeakMtd -> Draw();
    hXallSumBGMtd -> Draw("same");
    l1a -> Draw("same");
    */
    //invM scaling MTD
    TCanvas *cimLsAmtdsc = new TCanvas("cimLsAmtdsc", "cimLsAmtdsc");
    TCanvas *cimLsRmtdsc = new TCanvas("cimLsRmtdsc", "cimLsRmtdsc");
    TCanvas *cimLsBGmtdsc = new TCanvas("cimLsBGmtdsc", "cimLsBGmtdsc");
    TCanvas *cimXsAmtdsc = new TCanvas("cimXsAmtdsc", "cimXsAmtdsc");
    TCanvas *cimXsRmtdsc = new TCanvas("cimXsRmtdsc", "cimXsRmtdsc");
    TCanvas *cimXsBGmtdsc = new TCanvas("cimXsBGmtdsc", "cimXsBGmtdsc");
    

    TCanvas *cimLMtdlSc = new TCanvas("cimLMtdlSc","cimLMtdlSc"); //inv mass Lambda spectrum, MTD_L cut, cr sec scaling
    TCanvas *cimXMtdlVertlMlMtdxSc = new TCanvas("cimXMtdlVerlMlMtdxSc","cimXMtdlVerlMlMtdxSc"); //inv mass Xi spectrum, MTD_L, VERTz_L, Lmass, MTD_X cuts, cr sec scaling

    cLambdaXiMassScMtd -> cd(1);
    nice_canv1(gPad);
    hLallSumScMtd -> SetTitle("#pi^{-} in Hades - anything (p) in FwDet");
    hLallSumScMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScMtd -> Draw();
    hLall90ScMtd -> Draw("same");
    l1 -> Draw("same");
    
    cimLsAmtdsc -> cd();
    nice_canv1(gPad);
    hLallSumScMtd -> SetTitle("#pi^{-} in Hades - anything (p) in FwDet");
    hLallSumScMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScMtd -> SetMarkerStyle(20);
    hLallSumScMtd -> SetMarkerSize(.5);
    hLallSumScMtd -> SetMarkerColor(4);
    hLall90ScMtd -> SetMarkerStyle(20);
    hLall90ScMtd -> SetMarkerSize(.5);
    hLallSumScMtd -> Draw("pE1");
    hLall90ScMtd -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassScMtd -> cd(2);
    nice_canv1(gPad);
    hrealLSumScMtd -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumScMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealLSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumScMtd -> Draw("pE1");
    hrealL90ScMtd -> Draw("p same");
    l1 -> Draw("same");
    
    cimLsRmtdsc -> cd();
    nice_canv1(gPad);
    hrealLSumScMtd -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumScMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealLSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumScMtd -> SetMarkerStyle(20);
    hrealLSumScMtd -> SetMarkerSize(.5);
    hrealLSumScMtd -> SetMarkerColor(4);
    hrealL90ScMtd -> SetMarkerStyle(20);
    hrealL90ScMtd -> SetMarkerSize(.5);
    hrealLSumScMtd -> Draw("pE1");
    hrealL90ScMtd -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassScMtd -> cd(3);
    nice_canv1(gPad);
    hLallSumBGScMtd -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGScMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumBGScMtd -> Draw("p");
    hrealLSumPeakScMtd -> Draw("same");
    l1a -> Draw("same");
    
    cimLsBGmtdsc -> cd();
    nice_canv1(gPad);
    hLallSumBGScMtd -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGScMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumBGScMtd -> SetMarkerStyle(20);
    hLallSumBGScMtd -> SetMarkerSize(.5);
    hLallSumBGScMtd -> SetMarkerColor(2);
    hrealLSumPeakScMtd -> SetMarkerStyle(20);
    hrealLSumPeakScMtd -> SetMarkerSize(.5);
    hrealLSumPeakScMtd -> SetMarkerColor(8);
    hLallSumBGScMtd -> Draw("p");
    hrealLSumPeakScMtd -> Draw("same");
    l1a -> Draw("same");
    
    cimLMtdlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hLallSumScMtd -> SetTitle("#Lambda reconstruction, MTD_L cut");
    hLallSumScMtd -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    //hLallSumScMtd -> SetMarkerStyle(34);
    //hLallSumScMtd -> SetMarkerSize(1.7);
    hLallSumScMtd -> SetLineColor(4);
    hLallSumScMtd -> SetLineStyle(2);
    hLallSumScMtd -> SetLineWidth(2);
//hrealLSumScMtd -> SetMarkerStyle(20);
    //hrealLSumScMtd -> SetMarkerSize(1.2);
    hrealLSumScMtd -> SetLineColor(8);
    hLallSumBGScMtd -> SetMarkerStyle(21);
    hLallSumBGScMtd -> SetMarkerSize(1);
    hLallSumBGScMtd -> SetMarkerColor(2);
    hLallSumScMtd -> Draw();
    hLallSumBGScMtd -> Draw("p same");
    hrealLSumScMtd -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");
    lfin -> Draw("same");//<<<<<<<<<<<<<<

    cLambdaXiMassScMtd -> cd(4);
    nice_canv1(gPad);
    hrealXSumScMtd -> SetTitle("2#pi^{-} in Hades - anything (p) in FwDet");
    hrealXSumScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScMtd -> Draw("pE1");
    hrealX90ScMtd -> Draw("p same");
    l1 -> Draw("same");
    
    cimXsAmtdsc -> cd();
    nice_canv1(gPad);
    hrealXSumScMtd -> SetTitle("2#pi^{-} in Hades - anything (p) in FwDet");
    hrealXSumScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScMtd -> SetMarkerStyle(20);
    hrealXSumScMtd -> SetMarkerSize(.5);
    hrealXSumScMtd -> SetMarkerColor(4);
    hrealX90ScMtd -> SetMarkerStyle(20);
    hrealX90ScMtd -> SetMarkerSize(.5);
    hrealXSumScMtd -> Draw("pE1");
    hrealX90ScMtd -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassScMtd -> cd(5);
    nice_canv1(gPad);
    hrealXSumScMtd -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScMtd -> Draw("pE1");
    hrealX90ScMtd -> Draw("p same");
    l1 -> Draw("same");
    
    cimXsRmtdsc -> cd();
    nice_canv1(gPad);
    hrealXSumScMtd -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScMtd -> SetMarkerStyle(20);
    hrealXSumScMtd -> SetMarkerSize(.5);
    hrealXSumScMtd -> SetMarkerColor(4);
    hrealX90ScMtd -> SetMarkerStyle(20);
    hrealX90ScMtd -> SetMarkerSize(.5);
    hrealXSumScMtd -> Draw("pE1");
    hrealX90ScMtd -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassScMtd -> cd(6);
    nice_canv1(gPad);
    hXallSumBGScMtd -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hXallSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hXallSumBGScMtd -> Draw("p");
    hrealXSumPeakScMtd -> Draw("same");
    l1a -> Draw("same");
    
    cimXsBGmtdsc -> cd();
    nice_canv1(gPad);
    hXallSumBGScMtd -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hXallSumBGScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    hXallSumBGScMtd -> SetMarkerStyle(20);
    hXallSumBGScMtd -> SetMarkerSize(.5);
    hXallSumBGScMtd -> SetMarkerColor(2);
    hrealXSumPeakScMtd -> SetMarkerStyle(20);
    hrealXSumPeakScMtd -> SetMarkerSize(.5);
    hrealXSumPeakScMtd -> SetMarkerColor(8);
    hXallSumBGScMtd -> Draw("p");
    hrealXSumPeakScMtd -> Draw("same");
    l1a -> Draw("same");
    
    cimXMtdlVertlMlMtdxSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumScMtd -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass, MTD_X cuts");
    hrealXSumScMtd -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScMtd -> GetYaxis() -> SetTitle("counts*#sigma");
    //hrealXSumScMtd -> SetMarkerStyle(34);
    //hrealXSumScMtd -> SetMarkerSize(1.7);
    hrealXSumScMtd -> SetLineColor(4);
    hXallSumScMtd -> SetLineStyle(2);
    hXallSumScMtd -> SetLineWidth(2);
    //hrealXSumScMtd -> SetMarkerStyle(20);
    //hrealXSumScMtd -> SetMarkerSize(1.2);
    hrealXSumScMtd -> SetLineColor(8);
    hXallSumBGScMtd -> SetMarkerStyle(21);
    hXallSumBGScMtd -> SetMarkerSize(.5;
    hXallSumBGScMtd -> SetMarkerColor(2);
    hrealXSumScMtd -> Draw();
    hXallSumBGScMtd -> Draw("p same");
    hrealXSumScMtd -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");
    lfin -> Draw("same");//<<<<<<<<<<<<<<


    /* //MTD scan
    char mtdmax[24];

    for(int k = 0; k < 20; k++){
      cMTD_LscanSB -> cd(k+1);
      nice_canv1(gPad);
      hrealLSumPeakScMTDScan[k] -> SetTitle("Real #Lambda(1115) peak and BG");
      hrealLSumPeakScMTDScan[k] -> GetXaxis() -> SetTitle("invM [MeV]");
      hrealLSumPeakScMTDScan[k] -> GetYaxis() -> SetTitle("counts*#sigma");
      hLallSumBGScMTDScan[k] -> SetTitle("Real #Lambda(1115) peak and BG");
      hLallSumBGScMTDScan[k] -> GetXaxis() -> SetTitle("invM [MeV]");
      hLallSumBGScMTDScan[k] -> GetYaxis() -> SetTitle("counts*#sigma");
      if((hLallSumBGScMTDScan[k]->GetBinContent(hLallSumBGScMTDScan[k]->GetMaximumBin())) > (hrealLSumPeakScMTDScan[k]->GetBinContent(hrealLSumPeakScMTDScan[k]->GetMaximumBin()))){
	hLallSumBGScMTDScan[k] -> Draw();
	hrealLSumPeakScMTDScan[k] -> Draw("same");
      }else{
	hrealLSumPeakScMTDScan[k] -> Draw();
	hLallSumBGScMTDScan[k] -> Draw("same");
      }
      sprintf(mtdmax, "MTD < %d", (k*5)+5);
      TPaveText *ptmtd = new TPaveText(.25, .7, .4, .85, "NDC");
      ptmtd -> Clear();
      ptmtd -> SetFillColor(0);
      ptmtd -> SetBorderSize(0);
      ptmtd -> SetTextSize(0.07);
      ptmtd -> AddText(mtdmax);
      ptmtd -> Draw("same");

      cMTD_XscanSB -> cd(k+1);
      nice_canv1(gPad);
      hrealXSumPeakScMTDScan[k] -> SetTitle("Real #Xi^{-} peak and BG");
      hrealXSumPeakScMTDScan[k] -> GetXaxis() -> SetTitle("invM [MeV]");
      hrealXSumPeakScMTDScan[k] -> GetYaxis() -> SetTitle("counts*#sigma");
      hXallSumBGScMTDScan[k] -> SetTitle("Real #Xi^{-} peak and BG");
      hXallSumBGScMTDScan[k] -> GetXaxis() -> SetTitle("invM [MeV]");
      hXallSumBGScMTDScan[k] -> GetYaxis() -> SetTitle("counts*#sigma");
      if((hXallSumBGScMTDScan[k]->GetBinContent(hXallSumBGScMTDScan[k]->GetMaximumBin())) > (hrealXSumPeakScMTDScan[k]->GetBinContent(hrealXSumPeakScMTDScan[k]->GetMaximumBin()))){
	hXallSumBGScMTDScan[k] -> Draw();
	hrealXSumPeakScMTDScan[k] -> Draw("same");
      }else{
	hrealXSumPeakScMTDScan[k] -> Draw();
	hXallSumBGScMTDScan[k] -> Draw("same");
      }
      ptmtd -> Draw("same");
    }//end MTD scan
    */
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
    
    hrealLSumVert -> Fit(fit, "0");
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
      else
	hrealLSumPeakVert -> SetBinContent(j, hrealLSumVert -> GetBinContent(j));
    }
    hrealLSumScVert -> Fit(fit, "0");
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
      else hrealLSumPeakScVert -> SetBinContent(j, hrealLSumScVert -> GetBinContent(j));    
    }

    TH1F *hrealLSumPeakClVert = (TH1F*)hrealLSumPeakVert -> Clone();
    TH1F *hrealLSumPeakScClVert = (TH1F*)hrealLSumPeakScVert -> Clone();
    hLallSumBGVert -> Add(hLallSumVert, hrealLSumPeakClVert, 1, -1); 
    hLallSumBGScVert -> Add(hLallSumScVert, hrealLSumPeakScClVert, 1, -1); 

    hLallSumBGVert -> SetLineColor(kRed);
    hLallSumBGScVert -> SetLineColor(kRed);
    hrealLSumPeakVert -> SetLineColor(8);
    hrealLSumPeakScVert -> SetLineColor(8);

    cntSLVert = hrealLSumVert -> Integral(a,b);
    cntBLVert = hLallSumBGVert -> Integral(a,b);
    cntSLscVert = hrealLSumScVert -> Integral(a,b);
    cntBLscVert = hLallSumBGScVert -> Integral(a,b);

    /*    //VertzL scan
    int nLScVertScan[30];
    for(int k = -10; k < 20; k++){
      nLScVertScan[k+10] = hrealL1scVertScanSum[k+10] -> GetNbinsX();
      hrealLSumPeakScVertScan[k+10] = new TH1F("hRLsig", "hRLsig", nLScVertScan[k+10], minL, maxL);
      hLallSumBGScVertScan[k+10] = new TH1F("hLbg", "hLbg", nLScVertScan[k+10], minL, maxL);
      for(int j = 1; j <= nLScVertScan[k+10]; j++){
	massLSc = hrealL1scVertScanSum[k+10] -> GetBinLowEdge(j);
	if(massLSc < MassminL) continue;
	else if(massLSc > MassmaxL) break;
	else hrealLSumPeakScVertScan[k+10] -> SetBinContent(j, hrealL1scVertScanSum[k+10] -> GetBinContent(j));    
	}
      TH1F *hrealLSumPeakScClVertScan = hrealLSumPeakScVertScan[k+10] -> Clone();
      hLallSumBGScVertScan[k+10] -> Add(hLall1scVertScanSum[k+10], hrealLSumPeakScClVertScan, 1, -1); 
      hLallSumBGScVertScan[k+10] -> SetLineColor(kRed);
      hrealLSumPeakScVertScan[k+10] -> SetLineColor(8);
    }
    //end VertzL scan
    */
    //SB
    for(int j = 1; j <= nLVert; j++){
      if(hrealLSumPeakVert -> GetBinContent(j)){
	kLVert++;
	s_bg_vLVert[kLVert] = (hrealLSumPeakVert -> GetBinContent(j))/(hLallSumBGVert -> GetBinContent(j));
	binLVert[kLVert] = (hrealLSumPeakVert -> GetBinLowEdge(j)) + (hrealLSumPeakVert -> GetBinWidth(j));
      }
    }
    for(int j = 1; j <= nLScVert; j++){
      if(hrealLSumPeakScVert -> GetBinContent(j)){
	kLScVert++;
	s_bg_vLScVert[kLScVert] = (hrealLSumPeakScVert -> GetBinContent(j))/(hLallSumBGScVert -> GetBinContent(j));
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

    hrealXSumVert-> Fit(fit, "0");
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
      else hrealXSumPeakVert -> SetBinContent(j, hrealXSumVert -> GetBinContent(j));
    }
    hrealXSumScVert-> Fit(fit, "0");
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
      else hrealXSumPeakScVert -> SetBinContent(j, hrealXSumScVert -> GetBinContent(j));
    }

    TH1F *hrealXSumPeakClVert = (TH1F*)hrealXSumPeakVert -> Clone();
    TH1F *hrealXSumPeakScClVert = (TH1F*)hrealXSumPeakScVert -> Clone();
    //    hXallSumBGVert -> Add(hXallSumVert, hrealXSumPeakClVert, 1, -1); 
    //    hXallSumBGScVert -> Add(hXallSumScVert, hrealXSumPeakScClVert, 1, -1);
    hXallSumBGVert -> Add(hrealXSumVert, hrealXSumPeakClVert, 1, -1); 
    hXallSumBGScVert -> Add(hrealXSumScVert, hrealXSumPeakScClVert, 1, -1); 

    hXallSumBGVert -> SetLineColor(kRed);
    hXallSumBGScVert -> SetLineColor(kRed);
    hrealXSumPeakVert -> SetLineColor(8);
    hrealXSumPeakScVert -> SetLineColor(8);

    cntSXVert = hrealXSumVert -> Integral(a,b);
    cntBXVert = hXallSumBGVert -> Integral(a,b);
    cntSXscVert = hrealXSumScVert -> Integral(a,b);
    cntBXscVert = hXallSumBGScVert -> Integral(a,b);


    /*  //VertzX scan
    int nXScVertScan[30];
    for(int k = -10; k < 20; k++){
      nXScVertScan[k+10] = hrealX1scVertScanSum[k+10] -> GetNbinsX();
      hrealXSumPeakScVertScan[k+10] = new TH1F("hRXsig", "hRXsig", nXScVertScan[k+10], minX, maxX);
      hXallSumBGScVertScan[k+10] = new TH1F("hXbg", "hXbg", nXScVertScan[k+10], minX, maxX);
      for(int j = 1; j <= nXScVertScan[k+10]; j++){
	massXSc = hrealX1scVertScanSum[k+10] -> GetBinLowEdge(j);
	if(massXSc < MassminX) continue;
	else if(massXSc > MassmaxX) break;
	else hrealXSumPeakScVertScan[k+10] -> SetBinContent(j, hrealX1scVertScanSum[k+10] -> GetBinContent(j));    
      }

      TH1F *hrealXSumPeakScClVertScan = hrealXSumPeakScVertScan[k+10] -> Clone();
      hXallSumBGScVertScan[k+10] -> Add(hXall1scVertScanSum[k+10], hrealXSumPeakScClVertScan, 1, -1); 

      hXallSumBGScVertScan[k+10] -> SetLineColor(kRed);
      hrealXSumPeakScVertScan[k+10] -> SetLineColor(8);
    }
    //end VertzX scan
    */

    //SB
    for(int j = 1; j <= nXVert; j++){
      if(hrealXSumPeakVert -> GetBinContent(j)){
	kXVert++;
	s_bg_vXVert[kXVert] = (hrealXSumPeakVert -> GetBinContent(j))/(hXallSumBGVert -> GetBinContent(j));
	binXVert[kXVert] = (hrealXSumPeakVert -> GetBinLowEdge(j)) + (hrealXSumPeakVert -> GetBinWidth(j));
	// cout << "kL:" << kL << " s_bg_vL[kL]:" << s_bg_vL[kL] << " S:" << hrealLSumPeak -> GetBinContent(j) << " B:" << hLallSumBG -> GetBinContent(j)  << endl;
      }
    }
    for(int j = 1; j <= nXScVert; j++){
      if(hrealXSumPeakScVert -> GetBinContent(j)){
	kXScVert++;
	s_bg_vXScVert[kXScVert] = (hrealXSumPeakScVert -> GetBinContent(j))/(hXallSumBGScVert -> GetBinContent(j));
	binXScVert[kXScVert] = (hrealXSumPeakScVert -> GetBinLowEdge(j)) + (hrealXSumPeakScVert -> GetBinWidth(j));
	// cout << "kL:" << kL << " s_bg_vL[kL]:" << s_bg_vL[kL] << " S:" << hrealLSumPeak -> GetBinContent(j) << " B:" << hLallSumBG -> GetBinContent(j)  << endl;
      }
    }


    /*  l1Vert -> AddEntry(hLallSumVert, "sum all channels", "L");
    l1Vert -> AddEntry(hLall90Vert, "#Xi^{-}2K^{+}p", "L");
    l1Vert -> AddEntry(hLallSumBGVert, "BG", "L");
    l1Vert -> AddEntry(hrealLSumPeakVert, "signal", "L");
    */

    //invM no scaling MTD, Vert
    /* TCanvas *cimLnsAvert = new TCanvas("cimLnsAvert", "cimLnsAvert");
    TCanvas *cimLnsRvert = new TCanvas("cimLnsRvert", "cimLnsRvert");
    TCanvas *cimLnsBGvert = new TCanvas("cimLnsBGvert", "cimLnsBGvert");
    TCanvas *cimXnsAvert = new TCanvas("cimXnsAvert", "cimXnsAvert");
    TCanvas *cimXnsRvert = new TCanvas("cimXnsRvert", "cimXnsRvert");
    TCanvas *cimXnsBGvert = new TCanvas("cimXnsBGvert", "cimXnsBGvert");
    */
    cLambdaXiMassVert -> cd(1);
    nice_canv1(gPad);
    hLallSumVert -> SetTitle("#pi^{-} in Hades + anything (p) in FwDet");
    hLallSumVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumVert -> GetYaxis() -> SetTitle("counts");
    hLallSumVert -> Draw();
    hLall90Vert -> Draw("same");
    l1 -> Draw("same");
    
    /*cimLnsAvert -> cd();
    nice_canv1(gPad);
    hLallSumVert -> SetTitle("#pi^{-} in Hades + anything (p) in FwDet");
    hLallSumVert -> GetXaxis() -> SetTitle("invM [MeV]");
    hLallSumVert -> GetYaxis() -> SetTitle("counts");
    hLallSumVert -> Draw();
    hLall90Vert -> Draw("same");
    l1 -> Draw("same");
    */
    cLambdaXiMassVert -> cd(2);
    nice_canv1(gPad);
    hrealLSumVert -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealLSumVert -> GetYaxis() -> SetTitle("counts");
    hrealLSumVert -> Draw();
    hrealL90Vert -> Draw("same");
    l1 -> Draw("same");
    /*
    cimLnsRvert -> cd();
    nice_canv1(gPad);
    hrealLSumVert -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumVert -> GetXaxis() -> SetTitle("invM [MeV]");
    hrealLSumVert -> GetYaxis() -> SetTitle("counts");
    hrealLSumVert -> Draw();
    hrealL90Vert -> Draw("same");
    */
    cLambdaXiMassVert -> cd(3);
    nice_canv1(gPad);
    hLallSumBGVert -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumBGVert -> GetYaxis() -> SetTitle("counts");
    hrealLSumPeakVert -> Draw();
    hLallSumBGVert -> Draw("same");
    l1a -> Draw("same");
    /*
    cimLnsBGvert -> cd();
    nice_canv1(gPad);
    hLallSumBGVert -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGVert -> GetXaxis() -> SetTitle("invM [MeV]");
    hLallSumBGVert -> GetYaxis() -> SetTitle("counts");
    hrealLSumPeakVert -> Draw();
    hLallSumBGVert -> Draw("same");
    l1a -> Draw("same");
    */
    cLambdaXiMassVert -> cd(4);
    nice_canv1(gPad);
    hrealXSumVert -> SetTitle("2#pi^{-} in Hades + anything (p) in FwDet");
    hrealXSumVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumVert -> GetYaxis() -> SetTitle("counts");
    hrealXSumVert -> Draw();
    hrealX90Vert -> Draw("same");
    l1 -> Draw("same");
    /*
    cimXnsAvert -> cd();
    nice_canv1(gPad);
    hXallSumVert -> SetTitle("2#pi^{-} in Hades + anything (p) in FwDet");
    hXallSumVert -> GetXaxis() -> SetTitle("invM [MeV]");
    hXallSumVert -> GetYaxis() -> SetTitle("counts");
    hXallSumVert -> Draw();
    hXall90Vert -> Draw("same");
    l1 -> Draw("same");
    */
    cLambdaXiMassVert -> cd(5);
    nice_canv1(gPad);
    hrealXSumVert -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumVert -> GetYaxis() -> SetTitle("counts");
    hrealXSumVert -> Draw();
    hrealX90Vert -> Draw("same");
    l1 -> Draw("same");
    /*
    cimXnsRvert -> cd();
    nice_canv1(gPad);
    hrealXSumVert -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumVert -> GetXaxis() -> SetTitle("invM [MeV]");
    hrealXSumVert -> GetYaxis() -> SetTitle("counts");
    hrealXSumVert -> Draw();
    hrealX90Vert -> Draw("same");
    */
    cLambdaXiMassVert -> cd(6);
    nice_canv1(gPad);
    hXallSumBGVert -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hXallSumBGVert -> GetYaxis() -> SetTitle("counts");
    hrealXSumPeakVert -> Draw();
    hXallSumBGVert -> Draw("same");
    l1a -> Draw("same");
    /*
    cimXnsBGvert -> cd();
    nice_canv1(gPad);
    hXallSumBGVert -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGVert -> GetXaxis() -> SetTitle("invM [MeV]");
    hXallSumBGVert -> GetYaxis() -> SetTitle("counts");
    hrealXSumPeakVert -> Draw();
    hXallSumBGVert -> Draw("same");
    l1a -> Draw("same");
    */

    //invM scaling MTD, Vert
    TCanvas *cimLsAvertsc = new TCanvas("cimLsAvertsc", "cimLsAvertsc");
    TCanvas *cimLsRvertsc = new TCanvas("cimLsRvertsc", "cimLsRvertsc");
    TCanvas *cimLsBGvertsc = new TCanvas("cimLsBGvertsc", "cimLsBGvertsc");
    TCanvas *cimXsAvertsc = new TCanvas("cimXsAvertsc", "cimXsAvertsc");
    TCanvas *cimXsRvertsc = new TCanvas("cimXsRvertsc", "cimXsRvertsc");
    TCanvas *cimXsBGvertsc = new TCanvas("cimXsBGvertsc", "cimXsBGvertsc");
    
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
    hLallSumScVert -> SetTitle("#pi^{-} in Hades - anything (p) in FwDet");
    hLallSumScVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScVert -> Draw("pE1");
    hLall90ScVert -> Draw("p same");
    l1 -> Draw("same");
   
    cimLsAvertsc -> cd();
    nice_canv1(gPad);
    hLallSumScVert -> SetTitle("#pi^{-} in Hades - anything (p) in FwDet");
    hLallSumScVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumScVert -> SetMarkerStyle(20);
    hLallSumScVert -> SetMarkerSize(.5);
    hLallSumScVert -> SetMarkerColor(4);
    hLall90ScVert -> SetMarkerStyle(20);
    hLall90ScVert -> SetMarkerSize(.5);
    hLallSumScVert -> Draw("pE1");
    hLall90ScVert -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassScVert -> cd(2);
    nice_canv1(gPad);
    hrealLSumScVert -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumScVert -> GetXaxis() -> SetTitle("M_{#pi_{-}} [MeV]");
    hrealLSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumScVert -> Draw();
    hrealL90ScVert -> Draw("p same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");
    l1 -> Draw("same");
    
    cimLsRvertsc -> cd();
    nice_canv1(gPad);
    hrealLSumScVert -> SetTitle("Real #Lambda: #pi^{-} and p from #Lambda(1115)");
    hrealLSumScVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealLSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumScVert -> SetMarkerStyle(20);
    hrealLSumScVert -> SetMarkerSize(.5);
    hrealLSumScVert -> SetMarkerColor(8);
    hrealL90ScVert -> SetMarkerStyle(20);
    hrealL90ScVert -> SetMarkerSize(.5);
    hrealLSumScVert -> Draw("p E1");
    hrealL90ScVert -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassScVert -> cd(3);
    nice_canv1(gPad);
    hrealLSumPeakScVert -> SetTitle("Real #Lambda peak and BG");
    hrealLSumPeakScVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealLSumPeakScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hLallSumBGScVert -> Draw("p");
    hrealLSumPeakScVert -> Draw("pE1 same");
    l1a -> Draw("same");
    
    cimLsBGvertsc -> cd();
    nice_canv1(gPad);
    hLallSumBGScVert -> SetTitle("Real #Lambda peak and BG");
    hLallSumBGScVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumBGScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealLSumPeakScVert -> SetMarkerStyle(20);
    hrealLSumPeakScVert -> SetMarkerSize(.5);
    hrealLSumPeakScVert -> SetMarkerColor(8);
    hLallSumBGScVert -> SetMarkerStyle(20);
    hLallSumBGScVert -> SetMarkerSize(.5);
    hLallSumBGScVert -> SetMarkerColor(2);
    hLallSumBGScVert -> Draw("p");
    hrealLSumPeakScVert -> Draw("pE1 same");
    l1a -> Draw("same");
    
    cimLMtdlVertlSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hLallSumScVert -> SetTitle("#Lambda reconstruction, MTD_L, VERTz_L cuts");
    hLallSumScVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLallSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    //hLallSumScVert -> SetMarkerStyle(34);
    //hLallSumScVert -> SetMarkerSize(1.7);
    hLallSumScVert -> SetLineColor(4);
    hLallSumScVert -> SetLineStyle(2);
    hLallSumScVert -> SetLineWidth(2);
    //hrealLSumScVert -> SetMarkerStyle(20);
    //hrealLSumScVert -> SetMarkerSize(1.2);
    hrealLSumScVert -> SetLineColor(8);
    hrealLSumScVert -> SetLineStyle(10);
    hLallSumBGScVert -> SetMarkerStyle(21);
    hLallSumBGScVert -> SetMarkerSize(.5);
    hLallSumBGScVert -> SetMarkerColor(2);
    hLallSumScVert -> Draw();
    hLallSumBGScVert -> Draw("p same");
    hrealLSumScVert -> Draw("same");
    massL_min -> Draw("same");
    massL_max -> Draw("same");
    lfin -> Draw("same");//<<<<<<<<<<<<<<

    cLambdaXiMassScVert -> cd(4);
    nice_canv1(gPad);
    hrealXSumScVert -> SetTitle("2#pi^{-} in Hades - anything (p) in FwDet");
    hrealXSumScVert -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hrealXSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScVert -> Draw("pE1");
    hrealX90ScVert -> Draw("p same");
    l1 -> Draw("same");
    
    cimXsAvertsc -> cd();
    nice_canv1(gPad);
    hrealXSumScVert -> SetTitle("2#pi^{-} in Hades - anything (p) in FwDet");
    hrealXSumScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScVert -> SetMarkerStyle(20);
    hrealXSumScVert -> SetMarkerSize(.5);
    hrealXSumScVert -> SetMarkerColor(4);
    hrealX90ScVert -> SetMarkerStyle(20);
    hrealX90ScVert -> SetMarkerSize(.5);
    hrealXSumScVert -> Draw("pE1");
    hrealX90ScVert -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassScVert -> cd(5);
    nice_canv1(gPad);
    hrealXSumScVert -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScVert -> Draw("pE1");
    hrealX90ScVert -> Draw("p same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");
    l1 -> Draw("same");
    
    cimXsRvertsc-> cd();
    nice_canv1(gPad);
    hrealXSumScVert -> SetTitle("Real #Xi: #pi^{-} and p from #Lambda(1115) + #pi^{-} from #Xi");
    hrealXSumScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hrealXSumScVert -> SetMarkerStyle(20);
    hrealXSumScVert -> SetMarkerSize(.5);
    hrealXSumScVert -> SetMarkerColor(4);
    hrealX90ScVert -> SetMarkerStyle(20);
    hrealX90ScVert -> SetMarkerSize(.5);
    hrealXSumScVert -> Draw("pE1");
    hrealX90ScVert -> Draw("p same");
    l1 -> Draw("same");
    
    cLambdaXiMassScVert -> cd(6);
    nice_canv1(gPad);
    hrealXSumPeakScVert -> SetTitle("Real #Xi^{-} peak and BG");
    hrealXSumPeakScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumPeakScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hXallSumBGScVert -> Draw("p");
    hrealXSumPeakScVert -> Draw("pE1 same");
    l1a -> Draw("same");
    
    cimXsBGvertsc -> cd();
    nice_canv1(gPad);
    hXallSumBGScVert -> SetTitle("Real #Xi^{-} peak and BG");
    hXallSumBGScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hXallSumBGScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    hXallSumBGScVert -> SetMarkerStyle(20);
    hXallSumBGScVert -> SetMarkerSize(.5);
    hXallSumBGScVert -> SetMarkerColor(2);
    hrealXSumPeakScVert -> SetMarkerStyle(20);
    hrealXSumPeakScVert -> SetMarkerSize(.5);
    hrealXSumPeakScVert -> SetMarkerColor(8);
    hXallSumBGScVert -> Draw("pE1");
    hrealXSumPeakScVert -> Draw("p same");
    l1a -> Draw("same");

    cimXMtdlVertlMlMtdxVertxSc -> cd();//<<<<<<<<<<<<<<
    nice_canv1(gPad);
    hrealXSumScVert -> SetTitle("#Xi reconstruction, MTD_L, VERTz_L, Lmass, MTD_X, VERTz_X");
    hrealXSumScVert -> GetXaxis() -> SetTitle("M_{#Lambda#pi_{-}} [MeV]");
    hrealXSumScVert -> GetYaxis() -> SetTitle("counts*#sigma");
    //hrealXSumScVert -> SetMarkerStyle(34);
    //hrealXSumScVert -> SetMarkerSize(1.7);
    hrealXSumScVert -> SetLineColor(4);
    hXallSumScVert -> SetLineStyle(2);
    hXallSumScVert -> SetLineWidth(2);
     //hrealXSumScVert -> SetMarkerStyle(20);
    //hrealXSumScVert -> SetMarkerSize(1.2);
    hrealXSumScVert -> SetLineColor(8);
    hXallSumBGScVert -> SetMarkerStyle(21);
    hXallSumBGScVert -> SetMarkerSize(.5);
    hXallSumBGScVert -> SetMarkerColor(2);
    hrealXSumScVert -> Draw();
    hXallSumBGScVert -> Draw("p same");
    hrealXSumScVert -> Draw("same");
    massX_min -> Draw("same");
    massX_max -> Draw("same");
    lfin -> Draw("same");//<<<<<<<<<<<<<<


    //
   
    //
    /* cVertZ_LscanAll -> cd(1);
    nice_canv1(gPad);
    lChan -> Draw("same");
    cVertZ_LscanReal -> cd(1);
    nice_canv1(gPad);
    lChan -> Draw("same");
    */
    char vertzmin[24];
    /*
    for(int k = -10; k < 20; k++){
      if(k < 5) cVertZ_LscanSB1 -> cd(k+11);
      else cVertZ_LscanSB2 -> cd(k-4);
      nice_canv1(gPad);
      hrealLSumPeakScVertScan[k+10] -> SetTitle("Real #Lambda(1115) peak and BG");
      hrealLSumPeakScVertScan[k+10] -> GetXaxis() -> SetTitle("invM [MeV]");
      hrealLSumPeakScVertScan[k+10] -> GetYaxis() -> SetTitle("counts*#sigma");
      hLallSumBGScVertScan[k+10] -> SetTitle("Real #Lambda(1115) peak and BG");
      hLallSumBGScVertScan[k+10] -> GetXaxis() -> SetTitle("invM [MeV]");
      hLallSumBGScVertScan[k+10] -> GetYaxis() -> SetTitle("counts*#sigma");
      if((hLallSumBGScVertScan[k+10]->GetBinContent(hLallSumBGScVertScan[k+10]->GetMaximumBin())) > (hrealLSumPeakScVertScan[k+10]->GetBinContent(hrealLSumPeakScVertScan[k+10]->GetMaximumBin()))){
	hLallSumBGScVertScan[k+10] -> Draw();
	hrealLSumPeakScVertScan[k+10] -> Draw("same");
      }else{
	hrealLSumPeakScVertScan[k+10] -> Draw();
	hLallSumBGScVertScan[k+10] -> Draw("same");
      }
      sprintf(vertzmin, "vertz > %d", k*10);
      TPaveText *ptvert = new TPaveText(.25, .7, .4, .85, "NDC");
      ptvert -> Clear();
      ptvert -> SetFillColor(0);
      ptvert -> SetBorderSize(0);
      ptvert -> SetTextSize(0.07);
      ptvert -> AddText(vertzmin);
      ptvert -> Draw("same");

      if(k < 5) cVertZ_XscanSB1 -> cd(k+11);
      else cVertZ_XscanSB2 -> cd(k-4);
      nice_canv1(gPad);
      hrealXSumPeakScVertScan[k+10] -> SetTitle("Real #Xi^{-} peak and BG");
      hrealXSumPeakScVertScan[k+10] -> GetXaxis() -> SetTitle("invM [MeV]");
      hrealXSumPeakScVertScan[k+10] -> GetYaxis() -> SetTitle("counts*#sigma");
      hXallSumBGScVertScan[k+10] -> SetTitle("Real #Xi^{-} peak and BG");
      hXallSumBGScVertScan[k+10] -> GetXaxis() -> SetTitle("invM [MeV]");
      hXallSumBGScVertScan[k+10] -> GetYaxis() -> SetTitle("counts*#sigma");
      if((hXallSumBGScVertScan[k+10]->GetBinContent(hXallSumBGScVertScan[k+10]->GetMaximumBin())) > (hrealXSumPeakScVertScan[k+10]->GetBinContent(hrealXSumPeakScVertScan[k+10]->GetMaximumBin()))){
	hXallSumBGScVertScan[k+10] -> Draw();
	hrealXSumPeakScVertScan[k+10] -> Draw("same");
      }else{
	hrealXSumPeakScVertScan[k+10] -> Draw();
	hXallSumBGScVertScan[k+10] -> Draw("same");
      }
      ptvert -> Draw("same");
    }
    */
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
    /*
    //Vert diff
    cVertDiff_allCh -> cd(1);
    lChan -> Draw("same");
    */
    //end Vert diff
    
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
    //VERTz in [5;300]????????????????
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

    /* //MTD scan
    double SgnLMTDscScan[20];
    double SgnXMTDscScan [20];
    double cntSLscMTDscan, cntBLscMTDscan, cntSXscMTDscan, cntBXscMTDscan;
    double mtdMax[20]; 
    double lostSigMtdL[20], lostSigMtdX[20]; 

    for(int k = 0; k < 20; k++){
      hrealLSumPeakScMTDScan[k] -> Fit(fit, "0");
      center_fit = fit -> GetParameter(1);
      sigma_fit = fit -> GetParameter(2);
      m3sigma = center_fit - 3*sigma_fit;
      p3sigma = center_fit + 3*sigma_fit;
      a = hrealLSumPeakScMTDScan[k] -> GetXaxis() -> FindBin(m3sigma);
      b = hrealLSumPeakScMTDScan[k] -> GetXaxis() -> FindBin(p3sigma);
      cntSLscMTDscan = hrealLSumPeakScMTDScan[k] -> Integral(a,b);
      cntBLscMTDscan = hLallSumBGScMTDScan[k] -> Integral(a,b);

      lostSigMtdL[k] = cntSLscMTDscan/cntSLsc;

      hrealXSumPeakScMTDScan[k] -> Fit(fit, "0");
      center_fit = fit -> GetParameter(1);
      sigma_fit = fit -> GetParameter(2);
      m3sigma = center_fit - 3*sigma_fit;
      p3sigma = center_fit + 3*sigma_fit;
      a = hrealXSumPeakScMTDScan[k] -> GetXaxis() -> FindBin(m3sigma);
      b = hrealXSumPeakScMTDScan[k] -> GetXaxis() -> FindBin(p3sigma);
      cntSXscMTDscan = hrealXSumPeakScMTDScan[k] -> Integral(a,b);
      cntBXscMTDscan = hXallSumBGScMTDScan[k] -> Integral(a,b);

      lostSigMtdX[k] = cntSXscMTDscan/cntSXsc;

      SgnLMTDscScan[k] = cntSLscMTDscan/TMath::Sqrt(cntBLscMTDscan+cntSLscMTDscan);
      SgnXMTDscScan[k] = cntSXscMTDscan/TMath::Sqrt(cntBXscMTDscan+cntSXscMTDscan);

      mtdMax[k] = (k*5)+5;
      cout << "k:" << k << " SgnLMTDscScan:" << SgnLMTDscScan[k] << " cntSLscMTDscan:" << cntSLscMTDscan << " cntBKscMTDscan:" << cntBLscMTDscan << endl;
      cout << "k:" << k << " SgnXMTDscScan:" << SgnXMTDscScan[k] << " cntSXscMTDscan:" << cntSXscMTDscan << " cntBXscMTDscan:" << cntBXscMTDscan << endl;
    }

    ymax = 5500;
    TLine *lim_min = new TLine(distcut_minL, 0, distcut_minL, ymax);

    TCanvas *cSgnMTDL = new TCanvas("cSgnMTDL", "cSgnMTDL");
    cSgnMTDL -> cd();
    nice_canv1(gPad);
    TGraph *sgnMTDLscan = new TGraph(20, mtdMax, SgnLMTDscScan);
    sgnMTDLscan -> SetName("sgnMTDLscan");
    sgnMTDLscan -> SetTitle("Significance for different MTD_L");
    sgnMTDLscan -> GetXaxis() -> SetTitle("max MTD_L [mm]");
    sgnMTDLscan -> GetYaxis() -> SetTitle("#alpha");
    sgnMTDLscan -> GetYaxis() -> SetRangeUser(0,ymax);
    sgnMTDLscan -> SetMarkerStyle(20);
    sgnMTDLscan -> Draw("ap");
    lim_min -> Draw("same");
    *//*TGaxis *axis1 = new TGaxis(110,0,110,.95,0,1);
    axis1 -> SetName("S_{MTD}/S_{nc}");
    axis1 -> Draw("same");
    TGraph *glostSigMTDL = new TGraph(20, mtdMax, lostSigMtdL);
    glostSigMTDL -> GetXaxis() -> SetTitle("max MTD_L [mm]");
    //glostSigMTDL -> GetYaxis() -> SetTitle("S_{MTD}/S_{nc}");
    glostSigMTDL -> SetMarkerStyle(31);
    glostSigMTDL -> SetMarkerColor(8);
    glostSigMTDL -> Draw("same p");
    */
    /*
    ymax = 1000;
    TLine *lim_min = new TLine(distcut_minX, 0, distcut_minX, ymax);
    
    TCanvas *cSgnMTDX = new TCanvas("cSgnMTDX", "cSgnMTDX");
    cSgnMTDX -> cd();
    nice_canv1(gPad);
    TGraph *sgnMTDXscan = new TGraph(20, mtdMax, SgnXMTDscScan);
    sgnMTDXscan -> SetName("sgnMTDXscan");
    sgnMTDXscan -> SetTitle("Significance for different MTD_X");
    sgnMTDXscan -> GetXaxis() -> SetTitle("max MTD_X [mm]");
    sgnMTDXscan -> GetYaxis() -> SetTitle("#alpha");
    sgnMTDXscan -> GetYaxis() -> SetRangeUser(0,ymax);
    sgnMTDXscan -> SetMarkerStyle(20);
    sgnMTDXscan -> Draw("ap");
    lim_min -> Draw("same");

    //end MTD scan
    *//*
    //VERTz scan
    double SgnLVertscScan[30];
    double SgnXVertscScan [30];
    double cntSLscVertscan, cntBLscVertscan, cntSXscVertscan, cntBXscVertscan;
    double vertzMin[30]; 

    for(int k = -10; k < 20; k++){
      hrealLSumPeakScVertScan[k+10] -> Fit(fit, "0");
      center_fit = fit -> GetParameter(1);
      sigma_fit = fit -> GetParameter(2);
      m3sigma = center_fit - 3*sigma_fit;
      p3sigma = center_fit + 3*sigma_fit;
      a = hrealLSumPeakScVertScan[k+10] -> GetXaxis() -> FindBin(m3sigma);
      b = hrealLSumPeakScVertScan[k+10] -> GetXaxis() -> FindBin(p3sigma);
      //cntSLscVertscan = hrealLSumPeakScVertScan[k+10] -> Integral(a,b);
      //cntBLscVertscan = hrealLSumPeakScVertScan[k+10] -> Integral(a,b);
      cntSLscVertscan = hrealLSumPeakScVertScan[k+10] -> Integral(a,b);
      cntBLscVertscan = hLallSumBGScVertScan[k+10] -> Integral(a,b);

      hrealXSumPeakScVertScan[k+10] -> Fit(fit, "0");
      center_fit = fit -> GetParameter(1);
      sigma_fit = fit -> GetParameter(2);
      m3sigma = center_fit - 3*sigma_fit;
      p3sigma = center_fit + 3*sigma_fit;
      a = hrealXSumPeakScVertScan[k+10] -> GetXaxis() -> FindBin(m3sigma);
      b = hrealXSumPeakScVertScan[k+10] -> GetXaxis() -> FindBin(p3sigma);
      // cntSXscVertscan = hrealXSumPeakScVertScan[k+10] -> Integral(a,b);
      //cntBXscVertscan = hrealXSumPeakScVertScan[k+10] -> Integral(a,b);
      cntSXscVertscan = hrealXSumPeakScVertScan[k+10] -> Integral(a,b);
      cntBXscVertscan = hXallSumBGScVertScan[k+10] -> Integral(a,b);

      SgnLVertscScan[k+10] = cntSLscVertscan/TMath::Sqrt(cntBLscVertscan+cntSLscVertscan);
      SgnXVertscScan[k+10] = cntSXscVertscan/TMath::Sqrt(cntBXscVertscan+cntSXscVertscan);

      vertzMin[k+10] = k*10;
    }

    ymax = 8500;
    TLine *lim_min = new TLine(zlim_minL, 0, zlim_minL, ymax);
    TLine *lim_max = new TLine(zlim_max, 0, zlim_max, ymax);
    
    TCanvas *cSgnVertL = new TCanvas("cSgnVertL", "cSgnVertL");
    cSgnVertL -> cd();
    nice_canv1(gPad);
    TGraph *sgnVertzLscan = new TGraph(30, vertzMin, SgnLVertscScan);
    sgnVertzLscan -> SetName("sgnVertzLscan");
    sgnVertzLscan -> SetTitle("Significance for different VERTz_L");
    sgnVertzLscan -> GetXaxis() -> SetTitle("min VERTz_L [mm]");
    sgnVertzLscan -> GetYaxis() -> SetTitle("#alpha");
    sgnVertzLscan -> GetYaxis() -> SetRangeUser(0,ymax);
    sgnVertzLscan -> SetMarkerStyle(20);
    sgnVertzLscan -> Draw("ap");
    lim_max -> Draw("same");
    lim_min -> Draw("same");

    ymax = 1000;
    TLine *lim_min = new TLine(zlim_minX, 0, zlim_minX, ymax);
    TLine *lim_max = new TLine(zlim_max, 0, zlim_max, ymax);
   
    TCanvas *cSgnVertX = new TCanvas("cSgnVertX", "cSgnVertX");
    cSgnVertX -> cd();
    nice_canv1(gPad);
    TGraph *sgnVertzXscan = new TGraph(30, vertzMin, SgnXVertscScan);
    sgnVertzXscan -> SetName("sgnVertzXscan");
    sgnVertzXscan -> SetTitle("Significance for different VERTz_X");
    sgnVertzXscan -> GetXaxis() -> SetTitle("min VERTz_X [mm]");
    sgnVertzXscan -> GetYaxis() -> SetTitle("#alpha");
    sgnVertzXscan -> GetYaxis() -> SetRangeUser(0,ymax);
    sgnVertzXscan -> SetMarkerStyle(20);
    sgnVertzXscan -> Draw("ap");
    lim_max -> Draw("same");
    lim_min -> Draw("same");

    //end VERTz scan
    */
    //effi
    int nall = 500000; //n evt*100 -> [%]
    double brLxchn = 0.64*5; //BR for Lambda->p pim * number of simulated channels with real Lambda1115
    printf("Effi rec.:\nL: MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f\nX: MTD: %f, MTDsc: %f, Vert: %f, Vertsc: %f\n", cntSLMtd/nall/brLxchn, cntSLscMtd/nall/brLxchn, cntSLVert/nall/brLxchn, cntSLscVert/nall/brLxchn, cntSXMtd/nall, cntSXscMtd/nall, cntSXVert/nall, cntSXscVert/nall);

    //3sigma Xi
    cout << "-3s:" << m3sigma << " +3s:" << p3sigma << " a:" << a << " b:" << b << endl;
    //Xi counts:
    cout << "Xi(MTD_L, Vert_L, Lmass, MTD_X, no_sc):" << cntSXMtd << endl;

    TCanvas *cL_nocuts_sc = new TCanvas("cL_nocuts_sc", "Reconstruction of #Lambda(1115) (no cuts, #sigma sc.)", 1000, 600);
    cL_nocuts_sc -> cd();
    nice_canv1(gPad);
    hLmass_sc -> Add(hLallSumSc);
    hLmass_sc -> Draw("nostack");
    hLmass_sc -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
    hLmass_sc -> GetYaxis() -> SetTitle("counts*#sigma");
    hLmass_sc -> GetYaxis() -> SetRangeUser(0, 100000000);
    //hLallSumSc -> Draw("same");
    cL_nocuts_sc -> Modified();
    lChan -> AddEntry(hLallSumSc, "sum of all channels");
    lChan -> Draw("same");

    TCanvas *cL_rec_sc = new TCanvas("cL_rec_sc", "Reconstruction of #Lambda(1115) (all cuts, #sigma sc.)", 1000, 600);
    cL_rec_sc -> cd();
    nice_canv1(gPad);
    hLmass_sc_rec -> Add(hLallSumScVert);//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    hLmass_sc_rec -> Draw("nostack");
    hLmass_sc_rec -> GetXaxis() -> SetTitle("M_{p#pi_{-}} [MeV]");
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

        
    TFile *f = new TFile("./out_ana/out_anaBkgd_all5.root", "RECREATE");
    cLambdaXiMass -> Write();
    cLambdaXiMassSc -> Write();
    // cSBL -> Write();
    // cSBLSc -> Write();
    // cSBX -> Write();
    // cSBXSc -> Write();
    cLambdaXiMassMtd -> Write();
    cLambdaXiMassScMtd -> Write();
    cLambdaXiMassVert -> Write();
    cLambdaXiMassScVert -> Write();
    // cSBLMtd -> Write();
    // cSBLScMtd -> Write();
    // cSBXMtd -> Write();
    // cSBXScMtd -> Write();
    cMTDL -> Write();
    cMTDX -> Write();
    cVERTL -> Write();
    cVERTX -> Write();
    cVERTL1 -> Write();
    cVERTX1 -> Write();
    cVertZ_L -> Write();
    cVertZ_X -> Write();
   // cVertDiff_allCh -> Write();
    //cMTD_LscanAll -> Write();
    //cMTD_LscanReal -> Write();
    //    cMTD_LscanSB -> Write();
    //    cMTD_XscanSB -> Write();
    //cVertZ_LscanAll1 -> Write();
    //cVertZ_LscanReal1 -> Write();
    //cVertZ_LscanSB1 -> Write();
    //cVertZ_XscanSB1 -> Write();
    //cVertZ_LscanAll2 -> Write();
    //cVertZ_LscanReal2 -> Write();
    //cVertZ_LscanSB2 -> Write();
    //cVertZ_XscanSB2 -> Write();
    //    cSgnMTDL -> Write();
    //    cSgnMTDX -> Write();
    //    cSgnVertL -> Write();
    //    cSgnVertX -> Write();

    //    sgnMTDLscan -> Write();
    //    sgnMTDXscan -> Write();
    //    sgnVertzLscan -> Write();
    //    sgnVertzXscan -> Write();
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
