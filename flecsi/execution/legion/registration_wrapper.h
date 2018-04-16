/*
    @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
   /@@/////  /@@          @@////@@ @@////// /@@
   /@@       /@@  @@@@@  @@    // /@@       /@@
   /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
   /@@////   /@@/@@@@@@@/@@       ////////@@/@@
   /@@       /@@/@@//// //@@    @@       /@@/@@
   /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
   //       ///  //////   //////  ////////  //

   Copyright (c) 2016, Los Alamos National Security, LLC
   All rights reserved.
                                                                              */
#pragma once

/*! @file */

#include <flecsi-config.h>

#if !defined(FLECSI_ENABLE_LEGION)
#error FLECSI_ENABLE_LEGION not defined! This file depends on Legion!
#endif

#include <legion.h>

namespace flecsi {
namespace execution {

/*!
 The registration_wrapper__ type selects between void and non-void
 return values for task registration.

 Reduction task specialization

 @tparam RETURN The return type of the task.
 @tparam TASK   The function pointer template type of the task.
 @tparam REDUCTION  The reduction ID

 @ingroup legion-execution
 */

template<
    typename RETURN,
    RETURN (*TASK)(
        const Legion::Task *,
        const std::vector<Legion::PhysicalRegion> &,
        Legion::Context,
        Legion::Runtime *),
	size_t REDUCTION>
struct registration_wrapper__ {

  /*!
   This method registers the given task with the Legion runtime.
  
   @tparam ARGS The variadic argument pack.
   */

  static void register_task(
      const Legion::TaskID tid,
      const Legion::Processor::Kind & processor,
      const Legion::TaskConfigOptions config_options,
      std::string & task_name) {

    {
      Legion::TaskVariantRegistrar registrar(tid, task_name.c_str());
      registrar.add_constraint(Legion::ProcessorConstraint(processor));
      registrar.set_leaf(config_options.leaf);
      registrar.set_inner(config_options.inner);
      registrar.set_idempotent(config_options.idempotent);
      Legion::Runtime::preregister_task_variant<RETURN, TASK>(
          registrar, task_name.c_str());
    } // scope

  } // register_task
}; // struct registration_wrapper__

/*!
 Partial specialization for the registration_wrapper__ type struct for the case
 when reduction ID=0 (non-reduction task) 
 return values for task registration.

 @tparam RETURN The return type of the task.
 @tparam TASK   The function pointer template type of the task.

 @ingroup legion-execution
 */

template<
    typename RETURN,
    RETURN (*TASK)(
        const Legion::Task *,
        const std::vector<Legion::PhysicalRegion> &,
        Legion::Context,
        Legion::Runtime *)>
struct registration_wrapper__<RETURN, TASK, 0> {

  /*!
    This method registers the given task with the Legion runtime.
      
    @tparam ARGS The variadic argument pack.
   */

  static void register_task(
      const Legion::TaskID tid,
      const Legion::Processor::Kind & processor,
      const Legion::TaskConfigOptions config_options,
      std::string & task_name) {

    {
      Legion::TaskVariantRegistrar registrar(tid, task_name.c_str());
      registrar.add_constraint(Legion::ProcessorConstraint(processor));
      registrar.set_leaf(config_options.leaf);
      registrar.set_inner(config_options.inner);
      registrar.set_idempotent(config_options.idempotent);
      std::vector<Legion::DimensionKind> ordering;
      ordering.push_back(Legion::DimensionKind::DIM_Y);
      ordering.push_back(Legion::DimensionKind::DIM_X);
      ordering.push_back(Legion::DimensionKind::DIM_F);  // SOA
      Legion::OrderingConstraint ordering_constraint(ordering, true /*contiguous*/);
      Legion::LayoutConstraintRegistrar layout_constraint;
      layout_constraint.add_constraint(ordering_constraint);
for (int i =0 ;i<24; i++)
      registrar.add_layout_constraint_set(i, Legion::Runtime::preregister_layout(layout_constraint));
      Legion::Runtime::preregister_task_variant<RETURN, TASK>(
          registrar, task_name.c_str());
    } // scope

  } // register_task
}; // struct registration_wrapper__


/*!
 Partial specialization of registration_wrapper__ for void return type.

 @tparam TASK   The function pointer template type of the task.
 @tparam REDUCTION  The reduction ID

 @ingroup legion-execution
 */

template<void (*TASK)(
    const Legion::Task *,
    const std::vector<Legion::PhysicalRegion> &,
    Legion::Context,
    Legion::Runtime *),
    size_t REDUCTION>
struct registration_wrapper__<void, TASK, REDUCTION> {

  static void register_task(
      const Legion::TaskID tid,
      const Legion::Processor::Kind & processor,
      const Legion::TaskConfigOptions config_options,
      std::string & task_name) {

    {
      Legion::TaskVariantRegistrar registrar(tid, task_name.c_str());
      registrar.add_constraint(Legion::ProcessorConstraint(processor));
      registrar.set_leaf(config_options.leaf);
      registrar.set_inner(config_options.inner);
      registrar.set_idempotent(config_options.idempotent);
      Legion::Runtime::preregister_task_variant<TASK>(
          registrar, task_name.c_str());
    } // scope

  } // register_task
}; // struct registration_wrapper__


/*!
 Partial specialization of registration_wrapper__ for void return type
 and reduction ID = 0 (non-reduction task)

 @tparam TASK   The function pointer template type of the task.

 @ingroup legion-execution
 */

template<void (*TASK)(
    const Legion::Task *,
    const std::vector<Legion::PhysicalRegion> &,
    Legion::Context,
    Legion::Runtime *)>
struct registration_wrapper__<void, TASK, 0> {

  static void register_task(
      const Legion::TaskID tid,
      const Legion::Processor::Kind & processor,
      const Legion::TaskConfigOptions config_options,
      std::string & task_name) {

    {
      Legion::TaskVariantRegistrar registrar(tid, task_name.c_str());
      registrar.add_constraint(Legion::ProcessorConstraint(processor));
      registrar.set_leaf(config_options.leaf);
      registrar.set_inner(config_options.inner);
      registrar.set_idempotent(config_options.idempotent);
       std::vector<Legion::DimensionKind> ordering;
      ordering.push_back(Legion::DimensionKind::DIM_Y);
      ordering.push_back(Legion::DimensionKind::DIM_X);
      ordering.push_back(Legion::DimensionKind::DIM_F);  // SOA
      Legion::OrderingConstraint ordering_constraint(ordering, true /*contiguous*/);
      Legion::LayoutConstraintRegistrar layout_constraint;
      layout_constraint.add_constraint(ordering_constraint);
for (int i =0 ;i<24; i++)
      registrar.add_layout_constraint_set(i, Legion::Runtime::preregister_layout(layout_constraint));

      Legion::Runtime::preregister_task_variant<TASK>(
          registrar, task_name.c_str());
    } // scope

  } // register_task
}; // struct registration_wrapper__


} // namespace execution
} // namespace flecsi
