#!/bin/bash
mkdir data
mkdir data/conv
wget -P data https://hgdownload.soe.ucsc.edu/goldenPath/hg38/bigZips/analysisSet/hg38.analysisSet.fa.gz
gzip -d data/hg38.analysisSet.fa.gz
g++ -Ofast -o generator generator-multithreaded.cpp
./generator -I data/hg38.analysisSet.fa -O data/conv
python -m venv env
source env/bin/activate
pip install sentencepiece
python tokenization.py

