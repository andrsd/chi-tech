#include "chi_sweepbuffer.h"

#include "chi_angleset.h"
#include "chi_SPDS.h"
#include "chi_FLUDS.h"

#include <chi_log.h>
#include <chi_mpi.h>
#include <ChiConsole/chi_console.h>

extern ChiLog     chi_log;
extern ChiMPI     chi_mpi;
extern ChiConsole chi_console;

extern double chi_global_timings[20];

//###################################################################
/**Constructor.*/
chi_mesh::SweepManagement::SweepBuffer::
  SweepBuffer(chi_mesh::SweepManagement::AngleSet* ref_angleset,
              int sweep_eager_limit,
              ChiMPICommunicatorSet* in_comm_set)
{
  angleset = ref_angleset;
  initialized = false;
  done_sending = false;
  data_initialized = false;
  upstream_data_initialized = false;
  EAGER_LIMIT = sweep_eager_limit;
  comm_set = in_comm_set;
}

//###################################################################
/**Check if buffer has been initialized.*/
void chi_mesh::SweepManagement::SweepBuffer::CheckInitialized()
{
  if (initialized) return;

  //============================================= Check angleset is complete
  if (angleset->angles.size() == 0)
  {
    chi_log.Log(LOG_ALLERROR)
    << "A call to SweepBuffer::Initialize() has been made without"
       " an initialized angleset.";
    exit(EXIT_FAILURE);
  }

  chi_mesh::SweepManagement::SPDS*  spds =  angleset->GetSPDS();
  chi_mesh::SweepManagement::FLUDS* fluds=  angleset->fluds;

  int num_grps   = angleset->GetNumGrps();
  int num_angles = angleset->angles.size();

  //============================================= Predecessor locations
  for (int prelocI=0; prelocI<spds->location_dependencies.size(); prelocI++)
  {
    u_ll_int num_unknowns =
      fluds->prelocI_face_dof_count[prelocI]*num_grps*num_angles;

    u_ll_int message_size  = num_unknowns;
    int      message_count = 1;
    if ((num_unknowns*8)<=EAGER_LIMIT)
    {
      message_count = num_angles;
      message_size  = ceil((double)num_unknowns/(double)message_count);
    }
    else
    {
      message_count = ceil((double)num_unknowns*8/(double)(double)EAGER_LIMIT);
      message_size  = ceil((double)num_unknowns/(double)message_count);
    }

    prelocI_message_count.push_back(message_count);
    prelocI_message_size.push_back(std::vector<u_ll_int>());
    prelocI_message_blockpos.push_back(std::vector<u_ll_int>());

    u_ll_int pre_block_pos = 0;
    for (int m=0; m<(message_count-1); m++)
    {
      prelocI_message_size[prelocI].push_back(message_size);
      prelocI_message_blockpos[prelocI].push_back(pre_block_pos);
      num_unknowns -= message_size;
      pre_block_pos += message_size;
    }
    if (num_unknowns>0)
    {
      prelocI_message_blockpos[prelocI].push_back(pre_block_pos);
      prelocI_message_size[prelocI].push_back(num_unknowns);
    }

    prelocI_message_available.push_back(std::vector<bool>(message_count,false));
  }

  //============================================= Delayed Predecessor locations
  for (int prelocI=0; prelocI<spds->delayed_location_dependencies.size(); prelocI++)
  {
    angleset->delayed_prelocI_norm.push_back(0.0);

    u_ll_int num_unknowns =
        fluds->delayed_prelocI_face_dof_count[prelocI]*num_grps*num_angles;

    u_ll_int message_size  = num_unknowns;
    int      message_count = 1;
    if ((num_unknowns*8)<=EAGER_LIMIT)
    {
      message_count = num_angles;
      message_size  = ceil((double)num_unknowns/(double)message_count);
    }
    else
    {
      message_count = ceil((double)num_unknowns*8/(double)(double)EAGER_LIMIT);
      message_size  = ceil((double)num_unknowns/(double)message_count);
    }

    delayed_prelocI_message_count.push_back(message_count);
    delayed_prelocI_message_size.push_back(std::vector<u_ll_int>());
    delayed_prelocI_message_blockpos.push_back(std::vector<u_ll_int>());

    u_ll_int pre_block_pos = 0;
    for (int m=0; m<(message_count-1); m++)
    {
      delayed_prelocI_message_size[prelocI].push_back(message_size);
      delayed_prelocI_message_blockpos[prelocI].push_back(pre_block_pos);
      num_unknowns -= message_size;
      pre_block_pos += message_size;
    }
    if (num_unknowns>0)
    {
      delayed_prelocI_message_blockpos[prelocI].push_back(pre_block_pos);
      delayed_prelocI_message_size[prelocI].push_back(num_unknowns);
    }

    delayed_prelocI_message_available.push_back(std::vector<bool>(message_count,false));
  }


  //============================================= Successor locations
  for (int deplocI=0; deplocI<spds->location_successors.size(); deplocI++)
  {
    u_ll_int num_unknowns =
      fluds->deplocI_face_dof_count[deplocI]*num_grps*num_angles;

    u_ll_int message_size  = num_unknowns;
    int      message_count = 1;
    if ((num_unknowns*8)<=EAGER_LIMIT)
    {
      message_count = num_angles;
      message_size  = ceil((double)num_unknowns/(double)message_count);
    }
    else
    {
      message_count = ceil((double)num_unknowns*8/(double)(double)EAGER_LIMIT);
      message_size  = ceil((double)num_unknowns/(double)message_count);
    }

    chi_global_timings[12] += num_unknowns;
    chi_global_timings[13] += 1.0;
    chi_global_timings[14] += message_count;
    chi_global_timings[15] += 1.0;

    deplocI_message_count.push_back(message_count);
    deplocI_message_size.push_back(std::vector<u_ll_int>());
    deplocI_message_blockpos.push_back(std::vector<u_ll_int>());

    u_ll_int dep_block_pos = 0;
    for (int m=0; m<(message_count-1); m++)
    {
      deplocI_message_size[deplocI].push_back(message_size);
      deplocI_message_blockpos[deplocI].push_back(dep_block_pos);
      num_unknowns -= message_size;
      dep_block_pos += message_size;
    }
    if (num_unknowns>0)
    {
      deplocI_message_blockpos[deplocI].push_back(dep_block_pos);
      deplocI_message_size[deplocI].push_back(num_unknowns);
    }

    deplocI_message_sent.push_back(std::vector<bool>(message_count,false));
    deplocI_message_request.push_back(
      std::vector<MPI_Request>(message_count,MPI_Request()));
  }

  angleset->fluds->SetReferencePsi(&angleset->local_psi,
                                   &angleset->deplocI_outgoing_psi,
                                   &angleset->prelocI_outgoing_psi,
                                   &angleset->boundryI_incoming_psi,
                                   &angleset->delayed_prelocI_outgoing_psi);

  initialized = true;
}

//###################################################################
/**Checks if data has been initialized and initializes it if not.*/
void chi_mesh::SweepManagement::SweepBuffer::
  InitializeBuffers()
{
  if (!data_initialized)
  {
    chi_mesh::SweepManagement::SPDS*  spds =  angleset->GetSPDS();
    chi_mesh::SweepManagement::FLUDS* fluds=  angleset->fluds;

    int num_grps   = angleset->GetNumGrps();
    int num_angles = angleset->angles.size();

    //============================ Resize FLUDS local outgoing Data
    angleset->local_psi.resize(fluds->local_psi_stride*
                               fluds->local_psi_max_elements*
                               num_grps*num_angles,0.0);

    //============================ Resize FLUDS non-local outgoing Data
    angleset->deplocI_outgoing_psi.resize(
      spds->location_successors.size(),std::vector<double>());
    for (int deplocI=0; deplocI<spds->location_successors.size(); deplocI++)
    {
      angleset->deplocI_outgoing_psi[deplocI].resize(
        fluds->deplocI_face_dof_count[deplocI]*num_grps*num_angles,0.0);
    }

    //================================================ Make a memory query
    double memory_mb = chi_console.GetMemoryUsageInMB();

    if (memory_mb>chi_global_timings[9])
      chi_global_timings[9] = memory_mb;

    chi_global_timings[10] += memory_mb;
    chi_global_timings[11] += 1.0;



    data_initialized = true;
  }
}

//###################################################################
/**Sends downstream psi.*/
void chi_mesh::SweepManagement::SweepBuffer::
  SendDownstreamPsi(int angle_set_num)
{
  chi_mesh::SweepManagement::SPDS*  spds =  angleset->GetSPDS();

  for (int deplocI=0; deplocI<spds->location_successors.size(); deplocI++)
  {
    int locJ              = spds->location_successors[deplocI];

    int num_mess = deplocI_message_count[deplocI];
    for (int m=0; m<num_mess; m++)
    {
      u_ll_int block_addr   = deplocI_message_blockpos[deplocI][m];
      u_ll_int message_size = deplocI_message_size[deplocI][m];

        MPI_Isend(&angleset->deplocI_outgoing_psi[deplocI].data()[block_addr],
                  message_size,
                  MPI_DOUBLE,
                  comm_set->MapIonJ(locJ,locJ),
                  10000*angle_set_num + 100*num_mess + m,   //tag
                  comm_set->communicators[locJ],
                  &deplocI_message_request[deplocI][m]);

        if (  ((10000*angle_set_num + 100*num_mess + m) == 84000) &&
              (chi_mpi.location_id == 1))
        {
          chi_log.Log(LOG_ALL)
          << "Tag: " << 10000*angle_set_num + 100*num_mess + m
          << " angle_set_num=" << angle_set_num
          << " num_mess=" << num_mess
          << " message=" << m
          << " message size=" << message_size;
        }
    }

  }


}

void chi_mesh::SweepManagement::SweepBuffer::
ReceiveDelayedData(int angle_set_num)
{
  chi_mesh::SweepManagement::SPDS*  spds =  angleset->GetSPDS();
  MPI_Barrier(MPI_COMM_WORLD);
  //======================================== Receive delayed data
  for (int prelocI=0; prelocI<spds->delayed_location_dependencies.size(); prelocI++)
  {
    int locJ = spds->delayed_location_dependencies[prelocI];

    std::vector<double> psi_old(angleset->delayed_prelocI_outgoing_psi[prelocI].size(),0.0);

    for (int k=0; k<psi_old.size(); k++)
      psi_old[k] = angleset->delayed_prelocI_outgoing_psi[prelocI][k];

    int num_mess = delayed_prelocI_message_count[prelocI];
    for (int m=0; m<num_mess; m++)
    {

      if (!delayed_prelocI_message_available[prelocI][m])
      {
        int msg_avail = 1;

        int comm_index = comm_set->MapIonJ(locJ,chi_mpi.location_id);

        MPI_Status status0;
        MPI_Iprobe(comm_set->MapIonJ(locJ,chi_mpi.location_id),
                   10000*angle_set_num + 100*num_mess + m, //tag
                   comm_set->communicators[chi_mpi.location_id],
                   &msg_avail,&status0);

        if (msg_avail != 1)
        {
//          ready_to_execute = false;
          chi_log.Log(LOG_ALL)
            << "SweepBuffer: Delayed Data message was not available";
//          break;
        }//if message is not available

        //============================ Receive upstream data
        u_ll_int block_addr   = delayed_prelocI_message_blockpos[prelocI][m];
        u_ll_int message_size = delayed_prelocI_message_size[prelocI][m];

        MPI_Status status;
        int error_code = MPI_Recv(&angleset->delayed_prelocI_outgoing_psi[prelocI].data()[block_addr],
                 message_size,
                 MPI_DOUBLE,
                 comm_set->MapIonJ(locJ,chi_mpi.location_id),
                 10000*angle_set_num + 100*num_mess + m, //tag
                 comm_set->communicators[chi_mpi.location_id],
                 &status);

        int num = MPI_Get_count(&status,MPI_DOUBLE,&num);

        if (error_code != MPI_SUCCESS)
        {
          std::stringstream err_stream;
          err_stream << "################# Delayed receive error."
                     << " message size=" << message_size
                     << " as_num=" << angle_set_num
                     << " num_mess=" << num_mess
                     << " m=" << m
                     << " error=" << status.MPI_ERROR
                     << " size=" << num << "\n";
          char error_string[BUFSIZ];
          int length_of_error_string, error_class;
          MPI_Error_class(error_code, &error_class);
          MPI_Error_string(error_class, error_string, &length_of_error_string);
          err_stream << error_string << "\n";
          MPI_Error_string(error_code, error_string, &length_of_error_string);
          err_stream << error_string << "\n";
          chi_log.Log(LOG_ALLWARNING) << err_stream.str();
        }

      }//if not message already received
    }//for message

    double rel_change = 0.0;
    for (int k=0; k<psi_old.size(); k++)
    {
      double psi_new = angleset->delayed_prelocI_outgoing_psi[prelocI][k];
      if (std::fabs(psi_new) >= std::numeric_limits<double>::min())
      {
        double max_change =
            std::fabs(psi_new - psi_old[k])/std::fabs(psi_new);
        rel_change = std::max(max_change,rel_change);
      }
    }
    angleset->delayed_prelocI_norm[prelocI] = rel_change;
  }//for delayed predecessor
}

//###################################################################
/**Sends downstream psi.*/
void chi_mesh::SweepManagement::SweepBuffer::
 CheckDownstreamBuffersClear()
{
  if (done_sending) return;

  chi_mesh::SweepManagement::SPDS*  spds =  angleset->GetSPDS();

  done_sending = true;
  for (int deplocI=0; deplocI<spds->location_successors.size(); deplocI++)
  {
    int locJ              = spds->location_successors[deplocI];

    int num_mess = deplocI_message_count[deplocI];
    for (int m=0; m<num_mess; m++)
    {
      int  send_request_status = 1;
      MPI_Test(&deplocI_message_request[deplocI][m],
               &send_request_status,MPI_STATUS_IGNORE);
      if (send_request_status == 0) done_sending = false;
    }

  }

  if (done_sending)
  {
    for (int deplocI=0; deplocI<spds->location_successors.size(); deplocI++)
    {
      angleset->deplocI_outgoing_psi[deplocI].clear();
      angleset->deplocI_outgoing_psi[deplocI].shrink_to_fit();
    }
  }
}


//###################################################################
/**Check if all upstream dependencies have been met.*/
bool chi_mesh::SweepManagement::SweepBuffer::
CheckUpstreamPsiAvailable(int angle_set_num)
{
  chi_mesh::SweepManagement::SPDS*  spds =  angleset->GetSPDS();
  chi_mesh::SweepManagement::FLUDS* fluds=  angleset->fluds;

  int num_grps   = angleset->GetNumGrps();
  int num_angles = angleset->angles.size();

  //============================ Resize FLUDS non-local incoming Data
  if (!upstream_data_initialized)
  {
    angleset->prelocI_outgoing_psi.resize(
      spds->location_dependencies.size(),std::vector<double>());
    for (int prelocI=0; prelocI<spds->location_dependencies.size(); prelocI++)
    {
      angleset->prelocI_outgoing_psi[prelocI].resize(
        fluds->prelocI_face_dof_count[prelocI]*num_grps*num_angles,0.0);
    }

    upstream_data_initialized = true;
  }
  bool ready_to_execute = true;

  for (int prelocI=0; prelocI<spds->location_dependencies.size(); prelocI++)
  {
    int locJ = spds->location_dependencies[prelocI];

    int num_mess = prelocI_message_count[prelocI];
    for (int m=0; m<num_mess; m++)
    {

      if (!prelocI_message_available[prelocI][m])
      {
        int msg_avail = 1;

        MPI_Iprobe(comm_set->MapIonJ(locJ,chi_mpi.location_id),
                   10000*angle_set_num + 100*num_mess + m, //tag
                   comm_set->communicators[chi_mpi.location_id],
                   &msg_avail,MPI_STATUS_IGNORE);

        if (msg_avail != 1)
        {
          ready_to_execute = false;
          break;
        }//if message is not available
        //============================ Receive upstream data
        else
        {
          prelocI_message_available[prelocI][m] = true;

          u_ll_int block_addr   = prelocI_message_blockpos[prelocI][m];
          u_ll_int message_size = prelocI_message_size[prelocI][m];

          int error_code = MPI_Recv(&angleset->prelocI_outgoing_psi[prelocI].data()[block_addr],
                   message_size,
                   MPI_DOUBLE,
                   comm_set->MapIonJ(locJ,chi_mpi.location_id),
                   10000*angle_set_num + 100*num_mess + m, //tag
                   comm_set->communicators[chi_mpi.location_id],
                   MPI_STATUS_IGNORE);

          if (error_code != MPI_SUCCESS)
          {
            std::stringstream err_stream;
            err_stream << "################# Delayed receive error."
                       << " message size=" << message_size
                       << " as_num=" << angle_set_num
                       << " num_mess=" << num_mess
                       << " m=" << m
                       << " error="
                       << " size=\n";
            char error_string[BUFSIZ];
            int length_of_error_string, error_class;
            MPI_Error_class(error_code, &error_class);
            MPI_Error_string(error_class, error_string, &length_of_error_string);
            err_stream << error_string << "\n";
            MPI_Error_string(error_code, error_string, &length_of_error_string);
            err_stream << error_string << "\n";
            chi_log.Log(LOG_ALLWARNING) << err_stream.str();
          }
        }
      }//if not message already received
    }//for message

    if (!ready_to_execute) break;
  }//for predecessor

  return ready_to_execute;
}


//###################################################################
/**Receive all upstream Psi.*/
void chi_mesh::SweepManagement::SweepBuffer::
  ClearReceiveBuffers()
{
  chi_mesh::SweepManagement::SPDS*  spds =  angleset->GetSPDS();

  angleset->local_psi.clear();
  angleset->local_psi.shrink_to_fit();
  //Clear receive buffers
  for (int prelocI=0; prelocI<spds->location_dependencies.size(); prelocI++)
  {
    angleset->prelocI_outgoing_psi.clear();
    angleset->prelocI_outgoing_psi.shrink_to_fit();
  }
}