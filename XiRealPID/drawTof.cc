/////////////////////////////////////////////////////////////
//Use this macro to draw ToF distribution of the particles //
//////////////////identified by GEANT in FD//////////////////
//run: root 'drawTof.cc("name_of_output_chan.root")'////////
// e.g.: root 'drawTof.cc("output_090_test5.root")'/////////
////////////////////////////////////////////////////////////

void drawTof(char* outfile){
  TFile * fin = TFile::Open(outfile, "READ");
  int toff1 = 20; //15
  int toff2 = 40;
  int nbins1 = 200;

  TH1F *hTof_fd_all_GeantID = (TH1F*)fin->Get("hTof_all_fd_GeantID") -> Clone("h1");
  TH1F *hTof_all_GeantID = (TH1F*)fin->Get("hTof_all_GeantID") -> Clone("h2");
  TH1F *hTof_fd_pim_GeantID = (TH1F*)fin->Get("hTof_pim_fd_GeantID") -> Clone("h3");
  TH1F *hTof_fd_Kp_GeantID = (TH1F*)fin->Get("hTof_Kp_fd_GeantID") -> Clone("h4");
  TH1F *hTof_fd_p_GeantID = (TH1F*)fin->Get("hTof_p_fd_GeantID") -> Clone("h5");

  hTof_fd_all_GeantID -> SetLineColor(kBlack);
  hTof_fd_pim_GeantID -> SetLineColor(kMagenta);
  hTof_fd_Kp_GeantID -> SetLineColor(kBlue);
  hTof_fd_p_GeantID -> SetLineColor(kGreen);

  hTof_fd_all_GeantID -> GetXaxis() -> SetRangeUser(toff1, toff2);
  
  TLegend *l1 = new TLegend(.8,.5,.9,.7);
  l1 -> AddEntry(hTof_fd_all_GeantID, "all");
  l1 -> AddEntry(hTof_fd_pim_GeantID, "#pi^{-}");
  l1 -> AddEntry(hTof_fd_Kp_GeantID, "K^{+}");
  l1 -> AddEntry(hTof_fd_p_GeantID, "p");

  float pi1 = 25;
//      18.5; //the lower range of pions in FD                                                  
  float pi_p_cut = 27.2;
//      20.5; //where to put a difference between protons and pions (see drawTof.cc)       
      float p2 = 36;
//      27.; //the upper range of protons in FD                                                   
 
  float y1 = 0.;
  float y2 = hTof_fd_all_GeantID -> GetMaximum();
  TLine *line1 = new TLine(pi1, y1, pi1, y2);
  TLine *line2 = new TLine(pi_p_cut, y1, pi_p_cut, y2);
  TLine *line3 = new TLine(p2, y1, p2, y2);
  line1 -> SetLineColor(kRed);
  line1 -> SetLineWidth(3);
  line2 -> SetLineColor(kRed);
  line2 -> SetLineWidth(3);
  line3 -> SetLineColor(kRed);
  line3 -> SetLineWidth(3);

//  TPaveText *pt1 = new TPaveText(0.17,0.75,0.22,0.8,"brNDC");
  TPaveText *pt1 = new TPaveText(0.27,0.75,0.32,0.8,"brNDC");
  pt1->SetBorderSize(0);
  pt1->SetFillColor(0);
  pt1->SetTextSize(0.03);
  char t1[32];
  sprintf(t1, "%.01f ns", pi1);
  pt1 -> AddText(t1); 

//  TPaveText *pt2 = new TPaveText(0.25,0.75,0.3,0.8,"brNDC");
  TPaveText *pt2 = new TPaveText(0.35,0.75,0.4,0.8,"brNDC");
  pt2->SetBorderSize(0);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.03);
  char t2[32];
  sprintf(t2, "%.01f ns", pi_p_cut);
  pt2 -> AddText(t2); 

//  TPaveText *pt3 = new TPaveText(0.45,0.75,0.5,0.8,"brNDC");
  TPaveText *pt3 = new TPaveText(0.72,0.75,0.77,0.8,"brNDC");
  pt3->SetBorderSize(0);
  pt3->SetFillColor(0);
  pt3->SetTextSize(0.03);
  char t3[32];
  sprintf(t3, "%.01f ns", p2);
  pt3 -> AddText(t3); 

  
  TCanvas *cTofFD = new TCanvas("cTofFD", "cTofFD", 1200, 800);
  cTofFD -> cd();
  hTof_fd_all_GeantID -> Draw();
  hTof_fd_pim_GeantID -> Draw("same");
  hTof_fd_Kp_GeantID -> Draw("same");
  hTof_fd_p_GeantID -> Draw("same");
  line1 -> Draw("same");
  line2 -> Draw("same");
//  line3 -> Draw("same");
  l1 -> Draw("same");
  pt1 -> Draw("same");
  pt2 -> Draw("same");
//  pt3 -> Draw("same");
}
