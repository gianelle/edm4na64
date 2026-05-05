EDM4na64 - NA64 data model
========================

A data model for NA64 defined with [podio](https://github.com/AIDASoft/podio) and based on [EDM4hep](https://github.com/key4hep/EDM4hep).

## Full Description File

The entire data model is defined with a single YAML file, `edm4na64.yml`.

\verbinclude edm4na64.yaml

## Installing

To install the data model into `~/local`, use the following commands:
```console
git clone https://github.com/gianelle/edm4na64
cd edm4na64
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=~/local
cmake --build build
cmake --install build
```

