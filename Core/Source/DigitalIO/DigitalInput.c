#include "MicroPeripheral.h"  
#include "Registers.h"
#include "RegisterOperation.h"
#include "DigitalInput.h"
#include "PlcDefinition.h"
#include "DigitalInputMicroLayer.h"


extern strcREGISTERS Registers;
extern strcPLC Plc;

void DigitalInput(void)
{
 
	//
	// MicroController �zerindeki Portlari Okur
	//
	DigitalInputReadFromMicroPort(0);
 
	Plc.Peripheral.DigitalInput.State->DIs = Registers.Input[0];
}
