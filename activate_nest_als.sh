#!/usr/bin/env bash

PROJECT_ROOT="$HOME/Desktop/nest_als/AngusGray_als_contralateral_cpg_model"
VENV="$PROJECT_ROOT/nest_als"
LOCAL_PREFIX="$HOME/local"

NEST_PKG="$VENV/lib/python3.13/site-packages/nest"
NEST_MODULE_DIR="$HOME/Desktop/nest_als/nest_models/aeif_cond_beta_install"

# Activate virtual environment
source "$VENV/bin/activate"

# Compiler
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++

# Local GSL
export CPATH="$LOCAL_PREFIX/include"
export LIBRARY_PATH="$LOCAL_PREFIX/lib"

# NEST Python package
export NEST_PKG="$NEST_PKG"

# NEST external module
export NEST_MODULE_PATH="$NEST_MODULE_DIR"

# Libraries needed by NEST
export LD_LIBRARY_PATH="$NEST_PKG:$LOCAL_PREFIX/lib"

echo "Activated nest_als environment"
echo "Python: $(which python)"
echo "NEST Python package: $NEST_PKG"
echo "NEST module path: $NEST_MODULE_PATH"
echo "NEST module:"
echo "  $NEST_MODULE_DIR/libnestml_aeif_cond_beta_module.so"
echo "GSL include path: $LOCAL_PREFIX/include"
echo "GSL library path: $LOCAL_PREFIX/lib"
echo "LD_LIBRARY_PATH: $LD_LIBRARY_PATH"
