#include "dagmctransform.hpp"
#include <iostream>

// constructor for metadata class
dagmcTransform::dagmcTransform(moab::DagMC* dag_ptr)
{
  DAG = dag_ptr; // dagmc pointer
}

// destructor 
dagmcTransform::~dagmcTransform()
{
}

void dagmcTransform::fxn()
{
}
