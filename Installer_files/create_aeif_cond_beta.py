import os
from pathlib import Path

from pynestml.frontend.pynestml_frontend import generate_nest_target


input_path = (
    "/home/gray2/Desktop/nest_als/"
    "AngusGray_als_contralateral_cpg_model/"
    "Installer_files/aeif_cond_beta.nestml"
)

target_path = (
    "/home/gray2/Desktop/nest_als/"
    "nest_models/aeif_cond_beta_component"
)

install_path = (
    "/home/gray2/Desktop/nest_als/"
    "nest_models/aeif_cond_beta_install"
)

# This is the ACTUAL NEST prefix containing bin/nest-config
nest_path = os.environ["VIRTUAL_ENV"]

print("Using NEST prefix:", nest_path)

generate_nest_target(
    input_path=input_path,
    target_path=target_path,
    install_path=install_path,
    logging_level="DEBUG",
    module_name="nestml_aeif_cond_beta_module",
    suffix="_aeif_cond_beta_nestml",
    codegen_opts={
        "nest_path": nest_path
    }
)
