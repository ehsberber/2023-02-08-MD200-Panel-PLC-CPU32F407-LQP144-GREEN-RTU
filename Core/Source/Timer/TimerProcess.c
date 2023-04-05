#include "Registers.h"
extern strcREGISTERS  Registers;

void TimerInitialize(void)
{
	 unsigned char TimerNo;
	 for(TimerNo = 0; TimerNo < TIMER_COUNT ; TimerNo++)
	 	 {
			 *Registers.Timers.Counter[TimerNo] = 0;
			 *Registers.Timers.TimeOut[TimerNo] = 0;
			 Registers.Timers.Control[TimerNo]->Enable = 0;
			 Registers.Timers.Control[TimerNo]->Timeout = 0;
	 	 }
}

void TimerStart(unsigned short TimerNo, unsigned int Timeout)
{
	*Registers.Timers.Counter[TimerNo]  		=  0;
	*Registers.Timers.TimeOut[TimerNo]  		= Timeout;
	Registers.Timers.Control[TimerNo]->Timeout 	= 0;
	Registers.Timers.Control[TimerNo]->Enable 	= 1;
	Registers.Timers.Control[TimerNo]->Hang 	= 0;
}

void TimerRestart(unsigned short TimerNo, unsigned int Timeout)
{
	*Registers.Timers.Counter[TimerNo] 			=  0;
	*Registers.Timers.TimeOut[TimerNo] 			= Timeout;
	Registers.Timers.Control[TimerNo]->Enable 	= 1;
	Registers.Timers.Control[TimerNo]->Timeout 	= 0;
	Registers.Timers.Control[TimerNo]->Hang 	= 0;
}

void TimerStop(unsigned short TimerNo)
{
	Registers.Timers.Control[TimerNo]->Enable = 0;
	*Registers.Timers.Counter[TimerNo] 		  = 0;
	Registers.Timers.Control[TimerNo]->Hang   = 1;
}

//void TimerProcess(void)
//{
//	unsigned short TimerNo;
//	for(TimerNo=0; TimerNo < TIMER_COUNT; TimerNo++)
//		{
//			//
//			// Reset Timer
//			//
//			if (*Registers.Timers.Counter[TimerNo].Reset ) { *Registers.Timers.Counter[TimerNo].Counter = 0;*Registers.Timers.Counter[TimerNo].Reset = 0;}
//			//
//			// Check Timer Timeout
//			//
//			if (*Registers.Timers.Counter[TimerNo].Enable )
//				{
//					if(*Registers.Timers.Counter[TimerNo].Counter >= (*Registers.Timers.Counter[TimerNo].Count * *Registers.Timers.Counter[TimerNo].Resolution) )
//						{
//							*Registers.Timers.Counter[TimerNo].Timeout = 1;
//							*Registers.Timers.Counter[TimerNo].Enable = 0;
//						}
//				}
//		}
//}

void SettingRTU(void)
{

}
void TimerControlProcess(void)
{
	unsigned char i;

	for(i=0;i<TIMER_COUNT;i++)
		{
		   //Registers.Timers.Control[i]->Timeout = 0;

		   if ( ( (!(Registers.Timers.Control[i]->Timeout   ||  Registers.Timers.Control[i]->Hang ))  && ( Registers.Timers.Control[i]->Enable) && ( *Registers.Timers.TimeOut[i] > 0) ))
				{
					if ( *Registers.Timers.Counter[i] >= *Registers.Timers.TimeOut[i])
						{
							if( Registers.Timers.Control[i]->Restart)
								{
									Registers.Timers.Control[i]->Timeout = 1;
									Registers.Timers.Control[i]->Started = 1;
									Registers.Timers.Control[i]->Hang = 0;
								}
							else
								{
									Registers.Timers.Control[i]->Timeout = 1;
									Registers.Timers.Control[i]->Started = 1;
									Registers.Timers.Control[i]->Hang = 0;
								}
							*Registers.Timers.Counter[i] = 0;
						}
					else
						{
							if( Registers.Timers.Control[i]->Restart)
								{
									*Registers.Timers.Counter[i] = 0;
									Registers.Timers.Control[i]->Restart = 0;
								}
						}
				}
		}
}
