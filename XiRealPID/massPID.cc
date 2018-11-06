TH1F* massPID(TH1F *hM){
    TH1F *hMass = hM;
    //peak mass range
    const double mpim = HPhysicsConstants::mass(9);
    const double mpip = HPhysicsConstants::mass(8);
    const double mpim2 = -HPhysicsConstants::mass(9)* HPhysicsConstants::mass(9);
    const double mpip2 = HPhysicsConstants::mass(8)*HPhysicsConstants::mass(8);
    const double m1pi = 0;
    const double m2pi = 120000;
    const double mK = HPhysicsConstants::mass(11);
    const double mK2 = HPhysicsConstants::mass(11)* HPhysicsConstants::mass(11);
    const double m1K = 120000;
//    const double m2K = 550;
    const double mp = HPhysicsConstants::mass(14);
    const double mp2 = HPhysicsConstants::mass(14)* HPhysicsConstants::mass(14);
    const double m1p = 300000;
//    const double m2p = 1020;
    const double m1 = -200000;
    const double m2 = 3000000;

    TF1 *fitPim = new TF1("fitPim", "gaus", -m2pi, -m1pi);
    TF1 *fitPip = new TF1("fitPip", "gaus", m1pi, m2pi);
    TF1 *fitK = new TF1("fitK", "gaus", mK2-m1K, mK2+m1K);
    TF1 *fitP = new TF1("fitP", "gaus", mp2-m1p, mp2+m1p);
    TF1 *fitBG1 = new TF1("fitBG1", "expo+pol0", m1, m2);
//    TF1 *fitBG2 = new TF1("fitBG2", "pol1", m2K, m2);
    fitPim -> SetLineColor(4);
    fitPip -> SetLineColor(4);
    fitK -> SetLineColor(4);
    fitP -> SetLineColor(4);
    fitBG1 -> SetLineColor(4);
//    fitBG2 -> SetLineColor(4);

    int npar = 16;
    Double_t par[npar];
    hMass -> Fit(fitPim, "R");
    hMass -> Fit(fitPip, "R+");
    hMass -> Fit(fitK, "R+");
    hMass -> Fit(fitP, "R+");
    hMass -> Fit(fitBG1, "R+");
//    hMass -> Fit(fitBG2, "R+");
    fitPim -> GetParameters(&par[0]);
    fitPip -> GetParameters(&par[3]);
    fitK -> GetParameters(&par[6]);
    fitP -> GetParameters(&par[9]);
    fitBG1 -> GetParameters(&par[12]);
    //  fitBG2 -> GetParameters(&par[11]);
    TF1 *fitPID = new TF1("fitPID", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+expo(12)+pol0(15)", m1, m2);
    fitPID -> SetParameters(par);

    hMass -> Fit(fitPID, "R+"); 

/*    TCanvas *massfit = new TCanvas("massfit","massfit");
    massfit -> cd();
    hMass -> GetXaxis() -> SetTitle("m [MeV]");
    hMass -> GetXaxis() -> SetTitle("#");
    hMass -> Draw();
*/  
/*    FILE *fp = fopen("fitPar.dat","w");
    if (fp!=NULL) {
	int i = 0;
	while(par[i]){
	    if((i+1)%3 == 0)
		fprintf(fp,"%f \n", par[i]);
	    else
		fprintf(fp,"%f ", par[i]);
	    i++;
	}
    }
    fclose(fp);
*/
    return hMass;
}

