int mass2PID(float mass2h, float chargeh){
    int partID = -1;
    //peak mass range
    const double mpim = HPhysicsConstants::mass(9);
    const double mpip = HPhysicsConstants::mass(8);
    const double mpim2 = -HPhysicsConstants::mass(9)* HPhysicsConstants::mass(9);
    const double mpip2 = HPhysicsConstants::mass(8)*HPhysicsConstants::mass(8);
    const double m1pi = 0;
    const double m2pi = 100000;
    const double mK = HPhysicsConstants::mass(11);
    const double mK2 = HPhysicsConstants::mass(11)* HPhysicsConstants::mass(11);
    const double m1K = 100000;
//    const double m2K = 550;
    const double mp = HPhysicsConstants::mass(14);
    const double mp2 = HPhysicsConstants::mass(14)* HPhysicsConstants::mass(14);
    const double m1p = 300000;
//    const double m2p = 1020;
    const double m1 = -200000;
    const double m2 = 3000000;

    double m2q = mass2h*chargeh;
    if(m2q > -m2pi && m2q < m1pi)
	partID = 9;
    else if(m2q > m1pi && m2q < m2pi)
	partID = 8;
    else if(m2q > (mK2-m1K) && m2q < (mK2+m1K))
	partID = 11;
    else if(m2q > (mp2-m1p) && m2q < (mp2+m1p))
	partID = 14;
   
    return partID;
}
