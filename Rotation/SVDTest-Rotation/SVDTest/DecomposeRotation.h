#pragma once

//////////////////////////////
// Written by Seung-Chan Kim
// dalek@kaist.ac.kr
// September 25th, 2014

#include "../lib/3d/dhVector.h"
#include "../lib/3d/dhMat.h"

#include "../lib/vArray.h"
#include "../lib/vToken.h"



class DecomposeRotation
{
public:
	DecomposeRotation(void);
	~DecomposeRotation(void);

public:
	void LoadData(char* fn_A,char* fn_B, char* fn_R, char* fn_t);

	void Calc();
	vArray <dhVector, dhVector> A;
	vArray <dhVector, dhVector> B;


	vArray <dhVector, dhVector> Ac;
	vArray <dhVector, dhVector> Bc;

	dhMat R;
	dhVector t;


private:
	
};

/*

void CVRecogImg::SetH(const float* R_, const float* T_, float* H_)
{

	H_[0] = R_[0];
	H_[1] = R_[3];
	H_[2] = R_[6];
	H_[3] = 0; 

	H_[4] = R_[1];
	H_[5] = R_[4];
	H_[6] = R_[7];
	H_[7] = 0;

	H_[8] = R_[2];
	H_[9] = R_[5];
	H_[10] = R_[8];
	H_[11] = 0;

	H_[12] = T_[0];
	H_[13] = T_[1];
	H_[14] = T_[2];
	H_[15] = 1;
}
*/