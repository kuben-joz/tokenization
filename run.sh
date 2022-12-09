#!/bin/bash
mkdir data/conv
g++ -Ofast -pthread -o generator generator-multithreaded.cpp
./generator -I data/GRCh38_full_analysis_set_plus_decoy_hla.fa -O data/conv
if [ ! -d "env" ]
then
  virtualenv env
fi
source env/bin/activate
pip3 install sentencepiece
python3 tokenization.py

