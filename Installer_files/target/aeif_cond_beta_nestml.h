
/**
 *  aeif_cond_beta_nestml.h
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
#ifndef AEIF_COND_BETA_NESTML
#define AEIF_COND_BETA_NESTML

#ifndef HAVE_LIBLTDL
#error "NEST was compiled without support for dynamic loading. Please install libltdl and recompile NEST."
#endif

// C++ includes:
#include <cmath>

#include "config.h"

#ifndef HAVE_GSL
#error "The GSL library is required for the Runge-Kutta solver."
#endif

// External includes:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

// Includes from nestkernel:
#include "structural_plasticity_node.h"
#include "connection.h"
#include "dict_util.h"
#include "event.h"
#include "nest_types.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"

// uncomment the next line to enable printing of detailed debug information
// #define DEBUG
typedef Dictionary DictionaryDatum;

namespace nest
{
namespace aeif_cond_beta_nestml_names
{
    typedef std::string Name;
    // state variables
    const Name _V_m( "V_m" );
    const Name _w( "w" );
    const Name _r( "r" );
    const Name _g_in__X__inh_spikes( "g_in__X__inh_spikes" );
    const Name _g_in__DOLLAR__X__inh_spikes( "g_in__DOLLAR__X__inh_spikes" );
    const Name _g_ex__X__exc_spikes( "g_ex__X__exc_spikes" );
    const Name _g_ex__DOLLAR__X__exc_spikes( "g_ex__DOLLAR__X__exc_spikes" );
    // parameters
    const Name _C_m( "C_m" );
    const Name _t_ref( "t_ref" );
    const Name _V_reset( "V_reset" );
    const Name _g_L( "g_L" );
    const Name _E_L( "E_L" );
    const Name _a( "a" );
    const Name _b( "b" );
    const Name _Delta_T( "Delta_T" );
    const Name _tau_w( "tau_w" );
    const Name _V_th( "V_th" );
    const Name _V_peak( "V_peak" );
    const Name _E_exc( "E_exc" );
    const Name _E_inh( "E_inh" );
    const Name _tau_syn_rise_I( "tau_syn_rise_I" );
    const Name _tau_syn_decay_I( "tau_syn_decay_I" );
    const Name _tau_syn_rise_E( "tau_syn_rise_E" );
    const Name _tau_syn_decay_E( "tau_syn_decay_E" );
    const Name _I_e( "I_e" );
    // internals
    const Name _t_peak_E( "t_peak_E" );
    const Name ___h( "__h" );
    const Name _t_peak_I( "t_peak_I" );
    const Name _g_E_const( "g_E_const" );
    const Name _g_I_const( "g_I_const" );
    const Name _RefractoryCounts( "RefractoryCounts" );
    const Name ___P__g_in__X__inh_spikes__g_in__X__inh_spikes( "__P__g_in__X__inh_spikes__g_in__X__inh_spikes" );
    const Name ___P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes( "__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes" );
    const Name ___P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes( "__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes" );
    const Name ___P__g_ex__X__exc_spikes__g_ex__X__exc_spikes( "__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes" );
    const Name ___P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes( "__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes" );
    const Name ___P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes( "__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes" );

    const Name gsl_abs_error_tol("gsl_abs_error_tol");
    const Name gsl_rel_error_tol("gsl_rel_error_tol");
}
}



/**
 * Function computing right-hand side of ODE for GSL solver.
 * @note Must be declared here so we can befriend it in class.
 * @note Must have C-linkage for passing to GSL. Internally, it is
 *       a first-class C++ function, but cannot be a member function
 *       because of the C-linkage.
 * @note No point in declaring it inline, since it is called
 *       through a function pointer.
 * @param void* Pointer to model neuron instance.
 *
 * Integrate the variables: 
**/
extern "C" inline int aeif_cond_beta_nestml_dynamics( double, const double ode_state[], double f[], void* pnode );

#include "nest_time.h"
  typedef size_t nest_port_t;
  typedef size_t nest_rport_t;

/* BeginDocumentation
  Name: aeif_cond_beta_nestml

  Description:

    aeif_cond_beta - Conductance based exponential integrate-and-fire neuron model
  ###############################################################################

  Description
  +++++++++++
  aeif_cond_beta is the adaptive exponential integrate and fire neuron according to Brette and Gerstner (2005), with post-synaptic conductances in the form of a bi-exponential ("beta") function.

  The membrane potential is given by the following differential equation:

  . math::

    C_m \frac{dV_m}{dt} =
   g_e(t)(V_m-E_e) \\
                                                       -g_i(t)(V_m-E_i)-w + I_e

  and
  .. math::

  \tau_w \frac{dw}{dt} = a(V_m-E_L) - w

  Note that the membrane potential can diverge to positive infinity due to the exponential term. To avoid numerical instabilities, instead of :math:`V_m`, the value :math:`\min(V_m,V_{peak})` is used in the dynamical equations.


  References
  ++++++++++#

  . [1] Brette R and Gerstner W (2005). Adaptive exponential
        integrate-and-fire model as an effective description of neuronal
         activity. Journal of Neurophysiology. 943637-3642
         DOI: https://doi.org/10.1152/jn.00686.2005

  See also
  ++++++++

  iaf_cond_beta, aeif_cond_exp



  Parameters:
  The following parameters can be set in the status dictionary.
C_m [pF] membrane parameters
 Membrane Capacitance
t_ref [ms]  Refractory period
V_reset [mV]  Reset Potential
g_L [nS]  Leak Conductance
E_L [mV]  Leak reversal Potential (aka resting potential)
a [nS] spike adaptation parameters
 Subthreshold adaptation
b [pA]  Spike-triggered adaptation
Delta_T [mV]  Slope factor
tau_w [ms]  Adaptation time constant
V_th [mV]  Threshold Potential
V_peak [mV]  Spike detection threshold
E_exc [mV] synaptic parameters
 Excitatory reversal Potential
E_inh [mV]  Inhibitory reversal Potential
tau_syn_rise_I [ms]  Synaptic time constant inhibitory synapse
tau_syn_decay_I [ms]  Synaptic time constant for inhibitory synapse
tau_syn_rise_E [ms]  Synaptic time constant excitatory synapse
tau_syn_decay_E [ms]  Synaptic time constant for excitatory synapse
I_e [pA] constant external input current


  Dynamic state variables:
V_m [mV]  Membrane potential
w [pA]  Spike-adaptation current
r [integer]  Counts number of tick during the refractory period


  Sends: nest::SpikeEvent

  Receives: Spike, Current, DataLoggingRequest
*/

// Register the neuron model
void register_aeif_cond_beta_nestml( const std::string& name );

class aeif_cond_beta_nestml : public nest::StructuralPlasticityNode
{
public:
  /**
   * The constructor is only used to create the model prototype in the model manager.
  **/
  aeif_cond_beta_nestml();

  /**
   * The copy constructor is used to create model copies and instances of the model.
   * @node The copy constructor needs to initialize the parameters and the state.
   *       Initialization of buffers and interal variables is deferred to
   *       @c init_buffers_() and @c pre_run_hook() (or calibrate() in NEST 3.3 and older).
  **/
  aeif_cond_beta_nestml(const aeif_cond_beta_nestml &);

  /**
   * Destructor.
  **/
  ~aeif_cond_beta_nestml() override;

  // -------------------------------------------------------------------------
  //   Import sets of overloaded virtual functions.
  //   See: Technical Issues / Virtual Functions: Overriding, Overloading,
  //        and Hiding
  // -------------------------------------------------------------------------

  using nest::Node::handles_test_event;
  using nest::Node::handle;

  /**
   * Used to validate that we can send nest::SpikeEvent to desired target:port.
  **/
  nest_port_t send_test_event(nest::Node& target, nest_rport_t receptor_type, nest::synindex, bool) override;


  // -------------------------------------------------------------------------
  //   Functions handling incoming events.
  //   We tell nest that we can handle incoming events of various types by
  //   defining handle() for the given event.
  // -------------------------------------------------------------------------


  void handle(nest::SpikeEvent &) override;        //! accept spikes
  void handle(nest::CurrentEvent &) override;      //! accept input current

  void handle(nest::DataLoggingRequest &) override;//! allow recording with multimeter
  nest_port_t handles_test_event(nest::SpikeEvent&, nest_port_t) override;
  nest_port_t handles_test_event(nest::CurrentEvent&, nest_port_t) override;
  nest_port_t handles_test_event(nest::DataLoggingRequest&, nest_port_t) override;

  // -------------------------------------------------------------------------
  //   Functions for getting/setting parameters and state values.
  // -------------------------------------------------------------------------

  void get_status(DictionaryDatum&) const override;
  void set_status(const DictionaryDatum&) override;


  // -------------------------------------------------------------------------
  //   Getters/setters for state block
  // -------------------------------------------------------------------------

  inline double get_V_m() const
  {
    return S_.ode_state[State_::V_m];
  }inline void set_V_m(const double __v)
  {
    S_.ode_state[State_::V_m] = __v;
  }

  inline double get_w() const
  {
    return S_.ode_state[State_::w];
  }inline void set_w(const double __v)
  {
    S_.ode_state[State_::w] = __v;
  }

  inline long get_r() const
  {
    return S_.r;
  }inline void set_r(const long __v)
  {
    S_.r = __v;
  }

  inline double get_g_in__X__inh_spikes() const
  {
    return S_.ode_state[State_::g_in__X__inh_spikes];
  }inline void set_g_in__X__inh_spikes(const double __v)
  {
    S_.ode_state[State_::g_in__X__inh_spikes] = __v;
  }

  inline double get_g_in__DOLLAR__X__inh_spikes() const
  {
    return S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes];
  }inline void set_g_in__DOLLAR__X__inh_spikes(const double __v)
  {
    S_.ode_state[State_::g_in__DOLLAR__X__inh_spikes] = __v;
  }

  inline double get_g_ex__X__exc_spikes() const
  {
    return S_.ode_state[State_::g_ex__X__exc_spikes];
  }inline void set_g_ex__X__exc_spikes(const double __v)
  {
    S_.ode_state[State_::g_ex__X__exc_spikes] = __v;
  }

  inline double get_g_ex__DOLLAR__X__exc_spikes() const
  {
    return S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes];
  }inline void set_g_ex__DOLLAR__X__exc_spikes(const double __v)
  {
    S_.ode_state[State_::g_ex__DOLLAR__X__exc_spikes] = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for parameters
  // -------------------------------------------------------------------------

  inline double get_C_m() const
  {
    return P_.C_m;
  }inline void set_C_m(const double __v)
  {
    P_.C_m = __v;
  }

  inline double get_t_ref() const
  {
    return P_.t_ref;
  }inline void set_t_ref(const double __v)
  {
    P_.t_ref = __v;
  }

  inline double get_V_reset() const
  {
    return P_.V_reset;
  }inline void set_V_reset(const double __v)
  {
    P_.V_reset = __v;
  }

  inline double get_g_L() const
  {
    return P_.g_L;
  }inline void set_g_L(const double __v)
  {
    P_.g_L = __v;
  }

  inline double get_E_L() const
  {
    return P_.E_L;
  }inline void set_E_L(const double __v)
  {
    P_.E_L = __v;
  }

  inline double get_a() const
  {
    return P_.a;
  }inline void set_a(const double __v)
  {
    P_.a = __v;
  }

  inline double get_b() const
  {
    return P_.b;
  }inline void set_b(const double __v)
  {
    P_.b = __v;
  }

  inline double get_Delta_T() const
  {
    return P_.Delta_T;
  }inline void set_Delta_T(const double __v)
  {
    P_.Delta_T = __v;
  }

  inline double get_tau_w() const
  {
    return P_.tau_w;
  }inline void set_tau_w(const double __v)
  {
    P_.tau_w = __v;
  }

  inline double get_V_th() const
  {
    return P_.V_th;
  }inline void set_V_th(const double __v)
  {
    P_.V_th = __v;
  }

  inline double get_V_peak() const
  {
    return P_.V_peak;
  }inline void set_V_peak(const double __v)
  {
    P_.V_peak = __v;
  }

  inline double get_E_exc() const
  {
    return P_.E_exc;
  }inline void set_E_exc(const double __v)
  {
    P_.E_exc = __v;
  }

  inline double get_E_inh() const
  {
    return P_.E_inh;
  }inline void set_E_inh(const double __v)
  {
    P_.E_inh = __v;
  }

  inline double get_tau_syn_rise_I() const
  {
    return P_.tau_syn_rise_I;
  }inline void set_tau_syn_rise_I(const double __v)
  {
    P_.tau_syn_rise_I = __v;
  }

  inline double get_tau_syn_decay_I() const
  {
    return P_.tau_syn_decay_I;
  }inline void set_tau_syn_decay_I(const double __v)
  {
    P_.tau_syn_decay_I = __v;
  }

  inline double get_tau_syn_rise_E() const
  {
    return P_.tau_syn_rise_E;
  }inline void set_tau_syn_rise_E(const double __v)
  {
    P_.tau_syn_rise_E = __v;
  }

  inline double get_tau_syn_decay_E() const
  {
    return P_.tau_syn_decay_E;
  }inline void set_tau_syn_decay_E(const double __v)
  {
    P_.tau_syn_decay_E = __v;
  }

  inline double get_I_e() const
  {
    return P_.I_e;
  }inline void set_I_e(const double __v)
  {
    P_.I_e = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for internals
  // -------------------------------------------------------------------------

  inline double get_t_peak_E() const
  {
    return V_.t_peak_E;
  }inline void set_t_peak_E(const double __v)
  {
    V_.t_peak_E = __v;
  }
  inline double get___h() const
  {
    return V_.__h;
  }inline void set___h(const double __v)
  {
    V_.__h = __v;
  }
  inline double get_t_peak_I() const
  {
    return V_.t_peak_I;
  }inline void set_t_peak_I(const double __v)
  {
    V_.t_peak_I = __v;
  }
  inline double get_g_E_const() const
  {
    return V_.g_E_const;
  }inline void set_g_E_const(const double __v)
  {
    V_.g_E_const = __v;
  }
  inline double get_g_I_const() const
  {
    return V_.g_I_const;
  }inline void set_g_I_const(const double __v)
  {
    V_.g_I_const = __v;
  }
  inline long get_RefractoryCounts() const
  {
    return V_.RefractoryCounts;
  }inline void set_RefractoryCounts(const long __v)
  {
    V_.RefractoryCounts = __v;
  }
  inline double get___P__g_in__X__inh_spikes__g_in__X__inh_spikes() const
  {
    return V_.__P__g_in__X__inh_spikes__g_in__X__inh_spikes;
  }inline void set___P__g_in__X__inh_spikes__g_in__X__inh_spikes(const double __v)
  {
    V_.__P__g_in__X__inh_spikes__g_in__X__inh_spikes = __v;
  }
  inline double get___P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes() const
  {
    return V_.__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes;
  }inline void set___P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes(const double __v)
  {
    V_.__P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes = __v;
  }
  inline double get___P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes() const
  {
    return V_.__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes;
  }inline void set___P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes(const double __v)
  {
    V_.__P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes = __v;
  }
  inline double get___P__g_ex__X__exc_spikes__g_ex__X__exc_spikes() const
  {
    return V_.__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes;
  }inline void set___P__g_ex__X__exc_spikes__g_ex__X__exc_spikes(const double __v)
  {
    V_.__P__g_ex__X__exc_spikes__g_ex__X__exc_spikes = __v;
  }
  inline double get___P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes() const
  {
    return V_.__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes;
  }inline void set___P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes(const double __v)
  {
    V_.__P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes = __v;
  }
  inline double get___P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes() const
  {
    return V_.__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes;
  }inline void set___P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes(const double __v)
  {
    V_.__P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes = __v;
  }


  // -------------------------------------------------------------------------
  //   Methods corresponding to event handlers
  // -------------------------------------------------------------------------

  

  // -------------------------------------------------------------------------
  //   Initialization functions
  // -------------------------------------------------------------------------
  void calibrate_time( const nest::TimeConverter& tc ) override;

protected:

private:
  void recompute_internal_variables(bool exclude_timestep=false);

private:

  static const nest_port_t MIN_SPIKE_RECEPTOR = 0;
  static const nest_port_t PORT_NOT_AVAILABLE = -1;

  enum SynapseTypes
  {
    INH_SPIKES = 0,
    EXC_SPIKES = 1,
    MAX_SPIKE_RECEPTOR = 2
  };

  enum ContinuousInput
  {
    I_STIM = 0,
    NUM_CONTINUOUS_INPUT_PORTS = 1
  };

  static const size_t NUM_SPIKE_RECEPTORS = MAX_SPIKE_RECEPTOR - MIN_SPIKE_RECEPTOR;

static std::vector< std::tuple< int, int > > rport_to_nestml_buffer_idx;

  /**
   * Reset state of neuron.
  **/

  void init_state_internal_();

  /**
   * Reset internal buffers of neuron.
  **/
  void init_buffers_() override;

  /**
   * Initialize auxiliary quantities, leave parameters and state untouched.
  **/
  void pre_run_hook() override;

  /**
   * Take neuron through given time interval
  **/
  void update(nest::Time const &, const long, const long) override;

  // The next two classes need to be friends to access the State_ class/member
  friend class nest::RecordablesMap<aeif_cond_beta_nestml>;
  friend class nest::UniversalDataLogger<aeif_cond_beta_nestml>;

  /**
   * Free parameters of the neuron.
   *


   *
   * These are the parameters that can be set by the user through @c `node.set()`.
   * They are initialized from the model prototype when the node is created.
   * Parameters do not change during calls to @c update() and are not reset by
   * @c ResetNetwork.
   *
   * @note Parameters_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If Parameters_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If Parameters_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct Parameters_
  {    
    //! membrane parameters
    //!  Membrane Capacitance
    double C_m;
    //!  Refractory period
    double t_ref;
    //!  Reset Potential
    double V_reset;
    //!  Leak Conductance
    double g_L;
    //!  Leak reversal Potential (aka resting potential)
    double E_L;
    //! spike adaptation parameters
    //!  Subthreshold adaptation
    double a;
    //!  Spike-triggered adaptation
    double b;
    //!  Slope factor
    double Delta_T;
    //!  Adaptation time constant
    double tau_w;
    //!  Threshold Potential
    double V_th;
    //!  Spike detection threshold
    double V_peak;
    //! synaptic parameters
    //!  Excitatory reversal Potential
    double E_exc;
    //!  Inhibitory reversal Potential
    double E_inh;
    //!  Synaptic time constant inhibitory synapse
    double tau_syn_rise_I;
    //!  Synaptic time constant for inhibitory synapse
    double tau_syn_decay_I;
    //!  Synaptic time constant excitatory synapse
    double tau_syn_rise_E;
    //!  Synaptic time constant for excitatory synapse
    double tau_syn_decay_E;
    //! constant external input current
    double I_e;

    double __gsl_abs_error_tol;
    double __gsl_rel_error_tol;

    /**
     * Initialize parameters to their default values.
    **/
    Parameters_();
  };

  /**
   * Dynamic state of the neuron.
   *
   *
   *
   * These are the state variables that are advanced in time by calls to
   * @c update(). In many models, some or all of them can be set by the user
   * through @c `node.set()`. The state variables are initialized from the model
   * prototype when the node is created. State variables are reset by @c ResetNetwork.
   *
   * @note State_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If State_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If State_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct State_
  {

    // non-ODE state variables
//!  Counts number of tick during the refractory period
long r;
    //! Symbolic indices to the elements of the state vector y
    enum StateVecElems
    {
      V_m,
      w,
      g_in__X__inh_spikes,
      g_in__DOLLAR__X__inh_spikes,
      g_ex__X__exc_spikes,
      g_ex__DOLLAR__X__exc_spikes,
      // moved state variables from synapse (numeric)
      // moved state variables from synapse (analytic)
      // final entry to easily get the vector size
      STATE_VEC_SIZE
    };

    //! state vector, must be C-array for GSL solver
    double ode_state[STATE_VEC_SIZE];

    State_();
  };

  struct DelayedVariables_
  {
  };

  /**
   * Internal variables of the neuron.
   *
   *
   *
   * These variables must be initialized by @c pre_run_hook (or calibrate in NEST 3.3 and older), which is called before
   * the first call to @c update() upon each call to @c Simulate.
   * @node Variables_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c pre_run_hook() (or calibrate() in NEST 3.3 and older). If Variables_ has members that
   *       cannot destroy themselves, Variables_ will need a destructor.
  **/
  struct Variables_
  {
    //! time of peak conductance excursion after spike arrival at t = 0
    double t_peak_E;
    double __h;
    double t_peak_I;
    //! normalisation constants to ensure arriving spike yields peak conductance of 1 nS
    double g_E_const;
    double g_I_const;
    //! refractory time in steps
    long RefractoryCounts;
    double __P__g_in__X__inh_spikes__g_in__X__inh_spikes;
    double __P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes;
    double __P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes;
    double __P__g_ex__X__exc_spikes__g_ex__X__exc_spikes;
    double __P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes;
    double __P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes;
  };

  /**
   * Buffers of the neuron.
   * Usually buffers for incoming spikes and data logged for analog recorders.
   * Buffers must be initialized by @c init_buffers_(), which is called before
   * @c pre_run_hook() (or calibrate() in NEST 3.3 and older) on the first call to @c Simulate after the start of NEST,
   * ResetKernel or ResetNetwork.
   * @node Buffers_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c init_nodes_(). If Buffers_ has members that
   *       cannot destroy themselves, Buffers_ will need a destructor.
  **/
  struct Buffers_
  {
    Buffers_(aeif_cond_beta_nestml &);
    Buffers_(const Buffers_ &, aeif_cond_beta_nestml &);

    /**
     * Logger for all analog data
    **/
    nest::UniversalDataLogger<aeif_cond_beta_nestml> logger_;

    // -----------------------------------------------------------------------
    //   Spike buffers and sums of incoming spikes/currents per timestep
    // -----------------------------------------------------------------------    



    /**
     * Buffer containing the incoming spikes
    **/
    inline std::vector< nest::RingBuffer >& get_spike_inputs_()
    {
        return spike_inputs_;
    }
    std::vector< nest::RingBuffer > spike_inputs_;

    /**
     * Buffer containing the sum of all the incoming spikes
    **/
    inline std::vector< double >& get_spike_inputs_grid_sum_()
    {
        return spike_inputs_grid_sum_;
    }
    std::vector< double > spike_inputs_grid_sum_;

    /**
     * Buffer containing a flag whether incoming spikes have been received on a given port
    **/
    inline std::vector< nest::RingBuffer >& get_spike_input_received_()
    {
        return spike_input_received_;
    }
    std::vector< nest::RingBuffer > spike_input_received_;

    /**
     * Buffer containing a flag whether incoming spikes have been received on a given port
    **/
    inline std::vector< double >& get_spike_input_received_grid_sum_()
    {
        return spike_input_received_grid_sum_;
    }
    std::vector< double > spike_input_received_grid_sum_;

    // -----------------------------------------------------------------------
    //   Continuous-input buffers
    // -----------------------------------------------------------------------

    




    /**
     * Buffer containing the incoming continuous input
    **/
    inline std::vector< nest::RingBuffer >& get_continuous_inputs_()
    {
        return continuous_inputs_;
    }
    std::vector< nest::RingBuffer > continuous_inputs_;

    /**
     * Buffer containing the sum of all the continuous inputs
    **/
    inline std::vector< double >& get_continuous_inputs_grid_sum_()
    {
        return continuous_inputs_grid_sum_;
    }
    std::vector< double > continuous_inputs_grid_sum_;

    // -----------------------------------------------------------------------
    //   GSL ODE solver data structures
    // -----------------------------------------------------------------------

    gsl_odeiv_step* __s;    //!< stepping function
    gsl_odeiv_control* __c; //!< adaptive stepsize control function
    gsl_odeiv_evolve* __e;  //!< evolution function
    gsl_odeiv_system __sys; //!< struct describing system

    // __integration_step should be reset with the neuron on ResetNetwork,
    // but remain unchanged during calibration. Since it is initialized with
    // step_, and the resolution cannot change after nodes have been created,
    // it is safe to place both here.
    double __step;             //!< step size in ms
    double __integration_step; //!< current integration time step, updated by GSL
  };

  // -------------------------------------------------------------------------
  //   Getters for inline expressions
  // -------------------------------------------------------------------------
public:
  inline double get_V_bounded() const
  {
    return std::min(S_.ode_state[State_::V_m], P_.V_peak);
  }

  inline double get_exp_arg() const
  {
    return ((std::min(S_.ode_state[State_::V_m], P_.V_peak)) - P_.V_th) / P_.Delta_T;
  }

  inline double get_I_spike() const
  {
    return P_.g_L * P_.Delta_T * std::exp((((std::min(S_.ode_state[State_::V_m], P_.V_peak)) - P_.V_th) / P_.Delta_T));
  }

  inline double get_I_syn_exc() const
  {
    return S_.ode_state[State_::g_ex__X__exc_spikes] * 1.0 * ((std::min(S_.ode_state[State_::V_m], P_.V_peak)) - P_.E_exc);
  }

  inline double get_I_syn_inh() const
  {
    return S_.ode_state[State_::g_in__X__inh_spikes] * 1.0 * ((std::min(S_.ode_state[State_::V_m], P_.V_peak)) - P_.E_inh);
  }



  // -------------------------------------------------------------------------
  //   Setters for inline expressions (this is allowed for expressions containing a convolve() call)
  // -------------------------------------------------------------------------
private:
  











  // -------------------------------------------------------------------------
  //   Getters/setters for input buffers
  // -------------------------------------------------------------------------  




  /**
   * Buffer containing the incoming spikes
  **/
  inline std::vector< nest::RingBuffer >& get_spike_inputs_()
  {
      return B_.get_spike_inputs_();
  }

  /**
   * Buffer containing the sum of all the incoming spikes
  **/
  inline std::vector< double >& get_spike_inputs_grid_sum_()
  {
      return B_.get_spike_inputs_grid_sum_();
  }

  /**
   * Buffer containing a flag whether incoming spikes have been received on a given port
  **/
  inline std::vector< nest::RingBuffer >& get_spike_input_received_()
  {
      return B_.get_spike_input_received_();
  }

  /**
   * Buffer containing a flag whether incoming spikes have been received on a given port
  **/
  inline std::vector< double >& get_spike_input_received_grid_sum_()
  {
      return B_.get_spike_input_received_grid_sum_();
  }




  /**
   * Buffer containing the incoming continuous input
  **/
  inline std::vector< nest::RingBuffer >& get_continuous_inputs_()
  {
      return B_.get_continuous_inputs_();
  }

  /**
   * Buffer containing the sum of all the continuous inputs
  **/
  inline std::vector< double >& get_continuous_inputs_grid_sum_()
  {
      return B_.get_continuous_inputs_grid_sum_();
  }

  // -------------------------------------------------------------------------
  //   Member variables of neuron model.
  //   Each model neuron should have precisely the following four data members,
  //   which are one instance each of the parameters, state, buffers and variables
  //   structures. Experience indicates that the state and variables member should
  //   be next to each other to achieve good efficiency (caching).
  //   Note: Devices require one additional data member, an instance of the
  //   ``Device`` child class they belong to.
  // -------------------------------------------------------------------------


  Parameters_       P_;        //!< Free parameters.
  State_            S_;        //!< Dynamic state.
  DelayedVariables_ DV_;       //!< Delayed state variables.
  Variables_        V_;        //!< Internal Variables
  Buffers_          B_;        //!< Buffers.

  //! Mapping of recordables names to access functions
  static nest::RecordablesMap<aeif_cond_beta_nestml> recordablesMap_;
  friend int aeif_cond_beta_nestml_dynamics( double, const double ode_state[], double f[], void* pnode );

}; /* neuron aeif_cond_beta_nestml */

inline nest_port_t aeif_cond_beta_nestml::send_test_event(nest::Node& target, nest_rport_t receptor_type, nest::synindex, bool)
{
  // You should usually not change the code in this function.
  // It confirms that the target of connection @c c accepts @c nest::SpikeEvent on
  // the given @c receptor_type.
  nest::SpikeEvent e;
  e.set_sender(*this);
  return target.handles_test_event(e, receptor_type);
}

inline nest_port_t aeif_cond_beta_nestml::handles_test_event(nest::SpikeEvent&, nest_port_t receptor_type)
{
    // You should usually not change the code in this function.
    // It confirms to the connection management system that we are able
    // to handle @c SpikeEvent on port 0. You need to extend the function
    // if you want to differentiate between input ports.
    if (receptor_type != 0)
    {
      throw nest::UnknownReceptorType(receptor_type, get_name());
    }
    return 0;
}

inline nest_port_t aeif_cond_beta_nestml::handles_test_event(nest::CurrentEvent&, nest_port_t receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c CurrentEvent on port 0. You need to extend the function
  // if you want to differentiate between input ports.
  if (receptor_type >= NUM_CONTINUOUS_INPUT_PORTS)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }
  return receptor_type;
}

inline nest_port_t aeif_cond_beta_nestml::handles_test_event(nest::DataLoggingRequest& dlr, nest_port_t receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c DataLoggingRequest on port 0.
  // The function also tells the built-in UniversalDataLogger that this node
  // is recorded from and that it thus needs to collect data during simulation.
  if (receptor_type != 0)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }

  return B_.logger_.connect_logging_device(dlr, recordablesMap_);
}

inline void aeif_cond_beta_nestml::get_status(DictionaryDatum&__d) const
{
  // parameters

  __d[ nest::aeif_cond_beta_nestml_names::_C_m ] = get_C_m();

  __d[ nest::aeif_cond_beta_nestml_names::_t_ref ] = get_t_ref();

  __d[ nest::aeif_cond_beta_nestml_names::_V_reset ] = get_V_reset();

  __d[ nest::aeif_cond_beta_nestml_names::_g_L ] = get_g_L();

  __d[ nest::aeif_cond_beta_nestml_names::_E_L ] = get_E_L();

  __d[ nest::aeif_cond_beta_nestml_names::_a ] = get_a();

  __d[ nest::aeif_cond_beta_nestml_names::_b ] = get_b();

  __d[ nest::aeif_cond_beta_nestml_names::_Delta_T ] = get_Delta_T();

  __d[ nest::aeif_cond_beta_nestml_names::_tau_w ] = get_tau_w();

  __d[ nest::aeif_cond_beta_nestml_names::_V_th ] = get_V_th();

  __d[ nest::aeif_cond_beta_nestml_names::_V_peak ] = get_V_peak();

  __d[ nest::aeif_cond_beta_nestml_names::_E_exc ] = get_E_exc();

  __d[ nest::aeif_cond_beta_nestml_names::_E_inh ] = get_E_inh();

  __d[ nest::aeif_cond_beta_nestml_names::_tau_syn_rise_I ] = get_tau_syn_rise_I();

  __d[ nest::aeif_cond_beta_nestml_names::_tau_syn_decay_I ] = get_tau_syn_decay_I();

  __d[ nest::aeif_cond_beta_nestml_names::_tau_syn_rise_E ] = get_tau_syn_rise_E();

  __d[ nest::aeif_cond_beta_nestml_names::_tau_syn_decay_E ] = get_tau_syn_decay_E();

  __d[ nest::aeif_cond_beta_nestml_names::_I_e ] = get_I_e();

  // internals

  __d[ nest::aeif_cond_beta_nestml_names::_t_peak_E ] = get_t_peak_E();

  __d[ nest::aeif_cond_beta_nestml_names::___h ] = get___h();

  __d[ nest::aeif_cond_beta_nestml_names::_t_peak_I ] = get_t_peak_I();

  __d[ nest::aeif_cond_beta_nestml_names::_g_E_const ] = get_g_E_const();

  __d[ nest::aeif_cond_beta_nestml_names::_g_I_const ] = get_g_I_const();

  __d[ nest::aeif_cond_beta_nestml_names::_RefractoryCounts ] = get_RefractoryCounts();

  __d[ nest::aeif_cond_beta_nestml_names::___P__g_in__X__inh_spikes__g_in__X__inh_spikes ] = get___P__g_in__X__inh_spikes__g_in__X__inh_spikes();

  __d[ nest::aeif_cond_beta_nestml_names::___P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes ] = get___P__g_in__X__inh_spikes__g_in__DOLLAR__X__inh_spikes();

  __d[ nest::aeif_cond_beta_nestml_names::___P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes ] = get___P__g_in__DOLLAR__X__inh_spikes__g_in__DOLLAR__X__inh_spikes();

  __d[ nest::aeif_cond_beta_nestml_names::___P__g_ex__X__exc_spikes__g_ex__X__exc_spikes ] = get___P__g_ex__X__exc_spikes__g_ex__X__exc_spikes();

  __d[ nest::aeif_cond_beta_nestml_names::___P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes ] = get___P__g_ex__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes();

  __d[ nest::aeif_cond_beta_nestml_names::___P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes ] = get___P__g_ex__DOLLAR__X__exc_spikes__g_ex__DOLLAR__X__exc_spikes();

  // initial values for state variables in ODE or kernel

  __d[ nest::aeif_cond_beta_nestml_names::_V_m ] = get_V_m();

  __d[ nest::aeif_cond_beta_nestml_names::_w ] = get_w();

  __d[ nest::aeif_cond_beta_nestml_names::_r ] = get_r();

  __d[ nest::aeif_cond_beta_nestml_names::_g_in__X__inh_spikes ] = get_g_in__X__inh_spikes();

  __d[ nest::aeif_cond_beta_nestml_names::_g_in__DOLLAR__X__inh_spikes ] = get_g_in__DOLLAR__X__inh_spikes();

  __d[ nest::aeif_cond_beta_nestml_names::_g_ex__X__exc_spikes ] = get_g_ex__X__exc_spikes();

  __d[ nest::aeif_cond_beta_nestml_names::_g_ex__DOLLAR__X__exc_spikes ] = get_g_ex__DOLLAR__X__exc_spikes();

  StructuralPlasticityNode::get_status( __d );

  
__d[ nest::names::recordables ] = recordablesMap_.get_list();
  
__d[ nest::aeif_cond_beta_nestml_names::gsl_abs_error_tol ] = P_.__gsl_abs_error_tol;
  if ( P_.__gsl_abs_error_tol <= 0. ){
    throw nest::BadProperty( "The gsl_abs_error_tol must be strictly positive." );
  }
  
__d[ nest::aeif_cond_beta_nestml_names::gsl_rel_error_tol ] = P_.__gsl_rel_error_tol;
  if ( P_.__gsl_rel_error_tol < 0. ){
    throw nest::BadProperty( "The gsl_rel_error_tol must be zero or positive." );
  }
}

inline void aeif_cond_beta_nestml::set_status(const DictionaryDatum&__d)
{
  // parameters
  double tmp_C_m = get_C_m();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_C_m, tmp_C_m, this);
  double tmp_t_ref = get_t_ref();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_t_ref, tmp_t_ref, this);
  double tmp_V_reset = get_V_reset();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_V_reset, tmp_V_reset, this);
  double tmp_g_L = get_g_L();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_g_L, tmp_g_L, this);
  double tmp_E_L = get_E_L();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_E_L, tmp_E_L, this);
  double tmp_a = get_a();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_a, tmp_a, this);
  double tmp_b = get_b();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_b, tmp_b, this);
  double tmp_Delta_T = get_Delta_T();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_Delta_T, tmp_Delta_T, this);
  double tmp_tau_w = get_tau_w();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_tau_w, tmp_tau_w, this);
  double tmp_V_th = get_V_th();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_V_th, tmp_V_th, this);
  double tmp_V_peak = get_V_peak();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_V_peak, tmp_V_peak, this);
  double tmp_E_exc = get_E_exc();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_E_exc, tmp_E_exc, this);
  double tmp_E_inh = get_E_inh();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_E_inh, tmp_E_inh, this);
  double tmp_tau_syn_rise_I = get_tau_syn_rise_I();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_tau_syn_rise_I, tmp_tau_syn_rise_I, this);
  double tmp_tau_syn_decay_I = get_tau_syn_decay_I();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_tau_syn_decay_I, tmp_tau_syn_decay_I, this);
  double tmp_tau_syn_rise_E = get_tau_syn_rise_E();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_tau_syn_rise_E, tmp_tau_syn_rise_E, this);
  double tmp_tau_syn_decay_E = get_tau_syn_decay_E();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_tau_syn_decay_E, tmp_tau_syn_decay_E, this);
  double tmp_I_e = get_I_e();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_I_e, tmp_I_e, this);

  // initial values for state variables in ODE or kernel
  double tmp_V_m = get_V_m();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_V_m, tmp_V_m, this);
  double tmp_w = get_w();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_w, tmp_w, this);
  long tmp_r = get_r();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_r, tmp_r, this);
  double tmp_g_in__X__inh_spikes = get_g_in__X__inh_spikes();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_g_in__X__inh_spikes, tmp_g_in__X__inh_spikes, this);
  double tmp_g_in__DOLLAR__X__inh_spikes = get_g_in__DOLLAR__X__inh_spikes();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_g_in__DOLLAR__X__inh_spikes, tmp_g_in__DOLLAR__X__inh_spikes, this);
  double tmp_g_ex__X__exc_spikes = get_g_ex__X__exc_spikes();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_g_ex__X__exc_spikes, tmp_g_ex__X__exc_spikes, this);
  double tmp_g_ex__DOLLAR__X__exc_spikes = get_g_ex__DOLLAR__X__exc_spikes();
  update_value_param(__d, nest::aeif_cond_beta_nestml_names::_g_ex__DOLLAR__X__exc_spikes, tmp_g_ex__DOLLAR__X__exc_spikes, this);

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  StructuralPlasticityNode::set_status(__d);

  // if we get here, temporaries contain consistent set of properties
  set_C_m(tmp_C_m);
  set_t_ref(tmp_t_ref);
  set_V_reset(tmp_V_reset);
  set_g_L(tmp_g_L);
  set_E_L(tmp_E_L);
  set_a(tmp_a);
  set_b(tmp_b);
  set_Delta_T(tmp_Delta_T);
  set_tau_w(tmp_tau_w);
  set_V_th(tmp_V_th);
  set_V_peak(tmp_V_peak);
  set_E_exc(tmp_E_exc);
  set_E_inh(tmp_E_inh);
  set_tau_syn_rise_I(tmp_tau_syn_rise_I);
  set_tau_syn_decay_I(tmp_tau_syn_decay_I);
  set_tau_syn_rise_E(tmp_tau_syn_rise_E);
  set_tau_syn_decay_E(tmp_tau_syn_decay_E);
  set_I_e(tmp_I_e);
  set_V_m(tmp_V_m);
  set_w(tmp_w);
  set_r(tmp_r);
  set_g_in__X__inh_spikes(tmp_g_in__X__inh_spikes);
  set_g_in__DOLLAR__X__inh_spikes(tmp_g_in__DOLLAR__X__inh_spikes);
  set_g_ex__X__exc_spikes(tmp_g_ex__X__exc_spikes);
  set_g_ex__DOLLAR__X__exc_spikes(tmp_g_ex__DOLLAR__X__exc_spikes);




  __d.update_value(nest::aeif_cond_beta_nestml_names::gsl_abs_error_tol, P_.__gsl_abs_error_tol);
  if ( P_.__gsl_abs_error_tol <= 0. )
  {
    throw nest::BadProperty( "The gsl_abs_error_tol must be strictly positive." );
  }
  __d.update_value(nest::aeif_cond_beta_nestml_names::gsl_rel_error_tol, P_.__gsl_rel_error_tol);
  if ( P_.__gsl_rel_error_tol < 0. )
  {
    throw nest::BadProperty( "The gsl_rel_error_tol must be zero or positive." );
  }

  // recompute internal variables in case they are dependent on parameters or state that might have been updated in this call to set_status()
  recompute_internal_variables();
};



#endif /* #ifndef AEIF_COND_BETA_NESTML */
