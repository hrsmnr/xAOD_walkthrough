#define APP_NAME "Plotter"
#define MyVerbose(a,b) if(m_dbg<=MSG::VERBOSE) std::cout<<"Verbose in <Plotter::"<<(a)<<">: "<<(b)<<std::endl;
#define MyDebug(a,b) if(m_dbg<=MSG::DEBUG) std::cout<<"Debug in <Plotter::"<<(a)<<">: "<<(b)<<std::endl;
#define MyInfo(a,b) if(m_dbg<=MSG::INFO) std::cout<<"Info in <Plotter::"<<(a)<<">: "<<(b)<<std::endl;
#define MyError(a,b) if(m_dbg<=MSG::ERROR) std::cout<<"Error in <Plotter::"<<(a)<<">: "<<(b)<<std::endl;
#define MyAlways(a,b) if(m_dbg<=MSG::ALWAYS) std::cout<<"In <Plotter::"<<(a)<<">: "<<(b)<<std::endl;

#include<iostream>
#include"MyAnalysis/Plotter.h"

/*--------------------------------------------------------------------------------*/
// Plotter Constructor
/*--------------------------------------------------------------------------------*/
Plotter::Plotter(std::string sel, std::string sys, MSG::Level dbg) : 
  m_dbg(dbg)
{}

/*--------------------------------------------------------------------------------*/
// Initialize the plotter
/*--------------------------------------------------------------------------------*/
void Plotter::initialize()
{
  MyDebug("initialize()","Plotter::initialize()");

  // Booking histograms
  BookHistograms();

}

/*--------------------------------------------------------------------------------*/
// Finalize event selection
/*--------------------------------------------------------------------------------*/
void Plotter::finalize()
{
  MyDebug("finalize()","Plotter::finalize()");

}

/*--------------------------------------------------------------------------------*/
bool Plotter::BookHistograms()
{
  MyDebug("BookHistograms()","Plotter::BookHistograms()");

  return true;
}

/*--------------------------------------------------------------------------------*/
bool Plotter::FillHistograms(EventSelector *EveSelec)
{
  MyDebug("FillHistograms()","Plotter::FillHistograms()");
  
  return true;
}
