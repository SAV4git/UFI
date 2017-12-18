#include "../UFI_lib/UFI.h"
#include "../UFI_lib/UFI_Types.h"
#include "UFI_Anim.h"

UFI_Anim::UFI_Anim()
{
}

UFI_Anim::~UFI_Anim()
{
}

UFI_Anim::UFI_Anim(const UFI_Anim& rhs)
{
}


void UFI_Anim::SetAnim(int from, int to){
	from_p = from;
	to_p = to;
}


void UFI_Anim::SetTime(int timestep, int period){
	timestep_p = timestep;
	period_p = period;
	N = (int) period_p/timestep_p;
	//printf("N= %d\n", N );
}


void UFI_Anim::Start(){
	N_state = 0;
	param = from_p;
}


int UFI_Anim::Update(){
	if(N_state < N){
		N_state++;
		//printf("N_state= %d, =%d\n", N_state, Anim_IntVec[N_state] );
		return Anim_IntVec[N_state];
	}
	else return Anim_IntVec[N];
}


void UFI_Anim::SetLinear(void){
	int delta = (to_p - from_p)/N; //printf("delta= %d\n", delta );
	
	for (int i = 0; i <= N; i++){
		if( (from_p + delta*i) >= to_p) Anim_IntVec.push_back(to_p);
		else Anim_IntVec.push_back( from_p + delta*i );
		//printf("Anim_IntVec= %d\n", Anim_IntVec[i] );
	}
}


void UFI_Anim::SetSigmoid(void){
	
}

