#include <iostream>
#include "DagMC.hpp"
#include "moab/Interface.hpp"

class dagmcTransform
{
 public:
  dagmcTransform(moab::Interface *mbi_ptr);
  ~dagmcTransform();

  moab::ErrorCode get_verts(moab::EntityHandle vol, moab::Range &verts);


  // private member functions
 private:

 private:
  moab::DagMC *DAG; // Pointer to DAGMC instance
  moab::Interface *MBI; // Pointer to MOAB instance
};
