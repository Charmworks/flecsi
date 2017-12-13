/*~--------------------------------------------------------------------------~*
 *~--------------------------------------------------------------------------~*/

#pragma once

#include "flecsi/data/common/data_types.h"

//----------------------------------------------------------------------------//
/// @file
/// @date Initial file creation: Apr 04, 2017
//----------------------------------------------------------------------------//

namespace flecsi {

//----------------------------------------------------------------------------//
//! The mpi_mutator_handle_policy_t type provides backend storage for
//! interfacing to the Legion runtime.
//!
//! @ingroup data
//----------------------------------------------------------------------------//

struct mpi_mutator_handle_policy_t
{
  using offset_t = data::sparse_data_offset_t;

  mpi_mutator_handle_policy_t(){}

  mpi_mutator_handle_policy_t(const mpi_mutator_handle_policy_t& p) = default;

  field_id_t fid;
  size_t index_space;
  size_t data_client_hash;

  std::vector<offset_t>* offsets;
  std::vector<uint8_t>* entries;
  size_t* reserve;
  size_t reserve_chunk;
  size_t* num_exclusive_entries;
}; // class mpi_mutator_handle_policy_t

} // namespace flecsi

/*~-------------------------------------------------------------------------~-*
*~-------------------------------------------------------------------------~-*/
