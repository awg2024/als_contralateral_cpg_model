#!/usr/bin/env python

import nest
import nest.raster_plot
import numpy as np
import sys
import pylab
import math
import matplotlib.pyplot as plt
import random
import scipy
import scipy.fftpack
import time
import numpy as np
import set_network_params as netparams

nn=netparams.neural_network()

class nest_start():
    def __init__(self):
        np.set_printoptions(precision=1,threshold=sys.maxsize)
        #nest.Install("nestml_gap_dopa_module")
        nest.set_verbosity('M_ERROR')
        nest.ResetKernel()

        # Freshly rebuilt NESTML module
        nest.Install(
            "/home/gray2/Desktop/nest_als/"
            "nest_models/aeif_cond_beta_component/build/"
            "nestml_aeif_cond_beta_module.so"
        )

        # Verify that our generated neuron is actually registered
        print(
            "aeif beta models:",
            [m for m in nest.node_models if "aeif_cond_beta" in m]
        )

        # optimum CPU threads: 16 4.95 s for 500ms in Jeeves laboratory. 
        nest.SetKernelStatus({"local_num_threads":16})
        
        nest.SetKernelStatus({"resolution":nn.time_resolution})
        nest.SetKernelStatus({'rng_seed': nn.rng_seed})
        #nest.SetKernelStatus({'print_time': True})
        plt.rcParams.update({'font.size': 20})
        nest.GetKernelStatus("recording_backends")

