/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TraitsApp.h
 * Author: rafael.luiz.cancian
 *
 * Created on 14 de Agosto de 2018, 19:36
 */

#ifndef TRAITSAPP_H
#define TRAITSAPP_H

#include "GenesysApplication_if.h"
#include "../kernel/simulator/TraceManager.h"

#include "terminal/examples/smarts/Smart_Buffer.h"

//#include "terminal/examples/smarts/Smart_ExtendedFSM.h"
#include "terminal/examples/smarts/Smart_FiniteStateMachine.h"
#include "terminal/examples/smarts/Smart_EFSM1.h"
#include "terminal/examples/smarts/Smart_EFSM2.h"
#include "terminal/examples/smarts/Smart_Buffer.h"

#include "terminal/examples/smarts/Smart_Dummy.h"
#include "terminal/examples/smarts/Smart_Record.h"
#include "terminal/examples/smarts/Smart_LSODE.h"
#include "terminal/examples/smarts/Smart_Failures.h"
#include "terminal/examples/smarts/Smart_HoldSearchRemove.h"


#include "terminal/examples/smarts/Smart_AssignWriteSeizes.h"


template <typename T>
struct TraitsApp {
};

/*!
 *  Configure the Genesys Application
 */
template <> struct TraitsApp<GenesysApplication_if> {
    static const TraceManager::Level traceLevel = TraceManager::Level::L9_mostDetailed;
    static const bool runTests = false;
    static const bool runGraphicalUserInterface = true; ///< If false, a terminal application will be compiled and executed (See TraitsTerminalApp.h). If true, a GUI for a general simulator will be executed.

    //typedef Smart_ExtendedFSM Application;
    //typedef Smart_FiniteStateMachine Application;
    //typedef Smart_Buffer Application;
    //typedef Smart_FiniteStateMachine Application;
    typedef Smart_EFSM1 Application;
    //typedef Smart_Buffer Application;
    //typedef Smart_Failures Application;
    //typedef Smart_AssignWriteSeizes Application;
    //typedef Smart_LSODE Application;
    //typedef Smart_Record Application;
    
    //typedef Smart_EFSM2 Application;
    //typedef Smart_HoldSearchRemove Application;

    //typedef Smart_Dummy Application;

};
/*
template <> struct TraitsApp<GenesysApplication_if> {
    static const TraceManager::Level traceLevel = TraceManager::Level::L9_mostDetailed;
    static const bool runTests = false;
    static const bool runGraphicalUserInterface = true; ///< If false, a terminal application will be compiled and executed (See TraitsTerminalApp.h). If true, a GUI for a general simulator will be executed.

    typedef Smart_FiniteStateMachine Application;
};*/


#endif /* TRAITSAPP_H */

