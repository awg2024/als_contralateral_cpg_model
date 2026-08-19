
/*
 *  aeif_cond_beta_nestml.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Generated from NESTML 8.3.0 at time: 2026-08-13 15:07:45.125167
**/

// C++ includes:
#include <limits>

// Includes from libnestutil:
#include "numerics.h"

// Includes from nestkernel:
#include "exceptions.h"
#include "kernel_manager.h"
#include "nest_impl.h"
#include "universal_data_logger_impl.h"

#include "aeif_cond_beta_nestml.h"
void
register_aeif_cond_beta_nestml( const std::string& name )
{
  nest::register_node_model< aeif_cond_beta_nestml >( name );
}

// ---------------------------------------------------------------------------
//   Recordables map
// ---------------------------------------------------------------------------
nest::RecordablesMap<aeif_cond_beta_nestml> aeif_cond_beta_nestml::recordablesMap_;
namespace nest
{
  // Override the create() method with one call to RecordablesMap::insert_() for each quantity to be recorded.
template <> void RecordablesMap<aeif_cond_beta_nestml>::create()
  {
    // add state variables to recordables map
    // add state variables to recordables map
    insert_(aeif_cond_beta_nestml_names::_V_m, &aeif_cond_beta_nestml::get_V_m);
    insert_(aeif_cond_beta_nestml_names::_w, &aeif_cond_beta_nestml::get_w);
    insert_(aeif_cond_beta_nestml_names::_g_in__X__inh_spikes, &aeif_cond_beta_nestml::get_g_in__X__inh_spikes);
    insert_(aeif_cond_beta_nestml_names::_g_in__DOLLAR__X__inh_spikes, &aeif_cond_beta_nestml::get_g_in__DOLLAR__X__inh_spikes);
    insert_(aeif_cond_beta_nestml_names::_g_ex__X__exc_spikes, &aeif_cond_beta_nestml::get_g_ex__X__exc_spikes);
    insert_(aeif_cond_beta_nestml_names::_g_ex__DOLLAR__X__exc_spikes, &aeif_cond_beta_nestml::get_g_ex__DOLLAR__X__exc_spikes);
  }
}
std::vector< std::tuple< int, int > > aeif_cond_beta_nestml::rport_to_nestml_buffer_idx =
{
  
  { aeif_cond_beta_nestml::EXC_SPIKES, aeif_cond_beta_nestml::INH_SPIKES },
};

// ---------------------------------------------------------------------------
//   Default constructors defining default parameters and state
//   Note: the implementation is empty. The initialization is of variables
//   is a part of aeif_cond_beta_nestml's constructor.
// ---------------------------------------------------------------------------

aeif_cond_beta_nestml::Parameters_::Parameters_()
{
}

aeif_cond_beta_nestml::State_::State_()
{
}

// ---------------------------------------------------------------------------
//   Parameter and state extractions and manipulation functions
// ---------------------------------------------------------------------------

aeif_cond_beta_nestml::Buffers_::Buffers_(aeif_cond_beta_nestml &n):
  logger_(n)
  , spike_inputs_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_inputs_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , continuous_inputs_( std::vector< nest::RingBuffer >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , continuous_inputs_grid_sum_( std::vector< double >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , __s( nullptr ), __c( nullptr ), __e( nullptr )
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

aeif_cond_beta_nestml::Buffers_::Buffers_(const Buffers_ &, aeif_cond_beta_nestml &n):
  logger_(n)
  , spike_inputs_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_inputs_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , continuous_inputs_( std::vector< nest::RingBuffer >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , continuous_inputs_grid_sum_( std::vector< double >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , __s( nullptr ), __c( nullptr ), __e( nullptr )
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

// ---------------------------------------------------------------------------
//   Default constructor for node
// ---------------------------------------------------------------------------

aeif_cond_beta_nestml::aeif_cond_beta_nestml():StructuralPlasticityNode(), P_(), S_(), B_(*this)
{
  init_state_internal_();
  recordablesMap_.create();
  pre_run_hook();
}

// ---------------------------------------------------------------------------
//   Copy constructor for node
// ---------------------------------------------------------------------------

aeif_cond_beta_nestml::aeif_cond_beta_nestml(const aeif_cond_beta_nestml& __n):
  StructuralPlasticityNode(), P_(__n.P_), S_(__n.S_), B_(__n.B_, *this)
{
  // copy parameter struct P_
  P_.C_m = __n.P_.C_m;
  P_.t_ref = __n.P_.t_ref;
  P_.V_reset = __n.P_.V_reset;
  P_.g_L = __n.P_.g_L;
  P_.E_L = __n.P_.E_L;
  P_.a = __n.P_.a;
  P_.b = __n.P_.b;
  P_.Delta_T = __n.P_.Delta_T;
  P_.tau_w = __n.P_.tau_w;
  P_.V_th = __n.P_.V_th;
  P_.V_peak = __n.P_.V_peak;
  P_.E_exc = __n.P_.E_exc;
  P_.E_inh = __n.P_.E_inh;
  P_.tau_syn_rise_I = __n.P_.tau_syn_rise_I;
  P_.tau_syn_decay_I = __n.P_.tau_syn_decay_I;
  P_.tau_syn_rise_E = __n.P_.tau_syn_rise_E;
  P_.tau_syn_decay_E = __n.P_.tau_syn_decay_E;
  P_.I_e = __n.P_.I_e;

  // copy state struct S_
  S_.ode_state[State_::V_m] = __n.S_.ode_state[State_::V_m];
  S_.ode_state[State_::w] = __n.S_.ode_state[State_::w];
  S_.r = __n.S_.r;
  S_.ode_state[State_::g_in__X__inh_spikes] = __n.S_.ode_state[State_::g_in__X__inh_spikes];
  S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes] = __n.S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes];
  S_.ode_state[State_::g_ex__X__exc_spikes] = __n.S_.ode_state[State_::g_ex__X__exc_spikes];
  S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes] = __n.S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes];

  // copy internals V_
  V_.t_peak_E = __n.V_.t_peak_E;
  V_.__h = __n.V_.__h;
  V_.t_peak_I = __n.V_.t_peak_I;
  V_.g_E_const = __n.V_.g_E_const;
  V_.g_I_const = __n.V_.g_I_const;
  V_.RefractoryCounts = __n.V_.RefractoryCounts;
  V_.__P__g_in__X__inh_spikes__g_in__X__inh_spikes = __n.V_.__P__g_in__X__inh_spikes__g_in__X__inh_spikes;
  V_.__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes = __n.V_.__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes;
  V_.__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes = __n.V_.__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes;
  V_.__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes = __n.V_.__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes;
  V_.__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes = __n.V_.__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes;
  V_.__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes = __n.V_.__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes;
}

// ---------------------------------------------------------------------------
//   Destructor for node
// ---------------------------------------------------------------------------

aeif_cond_beta_nestml::~aeif_cond_beta_nestml()
{
  // GSL structs may not have been allocated, so we need to protect destruction

  if (B_.__s)
  {
    gsl_odeiv_step_free( B_.__s );
  }

  if (B_.__c)
  {
    gsl_odeiv_control_free( B_.__c );
  }

  if (B_.__e)
  {
    gsl_odeiv_evolve_free( B_.__e );
  }
}

// ---------------------------------------------------------------------------
//   Node initialization functions
// ---------------------------------------------------------------------------
void aeif_cond_beta_nestml::calibrate_time( const nest::TimeConverter& tc )
{
  LOG( nest::VerbosityLevel::WARNING,
    "aeif_cond_beta_nestml",
    "Simulation resolution has changed. Internal state and parameters of the model have been reset!" );

  init_state_internal_();
}
void aeif_cond_beta_nestml::init_state_internal_()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] aeif_cond_beta_nestml::init_state_internal_()" << std::endl;
#endif

  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function
  // by default, integrate all variables with a conservative tolerance, in the sense that we err on the side of integrating very precisely at the expense of extra computation
  P_.__gsl_abs_error_tol = 1e-6;
  P_.__gsl_rel_error_tol = 1e-6;
  // initial values for parameters
  P_.C_m = 281.0; // as pF
  P_.t_ref = 0.0; // as ms
  P_.V_reset = (-60.0); // as mV
  P_.g_L = 30.0; // as nS
  P_.E_L = (-70.6); // as mV
  P_.a = 4; // as nS
  P_.b = 80.5; // as pA
  P_.Delta_T = 2.0; // as mV
  P_.tau_w = 144.0; // as ms
  P_.V_th = (-50.4); // as mV
  P_.V_peak = 0; // as mV
  P_.E_exc = 0; // as mV
  P_.E_inh = (-85.0); // as mV
  P_.tau_syn_rise_I = 0.2; // as ms
  P_.tau_syn_decay_I = 2; // as ms
  P_.tau_syn_rise_E = 0.2; // as ms
  P_.tau_syn_decay_E = 2; // as ms
  P_.I_e = 0; // as pA

  V_.__h = nest::Time::get_resolution().get_ms();
  recompute_internal_variables();
  // initial values for state variables
  S_.ode_state[State_::V_m] = P_.E_L; // as mV
  S_.ode_state[State_::w] = 0; // as pA
  S_.r = 0; // as integer
  S_.ode_state[State_::g_in__X__inh_spikes] = 0; // as real
  S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes] = 0; // as real
  S_.ode_state[State_::g_ex__X__exc_spikes] = 0; // as real
  S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes] = 0; // as real
}

void aeif_cond_beta_nestml::init_buffers_()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] aeif_cond_beta_nestml::init_buffers_()" << std::endl;
#endif
  // spike input buffers
  get_spike_inputs_().clear();
  get_spike_inputs_grid_sum_().clear();
  get_spike_input_received_().clear();
  get_spike_input_received_grid_sum_().clear();
  get_continuous_inputs_().clear();
  get_continuous_inputs_grid_sum_().clear();


  B_.logger_.reset();



  if ( not B_.__s )
  {
    B_.__s = gsl_odeiv_step_alloc( gsl_odeiv_step_rkf45, State_::STATE_VEC_SIZE );
  }
  else
  {
    gsl_odeiv_step_reset( B_.__s );
  }

  if ( not B_.__c )
  {
    B_.__c = gsl_odeiv_control_y_new( P_.__gsl_abs_error_tol, P_.__gsl_rel_error_tol );
  }
  else
  {
    gsl_odeiv_control_init( B_.__c, P_.__gsl_abs_error_tol, P_.__gsl_rel_error_tol, 1.0, 0.0 );

  }

  if ( not B_.__e )
  {
    B_.__e = gsl_odeiv_evolve_alloc( State_::STATE_VEC_SIZE );
  }
  else
  {
    gsl_odeiv_evolve_reset( B_.__e );
  }

  // B_.__sys.function = aeif_cond_beta_nestml_dynamics; // will be set just prior to the call to gsl_odeiv_evolve_apply()
  B_.__sys.jacobian = nullptr;
  B_.__sys.dimension = State_::STATE_VEC_SIZE;
  B_.__sys.params = reinterpret_cast< void* >( this );
  B_.__step = nest::Time::get_resolution().get_ms();
  B_.__integration_step = nest::Time::get_resolution().get_ms();
}

void aeif_cond_beta_nestml::recompute_internal_variables(bool exclude_timestep)
{
  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function

  if (exclude_timestep)
  {    
    V_.t_peak_E = P_.tau_syn_decay_E * P_.tau_syn_rise_E * std::log(P_.tau_syn_decay_E / P_.tau_syn_rise_E) / (P_.tau_syn_decay_E - P_.tau_syn_rise_E); // as real
    V_.t_peak_I = P_.tau_syn_decay_I * P_.tau_syn_rise_I * std::log(P_.tau_syn_decay_I / P_.tau_syn_rise_I) / (P_.tau_syn_decay_I - P_.tau_syn_rise_I); // as real
    V_.g_E_const = 1 / (std::exp((-V_.t_peak_E) / P_.tau_syn_decay_E) - std::exp((-V_.t_peak_E) / P_.tau_syn_rise_E)); // as real
    V_.g_I_const = 1 / (std::exp((-V_.t_peak_I) / P_.tau_syn_decay_I) - std::exp((-V_.t_peak_I) / P_.tau_syn_rise_I)); // as real
    V_.RefractoryCounts = nest::Time(nest::Time::ms((double) (P_.t_ref))).get_steps(); // as integer
    V_.__P__g_in__X__inh_spikes__g_in__X__inh_spikes = std::exp((-V_.__h) / P_.tau_syn_rise_I); // as real
    V_.__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes = (-P_.tau_syn_decay_I) * P_.tau_syn_rise_I * std::exp((-V_.__h) / P_.tau_syn_rise_I) / (P_.tau_syn_decay_I - P_.tau_syn_rise_I) + P_.tau_syn_decay_I * P_.tau_syn_rise_I * std::exp((-V_.__h) / P_.tau_syn_decay_I) / (P_.tau_syn_decay_I - P_.tau_syn_rise_I); // as real
    V_.__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes = std::exp((-V_.__h) / P_.tau_syn_decay_I); // as real
    V_.__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes = std::exp((-V_.__h) / P_.tau_syn_rise_E); // as real
    V_.__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes = (-P_.tau_syn_decay_E) * P_.tau_syn_rise_E * std::exp((-V_.__h) / P_.tau_syn_rise_E) / (P_.tau_syn_decay_E - P_.tau_syn_rise_E) + P_.tau_syn_decay_E * P_.tau_syn_rise_E * std::exp((-V_.__h) / P_.tau_syn_decay_E) / (P_.tau_syn_decay_E - P_.tau_syn_rise_E); // as real
    V_.__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes = std::exp((-V_.__h) / P_.tau_syn_decay_E); // as real
  }
  else {    
    V_.t_peak_E = P_.tau_syn_decay_E * P_.tau_syn_rise_E * std::log(P_.tau_syn_decay_E / P_.tau_syn_rise_E) / (P_.tau_syn_decay_E - P_.tau_syn_rise_E); // as real
    V_.__h = nest::Time::get_resolution().get_ms(); // as ms
    V_.t_peak_I = P_.tau_syn_decay_I * P_.tau_syn_rise_I * std::log(P_.tau_syn_decay_I / P_.tau_syn_rise_I) / (P_.tau_syn_decay_I - P_.tau_syn_rise_I); // as real
    V_.g_E_const = 1 / (std::exp((-V_.t_peak_E) / P_.tau_syn_decay_E) - std::exp((-V_.t_peak_E) / P_.tau_syn_rise_E)); // as real
    V_.g_I_const = 1 / (std::exp((-V_.t_peak_I) / P_.tau_syn_decay_I) - std::exp((-V_.t_peak_I) / P_.tau_syn_rise_I)); // as real
    V_.RefractoryCounts = nest::Time(nest::Time::ms((double) (P_.t_ref))).get_steps(); // as integer
    V_.__P__g_in__X__inh_spikes__g_in__X__inh_spikes = std::exp((-V_.__h) / P_.tau_syn_rise_I); // as real
    V_.__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes = (-P_.tau_syn_decay_I) * P_.tau_syn_rise_I * std::exp((-V_.__h) / P_.tau_syn_rise_I) / (P_.tau_syn_decay_I - P_.tau_syn_rise_I) + P_.tau_syn_decay_I * P_.tau_syn_rise_I * std::exp((-V_.__h) / P_.tau_syn_decay_I) / (P_.tau_syn_decay_I - P_.tau_syn_rise_I); // as real
    V_.__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes = std::exp((-V_.__h) / P_.tau_syn_decay_I); // as real
    V_.__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes = std::exp((-V_.__h) / P_.tau_syn_rise_E); // as real
    V_.__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes = (-P_.tau_syn_decay_E) * P_.tau_syn_rise_E * std::exp((-V_.__h) / P_.tau_syn_rise_E) / (P_.tau_syn_decay_E - P_.tau_syn_rise_E) + P_.tau_syn_decay_E * P_.tau_syn_rise_E * std::exp((-V_.__h) / P_.tau_syn_decay_E) / (P_.tau_syn_decay_E - P_.tau_syn_rise_E); // as real
    V_.__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes = std::exp((-V_.__h) / P_.tau_syn_decay_E); // as real
  }
}
void aeif_cond_beta_nestml::pre_run_hook()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] aeif_cond_beta_nestml::pre_run_hook()" << std::endl;
#endif

  B_.logger_.init();

  // parameters might have changed -- recompute internals
  V_.__h = nest::Time::get_resolution().get_ms();
  recompute_internal_variables();

  // buffers B_
  B_.spike_inputs_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_inputs_grid_sum_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_input_received_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_input_received_grid_sum_.resize(NUM_SPIKE_RECEPTORS);
  B_.continuous_inputs_.resize(NUM_CONTINUOUS_INPUT_PORTS);
  B_.continuous_inputs_grid_sum_.resize(NUM_CONTINUOUS_INPUT_PORTS);

}

// ---------------------------------------------------------------------------
//   Update and spike handling functions
// ---------------------------------------------------------------------------


extern "C" inline int aeif_cond_beta_nestml_dynamics(double __time, const double ode_state[], double f[], void* pnode)
{
  typedef aeif_cond_beta_nestml::State_ State_;
   // get access to node so we can almost work as in a member function
  assert( pnode );
  const aeif_cond_beta_nestml& node = *( reinterpret_cast< aeif_cond_beta_nestml* >( pnode ) );
  constexpr int I_STIM = aeif_cond_beta_nestml::I_STIM;
  // ode_state[] here is---and must be---the state vector supplied by the integrator,
  // not the state vector in the node, node.S_.ode_state[].

  f[State_::V_m] = (node.P_.Delta_T * node.P_.g_L * std::exp(((-node.P_.V_th) + std::min(ode_state[State_::V_m], node.P_.V_peak)) / node.P_.Delta_T) + node.P_.I_e + node.B_.continuous_inputs_grid_sum_[I_STIM] - node.P_.g_L * ((-node.P_.E_L) + std::min(ode_state[State_::V_m], node.P_.V_peak)) - 1. * ode_state[State_::g_ex__X__exc_spikes] * ((-node.P_.E_exc) + std::min(ode_state[State_::V_m], node.P_.V_peak)) - 1. * ode_state[State_::g_in__X__inh_spikes] * ((-node.P_.E_inh) + std::min(ode_state[State_::V_m], node.P_.V_peak)) - ode_state[State_::w]) / node.P_.C_m;
  f[State_::w] = (node.P_.a * ((-node.P_.E_L) + std::min(ode_state[State_::V_m], node.P_.V_peak)) - ode_state[State_::w]) / node.P_.tau_w;
  f[State_::g_in__X__inh_spikes] = ode_state[State_::g_in__DOLLAR__X__inh_spikes] - ode_state[State_::g_in__X__inh_spikes] / node.P_.tau_syn_rise_I;
  f[State_::g_in__DOLLAR__X__inh_spikes] = (-ode_state[State_::g_in__DOLLAR__X__inh_spikes]) / node.P_.tau_syn_decay_I;
  f[State_::g_ex__X__exc_spikes] = ode_state[State_::g_ex__DOLLAR__X__exc_spikes] - ode_state[State_::g_ex__X__exc_spikes] / node.P_.tau_syn_rise_E;
  f[State_::g_ex__DOLLAR__X__exc_spikes] = (-ode_state[State_::g_ex__DOLLAR__X__exc_spikes]) / node.P_.tau_syn_decay_E;
  return GSL_SUCCESS;
}

void aeif_cond_beta_nestml::update(nest::Time const & origin, const long from, const long to)
{
  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function

  for ( long lag = from ; lag < to ; ++lag )
  {


    auto get_t = [origin, lag](){ return nest::Time( nest::Time::step( origin.get_steps() + lag + 1) ).get_ms(); };

#ifdef DEBUG
    std::cout << "[neuron " << this << "] aeif_cond_beta_nestml::update: handling post spike at t = " << get_t() << std::endl;
#endif
    /**
     * buffer spikes from spiking input ports
    **/

    for (long i = 0; i < NUM_SPIKE_RECEPTORS; ++i)
    {
      get_spike_inputs_grid_sum_()[i] = get_spike_inputs_()[i].get_value(lag);
      get_spike_input_received_grid_sum_()[i] = get_spike_input_received_()[i].get_value(lag);
    }

    /**
     * subthreshold updates of the convolution variables
     *
     * step 1: regardless of whether and how integrate_odes() will be called, update variables due to convolutions
    **/

    const double g_in__X__inh_spikes__tmp_ = V_.__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes * S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes] + V_.__P__g_in__X__inh_spikes__g_in__X__inh_spikes * S_.ode_state[State_::g_in__X__inh_spikes];
    const double g_in__DOLLAR__X__inh_spikes__tmp_ = V_.__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes * S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes];
    const double g_ex__X__exc_spikes__tmp_ = V_.__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes * S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes] + V_.__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes * S_.ode_state[State_::g_ex__X__exc_spikes];
    const double g_ex__DOLLAR__X__exc_spikes__tmp_ = V_.__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes * S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes];


    /**
     * Begin NESTML generated code for the update block(s)
    **/


  // start rendered code for integrate_odes()

  // analytic solver: integrating state variables (first step): g_in__X__inh_spikes, g_in__DOLLAR__X__inh_spikes, g_ex__X__exc_spikes, g_ex__DOLLAR__X__exc_spikes
  const double g_in__X__inh_spikes__tmp = V_.__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes * S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes] + V_.__P__g_in__X__inh_spikes__g_in__X__inh_spikes * S_.ode_state[State_::g_in__X__inh_spikes];
  const double g_in__DOLLAR__X__inh_spikes__tmp = V_.__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes * S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes];
  const double g_ex__X__exc_spikes__tmp = V_.__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes * S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes] + V_.__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes * S_.ode_state[State_::g_ex__X__exc_spikes];
  const double g_ex__DOLLAR__X__exc_spikes__tmp = V_.__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes * S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes];

  // numeric solver: integrating state variables: V_m, w, g_in__X__inh_spikes, g_in__DOLLAR__X__inh_spikes, g_ex__X__exc_spikes, g_ex__DOLLAR__X__exc_spikes
  double __t = 0;
  B_.__sys.function = aeif_cond_beta_nestml_dynamics;
  // numerical integration with adaptive step size control:
  // ------------------------------------------------------
  // gsl_odeiv_evolve_apply performs only a single numerical
  // integration step, starting from t and bounded by step;
  // the while-loop ensures integration over the whole simulation
  // step (0, step] if more than one integration step is needed due
  // to a small integration step size;
  // note that (t+IntegrationStep > step) leads to integration over
  // (t, step] and afterwards setting t to step, but it does not
  // enforce setting IntegrationStep to step-t; this is of advantage
  // for a consistent and efficient integration across subsequent
  // simulation intervals
  while ( __t < B_.__step )
  {

    const int status = gsl_odeiv_evolve_apply(B_.__e,
                                              B_.__c,
                                              B_.__s,
                                              &B_.__sys,              // system of ODE
                                              &__t,                   // from t
                                              B_.__step,              // to t <= step
                                              &B_.__integration_step, // integration step size
                                              S_.ode_state);          // neuronal state

    if ( status != GSL_SUCCESS )
    {
      throw nest::GSLSolverFailure( get_name(), status );
    }
  }
  // analytic solver: integrating state variables (second step): g_in__X__inh_spikes, g_in__DOLLAR__X__inh_spikes, g_ex__X__exc_spikes, g_ex__DOLLAR__X__exc_spikes
  /* replace analytically solvable variables with precisely integrated values  */
  S_.ode_state[State_::g_in__X__inh_spikes] = g_in__X__inh_spikes__tmp;
  S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes] = g_in__DOLLAR__X__inh_spikes__tmp;
  S_.ode_state[State_::g_ex__X__exc_spikes] = g_ex__X__exc_spikes__tmp;
  S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes] = g_ex__DOLLAR__X__exc_spikes__tmp;
  if (S_.r > 0)
  {  
    S_.r -= 1;
    S_.ode_state[State_::V_m] = P_.V_reset;
  }
  else if (S_.ode_state[State_::V_m] >= P_.V_peak)
  {  
    S_.r = V_.RefractoryCounts;
    S_.ode_state[State_::V_m] = P_.V_reset;
    S_.ode_state[State_::w] += P_.b;

    // begin generated code for emit_spike() function

    #ifdef DEBUG
    std::cout << "[neuron " << this << "] Emitting a spike at t = " << nest::Time(nest::Time::step(origin.get_steps() + lag + 1)).get_ms() << "\n";
    #endif
    set_spiketime(nest::Time::step(origin.get_steps() + lag + 1));
    nest::SpikeEvent se;
    nest::kernel().event_delivery_manager.send(*this, se, lag);
    // end generated code for emit_spike() function
  }

    /**
     * Begin NESTML generated code for the onReceive block(s)
    **/


    /**
     * subthreshold updates of the convolution variables
     *
     * step 2: regardless of whether and how integrate_odes() was called, update variables due to convolutions. Set to the updated values at the end of the timestep.
    **/

    S_.ode_state[State_::g_in__X__inh_spikes] = g_in__X__inh_spikes__tmp_;
    S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes] = g_in__DOLLAR__X__inh_spikes__tmp_;
    S_.ode_state[State_::g_ex__X__exc_spikes] = g_ex__X__exc_spikes__tmp_;
    S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes] = g_ex__DOLLAR__X__exc_spikes__tmp_;

    /**
     * spike updates due to convolutions
    **/

    S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes] += ((0.001 * B_.spike_inputs_grid_sum_[INH_SPIKES - MIN_SPIKE_RECEPTOR])) * (V_.g_I_const * (1 / P_.tau_syn_rise_I - 1 / P_.tau_syn_decay_I)) / (1 / 1000.0);
    S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes] += ((0.001 * B_.spike_inputs_grid_sum_[EXC_SPIKES - MIN_SPIKE_RECEPTOR])) * (V_.g_E_const * (1 / P_.tau_syn_rise_E - 1 / P_.tau_syn_decay_E)) / (1 / 1000.0);

    /**
     * Begin NESTML generated code for the onCondition block(s)
    **/


    /**
     * handle continuous input ports
    **/
    for (long i = 0; i < NUM_CONTINUOUS_INPUT_PORTS; ++i)
    {
      get_continuous_inputs_grid_sum_()[i] = get_continuous_inputs_()[i].get_value(lag);
    }
    // voltage logging
    B_.logger_.record_data(origin.get_steps() + lag);
  }
}

// Do not move this function as inline to h-file. It depends on
// universal_data_logger_impl.h being included here.
void aeif_cond_beta_nestml::handle(nest::DataLoggingRequest& e)
{
  B_.logger_.handle(e);
}


void aeif_cond_beta_nestml::handle(nest::SpikeEvent &e)
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] aeif_cond_beta_nestml::handle(SpikeEvent)" << std::endl;
#endif

  assert(e.get_delay_steps() > 0);
  assert( e.get_rport() < B_.spike_inputs_.size() );

  double weight = e.get_weight();
  size_t nestml_buffer_idx = 0;
  if ( weight >= 0.0 )
  {
    nestml_buffer_idx = std::get<0>(rport_to_nestml_buffer_idx[e.get_rport()]);
  }
  else
  {
    nestml_buffer_idx = std::get<1>(rport_to_nestml_buffer_idx[e.get_rport()]);
    if ( nestml_buffer_idx == aeif_cond_beta_nestml::PORT_NOT_AVAILABLE )
    {
      nestml_buffer_idx = std::get<0>(rport_to_nestml_buffer_idx[e.get_rport()]);
    }
    weight = -weight;
  }
  B_.spike_inputs_[ nestml_buffer_idx - MIN_SPIKE_RECEPTOR ].add_value(
    e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin() ),
    weight * e.get_multiplicity() );
  B_.spike_input_received_[ nestml_buffer_idx - MIN_SPIKE_RECEPTOR ].add_value(
    e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin() ),
    1. );
}

void aeif_cond_beta_nestml::handle(nest::CurrentEvent& e)
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] aeif_cond_beta_nestml::handle(CurrentEvent)" << std::endl;
#endif
  assert(e.get_delay_steps() > 0);
  assert( e.get_rport() < B_.continuous_inputs_.size() );

  const double current = e.get_current();     // we assume that in NEST, this returns a current in pA
  const double weight = e.get_weight();

  B_.continuous_inputs_[e.get_rport()].add_value(
               e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin()),
               weight * current );
}

// -------------------------------------------------------------------------
//   Methods corresponding to event handlers
// -------------------------------------------------------------------------

