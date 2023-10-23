#include "Smart_EFSM2.h"

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/Simulator.h"

// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/data/EFSM.h"
#include "../../../../plugins/components/FiniteStateMachine.h"
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
	genesys->getTracer()->setTraceLevel(TraitsApp<GenesysApplication_if>::traceLevel);
	setDefaultTraceHandlers(genesys->getTracer());
    PluginManager* plugins = genesys->getPlugins();
    plugins->autoInsertPlugins("/mnt/HD_EXTERNO/computerScience/course/14ºFASE/modSim/new/Genesys-Simulator/autoloadplugins.txt");
	// create model
	Model* model = genesys->getModels()->newModel();
    Create* create1 = plugins->newInstance<Create>(model);
	
	// initialize model parts
    //ExtendedFSM* ExtendedExample = plugins->newInstance<ExtendedFSM>(model, "ExtendedFinishMachine_1");
    FiniteStateMachine* fsm = plugins->newInstance<FiniteStateMachine>(model, "ExtendedFinishMachine_1");
	fsm->setName("fsm_1");
    std::cout << fsm->getName() << "\n";
	std::cout << fsm->show() << "\n";
    
    Dispose* dispose1 = plugins->newInstance<Dispose>(model);
    std::cout << dispose1->getName();
    std::cout << dispose1->getId();

	// connect model components to create a "workflow"
	create1->getConnections()->insert(fsm);
	fsm->getConnections()->insert(dispose1);

    dispose1->setReportStatistics(true);
	
    std::cout << "\nplugins: " << plugins->front() << "\n";

	// creating states of efsm
    fsm->_createInternalAndAttachedData();

	// creating states of efsm
    fsm->_internalDataDefinition->insertState("Green", false, false);
    std::cout <<  "state Name: " << fsm->_internalDataDefinition->getStates()->at(0).getName() << "\n";
    fsm->_internalDataDefinition->insertState("Yellow", false, false);
    std::cout <<  "state Name: " << fsm->_internalDataDefinition->getStates()->at(1).getName() << "\n";
    fsm->_internalDataDefinition->insertState("Red", false, true);
    std::cout <<  "state Name: " << fsm->_internalDataDefinition->getStates()->at(2).getName() << "\n";
    fsm->_internalDataDefinition->insertState("Pending", false, false);
    std::cout <<  "state Name: " << fsm->_internalDataDefinition->getStates()->at(3).getName() << "\n";

    fsm->_internalDataDefinition->insertVariable("count", 0);
    //fsm->_internalDataDefinition->insertVariable("M", 100);

    // creating transitions of each state of efsm
    fsm->_internalDataDefinition->insertTransition("count >= 60", "Red", "Green","sigG = 1", "count = 0");
    //fsm->_internalDataDefinition->insertTransition("pedestrian & count < 60", "Green", "Pending", "", "count = count + 1");
    fsm->_internalDataDefinition->insertTransition("count < 60 & pedestrian = 1", "Green", "Pending", "", "count = count + 1");
    fsm->_internalDataDefinition->insertTransition("count >= 60", "Pending", "Yellow", "sigY = 1", "count = 0");
    fsm->_internalDataDefinition->insertTransition("count >= 5", "Yellow", "Red", "sigR = 1", "count = 0");
    fsm->_internalDataDefinition->insertTransition("pedestrian = 0 & count >= 60", "Green", "Yellow", "sigY", "count = 0");
    fsm->_internalDataDefinition->insertTransition("count < 60", "Red", "Red", "", "count = count + 1");
    fsm->_internalDataDefinition->insertTransition("count < 60", "Green", "Green", "", "count = count + 1");
    fsm->_internalDataDefinition->insertTransition("count < 60", "Pending", "Pending", "", "count = count + 1");
    fsm->_internalDataDefinition->insertTransition("count < 5", "Yellow", "Yellow", "", "count = count + 1");
	
	// run the simulation
    auto outputActions = std::map<std::string,int>{};
    auto input = std::map<std::string,int>{};
    input.insert(std::pair<std::string,int>("pedestrian", 1));
    //input.insert(std::pair<std::string,int>("pedestrian", 0));

    bool isfinalState;
    for (int i = 1; i <= 240; i++){
        outputActions.clear();
        isfinalState = fsm->_internalDataDefinition->fire(input, outputActions);
        std::cout << "currentState: " << fsm->_internalDataDefinition->getCurrentState() <<std::endl;
        for(auto outputAction: outputActions){
            std::cout << outputAction.first << " = " << outputAction.second << std::endl;
        }
    }

    std::cout << "" << std::endl;

    // set options, save and simulate
	model->getSimulation()->setNumberOfReplications(1);
	model->getSimulation()->setReplicationLength(3, Util::TimeUnit::second);
	//model->getSimulation()->setTerminatingCondition("count(Dispose_1.CountNumberIn)>30");
	model->getSimulation()->setReplicationReportBaseTimeUnit(Util::TimeUnit::hour);
    model->save("./models/Smart_EFSM2.gen");
	model->getSimulation()->start();	
	
	// free memory
	delete genesys;
	
	return 0;
};
