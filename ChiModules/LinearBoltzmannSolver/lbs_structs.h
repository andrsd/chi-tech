#ifndef LBS_STRUCTS_H
#define LBS_STRUCTS_H

#include <ChiMath/chi_math.h>
#include <ChiPhysics/PhysicsMaterial/transportxsections/material_property_transportxsections.h>

namespace lbs
{

enum class GeometryType
{
  NO_GEOMETRY_SET  = 0,
  ONED_SLAB        = 1,
  ONED_CYLINDRICAL = 2,
  ONED_SPHERICAL   = 3,
  TWOD_CARTESIAN   = 4,
  TWOD_CYLINDRICAL = 5,
  THREED_CARTESIAN = 6
};

/**Struct for storing LBS options.*/
struct Options
{
  typedef chi_math::SpatialDiscretizationType SDMType;

  GeometryType geometry_type = GeometryType::NO_GEOMETRY_SET;
  SDMType sd_type = SDMType::UNDEFINED;
  unsigned int scattering_order=1;
  int  sweep_eager_limit= 32000; //see chiLBSSetProperty documentation

  bool read_restart_data=false;
  std::string read_restart_folder_name = std::string("YRestart");
  std::string read_restart_file_base   = std::string("restart");

  bool write_restart_data=false;
  std::string write_restart_folder_name = std::string("YRestart");
  std::string write_restart_file_base   = std::string("restart");
  double write_restart_interval = 30.0;

  bool use_precursors = false;
  bool use_src_moments = false;

  bool save_angular_flux = false;

  bool verbose_inner_iterations = true;
  bool verbose_outer_iterations = true;

  Options() = default;
};


/**Transport view of a cell*/
class CellLBSView
{
private:
  size_t phi_address;
  unsigned int num_nodes;
  unsigned int num_grps;
  unsigned int num_grps_moms;
  const chi_physics::TransportCrossSections& xs;
  double volume;
  std::vector<bool> face_local_flags = {};
  std::vector<double> outflow;

public:
  CellLBSView(size_t in_phi_address,
              unsigned int in_num_nodes,
              unsigned int in_num_grps,
              unsigned int in_num_moms,
              const chi_physics::TransportCrossSections& in_xs_mapping,
              double in_volume,
              const std::vector<bool>& in_face_local_flags,
              bool cell_on_boundary) :
    phi_address(in_phi_address),
    num_nodes(in_num_nodes),
    num_grps(in_num_grps),
    num_grps_moms(in_num_grps*in_num_moms),
    xs(in_xs_mapping),
    volume(in_volume),
    face_local_flags(in_face_local_flags)
  {
    if (cell_on_boundary)
      outflow.resize(num_grps,0.0);
  }

  size_t MapDOF(unsigned int node, unsigned int moment, unsigned int grp) const
  {
    return phi_address + (size_t) node * num_grps_moms + (size_t) num_grps * moment + grp;
  }

   const chi_physics::TransportCrossSections& XS() const
  {return xs;}

  bool IsFaceLocal(unsigned int f) const {return face_local_flags[f];}

  unsigned int NumNodes() const {return num_nodes;}

  double Volume() const {return volume;}

  void ZeroOutflow(     ) {outflow.assign(outflow.size(),0.0);}
  void ZeroOutflow(unsigned int g) {if (g<outflow.size()) outflow[g]=0.0;}
  void AddOutflow(unsigned int g, double intS_mu_psi)
  {
    if (g<outflow.size()) outflow[g] += intS_mu_psi;
  }
  double GetOutflow(unsigned int g) const
  {
    if (g<outflow.size()) return outflow[g];
    else return 0.0;
  }
};

}

#endif
