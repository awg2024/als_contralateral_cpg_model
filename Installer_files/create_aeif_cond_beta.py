
import os
import sys
from pathlib import Path

from pynestml.frontend.pynestml_frontend import generate_nest_target

# Location of your NESTML model
model_dir = Path(
    "/Users/angusgray/Desktop/V0d-Publication/github.nosync/"
    "als_contralateral_cpg_model/Installer_files"
)

input_path = model_dir / "aeif_cond_beta.nestml"

# Locations for generated C++ code and compiled module
target_path = model_dir / "aeif_cond_beta_component"
install_path = model_dir / "aeif_cond_beta_install"

# Use NEST from the currently activated Conda environment
nest_path = Path(sys.prefix)

print("NEST prefix:", nest_path)
print("NEST config:", nest_path / "bin" / "nest-config")
print("NESTML input:", input_path)

assert input_path.is_file(), f"Model not found: {input_path}"
assert (nest_path / "bin" / "nest-config").is_file(), "nest-config not found"

generate_nest_target(
    input_path=str(input_path),
    target_path=str(target_path),
    install_path=str(install_path),
    logging_level="INFO",
    module_name="nestml_aeif_cond_beta_module",
    suffix="_aeif_cond_beta_nestml",
    codegen_opts={
        "nest_path": str(nest_path)
    }
)

print("NESTML compilation completed!")
