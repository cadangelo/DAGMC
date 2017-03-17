#include <iostream>
#include "DagMC.hpp"

class dagmcTransform
{
 public:
  dagmcTransform(moab::DagMC *dag_ptr);
  ~dagmcTransform();

  // private member functions
 private:
  void fxn();

 private:
  moab::DagMC *DAG; // Pointer to DAGMC instance
};
