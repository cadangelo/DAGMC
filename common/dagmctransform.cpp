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

  rval = MBI->get_child_meshsets(vol, surf_set);
  MB_CHK_SET_ERR(rval, "Failed to get child meshsets");
  for (it = surf_set.begin(); it != surf_set.end(); it++)
   {
     rval =  MBI->get_entities_by_type(*it, moab::MBVERTEX, vert_set);
     MB_CHK_SET_ERR(rval, "Failed to get the volume's vertices");
     for (itr = vert_set.begin(); itr != vert_set.end(); itr++)
       {
         verts.insert(*itr);
       }
   }

  return moab::MB_SUCCESS;
}

moab::ErrorCode dagmcTransform::translate(moab::Range vertices, double* trans_vec)
{
  moab::ErrorCode rval;
  // loop over all vertices, get coordinates, update position, save
  moab::Range::iterator it;
  double xyz_0[3], xyz[3];
  for (it = vertices.begin(); it != vertices.end(); ++it)
    {
      rval = MBI->get_coords(&(*it), 1, xyz_0);
      MB_CHK_SET_ERR(rval, "Failed to get vertex coordinates");
    
      // translation vector elements from mcnp trf have the opposite sign
      xyz[0] = xyz_0[0] + trans_vec[0]*(-1);
      xyz[1] = xyz_0[1] + trans_vec[1]*(-1);
      xyz[2] = xyz_0[2] + trans_vec[2]*(-1);

      rval = MBI->set_coords(&(*it), 1, xyz);
      MB_CHK_SET_ERR(rval, "Failed to set vertex coordinates");
    }
}

moab::ErrorCode dagmcTransform::pass_coords(moab::EntityHandle vert, double &xval)
{
  moab::ErrorCode rval;
  double xyz[3];
  rval = MBI->get_coords(&vert, 1, xyz);
  MB_CHK_SET_ERR(rval, "Failed to get vertex coordinates");
  xval = xyz[0];
}

moab::ErrorCode dagmcTransform::delete_obb(moab::EntityHandle vol)
{		
  moab::ErrorCode rval;
  moab::EntityHandle root;
  std::cout << "delete obb tree for vol " << vol << std::endl;
  rval = DAG->geom_tool()->get_root(vol, root);
  if (moab::MB_SUCCESS != rval){
    std::cout<< "No obb tree root found " << rval << std::endl;
	return moab::MB_SUCCESS;
  }	
  // if a root was found, delete the tree
  rval = DAG->geom_tool()->obb_tree()->delete_tree(root);
  MB_CHK_SET_ERR(rval, "Failed to delete obb tree");

}
