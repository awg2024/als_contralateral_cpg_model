#!/usr/bin/env bash

PROJECT_ROOT="$HOME/Desktop/nest_als/als_contralateral_cpg_model"
VENV="$PROJECT_ROOT/nest_als"
LOCAL_PREFIX="$HOME/local"

NEST_PKG="$VENV/lib/python3.13/site-packages/nest"
NEST_MODULE_DIR="$HOME/Desktop/nest_als/nest_models/aeif_cond_beta_component"

source "$VENV/bin/activate"

export CC=/usr/bin/gcc
export CXX=/usr/bin/g++

export CPATH="$LOCAL_PREFIX/include${CPATH:+:$CPATH}"
export LIBRARY_PATH="$LOCAL_PREFIX/lib${LIBRARY_PATH:+:$LIBRARY_PATH}"

export NEST_PKG="$NEST_PKG"
export NEST_MODULE_PATH="$NEST_MODULE_DIR"

export LD_LIBRARY_PATH="$NEST_MODULE_DIR:$NEST_PKG:$LOCAL_PREFIX/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

export MPLBACKEND=Agg

echo "Activated nest_als environment"
echo "Python: $(which python)"
echo "NEST Python package: $NEST_PKG"
echo "NEST module directory: $NEST_MODULE_DIR"
echo "NEST module:"
echo "  $NEST_MODULE_DIR/nestml_aeif_cond_beta_module.so"
echo "GSL include path: $LOCAL_PREFIX/include"
echo "GSL library path: $LOCAL_PREFIX/lib"
echo "LD_LIBRARY_PATH:"
echo "$LD_LIBRARY_PATH" | tr ':' '\n'
