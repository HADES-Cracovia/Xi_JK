int tofPID(float tof){
    int vecID = -1;

    float pi1 = 18.5; //the lower range of pions in FD
    float pi_p_cut = 20.5; //where to put a difference between protons and pions (see drawTof.cc)
    float p2 = 27.; //the upper range of protons in FD
    if(tof != -1){
	if(tof < pi_p_cut)
	    vecID = 9;
	else
	    vecID = 14;
    
    }//else cout << "tof_v==-1 ---> no PID in FD" << endl;

    return vecID;
}
