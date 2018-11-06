int mass2PIDfit(double fitarr[], float mass2h, float chargeh, int n){
    int partID = -1;

    for(int j = 0; j < n; j++){
	float mean = fitarr[3*j+1];
	float sigma = 4*fitarr[3*j+2];
	if(mass2h*chargeh > (mean-sigma) && mass2h*chargeh < mean+sigma){
	    switch(j){
	    case 0:
		partID = 9;
		break;
	    case 1:
		partID = 8;
		break;
	    case 2:
		partID = 11;
		break;
	    case 3:
		partID = 14;
		break;
	    default:
		partID = -1;
		break;
	    }
	}else partID = -1;
	if(partID != -1)
	    break;
    }

    return partID;

}
