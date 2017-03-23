#include "dagmctransform.hpp"
#include "moab/Interface.hpp"
#include <iostream>

// constructor for metadata class
//dagmcTransform::dagmcTransform(moab::DagMC* dag_ptr)
dagmcTransform::dagmcTransform(moab::Interface* mbi_ptr)
{
  MBI = mbi_ptr;
}

// destructor 
dagmcTransform::~dagmcTransform()
{
}

moab::ErrorCode dagmcTransform::get_verts(moab::EntityHandle vol, moab::Range &verts)
{
  moab::ErrorCode rval;
  moab::Range surf_set, vert_set;
  int num_verts;
  moab::Range::iterator it, itr;

  surf_set.clear();
  vert_set.clear();

  MBI->get_child_meshsets(vol, surf_set);
  for (it = surf_set.begin(); it != surf_set.end(); it++)
   {
     rval =  MBI->get_entities_by_type(*it, moab::MBVERTEX, vert_set);
     for (itr = vert_set.begin(); itr != vert_set.end(); itr++)
       {
         verts.insert(*itr);
       }
   }
}
