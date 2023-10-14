#include "Smart_EFSM1.h"

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/Simulator.h"

// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/components/ExtendedFinishStateMachine.h"
#include "../../../TraitsApp.h"

Smart_EFSM1::Smart_EFSM1() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int Smart_EFSM1::main(int argc, char** argv) {
	// instantiate simulator
	Simulator* genesys = new Simulator();
	genesys->getTracer()->setTraceLevel(TraceManager::Level::L9_mostDetailed);
	PluginManager* plugins = genesys->getPlugins();
	
	// create model
	Model* model = genesys->getModels()->newModel();
	
	// initialize model parts
	ExtendedFinishStateMachine* ExtendedExample = plugins->newInstance<ExtendedFinishMachine>(model, "ExtendedFinishMachine_1");
	
	// creating states of efsm
	ExtendedExample.insertState('Counting', false, true);
    ExtendedExample.insertVariable("c", 0);
    ExtendedExample.insertVariable("M", 100);

    // creating transitions of each state of efsm
    ExtendedExample.insertTransition("up = 1 & down = 0 & c < M", "Counting", "Counting","saida = c + 1", "c = c + 1");
    ExtendedExample.insertTransition("down = 1 & up = 0 & c > 0", "Counting", "Counting","saida = c - 1", "c = c - 1");
	
	// run the simulation
	auto output = ExtendedExample.fire();
	auto output = ExtendedExample.fire();
	auto output = ExtendedExample.fire();
	sim->start();
	
	// free memory
	delete genesys;
	
	return 0;
};