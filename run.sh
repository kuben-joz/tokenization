#!/bin/bash
mkdir data
mkdir data/conv
g++ -Ofast -o generator generator-multithreaded.cpp
./generator -I data/GRCh38_full_analysis_set_plus_decoy_hla.fa -O data/conv
python -m venv env
source env/bin/activate
pip install sentencepiece
python tokenization.py

