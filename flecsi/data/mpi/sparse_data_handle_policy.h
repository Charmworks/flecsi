/*~--------------------------------------------------------------------------~*
 *~--------------------------------------------------------------------------~*/

#pragma once

//----------------------------------------------------------------------------//
//! @file
//! @date Initial file creation: Apr 04, 2017
//----------------------------------------------------------------------------//

namespace flecsi {

//----------------------------------------------------------------------------//

struct mpi_sparse_data_handle_policy_t
{
  // +++ The following fields are set in get_handle(), using
  // information from the context which has data that is the same
  // across multiple ranks/colors and should be used ONLY as read-only data
  field_id_t fid;
 
  size_t exclusive_reserve;
  size_t max_entries_per_index;
}; // class mpi_sparse_data_handle_policy_t

} // namespace flecsi

/*~-------------------------------------------------------------------------~-*
*~-------------------------------------------------------------------------~-*/
