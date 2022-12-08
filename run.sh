#!/bin/bash
mkdir data/conv
g++ -Ofast -o generator generator-multithreaded.cpp
./generator -I data/GRCh38_full_analysis_set_plus_decoy_hla.fa -O data/conv
pip install sentencepiece
python tokenization.py

