#include "TCutG.h"

void CutsDef2(void){
    
  //no part
  TCutG *cutg_noPart = new TCutG("CUTG_00",10);
  cutg_noPart->SetVarX("hBeta");
  cutg_noPart->SetPoint(0,0,0);
  cutg_noPart->SetPoint(0,0,0);
  cutg_noPart->SetPoint(0,0,0);

    
  //pim
  TCutG *cutg_pim = new TCutG("CUTG_09",11);
  cutg_pim->SetVarX("hBeta");
  cutg_pim->SetPoint(0,-59.2427,0.874881);
  cutg_pim->SetPoint(1,-174.561,0.966365);
  cutg_pim->SetPoint(2,-282.995,1.00538);
  cutg_pim->SetPoint(3,-955.972,1.00538);
  cutg_pim->SetPoint(4,-956.833,0.970401);
  cutg_pim->SetPoint(5,-749.432,0.928695);
  cutg_pim->SetPoint(6,-459.415,0.870845);
  cutg_pim->SetPoint(7,-307.091,0.782052);
  cutg_pim->SetPoint(8,-91.0843,0.443024);
  cutg_pim->SetPoint(9,-52.358,0.452441);
  cutg_pim->SetPoint(10,-59.2427,0.874881);

 
  //pip
  TCutG *cutg_pip = new TCutG("CUTG_08",11);
  cutg_pip->SetVarX("hBeta");
  cutg_pip->SetPoint(0,59.2427,0.874881);
  cutg_pip->SetPoint(1,174.561,0.966365);
  cutg_pip->SetPoint(2,282.995,1.00538);
  cutg_pip->SetPoint(3,955.972,1.00538);
  cutg_pip->SetPoint(4,956.833,0.970401);
  cutg_pip->SetPoint(5,749.432,0.928695);
  cutg_pip->SetPoint(6,459.415,0.870845);
  cutg_pip->SetPoint(7,307.091,0.782052);
  cutg_pip->SetPoint(8,91.0843,0.443024);
  cutg_pip->SetPoint(9,52.358,0.452441);
  cutg_pip->SetPoint(10,59.2427,0.874881);


  //K+
  TCutG *cutg_Kp = new TCutG("CUTG_11",15);
  cutg_Kp->SetVarX("hBeta");
  cutg_Kp->SetPoint(0,1469.72,0.994383);
  cutg_Kp->SetPoint(1,1485.12,0.923851);
  cutg_Kp->SetPoint(2,1317.11,0.893809);
  cutg_Kp->SetPoint(3,1032.9,0.833725);
  cutg_Kp->SetPoint(4,782.29,0.761886);
  cutg_Kp->SetPoint(5,611.483,0.693966);
  cutg_Kp->SetPoint(6,454.676,0.601228);
  cutg_Kp->SetPoint(7,191.465,0.375261);
  cutg_Kp->SetPoint(8,167.664,0.460162);
  cutg_Kp->SetPoint(9,394.474,0.714864);
  cutg_Kp->SetPoint(10,590.482,0.841562);
  cutg_Kp->SetPoint(11,790.69,0.91732);
  cutg_Kp->SetPoint(12,1174.31,0.994383);
  cutg_Kp->SetPoint(13,1465.52,0.994383);
  cutg_Kp->SetPoint(14,1469.72,0.994383);


  //p
  TCutG *cutg_p = new TCutG("CUTG_14",13);
  cutg_p->SetVarX("hBeta");
  cutg_p->SetPoint(0,1997.39,0.860681);
  cutg_p->SetPoint(1,1293.64,0.735875);
  cutg_p->SetPoint(2,988.685,0.672816);
  cutg_p->SetPoint(3,849.401,0.625521);
  cutg_p->SetPoint(4,179.374,0.139436);
  cutg_p->SetPoint(5,108.999,0.235339);
  cutg_p->SetPoint(6,240.952,0.399557);
  cutg_p->SetPoint(7,452.077,0.575599);
  cutg_p->SetPoint(8,792.222,0.747699);
  cutg_p->SetPoint(9,1298.04,0.883015);
  cutg_p->SetPoint(10,1755.48,0.939506);
  cutg_p->SetPoint(11,1997.39,0.936878);
  cutg_p->SetPoint(12,1997.39,0.860681);


  TFile* file = new TFile("CutsDef2.root","RECREATE");
  cutg_noPart -> Write();
  cutg_pim -> Write();
  cutg_pip -> Write();
  cutg_Kp -> Write();
  cutg_p -> Write();

  file -> Write();
  file -> Close();

  delete file;

}
