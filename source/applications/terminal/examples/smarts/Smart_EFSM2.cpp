#include "Smart_EFSM2.h"

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/Simulator.h"

// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/components/ExtendedFinishStateMachine.h"
#include "../../../TraitsApp.h"

Smart_EFSM2::Smart_EFSM2() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int Smart_EFSM2::main(int argc, char** argv) {
	// instantiate simulator
	Simulator* genesys = new Simulator();
	genesys->getTracer()->setTraceLevel(TraceManager::Level::L9_mostDetailed);
	PluginManager* plugins = genesys->getPlugins();
	
	// create model
	Model* model = genesys->getModels()->newModel();
	
	// initialize model parts
	ExtendedFinishStateMachine* ExtendedExample = plugins->newInstance<ExtendedFinishMachine>(model, "ExtendedFinishMachine_1");
	
	// creating states of efsm
	ExtendedExample.insertState('Green', false, false);
    ExtendedExample.insertState('Yellow', false, false);
    ExtendedExample.insertState('Red', false, true);
    ExtendedExample.insertState('Pending', false, false);

    // creating transitions of each state of efsm
    ExtendedExample.insertTransition("count >= 60", "Red", "Green","sigG", "count = count + 1");
    ExtendedExample.insertTransition("pedestrian & count < 60", "Green", "Pending", nullptr, "count = count + 1");
    ExtendedExample.insertTransition("count >= 60", "Pending", "Yellow", "sigY", "count = 0");
    ExtendedExample.insertTransition("count >= 5", "Yellow", "Red", "sigR", "count = 0");
    ExtendedExample.insertTransition("pedestrian & count >= 60", "Green", "Yellow", "sigY", "count = 0");
    ExtendedExample.insertTransition(nullptr, "Red", "Red", nullptr, "count = count + 1");
    ExtendedExample.insertTransition("count < 60", "Green", "Green", nullptr, "count = count + 1");
    ExtendedExample.insertTransition(nullptr, "Pending", "Pending", nullptr, "count = count + 1");
    ExtendedExample.insertTransition(nullptr, "Yellow", "Yellow", nullptr, "count = count + 1");
	
	// run the simulation
	auto output = ExtendedExample.fire();
	auto output = ExtendedExample.fire();
	auto output = ExtendedExample.fire();
	sim->start();
	
	// free memory
	delete genesys;
	
	return 0;
};