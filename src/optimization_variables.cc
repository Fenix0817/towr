/*
 * optimization_variables.cc
 *
 *  Created on: May 24, 2016
 *      Author: winklera
 */

#include <xpp/zmp/optimization_variables.h>

namespace xpp {
namespace zmp {

OptimizationVariables::OptimizationVariables ()
{
}

OptimizationVariables::~OptimizationVariables ()
{
}

OptimizationVariables::VectorXd
OptimizationVariables::GetVariables (std::string id) const
{
  assert(initialized_);
  return nlp_structure_.GetVariables(id);
}

void
OptimizationVariables::SetVariables (std::string id, const VectorXd& values)
{
  assert(initialized_);
  nlp_structure_.SetVariables(id, values);
}

NlpStructure::VariableSetVector
OptimizationVariables::GetVarSets () const
{
  return nlp_structure_.GetVariableSets();
}

void
OptimizationVariables::AddVariableSet (std::string id, const VectorXd& values)
{
  nlp_structure_.AddVariableSet(id, values.rows());
  SetVariables(id, values);
  initialized_ = true;
}

//void
//OptimizationVariables::Init (int n_spline_coeff, int n_steps)
//{
//  nlp_structure_.Reset();
//  nlp_structure_.AddVariableSet(kSplineCoff, n_spline_coeff);
//  nlp_structure_.AddVariableSet(kFootholds, kDim2d*n_steps);
//  initialized_ = true;
//
//  NotifyObservers();
//}
//
//void
//OptimizationVariables::Init (const VectorXd& x_coeff_abcd,
//                             const StdVecEigen2d& footholds)
//{
//  Init(x_coeff_abcd.rows(), footholds.size());
//
//  nlp_structure_.SetVariables(kSplineCoff, x_coeff_abcd);
//  nlp_structure_.SetVariables(kFootholds, ConvertStdToEig(footholds));
//  NotifyObservers();
//}

void
OptimizationVariables::SetVariables(const VectorXd& x)
{
  assert(initialized_);
  nlp_structure_.SetAllVariables(x);
  NotifyObservers();
}

//void
//OptimizationVariables::SetSplineCoefficients (const VectorXd& x)
//{
//  nlp_structure_.SetVariables("SplineCoff", x);
//  NotifyObservers();
//}

OptimizationVariables::VectorXd
OptimizationVariables::GetOptimizationVariables () const
{
  return nlp_structure_.GetAllOptimizationVariables();
}

OptimizationVariables::VecBound
OptimizationVariables::GetOptimizationVariableBounds () const
{
  return nlp_structure_.GetAllBounds();
}

int
OptimizationVariables::GetOptimizationVariableCount () const
{
  assert(initialized_);
  return nlp_structure_.GetOptimizationVariableCount();
}

//OptimizationVariables::StdVecEigen2d
//OptimizationVariables::GetFootholdsStd () const
//{
//  assert(initialized_);
//  Eigen::VectorXd footholds_xy = nlp_structure_.GetVariables(kFootholds);
//  return utils::ConvertEigToStd(footholds_xy);
//}

//OptimizationVariables::VectorXd
//OptimizationVariables::GetSplineCoefficients () const
//{
//  assert(initialized_);
//  return nlp_structure_.GetVariables("SplineCoff");
//}


} /* namespace zmp */
} /* namespace xpp */

